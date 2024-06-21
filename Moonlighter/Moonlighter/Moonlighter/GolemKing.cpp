#include "GolemKing.h"
#include"UIMgr.h"
#include"GolemPunch.h"
#include"Rocks.h"
#include"SlimeBullet.h"
#include"Camera.h"
#include"SoundMgr.h"
#include"Effect.h"


CGolemKing::CGolemKing() : m_ObjListCopy(nullptr) , m_PunchHand(nullptr)
{
}

CGolemKing::~CGolemKing()
{
}

void CGolemKing::Initialize()
{
	CMonster::Initialize();
	m_tSize = { 250.f,150.f };
	m_iHp = 200;
	CUIMgr::GetInstance()->SetBossMaxHp(200);
	m_dwAttackTime = (DWORD)GetTickCount64();
	m_eBossState = INIT;
	m_PunchPos = { m_tPosition.m_fX, m_tPosition.m_fY + m_tSize.m_fY * 0.5f };
	dwPunchTime = GetTickCount64()+5000;
	CUIMgr::GetInstance()->ScrollOn();

	CSoundMgr::Get_Instance()->StopSound(BOSS_EFFECT);
	CSoundMgr::Get_Instance()->PlaySound(L"golem_dungeon_king_golem_awake.wav", BOSS_EFFECT, 1.f);
}

void CGolemKing::Update()
{

	if (INIT == m_eBossState) {
		return;
	}

	if (true != m_bIsOnAtk && m_eBossState == IDLE) {
		if (m_dwAttackTime + 4000 <= (DWORD)GetTickCount64()) {
			++m_iAtkNum;

			if (m_iAtkNum > 3) {
				m_iAtkNum = 1;
			}
			if (1 == m_iAtkNum) {
				m_eBossState = ATTACK1;
				CSoundMgr::Get_Instance()->StopSound(BOSS_EFFECT);
				CSoundMgr::Get_Instance()->PlaySound(L"golem_dungeon_king_golem_handcrash_prepare.wav", BOSS_EFFECT, 1.f);
			}
			else if (2 == m_iAtkNum) {
				m_eBossState = ATTACK2;
				CSoundMgr::Get_Instance()->StopSound(BOSS_EFFECT);
				CSoundMgr::Get_Instance()->PlaySound(L"golem_dungeon_king_golem_avalanch_pre.wav", BOSS_EFFECT, 1.5f);
			}
			else if (3 == m_iAtkNum) {
				m_eBossState = ATTACK3;
				CSoundMgr::Get_Instance()->StopSound(BOSS_EFFECT);
				CSoundMgr::Get_Instance()->PlaySound(L"golem_dungeon_king_golem_slimearm_prepare.wav", BOSS_EFFECT, 1.f);

			}
			m_dwAttackTime = (DWORD)GetTickCount64();
			m_bIsOnAtk = true;
		}
	}

	if (m_bIsNoArm == true && m_bIsAnimFin == false && dwPunchTime+3000<GetTickCount64() && m_PunchHand == nullptr) {
		PunchAtk();
		m_fShadowSize = 0.05f;
	}

	if (m_bIsNoArm == true && m_bIsAnimFin == false &&  m_PunchHand == nullptr) {
		SetShadowPosition();
	}

}

