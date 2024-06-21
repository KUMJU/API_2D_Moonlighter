#include "Cutting.h"
#include"SeedProj.h"

CCutting::CCutting()
{
}

CCutting::~CCutting()
{
}

void CCutting::Initialize()
{
	m_iHp = 40;
	m_tSize = { 20.f,20.f };
	CMonster::Initialize();
}

void CCutting::Update()
{

	if ((m_dwAttackTime + 3000 < (DWORD)GetTickCount64()) && m_IsReady == true) {
		CObj* newSeed = new CSeedProj;
		dynamic_cast<CSeedProj*>(newSeed)->SetAngle(GetAngle());
		newSeed->SetPosition(m_tPosition);
		newSeed->Initialize();
		m_pProjList->push_back(newSeed);
		m_dwAttackTime = (DWORD)GetTickCount64();
	}

}

void CCutting::Render(HDC _hDC)
{
	CheckHitRender();

	if (m_IsReady) {
		(m_pComponent->RenderImage("CUTTING_IDLE", _hDC, m_tPosition));
		(m_pComponent->PlayAnimGetRow("CUTTING_SHOT", _hDC, { m_tPosition.m_fX , m_tPosition.m_fY- 20.f }, (int)m_HitRender));
	}
	else {
		if (m_pComponent->PlayAnimGetRow("CUTTING_GLOWUP", _hDC, m_tPosition, (int)m_HitRender)) {
			m_IsReady = true;
			m_dwAttackTime = (DWORD)GetTickCount64();
		}
	}

//	m_pComponent->RenderImage("CUTTING_TEST", _hDC, m_tPosition);
}

void CCutting::LateUpdate()
{
	CheckHitTime();
}

void CCutting::Release()
{
}

float CCutting::GetAngle()
{
	float m_distanceX = m_pPlayerCopy->GetPosition().m_fX - m_tPosition.m_fX;
	float m_distanceY = m_pPlayerCopy->GetPosition().m_fY - m_tPosition.m_fY;

	float fDistance = sqrtf(m_distanceX * m_distanceX + m_distanceY * m_distanceY);
	float m_fAngle = acosf(m_distanceX / fDistance);

	if (m_pPlayerCopy->GetPosition().m_fY > m_tPosition.m_fY) {
		m_fAngle *= -1.f;
	}
	m_fAngle = m_fAngle * (180 / PI);

	return m_fAngle;
}
