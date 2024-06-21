#include"pch.h"
#include "MainMenu.h"
#include"KeyMgr.h"
#include"SceneMgr.h"
#include"SoundMgr.h"


CMainMenu::CMainMenu() : m_mainComp(nullptr)
{
}

CMainMenu::~CMainMenu()
{
	Release();
}

void CMainMenu::Initialize()
{
	m_mainComp = new CComponent;
	CSoundMgr::Get_Instance()->PlayBGM(L"main_menu_screen.wav", 1.f);

}

void CMainMenu::Update()
{
	InputKey();
}

void CMainMenu::Render(HDC _hDC)
{
	m_mainComp->PlayAnimIndependent("MAIN_BACKGROUND", _hDC, { 0 , 0 });
	m_mainComp->PlayAnimIndependent("MAIN_BACKLAYER", _hDC , { 0 , 0 });
	m_mainComp->RenderFixedImage("MAIN_LOGO", _hDC , { WINCX*0.5f ,WINCY*0.5f - 140.f });
	m_mainComp->RenderFixedImage("MAIN_START_FONT", _hDC , { WINCX*0.5f ,	WINCY*0.5f+150.f });

	if (1 == m_iCurrentCursor) {
		m_mainComp->RenderFixedImage("MAIN_ARROW", _hDC, { WINCX * 0.5f + 150.f ,	WINCY * 0.5f + 110.f });
	}
	else {
		m_mainComp->RenderFixedImage("MAIN_ARROW", _hDC, { WINCX * 0.5f + 150.f ,	WINCY * 0.5f + 190.f });

	}

}

void CMainMenu::Release()
{
	CSoundMgr::Get_Instance()->StopSound(SOUND_BGM);
	SAFE_DELETE<CComponent*>(m_mainComp);
}

void CMainMenu::SwitchingCursor()
{
	if (1 == m_iCurrentCursor)
		m_iCurrentCursor = 2;
	else
		m_iCurrentCursor = 1;
}

void CMainMenu::InputKey()
{
	if(CKeyMgr::GetInstance()->Key_Down(VK_DOWN)) {
		SwitchingCursor();
	}

	if (CKeyMgr::GetInstance()->Key_Down(VK_UP)) {
		SwitchingCursor();
	}

	if (CKeyMgr::GetInstance()->Key_Down(VK_SPACE)) {
		if (1 == m_iCurrentCursor) {
			CResourceMgr::GetInstance()->SetCurrentFlag(0);
			CSceneMgr::GetInstance()->ChangeScene(ESceneType::LOADING);
		}
		else if (2 == m_iCurrentCursor) {

			CResourceMgr::GetInstance()->SetCurrentFlag(3);
			CSceneMgr::GetInstance()->ChangeScene(ESceneType::LOADING);
		}
	}
}
