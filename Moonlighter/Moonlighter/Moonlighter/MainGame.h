#pragma once
#include"pch.h"
#include"Obj.h"
#include"Player.h"

class CMainGame
{
public:
	CMainGame();
	~CMainGame();

	void Initialize(HWND _hwnd);
	void Update();
	void Render();
	void LateUpdate();
	void Release();

private:

	HWND m_hWnd{};
	HDC		m_hDC{};
	RECT	m_rect{};
	HDC m_hDCBack = {};
	HBITMAP m_bmpBack = {};


	DWORD		m_dwTime = 0;
	int			m_iFPS = 0;
	TCHAR		m_szFPS[16] =L"";
};