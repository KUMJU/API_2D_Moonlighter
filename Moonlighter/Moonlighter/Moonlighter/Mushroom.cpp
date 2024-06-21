#include "Mushroom.h"
#include"Tile.h"
#include"SoundMgr.h"


CMushroom::CMushroom()
{
}

CMushroom::~CMushroom()
{
}

void CMushroom::Initialize()
{
	CMonster::Initialize();
	m_fSpeed = 9.f;
	m_iHp = 50;
	m_tSize = { 60.f,60.f };
	m_eCurrentState = EMushState::STUN;
	m_dwCrashTime = (DWORD)GetTickCount64();
}

void CMushroom::Update()
{

	if (m_dwCrashTime + 3000 < (DWORD)GetTickCount64() && EMushState::STUN == m_eCurrentState) {
		m_eCurrentState = EMushState::PREPARE;
		//CSoundMgr::Get_Instance()->StopSound(MONSTER_EFFECT);
	//	CSoundMgr::Get_Instance()->PlaySound(L"forest_dungeon_spinningmushroom_clash.wav", MONSTER_EFFECT, 1.f);
	}

	if (EMushState::ATTACK == m_eCurrentState) {
		m_tPosition = m_tPosition + DirVec * m_fSpeed;
		m_isSetDir = false;
	}
}

void CMushroom::Render(HDC _hDC)
{
	CheckHitRender();

	switch (m_eCurrentState)
	{
	case EMushState::STUN:
		m_pComponent->PlayAnimGetRow("MUSH_PRE", _hDC, m_tPosition, (int)m_HitRender);
		break;
	case EMushState::PREPARE:
		if (m_pComponent->PlayAnimGetRow("MUSH_IDLE", _hDC, m_tPosition, (int)m_HitRender)) {
			m_eCurrentState = EMushState::ATTACK;
			CSoundMgr::Get_Instance()->StopSound(MONSTER_EFFECT);
			CSoundMgr::Get_Instance()->PlaySound(L"forest_dungeon_spinningmushroom_prepare.wav", MONSTER_EFFECT, 1.f);
		}
		break;
	case EMushState::ATTACK:
		m_pComponent->PlayAnimGetRow("MUSH_CRASH", _hDC, m_tPosition, (int)m_HitRender);
		break;
	case EMushState::ENUM_END:
		break;
	default:
		break;
	}


}

void CMushroom::LateUpdate()
{
	CheckHitTime();

	if (m_eCurrentState == EMushState::PREPARE) {
		SetNewAngle();
	}

}

void CMushroom::Release()
{
}

void CMushroom::OnAttacked(int _damage)
{
	CMonster::OnAttacked(_damage);
	CSoundMgr::Get_Instance()->StopSound(DAMAGE_EFFECT);
	CSoundMgr::Get_Instance()->PlaySound(L"forest_dungeon_enemy_hit.wav", DAMAGE_EFFECT, 1.f);

}

void CMushroom::OnCollide(CObj* _pObj)
{

	if (true == m_isSetDir) {
		return;
	}

	if (_pObj->GetObjType() == EObjectType::OBSTACLE) {
		if (ETileType::WALL == dynamic_cast<CTile*>(_pObj)->GetTileType()) {
			if (m_eCurrentState == EMushState::ATTACK ) {
				m_dwCrashTime = GetTickCount64();
				m_isSetDir = true;
				m_eCurrentState = EMushState::STUN;

				CSoundMgr::Get_Instance()->StopSound(MONSTER_EFFECT);
				CSoundMgr::Get_Instance()->PlaySound(L"ghost_hit.wav", MONSTER_EFFECT, 1.f);
			}

		}
	}


}

void CMushroom::SetNewAngle()
{
	Vector plrVec = { m_pPlayerCopy->GetPosition().m_fX , m_pPlayerCopy->GetPosition().m_fY };
	DirVec = plrVec - m_tPosition;
	DirVec.Normalize();
}
