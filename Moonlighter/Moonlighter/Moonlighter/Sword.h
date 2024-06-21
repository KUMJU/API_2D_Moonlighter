#pragma once

#include"Projectile.h"

class CSword: public CProjectile
{
public:
	CSword();
	~CSword();

	void Initialize() override;
	void Update() override;
	void Render(HDC _hDC) override;
	void LateUpdate() override;
	void Release() override;

private:
	DWORD dwTime = 0;
};

