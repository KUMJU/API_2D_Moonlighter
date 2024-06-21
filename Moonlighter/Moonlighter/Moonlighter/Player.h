#pragma once
#include"Obj.h"
#include"KeyMgr.h"

class CInventory;

class CPlayer : public CObj
{
public:
	CPlayer();
	~CPlayer();

	void Initialize() override;
	void Update() override;
	void LateUpdate() override;
	void Render(HDC _hDC) override;
	void Release();

	void OnCollide(CObj* _pObj);
public:
	void KeyInput();
	void StateUpdate();
	void SwitchingWeapon();
	void ChangeWeapon(int _src, int _dst);
	void OnAttacked(int Damage);
	void KnockBack();

public:

	void HitRender();
	void CalcHitTime();
	void GetSkill() { m_IsHaveSkill = true; }

public:

	void PlayerRoll();
	EPlayerState GetPlayerState() { return m_ePlrState; }
	void SetProjList(list<CObj*>* _list) { m_PlrProjList = _list; }
	void SetObsList(list<CObj*>* _list) { m_PlrObstacleList = _list; }
	void AttackAction();

	void HealingHP(int _iHp);
	void SetMaxHp(int _iHp);

	int GetGold() { return m_iGold; }
	void SetGold(int _gold);
	void CheckSkillCoolTime();

	void GetNewItem(CObj* _item);
	void SellItem(string _itemKeyName, int _price);

private:

	float	m_fSpeed = 0.f;
	bool	m_IsStateChange = false;
	int		m_iHp = 100;
	int		m_iMaxHp = 100;
	int		m_iGold = 0;

	bool	m_IsSuperArmor = false;
	bool	m_IsSwim = false;
	bool	m_IsCanShield = true;

	DWORD m_HitTime = 0; //실질적으로 맞은 시간
	DWORD m_HitRenderTime = 0; //렌더 쿨타임
	DWORD m_HealingCoolTime = 0;
	DWORD m_SoundConrol = 0;
	DWORD m_ShieldCoolTime = 0;

	bool m_IsOnHit = false;
	bool m_HitRender = false;
	bool m_IsHaveSkill = false;

private:
	vector<EWeaponType> m_weaponList[2];
	CComponent* m_Animator;
	EPlayerState m_ePlrState = EPlayerState::ENUM_END;
	list<CObj*>* m_PlrProjList;
	list<CObj*>* m_PlrObstacleList;


private:
	CInventory* m_pInven;
	bool m_bIsUIOn = false;

};

