#include "GolemSoldier.h"
#include"SoundMgr.h"

CGolemSoldier::CGolemSoldier()
{
}

CGolemSoldier::~CGolemSoldier()
{
}

void CGolemSoldier::Initialize()
{
	CMonster::Initialize();
	m_iHp = 70;
	m_tSize = { 50.f,60.f };
	m_iDropItemNum = 4;
}

void CGolemSoldier::Update()
{
	if (IDLE == m_eState) {
		PlayerDetect();
	}

	if (GetPlayerDistance() < 130 && m_dwAttackTime+4000 < (DWORD)GetTickCount64()) {
		m_eState = ATTACK;
	}

}

void CGolemSoldier::Render(HDC _hDC)
{
	CheckHitRender();
	switch (m_eDir)
	{
	case EDirection::UP:
		if (m_eState == ATTACK) {
			if (m_pComponent->PlayAnimGetRow("SOLDIER_ATK_UP", _hDC, m_tPosition, (int)m_HitRender)) {
				m_eState = IDLE;
				m_dwAttackTime = (DWORD)GetTickCount64();
			}
		}
		else {
			m_pComponent->PlayAnimGetRow("SOLDIER_IDLE_UP", _hDC, m_tPosition, (int)m_HitRender);
		}
		break;
	case EDirection::DOWN:
		if (m_eState == ATTACK) {
			if (m_pComponent->PlayAnimGetRow("SOLDIER_ATK_DOWN", _hDC, m_tPosition, (int)m_HitRender)) {
				m_eState = IDLE;
				m_dwAttackTime = (DWORD)GetTickCount64();
			}
		}
		else {
			m_pComponent->PlayAnimGetRow("SOLDIER_IDLE_DOWN", _hDC, m_tPosition, (int)m_HitRender);
		}

		break;
	case EDirection::LEFT:
		if (m_eState == ATTACK) {
			if (m_pComponent->PlayAnimGetRow("SOLDIER_ATK_LEFT", _hDC, m_tPosition, (int)m_HitRender)) {
				m_eState = IDLE;
				m_dwAttackTime = (DWORD)GetTickCount64();
			}
		}
		else {
			m_pComponent->PlayAnimGetRow("SOLDIER_IDLE_LEFT", _hDC, m_tPosition, (int)m_HitRender);
		}

		break;
	case EDirection::RIGHT:

		if (m_eState == ATTACK) {
			if (m_pComponent->PlayAnimGetRow("SOLDIER_ATK_RIGHT", _hDC, m_tPosition, (int)m_HitRender)) {
				m_eState = IDLE;
				m_dwAttackTime = (DWORD)GetTickCount64();
			}
		}
		else {
			m_pComponent->PlayAnimGetRow("SOLDIER_IDLE_RIGHT", _hDC, m_tPosition, (int)m_HitRender);
		}

		break;
	case EDirection::ENUM_END:
		break;
	default:
		break;
	}
	CMonster::Render();

}

void CGolemSoldier::LateUpdate()
{
	CheckHitTime();
}

void CGolemSoldier::Release()
{
}

void CGolemSoldier::OnAttacked(int _damage)
{
	CMonster::OnAttacked(_damage);
	CSoundMgr::Get_Instance()->StopSound(SOUND_EFFECT);
	CSoundMgr::Get_Instance()->PlaySound(L"golem_dungeon_king_golem_hit.wav", SOUND_EFFECT, 1.f);
}
