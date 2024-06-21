#include "HiddenMap.h"
#include"Obj.h"
#include"MapCenter.h"
#include"Tile.h"
#include"DungeonDoor.h"
#include"SoundMgr.h"
#include"HealingPool.h"
#include"Turret.h"
#include"Mushroom.h"
#include"NPC.h"
#include"DisplayItem.h"
#include"WindLeaf.h"

CHiddenMap::CHiddenMap() : m_hiddenCenterPos(nullptr)
{
}

CHiddenMap::CHiddenMap(const TCHAR* _path) : CDungeonRoom(_path)
{
}

CHiddenMap::~CHiddenMap()
{
	Release();
}

void CHiddenMap::Initialize()
{
	//Collision

	Vector renderVec = m_CenterPos->GetPosition();
	Vector StartVec = { renderVec.m_fX - WINCX * 0.5f , renderVec.m_fY - WINCY * 0.5f };
	Vector EndVec = { renderVec.m_fX + WINCX * 0.5f , renderVec.m_fY + WINCY * 0.5f };

	CObj* newTile1 = new CTile(ETileType::WALL, StartVec.m_fX + 155 * 0.5f, StartVec.m_fY + WINCY * 0.5f, 155, WINCY);
	m_ObjectList[(unsigned int)EObjectType::OBSTACLE].push_back(newTile1);
	CObj* newTile2 = new CTile(ETileType::WALL, (EndVec.m_fX - 155 * 0.5f), StartVec.m_fY + 215 * 0.5f, 155, 215);
	m_ObjectList[(unsigned int)EObjectType::OBSTACLE].push_back(newTile2);
	newTile2 = new CTile(ETileType::WALL, (EndVec.m_fX - 155 * 0.5f), EndVec.m_fY - 375 * 0.5f, 155, 375);
	m_ObjectList[(unsigned int)EObjectType::OBSTACLE].push_back(newTile2);


	CObj* newTile3 = new CTile(ETileType::WALL, renderVec.m_fX, StartVec.m_fY + (90 * 0.5f), WINCX, 90);
	m_ObjectList[(unsigned int)EObjectType::OBSTACLE].push_back(newTile3);
	CObj* newTile4 = new CTile(ETileType::WALL, renderVec.m_fX, EndVec.m_fY - (90 * 0.5f), WINCX, 90);
	m_ObjectList[(unsigned int)EObjectType::OBSTACLE].push_back(newTile4);

	//hidden room collision

	renderVec = { renderVec.m_fX + WINCX , renderVec.m_fY };
	StartVec = { renderVec.m_fX - WINCX * 0.5f , renderVec.m_fY - WINCY * 0.5f };
	EndVec = { renderVec.m_fX + WINCX * 0.5f , renderVec.m_fY + WINCY * 0.5f };

	newTile2 = new CTile(ETileType::WALL, (StartVec.m_fX + 155 * 0.5f), StartVec.m_fY + 215 * 0.5f, 155, 215);
	m_ObjectList[(unsigned int)EObjectType::OBSTACLE].push_back(newTile2);
	newTile2 = new CTile(ETileType::WALL, (StartVec.m_fX + 155 * 0.5f), EndVec.m_fY - 375 * 0.5f, 155, 375);
	m_ObjectList[(unsigned int)EObjectType::OBSTACLE].push_back(newTile2);

	
	newTile2 = new CTile(ETileType::WALL, (EndVec.m_fX - 155 * 0.5f), StartVec.m_fY + WINCY * 0.5f, 155, WINCY);
	m_ObjectList[(unsigned int)EObjectType::OBSTACLE].push_back(newTile2);

	newTile3 = new CTile(ETileType::WALL, renderVec.m_fX, StartVec.m_fY + (90 * 0.5f), WINCX, 90);
	m_ObjectList[(unsigned int)EObjectType::OBSTACLE].push_back(newTile3);
	newTile4 = new CTile(ETileType::WALL, renderVec.m_fX, EndVec.m_fY - (90 * 0.5f), WINCX, 90);
	m_ObjectList[(unsigned int)EObjectType::OBSTACLE].push_back(newTile4);

	//히든방 센터 pos
	m_hiddenCenterPos = new CMapCenter;
	m_hiddenCenterPos->SetPosition({m_CenterPos->GetPosition().m_fX + WINCX ,m_CenterPos->GetPosition().m_fY});

	//히든방으로 가는 길목에 있는벽
	CObj* pHiddenWall = new CTile;
	pHiddenWall->Initialize();
	pHiddenWall->SetPosition({ m_CenterPos->GetPosition().m_fX + WINCX * 0.5f - 64.f, m_CenterPos->GetPosition().m_fY - 101.f });
	dynamic_cast<CTile*>(pHiddenWall)->SetImgKeyInt(8);
	m_ObjectList[(unsigned int)EObjectType::OBSTACLE].push_back(pHiddenWall);

	CDungeonRoom::Initialize();
	
	CreateSpcObj();
	CreateMon();

	m_iPrevRoom = 2;
	CCamera::GetInstance()->SetTarget(m_CenterPos);
	CCamera::GetInstance()->SetCameraMode(2);

	m_IsInitDone = true;

}

