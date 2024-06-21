#include "Arrow.h"
#include"Camera.h"

CArrow::CArrow()
{
}

CArrow::~CArrow()
{
}

void CArrow::Initialize()
{
	m_iDamage = 20;
	m_fSpeed = 15.f;

	if (m_eDir == EDirection::UP) {
		m_tSize = { 13.f,50.f };
		m_tPosition.m_fY -= 20.f;

	}else if(m_eDir == EDirection::DOWN) {
		m_tSize = { 13.f,50.f };
		m_tPosition.m_fY += 20.f;

	}
	else if (m_eDir == EDirection::RIGHT) {
		m_tSize = { 50.f,13.f };
		m_tPosition.m_fX += 20.f;

	}
	else if (m_eDir == EDirection::LEFT) {
		m_tSize = { 50.f,13.f };
		m_tPosition.m_fX += 20.f;
	}

	m_iAnimNum = static_cast<unsigned int>(m_eDir);
	m_eProjType = EProjectileType::PLAYER;

}

void CArrow::Update()
{
	switch (m_eDir)
	{
	case EDirection::UP:
		m_tPosition.m_fY -= m_fSpeed;
		break;
	case EDirection::DOWN:
		m_tPosition.m_fY += m_fSpeed;
		break;
	case EDirection::LEFT:
		m_tPosition.m_fX -= m_fSpeed;

		break;
	case EDirection::RIGHT:
		m_tPosition.m_fX += m_fSpeed;

		break;
	case EDirection::ENUM_END:
		break;
	default:
		break;
	}

	m_fCurDistance += m_fSpeed;

}

void CArrow::Render(HDC _hDC)
{
	Vector RenderVec = CCamera::GetInstance()->GetRenderPos(m_tPosition);
	CMyResource* CurRes = CResourceMgr::GetInstance()->FindRes("WEAPON_ARROW");

	if (CurRes) {
		AnimInfo tempInfo = CurRes->GetResInfo();

		GdiTransparentBlt(_hDC,
			static_cast<int>(RenderVec.m_fX - tempInfo.iSizeX *0.5f),
			static_cast<int>(RenderVec.m_fY - tempInfo.iSizeY*0.5f),
			tempInfo.iSizeX,
			tempInfo.iSizeY,
			CurRes->GetMemDC(),
			m_iAnimNum * tempInfo.iSizeX,
			0,
			tempInfo.iSizeX,
			tempInfo.iSizeY,
			RGB(0, 0, 0));
	}
}

void CArrow::LateUpdate()
{
	if (m_fMaxDistance <= m_fCurDistance) {
		m_bIsDead = true;
	}

}

void CArrow::Release()
{
}

void CArrow::OnCollide(CObj* _pObj)
{
}
