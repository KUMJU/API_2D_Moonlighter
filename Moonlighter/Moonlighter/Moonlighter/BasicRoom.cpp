#include "BasicRoom.h"
#include"Tile.h"
#include"ScrollMgr.h"
#include"GolemSoldier.h"
#include"Turret.h"
#include"Slime.h"
#include"Camera.h"
#include"FruitTurret.h"
#include"WindLeaf.h"
#include"DungeonDoor.h"
#include"Mushroom.h"

CBasicRoom::CBasicRoom()
{
}

CBasicRoom::CBasicRoom(const TCHAR* _path) : CDungeonRoom(_path)
{
}

CBasicRoom::~CBasicRoom()
{
	Release();
}

void CBasicRoom::Initialize()
{
	Vector renderVec = m_CenterPos->GetPosition();
	Vector StartVec = { renderVec.m_fX - WINCX * 0.5f , renderVec.m_fY - WINCY * 0.5f };
	Vector EndVec = { renderVec.m_fX + WINCX * 0.5f , renderVec.m_fY + WINCY * 0.5f };

	CObj* newTile1 = new CTile(ETileType::WALL, StartVec.m_fX + 155 * 0.5f, StartVec.m_fY + WINCY * 0.5f , 155, WINCY);
	m_ObjectList[(unsigned int)EObjectType::OBSTACLE].push_back(newTile1);
	newTile1 = new CTile(ETileType::WALL, (EndVec.m_fX -155 * 0.5f), StartVec.m_fY +WINCY * 0.5f , 155,WINCY);
	m_ObjectList[(unsigned int)EObjectType::OBSTACLE].push_back(newTile1);

	newTile1 = new CTile(ETileType::WALL,renderVec.m_fX , StartVec.m_fY + (90 * 0.5f), WINCX, 90);
	m_ObjectList[(unsigned int)EObjectType::OBSTACLE].push_back(newTile1);
	newTile1 = new CTile(ETileType::WALL, renderVec.m_fX, EndVec.m_fY - (90 * 0.5f), WINCX, 90);
	m_ObjectList[(unsigned int)EObjectType::OBSTACLE].push_back(newTile1);

	CDungeonRoom::Initialize();
	CreateMon();
	CCamera::GetInstance()->SetTarget(m_CenterPos);
	CCamera::GetInstance()->SetCameraMode(2);

	m_IsInitDone = true;

}

void CBasicRoom::Update()
{
}

void CBasicRoom::Render(HDC _hDC)
{

	Vector renderVec = CCamera::GetInstance()->GetRenderPos(m_CenterPos->GetPosition());
	AnimInfo tempInfo = CResourceMgr::GetInstance()->FindRes(m_strBackGroundKey)->GetResInfo();

	GdiTransparentBlt(_hDC,
		renderVec.m_fX- WINCX*0.5f,
		renderVec.m_fY - WINCY * 0.5f,
		tempInfo.iSizeX,
		tempInfo.iSizeY,
		CResourceMgr::GetInstance()->FindRes(m_strBackGroundKey)->GetMemDC(),
		0,
		0,
		tempInfo.iSizeX,
		tempInfo.iSizeY,
		RGB(0, 0, 0));

}


void CBasicRoom::Release()
{
	SAFE_DELETE<CObj*>(m_CenterPos);

}

void CBasicRoom::LateUpdate()
{
	if (true == m_RoomClear || m_IsInitDone == false)
		return;

	if (m_ObjectList[static_cast<unsigned int>(EObjectType::MONSTER)].empty()) {
		m_RoomClear = true;
		for (auto& iter : m_doorList) {
			dynamic_cast<CDungeonDoor*>(iter)->SetDoorOpen();
		}
	}

}

void CBasicRoom::SettingCamera()
{
	CCamera::GetInstance()->SetTarget(m_CenterPos);
	CCamera::GetInstance()->SetCameraMode(2);
}

