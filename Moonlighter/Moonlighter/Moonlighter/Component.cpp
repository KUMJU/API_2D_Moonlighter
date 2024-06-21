#include "Component.h"
#include"Camera.h"

CComponent::CComponent()
{
}

CComponent::~CComponent()
{
}

bool CComponent::PlayAnim(string _keyName , HDC _hDC, Vector _position)
{

	Vector tempVec = CCamera::GetInstance()->GetRenderPos({0.f,0.f});
	_position = CCamera::GetInstance()->GetRenderPos(_position);
	CMyResource* CurRes = CResourceMgr::GetInstance()->FindRes(_keyName);

	COLORREF myRGB = RGB(0, 0, 0);

	int ySize = 0;


	if (CurRes) {
		if (_keyName != m_strPrevKey) {
			m_iCurFrame = 0;
		}

		if (string::npos != _keyName.find("BOSS1_DEAD")) {
			myRGB = RGB(32, 226, 218);
			
		}
		else if (string::npos != _keyName.find("BOSS1")) {
			myRGB = RGB(246, 0, 255);
		}
		else if (string::npos != _keyName.find("KIRBY") ||
			string::npos != _keyName.find("PROJ_BOMB")) {
			myRGB = RGB(136, 227, 148);
		}
		else if (string::npos != _keyName.find("HIDDEN") || string::npos != _keyName.find("PIANO")) {
			myRGB = RGB(70, 70, 70);
		}
		else if (string::npos != _keyName.find("SHIELD")) {
			myRGB = RGB(0, 128, 128);
		}

		AnimInfo tempInfo = CurRes->GetResInfo();

		GdiTransparentBlt(_hDC,
			(int)(_position.m_fX - (tempInfo.iSizeX * 0.5f)),
			(int)(_position.m_fY - (tempInfo.iSizeX * 0.5f)),
			tempInfo.iSizeX,
			tempInfo.iSizeY,
			CurRes->GetMemDC(),	
			m_iCurFrame * tempInfo.iSizeX,
			ySize * tempInfo.iSizeY,
			tempInfo.iSizeX,
			tempInfo.iSizeY,
			myRGB);
	
		m_strPrevKey = _keyName;
		m_bIsAnimFinish = MoveFrame(tempInfo);
	}

	return m_bIsAnimFinish;
}

bool CComponent::PlayAnimGetRow(string _keyName, HDC _hDC, Vector _position, int _row) {

	_position = CCamera::GetInstance()->GetRenderPos(_position);
	CMyResource* CurRes = CResourceMgr::GetInstance()->FindRes(_keyName);
	COLORREF myRGB = RGB(0, 0, 0);

	if (string::npos != _keyName.find("BOSS1")) {
		myRGB = RGB(246, 0, 255);
	}
	else if(string::npos != _keyName.find("TURRET") || string::npos != _keyName.find("BUD") 
		|| string::npos != _keyName.find("CUTTING")) {
		myRGB = RGB(70, 70, 70);
	}


	if (CurRes) {
		if (_keyName != m_strPrevKey) {
			m_iCurFrame = 0;
		}

		AnimInfo tempInfo = CurRes->GetResInfo();

		GdiTransparentBlt(_hDC,
			(int)(_position.m_fX - (tempInfo.iSizeX * 0.5f)),
			(int)(_position.m_fY - (tempInfo.iSizeX * 0.5f)),
			tempInfo.iSizeX,
			tempInfo.iSizeY,
			CurRes->GetMemDC(),
			m_iCurFrame * tempInfo.iSizeX,
			_row * tempInfo.iSizeY,
			tempInfo.iSizeX,
			tempInfo.iSizeY,
			myRGB);

		m_strPrevKey = _keyName;
		m_bIsAnimFinish = MoveFrame(tempInfo);
	}

	return m_bIsAnimFinish;
}


