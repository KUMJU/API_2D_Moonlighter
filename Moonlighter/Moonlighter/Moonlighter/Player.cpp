#include "Player.h"
#include"Tile.h"
#include"SceneMgr.h"
#include"UIMgr.h"
#include"Arrow.h"
#include"Spear.h"
#include"Sword.h"
#include"SoundMgr.h"
#include"Inventory.h"
#include"GameMgr.h"
#include"BombKirby.h"
#include"Bomb.h"
#include"FireShield.h"

CPlayer::CPlayer() :m_Animator(nullptr) , m_PlrProjList(nullptr), m_pInven(nullptr){
}

CPlayer::~CPlayer()
{
	Release();
}

void CPlayer::Initialize()
{
	m_iRendNum = GAMEOBJECT;
	m_eObjType = EObjectType::PLAYER;
	m_fSpeed = 5.f;
	m_tPosition = { 400.f,200.f };
	m_Animator = new CComponent;
	m_ePlrState = EPlayerState::IDLE;
	m_eDir = EDirection::DOWN;
	m_tSize = { 30.f, 40.f };
	m_pInven = new CInventory;
	m_pInven->Initialize();
	CUIMgr::GetInstance()->SetInventory(m_pInven);
	m_weaponList->push_back(EWeaponType::SWORD);
	m_weaponList->push_back(EWeaponType::SPEAR);
	CUIMgr::GetInstance()->SetGold(m_iGold);
	CUIMgr::GetInstance()->WeaponInventoryUpdate();


}

void CPlayer::Update()
{
	m_IsSwim = false;
	KeyInput();
	m_fSpeed = 5.f;
}

void CPlayer::KeyInput()
{
	if (EPlayerState::ROLLDOWN == m_ePlrState or EPlayerState::ATTACK == m_ePlrState) {
		return;
	}


	if (CKeyMgr::GetInstance()->Key_Down('I')) {
		CUIMgr::GetInstance()->InventorySwitch();
		//m_bIsUIOn = !m_bIsUIOn;
	}


	if(EGameState::PAUSE != CGameMgr::GetInstance()->GetGameState()) {
		if (CKeyMgr::GetInstance()->Key_Pressing(VK_LEFT)) {

			if (EPlayerState::IDLE == m_ePlrState)
				m_ePlrState = EPlayerState::WALK;

			m_eDir = EDirection::LEFT;
			m_tPosition.m_fX -= m_fSpeed;
		}

		if (CKeyMgr::GetInstance()->Key_Pressing(VK_RIGHT)) {
			if (EPlayerState::IDLE == m_ePlrState)
				m_ePlrState = EPlayerState::WALK;

			m_eDir = EDirection::RIGHT;
			m_tPosition.m_fX += m_fSpeed;
		}

		if (CKeyMgr::GetInstance()->Key_Pressing(VK_UP)) {
			if (EPlayerState::IDLE == m_ePlrState)
				m_ePlrState = EPlayerState::WALK;

			m_eDir = EDirection::UP;
			m_tPosition.m_fY -= m_fSpeed;
		}

		if (CKeyMgr::GetInstance()->Key_Pressing(VK_DOWN)) {
			if (EPlayerState::IDLE == m_ePlrState)
				m_ePlrState = EPlayerState::WALK;

			m_eDir = EDirection::DOWN;
			m_tPosition.m_fY += m_fSpeed;
		}

		if (CKeyMgr::GetInstance()->Key_Down(VK_SPACE)) {
			CSoundMgr::Get_Instance()->StopSound(SOUND_EFFECT);
			CSoundMgr::Get_Instance()->PlaySound(L"will_roll.wav", SOUND_EFFECT, 1.f);
			m_ePlrState = EPlayerState::ROLLDOWN;
		}

		if (CKeyMgr::GetInstance()->Key_Pressing('Z')) {
			m_ePlrState = EPlayerState::ATTACK;
			AttackAction();
		}

		if (CKeyMgr::GetInstance()->Key_Down('X')) {
			SwitchingWeapon();
		}

		if (CKeyMgr::GetInstance()->Key_Down('B')) {

			CObj* newBomb = new CBombKirby;
			newBomb->SetPosition({ m_tPosition.m_fX - 70.f,m_tPosition.m_fY });
			newBomb->Initialize();
			dynamic_cast<CBombKirby*>(newBomb)->SetList(m_PlrProjList, m_PlrObstacleList);
			m_PlrObstacleList->push_back(newBomb);
		}

		if (CKeyMgr::GetInstance()->Key_Pressing('V')) {
			if (m_IsCanShield && m_IsHaveSkill) {
				CObj* newShield = new CFireShield;
				newShield->SetPosition(m_tPosition);
				newShield->Initialize();
				m_PlrProjList->push_back(newShield);
				m_IsCanShield = false;
				m_ShieldCoolTime = (DWORD)GetTickCount64();
			}

		}

		if (CKeyMgr::GetInstance()->Key_Pressing('P')) {
			SetGold(500);
		}
	
	}

}

