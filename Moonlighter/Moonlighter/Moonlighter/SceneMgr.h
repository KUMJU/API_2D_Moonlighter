#pragma once
#include"Enums.h"
#include"Define.h"
#include"Scenes.h"
#include"Obj.h"


class CSceneMgr
{
private:
	CSceneMgr();
	~CSceneMgr();

public:

	static CSceneMgr* GetInstance() {
		if (!m_pInstance)
			m_pInstance = new CSceneMgr;

		return m_pInstance;
	}

	static void DestroyInstance() {
		if (m_pInstance) {
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}

public:
	CScenes* GetCurrentScene() { return m_currentScene; }
	ESceneType GetCurrentSceneType() { return m_eCurSceneType; }

	void ChangeScene(ESceneType _changeScene);
	void DeleteScene(CScenes* _scene){ SAFE_DELETE<CScenes*>(m_currentScene); }
	
	void Release();
	void GetHandler(HWND _mainHandle) { m_halnlder = _mainHandle; };

private:
	static CSceneMgr* m_pInstance;
	CScenes* m_currentScene;
	ESceneType m_eCurSceneType = ESceneType::ENUM_END;
	HWND m_halnlder{};
};