void CGolemKing::Render(HDC _hDC)
{	
	CheckHitRender();
	m_pComponent->RenderImage("BOSS1_CRACK", _hDC, { m_tPosition.m_fX - 30.f, m_tPosition.m_fY});

	//공격1 준비
	if (ATTACK1 == m_eBossState && m_bIsNoArm == false)
	{
		if (m_pComponent->PlayAnimGetRow("BOSS1_ATTACK1", _hDC, m_tPosition, (int)m_HitRender)) {
			m_bIsAnimFin = true;
		}
	}
	//공격1 이후 팔X + 실제 공격중
	else if (ATTACK1 == m_eBossState && m_bIsNoArm == true) {

		m_pComponent->PlayAnimGetRow("BOSS1_IDLE_NOARM", _hDC, m_tPosition, (int)m_HitRender);

		if (m_PunchHand == nullptr) {
			CMyResource* CurRes = CResourceMgr::GetInstance()->FindRes("PUNCHSHADOW");

			if (CurRes) {
				AnimInfo tempInfo = CurRes->GetResInfo();
				Vector RenderVec = CCamera::GetInstance()->GetRenderPos({(m_PunchPos.m_fX) - (tempInfo.iSizeX * m_fShadowSize * 0.5f) ,(m_PunchPos.m_fY) - (tempInfo.iSizeY * m_fShadowSize * 0.5f)});
				GdiTransparentBlt(_hDC,

					static_cast<int>(RenderVec.m_fX),
					static_cast<int>(RenderVec.m_fY),
					tempInfo.iSizeX * m_fShadowSize,
					tempInfo.iSizeY * m_fShadowSize,
					CurRes->GetMemDC(),
					tempInfo.iFrameStart * tempInfo.iSizeX,
					0,
					tempInfo.iSizeX,
					tempInfo.iSizeY,
					RGB(52, 52, 52));
			}
			m_fShadowSize += 0.005f;

			if (m_fShadowSize > 1.f) {
				m_fShadowSize = 1.f;
			}
		}
	}
	//공격2 준비중
	else if (ATTACK2 == m_eBossState && m_bIsAnimFin == false) {
		if (m_pComponent->PlayAnimGetRow("BOSS1_ROCKSPAWN", _hDC, m_tPosition, (int)m_HitRender)) {
			m_bIsAnimFin = true;
			CCamera::GetInstance()->Vibration(20.f, 0.4f, 40.f, EDirection::UP);
		}
	}
	//기본상태
	else if (IDLE == m_eBossState && m_bIsNoArm == false)
	{
		m_pComponent->PlayAnimGetRow("BOSS1_IDLE", _hDC, m_tPosition, (int)m_HitRender);
	}
	//공격1 이후 팔 회복
	else if (RECOVER == m_eBossState) {
		if (m_pComponent->PlayAnimGetRow("BOSS1_RECOVERARM", _hDC, m_tPosition,(int)m_HitRender)) {
			m_eBossState = IDLE;
			m_bIsOnAtk = false;
			m_bIsAnimFin = false;
			m_dwAttackTime = GetTickCount64();
			m_iPunchCount = 0;
		}

	}
	//공격3 준비 애니메이션
	else if (ATTACK3 == m_eBossState && m_bIsAnimFin == false) {
		if (m_pComponent->PlayAnimGetRow("BOSS1_ATTACK3_PREPARE", _hDC, { m_tPosition.m_fX+10.f, m_tPosition.m_fY - 80.f}, (int)m_HitRender)) {
			m_bIsAnimFin = true;
			m_dwAttackTime = (DWORD)GetTickCount64();
		}
	}
	//공격3 진행중
	else if (ATTACK3 == m_eBossState && m_bIsAnimFin == true && m_bIsOnAtk == true) {
		if (m_pComponent->PlayAnimGetRow("BOSS1_ATTACK3_AIM", _hDC, { m_tPosition.m_fX + 10.f, m_tPosition.m_fY - 80.f }, (int)m_HitRender)) {
			m_bIsOnAtk = false;
		}

		m_pComponent->RenderImage("BOSS1_STICKYARM", _hDC, { m_tPosition.m_fX - 130.f , m_tPosition.m_fY - 40.f });
	}
	//공격3 종료
	else if ((ATTACK3 == m_eBossState && m_bIsAnimFin == true) && m_bIsOnAtk == false) {
		if ((m_pComponent->PlayAnimGetRow("BOSS1_ATTACK3_END", _hDC, { m_tPosition.m_fX + 10.f, m_tPosition.m_fY - 80.f }, (int)m_HitRender))) {
			m_eBossState = IDLE;
			m_bIsAnimFin = false;
		}
	}
	else if (DEAD == m_eBossState) {
		if (m_pComponent->PlayAnim("BOSS1_DEAD", _hDC, m_tPosition)) {
			CUIMgr::GetInstance()->SetBossMaxHp(0);
			m_bIsDead = true;
		}
	}
	else if (INIT == m_eBossState) {
		if (m_pComponent->PlayAnim("BOSS1_WAKEUP", _hDC, m_tPosition)) {
			CCamera::GetInstance()->SetTarget(m_ObjListCopy[(unsigned int)EObjectType::PLAYER].front());
			m_eBossState = IDLE;
			m_bIsOnAtk = false;
		}
	}

}

void CGolemKing::LateUpdate()
{
	CheckHitTime();

	//공격시작
	switch (m_eBossState)
	{
	case IDLE:
		break;
	case ATTACK1: // 펀치 공격
		if (true == m_bIsAnimFin && true == m_bIsOnAtk) {
			m_bIsAnimFin = false;
			m_bIsNoArm = true;
			dwPunchTime = (DWORD)GetTickCount64();
		} 

		if (m_PunchHand != nullptr) {
			if (dynamic_cast<CGolemPunch*>(m_PunchHand)->GetisAtkDone()) {
				m_PunchHand = nullptr;
				++m_iPunchCount;
				dwPunchTime = GetTickCount64();
				if (3 == m_iPunchCount) {
					m_bIsNoArm = false;
					m_eBossState = RECOVER;
				}
			}
		}
		break;
	case ATTACK2: //바위소환 공격
		if (m_bIsAnimFin) {
			SpawnRock();
			m_eBossState = IDLE;
			m_bIsOnAtk = false;
			m_bIsAnimFin = false;

		}
		break;
	case ATTACK3:
		
		if (m_bIsAnimFin == true && m_bIsOnAtk == true) {
			ShootingSlime();
		}

		break;
	case DEAD:
		break;
	default:
		break;
	}
}

void CGolemKing::Release()
{
}

