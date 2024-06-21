#include "Rocks.h"
#include"SoundMgr.h"
#include"Effect.h"

CRocks::CRocks() : m_dwTime(0),m_iImgNum(0), m_bIsDrop(false),m_EffectList(nullptr)
{
}

CRocks::~CRocks()
{
}

void CRocks::Initialize()
{
	m_eObjType = EObjectType::OBSTACLE;
	m_pComponent = new CComponent;
	m_strImgKey = "BOSS1_ROCK";
	m_eTileType = ETileType::DECO;
	m_iRendNum = GAMEOBJECT;

	m_iImgNum = rand() % 6;
	m_dwTime = (DWORD)GetTickCount64();

	m_tPosition = { m_tTarget.m_fX, m_tTarget.m_fY - 500.f };
	m_tSize = { 40.f,40.f };

}

void CRocks::Update()
{
	if (m_bIsDrop) {
		if (m_tPosition.m_fY < m_tTarget.m_fY) {
			m_tPosition.m_fY += 30.f;
			if (m_tPosition.m_fY >= m_tTarget.m_fY) {
				m_tPosition.m_fY = m_tTarget.m_fY;
				m_eTileType = ETileType::ROCK;
			}
		}
	}

}

void CRocks::Render(HDC _hDC)
{

	if (m_bIsDrop) {

		m_pComponent->RenderImage("BOSS1_ROCK", _hDC, m_tPosition);

	}
	else {
		m_pComponent->RenderImage("PUNCHSHADOW", _hDC, m_tTarget);
	}

}

void CRocks::LateUpdate()
{
	if (m_bIsDrop) {
		if (m_dwTime + 20000 <= (DWORD)GetTickCount64()) {
			m_bIsDead = true;
			CSoundMgr::Get_Instance()->StopSound(MONSTER_EFFECT);
			CSoundMgr::Get_Instance()->PlaySound(L"rock_breakable.wav", MONSTER_EFFECT, 1.f);


			CObj* newEffect = new CEffect("EFFECT_ROCK", 900, EDirection::UP);
			newEffect->SetPosition(m_tPosition);
			newEffect->Initialize();
			m_EffectList->push_back(newEffect);
		}
	}
	else {
		if (m_dwTime + 1000 <= (DWORD)GetTickCount64()) {
			m_bIsDrop = true;
			m_dwTime = (DWORD)GetTickCount64();
		}
	}
}

void CRocks::Release()
{
}

void CRocks::OnCollide(CObj* _pObj)
{
	++m_iHitCount;
	CSoundMgr::Get_Instance()->StopSound(MONSTER_EFFECT);
	CSoundMgr::Get_Instance()->PlaySound(L"golem_dungeon_king_golem_hit.wav", MONSTER_EFFECT, 1.f);

	if (2 == m_iHitCount) {
		m_bIsDead = true;
		CSoundMgr::Get_Instance()->StopSound(MONSTER_EFFECT);
		CSoundMgr::Get_Instance()->PlaySound(L"rock_breakable.wav", MONSTER_EFFECT, 1.f);
		

		CObj* newEffect = new CEffect("EFFECT_ROCK",900,EDirection::UP);
		newEffect->SetPosition(m_tPosition);
		newEffect->Initialize();
		m_EffectList->push_back(newEffect);
	}
}
