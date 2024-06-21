#include "TileEditor.h"
#include"KeyMgr.h"
#include"ResourceMgr.h"
#include"Tile.h"

CTileEditor::CTileEditor()
{
}

CTileEditor::~CTileEditor()
{
	Release();
}

void CTileEditor::Initialize()
{
}

void CTileEditor::Update()
{
	KeyInput();
}

void CTileEditor::Render(HDC _hDC)
{
	string KeyName = "BackGround1";
	int setXpos = 60;

	if (2 == m_iRoomType) {
		KeyName = "BackGround_Boss1";
		setXpos = 0;
	}

	//배경출력
	AnimInfo tempInfo = CResourceMgr::GetInstance()->FindRes(KeyName)->GetResInfo();

	GdiTransparentBlt(_hDC,
		0,
		0,
		tempInfo.iSizeX,
		tempInfo.iSizeY,
		CResourceMgr::GetInstance()->FindRes(KeyName)->GetMemDC(),
		0,
		0,
		tempInfo.iSizeX,
		tempInfo.iSizeY,
		RGB(0, 0, 0));
	
	for (auto& iter : m_tileList) {
		iter->Render(_hDC);

	}

	//그리드 출력
	for (int i = 0; i <= WINCY; ) {
		MoveToEx(_hDC, 0, i, nullptr);
		LineTo(_hDC, WINCX, i);
		i += 50;
	}

	for (int i = 0; i <= WINCX; ) {
		MoveToEx(_hDC, i ,0, nullptr);
		LineTo(_hDC, i, WINCY);
		i += 50;
	}

}

void CTileEditor::Release()
{
	for (auto& iter : m_tileList) {
		SAFE_DELETE<CObj*>(iter);
	}
	m_tileList.clear();

}

void CTileEditor::KeyInput()
{
	//BackGroundChange
	if (CKeyMgr::GetInstance()->Key_Down(VK_F1)) {
		m_iRoomType = 1;
	}

	if (CKeyMgr::GetInstance()->Key_Down(VK_F2)) {
		m_iRoomType = 2;
	}

	//타일생성
	if (CKeyMgr::GetInstance()->Key_Down(VK_LBUTTON))
	{
		POINT pt{};
		GetCursorPos(&pt);
		ScreenToClient(m_handler, &pt);

		CObj* myTile = new CTile;
		myTile->Initialize();

		float _fx = (float)(pt.x - (pt.x % 50));
		float _fy = (float)(pt.y - (pt.y % 50));
		myTile->SetPosition({ _fx,_fy });
		dynamic_cast<CTile*>(myTile)->SetImgKeyInt(m_iTileNum);
		m_tileList.push_back(myTile);
	}

	if (CKeyMgr::GetInstance()->Key_Down(VK_RBUTTON))
	{
		m_tileList.pop_back();
	}

	//타일이미지 변경

	if (CKeyMgr::GetInstance()->Key_Down(VK_RIGHT)) {
		++m_iTileNum;
	}

	if (CKeyMgr::GetInstance()->Key_Down(VK_LEFT)) {
		--m_iTileNum;
	}

	//로드 & 세이브
	if (CKeyMgr::GetInstance()->Key_Down('L')) {
		Load_Tile();
	}

	if (CKeyMgr::GetInstance()->Key_Down('S')) {
		Save_Tile();
	}
}

void CTileEditor::Save_Tile()
{

	HANDLE		hFile = CreateFile(L"../Data/Dungeon1_1.dat", GENERIC_WRITE, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	TileInfo	tTileInfo = {};
	DWORD	dwByte(0);

	for (auto& iter : m_tileList)
	{
		tTileInfo.fX = iter->GetPosition().m_fX;
		tTileInfo.fY = iter->GetPosition().m_fY;
		tTileInfo.iTileNum = dynamic_cast<CTile*>(iter)->GetTileNum();
			//GetTileNum
		WriteFile(hFile, &(tTileInfo), sizeof(TileInfo), &dwByte, nullptr);
	}

	CloseHandle(hFile);
}

void CTileEditor::Load_Tile()
{
	HANDLE		hFile = CreateFile(L"../Data/Dungeon1_1.dat",
		GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	DWORD	dwByte(0);
	TileInfo tInfo;
	int iTileNum(0);

	Release();

	while (true)
	{
		ReadFile(hFile, &tInfo, sizeof(TileInfo), &dwByte, nullptr);

		if (0 == dwByte)
			break;

		CObj* pObj = new CTile;
		pObj->Initialize();
		pObj->SetPosition({ tInfo.fX, tInfo.fY });
		dynamic_cast<CTile*>(pObj)->SetImgKeyInt(tInfo.iTileNum);
		m_tileList.push_back(pObj);
	}

	CloseHandle(hFile);
}

void CTileEditor::MakeNewTile(Vector _tilePos)
{
}

void CTileEditor::MakeCollisionTile()
{


}

