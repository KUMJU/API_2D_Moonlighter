#pragma once
#include"Tile.h"

class CDisplayItem : public CTile 
{
public:
	CDisplayItem();
	~CDisplayItem();

	void Initialize() override;
	void Update() override;
	void Render(HDC _hDC);
	void LateUpdate();
	void Release() override;

	void OnCollide(CObj* _pObj);
	void KeyInput();
	void SetItemNum(int _num) { m_iItemNum = _num; }

public:
	void DetectedPlayer();
	void ItemActive();

private:
	CObj* m_pPlayerCopy;
	bool m_IsPromptOn = false;
	int m_iItemNum= 0;
	int m_iPrice = 0;
};

