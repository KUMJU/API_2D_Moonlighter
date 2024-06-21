#pragma once
#include"Projectile.h"

class CSpear: public CProjectile
{
public:
	CSpear();
	~CSpear();

	void Initialize() override;
	void Update() override;
	void Render(HDC _hDC) override;
	void LateUpdate() override;
	void Release() override;

private:
	DWORD dwTime = 0;
};

