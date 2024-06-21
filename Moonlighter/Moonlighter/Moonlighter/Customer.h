#pragma once
#include"Obj.h"

class CComponent;

enum class CustomerState {
	IDLE,
	WALK,
	BUY,
	FIN,
	ENUM_END
};

class CCustomer : public CObj
{
public:
	CCustomer();
	CCustomer(int _slotNum);
	~CCustomer();

	void Initialize() override;
	void Update() override;
	void LateUpdate() override;
	void Render(HDC _hDC) override;
	void Release();

	void OnCollide(CObj* _pObj);

public:
	
	int GetSlotNum() { return m_iSlotNum; }
	void SetSlotNum(int _num) { m_iSlotNum = _num; }
	void SetTargetPos(Vector _pos) { m_TargetPos = _pos; }
	void SetItemInfo(ItemViewInfo _info) { m_itemInfo = _info; }
	bool GetProcessDone() { return m_IsProcessDone; }
	void SetEmotion(int _num) { m_iEmotion = _num; }


private:
	Vector m_TargetPos;
	Vector m_DirVec;
	int m_iSlotNum;
	int m_iEmotion; // ±âºÐ state
	float m_fSpeed = 0.f;
	CustomerState m_eCurrentState;
	CObj* m_pPlayer;

	CComponent* m_pComponent;

	DWORD m_CreateTime = 0;
	ItemViewInfo m_itemInfo;
	float m_Time = 0.f;
	int m_AnimNum = 0;

	bool m_IsProcessDone = false;

};

