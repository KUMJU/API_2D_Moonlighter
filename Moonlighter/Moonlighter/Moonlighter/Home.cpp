#include "Home.h"
#include"Player.h"
#include"Customer.h"
#include"MapCenter.h"
#include"Component.h"
#include"KeyMgr.h"
#include"GameMgr.h"
#include"UIMgr.h"
#include"SoundMgr.h"
#include"SceneDoor.h"



CHome::CHome() : m_centerPos(nullptr), m_pComponent(nullptr)
{
}

CHome::~CHome()
{
	Release();
}

void CHome::Initialize()
{
	CScenes::Initialize();
	m_centerPos = new CMapCenter;
	m_centerPos->SetPosition({WINCX*0.5f,WINCY*0.5f});
	m_centerPos->Initialize();

	CCamera::GetInstance()->SetCameraMode(2);
	CCamera::GetInstance()->SetTarget(m_centerPos);


	CObj* tempDoor2 = new CSceneDoor;
	tempDoor2->SetPosition({ 800.f , 200.f });
	dynamic_cast<CSceneDoor*>(tempDoor2)->SetNextScene(ESceneType::VILLAGE);
	tempDoor2->Initialize();
	m_objLists[(unsigned int)EObjectType::DOOR].push_back(tempDoor2);

	m_itemList.reserve(4);
	m_SellChecker.reserve(4);
	m_CustomerList.reserve(4);

	for (int i = 0; i < 4; ++i) {
		m_itemList.push_back({ "",0,0});
		m_CustomerList.push_back(nullptr);
		m_SellChecker.push_back(false);
	}

	SetItemDic();
	m_objLists[static_cast<unsigned int>(EObjectType::PLAYER)].front()->SetPosition({ WINCX * 0.5f,WINCY * 0.5f + 150.f });
	//CUIMgr::GetInstance()->StuffInventoryUpdate();

	CSoundMgr::Get_Instance()->StopAll();
	CSoundMgr::Get_Instance()->PlayBGM(L"shop_day_open.wav", 1.f);

}

void CHome::Update()
{
	//가게 오픈 상태
	if (m_IsShopOpen) {

		if (m_dwLastDetect + 8000 <= (DWORD)GetTickCount64()) {
			DetectingItemSlot();
			m_dwLastDetect = (DWORD)GetTickCount64();
		}

	}

	KeyInput();
	CScenes::Update();

}

void CHome::Render(HDC _hDC)
{
	m_pComponent->RenderImage("HOMESHOP", _hDC, { WINCX*0.5f, WINCY*0.5f });
	
	int iCount = 0;
	for (auto& iter : m_itemList) {
		if("" != iter.strKeyName)
			m_pComponent->RenderImage(iter.strKeyName, _hDC, { 575.f + iCount * 45.f, 355.f });

		++iCount;
	}

	CScenes::Render(_hDC);

	m_pComponent->RenderImageGetRow("HOMESHOP_STATE", _hDC, { WINCX * 0.5f, 50.f }, m_IsShopOpen);

}

void CHome::LateUpdate()
{
	for (int i = 0; i < 4; ++i) {
		if (nullptr != m_CustomerList[i]) {
			if (true == static_cast<CCustomer*>(m_CustomerList[i])->GetProcessDone()) {
				m_CustomerList[i] = nullptr;
				
				if (true == m_SellChecker[i]) {
					m_itemList[i].strKeyName = "";
					m_itemList[i].iPrice = 0;
					CUIMgr::GetInstance()->ResetOneSlot(i);
				}
			}
		}
	}


	CScenes::LateUpdate();
}

void CHome::Release()
{
	CScenes::Release();
	SAFE_DELETE<CObj*>(m_centerPos);
}

void CHome::KeyInput()
{
	if (m_IsShopOpen) {
		
		if (CKeyMgr::GetInstance()->Key_Down('W')) {
			CSoundMgr::Get_Instance()->StopSound(BOSS_EFFECT);
			CSoundMgr::Get_Instance()->PlaySound(L"shop_door_closing.wav", BOSS_EFFECT, 1.f);
			m_IsShopOpen = false;
		}

	}
	else {

		if (CKeyMgr::GetInstance()->Key_Down('Q')) {
			m_SettingUIOn = !m_SettingUIOn;
			CUIMgr::GetInstance()->HomeShopSwitch();

			if (false == m_SettingUIOn) {
				m_itemList = CUIMgr::GetInstance()->GetSellList();
			}

		}

		if (CKeyMgr::GetInstance()->Key_Down('W')) {
			CSoundMgr::Get_Instance()->StopSound(BOSS_EFFECT);
			CSoundMgr::Get_Instance()->PlaySound(L"shop_door_opening.wav", BOSS_EFFECT, 1.f);
			m_IsShopOpen = true;
		}

	}


}

void CHome::ItemSetting()
{
}

void CHome::DetectingItemSlot()
{

	for (int i = 0; i < 4; ++i) {
		if (m_itemList[i].strKeyName != "") {
			if (m_CustomerList[i] == nullptr) {
				SpawnCustomer(i);
				break;
			}
		}
	}
}

void CHome::SpawnCustomer(int _slotNum)
{

	CObj* newCustomer = new CCustomer;
	newCustomer->SetPosition({750.f ,560.f});
	m_CustomerList[_slotNum] = newCustomer;
	static_cast<CCustomer*>(newCustomer)->SetSlotNum(_slotNum);
	static_cast<CCustomer*>(newCustomer)->SetItemInfo(m_itemList[_slotNum]);

	CheckPrice(_slotNum, newCustomer);
	newCustomer->Initialize();
	m_objLists[static_cast<unsigned int>(EObjectType::OBSTACLE)].push_back(newCustomer);

	CSoundMgr::Get_Instance()->StopSound(MONSTER_EFFECT);
	CSoundMgr::Get_Instance()->PlaySound(L"shop_visitor_enters_shop_bell.wav", MONSTER_EFFECT, 1.f);
	
}

void CHome::SetItemDic()
{
	m_itemInfoDic.insert({"ITEM_STEEL", 70});
	m_itemInfoDic.insert({"ITEM_CORE", 100});
}

void CHome::CheckPrice(int _slot, CObj* _obj)
{
	int iCurPrice = m_itemList[_slot].iPrice;

	auto iter = m_itemInfoDic.find(m_itemList[_slot].strKeyName);
	int OriginPrice = iter->second;

	if (iCurPrice <= OriginPrice * 1.2 && iCurPrice >= OriginPrice * 0.8) {
		m_SellChecker[_slot] = true;
		static_cast<CCustomer*>(_obj)->SetEmotion(1);


	}
	else if (iCurPrice < OriginPrice * 0.8) {
		m_SellChecker[_slot] = true;
		static_cast<CCustomer*>(_obj)->SetEmotion(0);

	}
	else {
		m_SellChecker[_slot] = false;
		static_cast<CCustomer*>(_obj)->SetEmotion(2);
	}
}
