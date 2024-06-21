#include "PuzzleRoom.h"
#include"Tile.h"
#include"DungeonDoor.h"
#include"NPC.h"
#include"MusicBox.h"
#include"SoundMgr.h"

CPuzzleRoom::CPuzzleRoom()
{
}

CPuzzleRoom::~CPuzzleRoom()
{
	Release();
}

void CPuzzleRoom::Initialize()
{
	m_AnswerList.reserve(5);

	Vector renderVec = m_CenterPos->GetPosition();
	Vector StartVec = { renderVec.m_fX - WINCX * 0.5f , renderVec.m_fY - WINCY * 0.5f };
	Vector EndVec = { renderVec.m_fX + WINCX * 0.5f , renderVec.m_fY + WINCY * 0.5f };

	CObj* newTile1 = new CTile(ETileType::WALL, StartVec.m_fX + 155 * 0.5f, StartVec.m_fY + WINCY * 0.5f, 155, WINCY);
	m_ObjectList[(unsigned int)EObjectType::OBSTACLE].push_back(newTile1);
	newTile1 = new CTile(ETileType::WALL, (EndVec.m_fX - 155 * 0.5f), StartVec.m_fY + WINCY * 0.5f, 155, WINCY);
	m_ObjectList[(unsigned int)EObjectType::OBSTACLE].push_back(newTile1);

	newTile1 = new CTile(ETileType::WALL, renderVec.m_fX, StartVec.m_fY + (90 * 0.5f), WINCX, 90);
	m_ObjectList[(unsigned int)EObjectType::OBSTACLE].push_back(newTile1);
	newTile1 = new CTile(ETileType::WALL, renderVec.m_fX, EndVec.m_fY - (90 * 0.5f), WINCX, 90);
	m_ObjectList[(unsigned int)EObjectType::OBSTACLE].push_back(newTile1);

	//뮤직박스 및 맵 세팅

	CObj* newNpc = new CNPC;
	dynamic_cast<CNPC*>(newNpc)->SetImgKey("NPC_PIANO");
	dynamic_cast<CNPC*>(newNpc)->SetNpcType(2);
	newNpc->SetPosition({ m_CenterPos->GetPosition().m_fX,m_CenterPos->GetPosition().m_fY - 120.f });
	newNpc->Initialize();
	m_ObjectList[(unsigned int)EObjectType::OBSTACLE].push_back(newNpc);


	for (int i = 0; i < 5; ++i) {
		CObj* newMusicBox = new CMusicBox;
		newMusicBox->SetPosition({ m_CenterPos->GetPosition().m_fX - 300.f + 150 * i,m_CenterPos->GetPosition().m_fY + 80.f });
		static_cast<CMusicBox*>(newMusicBox)->SetBoxType(i);
		newMusicBox->Initialize();
		m_ObjectList[(unsigned int)EObjectType::OBSTACLE].push_back(newMusicBox);
		m_musicBoxList.push_back(newMusicBox);
	}

	//비교를 위해 미리 정답리스트를 채워둔다
	m_AnswerList.push_back(3);
	m_AnswerList.push_back(2);
	m_AnswerList.push_back(1);
	m_AnswerList.push_back(4);
	m_AnswerList.push_back(0);

	CCamera::GetInstance()->SetTarget(m_CenterPos);
	CCamera::GetInstance()->SetCameraMode(2);
	m_IsInitDone = true;

}

void CPuzzleRoom::Update()
{
	if (m_RoomClear) {
		return;
	}

	for (auto& iter : m_musicBoxList) {
		if (static_cast<CMusicBox*>(iter)->GetHitDone()) {
			int currentNum = static_cast<CMusicBox*>(iter)->GetTypeNum();
			auto it = find(m_plrAnswerList.begin(), m_plrAnswerList.end(), currentNum);
			if (it == m_plrAnswerList.end()) {
				m_plrAnswerList.push_back(currentNum);
				break;
			}
		}
	}
	

	for (auto& iter : m_plrAnswerList) {
		if (iter == m_AnswerList[m_iAnswerNum]) {
			m_IsReset = false;
			++m_iAnswerNum;
			if (5 == m_iAnswerNum) {
				break;
			}
		}
		else {
			m_IsReset = true;
			break;
		}
	}

	//snd_hurtloox
	if (m_IsReset) {
		m_plrAnswerList.clear();
		for (auto& iter : m_musicBoxList) {
			static_cast<CMusicBox*>(iter)->SetReset();
		}
		CSoundMgr::Get_Instance()->StopSound(MONSTER_EFFECT);
		CSoundMgr::Get_Instance()->PlaySound(L"snd_hurtloox.wav", MONSTER_EFFECT, 1.f);
	}

}

void CPuzzleRoom::Render(HDC _hDC)
{
	Vector renderVec = CCamera::GetInstance()->GetRenderPos(m_CenterPos->GetPosition());
	AnimInfo tempInfo = CResourceMgr::GetInstance()->FindRes(m_strBackGroundKey)->GetResInfo();

	GdiTransparentBlt(_hDC,
		renderVec.m_fX - WINCX * 0.5f,
		renderVec.m_fY - WINCY * 0.5f,
		tempInfo.iSizeX,
		tempInfo.iSizeY,
		CResourceMgr::GetInstance()->FindRes(m_strBackGroundKey)->GetMemDC(),
		0,
		0,
		tempInfo.iSizeX,
		tempInfo.iSizeY,
		RGB(0, 0, 0));

}

void CPuzzleRoom::LateUpdate()
{

	if (true == m_RoomClear || m_IsInitDone == false)
		return;

	if ( 5 == m_iAnswerNum) {
		m_RoomClear = true;
		for (auto& iter : m_doorList) {
			dynamic_cast<CDungeonDoor*>(iter)->SetDoorOpen();
		}
	}

	m_iAnswerNum = 0;
	m_IsReset = false;

}

void CPuzzleRoom::Release()
{
	SAFE_DELETE<CObj*>(m_CenterPos);

}

void CPuzzleRoom::SettingCamera()
{
	
	CCamera::GetInstance()->SetTarget(m_CenterPos);
	CCamera::GetInstance()->SetCameraMode(2);

}
