#pragma once
#include"Obj.h"

class CProjectile : public CObj
{
public:
	CProjectile();
	virtual ~CProjectile();

	void Initialize() override;
	void Update() override;
	void Render(HDC _hDC) override;
	void LateUpdate() override;
	void Release() override;

	void SetDirection(EDirection _dir) {
		m_eDir = _dir;
	}

	void OnCollide(CObj* _pObj);
	int GetDamage() { return m_iDamage; }
	void SetDamage(int _damage) {m_iDamage = _damage;}
	void SetAnimKey(string _keyName) { m_strKeyName = _keyName; }

	EProjectileType GetProjType() { return m_eProjType; }

protected:
	int m_iDamage = 0;
	string m_strKeyName = "";
	float m_fSpeed = 0.f;
	EDirection m_eDir = EDirection::ENUM_END;
	EProjectileType m_eProjType = EProjectileType::BASIC;


};

