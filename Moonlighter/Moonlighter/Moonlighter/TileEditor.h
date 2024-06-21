#pragma once
#include"Scenes.h"

class CTileEditor : public CScenes
{
public:
	CTileEditor();
	~CTileEditor();

	void Initialize();
	void Update();
	void Render(HDC _hDC);
	void Release();

	void KeyInput();
	void Save_Tile();
	void Load_Tile();

	void SetHandler(HWND _newHandler) { m_handler = _newHandler; };
	void MakeNewTile(Vector _tilePos);
	void MakeCollisionTile();

private:
	int m_iRoomType =1;
	int m_iCurrentMod = 1;
	//1= collision_mod 2 = deco_mod
	int m_iTileNum = 1;

	list<CObj*> m_tileList;
	HWND m_handler{};






};

