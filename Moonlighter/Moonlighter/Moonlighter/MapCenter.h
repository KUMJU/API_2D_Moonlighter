#pragma once
#include"Obj.h"

class CMapCenter : public CObj
{
public:
	CMapCenter();
	~CMapCenter();

	virtual void Initialize();
	virtual void Update();
	virtual void Render(HDC _hDC);
	virtual void LateUpdate();
	virtual void Release();

	void OnCollide(CObj* _pObj);
};

