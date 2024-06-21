#pragma once
#include"Tile.h"

class CObj;

class CNPC : public CTile
{
public:
	CNPC();
	~CNPC();

	void Initialize() override;
	void Update() override;
	void Render(HDC _hDC);
	void LateUpdate();
	void Release() override;

	void OnCollide(CObj* _pObj);
	void KeyInput();
	void SetNpcType(int _num) { m_iNpcNum = _num; }

public:
	void DetectedPlayer();

private:
	CObj* m_pPlayerCopy;
	bool m_IsPromptOn = false;
	int m_iNpcNum = 0;
};

