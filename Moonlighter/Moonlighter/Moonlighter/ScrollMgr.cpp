#include "pch.h"
#include "ScrollMgr.h"

CScrollMgr* CScrollMgr::_instance = nullptr;

CScrollMgr::CScrollMgr() : m_fScrollX(0.f), m_fPrevX(0.f)
{

}

CScrollMgr::~CScrollMgr()
{

}

void CScrollMgr::CalcPosition(float _fPlrX, float _fPlrY)
{
	float fTemp = WINCX * 0.5f - _fPlrX;
	SetScrollX(m_fPrevX - fTemp);
	m_fPrevX = fTemp;
	
	fTemp = WINCY * 0.5f - _fPlrY;
	SetScrollY(m_fPrevY - fTemp);
	m_fPrevY = fTemp;
}