void CPlayer::LateUpdate()
{
	CalcHitTime();

	switch (m_ePlrState)
	{
	case EPlayerState::IDLE:
		break;
	case EPlayerState::WALK:
		CSoundMgr::Get_Instance()->PlaySound(L"will_step_golem_dungeon2.wav", SOUND_EFFECT, 1.5f);
		break;
	case EPlayerState::ROLLDOWN:
		PlayerRoll();
		break;
	case EPlayerState::ATTACK:
		break;
	case EPlayerState::ENUM_END:
		break;
	case EPlayerState::SWIM:
	
		break;
	default:
		break;
	}

	StateUpdate();

	if (false == m_IsCanShield) {
		CheckSkillCoolTime();
	}
}

void CPlayer::StateUpdate()
{
	if (m_ePlrState != EPlayerState::SWIM) {
		if (m_ePlrState == EPlayerState::WALK || true == m_IsStateChange) {
			m_ePlrState = EPlayerState::IDLE;
			m_IsStateChange = false;
		}
	}
	else {
		if (m_IsSwim == false) {
			CSoundMgr::Get_Instance()->StopSound(PLAYER_EFFECT);
			m_ePlrState = EPlayerState::IDLE;
			m_IsStateChange = false;
		}
	}

} 

void CPlayer::SwitchingWeapon()                                                                                                                                                                                                                                                                                                                                                      
{	
	CSoundMgr::Get_Instance()->StopSound(SOUND_EFFECT);
	CSoundMgr::Get_Instance()->PlaySound(L"will_weapon_change.wav", SOUND_EFFECT, 1.f);
	iter_swap(m_weaponList->begin(), m_weaponList->end()-1);
	m_pInven->SwitchingWeapon();
	//CUIMgr::GetInstance()->SetWeapon((unsigned int)(m_weaponList->front()));
}

void CPlayer::ChangeWeapon(int _src,int _dst)
{
	string newWeapon = m_pInven->ChangeWeapon(_src, _dst);

	auto iter1 = m_weaponList->begin();

	if (1 == _src) {
		++iter1;
	}

	if ("UI_SWORD" == newWeapon) {
		*iter1 = EWeaponType::SWORD;
	}
	else if ("UI_BOW" == newWeapon) {
		*iter1 = EWeaponType::BOW;
	}
	else if ("UI_SPEAR" == newWeapon) {
		*iter1 = EWeaponType::SPEAR;
	}
}

void CPlayer::OnAttacked(int Damage)
{
	if (m_IsSuperArmor) {
		return;
	}

	m_IsSuperArmor = true;
	m_IsOnHit = true;
	m_HitTime = GetTickCount64();
	m_iHp -= Damage;

	CSoundMgr::Get_Instance()->StopSound(SOUND_EFFECT);
	CSoundMgr::Get_Instance()->PlaySound(L"will_damaged.wav", SOUND_EFFECT, 1.f);
	KnockBack();
	if (m_iHp <= 0) {
		m_iHp = 0;
		m_ePlrState = EPlayerState::DEAD;
	}

	CCamera::GetInstance()->Vibration(5.f, 0.2f, 30.f, EDirection::RIGHT);
	CUIMgr::GetInstance()->SetHP(m_iHp);
}

void CPlayer::KnockBack()
{
	if (EDirection::DOWN == m_eDir) {
		m_tPosition.m_fY -= 10.f;
	}
	else if (EDirection::LEFT == m_eDir) {
		m_tPosition.m_fX += 10.f;

	}
	else if (EDirection::RIGHT == m_eDir) {
		m_tPosition.m_fX -= 10.f;


	}else if (EDirection::UP == m_eDir) {
		m_tPosition.m_fY += 10.f;

	}


}

void CPlayer::HitRender()
{
	if (!m_IsOnHit) {
		return;
	}

	if (m_HitRenderTime + 100 <= (DWORD)GetTickCount64()) {
		m_HitRender = !m_HitRender;
		m_HitRenderTime = GetTickCount64();
	}

}

void CPlayer::CalcHitTime()
{
	if (true == m_IsOnHit) {
		if (m_HitTime + 1500 < (DWORD)GetTickCount64()) {
			m_IsOnHit = false;
			m_HitRender = false;
			m_IsSuperArmor = false;
		}
	}

}

void CPlayer::PlayerRoll()
{
	if (EDirection::DOWN == m_eDir) {
		m_tPosition.m_fY += 5.f;
	}
	else if (EDirection::UP == m_eDir) {
		m_tPosition.m_fY -= 5.f;
	}
	else if (EDirection::LEFT == m_eDir) {
		m_tPosition.m_fX -= 5.f;
	}
	else if (EDirection::RIGHT == m_eDir) {
		m_tPosition.m_fX += 5.f;
	}
}

