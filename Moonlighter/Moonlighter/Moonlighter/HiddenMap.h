#pragma once
#include"DungeonRoom.h"

class CObj;

class CHiddenMap : public CDungeonRoom
{
public:
	CHiddenMap();
	CHiddenMap(const TCHAR* _path);
	~CHiddenMap();

	void Initialize();
	void Update();
	void Render(HDC _hDC);
	void LateUpdate();
	void Release();

public:

	void CreateMon();
	void SetDungeonNum(int _num) { m_iDungeonNum = _num; }
	void CreateSpcObj();

private:
	CObj* m_hiddenCenterPos;
	int m_iPrevRoom = 1;
	int m_iDungeonNum = 0;

	string m_strBackImg = "";
};

