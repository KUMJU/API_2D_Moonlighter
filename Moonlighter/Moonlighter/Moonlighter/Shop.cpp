#include "Shop.h"
#include"Obj.h"
#include"Inventory.h"
#include"Player.h"
#include"Item.h"

CShop::CShop() : m_pPlayerCopy(nullptr), m_PlrInventory(nullptr), m_itemList()
{
}

CShop::~CShop()
{
}

void CShop::Initialize()
{
	m_itemList.reserve(3);

	m_itemList.push_back({ 0,50 });
	m_itemList.push_back({ 2,150 });
	m_itemList.push_back({ 3,100 });

}

void CShop::Update()
{
}

void CShop::Release()
{
}

bool CShop::PurchaseProduct(int _itemNum)
{
	int currentPrice = m_itemList[_itemNum].iPrice;
	
	if (dynamic_cast<CPlayer*>(m_pPlayerCopy)->GetGold() >= currentPrice) {
		dynamic_cast<CPlayer*>(m_pPlayerCopy)->SetGold(currentPrice * -1);

		CObj* newItem = new CItem;
		dynamic_cast<CItem*>(newItem)->SetItemInfo(_itemNum);
		dynamic_cast<CPlayer*>(m_pPlayerCopy)->GetNewItem(newItem);

		return true;
	}
	else {
		return false;

	}

	return false;
}
