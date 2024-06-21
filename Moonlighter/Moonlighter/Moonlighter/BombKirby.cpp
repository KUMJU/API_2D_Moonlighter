#include "BombKirby.h"
#include"GameMgr.h"
#include"SoundMgr.h"
#include"Bomb.h"

CBombKirby::CBombKirby() : m_pPlayerCopy(nullptr)
{
}

CBombKirby::~CBombKirby()
{
}

void CBombKirby::Initialize()
{
	CTile::Initialize();
	m_pPlayerCopy = CGameMgr::GetInstance()->GetPlayer();
	m_strImgKey = "BOMB_KIRBY";
	m_eTileType = ETileType::DECO;
	m_iRendNum = GAMEOBJECT;

	CSoundMgr::Get_Instance()->StopSound(PLAYER_EFFECT);
	CSoundMgr::Get_Instance()->PlaySound(L"kirby-uee.wav", PLAYER_EFFECT, 1.f);
	m_dwCreateTime = GetTickCount64();
}


void CBombKirby::Update()
{
}

void CBombKirby::Render(HDC _hDC)
{

	if (m_pComponent->PlayAnim(m_strImgKey, _hDC, m_tPosition)) {
		m_bIsDead = true;
	}

}

void CBombKirby::LateUpdate()
{
	if (m_IsBombCreate) {
		return;
	}

	if (m_dwCreateTime + 400 <= (DWORD)GetTickCount64()) {

		CObj* newBomb = new CBomb;
		newBomb->SetPosition({ m_tPosition.m_fX + 200.f,m_tPosition.m_fY });
		newBomb->Initialize();
		m_ProjList->push_back(newBomb);
		m_IsBombCreate = true;
	}

}

void CBombKirby::Release()
{
}

void CBombKirby::OnCollide(CObj* _pObj)
{
}
