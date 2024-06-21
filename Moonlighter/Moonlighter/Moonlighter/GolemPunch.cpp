#include "GolemPunch.h"
#include"Component.h"
#include"Camera.h"
#include"SoundMgr.h"
#include"Tile.h"

CGolemPunch::CGolemPunch() : m_pComponent(nullptr), m_pEffectList(nullptr)
{
}


CGolemPunch::~CGolemPunch()
{
	Release();
}

void CGolemPunch::Initialize()
{
	m_iRendNum = PROJ;

	m_fPunchSpeed = 30.f;
	m_pComponent = new CComponent;
	m_strKeyName = "PROJ_PUNCH";
	m_iDamage = 10;
	m_eProjType = EProjectileType::GOLEMPUNCH;
	m_tSize = { 40.f, 40.f };
}

void CGolemPunch::Update()
{

	if (m_bIsAtkDone) {
		m_bIsDead = true;
	}

	if (_iAnimRow >= 1) {
		m_tSize = { 0.f , 0.f };
		m_iDamage = 0;
	}

	m_tPosition.m_fY += m_fPunchSpeed ;
	if (m_tTargetPos.m_fY <= m_tPosition.m_fY && _iAnimRow == 0) {
		m_tPosition.m_fY = m_tTargetPos.m_fY;
		m_tSize = { 40.f,30.f };
		if (!m_vib) {
			CCamera::GetInstance()->Vibration(20.f, 0.4f, 40.f, EDirection::RIGHT);
			CSoundMgr::Get_Instance()->StopSound(BOSS_EFFECT);
			CSoundMgr::Get_Instance()->PlaySound(L"golem_dungeon_king_golem_handcrash.wav", BOSS_EFFECT, 1.f);
			
			//咯扁 农发 积己
			CObj* newCrack = new CTile();
			dynamic_cast<CTile*>(newCrack)->SetImgKeyInt(9);
			newCrack->SetPosition(m_tTargetPos);
			newCrack->Initialize();
			m_pEffectList->push_back(newCrack);

			m_vib = true;
		}
	}
}

void CGolemPunch::Render(HDC _hDC)
{

	if (m_bIsAtkDone) {
		return;
	}

	if (m_pComponent->PlayAnimGetRow(m_strKeyName, _hDC, { m_tPosition.m_fX , m_tPosition.m_fY }, _iAnimRow)) {
		if (_iAnimRow == 0) {
			++_iAnimRow;
			m_fPunchSpeed *= -1;
		}
		else if (_iAnimRow == 1) {
			m_bIsAtkDone = true;
		}
	}
}

void CGolemPunch::LateUpdate()
{
}

void CGolemPunch::Release()
{
	SAFE_DELETE<CComponent*>(m_pComponent);
}

void CGolemPunch::OnCollide(CObj* _pObj)
{
}
