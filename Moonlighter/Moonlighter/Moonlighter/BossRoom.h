#pragma once
#include"DungeonRoom.h"

class CBossRoom : public CDungeonRoom
{
public:

	CBossRoom();
	~CBossRoom();

	void Initialize();
	void Update();
	void Render(HDC _hDC);
	void LateUpdate();
	void Release();

public:

	void CreateRoomCollision();

};

