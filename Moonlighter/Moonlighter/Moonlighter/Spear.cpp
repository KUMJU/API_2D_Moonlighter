#include "Spear.h"

CSpear::CSpear()
{

}

CSpear::~CSpear()
{
}

void CSpear::Initialize()
{
	dwTime = GetTickCount64();
	m_iDamage = 20;


	if (m_eDir == EDirection::UP) {
		m_tSize = { 95.f,55.f };
		m_tPosition.m_fY -= 60.f;

	}
	else if (m_eDir == EDirection::DOWN) {
		m_tSize = { 95.f,55.f };
		m_tPosition.m_fY += 60.f;

	}
	else if (m_eDir == EDirection::RIGHT) {
		m_tSize = { 55.f,95.f };
		m_tPosition.m_fX += 60.f;

	}
	else if (m_eDir == EDirection::LEFT) {
		m_tSize = { 55.f,95.f };
		m_tPosition.m_fX -= 60.f;
	}

	m_eProjType = EProjectileType::PLAYER;

}

void CSpear::Update()
{
}

void CSpear::Render(HDC _hDC)
{
}

void CSpear::LateUpdate()
{
	if (dwTime + 500 <= (DWORD)GetTickCount64()) {
		m_bIsDead = true;
	}

}

void CSpear::Release()
{
}
