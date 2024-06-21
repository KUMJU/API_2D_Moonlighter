#pragma once
#include"pch.h"
#include"Obj.h"
#include"Camera.h"

class CDungeonRoom
{

public:
	CDungeonRoom();
	CDungeonRoom(const TCHAR* _path);

	virtual ~CDungeonRoom();

	virtual void Initialize();
	virtual void Update();
	virtual void Render(HDC _hDC);
	virtual void LateUpdate();
	virtual void Release();

public:
	void SetObjList(list<CObj*>* _copyList) { m_ObjectList = _copyList; }
	void SetBackGroundKey(string _strKey) { m_strBackGroundKey = _strKey; }
	void LoadTile(const TCHAR* _path);
	bool GetIsRoomClear() { return m_RoomClear; }
	void SetCenterPos(CObj* myCenter) { m_CenterPos = myCenter; }
	void SetRoomNumber(int _num) { m_iRoomNum = _num; }
	int GetRoomNumber() {return m_iRoomNum;}

	bool GetInItDone() { return m_IsInitDone; }

	void InsertDoorList(CObj* _obj) { m_doorList.push_back(_obj); }
	virtual void SettingCamera();

protected:
	CObj* m_CenterPos;
	Vector m_tPosition;
	bool m_RoomClear = false;
	const TCHAR* m_path;
	list<CObj*>* m_ObjectList;
	string m_strBackGroundKey;
	int m_iRoomNum = 0;
	bool m_IsInitDone = false;

	list<CObj*> m_doorList;

};