void CHiddenMap::Update()
{

}

void CHiddenMap::Render(HDC _hDC)
{
	if (1 == m_iDungeonNum) {
		m_strBackImg = "DUNGEON_HIDDEN";
	}
	else if (2 == m_iDungeonNum) {
		m_strBackImg = "DUNGEON_HIDDEN2";

	}

	Vector renderVec = CCamera::GetInstance()->GetRenderPos(m_CenterPos->GetPosition());
	AnimInfo tempInfo = CResourceMgr::GetInstance()->FindRes(m_strBackImg)->GetResInfo();

	GdiTransparentBlt(_hDC,
		renderVec.m_fX - WINCX * 0.5f,
		renderVec.m_fY - WINCY * 0.5f,
		tempInfo.iSizeX,
		tempInfo.iSizeY,
		CResourceMgr::GetInstance()->FindRes(m_strBackImg)->GetMemDC(),
		0,
		0,
		tempInfo.iSizeX,
		tempInfo.iSizeY,
		RGB(0, 0, 0));

}

void CHiddenMap::LateUpdate()
{

	if (m_ObjectList[(unsigned int)EObjectType::PLAYER].front()->GetPosition().m_fX - m_CenterPos->GetPosition().m_fX > WINCX * 0.5f) {
		CCamera::GetInstance()->SetTarget(m_hiddenCenterPos);

		if (1 != m_iPrevRoom) {
			if (1 == m_iDungeonNum) {
				CSoundMgr::Get_Instance()->StopSound(SOUND_BGM);
				CSoundMgr::Get_Instance()->PlayBGM(L"onsen_room.wav", 1.f);
			}
			else if (2 == m_iDungeonNum) {
				CSoundMgr::Get_Instance()->StopSound(SOUND_BGM);
				CSoundMgr::Get_Instance()->PlayBGM(L"hiddenShopBGM.wav", 0.4f);
			}

			m_iPrevRoom = 1;
		}

	}
	else {
		CCamera::GetInstance()->SetTarget(m_CenterPos);
		if (2 != m_iPrevRoom) {
			if (1 == m_iDungeonNum) {
				CSoundMgr::Get_Instance()->StopSound(SOUND_BGM);
				CSoundMgr::Get_Instance()->PlayBGM(L"golem_dungeon_floor.wav", 1.f);
			}
			else if (2 == m_iDungeonNum) {
				CSoundMgr::Get_Instance()->StopSound(SOUND_BGM);
				CSoundMgr::Get_Instance()->PlayBGM(L"forest_dungeon_floor.wav", 1.f);
			}
			m_iPrevRoom = 2;
		}

	}

	if (true == m_RoomClear || m_IsInitDone == false)
		return;

	if (m_ObjectList[static_cast<unsigned int>(EObjectType::MONSTER)].empty()) {
		m_RoomClear = true;
		for (auto& iter : m_doorList) {
			dynamic_cast<CDungeonDoor*>(iter)->SetDoorOpen();
		}
	}
}

void CHiddenMap::Release()
{
	SAFE_DELETE<CObj*>(m_CenterPos);
	SAFE_DELETE<CObj*>(m_hiddenCenterPos);
}

