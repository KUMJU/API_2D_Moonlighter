#pragma once
#include"Scenes.h"

class CComponent;
class CShop;

class CTown : public CScenes
{
public:
	CTown();
	~CTown();

	void Initialize() override;
	void Update() override;
	void Render(HDC _hDC) override;
	void LateUpdate() override;
	void Release() override;

private:
	CComponent* m_pComponent;
	CShop* m_pShop;
};

