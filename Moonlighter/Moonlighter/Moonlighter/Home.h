#pragma once
#include"Scenes.h"


class CInventory;
class CComponenet;

class CHome : public CScenes
{
public:
	CHome();
	~CHome();

	void Initialize() override;
	void Update() override;
	void Render(HDC _hDC) override;
	void LateUpdate() override;
	void Release() override;

	void KeyInput();

public:

	void ItemSetting();
	void DetectingItemSlot();
	void SpawnCustomer(int _slotNum);

	void SetItemDic();
	void CheckPrice(int _slot , CObj* _obj);

private:
	CObj* m_centerPos;

	bool m_IsShopOpen = false;
	bool m_SettingUIOn = false;

	vector<ItemViewInfo> m_itemList;
	vector<CObj*> m_CustomerList;
	vector<bool> m_SellChecker;

	CComponent* m_pComponent;

	DWORD m_dwLastDetect = 0;
	
	unordered_map<string, int> m_itemInfoDic;
};

