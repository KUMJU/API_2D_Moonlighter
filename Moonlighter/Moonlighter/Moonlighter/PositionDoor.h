#pragma once
#include"Door.h"

class CPositionDoor : public CDoor
{
public:
	CPositionDoor();
	~CPositionDoor();

	void Initialize() override;
	void Update() override;
	void Render(HDC _hDC) override;
	void LateUpdate() override;
	void Release() override;


	void OnCollide(CObj* _pObj);

public:
	void SetWarpPos(Vector _pos) { m_WarpPos = _pos; }
	Vector GetWarpPos() { return m_WarpPos; }
	void SetWarpMapSize(RECT _rect) { m_WarpMapsize = _rect; }

private:
	Vector m_WarpPos;
	RECT	m_WarpMapsize;

};