void CHiddenMap::CreateMon()
{
	if (1 == m_iDungeonNum) {
		CObj* newTurret = new CTurret();
		newTurret->Initialize();
		newTurret->SetPosition({ m_CenterPos->GetPosition().m_fX +300.f,m_CenterPos->GetPosition().m_fY - 200.f });
		dynamic_cast<CTurret*>(newTurret)->SetProjList(&(m_ObjectList[(unsigned int)EObjectType::MON_PROJ]));
		dynamic_cast<CTurret*>(newTurret)->SetItemList(&(m_ObjectList[(unsigned int)EObjectType::ITEM]));
		dynamic_cast<CTurret*>(newTurret)->SetEffectList(&(m_ObjectList[(unsigned int)EObjectType::EFFECT]));
		m_ObjectList[(unsigned int)EObjectType::MONSTER].push_back(newTurret);

		newTurret = new CTurret();
		newTurret->Initialize();
		newTurret->SetPosition({ m_CenterPos->GetPosition().m_fX - 300.f,m_CenterPos->GetPosition().m_fY + 200.f });
		dynamic_cast<CTurret*>(newTurret)->SetProjList(&(m_ObjectList[(unsigned int)EObjectType::MON_PROJ]));
		dynamic_cast<CTurret*>(newTurret)->SetItemList(&(m_ObjectList[(unsigned int)EObjectType::ITEM]));
		dynamic_cast<CTurret*>(newTurret)->SetEffectList(&(m_ObjectList[(unsigned int)EObjectType::EFFECT]));
		m_ObjectList[(unsigned int)EObjectType::MONSTER].push_back(newTurret);

	}
	else if (2 == m_iDungeonNum) {


		CObj* testMonster2 = new CWindLeaf;
		testMonster2->SetPosition({ m_CenterPos->GetPosition().m_fX - 150.f ,m_CenterPos->GetPosition().m_fY + 200.f });
		dynamic_cast<CWindLeaf*>(testMonster2)->SetProjList(&m_ObjectList[(unsigned int)EObjectType::MON_PROJ]);
		testMonster2->Initialize();
		dynamic_cast<CWindLeaf*>(testMonster2)->SetEffectList(&(m_ObjectList[(unsigned int)EObjectType::EFFECT]));
		m_ObjectList[(unsigned int)EObjectType::MONSTER].push_back(testMonster2);

		testMonster2 = new CWindLeaf;
		testMonster2->SetPosition({ m_CenterPos->GetPosition().m_fX + 200.f ,m_CenterPos->GetPosition().m_fY + 120.f });
		dynamic_cast<CWindLeaf*>(testMonster2)->SetProjList(&m_ObjectList[(unsigned int)EObjectType::MON_PROJ]);
		testMonster2->Initialize();
		dynamic_cast<CWindLeaf*>(testMonster2)->SetEffectList(&(m_ObjectList[(unsigned int)EObjectType::EFFECT]));
		m_ObjectList[(unsigned int)EObjectType::MONSTER].push_back(testMonster2);

	}

}

void CHiddenMap::CreateSpcObj()
{
	if (1 == m_iDungeonNum) {
		CObj* newHealingPool = new CHealingPool;
		newHealingPool->SetPosition(m_hiddenCenterPos->GetPosition());
		newHealingPool->Initialize();
		m_ObjectList[(unsigned int)EObjectType::OBSTACLE].push_back(newHealingPool);
	}
	else if (2 == m_iDungeonNum) {

		Vector hiddenCenterPos = m_hiddenCenterPos->GetPosition();

		CObj* newNpc = new CNPC;
		dynamic_cast<CNPC*>(newNpc)->SetImgKey("HIDDENSHOP_NPC");
		dynamic_cast<CNPC*>(newNpc)->SetNpcType(1);
		newNpc->SetPosition({ hiddenCenterPos.m_fX , hiddenCenterPos.m_fY - 100.f });
		newNpc->Initialize();
		m_ObjectList[(unsigned int)EObjectType::OBSTACLE].push_back(newNpc);

		CObj* newTile = new CTile;
		dynamic_cast<CTile*>(newTile)->SetImgKeyInt(13);
		newTile->SetPosition({ hiddenCenterPos.m_fX - 60.f , hiddenCenterPos.m_fY - 100.f });
		newTile->Initialize();
		m_ObjectList[(unsigned int)EObjectType::OBSTACLE].push_back(newTile);

		newTile = new CTile;
		dynamic_cast<CTile*>(newTile)->SetImgKeyInt(13);
		newTile->SetPosition({ hiddenCenterPos.m_fX + 60.f , hiddenCenterPos.m_fY - 100.f });
		newTile->Initialize();
		m_ObjectList[(unsigned int)EObjectType::OBSTACLE].push_back(newTile);


		//DisplayItem

		newTile = new CDisplayItem;
		dynamic_cast<CDisplayItem*>(newTile)->SetItemNum(0);
		newTile->SetPosition({ hiddenCenterPos.m_fX - 80.f , hiddenCenterPos.m_fY});
		newTile->Initialize();
		m_ObjectList[(unsigned int)EObjectType::OBSTACLE].push_back(newTile);

		newTile = new CDisplayItem;
		dynamic_cast<CDisplayItem*>(newTile)->SetItemNum(1);
		newTile->SetPosition({ hiddenCenterPos.m_fX , hiddenCenterPos.m_fY});
		newTile->Initialize();
		m_ObjectList[(unsigned int)EObjectType::OBSTACLE].push_back(newTile);

		newTile = new CDisplayItem;
		dynamic_cast<CDisplayItem*>(newTile)->SetItemNum(2);
		newTile->SetPosition({ hiddenCenterPos.m_fX + 80.f , hiddenCenterPos.m_fY });
		newTile->Initialize();
		m_ObjectList[(unsigned int)EObjectType::OBSTACLE].push_back(newTile);

	}		

}
