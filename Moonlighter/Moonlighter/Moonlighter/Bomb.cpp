#include "Bomb.h"
#include"Component.h"
#include"SoundMgr.h"

CBomb::CBomb()
{
}

CBomb::~CBomb()
{
	Release();
}

void CBomb::Initialize()
{
	m_pComponent = new CComponent;
	m_tSize = { 50.f,50.f };
	m_eProjType = EProjectileType::BOMB;
	m_iRendNum = PROJ;

	CSoundMgr::Get_Instance()->StopSound(SOUND_EFFECT2);
	CSoundMgr::Get_Instance()->PlaySound(L"explosive_bow.wav", SOUND_EFFECT2, 1.f);
}

void CBomb::Update()
{
	
}

void CBomb::Render(HDC _hDC)
{
	if (m_pComponent->PlayAnim("PROJ_BOMB", _hDC, m_tPosition)) {
		m_bIsDead = true;
	}
	
}

void CBomb::LateUpdate()
{
}

void CBomb::Release()
{
	SAFE_DELETE<CComponent*>(m_pComponent);
	
}

void CBomb::OnCollide(CObj* _pObj)
{
}
