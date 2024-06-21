#pragma once
#include"Scenes.h"

class CLoading : public CScenes
{
public:
	CLoading();
	~CLoading();

	void Initialize() override;
	void Update() override;
	void Render(HDC _hDC) override;
	void Release() override;
	void LateUpdate() override;

private:
	bool m_PlayerData = false;
	bool m_Dungeon1Data = false;
	bool m_UIData = false;


	bool m_TownData = false;
	bool m_Dungeon2Data = false;

	bool m_LoadingDone = false;
	int m_iCurrentFlag = 0;
};

