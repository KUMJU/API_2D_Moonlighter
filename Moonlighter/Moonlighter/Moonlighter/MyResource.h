#pragma once
#include"pch.h"
#include"Define.h"

class CMyResource
{
public:
	CMyResource();
	virtual  ~CMyResource();

	void Initialize(int _sizeX, int _sizeY, int _startFrame, int _endFrame, DWORD _speed);
	void LoadResource(const TCHAR* pFilePath , HWND _hwnd);
	void Release();

	void SetStartFrame(int _frameNum) { m_tResInfo.iFrameStart = _frameNum; }

	AnimInfo GetResInfo() { return m_tResInfo; }
	HDC GetMemDC() { return m_hMemDC; }

private:


	AnimInfo m_tResInfo;

	HDC m_hMemDC{};
	HBITMAP m_hOldBmp{};
	HBITMAP m_hBitmap{};

};

