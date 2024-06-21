#pragma once

#include"Scenes.h"
#include"Component.h"


class CMainMenu : public CScenes
{
public:
	CMainMenu();
	~CMainMenu();

	void Initialize() override;
	void Update() override;
	void Render(HDC _hDC) override;
	void Release() override;

	void SwitchingCursor();
	void InputKey();

private:
	int m_iCurrentCursor = 1;
	CComponent* m_mainComp;

};

