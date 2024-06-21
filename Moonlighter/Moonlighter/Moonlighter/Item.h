#pragma once

#include"Obj.h"

class CComponent;

class CItem : public CObj
{
public:
	CItem();
	~CItem();

	void Initialize();
	void Update();
	void Render(HDC _hDC);
	void LateUpdate();
	void Release();

public:

	void SetItemInfo(int _typeNum);
	void OnCollide(CObj* _pObj);
	EItemType GetItemType() { return m_eItemType; }
	bool GetIsVisible() { return m_IsVisible; }
	void SetVisible() { m_IsVisible = !m_IsVisible; }
	string GetImgKey() { return m_strImgKey; }

private:
	string m_strImgKey = "";
	string m_strItemName = "";
	EItemType m_eItemType = EItemType::ENUM_END;
	CComponent* m_pComponent;


	int iItemKey = 0;
	int iCapacity = 0;
	bool m_IsVisible = true;

	int m_iRendCount = 0;
	int m_iRendDir = 1;
};

