#pragma once
#include"Monster.h"

class CTurret : public CMonster
{
public:
	CTurret();
	~CTurret();

	void Initialize();
	void Update();
	void Render(HDC _hDC);
	void LateUpdate();
	void Release();

public:
	void CreateBullet();
	void OnAttacked(int _damage);
private:
	int m_iCount = 0;
	string m_strKeyName = "";

	bool m_IsAtk = false;
};

