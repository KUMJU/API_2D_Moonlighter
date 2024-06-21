#pragma once
#include"Monster.h"

enum EGolemState {
	IDLE,
	ATTACK
};


class CGolemSoldier : public CMonster
{

public:

	CGolemSoldier();
	~CGolemSoldier();

	void Initialize();
	void Update();
	void Render(HDC _hDC);
	void LateUpdate();
	void Release();
	void OnAttacked(int _damage);

private:
	EGolemState m_eState = IDLE;

};

