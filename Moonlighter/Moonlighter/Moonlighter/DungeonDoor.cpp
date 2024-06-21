#include "DungeonDoor.h"
#include"Component.h"
#include"GameMgr.h"
#include"SoundMgr.h"

CDungeonDoor::CDungeonDoor(): m_pComponent(nullptr)
{
}

CDungeonDoor::CDungeonDoor(EDirection _dir, int _roomNum, int _dungeonNum) : m_pComponent(nullptr)
{
	m_eDir = _dir;
	m_iNextRoomNum = _roomNum;
	m_iDungeonNum = _dungeonNum;
}

CDungeonDoor::~CDungeonDoor()
{
	Release();
}

void CDungeonDoor::Initialize()
{
	CDoor::Initialize();
	m_pComponent = new CComponent;
	m_currentState = EDoorState::CLOSE;

}

void CDungeonDoor::Update()
{
	m_IsPlrTouch = false;

}

void CDungeonDoor::Render(HDC _hDC)
{
	if (1 == m_iDungeonNum) {
		switch (m_currentState)
		{
		case EDoorState::CLOSE:
			if (m_IsAimFin) {
				m_pComponent->RenderImageGetRow("DUNGEON1_DOOR_CLOSE", _hDC, m_tPosition, (int)m_eDir);
			}
			else {
				if (m_pComponent->PlayAnimGetRow("DUNGEON1_DOOR_CLOSE_ANIM", _hDC, m_tPosition, (int)m_eDir)) {
					m_IsAimFin = true;
				}
			}
			break;
		case EDoorState::OPEN:
			if (m_IsAimFin) {
				m_pComponent->RenderImageGetRow("DUNGEON1_DOOR_OPEN", _hDC, m_tPosition, (int)m_eDir);

			}
			else {
				if (m_pComponent->PlayAnimGetRow("DUNGEON1_DOOR_OPEN_ANIM", _hDC, m_tPosition, (int)m_eDir)) {
					m_IsAimFin = true;
				}
			}
			break;
		case EDoorState::ENUM_END:
			break;
		default:
			break;
		}
	}
	else if (2 == m_iDungeonNum) {

		switch (m_currentState)
		{
		case EDoorState::CLOSE:
			if (m_IsAimFin) {
				m_pComponent->RenderImageGetRow("DUNGEON2_DOOR_CLOSE", _hDC, m_tPosition, (int)m_eDir);
			}
			else {
				if (m_pComponent->PlayAnimGetRow("DUNGEON2_DOOR_CLOSE_ANIM", _hDC, m_tPosition, (int)m_eDir)) {
					m_IsAimFin = true;
				}
			}
			break;
		case EDoorState::OPEN:
			if (m_IsAimFin) {
				m_pComponent->RenderImageGetRow("DUNGEON2_DOOR_OPEN", _hDC, m_tPosition, (int)m_eDir);

			}
			else {
				if (m_pComponent->PlayAnimGetRow("DUNGEON2_DOOR_OPEN_ANIM", _hDC, m_tPosition, (int)m_eDir)) {
					m_IsAimFin = true;
				}
			}
			break;
		case EDoorState::ENUM_END:
			break;
		default:
			break;
		}
	}
	
}

void CDungeonDoor::LateUpdate()
{
}

void CDungeonDoor::Release()
{
	SAFE_DELETE<CComponent*>(m_pComponent);

}

void CDungeonDoor::OnCollide(CObj* _pObj)
{
	if (_pObj->GetObjType() == EObjectType::PLAYER && m_currentState == EDoorState::OPEN) {
		m_IsPlrTouch = true;

		if (EDirection::UP == m_eDir) {
			CGameMgr::GetInstance()->GetPlayer()->SetPosition({m_tPosition.m_fX , m_tPosition.m_fY-300.f});

		}
		else if (EDirection::DOWN == m_eDir) {
			CGameMgr::GetInstance()->GetPlayer()->SetPosition({ m_tPosition.m_fX , m_tPosition.m_fY+300.f });

		}
		else if (EDirection::LEFT == m_eDir) {
			CGameMgr::GetInstance()->GetPlayer()->SetPosition({ m_tPosition.m_fX-400.f , m_tPosition.m_fY });
		}
		else if (EDirection::RIGHT == m_eDir) {
			CGameMgr::GetInstance()->GetPlayer()->SetPosition({ m_tPosition.m_fX+400.f , m_tPosition.m_fY });
		}

	}

}

void CDungeonDoor::SetSound()
{
	if (m_currentState == EDoorState::OPEN) {
		if (1 == m_iDungeonNum) {
			CSoundMgr::Get_Instance()->StopSound(BOSS_EFFECT);
			CSoundMgr::Get_Instance()->PlaySound(L"golem_dungeon_normal_door_opening.wav", BOSS_EFFECT, 1.5f);
		}
		else if (2 == m_iDungeonNum) {
		
			CSoundMgr::Get_Instance()->StopSound(BOSS_EFFECT);
			CSoundMgr::Get_Instance()->PlaySound(L"forest_dungeon_normal_door_opening.wav", BOSS_EFFECT, 1.5f);
		}
	}

}
