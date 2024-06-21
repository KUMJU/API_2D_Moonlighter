#pragma once
#include"Monster.h"

enum EBOSS2STATE {
	BOSS2_INIT,
	BOSS2_IDLE,
	BOSS2_ATTACK1, // ���� �Ѹ���(�Ѿ�)
	BOSS2_ATTACK2, // �̸� ��ȯ
	BOSS2_ATTACK3, // �˼�����
	BOSS2_ATTACK4, // ����
	BOSS2_DEAD
};


class CGiantBud : public CMonster
{
public:
	CGiantBud();
	~CGiantBud();

	void Initialize();
	void Update();
	void Render(HDC _hDC);
	void LateUpdate();
	void Release();

public:
	void SetObjList(list<CObj*>* _list) { m_ObjListCopy = _list; }

	//ATTACK
public:
	void ShootingSeed();
	void Jumping();
	void CalCulateSpeed();
	void TentacleAttack();
	void SpawnCutting();


	void OnAttacked(int _damage);

private:
	list<CObj*>* m_ObjListCopy;
	EBOSS2STATE m_eBossState;

	DWORD m_dwAtkTime;
	DWORD m_dWSkillTime;
	float m_fAngle = 0.f;
	int m_iAtkCount = 0;


private:
	bool m_IsAnimFin = false;
	float m_fJumpSpeed= 0.f;
	bool m_IsJumpFin = false;
	Vector m_tJumpDirVec;

	int m_PrevActNum = 0;
	int m_iInitAnim = 0;
	int m_ActCount = 0;

	vector<string> m_AnimVec[4];
};

