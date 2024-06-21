#pragma once
#include "Define.h"
#include "Enums.h"
#include "Types.h"
#include"Component.h"

class CObj abstract
{
public:
	CObj();
	virtual ~CObj();

	virtual void Initialize()		=0;
	virtual void Update()			=0;
	virtual void Render(HDC _hDC)	=0;
	virtual void LateUpdate()		=0;
	virtual void Release()			=0;

public:
	virtual void OnCollide(CObj* _pObj)	=0;
	virtual void OnAttacked(int _damage);

	EObjectType GetObjType() {return m_eObjType;}
	EDirection GetDir() { return m_eDir; }
	Vector GetPosition() { return m_tPosition; }
 	void SetPosition(Vector _newPos) { m_tPosition = _newPos; }
	
	Vector GetSize() { return m_tSize; }
	bool GetIsDead() { return m_bIsDead; }
	void SetIsDead() { m_bIsDead = true; }

	int GetRendNum() { return m_iRendNum; }
	float GetBottomPos() { return m_tPosition.m_fY + m_tSize.m_fY * 0.5f; }

protected:

	Vector m_tPosition;
	Vector m_tSize;
	bool m_bIsDead = false;

	RENDERID m_iRendNum = BACKGROUND;

	EDirection m_eDir = EDirection::ENUM_END;
	EObjectType m_eObjType = EObjectType::ENUM_END;

};

