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

	float m_fDS;			// delta secound : 1 �����ӿ� �ɸ� �ð�
	float m_fAddTime;		// 1�� ã��
	float m_fCurTime;		// ��� �ð� (�ʴ���) 

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

