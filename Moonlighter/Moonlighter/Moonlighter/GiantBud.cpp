#include "GiantBud.h"
#include"UIMgr.h"
#include"SeedProj.h"
#include"Camera.h"
#include"TentacleRoot.h"
#include"Cutting.h"
#include"TimeMgr.h"

CGiantBud::CGiantBud() : 
	m_ObjListCopy(nullptr) , 
	m_eBossState(BOSS2_IDLE) , 
	m_dwAtkTime(0) , 
	m_dWSkillTime(0)
{
}

CGiantBud::~CGiantBud()
{
}

void CGiantBud::Initialize()
{
	CMonster::Initialize();
	m_tSize = { 300.f,200.f };
	m_iHp = 300;
	CUIMgr::GetInstance()->SetBossMaxHp(300);
	m_fSpeed = 2.f;
	m_eBossState = BOSS2_INIT;
	m_dwAtkTime = (DWORD)GetTickCount64();
	m_dWSkillTime = (DWORD)GetTickCount64();

	m_AnimVec->push_back("BOSS_BUD_WAKEUP1");
	m_AnimVec->push_back("BOSS_BUD_WAKEUP2");
	m_AnimVec->push_back("BOSS_BUD_WAKEUP3");
	m_AnimVec->push_back("BOSS_BUD_WAKEUP4");
	
	CSoundMgr::Get_Instance()->StopSound(BOSS_EFFECT);
	CSoundMgr::Get_Instance()->PlaySound(L"forest_dungeon_boss_wakeup.wav", BOSS_EFFECT, 1.f);

	CUIMgr::GetInstance()->ScrollOn();

	
}

void CGiantBud::Update()
{

	if (BOSS2_ATTACK3 != m_eBossState && BOSS2_ATTACK4!= m_eBossState &&
		BOSS2_INIT != m_eBossState && BOSS2_DEAD != m_eBossState) {
		FollowPlayer();
	}

	if (BOSS2_IDLE == m_eBossState && m_dwAtkTime + 5000 < (DWORD)GetTickCount64()) {

		++m_PrevActNum;

		if (1 == m_PrevActNum) {
			m_eBossState = BOSS2_ATTACK1;

		}
		else if (2 == m_PrevActNum) {
			m_eBossState = BOSS2_ATTACK2;

		}
		else if (3 == m_PrevActNum) {
			m_eBossState = BOSS2_ATTACK3;

		}
		else if (4 == m_PrevActNum) {
			m_eBossState = BOSS2_ATTACK4;

		}
		m_dwAtkTime = GetTickCount64();
	}

}

