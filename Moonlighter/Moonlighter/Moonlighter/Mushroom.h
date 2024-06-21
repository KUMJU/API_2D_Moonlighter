#pragma once
#include"Monster.h"

enum class EMushState {
	STUN,
	PREPARE,
	ATTACK,
	ENUM_END
};


class CMushroom : public CMonster
{
public:

	CMushroom();
	~CMushroom();

	void Initialize();
	void Update();
	void Render(HDC _hDC);
	void LateUpdate();
	void Release();

	void OnAttacked(int _damage);

public:
	void OnCollide(CObj* _pObj);
	void SetNewAngle();

private:
	int m_iCount = 0;
	Vector DirVec;
	bool m_isSetDir = false;
	DWORD m_dwCrashTime = 0;

	EMushState m_eCurrentState = EMushState::ENUM_END;
};

