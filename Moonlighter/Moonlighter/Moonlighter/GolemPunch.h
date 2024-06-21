#pragma once
#include"Projectile.h"

class CComponent;

enum EPunchState {
	
	
};

class CGolemPunch : public CProjectile
{
public:
	CGolemPunch();
	~CGolemPunch();

	void Initialize();
	void Update() override;
	void Render(HDC _hDC);
	void LateUpdate();
	void Release() override;

	void OnCollide(CObj* _pObj);
	void SetTargetPos(Vector _tPos) { 
		m_tTargetPos = _tPos; 
		m_tPosition = { m_tTargetPos.m_fX, m_tTargetPos.m_fY - 300.f };
	}
	bool GetisAtkDone() { return m_bIsAtkDone; }
	void SetEffectList(list<CObj*>* _list) { m_pEffectList = _list; }

private:

	DWORD dwTime = 0;
	bool m_bIsAtkDone = false;
	float m_fPunchSpeed = 0.f;
	Vector m_tTargetPos = { 0.f , 0.f };
	int _iAnimRow = 0;

	bool m_vib = false;
	CComponent* m_pComponent;

	list<CObj*>* m_pEffectList;

};

