#pragma once
#include"Projectile.h"
#include"Component.h"

class CSlimeBullet : public CProjectile
{
public:
	CSlimeBullet();
	~CSlimeBullet();

	void Initialize();
	void Update();
	void Render(HDC _hDC);
	void LateUpdate();
	void Release();

public:
	void SetAngle(float _angle) { m_fAngle = _angle; }

private:
	float m_fAngle = 0.f;
	CComponent* m_pComponent;

};

