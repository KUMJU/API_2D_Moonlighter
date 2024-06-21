#pragma once
#include"pch.h"
#include"MyResource.h"

class CResourceMgr
{
private:
	CResourceMgr();
	~CResourceMgr();

public:

	static CResourceMgr* GetInstance() {
		if (!m_pInstance)
			m_pInstance = new CResourceMgr;

		return m_pInstance;
	}

	static void DestroyInstance() {

		if (m_pInstance) {
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}

public:

	void Initialize(HWND _hwnd);
	CMyResource* FindRes(string _findKey);
	void CreateResource(string _keyName, int _sizeX, int sizeY, const TCHAR* _path , int _startFrame, int _EndFrame, DWORD _speed);
	void Release();
	void PlayerDataLoad();
	void UIDataLoad();
	void Dungeon1DataLoad();
	void Dungeon2DataLoad();
	void TownDataLoad();
	void HomeDataLoad();

	void ReleasePrevData();
	bool IsDungeonResEmpty() { return m_DungeonKey.empty(); }
	int GetCurrentFlag() {return m_iCurrentFlag;}
	void SetCurrentFlag(int _num) { m_iCurrentFlag = _num; }
private:
	static CResourceMgr* m_pInstance;
	map<string, CMyResource*>	m_resList;

	HWND m_hWnd{};
	list<string> m_DungeonKey;

	bool m_IsDungeonRes = false;
	int m_iCurrentFlag = 0;

};

