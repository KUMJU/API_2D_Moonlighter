#pragma once
#include"Projectile.h"

enum ETentacleState {
	TS_READY,
	TS_IDLE,
	TS_DEAD
};

class CComponent;

class CTentacleRoot : public CProjectile
{

public:
	CTentacleRoot();
	~CTentacleRoot();

	void Initialize();
	void Update();
	void Render(HDC _hDC);
	void LateUpdate();
	void Release();

private:
	
	DWORD m_dwCreateTime;
	CComponent* m_pComponent;
	ETentacleState m_eState;
};

