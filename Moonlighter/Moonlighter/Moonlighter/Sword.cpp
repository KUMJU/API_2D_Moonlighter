#include "Sword.h"

#include"Camera.h"


CSword::CSword()
{
}

CSword::~CSword()
{
}

void CSword::Initialize()
{
	dwTime = GetTickCount64();
	m_iDamage = 30;


	if (m_eDir == EDirection::UP) {
		m_tSize = { 65.f,55.f };
		m_tPosition.m_fY -= 60.f;

	}
	else if (m_eDir == EDirection::DOWN) {
		m_tSize = { 65.f,55.f };
		m_tPosition.m_fY += 60.f;

	}
	else if (m_eDir == EDirection::RIGHT) {
		m_tSize = { 55.f,65.f };
		m_tPosition.m_fX += 60.f;

	}
	else if (m_eDir == EDirection::LEFT) {
		m_tSize = { 55.f,65.f };
		m_tPosition.m_fX -= 60.f;
	}

	m_eProjType = EProjectileType::PLAYER;
}

void CSword::Update()
{
}

void CSword::Render(HDC _hDC)
{
	Vector renderVec = CCamera::GetInstance()->GetRenderPos(m_tPosition);

}

void CSword::LateUpdate()
{
	if (dwTime + 500 <= (DWORD)GetTickCount64()) {
		m_bIsDead = true;
	}
}

void CSword::Release()
{
}
