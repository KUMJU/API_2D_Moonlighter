#pragma once
#include"pch.h"

class CObj;
class CInventory;

struct ItemInfo
{
	int iItemNum;
	int iPrice;
};

class CShop
{
public:
	CShop();
	~CShop();

	void Initialize();
	void Update();
	void Release();

	bool PurchaseProduct(int _itemNum);
	void SetPlayer(CObj* _plr) { m_pPlayerCopy = _plr; }

private:
	CObj* m_pPlayerCopy;
	CInventory* m_PlrInventory;

private:
	vector<ItemInfo> m_itemList;
};

