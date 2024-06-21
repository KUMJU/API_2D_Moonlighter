#include "FireShield.h"
#include"GameMgr.h"
#include"Component.h"
#include"SoundMgr.h"

CFireShield::CFireShield() : m_pComponent(nullptr) , m_pPlayerCopy(nullptr)
{

}

CFireShield::~CFireShield()
{
	Release();
}

void CFireShield::Initialize()
{
	m_CreateTime = GetTickCount64();
	m_tSize = { 200.f,200.f };
	m_eProjType = EProjectileType::SHIELD;
	m_pPlayerCopy = CGameMgr::GetInstance()->GetPlayer();
	m_pComponent = new CComponent;

	CSoundMgr::Get_Instance()->StopSound(PLAYER_EFFECT);
	CSoundMgr::Get_Instance()->PlaySound(L"fireShield.wav", PLAYER_EFFECT, 1.f);
}

void CFireShield::Update()
{
	m_tPosition = m_pPlayerCopy->GetPosition();
}

void CFireShield::Render(HDC _hDC)
{
	m_pComponent->PlayAnim("FIRESHIELD", _hDC, m_tPosition);
}

void CFireShield::LateUpdate()
{
	if (m_CreateTime + 10000 < (DWORD)GetTickCount64()) {
		m_bIsDead = true;
	}

}

void CFireShield::Release()
{
	SAFE_DELETE<CComponent*>(m_pComponent);
}

void CFireShield::OnCollide(CObj* _pObj)
{
}
