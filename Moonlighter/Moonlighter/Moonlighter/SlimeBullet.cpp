#include "SlimeBullet.h"

CSlimeBullet::CSlimeBullet() :m_pComponent(nullptr)
{
}

CSlimeBullet::~CSlimeBullet()
{
	Release();
}

void CSlimeBullet::Initialize()
{
	m_iRendNum = PROJ;

	m_tSize = { 40.f,40.f };
	m_pComponent = new CComponent;
	m_fSpeed = 10.f;
	m_iDamage = 10.f;
}

void CSlimeBullet::Update()
{
	m_tPosition.m_fX += m_fSpeed * cosf(m_fAngle * (PI / 180.f));
	m_tPosition.m_fY += m_fSpeed * sinf(m_fAngle * (PI / 180.f));

}

void CSlimeBullet::Render(HDC _hDC)
{
	m_pComponent->PlayAnim("SLIMEBULLET", _hDC, m_tPosition);
	
}

void CSlimeBullet::LateUpdate()
{
}

void CSlimeBullet::Release()
{
	SAFE_DELETE<CComponent*>(m_pComponent);
}
