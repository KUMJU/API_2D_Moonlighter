#pragma once
#include"Obj.h"

class CComponent;

class CEffect : public CObj
{
public:
	CEffect();
	CEffect(string _key, DWORD _time, EDirection _dir);
	~CEffect();

	void Initialize();
	void Update();
	void Render(HDC _hDC);
	void LateUpdate();
	void Release();

	void OnCollide(CObj* _pObj);
	
private:

	string m_strAnimKey = "";
	DWORD m_dwExistTime = 0;
	DWORD m_dwCreateTime = 0;

	CComponent* m_pComponent;
};

