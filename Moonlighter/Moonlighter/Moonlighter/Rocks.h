#pragma once

#include"Tile.h"

class CRocks : public CTile
{
public:
	CRocks();
	~CRocks();

	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Render(HDC _hDC);
	virtual void LateUpdate();
	virtual void Release() override;

	void SetTargetPos(Vector _target) { m_tTarget = _target; }
	void OnCollide(CObj* _pObj);
	void SetEffectList(list<CObj*>* _list) { m_EffectList = _list; }

private:
	DWORD m_dwTime;
	int m_iImgNum;
	Vector m_tTarget;
	bool m_bIsDrop;

	list<CObj*>* m_EffectList;

	int m_iHitCount = 0;
	
};