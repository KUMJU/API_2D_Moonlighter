#include "NPC.h"
#include"KeyMgr.h"
#include"UIMgr.h"
#include"GameMgr.h"

CNPC::CNPC() : m_pPlayerCopy(nullptr)
{
}

CNPC::~CNPC()
{
	Release();
}

void CNPC::Initialize()
{
	CTile::Initialize();
	m_iRendNum = GAMEOBJECT;
	m_pPlayerCopy = CGameMgr::GetInstance()->GetPlayer();
	m_eTileType = ETileType::NPC;
}

void CNPC::Update()
{
	if (0 == m_iNpcNum) {
		DetectedPlayer();
		KeyInput();
	}
	else if (2 == m_iNpcNum) {
		DetectedPlayer();
	}
}

void CNPC::Render(HDC _hDC)
{
	m_pComponent->PlayAnim(m_strImgKey, _hDC, m_tPosition);

	if (true == m_IsPromptOn && 0 == m_iNpcNum) {
		m_pComponent->RenderImage("UI_SHOP_BUBBLE", _hDC, { m_tPosition.m_fX, m_tPosition.m_fY - 80.f });
	}
	else if (true == m_IsPromptOn && 2 == m_iNpcNum) {
		m_pComponent->RenderImage("PIANO_BUBBLE", _hDC, { m_tPosition.m_fX, m_tPosition.m_fY - 80.f });

	}

}

void CNPC::LateUpdate()
{
}

void CNPC::Release()
{
}

void CNPC::OnCollide(CObj* _pObj)
{
}

void CNPC::KeyInput()
{
	if (CKeyMgr::GetInstance()->Key_Down('A') && true == m_IsPromptOn) {
		CUIMgr::GetInstance()->ShopSwitch();
	}

}

void CNPC::DetectedPlayer()
{

	if (!m_pPlayerCopy) {
		m_pPlayerCopy = CGameMgr::GetInstance()->GetPlayer();
	}
	else {
		Vector tPlayerPos = m_pPlayerCopy->GetPosition();
		Vector DirVec = { m_tPosition.m_fX - tPlayerPos.m_fX ,
							m_tPosition.m_fY - tPlayerPos.m_fY };
		if (DirVec.Length() < 90 ) {
			m_IsPromptOn = true;
		}
		else {
			m_IsPromptOn = false;
		}
	}

}
