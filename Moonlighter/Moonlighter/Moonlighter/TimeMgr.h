#pragma once
#include"pch.h"

class CTimeMgr
{
private:
	CTimeMgr();
	~CTimeMgr();

public:
	static CTimeMgr* GetInstance() {
		if (!m_pInstance)
			m_pInstance = new CTimeMgr;

		return m_pInstance;
	}

	static void DestroyInstance() {
		if (m_pInstance) {
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}

private:
	LARGE_INTEGER m_liFreqency;
	LARGE_INTEGER m_liPrevCount;
	LARGE_INTEGER m_liCurCount;

	float m_fDS;			// delta secound : 1 프레임에 걸린 시간
	float m_fAddTime;		// 1초 찾기
	float m_fCurTime;		// 경과 시간 (초단위) 

	unsigned int m_iFPS;			// frame per second

public:
	void Init();
	void Update();

public:
	float GetDS() { return m_fDS; }
	float GetCurTime() { return m_fCurTime; }
	unsigned int GetFPS() { return m_iFPS; }

private:
	static CTimeMgr* m_pInstance;

};

