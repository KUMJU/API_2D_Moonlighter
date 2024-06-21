#include "UIMgr.h"
#include"MyResource.h"
#include"KeyMgr.h"
#include"Obj.h"
#include"Inventory.h"
#include"Item.h"
#include"Shop.h"
#include"Player.h"

CUIMgr* CUIMgr::m_pInstance = nullptr;

CUIMgr::CUIMgr() : m_pComponent(nullptr), m_inventory(nullptr), m_pShop(nullptr)
{
}

CUIMgr::~CUIMgr()
{
	Release();
}

void CUIMgr::Initialize()
{
	m_pComponent = new CComponent;
	ResetSettingUI();
}

void CUIMgr::Update()
{
	if (m_eCurrentUI != EUIState::DEFAULT) {
		KeyInput();
	}

}

void CUIMgr::Render(HDC _hDC)
{
	if (false == m_IsUIVisible) {
		return;
	}

	//PLAYER_HPBAR
	m_pComponent->RenderFixedImage("HPBAR_ROUND", _hDC, { 250.f,49.f });
	m_pComponent->RenderFixedImage("HPCIRCLE", _hDC, { 163.f,49.f });
	m_pComponent->RenderFixedImage("HEART", _hDC, { 163.f,51.f });

	//가변적으로 변해야함
	RenderHpBar(_hDC);

	//GOLD
	m_pComponent->RenderFixedImage("UI_BASICCIRCLE", _hDC, { 80.f,100.f });
	m_pComponent->RenderFixedImage("UI_GOLD", _hDC, { 80.f,100.f });
	m_pComponent->RenderFixedImage("UI_COIN", _hDC, { 50.f,170.f });

	TCHAR		szLife[32] = L"";

	SetTextColor(_hDC, RGB(255, 255, 255));
	SetBkMode(_hDC, TRANSPARENT);
	wsprintf(szLife, L"%d", m_currentPlrGold);
	TextOut(_hDC, 70, 160, szLife, lstrlen(szLife));

	//weapon
	m_pComponent->RenderFixedImage("UI_BASICCIRCLEBACK", _hDC, { WINCX - 100.f,100.f });
	m_pComponent->RenderFixedImage("UI_BASICCIRCLE", _hDC, { WINCX - 80.f,100.f });

	//inventory
	m_pComponent->RenderFixedImage("UI_BASICCIRCLE", _hDC, { WINCX - 80.f,220.f });
	m_pComponent->RenderFixedImage("UI_BAG", _hDC, { WINCX - 80.f,220.f });

	m_pComponent->RenderFixedImage("UI_BTN_X", _hDC, { WINCX - 110.f,130.f });
	m_pComponent->RenderFixedImage("UI_BTN_I", _hDC, { WINCX - 110.f,250.f });

	wsprintf(szLife, L"%d", m_currentPlrHp);
	TextOut(_hDC, 257, 65, szLife, lstrlen(szLife));

	wsprintf(szLife, L"/ ");
	TextOut(_hDC, 285, 65, szLife, lstrlen(szLife));

	wsprintf(szLife, L"%d", m_iPlrMaxHp);
	TextOut(_hDC, 290, 65, szLife, lstrlen(szLife));

	RenderWeapon(_hDC);


	if (0 != m_iBossMaxHp) {

		RenderBossHpBar(_hDC);
		m_pComponent->RenderFixedImage(m_strBossName, _hDC, { WINCX * 0.5f,620.f });

	}

	if (m_ScrollOn) {
		if (m_pComponent->RenderFixedAnim(m_strScrollName, _hDC, { WINCX * 0.5f, 550.f }, iAnimRow)) {
			if (0 == iAnimRow) {
				++iAnimRow;
			}
			else if (1 == iAnimRow) {
				m_ScrollOn = false;
				m_DungeonNameVisible = false;
			}
		}
	}

	if (m_DungeonNameVisible) {
		m_pComponent->RenderFixedImage(m_strDungeonName, _hDC, { WINCX * 0.5f, 630.f });
	}

	if (EUIState::INVENTORY == m_eCurrentUI || EUIState::EQUIP == m_eCurrentUI) {
		InventoryRender(_hDC);
	}

	if (EUIState::EQUIP == m_eCurrentUI) {
		EquipRender(_hDC);
	}

	if (EUIState::SHOP == m_eCurrentUI) {
		ShopRender(_hDC);
	}

	if (EUIState::HOME_SHOP == m_eCurrentUI ) {
		HomeShopRender(_hDC);

	}
		
		
	if (EUIState::HOME_SHOP_SETTING == m_eCurrentUI) {
		HomeShopRender(_hDC);
		if (m_SettingCursor == 0) {
			m_pComponent->RenderFixedImage("UI_SHOP_SELECTOR", _hDC, { 797.f , 255.f });
		}
		else {
			m_pComponent->RenderFixedImage("UI_SHOP_SELECTOR", _hDC, { 797.f + 246.f * (m_SettingCursor % 2) , 255.f + 210.f * (m_SettingCursor / 2) });

		}
	}
}

