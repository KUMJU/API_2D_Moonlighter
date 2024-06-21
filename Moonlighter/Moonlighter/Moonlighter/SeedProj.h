#pragma once
#include"Projectile.h"

class CComponent;

class CSeedProj : public CProjectile
{
public:
	CSeedProj();
	~CSeedProj();
void Initialize();
	void Update() override;
	void Render(HDC _hDC);
	void LateUpdate();
	void Release() override;

	void OnCollide(CObj* _pObj);

public:

	void SetAngle(float _angle) { m_fAngle = _angle; }
	

private:

	float m_fAngle;
	CComponent* m_pComponent;

};

