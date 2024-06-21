#pragma once
#include"Scenes.h"

class CDungeonRoom;

class CForestDungeon :public CScenes
{
public:
	CForestDungeon();
	~CForestDungeon();

	void Initialize() override;
	void Update() override;
	void Render(HDC _hDC) override;
	void LateUpdate() override;
	void Release() override;

private:
	vector<CDungeonRoom*> m_RoomList;
	int m_iMaxRoomNum = 6;
	int m_iCurrentRoomNum = 0;
};