void CUIMgr::Release()
{
	SAFE_DELETE<CComponent*>(m_pComponent);
}

void CUIMgr::KeyInput()
{

	if (EUIState::DEFAULT == m_eCurrentUI)
		return;

	//인벤토리
	if (EUIState::INVENTORY == m_eCurrentUI) {

		if (CKeyMgr::GetInstance()->Key_Down(VK_RIGHT)) {
			++m_CurrentCursor;
			CSoundMgr::Get_Instance()->StopSound(SOUND_EFFECT);
			CSoundMgr::Get_Instance()->PlaySound(L"gui_selector_movement.wav", SOUND_EFFECT, 1.5f);
			if (m_CurrentCursor > 4) {
				m_CurrentCursor = 4;
			}
		}

		if (CKeyMgr::GetInstance()->Key_Down(VK_LEFT)) {
			--m_CurrentCursor;
			CSoundMgr::Get_Instance()->StopSound(SOUND_EFFECT);
			CSoundMgr::Get_Instance()->PlaySound(L"gui_selector_movement.wav", SOUND_EFFECT, 1.5f);
			if (m_CurrentCursor < 0) {
				m_CurrentCursor = 0;
			}
		}

		//장착 무기 변경
		if (CKeyMgr::GetInstance()->Key_Down(VK_SPACE)) {
			
			if (m_WeponInvenList.size() - 2 <= m_CurrentCursor)
				return;

			CSoundMgr::Get_Instance()->StopSound(SOUND_EFFECT);
			CSoundMgr::Get_Instance()->PlaySound(L"gui_press_button.wav", SOUND_EFFECT, 1.5f);
			m_eCurrentUI = EUIState::EQUIP;
		}
	}
	else if (EUIState::SHOP == m_eCurrentUI) {
		if (CKeyMgr::GetInstance()->Key_Down(VK_RIGHT)) {
			++m_CurrentCursor;

			if (m_CurrentCursor > 2) {
				m_CurrentCursor = 2;
			}
		}

		if (CKeyMgr::GetInstance()->Key_Down(VK_LEFT)) {
			--m_CurrentCursor;

			if (m_CurrentCursor < 0) {
				m_CurrentCursor = 0;
			}
		}

		//구매
		if (CKeyMgr::GetInstance()->Key_Down(VK_SPACE)) {
			if (m_pShop->PurchaseProduct(m_CurrentCursor)) {
				//구매에 성공했습니다.
				CSoundMgr::Get_Instance()->StopSound(SOUND_EFFECT);
				CSoundMgr::Get_Instance()->PlaySound(L"shop_item_sold.wav", SOUND_EFFECT, 1.5f);
			}
			else {
				CSoundMgr::Get_Instance()->StopSound(SOUND_EFFECT);
				CSoundMgr::Get_Instance()->PlaySound(L"will_exclamation_tutorial.wav", SOUND_EFFECT, 1.5f);
				//돈이 부족합니다.
			}
		}

	}
	else if (EUIState::EQUIP == m_eCurrentUI) {

		if (CKeyMgr::GetInstance()->Key_Down(VK_RIGHT)) {
			++m_equipCursor;
			CSoundMgr::Get_Instance()->StopSound(SOUND_EFFECT);
			CSoundMgr::Get_Instance()->PlaySound(L"gui_selector_movement.wav", SOUND_EFFECT, 1.5f);
			if (m_equipCursor > 1) {
				m_equipCursor = 0;
			}
		}

		if (CKeyMgr::GetInstance()->Key_Down(VK_LEFT)) {
			--m_equipCursor;
			CSoundMgr::Get_Instance()->StopSound(SOUND_EFFECT);
			CSoundMgr::Get_Instance()->PlaySound(L"gui_selector_movement.wav", SOUND_EFFECT, 1.5f);
			if (m_equipCursor < 0) {
				m_equipCursor = 1;
			}
		}

		if (CKeyMgr::GetInstance()->Key_Down(VK_SPACE)) {
			CObj* Pplr=	 CGameMgr::GetInstance()->GetPlayer();
			static_cast<CPlayer*>(Pplr)->ChangeWeapon(m_equipCursor, m_CurrentCursor+2);
			m_eCurrentUI = EUIState::INVENTORY;
		}

		if (CKeyMgr::GetInstance()->Key_Down(VK_ESCAPE)) {
			m_eCurrentUI = EUIState::INVENTORY;
		}
	}
	else if (EUIState::HOME_SHOP == m_eCurrentUI) {

		if (CKeyMgr::GetInstance()->Key_Down(VK_RIGHT)) {
			++m_CurrentCursor;
			CSoundMgr::Get_Instance()->StopSound(SOUND_EFFECT);
			CSoundMgr::Get_Instance()->PlaySound(L"gui_selector_movement.wav", SOUND_EFFECT, 1.5f);
			if (m_CurrentCursor > 4) {
				m_CurrentCursor = 4;
			}
		}

		if (CKeyMgr::GetInstance()->Key_Down(VK_LEFT)) {
			--m_CurrentCursor;
			CSoundMgr::Get_Instance()->StopSound(SOUND_EFFECT);
			CSoundMgr::Get_Instance()->PlaySound(L"gui_selector_movement.wav", SOUND_EFFECT, 1.5f);
			if (m_CurrentCursor < 0) {
				m_CurrentCursor = 0;
			}
		}

		if (CKeyMgr::GetInstance()->Key_Down(VK_SPACE)) {

			if (m_StuffInvenList.size() <= m_CurrentCursor) {
				return;
			}

			int iCount = 0;
			for (auto& iter : m_ShopSettingList) {
				if ("" == iter.strKeyName) {
					m_SettingCursor = iCount;
					break;
				}
				else {
					++iCount;
				}
			}

			if (iCount == 4) {
				return;
			}

			m_eCurrentUI = EUIState::HOME_SHOP_SETTING;

			auto it = m_StuffInvenList.begin();

			for (int i = 0; i < m_CurrentCursor; ++i) {
				++it;
			}

			m_ShopSettingList[m_SettingCursor].strKeyName = *(it);
		}

	}
	else if (EUIState::HOME_SHOP_SETTING == m_eCurrentUI) {
		if (CKeyMgr::GetInstance()->Key_Down(VK_RIGHT)) {
			m_ShopSettingList[m_SettingCursor].iPrice += 10;
		}

		if (CKeyMgr::GetInstance()->Key_Down(VK_LEFT)) {
			m_ShopSettingList[m_SettingCursor].iPrice -= 10;

			if (m_ShopSettingList[m_SettingCursor].iPrice < 0) {
				m_ShopSettingList[m_SettingCursor].iPrice = 0;
			}

		}

		if (CKeyMgr::GetInstance()->Key_Down(VK_SPACE)) {
			m_eCurrentUI = EUIState::HOME_SHOP;
		}
	}


}

