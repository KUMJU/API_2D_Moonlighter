#include "ForestDungeon.h"
#include"BossRoom.h"
#include"UIMgr.h"
#include"Player.h"
#include"MapCenter.h"
#include"BasicRoom.h"
#include"SoundMgr.h"
#include"DungeonDoor.h"
#include"HiddenMap.h"
#include"PuzzleRoom.h"
 
CForestDungeon::CForestDungeon()
{
}

CForestDungeon::~CForestDungeon()
{
	Release();
}

void CForestDungeon::Initialize()
{
	m_iMaxRoomNum = 6;
	m_RoomList.reserve(m_iMaxRoomNum);

	CObj* newCenter1 = new CMapCenter;
	newCenter1->SetPosition({ 1000.f,4000.f });
	CObj* newCenter2 = new CMapCenter;
	newCenter2->SetPosition({ 1000.f + WINCX,4000.f });
	CObj* newCenter3 = new CMapCenter;
	newCenter3->SetPosition({ 1000.f + WINCX *2 ,4000.f });

	CObj* newCenter4 = new CMapCenter;
	newCenter4->SetPosition({ 1000.f + WINCX *2,4000.f + WINCY });
	CObj* newCenter5 = new CMapCenter;
	newCenter5->SetPosition({ 1000.f + WINCX * 2,4000.f - WINCY });

	//StartRoom
	m_RoomList.push_back(new CBasicRoom());
	m_RoomList.back()->SetBackGroundKey("BackGround2");
	m_RoomList.back()->SetRoomNumber(0);
	m_RoomList.back()->SetCenterPos(newCenter1);
	
	CObj* newDoor1 = new CDungeonDoor(EDirection::RIGHT, 1, 2);
	newDoor1->SetPosition({ 1500.f, 4000.f });
	newDoor1->Initialize();
	m_objLists[static_cast<unsigned int>(EObjectType::DOOR)].push_back(newDoor1);
	dynamic_cast<CBasicRoom*>(m_RoomList.back())->InsertDoorList(newDoor1);


	//Room1
	m_RoomList.push_back(new CBasicRoom());
	m_RoomList.back()->SetBackGroundKey("BackGround2");
	m_RoomList.back()->SetRoomNumber(1);
	m_RoomList.back()->SetCenterPos(newCenter2);

	newDoor1 = new CDungeonDoor(EDirection::RIGHT, 2, 2);
	newDoor1->SetPosition({ 2800.f, 4000.f });
	newDoor1->Initialize();
	m_objLists[static_cast<unsigned int>(EObjectType::DOOR)].push_back(newDoor1);
	dynamic_cast<CBasicRoom*>(m_RoomList.back())->InsertDoorList(newDoor1);

	newDoor1 = new CDungeonDoor(EDirection::LEFT, 0, 2);
	newDoor1->SetPosition({ 1800.f, 4000.f });
	newDoor1->Initialize();
	m_objLists[static_cast<unsigned int>(EObjectType::DOOR)].push_back(newDoor1);
	dynamic_cast<CBasicRoom*>(m_RoomList.back())->InsertDoorList(newDoor1);


	//Room2
	m_RoomList.push_back(new CPuzzleRoom());
	m_RoomList.back()->SetBackGroundKey("BackGround2");
	m_RoomList.back()->SetRoomNumber(2);
	m_RoomList.back()->SetCenterPos(newCenter3);


	//center 3560,4000
	newDoor1 = new CDungeonDoor(EDirection::RIGHT, 5, 2);
	newDoor1->SetPosition({ 4010.f, 4000.f });
	newDoor1->Initialize();
	m_objLists[static_cast<unsigned int>(EObjectType::DOOR)].push_back(newDoor1);
	dynamic_cast<CPuzzleRoom*>(m_RoomList.back())->InsertDoorList(newDoor1);

	newDoor1 = new CDungeonDoor(EDirection::LEFT, 1, 2);
	newDoor1->SetPosition({ 3060.f, 4000.f });
	newDoor1->Initialize();
	m_objLists[static_cast<unsigned int>(EObjectType::DOOR)].push_back(newDoor1);
	dynamic_cast<CPuzzleRoom*>(m_RoomList.back())->InsertDoorList(newDoor1);

	newDoor1 = new CDungeonDoor(EDirection::UP, 4, 2);
	newDoor1->SetPosition({ 3560.f, 3680.f });
	newDoor1->Initialize();
	m_objLists[static_cast<unsigned int>(EObjectType::DOOR)].push_back(newDoor1);
	dynamic_cast<CPuzzleRoom*>(m_RoomList.back())->InsertDoorList(newDoor1);

	newDoor1 = new CDungeonDoor(EDirection::DOWN, 3, 2);
	newDoor1->SetPosition({ 3560.f, 4270.f });
	newDoor1->Initialize();
	m_objLists[static_cast<unsigned int>(EObjectType::DOOR)].push_back(newDoor1);
	dynamic_cast<CPuzzleRoom*>(m_RoomList.back())->InsertDoorList(newDoor1);

	//Room3
	m_RoomList.push_back(new CBasicRoom());
	m_RoomList.back()->SetBackGroundKey("BackGround2");
	m_RoomList.back()->SetRoomNumber(3);
	m_RoomList.back()->SetCenterPos(newCenter4);

	newDoor1 = new CDungeonDoor(EDirection::UP, 2, 2);
	newDoor1->SetPosition({ 3560.f, 4470.f });
	newDoor1->Initialize();
	m_objLists[static_cast<unsigned int>(EObjectType::DOOR)].push_back(newDoor1);
	dynamic_cast<CDungeonRoom*>(m_RoomList.back())->InsertDoorList(newDoor1);

	//Room4 
	m_RoomList.push_back(new CHiddenMap());
	dynamic_cast<CHiddenMap*>(m_RoomList.back())->SetDungeonNum(2);
	m_RoomList.back()->SetRoomNumber(4);
	m_RoomList.back()->SetCenterPos(newCenter5);

	newDoor1 = new CDungeonDoor(EDirection::DOWN, 2, 2);
	newDoor1->SetPosition({ 3560.f, 3570.f });
	newDoor1->Initialize();
	m_objLists[static_cast<unsigned int>(EObjectType::DOOR)].push_back(newDoor1);
	dynamic_cast<CDungeonRoom*>(m_RoomList.back())->InsertDoorList(newDoor1);

	//BossRoom
	m_RoomList.push_back(new CBossRoom);
	m_RoomList.back()->SetBackGroundKey("BackGround_Boss2");
	 
	

	CScenes::Initialize();

	m_RoomList[m_iCurrentRoomNum]->SetObjList(m_objLists);
	m_RoomList[m_iCurrentRoomNum]->Initialize();
	CUIMgr::GetInstance()->SetUIOn();
	CSoundMgr::Get_Instance()->StopSound(SOUND_BGM);
	CSoundMgr::Get_Instance()->PlayBGM(L"forest_dungeon_floor.wav", 1.f);

	m_objLists[static_cast<unsigned int>(EObjectType::PLAYER)].front()->SetPosition({ 1000.f,4000.f });

	CUIMgr::GetInstance()->SetScrollName("SCROLL2");
	CUIMgr::GetInstance()->ScrollOn();
	CUIMgr::GetInstance()->DungeonNameVisible();

}

void CForestDungeon::Update()
{
	m_RoomList[m_iCurrentRoomNum]->Update();
	CScenes::Update();

}

void CForestDungeon::Render(HDC _hDC)
{
	for (auto iter : m_RoomList) {
		iter->Render(_hDC);
	}

	CScenes::Render(_hDC);

}

void CForestDungeon::LateUpdate()
{
	CScenes::LateUpdate();
	
	m_RoomList[m_iCurrentRoomNum]->LateUpdate();

	if (!m_RoomList.empty()) {
		for (auto& iter : m_objLists[static_cast<unsigned int>(EObjectType::DOOR)]) {
			if (dynamic_cast<CDungeonDoor*>(iter)->GetPlrTouch()) {

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

void CForestDungeon::Release()
{
	for (auto& iter : m_RoomList) {
		SAFE_DELETE<CDungeonRoom*>(iter);
	}

	CScenes::Release();
}
