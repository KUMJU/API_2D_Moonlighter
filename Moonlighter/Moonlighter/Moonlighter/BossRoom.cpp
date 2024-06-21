#include "BossRoom.h"
#include"Tile.h"
#include"GolemKing.h"
#include"Camera.h"
#include"SceneMgr.h"
#include"GiantBud.h"
#include"SoundMgr.h"

CBossRoom::CBossRoom()
{
}

CBossRoom::~CBossRoom()
{
	Release();
}

void CBossRoom::Initialize()
{
	CreateRoomCollision();
}

void CBossRoom::Update()
{
}

void CBossRoom::Render(HDC _hDC)
{
	AnimInfo tempInfo = CResourceMgr::GetInstance()->FindRes(m_strBackGroundKey)->GetResInfo();
	Vector RenderVec = CCamera::GetInstance()->GetRenderPos({0.f,0.f});

	GdiTransparentBlt(_hDC,
		RenderVec.m_fX,
		RenderVec.m_fY,
		tempInfo.iSizeX,
		tempInfo.iSizeY,
		CResourceMgr::GetInstance()->FindRes(m_strBackGroundKey)->GetMemDC(),
		0,
		0,
		tempInfo.iSizeX,
		tempInfo.iSizeY,
		RGB(1, 0, 0));


}

void CBossRoom::LateUpdate()
{
	//보스를 다 잡으면 집으로 간다 
	
	if (m_ObjectList[(unsigned int)EObjectType::MONSTER].empty()) {
		CResourceMgr::GetInstance()->SetCurrentFlag(1);
		CSceneMgr::GetInstance()->ChangeScene(ESceneType::LOADING);
	}

}

void CBossRoom::Release()
{
}

void CBossRoom::CreateRoomCollision()
{

	if ("BackGround_Boss1" == m_strBackGroundKey) {
		m_ObjectList[(unsigned int)EObjectType::PLAYER].front()->SetPosition({ 2300 * 0.5f , 1300.f });

		//벽 충돌처리
		CObj* newTile1 = new CTile(ETileType::WALL, 45, 1550 * 0.5f, 90.f, 1550.f);
		m_ObjectList[(unsigned int)EObjectType::OBSTACLE].push_back(newTile1);
		CObj* newTile2 = new CTile(ETileType::WALL, 2300 * 0.5f, 45.f, 2300.f, 90.f);
		m_ObjectList[(unsigned int)EObjectType::OBSTACLE].push_back(newTile2);

		CObj* newTile3 = new CTile(ETileType::WALL, 2300 - 45, 1550.f * 0.5f, 90.f, 1550.f);
		m_ObjectList[(unsigned int)EObjectType::OBSTACLE].push_back(newTile3);
		CObj* newTile4 = new CTile(ETileType::WALL, 2300 * 0.5f, 1550.f - 45.f, 2300.f, 90.f);
		m_ObjectList[(unsigned int)EObjectType::OBSTACLE].push_back(newTile4);
		CObj* newTile5 = new CTile(ETileType::WALL, 2300 * 0.5f, 370.f, 1766.f, 95.f);
		m_ObjectList[(unsigned int)EObjectType::OBSTACLE].push_back(newTile5);

		//보스몬스터 스폰
		CObj* BossMon = new CGolemKing();
		BossMon->SetPosition({ 2300 * 0.5f ,1550 * 0.5f - 250.f });
		BossMon->Initialize();
		m_ObjectList[(unsigned int)EObjectType::MONSTER].push_back(BossMon);
		dynamic_cast<CGolemKing*>(BossMon)->SetObjList(m_ObjectList);

		CSoundMgr::Get_Instance()->StopSound(SOUND_BGM);
		CSoundMgr::Get_Instance()->PlayBGM(L"golem_boss_track.wav", 1.f);

		CCamera::GetInstance()->SetTarget(BossMon);
		CCamera::GetInstance()->SetCameraMode(1);
		CCamera::GetInstance()->SetCurrentMapSize({ 0,0,2300 ,1440 });

	}
	else if ("BackGround_Boss2" == m_strBackGroundKey) {
		m_ObjectList[(unsigned int)EObjectType::PLAYER].front()->SetPosition({ 2300 * 0.5f , 1300.f });

		CObj* newTile1 = new CTile(ETileType::WALL, 45, 1550 * 0.5f, 90.f, 1550.f);
		m_ObjectList[(unsigned int)EObjectType::OBSTACLE].push_back(newTile1);
		CObj* newTile2 = new CTile(ETileType::WALL, 2300 * 0.5f, 45.f, 2300.f, 90.f);
		m_ObjectList[(unsigned int)EObjectType::OBSTACLE].push_back(newTile2);

		CObj* newTile3 = new CTile(ETileType::WALL, 2300 - 45, 1550.f * 0.5f, 90.f, 1550.f);
		m_ObjectList[(unsigned int)EObjectType::OBSTACLE].push_back(newTile3);
		CObj* newTile4 = new CTile(ETileType::WALL, 2300 * 0.5f, 1550.f - 45.f, 2300.f, 90.f);
		m_ObjectList[(unsigned int)EObjectType::OBSTACLE].push_back(newTile4);

		CObj* BossMon = new CGiantBud();
		BossMon->SetPosition({ 2300 * 0.5f ,1550 * 0.5f - 250.f });
		BossMon->Initialize();
		m_ObjectList[(unsigned int)EObjectType::MONSTER].push_back(BossMon);
		static_cast<CGiantBud*>(BossMon)->SetObjList(m_ObjectList);

		CSoundMgr::Get_Instance()->StopSound(SOUND_BGM);
		CSoundMgr::Get_Instance()->PlayBGM(L"forest_boss_track.wav", 1.f);

		CCamera::GetInstance()->SetTarget(BossMon);
		CCamera::GetInstance()->SetCameraMode(1);
		CCamera::GetInstance()->SetCurrentMapSize({ 0,0,2300 ,1440 });

	}

}
