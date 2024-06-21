#include "Town.h"
#include"Camera.h"
#include"Component.h"
#include"Player.h"
#include"SoundMgr.h"
#include"PositionDoor.h"
#include"SceneDoor.h"
#include"UIMgr.h"
#include"NPC.h"
#include"Shop.h"

CTown::CTown() :m_pComponent(nullptr), m_pShop(nullptr)
{
}

CTown::~CTown()
{
	Release();
}

void CTown::Initialize()
{
	CScenes::Initialize();
	m_pComponent = new CComponent;
	m_objLists[(unsigned int)EObjectType::PLAYER].front()->SetPosition({ 2500.f, 1500.f });
	CCamera::GetInstance()->SetTarget(m_objLists[(unsigned int)EObjectType::PLAYER].front());
	CCamera::GetInstance()->SetCameraMode(1);
	CSoundMgr::Get_Instance()->PlayBGM(L"rynoka_day_normal.wav", 1.f);

	CObj* tempDoor = new CPositionDoor;
	tempDoor->SetPosition({ 3150.f , 1100.f });
	dynamic_cast<CPositionDoor*>(tempDoor)->SetWarpPos({ 5000.f , 1800.f });
	dynamic_cast<CPositionDoor*>(tempDoor)->SetWarpMapSize({ 3800,500,6200, 2500});
	tempDoor->Initialize();
	m_objLists[(unsigned int)EObjectType::DOOR].push_back(tempDoor);


	CObj* tempDoor2 = new CSceneDoor;
	tempDoor2->SetPosition({ 5000.f , 1100.f });
	//dynamic_cast<CSceneDoor*>(tempDoor2)->SetNextScene(ESceneType::FOREST_DUNGEON);
	dynamic_cast<CSceneDoor*>(tempDoor2)->SetNextScene(ESceneType::FOREST_DUNGEON);
	tempDoor2->Initialize();
	m_objLists[(unsigned int)EObjectType::DOOR].push_back(tempDoor2);


	tempDoor2 = new CSceneDoor;
	tempDoor2->SetPosition({ 2500.f , 1050.f });
	dynamic_cast<CSceneDoor*>(tempDoor2)->SetNextScene(ESceneType::HOME);
	tempDoor2->Initialize();
	m_objLists[(unsigned int)EObjectType::DOOR].push_back(tempDoor2);

	//NPC

	CObj* blackSmith = new CNPC;
	blackSmith->SetPosition({ 1800.f, 1050.f });
	blackSmith->Initialize();
	dynamic_cast<CNPC*>(blackSmith)->SetImgKey("NPC_BLACKSMITH");
	m_objLists[(unsigned int)EObjectType::OBSTACLE].push_back(blackSmith);


	CCamera::GetInstance()->SetCurrentMapSize({ 699,433,3201,2567 });
	CUIMgr::GetInstance()->SetUIOn();

	m_pShop = new CShop;
	m_pShop->SetPlayer(m_objLists[(unsigned int)EObjectType::PLAYER].front());
	m_pShop->Initialize();
	CUIMgr::GetInstance()->SetShop(m_pShop);
}

void CTown::Update()
{
	CScenes::Update();
}

void CTown::Render(HDC _hDC)
{
	//699,433,3201,2567
	//3800,500,6200, 2500
	m_pComponent->RenderImage("TOWN_MAIN", _hDC, { 2000.f, 1500.f });
	m_pComponent->RenderImage("TOWN_DUNGEON", _hDC, { 5000.f, 1500.f });

	CScenes::Render(_hDC);

}

void CTown::LateUpdate()
{
	CScenes::LateUpdate();
}

void CTown::Release()
{
	SAFE_DELETE<CComponent*>(m_pComponent);
	SAFE_DELETE<CShop*>(m_pShop);
}
