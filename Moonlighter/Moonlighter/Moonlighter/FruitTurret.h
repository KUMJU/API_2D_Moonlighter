#pragma once
#include"Monster.h"

enum class EFruitState {
	IDLE,
	ATTACK
};

class CFruitTurret : public CMonster
{
public:
	CFruitTurret();
	~CFruitTurret();

	void Initialize();
	void Update();
	void Render(HDC _hDC);
	void LateUpdate();
	void Release();
	
public:
	void WalkDir();
	void ShootBullet();
	void SetDirNum(int _num);

	void OnAttacked(int _damage);

private:

	string m_strKeyName= "";
	int m_iAtkiCount= 0;
	EFruitState m_currentState = EFruitState::IDLE;
};

