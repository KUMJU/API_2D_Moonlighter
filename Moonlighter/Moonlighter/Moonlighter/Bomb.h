#pragma once
#include"Projectile.h"

class CComponent;

class CBomb : public CProjectile
{
public:
	CBomb();
	~CBomb();

	void Initialize() override;
	void Update() override;
	void Render(HDC _hDC) override;
	void LateUpdate() override;
	void Release() override;

	void OnCollide(CObj* _pObj);

private:
	CComponent* m_pComponent;

};

