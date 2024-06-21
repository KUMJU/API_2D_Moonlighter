#include "SeedProj.h"
#include"Camera.h"

CSeedProj::CSeedProj() : m_fAngle(0.f) , m_pComponent(nullptr)
{
}

CSeedProj::~CSeedProj()
{
}

void CSeedProj::Initialize()
{
	m_iRendNum = PROJ;

	m_fSpeed = 5.f;
	m_tSize = { 10.f,10.f };

}

void CSeedProj::Update()
{
	m_tPosition.m_fX += m_fSpeed * cosf(m_fAngle * (PI / 180.f));
	m_tPosition.m_fY -= m_fSpeed * sinf(m_fAngle * (PI / 180.f));

}

void CSeedProj::Render(HDC _hDC)
{

	Vector renderVEC = CCamera::GetInstance()->GetRenderPos(m_tPosition);
	m_pComponent->RenderImage("BOSS2_SEED", _hDC, m_tPosition);

}

void CSeedProj::LateUpdate()
{
}

void CSeedProj::Release()
{
}

void CSeedProj::OnCollide(CObj* _pObj)
{
}
