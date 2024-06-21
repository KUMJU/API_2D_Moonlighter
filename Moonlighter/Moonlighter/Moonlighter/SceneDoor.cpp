#include "SceneDoor.h"
#include"SceneMgr.h"
#include"ResourceMgr.h"

CSceneDoor::CSceneDoor()
{
}

CSceneDoor::~CSceneDoor()
{
}

void CSceneDoor::Initialize()
{
	CDoor::Initialize();
	m_tSize = { 30.f,30.f };
}

void CSceneDoor::Update()
{
}

void CSceneDoor::Render(HDC _hDC)
{
	CDoor::Render(_hDC);
}

void CSceneDoor::LateUpdate()
{
}

void CSceneDoor::Release()
{
}

void CSceneDoor::OnCollide(CObj* _pObj)
{

	if (ESceneType::FOREST_DUNGEON == m_eNextScene) {
		CResourceMgr::GetInstance()->SetCurrentFlag(2);
	}
	else if (ESceneType::HOME == m_eNextScene) {
		CResourceMgr::GetInstance()->SetCurrentFlag(4);
	}
	else if (ESceneType::VILLAGE == m_eNextScene) {
		CResourceMgr::GetInstance()->SetCurrentFlag(1);
	}

	CSceneMgr::GetInstance()->ChangeScene(ESceneType::LOADING);

}

void CSceneDoor::SetNextScene(ESceneType _scene)
{
	m_eNextScene = _scene;
}
