#include "SceneMgr.h"
#include"GolemDungeon.h"
#include"MainMenu.h"
#include"TileEditor.h"
#include"Loading.h"
#include"Town.h"
#include"ForestDungeon.h"
#include"Home.h"

CSceneMgr* CSceneMgr::m_pInstance = nullptr;


CSceneMgr::CSceneMgr() : m_currentScene(nullptr)
{
}

CSceneMgr::~CSceneMgr()
{
	Release();
}

void CSceneMgr::ChangeScene(ESceneType _changeScene)
{
	if (m_currentScene) {
		DeleteScene(m_currentScene);
	}

	switch (_changeScene)
	{
	case ESceneType::MAINMENU:
		m_currentScene = new CMainMenu;
		m_currentScene->Initialize();
		break;
	case ESceneType::GOLEM_DUNGEON:
		m_currentScene = new CGolemDungeon;
		m_currentScene->Initialize();
		break;
	case ESceneType::FOREST_DUNGEON:
		m_currentScene = new CForestDungeon;
		m_currentScene->Initialize();
		break;
	case ESceneType::VILLAGE:
		m_currentScene = new CTown;
		m_currentScene->Initialize();
		break;
	case ESceneType::HOME:
		m_currentScene = new CHome;
		m_currentScene->Initialize();
		break;

	case ESceneType::EDITOR:
		m_currentScene = new CTileEditor;
		m_currentScene->Initialize();
		dynamic_cast<CTileEditor*>(m_currentScene)->SetHandler(m_halnlder);
		break;

	case ESceneType::LOADING:
		m_currentScene = new CLoading;
		m_currentScene->Initialize();
		break;
	case ESceneType::ENUM_END:

		break;
	default:
		if (!m_currentScene) {
			m_currentScene = new CMainMenu;
			m_currentScene->Initialize();
		}


		break;
	}


}

void CSceneMgr::Release()
{
	DeleteScene(m_currentScene);
}
