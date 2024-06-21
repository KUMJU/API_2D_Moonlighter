#include "MainGame.h"
#include"ResourceMgr.h"
#include"SceneMgr.h"
#include"KeyMgr.h"
#include"CollisionMgr.h"
#include"UIMgr.h"
#include"GameMgr.h"
#include"Camera.h"
#include"TimeMgr.h"
#include"SoundMgr.h"

CMainGame::CMainGame()
{
}

CMainGame::~CMainGame()
{
	Release();
}

void CMainGame::Initialize(HWND _hwnd)
{
	m_hWnd = _hwnd;
	m_hDC = GetDC(_hwnd);
	::GetClientRect(_hwnd, &m_rect);

	CTimeMgr::GetInstance()->Init();
	CResourceMgr::GetInstance()->Initialize(_hwnd);
	m_hDCBack = ::CreateCompatibleDC(m_hDC);
	m_bmpBack = ::CreateCompatibleBitmap(m_hDC, m_rect.right, m_rect.bottom);
	HBITMAP prevBmp = (HBITMAP)::SelectObject(m_hDCBack, m_bmpBack);
	::DeleteObject(prevBmp);

	CUIMgr::GetInstance()->Initialize();
	CSoundMgr::Get_Instance()->Initialize();
	CSceneMgr::GetInstance()->ChangeScene(ESceneType::MAINMENU);
	CSceneMgr::GetInstance()->GetHandler(_hwnd);
}

void CMainGame::Update()
{
	CSceneMgr::GetInstance()->GetCurrentScene()->Update();
	CTimeMgr::GetInstance()->Update();

}

void CMainGame::Render()
{

	++m_iFPS;

	if (m_dwTime + 1000 < GetTickCount64())
	{
		swprintf_s(m_szFPS, L"FPS : %d", m_iFPS);
		m_iFPS = 0;
		m_dwTime = (DWORD)GetTickCount64();

		// SetWindowText : 윈도우 타이틀에 출력하는 함수
		SetWindowText(m_hWnd, m_szFPS);
	}

	CSceneMgr::GetInstance()->GetCurrentScene()->Render(m_hDCBack);
	::BitBlt(m_hDC, 0, 0, m_rect.right, m_rect.bottom, m_hDCBack, 0, 0, SRCCOPY);
	::PatBlt(m_hDCBack, 0, 0, m_rect.right, m_rect.bottom, WHITENESS);
}

void CMainGame::LateUpdate()
{
	CSceneMgr::GetInstance()->GetCurrentScene()->LateUpdate();

}

void CMainGame::Release()
{
	CKeyMgr::GetInstance()->DestroyInstance();
	CResourceMgr::GetInstance()->DestroyInstance();
	CCollisionMgr::GetInstance()->DestroyInstance();
	CUIMgr::GetInstance()->DestroyInstance();
	CSoundMgr::Get_Instance()->Destroy_Instance();
	CTimeMgr::GetInstance()->DestroyInstance();
	CCamera::GetInstance()->DestroyInstance();
	CGameMgr::GetInstance()->DestroyInstance();
	CSceneMgr::GetInstance()->DestroyInstance();
	ReleaseDC(m_hWnd, m_hDC);
	
}