bool CComponent::PlayAnimIndependent(string _keyName, HDC _hDC, Vector _position)
{
	_position = CCamera::GetInstance()->GetRenderPos(_position);
	CMyResource* CurRes = CResourceMgr::GetInstance()->FindRes(_keyName);

	if (CurRes) {
		AnimInfo tempInfo = CurRes->GetResInfo();

		GdiTransparentBlt(_hDC,
			(int)(_position.m_fX),
			(int)(_position.m_fY),
			tempInfo.iSizeX,
			tempInfo.iSizeY,
			CurRes->GetMemDC(),
			tempInfo.iFrameStart * tempInfo.iSizeX,
			0,
			tempInfo.iSizeX,
			tempInfo.iSizeY,
			RGB(0, 0, 0));


		if ((m_dwTimeList.find(_keyName)) == m_dwTimeList.end()) {
			m_dwTimeList.insert({ _keyName , (DWORD)GetTickCount64() });
		}

		m_bIsAnimFinish = MoveFrameIndependent(tempInfo, CurRes, _keyName);
		
	}

	return m_bIsAnimFinish;
}

bool CComponent::PlayAnimIndependentRow(string _keyName, HDC _hDC, Vector _position, int _row)
{

	_position = CCamera::GetInstance()->GetRenderPos(_position);
	CMyResource* CurRes = CResourceMgr::GetInstance()->FindRes(_keyName);
	COLORREF myRGB = RGB(0, 0, 0);

	if (CurRes) {
		AnimInfo tempInfo = CurRes->GetResInfo();

		if (string::npos != _keyName.find("BOSS1")) {
			myRGB = RGB(246, 0, 255);
		}
		else if (string::npos != _keyName.find("TURRET") || string::npos != _keyName.find("BUD")) {
			myRGB = RGB(70, 70, 70);
		}


		GdiTransparentBlt(_hDC,
			(int)(_position.m_fX - (tempInfo.iSizeX * 0.5f)),
			(int)(_position.m_fY - (tempInfo.iSizeX * 0.5f)),
			tempInfo.iSizeX,
			tempInfo.iSizeY,
			CurRes->GetMemDC(),
			tempInfo.iFrameStart * tempInfo.iSizeX,
			_row * tempInfo.iSizeY,
			tempInfo.iSizeX,
			tempInfo.iSizeY,
			myRGB);


		if ((m_dwTimeList.find(_keyName)) == m_dwTimeList.end()) {
			m_dwTimeList.insert({ _keyName , (DWORD)GetTickCount64() });
		}

		m_bIsAnimFinish = MoveFrameIndependent(tempInfo, CurRes, _keyName);

	}

	return m_bIsAnimFinish;
}

//UI처럼 완전 고정좌표인거
void CComponent::RenderFixedImage(string _keyName, HDC _hDC, Vector _position)
{
	CMyResource* CurRes = CResourceMgr::GetInstance()->FindRes(_keyName);
	COLORREF myRGB = RGB(0, 0, 0);

	if (string::npos != _keyName.find("SHADOW")) {
		myRGB = RGB(52, 52, 52);
	}

	if (CurRes) {
		AnimInfo tempInfo = CurRes->GetResInfo();

		GdiTransparentBlt(_hDC,
			static_cast<int>((_position.m_fX)- (tempInfo.iSizeX * 0.5f)),
			static_cast<int>((_position.m_fY)- (tempInfo.iSizeY * 0.5f)),
			tempInfo.iSizeX,
			tempInfo.iSizeY,
			CurRes->GetMemDC(),
			tempInfo.iFrameStart * tempInfo.iSizeX,
			0,
			tempInfo.iSizeX,
			tempInfo.iSizeY,
			myRGB);
	}
}