void CPlayer::AttackAction()
{
	switch (m_weaponList->front()) {
	case EWeaponType::SWORD:
	{
		CSoundMgr::Get_Instance()->StopSound(PLAYER_EFFECT);
		CSoundMgr::Get_Instance()->PlaySound(L"short_sword_main_swing2.wav", PLAYER_EFFECT, 1.5f);

		CObj* newSword = new CSword;
		dynamic_cast<CProjectile*>(newSword)->SetDirection(m_eDir);
		newSword->SetPosition(m_tPosition);
		newSword->Initialize();
		m_PlrProjList->push_back(newSword);

		break;
	}
	case EWeaponType::BOW:
	{
		CSoundMgr::Get_Instance()->StopSound(SOUND_EFFECT);
		CSoundMgr::Get_Instance()->PlaySound(L"bow_main_attack_shoot.wav", SOUND_EFFECT, 1.5f);
		CObj* newArrow = new CArrow;
		dynamic_cast<CProjectile*>(newArrow)->SetDirection(m_eDir);
		newArrow->SetPosition(m_tPosition);
		newArrow->Initialize();
		m_PlrProjList->push_back(newArrow);
		break;

	}
	case EWeaponType::SPEAR:
	{
	CSoundMgr::Get_Instance()->StopSound(SOUND_EFFECT);
	CSoundMgr::Get_Instance()->PlaySound(L"spear_main_attack_swing.wav", SOUND_EFFECT, 1.5f);
		//spear_main_attack_swing
		CObj* newSpear = new CSpear;
		dynamic_cast<CProjectile*>(newSpear)->SetDirection(m_eDir);
		newSpear->SetPosition(m_tPosition);
		newSpear->Initialize();
		m_PlrProjList->push_back(newSpear);
		break;
	}
	}

}

void CPlayer::HealingHP(int _iHp)
{
	m_iHp += _iHp;

	//나중에 maxhp러 수정
	if (m_iHp > m_iMaxHp) {
		m_iHp = m_iMaxHp;
	}

	CUIMgr::GetInstance()->SetHP(m_iHp);

}

void CPlayer::SetMaxHp(int _iHp)
{
	m_iMaxHp += _iHp;
	CUIMgr::GetInstance()->SetMaxHP(m_iMaxHp);
}

void CPlayer::SetGold(int _gold)
{
	m_iGold += _gold;
	CUIMgr::GetInstance()->SetGold(m_iGold);
}

void CPlayer::CheckSkillCoolTime()
{
	if (m_ShieldCoolTime + 30000 < (DWORD)GetTickCount64()) {
		m_IsCanShield = true;
	}

}

void CPlayer::GetNewItem(CObj* _item)
{
	m_pInven->InsertItem(_item);

}

void CPlayer::SellItem(string _itemKeyName, int _price)
{
	SetGold(_price);
	m_pInven->SellItem(_itemKeyName);
}


void CPlayer::Render(HDC _hDC)
{
	HitRender();
	string currentKey = "Player" + to_string((int)m_ePlrState) + to_string((int)m_eDir);

	if (EPlayerState::ATTACK == m_ePlrState) {
		currentKey += to_string((int)m_weaponList->front());
	}
	m_IsStateChange = m_Animator->PlayAnimGetRow(currentKey, _hDC, m_tPosition, (int)m_HitRender);

}

void CPlayer::Release()
{
	SAFE_DELETE<CInventory*>(m_pInven);
	SAFE_DELETE<CComponent*>(m_Animator);
}

void CPlayer::OnCollide(CObj* _pObj)
{
	if (EObjectType::ITEM == _pObj->GetObjType()) {
		m_pInven->InsertItem(_pObj);
	}

	if (EObjectType::OBSTACLE == _pObj->GetObjType()) {
		if (ETileType::HEALINGPOOL == dynamic_cast<CTile*>(_pObj)->GetTileType()) {
			m_ePlrState = EPlayerState::SWIM;
			m_IsSwim = true;
			if (m_HealingCoolTime + 100 <= (DWORD)GetTickCount64()) {
				HealingHP(1);
				m_HealingCoolTime = (DWORD)GetTickCount64();
			}

			if (m_SoundConrol + 1000 <= (DWORD)GetTickCount64()) {
				CSoundMgr::Get_Instance()->StopSound(PLAYER_EFFECT);
				CSoundMgr::Get_Instance()->PlaySound(L"will_swimming.wav", PLAYER_EFFECT, 5.f);
				m_SoundConrol = (DWORD)GetTickCount64();
			}

		}
		else if(ETileType::SLOW == dynamic_cast<CTile*>(_pObj)->GetTileType()){

			m_fSpeed = 2.f;
		}
		else if (ETileType::HOLE == dynamic_cast<CTile*>(_pObj)->GetTileType()) {
			OnAttacked(5);
		}


	}


	if (true == m_IsSuperArmor) {
		return;
	}


}
