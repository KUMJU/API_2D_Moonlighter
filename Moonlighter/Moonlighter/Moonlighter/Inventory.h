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

	void InsertItem(CObj* _pObj); //������ �߰�
	void SellItem(string _itemKeyName);
	void FindItemByImgKey(string _itemKeyName);

	list<CObj*> GetStuffList() { return m_StuffItemList; }
	list<CObj*> GetWeaponList() { return m_WeaponItemList; }

	//1�� ����� 2�����⸦ ��ü
	void SwitchingWeapon();
	//��񽽷Կ��� ���⸦ �ƿ� ��ü
	string ChangeWeapon(int _src, int _dst);

private:

	list<CObj*> m_StuffItemList;
	list<CObj*> m_WeaponItemList;
	
};

