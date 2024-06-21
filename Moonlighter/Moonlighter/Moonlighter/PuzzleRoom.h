#pragma once
#include"DungeonRoom.h"

class CPuzzleRoom : public CDungeonRoom
{
public:
	CPuzzleRoom();
	~CPuzzleRoom();

	void Initialize();
	void Update();
	void Render(HDC _hDC);
	void LateUpdate();
	void Release();


	void SettingCamera();
	
private:

	vector<int> m_AnswerList;
	vector<int> m_plrAnswerList;

	list<CObj*> m_musicBoxList; // ������ ����box ��ü�� ����ִ´�.

	int m_iAnswerNum = 0;
	bool m_IsReset = false;

};

