#include "MusicBox.h"
#include"GameMgr.h"
#include"KeyMgr.h"
#include"SoundMgr.h"

CMusicBox::CMusicBox() : m_pPlayerCopy(nullptr)
{
}

CMusicBox::~CMusicBox()
{
}

void CMusicBox::Initialize()
{
	CTile::Initialize();
	m_eTileType= ETileType::MUSICBOX;
	m_iRendNum = GAMEOBJECT;
}

void CMusicBox::Update()
{
	DetectedPlayer();
	KeyInput();
}

void CMusicBox::Render(HDC _hDC)
{

	if (false == m_animFin && true == m_isHitDone) {
		if (m_pComponent->PlayAnim("MUSICBOX_ANIM", _hDC, m_tPosition)) {
			m_animFin = true;
		}
	}
	else {
		m_pComponent->RenderImageGetRow("MUSICBOX_IDLE", _hDC, m_tPosition, (int)m_isHitDone);
	}


	if (m_IsPromptOn) {
		m_pComponent->RenderImage("MUSICBOX_BUBBLE", _hDC, { m_tPosition.m_fX, m_tPosition.m_fY - 80.f });
	}

}

void CMusicBox::LateUpdate()
{
}

void CMusicBox::Release()
{
}

void CMusicBox::OnCollide(CObj* _pObj)
{
	if (m_isHitDone)
		return;

	CSoundMgr::Get_Instance()->StopSound(SOUND_EFFECT);
	CSoundMgr::Get_Instance()->PlaySound(L"golem_dungeon_king_golem_hit.wav", SOUND_EFFECT, 1.f);
	m_isHitDone = true;
}


void CMusicBox::KeyInput()
{
	if (true == m_IsPromptOn) {

		if (CKeyMgr::GetInstance()->Key_Down('A') && true == m_IsPromptOn) {

			if (0 == m_iBoxTypeNum) {
				CSoundMgr::Get_Instance()->StopSound(MONSTER_EFFECT);
				CSoundMgr::Get_Instance()->PlaySound(L"mus_piano5.wav", MONSTER_EFFECT, 1.f);
			}
			else if (1 == m_iBoxTypeNum) {
				CSoundMgr::Get_Instance()->StopSound(MONSTER_EFFECT);
				CSoundMgr::Get_Instance()->PlaySound(L"mus_piano3.wav", MONSTER_EFFECT, 1.f);
			}
			else if (2 == m_iBoxTypeNum) {
				CSoundMgr::Get_Instance()->StopSound(MONSTER_EFFECT);
				CSoundMgr::Get_Instance()->PlaySound(L"mus_piano2.wav", MONSTER_EFFECT, 1.f);
			}
			else if (3 == m_iBoxTypeNum) {

				CSoundMgr::Get_Instance()->StopSound(MONSTER_EFFECT);
				CSoundMgr::Get_Instance()->PlaySound(L"mus_piano1.wav", MONSTER_EFFECT, 1.f);
			}
			else if (4 == m_iBoxTypeNum) {
				CSoundMgr::Get_Instance()->StopSound(MONSTER_EFFECT);
				CSoundMgr::Get_Instance()->PlaySound(L"mus_piano4.wav", MONSTER_EFFECT, 1.f);
			}

		}
	}

}

void CMusicBox::DetectedPlayer()
{
	if (!m_pPlayerCopy) {
		m_pPlayerCopy = CGameMgr::GetInstance()->GetPlayer();
	}
	else {
		Vector tPlayerPos = m_pPlayerCopy->GetPosition();
		Vector DirVec = { m_tPosition.m_fX - tPlayerPos.m_fX ,
							m_tPosition.m_fY - tPlayerPos.m_fY };
		if (DirVec.Length() < 60) {
			m_IsPromptOn = true;
		}
		else {
			m_IsPromptOn = false;
		}
	}

}
