#pragma once
#include"Define.h"

class CScrollMgr
{
private:
	CScrollMgr();
	~CScrollMgr();

public:
	static CScrollMgr* GetInstance()
	{
		if (nullptr == _instance)
		{
			_instance = new CScrollMgr();
		}

		return _instance;
	}

	static void DestroyInstance()
	{
		if (_instance)
		{
			delete _instance;
			_instance = nullptr;
		}
	}

public:
	void SetScrollX(float _speed)
	{
		m_fScrollX -= static_cast<int>(_speed);
	}

	void SetScrollY(float _speed)
	{
		m_fScrollY -= static_cast<int>(_speed);

	}

	void Reset()
	{
		m_fScrollX = 0;
		m_fScrollY = 0;
	}

	int GetScrollX() { return m_fScrollX; }
	int GetScrollY() { return m_fScrollY; }
	void CalcPosition(float _fPlrX, float _fPlrY);

	void ScrollOn() { m_ScrollOn = true; }
	void ScrollOff() { m_ScrollOn = false; }
	bool GetScrollMod() { return m_ScrollOn; }
	

	void GetCurrentMapSize(int _iX, int _iY) {
		m_CurrentMapSizeX = _iX;
		m_CurrentMapSizeY = _iY;
	}

private:
	static CScrollMgr* _instance;

	bool m_ScrollOn = false;

	int m_fScrollX = 0;
	int m_fScrollY = 0;

	float m_fPrevX = 0.f;
	float m_fPrevY = 0.f;

	int m_CurrentMapSizeX = 0;
	int m_CurrentMapSizeY = 0;
};