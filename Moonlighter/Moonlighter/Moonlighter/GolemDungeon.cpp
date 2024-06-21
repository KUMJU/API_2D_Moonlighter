#include "GolemDungeon.h"
#include "ResourceMgr.h"
#include "Tile.h"
#include"UIMgr.h"
#include"BasicRoom.h"
#include"BossRoom.h"
#include"Player.h"
#include"MapCenter.h"
#include"SoundMgr.h"
#include"HiddenMap.h"
#include"DungeonDoor.h"

CGolemDungeon::CGolemDungeon()
{
}

CGolemDungeon::~CGolemDungeon()
{
	Release();
}

void CGolemDungeon::Initialize()
{

	m_iMaxRoomNum = 5;
	m_RoomList.reserve(m_iMaxRoomNum);

	CObj* newCenter0 = new CMapCenter;
	newCenter0->SetPosition({ 4000.f,4000.f + WINCY });
	CObj* newCenter1 = new CMapCenter;
	newCenter1->SetPosition({ 4000.f,4000.f });
	CObj* newCenter2 = new CMapCenter;
	newCenter2->SetPosition({ 4000.f,4000.f - WINCY });
	CObj* newCenter3 = new CMapCenter;
	newCenter3->SetPosition({ 4000.f,4000.f - WINCY * 2 });


	//StartRoom
	m_RoomList.push_back(new CBasicRoom()); // L"../Data/Stage1.dat"
	m_RoomList.back()->SetBackGroundKey("BackGround1");
	m_RoomList.back()->SetRoomNumber(0);
	m_RoomList.back()->SetCenterPos(newCenter0);

	CObj* newDoor1 = new CDungeonDoor(EDirection::UP, 1, 1);
	newDoor1->SetPosition({ 4000.f, 4440.f });
	newDoor1->Initialize();
	m_objLists[static_cast<unsigned int>(EObjectType::DOOR)].push_back(newDoor1);
	dynamic_cast<CDungeonRoom*>(m_RoomList.back())->InsertDoorList(newDoor1);

	//Room1
	m_RoomList.push_back(new CBasicRoom(L"../Data/Dungeon1_1.dat")); // L"../Data/Dungeon1_1.dat"
	m_RoomList.back()->SetBackGroundKey("BackGround1");
	m_RoomList.back()->SetRoomNumber(1);
	m_RoomList.back()->SetCenterPos(newCenter1);

	CObj* newDoor2 = new CDungeonDoor(EDirection::UP,2, 1);
	newDoor2->SetPosition({ 3800.f, 3720.f });
	newDoor2->Initialize();
	m_objLists[static_cast<unsigned int>(EObjectType::DOOR)].push_back(newDoor2);
	dynamic_cast<CDungeonRoom*>(m_RoomList.back())->InsertDoorList(newDoor2);

	CObj* newDoor3 = new CDungeonDoor(EDirection::DOWN, 0, 1);
	newDoor3->SetPosition({ 4000.f, 4280.f });
	newDoor3->Initialize();
	m_objLists[static_cast<unsigned int>(EObjectType::DOOR)].push_back(newDoor3);
	dynamic_cast<CDungeonRoom*>(m_RoomList.back())->InsertDoorList(newDoor3);


	//Room2

	m_RoomList.push_back(new CBasicRoom(L"../Data/Dungeon1_3.dat")); // L"../Data/Dungeon1_2.dat"
	m_RoomList.back()->SetBackGroundKey("BackGround1");
	m_RoomList.back()->SetRoomNumber(2);
	m_RoomList.back()->SetCenterPos(newCenter2);

	CObj* newDoor4 = new CDungeonDoor(EDirection::UP, 3, 1);
	newDoor4->SetPosition({ 4300.f, 3000.f });
	newDoor4->Initialize();
	m_objLists[static_cast<unsigned int>(EObjectType::DOOR)].push_back(newDoor4);
	dynamic_cast<CDungeonRoom*>(m_RoomList.back())->InsertDoorList(newDoor4);

	newDoor1 = new CDungeonDoor(EDirection::DOWN, 2, 1);
	newDoor1->SetPosition({ 3800.f, 3550.f });
	newDoor1->Initialize();
	m_objLists[static_cast<unsigned int>(EObjectType::DOOR)].push_back(newDoor1);
	dynamic_cast<CDungeonRoom*>(m_RoomList.back())->InsertDoorList(newDoor1);

	//Room3
	m_RoomList.push_back(new CHiddenMap(L"../Data/Dungeon1_2.dat"));
	dynamic_cast<CHiddenMap*>(m_RoomList.back())->SetDungeonNum(1);
	m_RoomList.back()->SetRoomNumber(3);
	m_RoomList.back()->SetCenterPos(newCenter3);

	newDoor1 = new CDungeonDoor(EDirection::UP, 4, 1);
	newDoor1->SetPosition({ 4000.f, 2300.f });
	newDoor1->Initialize();
	m_objLists[static_cast<unsigned int>(EObjectType::DOOR)].push_back(newDoor1);
	dynamic_cast<CDungeonRoom*>(m_RoomList.back())->InsertDoorList(newDoor1);

	newDoor1 = new CDungeonDoor(EDirection::DOWN, 2,1);
	newDoor1->SetPosition({ 4300.f, 2850.f });
	newDoor1->Initialize();
	m_objLists[static_cast<unsigned int>(EObjectType::DOOR)].push_back(newDoor1);
	dynamic_cast<CDungeonRoom*>(m_RoomList.back())->InsertDoorList(newDoor1);


	//Room4
	m_RoomList.push_back(new CBossRoom);
	m_RoomList.back()->SetBackGroundKey("BackGround_Boss1");
	m_RoomList.back()->SetRoomNumber(4);


	CScenes::Initialize();

	m_RoomList[m_iCurrentRoomNum]->SetObjList(m_objLists);
	m_RoomList[m_iCurrentRoomNum]->Initialize();
	CUIMgr::GetInstance()->SetUIOn();

	CSoundMgr::Get_Instance()->PlayBGM(L"golem_dungeon_floor.wav", 1.f);
	m_objLists[(unsigned int)EObjectType::PLAYER].front()->SetPosition({ 4000.f , 4720.f});

	CUIMgr::GetInstance()->SetScrollName("SCROLL1");
	CUIMgr::GetInstance()->ScrollOn();
	CUIMgr::GetInstance()->DungeonNameVisible();

}

