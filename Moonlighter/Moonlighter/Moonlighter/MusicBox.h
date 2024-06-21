#pragma once
#include"Tile.h"

class CMusicBox : public CTile
{
public:
	CMusicBox();
	~CMusicBox();


	void Initialize() override;
	void Update() override;
	void Render(HDC _hDC);
	void LateUpdate();
	void Release() override;

	void OnCollide(CObj* _pObj);
	void KeyInput();

	void SetBoxType(int _num) { m_iBoxTypeNum = _num; }
public:
	void DetectedPlayer();
	bool GetHitDone() { return m_isHitDone; }
	void SetReset() { m_isHitDone = false; m_animFin = false; }
	int GetTypeNum() { return m_iBoxTypeNum; }

private:

	CObj* m_pPlayerCopy;
	bool m_IsPromptOn = false;

	int m_iBoxTypeNum = 0;
	bool m_isHitDone = false;
	bool m_animFin = false;
};

