#include "Door.h"
#include "Camera.h"

CDoor::CDoor()
{
}

CDoor::~CDoor()
{
}

void CDoor::Initialize()
{
	m_tSize = { 100.f,100.f };

}

void CDoor::Update()
{
}

void CDoor::Render(HDC _hDC)
{
	Vector renderPos =  CCamera::GetInstance()->GetRenderPos(m_tPosition);
	Rectangle(_hDC, renderPos.m_fX - m_tSize.m_fX * 0.5f,
		renderPos.m_fY - m_tSize.m_fY * 0.5f,
		renderPos.m_fX + m_tSize.m_fX * 0.5f,
		renderPos.m_fY + m_tSize.m_fY * 0.5f);

}

void CDoor::LateUpdate()
{
}

void CDoor::Release()
{
}

void CDoor::OnCollide(CObj* _pObj)
{
}
