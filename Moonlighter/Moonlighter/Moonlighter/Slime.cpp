#include "Slime.h"
#include"SoundMgr.h"

CSlime::CSlime()
{
}

CSlime::~CSlime()
{
	Release();
}

void CSlime::Initialize()
{
	CMonster::Initialize();
	m_iHp = 40;
	m_tSize = { 30.f,30.f };
	m_fSpeed = 2.f;
}

void CSlime::Update()
{
	FollowPlayer();
}

void CSlime::Render(HDC _hDC)
{
	CheckHitRender();
	m_pComponent->PlayAnimGetRow("SLIME_ANIM",_hDC , m_tPosition, (int)m_HitRender);
}

void CSlime::LateUpdate()
{
	CheckHitTime();
}

void CSlime::Release()
{
}

void CSlime::OnAttacked(int _damage)
{
	CMonster::KnockBack();
	CMonster::OnAttacked(_damage);
	CSoundMgr::Get_Instance()->StopSound(SOUND_EFFECT);
	CSoundMgr::Get_Instance()->PlaySound(L"golem_dungeon_babyslime_hit.wav", SOUND_EFFECT, 1.f);
}
