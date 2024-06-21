#pragma once
#include"Monster.h"

enum EBoss1State {
	INIT,
	IDLE,
	ATTACK1,
	ATTACK2,
	ATTACK3,
	RECOVER,
	DEAD
};


class CGolemKing : public CMonster
{
public:
	CGolemKing();
	~CGolemKing();

	void Initialize();
	void Update();
	void Render(HDC _hDC);
	void LateUpdate();
	void Release();

public:

	void OnAttacked(int _damage);
	void OnCollide(CObj* _pObj);
	void SetObjList(list<CObj*>* _list) { m_ObjListCopy = _list; }
	void SetShadowPosition();

//Attack
public:
	void PunchAtk(); //ATTACK1
	void SpawnRock(); //ATTACK2
	void ShootingSlime(); //ATTACK3

private:
	bool m_bIsAnimFin = false; //애니메이션 종료 이후 실질적 공격 시작
	bool m_bIsOnAtk = false; //공격중 여부판단-> 공격 중일시 추가 공격을 하지 않음
	bool m_bIsNoArm = false;
	EBoss1State m_eBossState= IDLE;

	CObj* m_PunchHand;
	list<CObj*>* m_ObjListCopy;

	Vector m_PunchPos = { 0.f, 0.f };
	int	m_iPunchCount = 0;
	DWORD dwPunchTime = 0;

	float m_fShadowSize = 0.05f;

	 int m_iAtkNum = 0;

};