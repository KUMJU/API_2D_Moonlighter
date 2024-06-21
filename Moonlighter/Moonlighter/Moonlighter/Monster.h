#pragma once
#include"Obj.h"

class CComponent;

class CMonster : public CObj
{
public:
	CMonster();	
	virtual ~CMonster();


	virtual void Initialize();
	virtual void Update() = 0;
	virtual void Render();
	virtual void LateUpdate();
	virtual void Release();
	void OnCollide(CObj* _pObj);


public:
	virtual void OnAttacked(int _damage);
	void PlayerDetect();
	void FollowPlayer();
	float GetPlayerDistance();
	void SetProjList(list<CObj*>* _pList) { m_pProjList = _pList; }
	void SetItemList(list<CObj*>* _pList) { m_pItemList = _pList; }
	void SetEffectList(list<CObj*>* _pList) { m_pEffectList = _pList; }
	void CheckHitTime();
	void CheckHitRender();
	void KnockBack();
	void SetHitEffect();
	int GetDamage() { return m_iDamage; }


protected:
	int m_iHp= 0;
	int m_iMaxHP = 0;
	int m_iDamage = 0;
	float m_fSpeed = 0.f;

	DWORD m_HitTime;

	EDirection m_eDir = EDirection::ENUM_END;
	DWORD m_HitRenderTime = 0;
	DWORD m_dwAttackTime = 0;
	bool m_IsOnHit = false; //맞았는지 안맞았는지 여부
	bool m_HitRender = false; //Render때 Blink를 위해

	CComponent* m_pComponent;
	CObj* m_pPlayerCopy;
	list<CObj*>* m_pProjList;
	list<CObj*>* m_pItemList;
	list<CObj*>* m_pEffectList;

	int m_iDropItemNum = 0;

};

