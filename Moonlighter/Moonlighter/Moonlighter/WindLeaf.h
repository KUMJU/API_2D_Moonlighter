#pragma once
#include"Monster.h"

enum class EWindLeafState {
	IDLE,
	MOVE,
	ATTACK
};

class CWindLeaf : public CMonster
{
public:
	CWindLeaf();
	~CWindLeaf();

	void Initialize();
	void Update();
	void Render(HDC _hDC);
	void LateUpdate();
	void Release();


	void OnAttacked(int _damage);
public:
	void Moving();
	void ShootBullet();

private:
	EWindLeafState m_CurrentState = EWindLeafState::IDLE;
	string m_strKeyName = "";
};

