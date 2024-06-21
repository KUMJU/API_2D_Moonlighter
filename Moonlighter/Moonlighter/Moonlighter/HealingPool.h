#pragma once
#include"Tile.h"

class CHealingPool : public CTile
{
public:
	CHealingPool();
	~CHealingPool();

	void Initialize() override;
	void Update() override;
	void Render(HDC _hDC);
	void LateUpdate();
	void Release() override;

private:
};

