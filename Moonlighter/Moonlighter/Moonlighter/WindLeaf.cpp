#include "WindLeaf.h"
#include"BasicProj.h"
#include"SoundMgr.h"

CWindLeaf::CWindLeaf()
{
}

CWindLeaf::~CWindLeaf()
{
}

void CWindLeaf::Initialize()
{
	m_tSize = { 80.f,80.f };
	m_fSpeed = 2.f;
	m_iHp = 100;
	m_strKeyName = "PROJ_WINDBALL";
	CMonster::Initialize();

}

void CWindLeaf::Update()
{
	Moving();
}

void CWindLeaf::Render(HDC _hDC)
{
	CheckHitRender();

	switch (m_CurrentState)
	{
	case EWindLeafState::IDLE:
		switch (m_eDir)
		{
		case EDirection::UP:
			m_pComponent->PlayAnimGetRow("WINDLEAF_WALK_UP", _hDC, m_tPosition, (int)m_HitRender);
			break;
		case EDirection::DOWN:
			m_pComponent->PlayAnimGetRow("WINDLEAF_WALK_DOWN", _hDC, m_tPosition, (int)m_HitRender);
			break;
		case EDirection::LEFT:
			m_pComponent->PlayAnimGetRow("WINDLEAF_WALK_LEFT", _hDC, m_tPosition, (int)m_HitRender);
			break;
		case EDirection::RIGHT:
			m_pComponent->PlayAnimGetRow("WINDLEAF_WALK_RIGHT", _hDC, m_tPosition, (int)m_HitRender);
			break;
		default:
			break;
		}
		break;
	case EWindLeafState::MOVE:
		switch (m_eDir)
		{
		case EDirection::UP:
			m_pComponent->PlayAnimGetRow("WINDLEAF_WALK_UP", _hDC, m_tPosition, (int)m_HitRender);
			break;
		case EDirection::DOWN:
			m_pComponent->PlayAnimGetRow("WINDLEAF_WALK_DOWN", _hDC, m_tPosition, (int)m_HitRender);
			break;
		case EDirection::LEFT:
			m_pComponent->PlayAnimGetRow("WINDLEAF_WALK_LEFT", _hDC, m_tPosition, (int)m_HitRender);
			break;
		case EDirection::RIGHT:
			m_pComponent->PlayAnimGetRow("WINDLEAF_WALK_RIGHT", _hDC, m_tPosition, (int)m_HitRender);
			break;
		default:
			break;
		}

		break;
	case EWindLeafState::ATTACK:
		switch (m_eDir)
		{
		case EDirection::UP:
			if (m_pComponent->PlayAnimGetRow("WINDLEAF_ATK_UP", _hDC, m_tPosition, (int)m_HitRender)) {
				m_CurrentState = EWindLeafState::IDLE;
			}
			break;
		case EDirection::DOWN:
			if (m_pComponent->PlayAnimGetRow("WINDLEAF_ATK_DOWN", _hDC, m_tPosition, (int)m_HitRender)) {
				m_CurrentState = EWindLeafState::IDLE;
			}
			break;
		case EDirection::LEFT:			
			if (m_pComponent->PlayAnimGetRow("WINDLEAF_ATK_LEFT", _hDC, m_tPosition, (int)m_HitRender)) {
				m_CurrentState = EWindLeafState::IDLE;
			}
			break;
		case EDirection::RIGHT:
			if (m_pComponent->PlayAnimGetRow("WINDLEAF_ATK_RIGHT", _hDC, m_tPosition, (int)m_HitRender)) {
				m_CurrentState = EWindLeafState::IDLE;
			}
			break;
		default:
			break;
		}
		break;

	default:
		break;
	}
	
}

void CWindLeaf::LateUpdate()
{
	CheckHitTime();
	ShootBullet();
}

void CWindLeaf::Release()
{
}

void CWindLeaf::OnAttacked(int _damage)
{
	CMonster::OnAttacked(_damage);
	CSoundMgr::Get_Instance()->StopSound(DAMAGE_EFFECT);
	CSoundMgr::Get_Instance()->PlaySound(L"forest_dungeon_enemy_hit.wav", DAMAGE_EFFECT, 1.f);
}

void CWindLeaf::Moving()
{
	if (m_CurrentState == EWindLeafState::ATTACK) {
		return;
	}

	float distanceX = fabs(m_pPlayerCopy->GetPosition().m_fX - m_tPosition.m_fX);
	float distanceY = fabs(m_pPlayerCopy->GetPosition().m_fY - m_tPosition.m_fY);

	if (distanceX > 20 && distanceY > 20) {
		if (distanceX < distanceY) {
			if (m_pPlayerCopy->GetPosition().m_fX > m_tPosition.m_fX) {
				m_eDir = EDirection::RIGHT;
				m_tPosition.m_fX += m_fSpeed;
			}
			else if(m_pPlayerCopy->GetPosition().m_fX < m_tPosition.m_fX){
				m_eDir = EDirection::LEFT;
				m_tPosition.m_fX -= m_fSpeed;
			}
		}
		else {
			if (m_pPlayerCopy->GetPosition().m_fY > m_tPosition.m_fY) {
				m_eDir = EDirection::RIGHT;
				m_tPosition.m_fY += m_fSpeed;
			}
			else if (m_pPlayerCopy->GetPosition().m_fY < m_tPosition.m_fY) {
				m_eDir = EDirection::LEFT;
				m_tPosition.m_fY -= m_fSpeed;
			}

		}

	}
	else {
		PlayerDetect();
		m_CurrentState = EWindLeafState::ATTACK;
		m_dwAttackTime = GetTickCount64();
	}
}

void CWindLeaf::ShootBullet()
{

	if (m_dwAttackTime + 1500 < (DWORD)GetTickCount64() && EWindLeafState::ATTACK == m_CurrentState) {
		CObj* newBullet = new CBasicProj;
		newBullet->SetPosition(m_tPosition);
		dynamic_cast<CBasicProj*>(newBullet)->SetAnimKey(m_strKeyName);
		dynamic_cast<CBasicProj*>(newBullet)->SetDirection(m_eDir);
		dynamic_cast<CBasicProj*>(newBullet)->SetDamage(20);
		newBullet->Initialize();
		m_pProjList->push_back(newBullet);
		m_dwAttackTime = (DWORD)GetTickCount64();
	}



}
