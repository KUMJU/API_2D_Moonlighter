#pragma once
#include"Enums.h"

class CObj;

class CGameMgr
{
private:
	CGameMgr();
	~CGameMgr();

	void Release();

public:

	static CGameMgr* GetInstance() {
		if (!m_pInstance)
			m_pInstance = new CGameMgr;

		return m_pInstance;
	}

	static void DestroyInstance() {
		if (m_pInstance) {
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}

public:

	CObj* GetPlayer() { return m_Player; }
	void SetPlayer(CObj* _plr) { m_Player = _plr; }
	bool isPlayerExist() {
		if (m_Player) {
			return true;
		}
		return false;
	}
	void SetGameState(EGameState _state) { m_eGameState = _state; }
	EGameState GetGameState() { return m_eGameState; }


private:
	static CGameMgr* m_pInstance;
	
	CObj* m_Player;	
	EGameState m_eGameState = EGameState::DEFAULT;

};