void CUIMgr::RenderHpBar(HDC _hDC)
{
	CMyResource* CurRes = CResourceMgr::GetInstance()->FindRes("HPBAR");
	AnimInfo tempInfo = CurRes->GetResInfo();

	GdiTransparentBlt(_hDC,
		static_cast<int>(255.f - (tempInfo.iSizeX * 0.5f)),
		static_cast<int>(49.f - (tempInfo.iSizeY * 0.5f)),
		static_cast<int>(tempInfo.iSizeX * ((float)m_currentPlrHp / (float)m_iPlrMaxHp)),
		tempInfo.iSizeY,
		CurRes->GetMemDC(),
		0,
		0,
		tempInfo.iSizeX,
		tempInfo.iSizeY,
		RGB(0, 0, 0));

}

void CUIMgr::RenderBossHpBar(HDC _hDC)
{
	CMyResource* CurRes = CResourceMgr::GetInstance()->FindRes("UI_BOSSHP");		
	AnimInfo tempInfo = CurRes->GetResInfo();

	GdiTransparentBlt(_hDC,
		198,
		638,
		static_cast<int>(tempInfo.iSizeX * ((float)m_iBossCurHp / m_iBossMaxHp)),
		tempInfo.iSizeY,
		CurRes->GetMemDC(),
		0,
		0,
		static_cast<int>(tempInfo.iSizeX * ((float)m_iBossCurHp / m_iBossMaxHp)),
		tempInfo.iSizeY,
		RGB(0, 0, 0));

	m_pComponent->RenderFixedImage("UI_BOSSHP_ROUND", _hDC, { WINCX * 0.5f,650.f });

}

