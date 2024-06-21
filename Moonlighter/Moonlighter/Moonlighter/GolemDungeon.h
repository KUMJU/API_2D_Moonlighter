#pragma once
#include"Scenes.h"
#include"DungeonRoom.h"

class CGolemDungeon : public CScenes
{
public:
	CGolemDungeon();
	~CGolemDungeon();

	void Initialize() override;
	void Update() override;
	void Render(HDC _hDC) override;
	void LateUpdate() override;
	void Release() override;

private:
	vector<CDungeonRoom*> m_RoomList;
	vector<CObj*> m_CenterPosList;
	int m_iMaxRoomNum = 5;
	int m_iCurrentRoomNum = 0;
};

