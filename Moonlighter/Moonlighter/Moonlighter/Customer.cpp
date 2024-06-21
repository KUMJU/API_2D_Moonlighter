#include "Customer.h"
#include"Camera.h"
#include"Player.h"
#include"GameMgr.h"
#include"Component.h"
#include"TimeMgr.h"
#include"SoundMgr.h"

CCustomer::CCustomer()
{
}

CCustomer::CCustomer(int _slotNum) : m_iSlotNum(_slotNum), m_pPlayer(nullptr)
{
}

CCustomer::~CCustomer()
{
	Release();
}

void CCustomer::Initialize()
{
	m_TargetPos = { 575.f + 35.f * m_iSlotNum , 370.f };
	m_tSize = { 30.f,30.f };
	m_iRendNum = GAMEOBJECT;
	m_pPlayer = CGameMgr::GetInstance()->GetPlayer();
	m_CreateTime = (DWORD)GetTickCount64();
	m_eCurrentState = CustomerState::IDLE;

	m_pComponent = new CComponent;

	m_fSpeed = ((m_TargetPos - m_tPosition).Length()) / 3;
	m_DirVec = (m_TargetPos - m_tPosition);
	m_DirVec.Normalize();

	m_AnimNum = rand() % 2;

}

void CCustomer::Update()
{
	switch (m_eCurrentState)
	{
	case CustomerState::IDLE:
		m_tPosition +=m_DirVec* m_fSpeed* CTimeMgr::GetInstance()->GetDS();
		m_Time += CTimeMgr::GetInstance()->GetDS();

		if (m_Time > 3.f) {
			m_tPosition = m_TargetPos;
			m_eCurrentState = CustomerState::WALK;
			m_CreateTime = (DWORD)GetTickCount64();
		}

		break;
	case CustomerState::WALK:
		if (m_CreateTime + 5000 < (DWORD)GetTickCount64()) {
			m_eCurrentState = CustomerState::BUY;
		}
		break;
	case CustomerState::BUY:
	
		break;
	case CustomerState::FIN:
		m_tPosition += m_DirVec * m_fSpeed * CTimeMgr::GetInstance()->GetDS();
		m_Time += CTimeMgr::GetInstance()->GetDS();

		if (m_Time > 3.f) {
			m_tPosition = m_TargetPos;
			m_bIsDead = true;
		}
		break;
	case CustomerState::ENUM_END:
		break;
	default:
		break;
	}
	
}

void CCustomer::LateUpdate()
{

}

void CCustomer::Render(HDC _hDC)
{

	switch (m_eCurrentState)
	{
	case CustomerState::IDLE:
		m_pComponent->PlayAnimGetRow("MERCHANT_ANIM",_hDC,m_tPosition, m_AnimNum);
		break;
	case CustomerState::WALK:
		m_pComponent->RenderImageGetRow("MERCHANT_IDLE", _hDC, m_tPosition, m_AnimNum);
		break;
	case CustomerState::BUY:
		m_pComponent->RenderImage("BASE_EMOTION", _hDC, { m_tPosition.m_fX, m_tPosition.m_fY - 100.f });
		if (m_pComponent->PlayAnimGetRow("SHOP_EMOTION", _hDC, { m_tPosition.m_fX, m_tPosition.m_fY - 100.f }, m_iEmotion)) {
			m_IsProcessDone = true;

			m_TargetPos = { 740.f ,560.f };
			m_fSpeed = ((m_TargetPos - m_tPosition).Length()) / 3;
			m_DirVec = (m_TargetPos - m_tPosition);
			m_DirVec.Normalize();
			m_Time = 0.f;

			m_eCurrentState = CustomerState::FIN;
			if (m_iEmotion == 2) {
				CSoundMgr::Get_Instance()->StopSound(SOUND_EFFECT2);
				CSoundMgr::Get_Instance()->PlaySound(L"visitor_talk_expensive.wav", SOUND_EFFECT2, 1.f);
			}
			else if (m_iEmotion == 1) {
				CSoundMgr::Get_Instance()->StopSound(SOUND_EFFECT2);
				CSoundMgr::Get_Instance()->PlaySound(L"visitor_talk_cheap.wav", SOUND_EFFECT2, 1.f);
				static_cast<CPlayer*>(m_pPlayer)->SellItem(m_itemInfo.strKeyName, m_itemInfo.iPrice);

			}
			else if (m_iEmotion == 0) {
				CSoundMgr::Get_Instance()->StopSound(SOUND_EFFECT2);
				CSoundMgr::Get_Instance()->PlaySound(L"visitor_talk_too_cheap.wav", SOUND_EFFECT2, 1.f);
				static_cast<CPlayer*>(m_pPlayer)->SellItem(m_itemInfo.strKeyName, m_itemInfo.iPrice);

			}
		}
		m_pComponent->RenderImageGetRow("MERCHANT_IDLE", _hDC, m_tPosition, m_AnimNum);
		break;
	case CustomerState::FIN:
		m_pComponent->PlayAnimGetRow("MERCHANT_ANIM2", _hDC, m_tPosition, m_AnimNum);

		break;

	case CustomerState::ENUM_END:
		break;
	default:
		break;
	}
}

void CCustomer::Release()
{
	SAFE_DELETE<CComponent*>(m_pComponent);
}

void CCustomer::OnCollide(CObj* _pObj)
{
}
