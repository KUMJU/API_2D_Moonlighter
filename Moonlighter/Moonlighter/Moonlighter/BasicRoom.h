#pragma once
#include"DungeonRoom.h"

class CBasicRoom : public CDungeonRoom
{
public:
	CBasicRoom();
	CBasicRoom(const TCHAR* _path);
	~CBasicRoom();

	void Initialize();
	void Update();
	void Render(HDC _hDC);
	void Release();
	void LateUpdate();

	void SettingCamera() override;

	void CreateMon();

	void InsertDoorList(CObj* _obj) { m_doorList.push_back(_obj); }
private:
};