void CUIMgr::RenderWeapon(HDC _hDC)
{
	m_pComponent->RenderFixedImage(m_currentPlrWeapon, _hDC, { WINCX - 85.f,90.f });
}

void CUIMgr::UISlide()
{
}

void CUIMgr::UIShaking()
{
}

void CUIMgr::ResetOneSlot(int _num)
{
	m_ShopSettingList[_num].strKeyName = "";
	m_ShopSettingList[_num].iPrice = 0;

}

void CUIMgr::InventoryRender(HDC _hDC)
{

	m_pComponent->RenderFixedImage("INVENTORY", _hDC, { WINCX * 0.5f, WINCY * 0.5f + 10.f });
	int iCount = 0;

	for (auto& i : m_WeponInvenList) {
		if (0 == iCount) {
			m_pComponent->RenderFixedImage(i, _hDC, { 770.f ,195.f });
		}
		else if (1 == iCount) {
			m_pComponent->RenderFixedImage(i, _hDC, { 940.f ,195.f });
		}
		else {
			Vector tempPos = { 240.f + (iCount-2) * 71.5f, 195.f };
			m_pComponent->RenderFixedImage(i, _hDC, tempPos);

		}
		++iCount;
	}

	iCount = 0;
	for (auto &i : m_StuffInvenList) {
		Vector tempPos = { 245.f + iCount*71.5f, 290.f };
		m_pComponent->RenderFixedImage(i, _hDC, tempPos);
		++iCount;
	}
	m_pComponent->RenderFixedImage("INVENTORY_CURSOR", _hDC, { 245.f + m_CurrentCursor * 71.5f ,205.f });
}

void CUIMgr::HomeShopRender(HDC _hDC)
{
	//인벤토리 렌더
	m_pComponent->RenderFixedImage("UI_HOMESHOP", _hDC, { WINCX * 0.5f, WINCY * 0.5f });
	
	int iCount = 0;
	for (auto& i : m_WeponInvenList) {
		if(iCount >= 2){
			Vector tempPos = { 240.f + (iCount - 2) * 71.5f, 190.f };
			m_pComponent->RenderFixedImage(i, _hDC, tempPos);
		}
		++iCount;
	}

	iCount = 0;
	for (auto& i : m_StuffInvenList) {
		Vector tempPos = { 245.f + iCount * 71.5f, 280.f };
		m_pComponent->RenderFixedImage(i, _hDC, tempPos);
		++iCount;
	}

	m_pComponent->RenderFixedImage("INVENTORY_CURSOR", _hDC, { 245.f + m_CurrentCursor * 71.5f ,285.f });

	//itemslot
	iCount = 0;
	int iCount2 = 0;
	int iCount3 = 0;


	//아이템 슬롯 리스트 
	for (auto& iter : m_ShopSettingList) {
		if (iter.strKeyName != "") {
			
			if (iCount > 0) {
				iCount2 = iCount / 2;
				iCount3 = iCount % 2;
			}

			m_pComponent->RenderFixedImage(iter.strKeyName, _hDC, { 800.f + iCount3 * 245.f ,190.f  + iCount2 *215.f});

			TCHAR szPrice[16] = L"";
			wsprintf(szPrice, L"%d", iter.iPrice);
			TextOut(_hDC, 795 + iCount3 * 250, 310 + 215* iCount2, szPrice, lstrlen(szPrice));

			m_pComponent->RenderFixedImage("UI_COIN", _hDC, { 765.f + iCount3 * 250.f ,320.f + 215.f * iCount2 });

			++iCount;
		}
	}

}

