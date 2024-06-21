#include "Turret.h"
#include"BasicProj.h"
#include"SoundMgr.h"

CTurret::CTurret()
{
}

CTurret::~CTurret()
{
	Release();
}

void CTurret::Initialize()
{
	CMonster::Initialize();
	m_iHp = 40;
	m_tSize = { 40.f,40.f };
	m_iDropItemNum = 3;
}

void CTurret::Update()
{
	if(0 == m_iCount && false == m_IsAtk)
		PlayerDetect();

}

void CTurret::Render(HDC _hDC)
{
	CheckHitRender();
	m_IsAtk = true;
	switch (m_eDir)
	{
	case EDirection::UP:
		if (m_pComponent->PlayAnimGetRow("TURRET_ATK_UP", _hDC, m_tPosition, (int)m_HitRender)) {
			m_strKeyName = "PROJ_TURRET_UP";
			CreateBullet();
			++m_iCount;

		}
		break;
	case EDirection::DOWN:
		if (m_pComponent->PlayAnimGetRow("TURRET_ATK_DOWN", _hDC, m_tPosition, (int)m_HitRender)) {
			m_strKeyName = "PROJ_TURRET_DOWN";
			CreateBullet();
			++m_iCount;
		}
		break;
	case EDirection::LEFT:
		if (m_pComponent->PlayAnimGetRow("TURRET_ATK_LEFT", _hDC, m_tPosition, (int)m_HitRender)) {
			m_strKeyName = "PROJ_TURRET_LEFT";
			CreateBullet();
			++m_iCount;
		}
		break;
	case EDirection::RIGHT:
		if (m_pComponent->PlayAnimGetRow("TURRET_ATK_RIGHT", _hDC, m_tPosition, (int)m_HitRender)) {
			m_strKeyName = "PROJ_TURRET_RIGHT";
			CreateBullet();
			++m_iCount;
		}
		break;
	case EDirection::ENUM_END:

		break;
	default:
		break;
	}
	CMonster::Render();

}

void CTurret::LateUpdate()
{
	CheckHitTime();
	if (3 == m_iCount) {
		m_iCount = 0;
		m_IsAtk = false;
	}
}

void CTurret::Release()
{
}

void CTurret::CreateBullet()
{
	CObj* newBullet = new CBasicProj;
	newBullet->SetPosition(m_tPosition);
	newBullet->Initialize();
	dynamic_cast<CBasicProj*>(newBullet)->SetDamage(10);
	dynamic_cast<CBasicProj*>(newBullet)->SetDirection(m_eDir);
	dynamic_cast<CBasicProj*>(newBullet)->SetAnimKey(m_strKeyName);
	m_pProjList->push_back(newBullet);

	CSoundMgr::Get_Instance()->StopSound(SOUND_EFFECT);
	CSoundMgr::Get_Instance()->PlaySound(L"golem_dungeon_turret_shot.wav", SOUND_EFFECT, 1.f);
}

void CTurret::OnAttacked(int _damage)
{
	CMonster::OnAttacked(_damage);
	CSoundMgr::Get_Instance()->StopSound(SOUND_EFFECT);
	CSoundMgr::Get_Instance()->PlaySound(L"golem_dungeon_king_golem_hit.wav", SOUND_EFFECT, 1.f);
}