void CGolemDungeon::Update()
{
	CScenes::Update();

}

void CGolemDungeon::Render(HDC _hDC)
{

	for (auto iter : m_RoomList) {
		iter->Render(_hDC);
	}

	CScenes::Render(_hDC);

}

void CGolemDungeon::LateUpdate()
{
	CScenes::LateUpdate();
	m_RoomList[m_iCurrentRoomNum]->LateUpdate();

	if (!m_RoomList.empty()) {
		for (auto& iter : m_objLists[static_cast<unsigned int>(EObjectType::DOOR)]) {
			if (
				static_cast<CDungeonDoor*>(iter)->GetPlrTouch()) {

				m_iCurrentRoomNum = dynamic_cast<CDungeonDoor*>(iter)->GetNextRoomNum();
				if (!(dynamic_cast<CDungeonRoom*>(m_RoomList[m_iCurrentRoomNum])->GetInItDone())) {
					m_RoomList[m_iCurrentRoomNum]->SetObjList(m_objLists);
					m_RoomList[m_iCurrentRoomNum]->Initialize();
				}
				dynamic_cast<CDungeonRoom*>(m_RoomList[m_iCurrentRoomNum])->SettingCamera();

			}
		}
	}
}

void CGolemDungeon::Release()
{
	for (auto& iter : m_RoomList) {
		SAFE_DELETE<CDungeonRoom*>(iter);
	}


	CScenes::Release();

}
