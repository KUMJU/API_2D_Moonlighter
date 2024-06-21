#pragma once
#include"Monster.h"


class CSlime : public CMonster
{
public:
	CSlime();
	~CSlime();

public:
	void Initialize();
	void Update();
	void Render(HDC _hDC);
	void LateUpdate();
	void Release();

	void OnAttacked(int _damage);

};

