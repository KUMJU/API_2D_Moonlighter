#pragma once
#include"pch.h"
#include"Component.h"
#include"GameMgr.h"
#include"SoundMgr.h"
#include"Define.h"

enum class EUIState {
	DEFAULT,
	INVENTORY,
	EQUIP,
	SHOP,
	HOME_SHOP,
	HOME_SHOP_SETTING,
	ENUM_END
};


class CInventory;
class CShop;

class CUIMgr
{
private:
	CUIMgr();
	~CUIMgr();

public:
	static CUIMgr* GetInstance() {
		if (!m_pInstance) {
			m_pInstance = new CUIMgr;
		}

		return m_pInstance;
	}

	static void DestroyInstance()
	{
		if (m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}

public:
	void Initialize();
	void Update();
	void Render(HDC _hDC);
	void Release();
	void KeyInput();
public:
	//기능적인 부분들을 담당하는 함수
	void RenderHpBar(HDC _hDC);
	void RenderBossHpBar(HDC _hDC);
	void RenderWeapon(HDC _hDC);

public:

	//UI위치를 변환해서 비주얼적인 효과를 보여주는 함수
	void UISlide();
	void UIShaking();

public:


	void ResetOneSlot(int _num);

	void SetUIOn() { m_IsUIVisible = true; }
	void SetUIOff() { m_IsUIVisible = false; }

	void SetWeapon(int _weaponType) { m_currentPlrWeapon = _weaponType; }
	void SetGold(int _gold) { m_currentPlrGold = _gold; }
	void SetHP(int _hp) { m_currentPlrHp = _hp; }
	void SetMaxHP(int _maxHp) { m_iPlrMaxHp = _maxHp; }

	void SetBossHp(int _hp) { m_iBossCurHp = _hp; }
	void SetBossMaxHp(int _maxHp) { m_iBossMaxHp = _maxHp; 
									m_iBossCurHp = _maxHp;
									if (200 == _maxHp) {
										m_strBossName = "BOSS_NAME1";
									}
									else if (300 == _maxHp) {
										m_strBossName = "BOSS_NAME2";
									}
	}
	void ScrollOn() { m_ScrollOn = true; }
	void DungeonNameVisible() { m_DungeonNameVisible = true; }

	void InventoryRender(HDC _hDC);
	void InventorySwitch() { 
		CSoundMgr::Get_Instance()->StopSound(SOUND_EFFECT);
		CSoundMgr::Get_Instance()->PlaySound(L"gui_inventory_open.wav", SOUND_EFFECT, 1.5f);

		if (EUIState::INVENTORY == m_eCurrentUI) {
			m_eCurrentUI = EUIState::DEFAULT;
			UIReset();
			CGameMgr::GetInstance()->SetGameState(EGameState::DEFAULT);
		}
		else {
			m_eCurrentUI = EUIState::INVENTORY;
			CGameMgr::GetInstance()->SetGameState(EGameState::PAUSE);
		}
	}

	void ShopSwitch() {
		if (EUIState::SHOP == m_eCurrentUI) {
			m_eCurrentUI = EUIState::DEFAULT;
			UIReset();
			CGameMgr::GetInstance()->SetGameState(EGameState::DEFAULT);
		}
		else {
			CSoundMgr::Get_Instance()->StopSound(MONSTER_EFFECT);
			CSoundMgr::Get_Instance()->PlaySound(L"hawker_open_gui.wav", MONSTER_EFFECT, 1.f);
			m_eCurrentUI = EUIState::SHOP;
			CGameMgr::GetInstance()->SetGameState(EGameState::PAUSE);
		}
	}

	void HomeShopSwitch() {
		if (EUIState::HOME_SHOP == m_eCurrentUI) {
			m_eCurrentUI = EUIState::DEFAULT;
			UIReset();
			CGameMgr::GetInstance()->SetGameState(EGameState::DEFAULT);
		}
		else {
			m_eCurrentUI = EUIState::HOME_SHOP;
			CGameMgr::GetInstance()->SetGameState(EGameState::PAUSE);
		}
	}

	void HomeShopRender(HDC _hDC);

	void CalcCursorPos();
	
	void WeaponInventoryUpdate();
	void StuffInventoryUpdate();
	void SetInventory(CInventory* _inven) { m_inventory = _inven; }
	void SetShop(CShop* _shop) { m_pShop = _shop; }

	void ShopRender(HDC _hDC);
	void ItemInfoRender(HDC _hDC);
	void EquipRender(HDC _hDC);
	void SetScrollName(string _name) { 
		m_strScrollName = _name; 
	
		if ("SCROLL1" == _name) {
			m_strDungeonName = "DUNGEON1_NAME";

		}
		else if ("SCROLL2" == _name) {
			m_strDungeonName = "DUNGEON2_NAME";
		}
	
	}

	void UIReset();
	void ResetSettingUI();

	vector<ItemViewInfo> GetSellList() { return m_ShopSettingList; }

private: 
	static CUIMgr* m_pInstance;
	bool m_IsUIVisible = false;
	CComponent* m_pComponent;
	bool m_ScrollOn = false;
	bool m_DungeonNameVisible = false;
	bool m_IsInventoryOn = false;
	bool m_IsHomeShopOn = false;
	EUIState m_eCurrentUI = EUIState::DEFAULT;

private:
	int		m_currentPlrHp = 100;
	int		m_iPlrMaxHp = 100;
	string		m_currentPlrWeapon = "";
	string		m_currentPlrSecondWeapon = "";
	int		m_currentPlrGold = 0;

	string m_strBossName = "";
	string m_strScrollName = "";
	string m_strDungeonName = "";

private:

	int		m_iBossMaxHp = 0;
	int		m_iBossCurHp = 0;

	//inventory
private:
	CInventory* m_inventory;
	CShop* m_pShop;

	Vector m_tCursorPos;
	int m_CurrentCursor = 0;
	int m_equipCursor = 0;
	int m_SettingCursor = 0;

	list<string> m_WeponInvenList;
	list<string> m_StuffInvenList;
	int iAnimRow = 0;

	vector<ItemViewInfo> m_ShopSettingList;
	
};