void CComponent::RenderImage(string _keyName, HDC _hDC, Vector _position)
{
	_position = CCamera::GetInstance()->GetRenderPos(_position);
	CMyResource* CurRes = CResourceMgr::GetInstance()->FindRes(_keyName);
	COLORREF myRGB = RGB(0, 0, 0);

	if (string::npos != _keyName.find("SHADOW")) {
		myRGB = RGB(52, 52, 52);
	}
	else if (string::npos != _keyName.find("TURRET") || string::npos != _keyName.find("BUD")
		|| string::npos != _keyName.find("CUTTING") || string::npos != _keyName.find("HOME")) {
		myRGB = RGB(70, 70, 70);
	}

	if (CurRes) {
		AnimInfo tempInfo = CurRes->GetResInfo();

		GdiTransparentBlt(_hDC,
			static_cast<int>((_position.m_fX) - (tempInfo.iSizeX * 0.5f)),
			static_cast<int>((_position.m_fY) - (tempInfo.iSizeY * 0.5f)),
			tempInfo.iSizeX,
			tempInfo.iSizeY,
			CurRes->GetMemDC(),
			tempInfo.iFrameStart * tempInfo.iSizeX,
			0,
			tempInfo.iSizeX,
			tempInfo.iSizeY,
			myRGB);
	}

}

void CComponent::RenderImageGetRow(string _keyName, HDC _hDC, Vector _position, int _row)
{
	_position = CCamera::GetInstance()->GetRenderPos(_position);
	CMyResource* CurRes = CResourceMgr::GetInstance()->FindRes(_keyName);
	COLORREF myRGB = RGB(0, 0, 0);

	if (string::npos != _keyName.find("SHADOW")) {
		myRGB = RGB(52, 52, 52);
	}
	else if (string::npos != _keyName.find("TURRET") || string::npos != _keyName.find("BUD")
		|| string::npos != _keyName.find("CUTTING")) {
		myRGB = RGB(70, 70, 70);
	}

	if (CurRes) {
		AnimInfo tempInfo = CurRes->GetResInfo();

		GdiTransparentBlt(_hDC,
			static_cast<int>((_position.m_fX) - (tempInfo.iSizeX * 0.5f)),
			static_cast<int>((_position.m_fY) - (tempInfo.iSizeY * 0.5f)),
			tempInfo.iSizeX,
			tempInfo.iSizeY,
			CurRes->GetMemDC(),
			tempInfo.iFrameStart * tempInfo.iSizeX,
			_row* tempInfo.iSizeY,
			tempInfo.iSizeX,
			tempInfo.iSizeY,
			myRGB);
	}

}



bool CComponent::MoveFrame(AnimInfo _info)
{
	if (_info.Framespeed + m_dwTime < GetTickCount64())
	{
		++m_iCurFrame;

		m_dwTime = (DWORD)GetTickCount64();

		if (m_iCurFrame > _info.iFrameEnd) {
			m_iCurFrame = 0;
			return true;
		}
	}
	return false;
 }

bool CComponent::MoveFrameIndependent(AnimInfo _info, CMyResource* _myRes,string _keyName)
{
	if (_info.Framespeed + m_dwTimeList[_keyName] < GetTickCount64())
	{
		_myRes->SetStartFrame(++_info.iFrameStart);

		m_dwTimeList[_keyName] = (DWORD)GetTickCount64();

		if (_myRes->GetResInfo().iFrameStart > _info.iFrameEnd) {
			_myRes->SetStartFrame(0);
			return true;
		}
	}
	return false;
}

bool CComponent::RenderFixedAnim(string _keyName, HDC _hDC, Vector _position, int _row)
{
	CMyResource* CurRes = CResourceMgr::GetInstance()->FindRes(_keyName);
	COLORREF myRGB = RGB(0, 0, 0);

	if (CurRes) {
		if (_keyName != m_strPrevKey) {
			m_iCurFrame = 0;
		}

		AnimInfo tempInfo = CurRes->GetResInfo();

		GdiTransparentBlt(_hDC,
			static_cast<int>((_position.m_fX) - (tempInfo.iSizeX * 0.5f)),
			static_cast<int>((_position.m_fY) - (tempInfo.iSizeY * 0.5f)),
			tempInfo.iSizeX,
			tempInfo.iSizeY,
			CurRes->GetMemDC(),
			m_iCurFrame * tempInfo.iSizeX,
			_row * tempInfo.iSizeY,
			tempInfo.iSizeX,
			tempInfo.iSizeY,
			myRGB);

		m_strPrevKey = _keyName;
		m_bIsAnimFinish = MoveFrame(tempInfo);
	}

	return m_bIsAnimFinish;
}

