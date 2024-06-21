#pragma once
#include"Monster.h"

class CCutting : public CMonster
{
public:
	CCutting();
	~CCutting();

	void Initialize();
	void Update();
	void Render(HDC _hDC);
	void LateUpdate();
	void Release();

public:
	float GetAngle();

private:
	bool m_IsReady = false;
};