void CGolemKing::OnAttacked(int _damage)
{

	if (DEAD == m_eBossState) {
		return;
	}

	CObj* hitEffect = new CEffect("EFFECT_HIT", 300, EDirection::UP);
	int dif = rand() % 100;

	if (rand() % 100 > 50) {
		dif *= -1;
	}

	hitEffect->SetPosition({ m_tPosition.m_fX + (float)dif , m_tPosition.m_fY + m_tSize.m_fY * 0.5f });
	hitEffect->Initialize();
	m_ObjListCopy[static_cast<unsigned int>(EObjectType::EFFECT)].push_back(hitEffect);

	m_IsOnHit = true;
	m_iHp -= _damage;
	m_HitTime = (DWORD)GetTickCount64();

	CSoundMgr::Get_Instance()->StopSound(SOUND_EFFECT);
	CSoundMgr::Get_Instance()->PlaySound(L"golem_dungeon_king_golem_hit.wav", SOUND_EFFECT, 1.f);

	if (m_iHp <= 0) {
		m_iHp = 0;
		m_bIsNoArm = false;
		m_eBossState = DEAD;
	}

	CUIMgr::GetInstance()->SetBossHp(m_iHp);
}

void CGolemKing::OnCollide(CObj* _pObj)
{
}

void CGolemKing::SetShadowPosition()
{
	CObj* m_pTarget = m_ObjListCopy[static_cast<unsigned int>(EObjectType::PLAYER)].front();

	float m_distanceX = m_pTarget->GetPosition().m_fX - m_PunchPos.m_fX;
	float m_distanceY = m_pTarget->GetPosition().m_fY - m_PunchPos.m_fY;

	float fDistance = sqrtf(m_distanceX * m_distanceX + m_distanceY * m_distanceY);
	float m_fAngle = acosf(m_distanceX / fDistance);

	if (m_pTarget->GetPosition().m_fY > m_PunchPos.m_fY) {
		m_fAngle *= -1.f;
	}

	m_PunchPos.m_fX += (5.f * cosf(m_fAngle));
	m_PunchPos.m_fY -= (5.f * sinf(m_fAngle));
}

void CGolemKing::PunchAtk()
{
	CObj* punchProj = new CGolemPunch;
	punchProj->Initialize();
	dynamic_cast<CGolemPunch*>(punchProj)->SetTargetPos(m_PunchPos);
	dynamic_cast<CGolemPunch*>(punchProj)->SetEffectList(&m_ObjListCopy[static_cast<unsigned int>(EObjectType::OBSTACLE)]);
	m_ObjListCopy[static_cast<unsigned int>(EObjectType::MON_PROJ)].push_back(punchProj);

	m_PunchHand = punchProj;
}

void CGolemKing::SpawnRock()
{
	float m_fAngle = 0.f;
	float m_fDistance = 300.f;
	Vector tempVec = { 0.f, 0.f };

	for (int i = 0; i < 19; ++i) {   
		tempVec.m_fX = m_tPosition.m_fX+ m_fDistance * cosf(m_fAngle * (PI / 180.f));
		tempVec.m_fY = m_tPosition.m_fY + m_fDistance * sinf(m_fAngle * (PI / 180.f));

		CObj* tempRock = new CRocks;
		dynamic_cast<CRocks*>(tempRock)->SetTargetPos({ tempVec.m_fX,tempVec.m_fY  });
		dynamic_cast<CRocks*>(tempRock)->SetEffectList(&m_ObjListCopy[static_cast<unsigned int>(EObjectType::EFFECT)]);
		tempRock->Initialize();
		m_ObjListCopy[static_cast<unsigned int>(EObjectType::OBSTACLE)].push_back(tempRock);
		m_fAngle += 10.f;

	}
	 
	m_fAngle = 0.f;
	m_fDistance = 700.f;
	tempVec = { 0.f, 0.f };

	for (int i = 0; i < 37; ++i) {
		tempVec.m_fX = m_tPosition.m_fX + m_fDistance * cosf(m_fAngle * (PI / 180.f));
		tempVec.m_fY = m_tPosition.m_fY + m_fDistance * sinf(m_fAngle * (PI / 180.f));

		CObj* tempRock = new CRocks;
		dynamic_cast<CRocks*>(tempRock)->SetTargetPos({ tempVec.m_fX,tempVec.m_fY });
		tempRock->Initialize();
		dynamic_cast<CRocks*>(tempRock)->SetEffectList(&m_ObjListCopy[static_cast<unsigned int>(EObjectType::EFFECT)]);
		m_ObjListCopy[static_cast<unsigned int>(EObjectType::OBSTACLE)].push_back(tempRock);
		m_fAngle += 5.f;
	}

}

void CGolemKing::ShootingSlime()
{
	if (m_dwAttackTime + 500 > (DWORD)GetTickCount64()) {
		return;
	}

	float fAngle = 0.f;
	for (int i = 0; i < 10; ++i) {
		CObj* newBullet = new CSlimeBullet;
		newBullet->SetPosition({ m_tPosition.m_fX - 130.f, m_tPosition.m_fY -20.f });

		dynamic_cast<CSlimeBullet*>(newBullet)->SetAngle(fAngle);
		newBullet->Initialize();
		m_ObjListCopy[static_cast<unsigned int>(EObjectType::MON_PROJ)].push_back(newBullet);
		fAngle += 20.f;
	}

	m_dwAttackTime = GetTickCount64();
}
