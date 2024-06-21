#include "Monster.h"
#include"GameMgr.h"
#include"Item.h"
#include"SoundMgr.h"
#include"Effect.h"

CMonster::CMonster() : m_pComponent(nullptr), m_pPlayerCopy(nullptr), m_pProjList(nullptr)
{
}

CMonster::~CMonster()
{
	Release();
}

void CMonster::Initialize()
{
	m_iRendNum = GAMEOBJECT;
	m_pComponent = new CComponent;
	m_pPlayerCopy = CGameMgr::GetInstance()->GetPlayer();
	m_iDamage = 10;
}

void CMonster::Render()
{

}

void CMonster::LateUpdate()
{
	CheckHitTime();
}

void CMonster::Release()
{
	SAFE_DELETE<CComponent*>(m_pComponent);
}

void CMonster::OnCollide(CObj* _pObj)
{
}

void CMonster::OnAttacked(int _damage)
{
	if (m_IsOnHit)
		return;

	m_IsOnHit = true;
	m_iHp -= _damage;
	m_HitTime = (DWORD)GetTickCount64();

	//SetHitEffect();

	if (m_iHp <= 0) {
		m_iHp = 0;

		if (0 != m_iDropItemNum) {
			CObj* dropItem = new CItem;
			dropItem->SetPosition(m_tPosition);
			dropItem->Initialize();
			dynamic_cast<CItem*>(dropItem)->SetItemInfo(m_iDropItemNum);
			m_pItemList->push_back(dropItem);
		}

		//effect EFFECT_MONDEAD

		CObj* deadEffect = new CEffect("EFFECT_MONDEAD", 600, EDirection::UP);
		deadEffect->SetPosition(m_tPosition);
		deadEffect->Initialize();
		m_pEffectList->push_back(deadEffect);

		CSoundMgr::Get_Instance()->StopSound(SOUND_EFFECT2);
		CSoundMgr::Get_Instance()->PlaySound(L"enemy_death.wav", SOUND_EFFECT2, 2.f);
		m_bIsDead = true;
	}

}

void CMonster::PlayerDetect()
{
	Vector tPlayerPos = m_pPlayerCopy->GetPosition();

	float fDistanceX = m_tPosition.m_fX - tPlayerPos.m_fX;
	float fDistanceY = m_tPosition.m_fY - tPlayerPos.m_fY;

	if (fabs(fDistanceX) > fabs(fDistanceY)) {
		if (fDistanceX > 0) {
			m_eDir = EDirection::LEFT;
		}
		else {
			m_eDir = EDirection::RIGHT;
		}
	}
	else {
		if (fDistanceY > 0) {
			m_eDir = EDirection::UP;
		}
		else {
			m_eDir = EDirection::DOWN;
		}
	}
}

void CMonster::FollowPlayer()
{

	float m_distanceX = m_pPlayerCopy->GetPosition().m_fX - m_tPosition.m_fX;
	float m_distanceY = m_pPlayerCopy->GetPosition().m_fY - m_tPosition.m_fY;

	float fDistance = sqrtf(m_distanceX * m_distanceX + m_distanceY * m_distanceY);
	float m_fAngle = acosf(m_distanceX / fDistance);

	if (m_pPlayerCopy->GetPosition().m_fY > m_tPosition.m_fY) {
		m_fAngle *= -1.f;
	}

	m_tPosition.m_fX += (m_fSpeed * cosf(m_fAngle));
	m_tPosition.m_fY -= (m_fSpeed * sinf(m_fAngle));
}

float CMonster::GetPlayerDistance()
{
	Vector tPlayerPos = m_pPlayerCopy->GetPosition();

	float fDistanceX = m_tPosition.m_fX - tPlayerPos.m_fX;
	float fDistanceY = m_tPosition.m_fY - tPlayerPos.m_fY;

	float tDistance = sqrtf(fDistanceX * fDistanceX + fDistanceY * fDistanceY);

	return fabs(tDistance);
}

void CMonster::CheckHitTime()
{
	if (true == m_IsOnHit) {
		if (m_HitTime + 600 < (DWORD)GetTickCount64()) {
			m_IsOnHit = false;
			m_HitRender = false;
		}
	}
}

void CMonster::CheckHitRender()
{
	if (!m_IsOnHit) {
		return;
	}

	if (m_HitRenderTime + 100 <= (DWORD)GetTickCount64()) {
		m_HitRender = !m_HitRender;
		m_HitRenderTime = GetTickCount64();
	}
}

void CMonster::KnockBack()
{
		switch (m_pPlayerCopy->GetDir())
		{
		case EDirection::UP:
			m_tPosition.m_fY -= 30.f;
			break;
		case EDirection::DOWN:
			m_tPosition.m_fY += 30.f;

			break;
		case EDirection::LEFT:
			m_tPosition.m_fX -= 30.f;
			break;
		case EDirection::RIGHT:
			m_tPosition.m_fX += 30.f;
			break;
		default:
			break;
		}



}

void CMonster::SetHitEffect()
{
	EDirection dir = m_pPlayerCopy->GetDir();

	CObj* hitEffect = new CEffect("EFFECT_HIT", 300, dir);
	if (EDirection::DOWN == dir)
		hitEffect->SetPosition({ m_tPosition.m_fX, m_tPosition.m_fY - m_tSize.m_fY * 0.5f });
	else if (EDirection::UP == dir)
		hitEffect->SetPosition({ m_tPosition.m_fX, m_tPosition.m_fY + m_tSize.m_fY * 0.5f });
	else if (EDirection::LEFT == dir)
		hitEffect->SetPosition({ m_tPosition.m_fX + m_tSize.m_fX * 0.5f, m_tPosition.m_fY });
	else if (EDirection::RIGHT == dir)
		hitEffect->SetPosition({ m_tPosition.m_fX - m_tSize.m_fX * 0.5f, m_tPosition.m_fY });

	hitEffect->Initialize();
	m_pEffectList->push_back(hitEffect);
}
