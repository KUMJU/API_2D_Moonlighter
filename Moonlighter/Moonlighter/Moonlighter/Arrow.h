#pragma once
#include"Projectile.h"

class CArrow : public CProjectile
{
public:
	CArrow();
	~CArrow();

	void Initialize() override;
	void Update() override;
	void Render(HDC _hDC) override;
	void LateUpdate() override;
	void Release() override;

	void OnCollide(CObj* _pObj);

private:
	float m_fCurDistance = 0.f;
	float m_fMaxDistance = 500.f;
	int m_iAnimNum = 0;
	

};

