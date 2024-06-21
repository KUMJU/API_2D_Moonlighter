#pragma once
#include"Tile.h"

class CBombKirby : public CTile
{
public:
	//BOMB_KIRBY
	CBombKirby();
	~CBombKirby();

	void Initialize() override;
	void Update() override;
	void Render(HDC _hDC);
	void LateUpdate();
	void Release() override;

	void OnCollide(CObj* _pObj);
	void SetList(list<CObj*>* _list1, list<CObj*>* _list2){
		m_ProjList = _list1;
		m_ObstacleList = _list2;
	}

private:
	CObj* m_pPlayerCopy;

	list<CObj*>* m_ProjList;
	list<CObj*>* m_ObstacleList;

	DWORD m_dwCreateTime;
	bool m_IsBombCreate = false;
};

