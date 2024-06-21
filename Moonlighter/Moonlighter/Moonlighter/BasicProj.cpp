#include "BasicProj.h"
#include"Component.h"

CBasicProj::CBasicProj() :m_pComponent(nullptr)
{
}

CBasicProj::~CBasicProj()
{
	Release();
}

void CBasicProj::Initialize()
{
	m_iRendNum = PROJ;

	m_tSize = { 30.f,30.f };
	m_pComponent = new CComponent;
	m_fSpeed = 5.f;
}

void CBasicProj::Update()
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
}

void CBasicProj::Render(HDC _hDC)
{
	m_pComponent->PlayAnim(m_strKeyName, _hDC, m_tPosition);
}

void CBasicProj::LateUpdate()
{
}

void CBasicProj::Release()
{
	SAFE_DELETE<CComponent*>(m_pComponent);
}
