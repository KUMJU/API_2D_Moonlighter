#include "FruitTurret.h"
#include"Camera.h"
#include"BasicProj.h"
#include"SoundMgr.h"

CFruitTurret::CFruitTurret()
{
}

CFruitTurret::~CFruitTurret()
{
}

void CFruitTurret::Initialize()
{
	m_iHp = 50;
	m_tSize = { 60.f,80.f };
	CMonster::Initialize();
	m_fSpeed = 2.f;
	m_strKeyName = "BOSS2_SEED";
	m_dwAttackTime = 0;
}

void CFruitTurret::Update()
{
	WalkDir();
	if (EFruitState::ATTACK == m_currentState) {
		ShootBullet();
	}
}

void CFruitTurret::Render(HDC _hDC)
{
	CheckHitRender();

	/*Vector renderVEC = CCamera::GetInstance()->GetRenderPos(m_tPosition);

	
	
	Nngle(_hDC, renderVEC.m_fX - m_tSize.m_fX * 0.5f,
		renderVEC.m_fY - m_tSize.m_fY * 0.5f,
		renderVEC.m_fX + m_tSize.m_fX * 0.5f,
		renderVEC.m_fY + m_tSize.m_fY * 0.5f);*/


	switch (m_currentState)
	{
	case EFruitState::IDLE:
		if (EDirection::LEFT == m_eDir) {
			m_pComponent->PlayAnimGetRow("FRUIT_WALK_LEFT", _hDC, m_tPosition, (int)m_HitRender);

		}
		else if (EDirection::RIGHT == m_eDir) {
			m_pComponent->PlayAnimGetRow("FRUIT_WALK_RIGHT", _hDC, m_tPosition, (int)m_HitRender);
		}
		break;
	case EFruitState::ATTACK:
		if (EDirection::LEFT == m_eDir) {
			m_pComponent->PlayAnimGetRow("FRUIT_ATK_LEFT", _hDC, m_tPosition, (int)m_HitRender);

		}
		else if (EDirection::RIGHT == m_eDir) {
			m_pComponent->PlayAnimGetRow("FRUIT_ATK_RIGHT", _hDC, m_tPosition, (int)m_HitRender);
		}
		break;
	default:
		break;
	}
}

void CFruitTurret::LateUpdate()
{
	CheckHitTime();

	if (3 == m_iAtkiCount) {
		m_iAtkiCount = 0;
		m_dwAttackTime = (DWORD)GetTickCount64();
		m_currentState = EFruitState::IDLE;
	}

}

void CFruitTurret::Release()
{
}

void CFruitTurret::WalkDir()
{
	if (m_pPlayerCopy->GetPosition().m_fY < m_tPosition.m_fY) {
		m_tPosition.m_fY -= m_fSpeed;
	}

	if (m_pPlayerCopy->GetPosition().m_fY > m_tPosition.m_fY) {
		m_tPosition.m_fY += m_fSpeed;
	}
	
	if (fabs(m_tPosition.m_fY - m_pPlayerCopy->GetPosition().m_fY) < 70 && EFruitState::IDLE == m_currentState &&
		m_dwAttackTime + 800 < (DWORD)GetTickCount64()) {
		m_currentState = EFruitState::ATTACK;
		m_dwAttackTime = GetTickCount64();
	}

}

void CFruitTurret::ShootBullet()
{
	if (m_dwAttackTime + 800 < (DWORD)GetTickCount64()) {

		CSoundMgr::Get_Instance()->StopSound(SOUND_EFFECT2);
		CSoundMgr::Get_Instance()->PlaySound(L"forest_dungeon_fruitturret_attack.wav", SOUND_EFFECT2, 1.f);

		CObj* newBullet = new CBasicProj;
		newBullet->SetPosition(m_tPosition);

		if (EDirection::LEFT == m_eDir) {
			dynamic_cast<CBasicProj*>(newBullet)->SetDirection(EDirection::LEFT);
		}
		else if (EDirection::RIGHT == m_eDir) {
			dynamic_cast<CBasicProj*>(newBullet)->SetDirection(EDirection::RIGHT);
		}

		dynamic_cast<CBasicProj*>(newBullet)->SetAnimKey(m_strKeyName);
		dynamic_cast<CBasicProj*>(newBullet)->SetDamage(10);
		newBullet->Initialize();
		m_pProjList->push_back(newBullet);

		m_dwAttackTime = (DWORD)GetTickCount64();
		++m_iAtkiCount;
	}


}

void CFruitTurret::SetDirNum(int _num)
{

	if (1 == _num) {
		m_eDir = EDirection::RIGHT;
	}
	else {
		m_eDir = EDirection::LEFT;

	}

}

void CFruitTurret::OnAttacked(int _damage)
{
	CMonster::OnAttacked(_damage);
	CSoundMgr::Get_Instance()->StopSound(DAMAGE_EFFECT);
	CSoundMgr::Get_Instance()->PlaySound(L"forest_dungeon_enemy_hit.wav", DAMAGE_EFFECT, 1.f);

}
