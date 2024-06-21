#include "MyResource.h"

CMyResource::CMyResource()
{
	ZeroMemory(&m_tResInfo, sizeof(AnimInfo));
}

CMyResource::~CMyResource()
{
	Release();
}

void CMyResource::Initialize(int _sizeX, int _sizeY , int _startFrame , int _endFrame , DWORD _speed)
{
	m_tResInfo.iSizeX = _sizeX;
	m_tResInfo.iSizeY = _sizeY;
	m_tResInfo.iFrameEnd = _endFrame;
	m_tResInfo.iFrameStart = _startFrame;
	m_tResInfo.Framespeed = _speed;
}

void CMyResource::LoadResource(const TCHAR* pFilePath, HWND _hwnd)
{
	HDC			hDC = GetDC(_hwnd);

	m_hMemDC = CreateCompatibleDC(hDC);

	ReleaseDC(_hwnd, hDC);

	m_hBitmap = (HBITMAP)LoadImage(NULL,
								pFilePath,		
								IMAGE_BITMAP,	
								0,				
								0,
								LR_LOADFROMFILE | LR_CREATEDIBSECTION); 

	m_hOldBmp = (HBITMAP)SelectObject(m_hMemDC, m_hBitmap);
}

void CMyResource::Release()
{
	SelectObject(m_hMemDC, m_hOldBmp);
	DeleteObject(m_hBitmap);
	DeleteDC(m_hMemDC);

}
