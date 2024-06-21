#include "Inventory.h"
#include"Define.h"
#include"Item.h"
#include"UIMgr.h"

CInventory::CInventory()
{
}

CInventory::~CInventory()
{
	Release();
}

void CInventory::Initialize()
{
	CObj* newWeapon1 = new CItem;
	dynamic_cast<CItem*>(newWeapon1)->SetItemInfo(0);
	m_WeaponItemList.push_back(newWeapon1);

	CObj* newWeapon2 = new CItem;
	dynamic_cast<CItem*>(newWeapon2)->SetItemInfo(2);
	m_WeaponItemList.push_back(newWeapon2);



}                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                           

void CInventory::Update()
{
}

void CInventory::Render(HDC _hDC)
{
}

void CInventory::LateUpdate()
{
}

void CInventory::Release()
{
	for (auto& iter : m_StuffItemList) {
		SAFE_DELETE<CObj*>(iter);
	}

	for (auto& iter : m_WeaponItemList) {
		SAFE_DELETE<CObj*>(iter);
	}
}

void CInventory::InsertItem(CObj* _pObj)
{
	if (EItemType::STUFF == dynamic_cast<CItem*>(_pObj)->GetItemType()) {
		m_StuffItemList.push_back(_pObj);
		CUIMgr::GetInstance()->StuffInventoryUpdate();

	}
	else {
		m_WeaponItemList.push_back(_pObj);
		CUIMgr::GetInstance()->WeaponInventoryUpdate();

	}

	 
}

void CInventory::SellItem(string _itemKeyName)
{

	auto iter = m_StuffItemList.begin();

	//리스트 삭제
	for (iter; iter != m_StuffItemList.end(); ++iter) {
		if (_itemKeyName == static_cast<CItem*>(*iter)->GetImgKey()) {
			SAFE_DELETE<CObj*>(*iter);
			iter = m_StuffItemList.erase(iter);
			break;
		}
	}

	CUIMgr::GetInstance()->StuffInventoryUpdate();

}

void CInventory::FindItemByImgKey(string _itemKeyName)
{


}

void CInventory::SwitchingWeapon()
{
	iter_swap(m_WeaponItemList.begin(), ++m_WeaponItemList.begin());
	CUIMgr::GetInstance()->WeaponInventoryUpdate();
}

string CInventory::ChangeWeapon(int _src, int _dst)
{

	auto iter1 = m_WeaponItemList.begin();

	if (1 == _src) {
		++iter1;
	}

	auto iter2 = m_WeaponItemList.begin();

	for (int i = 0; i < _dst; ++i) {
		++iter2;
	}

	string StrKeyName = dynamic_cast<CItem*>(*iter2)->GetImgKey();


	iter_swap(iter1, iter2);
	CUIMgr::GetInstance()->WeaponInventoryUpdate();

	return StrKeyName;
}