void CGiantBud::Render(HDC _hDC)
{
	CheckHitRender();

	switch (m_eBossState)
	{
	case BOSS2_INIT:
		if (m_pComponent->PlayAnimIndependentRow(m_AnimVec->at(m_ActCount), _hDC, {m_tPosition.m_fX, m_tPosition.m_fY- 100.f}, m_iInitAnim)) {
			++m_iInitAnim;

			if (2 == m_iInitAnim) {
				++m_ActCount;
				m_iInitAnim = 0;
				
				if(4 == m_ActCount) {
					m_eBossState = BOSS2_IDLE;
					CCamera::GetInstance()->SetTarget(CGameMgr::GetInstance()->GetPlayer());
					m_iInitAnim = 0;
				}
			}
		}
		break;
	case BOSS2_IDLE:
		m_pComponent->PlayAnimIndependentRow("BOSS2_TENTACLE_IDLE", _hDC, { m_tPosition.m_fX, m_tPosition.m_fY + 100.f }, (int)m_HitRender);
		m_pComponent->PlayAnimIndependentRow("BOSS2_BUD_IDLE", _hDC, { m_tPosition.m_fX, m_tPosition.m_fY - 120.f }, (int)m_HitRender);
		break;

	case BOSS2_ATTACK1:
		m_pComponent->PlayAnimIndependentRow("BOSS2_TENTACLE_IDLE", _hDC, { m_tPosition.m_fX, m_tPosition.m_fY + 100.f }, (int)m_HitRender);

		if (m_IsAnimFin == true) {
			m_pComponent->PlayAnimIndependentRow("BOSS2_BUD_IDLE", _hDC, { m_tPosition.m_fX, m_tPosition.m_fY - 120.f }, (int)m_HitRender);
		}
		else {
			if (m_pComponent->PlayAnimIndependentRow("BOSS2_BUD_SHOOTING", _hDC, { m_tPosition.m_fX - 10.f, m_tPosition.m_fY - 120.f }, (int)m_HitRender)) {
				m_IsAnimFin = true;
			}
		}

		break;
	case BOSS2_ATTACK2:
		m_pComponent->PlayAnimIndependentRow("BOSS2_TENTACLE_IDLE", _hDC, { m_tPosition.m_fX, m_tPosition.m_fY+100.f }, (int)m_HitRender);
		m_pComponent->PlayAnimIndependentRow("BOSS2_BUD_POT", _hDC, { m_tPosition.m_fX, m_tPosition.m_fY - 120.f }, (int)m_HitRender);

		break;
	case BOSS2_ATTACK3:
		if (m_pComponent->PlayAnimIndependentRow("BOSS2_TENTACLE_ATTACK", _hDC, { m_tPosition.m_fX, m_tPosition.m_fY + 100.f }, (int)m_HitRender)) {
			m_eBossState = BOSS2_IDLE;
		}
		m_pComponent->PlayAnimIndependentRow("BOSS2_BUD_IDLE", _hDC, { m_tPosition.m_fX, m_tPosition.m_fY - 120.f }, (int)m_HitRender);

		break;
	case BOSS2_ATTACK4:

		if (false == m_IsAnimFin) {
			if (m_pComponent->PlayAnimIndependentRow("BOSS2_JUMP1", _hDC, { m_tPosition.m_fX, m_tPosition.m_fY - 120.f }, (int)m_HitRender)) {
				m_IsAnimFin = true; 
				CalCulateSpeed();
			}
			m_pComponent->PlayAnimIndependentRow("BUD_JUMP1", _hDC, { m_tPosition.m_fX, m_tPosition.m_fY - 170.f }, (int)m_HitRender);

		}
		else {

			if (true == m_IsJumpFin) {
				if (m_pComponent->PlayAnimIndependentRow("BOSS2_JUMP3", _hDC, { m_tPosition.m_fX, m_tPosition.m_fY  }, (int)m_HitRender)) {
					
					m_dwAtkTime = GetTickCount64();
					m_eBossState = BOSS2_IDLE;
				}
				m_pComponent->PlayAnimIndependentRow("BUD_JUMP3", _hDC, { m_tPosition.m_fX, m_tPosition.m_fY  }, (int)m_HitRender);
			}
			else {
				if (m_pComponent->PlayAnimIndependentRow("BOSS2_JUMP2", _hDC, { m_tPosition.m_fX, m_tPosition.m_fY + 100.f }, (int)m_HitRender)) {
					m_IsJumpFin = true;
					CCamera::GetInstance()->Vibration(20.f, 1.f, 40.f, EDirection::UP);
					CSoundMgr::Get_Instance()->StopSound(BOSS_EFFECT);
					CSoundMgr::Get_Instance()->PlaySound(L"forest_dungeon_boss_land.wav", BOSS_EFFECT, 1.f);

				}
				m_pComponent->PlayAnimIndependentRow("BUD_JUMP2", _hDC, { m_tPosition.m_fX, m_tPosition.m_fY - 150.f }, (int)m_HitRender);

			}
		}

		break;
	case BOSS2_DEAD:


		m_pComponent->PlayAnimIndependentRow("BOSS_TENTACLE_DEAD", _hDC, { m_tPosition.m_fX, m_tPosition.m_fY + 100.f }, m_iInitAnim);
		if (m_pComponent->PlayAnimIndependentRow("BOSS_BUD_DEAD", _hDC, { m_tPosition.m_fX, m_tPosition.m_fY - 180.f }, m_iInitAnim)) {
			if (0 == m_iInitAnim) {
				++m_iInitAnim;
			}
			else if (1 == m_iInitAnim) {
				CUIMgr::GetInstance()->SetBossMaxHp(0);
				m_bIsDead = true;
			}
		}

		break;
	default:
		break;
	}
}

void CGiantBud::LateUpdate()
{

	switch (m_eBossState)
	{
	case BOSS2_IDLE:
		m_IsAnimFin = false;
		m_IsJumpFin = false;
		break;
	case BOSS2_ATTACK1:
		if (m_dWSkillTime + 300 < (DWORD)GetTickCount64() && true == m_IsAnimFin )  {
			ShootingSeed();
			m_dWSkillTime = (DWORD)GetTickCount64();
		}
		break;
	case BOSS2_ATTACK2:
		SpawnCutting();
		m_eBossState = BOSS2_IDLE;
		break;
	case BOSS2_ATTACK3:
		if (m_dWSkillTime + 500 < (DWORD)GetTickCount64()) {
			TentacleAttack();
		}
		break;
	case BOSS2_ATTACK4:
		if (m_IsAnimFin == true && m_IsJumpFin == false) {
			Jumping();
		}
		break;
	case BOSS2_DEAD:
		break;
	default:
		break;
	}

	CMonster::LateUpdate();
}

void CGiantBud::Release()
{
}

