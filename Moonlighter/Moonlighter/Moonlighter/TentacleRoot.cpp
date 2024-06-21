#include "TentacleRoot.h"
#include"Component.h"

CTentacleRoot::CTentacleRoot() : m_dwCreateTime(0) , m_eState(TS_READY) , m_pComponent(nullptr)
{
}

CTentacleRoot::~CTentacleRoot()
{
	Release();

}

void CTentacleRoot::Initialize()
{
	m_iRendNum = GAMEOBJECT;
	m_tSize = { 30.f,30.f };
	m_pComponent = new CComponent;
	m_eState = TS_READY;
	m_eProjType = EProjectileType::TENTACLE;
	m_iDamage = 20;
	m_dwCreateTime = GetTickCount64();
	
}

void CTentacleRoot::Update()
{
	if (m_dwCreateTime + 6000 <= GetTickCount64()) {
		m_eState = TS_DEAD;
	}

}

void CTentacleRoot::Render(HDC _hDC)
{

	switch (m_eState)
	{
	case TS_READY:
		if (m_pComponent->PlayAnim("ROOT1_START", _hDC, m_tPosition)) {
			m_eState = TS_IDLE;
		}
		break;
	case TS_IDLE:
		m_pComponent->PlayAnim("ROOT1_IDLE", _hDC, m_tPosition);
		break;
	case TS_DEAD:
		if (m_pComponent->PlayAnim("ROOT1_FIN", _hDC, m_tPosition)) {
			m_bIsDead = true;
		}
		break;
	default:
		break;
	}

}

void CTentacleRoot::LateUpdate()
{
}

void CTentacleRoot::Release()
{
	SAFE_DELETE<CComponent*>(m_pComponent);
}