void CBasicRoom::CreateMon()
{

	if (m_strBackGroundKey == "BackGround1") {
		if (1 == m_iRoomNum) {
			CObj* newGolem = new CGolemSoldier();
			newGolem->Initialize();
			newGolem->SetPosition({ 3800.f,3800.f });
			dynamic_cast<CGolemSoldier*>(newGolem)->SetItemList(&(m_ObjectList[(unsigned int)EObjectType::ITEM]));
			dynamic_cast<CGolemSoldier*>(newGolem)->SetEffectList(&(m_ObjectList[(unsigned int)EObjectType::EFFECT]));


			m_ObjectList[(unsigned int)EObjectType::MONSTER].push_back(newGolem);


			CObj* newTurret = new CTurret();
			newTurret->Initialize();
			newTurret->SetPosition({ 4300.f,4200.f });
			dynamic_cast<CTurret*>(newTurret)->SetProjList(&(m_ObjectList[(unsigned int)EObjectType::MON_PROJ]));
			dynamic_cast<CTurret*>(newTurret)->SetItemList(&(m_ObjectList[(unsigned int)EObjectType::ITEM]));
			dynamic_cast<CTurret*>(newTurret)->SetEffectList(&(m_ObjectList[(unsigned int)EObjectType::EFFECT]));
			m_ObjectList[(unsigned int)EObjectType::MONSTER].push_back(newTurret);

		}
		else if (2 == m_iRoomNum) {

			CObj* newSlime = new CSlime();
			newSlime->Initialize();
			newSlime->SetPosition({ 3800.f,3100.f });
			dynamic_cast<CSlime*>(newSlime)->SetEffectList(&(m_ObjectList[(unsigned int)EObjectType::EFFECT]));
			m_ObjectList[(unsigned int)EObjectType::MONSTER].push_back(newSlime);


			CObj* newSlime2 = new CSlime();
			newSlime2->Initialize();
			newSlime2->SetPosition({ 4200.f,3100.f });
			dynamic_cast<CSlime*>(newSlime2)->SetEffectList(&(m_ObjectList[(unsigned int)EObjectType::EFFECT]));
			m_ObjectList[(unsigned int)EObjectType::MONSTER].push_back(newSlime2);

		}

	}
	else if (m_strBackGroundKey == "BackGround2") {
		if (1 == m_iRoomNum) {
			CObj* newMush = new CMushroom();
			newMush->Initialize();
			newMush->SetPosition({ 2400.f,4210.f });
			dynamic_cast<CMushroom*>(newMush)->SetEffectList(&(m_ObjectList[(unsigned int)EObjectType::EFFECT]));
			m_ObjectList[(unsigned int)EObjectType::MONSTER].push_back(newMush);

			newMush = new CMushroom();
			newMush->Initialize();
			newMush->SetPosition({ 2400.f,3770.f });
			dynamic_cast<CMushroom*>(newMush)->SetEffectList(&(m_ObjectList[(unsigned int)EObjectType::EFFECT]));
			m_ObjectList[(unsigned int)EObjectType::MONSTER].push_back(newMush);

		}
		else if (3 == m_iRoomNum) {

			CObj* testMonster = new CFruitTurret;
			testMonster->SetPosition({ m_CenterPos->GetPosition().m_fX + 350.f ,m_CenterPos->GetPosition().m_fY - 100.f });
			dynamic_cast<CFruitTurret*>(testMonster)->SetProjList(&m_ObjectList[(unsigned int)EObjectType::MON_PROJ]);
			dynamic_cast<CFruitTurret*>(testMonster)->SetEffectList(&(m_ObjectList[(unsigned int)EObjectType::EFFECT]));
			testMonster->Initialize();
			static_cast<CFruitTurret*>(testMonster)->SetDirNum(2);
			m_ObjectList[(unsigned int)EObjectType::MONSTER].push_back(testMonster);

			testMonster = new CFruitTurret;
			testMonster->SetPosition({ m_CenterPos->GetPosition().m_fX - 350.f ,m_CenterPos->GetPosition().m_fY - 100.f });
			dynamic_cast<CFruitTurret*>(testMonster)->SetProjList(&m_ObjectList[(unsigned int)EObjectType::MON_PROJ]);
			dynamic_cast<CFruitTurret*>(testMonster)->SetEffectList(&(m_ObjectList[(unsigned int)EObjectType::EFFECT]));
			testMonster->Initialize();
			static_cast<CFruitTurret*>(testMonster)->SetDirNum(1);

			m_ObjectList[(unsigned int)EObjectType::MONSTER].push_back(testMonster);

		}
	}
}
