#pragma once

#include"Obj.h"

enum class EDoorState {
	CLOSE,
	OPEN,
	ENUM_END
};


class CDoor : public CObj
{
public:
	CDoor();
	~CDoor();

	void Initialize() override;
	void Update() override;
	void Render(HDC _hDC) override;
	void LateUpdate() override;
	void Release() override;

	void OnCollide(CObj* _pObj);

protected:
	EDoorState m_currentState = EDoorState::OPEN;
};

