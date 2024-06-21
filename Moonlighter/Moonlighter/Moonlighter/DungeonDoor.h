#pragma once
#include"Door.h"

class CComponent;

class CDungeonDoor : public CDoor
{
public:
	CDungeonDoor();
	CDungeonDoor(EDirection _dir, int _roomNum, int _dungeonNum);
	~CDungeonDoor();

	void Initialize() override;
	void Update() override;
	void Render(HDC _hDC) override;
	void LateUpdate() override;
	void Release() override;

	void OnCollide(CObj* _pObj);


public:

	void SetDoorClose() { m_currentState = EDoorState::CLOSE; m_IsAimFin = false; };
	void SetDoorOpen() { 
		m_currentState = EDoorState::OPEN; 
		m_IsAimFin = false;
		SetSound();
	};
	void SetRoomNumber(int _num) { m_iNextRoomNum = _num; }
	void SetSound();


	bool GetPlrTouch() { return m_IsPlrTouch; }
	int GetNextRoomNum() { return m_iNextRoomNum; }

private:
	bool m_IsAimFin = false;
	bool m_IsPlrTouch = false;
	int m_iNextRoomNum = 0;
	int m_iDungeonNum = 0;
	EDirection m_eDir = EDirection::ENUM_END;

	CComponent* m_pComponent;
};

