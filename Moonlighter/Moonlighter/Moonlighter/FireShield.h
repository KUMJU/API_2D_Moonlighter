#pragma once
#include"Projectile.h"

class CComponent;

class CFireShield : public CProjectile
{
public:
	CFireShield();
	~CFireShield();

	void Initialize() override;
	void Update() override;
	void Render(HDC _hDC) override;
	void LateUpdate() override;
	void Release() override;

	void OnCollide(CObj* _pObj);


private:
	DWORD m_CreateTime = 0;
	CComponent* m_pComponent;
	CObj* m_pPlayerCopy;

};