void CGiantBud::ShootingSeed()
{
	Vector tempVec = { 0.f, 0.f };
	float m_fDistance = 180.f;

	

	for (int i = 0; i < 4; ++i) {
		tempVec.m_fX = m_tPosition.m_fX + m_fDistance * cosf(m_fAngle * (PI / 180.f));
		tempVec.m_fY = m_tPosition.m_fY - 100.f - m_fDistance * sinf(m_fAngle * (PI / 180.f));

		CObj* newSeed = new CSeedProj;
		newSeed->SetPosition(tempVec);
		dynamic_cast<CSeedProj*>(newSeed)->SetAngle(m_fAngle);
		newSeed->Initialize();
		m_ObjListCopy[static_cast<unsigned int>(EObjectType::MON_PROJ)].push_back(newSeed);
		
		m_fAngle += 90.f;
	}

	CSoundMgr::Get_Instance()->StopSound(BOSS_EFFECT);
	CSoundMgr::Get_Instance()->PlaySound(L"forest_dungeon_boss_shoot.wav", BOSS_EFFECT, 1.f);

	++m_iAtkCount;
	m_fAngle = m_iAtkCount * -10.f;
	m_dWSkillTime = GetTickCount64();

	if (17 == m_iAtkCount) {
		m_iAtkCount = 0;
		m_eBossState = BOSS2_IDLE;
		m_dwAtkTime = GetTickCount64();
	}
}

void CGiantBud::Jumping()
{
	m_tPosition.m_fX += 5;
	m_tPosition = m_tPosition + m_tJumpDirVec * m_fJumpSpeed * CTimeMgr::GetInstance()->GetDS();

}

void CGiantBud::CalCulateSpeed()
{
	CSoundMgr::Get_Instance()->StopSound(BOSS_EFFECT);
	CSoundMgr::Get_Instance()->PlaySound(L"forest_dungeon_boss_jump.wav", BOSS_EFFECT, 1.f);

	Vector targetVec = m_ObjListCopy[static_cast<unsigned int>(EObjectType::PLAYER)].front()->GetPosition();
	m_tJumpDirVec = (targetVec -m_tPosition);
	m_tJumpDirVec.Normalize();
	m_fJumpSpeed = (targetVec - m_tPosition).Length();
}

void CGiantBud::TentacleAttack()
{
	for (int i = 0; i < 3; ++i) {
		int iRandX = rand() % 30;
		int iRandY = rand() % 30;
		Vector newPos = m_ObjListCopy[static_cast<unsigned int>(EObjectType::PLAYER)].front()->GetPosition();

		if (rand() % 100 > 50) {
			iRandX *= -1;
		}

		if (rand() % 100 > 50) {
			iRandY *= -1;
		}

		CObj* tempTentacle = new CTentacleRoot;
		tempTentacle->SetPosition({ newPos.m_fX + (float)iRandX, newPos.m_fY+ (float)iRandY });
		tempTentacle->Initialize();
		m_ObjListCopy[static_cast<unsigned int>(EObjectType::MON_PROJ)].push_back(tempTentacle);
	}
	m_dWSkillTime = GetTickCount64();
	++m_iAtkCount;

	if (3 == m_iAtkCount) {
		m_eBossState = BOSS2_IDLE;
		m_dwAtkTime = GetTickCount64();
		m_iAtkCount = 0;
	}
}

void CGiantBud::SpawnCutting()
{
	CSoundMgr::Get_Instance()->StopSound(BOSS_EFFECT);
	CSoundMgr::Get_Instance()->PlaySound(L"forest_dungeon_boss_cutting_grow.wav", BOSS_EFFECT, 1.f);

	for (int i = 0; i < 4; ++i) {
		int RandPosX = rand() % 1500 + 300;
		int RandPosY = rand() % 900 + 300;

		CObj* netMonster = new CCutting;
		netMonster->SetPosition({ static_cast<float>(RandPosX) , static_cast<float>(RandPosY) });
		dynamic_cast<CMonster*>(netMonster)->SetProjList(&m_ObjListCopy[static_cast<unsigned int>(EObjectType::MON_PROJ)]);
		dynamic_cast<CMonster*>(netMonster)->SetEffectList(&m_ObjListCopy[static_cast<unsigned int>(EObjectType::EFFECT)]);

		netMonster->Initialize();
		m_ObjListCopy[static_cast<unsigned int>(EObjectType::MONSTER)].push_back(netMonster);
	}
}

void CGiantBud::OnAttacked(int _damage)
{

		if (BOSS2_DEAD == m_eBossState) {
			return;
		}

		m_IsOnHit = true;
		m_iHp -= _damage;
		m_HitTime = GetTickCount64();


		CSoundMgr::Get_Instance()->StopSound(SOUND_EFFECT);
		CSoundMgr::Get_Instance()->PlaySound(L"forest_dungeon_enemy_hit.wav", SOUND_EFFECT, 1.f);

		if (m_iHp <= 0) {
			m_iHp = 0;
			m_eBossState = BOSS2_DEAD;
			m_IsOnHit = false;
		}

		CUIMgr::GetInstance()->SetBossHp(m_iHp);
}
