#include "DisplayItem.h"
#include "GameMgr.h"
#include"KeyMgr.h"
#include"UIMgr.h"
#include"Player.h"

CDisplayItem::CDisplayItem() : m_pPlayerCopy(nullptr)
{
}

CDisplayItem::~CDisplayItem()
{
	Release();

}

void CDisplayItem::Initialize()
{
	CTile::Initialize();
	m_iRendNum = GAMEOBJECT;
	m_pPlayerCopy = CGameMgr::GetInstance()->GetPlayer();
	m_eTileType = ETileType::COLLISION_DECO;


	if (0 == m_iItemNum) {
		m_iPrice = 50;
	}
	else if (1 == m_iItemNum) {
		m_iPrice = 200;
	}
	else if (2 == m_iItemNum) {
		m_iPrice = 100;
	}

}

void CDisplayItem::Update()
{
	DetectedPlayer();
	KeyInput();

}

void CDisplayItem::Render(HDC _hDC)
{
	m_pComponent->RenderImageGetRow("HIDDEN_ITEM", _hDC, m_tPosition, m_iItemNum);

	if (true == m_IsPromptOn) {
		m_pComponent->RenderImageGetRow("ITEM_BUBLE", _hDC, { m_tPosition.m_fX, m_tPosition.m_fY - 80.f }, m_iItemNum);
	}

}

void CDisplayItem::LateUpdate()
{
}

void CDisplayItem::Release()
{
}

void CDisplayItem::OnCollide(CObj* _pObj)
{
}

void CDisplayItem::KeyInput()
{
	if (true == m_IsPromptOn) {
		if(CKeyMgr::GetInstance()->Key_Down('A'))
			ItemActive();
	}
}

void CDisplayItem::DetectedPlayer()
{

	if (!m_pPlayerCopy) {
		m_pPlayerCopy = CGameMgr::GetInstance()->GetPlayer();
	}
	else {
		Vector tPlayerPos = m_pPlayerCopy->GetPosition();
		Vector DirVec = { m_tPosition.m_fX - tPlayerPos.m_fX ,
							m_tPosition.m_fY - tPlayerPos.m_fY };
		if (DirVec.Length() < 65) {
			m_IsPromptOn = true;
		}
		else {
			m_IsPromptOn = false;
		}
	}
}

void CDisplayItem::ItemActive()
{

	if (dynamic_cast<CPlayer*>(m_pPlayerCopy)->GetGold() >= m_iPrice) {
		dynamic_cast<CPlayer*>(m_pPlayerCopy)->SetGold(m_iPrice * -1);

		CSoundMgr::Get_Instance()->StopSound(SOUND_EFFECT2);
		CSoundMgr::Get_Instance()->PlaySound(L"shop_item_sold.wav", SOUND_EFFECT2, 1.5f);

		if (0 == m_iItemNum) {
			dynamic_cast<CPlayer*>(m_pPlayerCopy)->HealingHP(40);
			CSoundMgr::Get_Instance()->StopSound(PLAYER_EFFECT);
			CSoundMgr::Get_Instance()->PlaySound(L"sfx_item_food.wav", PLAYER_EFFECT, 1.5f);
		}
		else if (1 == m_iItemNum) {
			dynamic_cast<CPlayer*>(m_pPlayerCopy)->GetSkill();
			CSoundMgr::Get_Instance()->StopSound(PLAYER_EFFECT);
			CSoundMgr::Get_Instance()->PlaySound(L"mus_create.wav", PLAYER_EFFECT, 1.0f);

		}
		else if (2 == m_iItemNum) {
			dynamic_cast<CPlayer*>(m_pPlayerCopy)->SetMaxHp(20);
			CSoundMgr::Get_Instance()->StopSound(PLAYER_EFFECT);
			CSoundMgr::Get_Instance()->PlaySound(L"will_heals.wav", PLAYER_EFFECT, 1.5f);
		}

		m_bIsDead = true;

	}
	else {

	}

}
