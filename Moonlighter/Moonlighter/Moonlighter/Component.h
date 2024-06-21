#pragma once
#include"ResourceMgr.h"
#include"Types.h"

class CComponent
{
public:
	CComponent();
	~CComponent();

	bool PlayAnim(string _keyName, HDC _hDC, Vector _position);
	bool PlayAnimGetRow(string _keyName, HDC _hDC, Vector _position, int _row);
	bool PlayAnimIndependent(string _keyName, HDC _hDC, Vector _position);
	bool PlayAnimIndependentRow(string _keyName, HDC _hDC, Vector _position, int _row);

	void RenderFixedImage(string _keyName, HDC _hDC, Vector _position);
	void RenderImage(string _keyName, HDC _hDC, Vector _position);
	void RenderImageGetRow(string _keyName, HDC _hDC, Vector _position, int _row);
	bool MoveFrame(AnimInfo _info);
	bool MoveFrameIndependent(AnimInfo _info, CMyResource* _myRes, string _keyName);
	bool RenderFixedAnim(string _keyName, HDC _hDC, Vector _position, int _row);

private:

	DWORD m_dwTime = (DWORD)GetTickCount64();
	string m_strPrevKey= "";

	unordered_map<string, DWORD> m_dwTimeList;

	int	m_iCurFrame= 0;
	bool m_bIsAnimFinish = false;

	bool m_currentHit = true;
	

};