void CUIMgr::CalcCursorPos()
{

	if (m_CurrentCursor <= 0) {
		m_CurrentCursor = 0;
		m_tCursorPos = { 245.f  , 290.f };
	}
	else {


	}
}

void CUIMgr::WeaponInventoryUpdate()
{
	m_WeponInvenList.clear();

	list<CObj*> tempList = m_inventory->GetWeaponList();
	for (auto& iter : tempList) {
		m_WeponInvenList.push_back(static_cast<CItem*>(iter)->GetImgKey());
	}
	m_currentPlrWeapon = *(m_WeponInvenList.begin());

}

void CUIMgr::StuffInventoryUpdate()
{
	m_StuffInvenList.clear();

	list<CObj*> tempList = m_inventory->GetStuffList();
	for (auto& iter : tempList) {
		m_StuffInvenList.push_back(static_cast<CItem*>(iter)->GetImgKey());
	}

}

void CUIMgr::ShopRender(HDC _hDC)
{
	m_pComponent->RenderFixedImage("UI_SHOP", _hDC, { WINCX * 0.5f, WINCY * 0.5f });

	m_pComponent->RenderFixedImage("UI_SLOTBASE", _hDC, { 500.f, 230.f });
	m_pComponent->RenderFixedImage("UI_SLOTBASE", _hDC, { 600.f, 230.f });
	m_pComponent->RenderFixedImage("UI_SLOTBASE", _hDC, { 700.f, 230.f });

	m_pComponent->RenderFixedImage("UI_SWORD", _hDC, { 495.f, 225.f });
	m_pComponent->RenderFixedImage("UI_BOW", _hDC, { 595.f, 225.f });
	m_pComponent->RenderFixedImage("UI_SPEAR", _hDC, { 695.f, 225.f });

	m_pComponent->RenderFixedImage("INVENTORY_CURSOR", _hDC, { 500.f + m_CurrentCursor * 100.f ,230.f });
	
	//옆에 뜨는 아이템 정보
	m_pComponent->RenderFixedImage("UI_COIN", _hDC, { 950.f ,320.f });
	ItemInfoRender(_hDC);
}

void CUIMgr::ItemInfoRender(HDC _hDC)
{
	TCHAR szPrice[16] = L"";

	switch (m_CurrentCursor)
	{
	case 0:
		m_pComponent->RenderFixedImage("UI_SWORD", _hDC, { 995.f, 185.f });
		m_pComponent->RenderFixedImage("UI_SWORD_INFO", _hDC, { 1000.f, 270.f });

		wsprintf(szPrice, L"%d", 50);
		TextOut(_hDC, 1000, 310, szPrice, lstrlen(szPrice));


		break;

	case 1:
		m_pComponent->RenderFixedImage("UI_BOW", _hDC, { 995.f, 185.f });
		m_pComponent->RenderFixedImage("UI_BOW_INFO", _hDC, { 1000.f, 270.f });

		wsprintf(szPrice, L"%d", 150);
		TextOut(_hDC, 1000, 310, szPrice, lstrlen(szPrice));


		break;

	case 2:
		m_pComponent->RenderFixedImage("UI_SPEAR", _hDC, { 995.f, 185.f });
		m_pComponent->RenderFixedImage("UI_SPEAR_INFO", _hDC, { 1000.f, 270.f });

		wsprintf(szPrice, L"%d", 100);
		TextOut(_hDC, 1000, 310, szPrice, lstrlen(szPrice));


		break;
	default:
		break;
	}


}

void CUIMgr::EquipRender(HDC _hDC)
{
	m_pComponent->RenderFixedImage("INVENTORY_CURSOR", _hDC, { 775.f + m_equipCursor * 172.f ,205.f });

}

void CUIMgr::UIReset()
{
	m_CurrentCursor = 0;
	m_tCursorPos = { 0.f , 0.f };

}

void CUIMgr::ResetSettingUI()
{

	m_ShopSettingList.clear();

	for (int i = 0; i < 4; ++i) {

		m_ShopSettingList.push_back({ "",0,0 });
	}

}
