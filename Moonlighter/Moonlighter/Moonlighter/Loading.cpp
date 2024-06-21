#include "Loading.h"
#include"SceneMgr.h"
#include"ResourceMgr.h"
#include"MyResource.h"
#include"GameMgr.h"
#include"Player.h"

CLoading::CLoading()
{
}

CLoading::~CLoading()
{
}

void CLoading::Initialize()
{
	m_iCurrentFlag = CResourceMgr::GetInstance()->GetCurrentFlag();

	if (CResourceMgr::GetInstance()->IsDungeonResEmpty()) {
		CResourceMgr::GetInstance()->ReleasePrevData();
	}

}

void CLoading::Update()
{

	switch (m_iCurrentFlag)
	{
	case 0: // 기본 데이터 + 던전1 데이터 로드
		if (false == m_PlayerData) {
			CResourceMgr::GetInstance()->PlayerDataLoad();
			m_PlayerData = true;
		}
		else if (false == m_Dungeon1Data) {
			CResourceMgr::GetInstance()->Dungeon1DataLoad();
			m_Dungeon1Data = true;
		}
		else if (false == m_UIData) {
			CResourceMgr::GetInstance()->UIDataLoad();
			m_UIData = true;
			m_LoadingDone = true;
		}
		break;

	case 1: // 마을 리소스 로드
		if (false == m_PlayerData) {
			CResourceMgr::GetInstance()->PlayerDataLoad();
			m_PlayerData = true;
		}
		else if (false == m_Dungeon1Data) {
			CResourceMgr::GetInstance()->UIDataLoad();
			m_Dungeon1Data = true;

		}else if (false == m_TownData) {
			CResourceMgr::GetInstance()->TownDataLoad();
			m_TownData = true;
			m_LoadingDone = true;
		}
		break;
	case 2: //던전2 리소스 로드 -> 지금은 플레이어 정보까지 넣어뒀으니 나중에 꼭 지울것!
		if (false == m_Dungeon2Data) {
			CResourceMgr::GetInstance()->Dungeon2DataLoad();
			m_Dungeon2Data = true;
			//m_LoadingDone = true;
		}
		else if (false == m_PlayerData) {
			CResourceMgr::GetInstance()->PlayerDataLoad();
			m_PlayerData = true;
		}
		else if (false == m_UIData) {
			CResourceMgr::GetInstance()->UIDataLoad();
			m_UIData = true;
			m_LoadingDone = true;
		}

		break;
	case 3: // 에디터 

		if (false == m_PlayerData) {
			CResourceMgr::GetInstance()->PlayerDataLoad();
			m_PlayerData = true;
		}
		else if (false == m_Dungeon1Data) {
			CResourceMgr::GetInstance()->Dungeon1DataLoad();
			m_Dungeon1Data = true;
		}
		else if (false == m_UIData) {
			CResourceMgr::GetInstance()->UIDataLoad();
			m_UIData = true;
		}
		else if (false == m_TownData) {
			CResourceMgr::GetInstance()->TownDataLoad();
			m_TownData = true;
		}
		else if (false == m_Dungeon2Data) {
			CResourceMgr::GetInstance()->Dungeon2DataLoad();
			m_Dungeon2Data = true;
			m_LoadingDone = true;
		}

		break;
	default:
		m_LoadingDone = true;
		break;
	}
}

void CLoading::Render(HDC _hDC)
{
	CMyResource* backImg = CResourceMgr::GetInstance()->FindRes("BACKGROUND_LOADING");
	AnimInfo tInfo = backImg->GetResInfo();
	BitBlt(_hDC,
		0,
		0,
		tInfo.iSizeX,
		tInfo.iSizeY,
		backImg->GetMemDC(),
		0,
		0,
		SRCCOPY);

	//BACKGROUND_LOADING


}

void CLoading::Release()
{
}

void CLoading::LateUpdate()
{
	if (true == m_LoadingDone) {
		if (0 == m_iCurrentFlag) {
			CSceneMgr::GetInstance()->ChangeScene(ESceneType::GOLEM_DUNGEON);
		}
		else if (1 == m_iCurrentFlag) {
			CSceneMgr::GetInstance()->ChangeScene(ESceneType::VILLAGE);
		}
		else if (2 == m_iCurrentFlag) {
			CSceneMgr::GetInstance()->ChangeScene(ESceneType::FOREST_DUNGEON);
		}
		else if (3 == m_iCurrentFlag) {
			CSceneMgr::GetInstance()->ChangeScene(ESceneType::EDITOR);
		}
		else if (4 == m_iCurrentFlag) {
			CSceneMgr::GetInstance()->ChangeScene(ESceneType::HOME);

		}

	}

}
