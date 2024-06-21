#pragma once
#include"Projectile.h"

class CComponent;

class CBasicProj : public CProjectile
{
public:
	CBasicProj();
	~CBasicProj();

	void Initialize();
	void Update() override;
	void Render(HDC _hDC);
	void LateUpdate();
	void Release() override;

private:
	CComponent* m_pComponent;

};

