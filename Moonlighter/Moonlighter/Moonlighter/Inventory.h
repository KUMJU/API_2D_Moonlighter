#pragma once
#include"pch.h"

class CObj;
class CInventory
{
public:
	CInventory();
	~CInventory();

	void Initialize();
	void Update();
	void Render(HDC _hDC);
	void LateUpdate();
	void Release();

public:

	void InsertItem(CObj* _pObj); //아이템 추가
	void SellItem(string _itemKeyName);
	void FindItemByImgKey(string _itemKeyName);

	list<CObj*> GetStuffList() { return m_StuffItemList; }
	list<CObj*> GetWeaponList() { return m_WeaponItemList; }

	//1번 무기와 2번무기를 교체
	void SwitchingWeapon();
	//장비슬롯에서 무기를 아예 교체
	string ChangeWeapon(int _src, int _dst);

private:

	list<CObj*> m_StuffItemList;
	list<CObj*> m_WeaponItemList;
	
};

