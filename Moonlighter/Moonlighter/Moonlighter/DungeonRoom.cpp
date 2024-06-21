#include "DungeonRoom.h"
#include"Tile.h"

CDungeonRoom::CDungeonRoom() : m_ObjectList(nullptr) , m_path(L"")
{
}

CDungeonRoom::CDungeonRoom(const TCHAR* _path) : m_ObjectList(nullptr), m_path(_path)
{
}

CDungeonRoom::~CDungeonRoom()
{
	Release();
}

void CDungeonRoom::Initialize()
{
	LoadTile(m_path);
	m_IsInitDone = true;
}

void CDungeonRoom::Update()
{
}

void CDungeonRoom::Render(HDC _hDC)
{

}

void CDungeonRoom::LateUpdate()
{
}

void CDungeonRoom::Release()
{

}


void CDungeonRoom::LoadTile(const TCHAR* _path)
{

	HANDLE		hFile = CreateFile(_path,
		GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	DWORD	dwByte(0);
	TileInfo tInfo;
	int iTileNum(0);


	Vector RenderVec = { m_CenterPos->GetPosition().m_fX- WINCX*0.5f
						, m_CenterPos->GetPosition().m_fY - WINCY * 0.5f };


	while (true)
	{
		ReadFile(hFile, &tInfo, sizeof(TileInfo), &dwByte, nullptr);

		if (0 == dwByte)
			break;

		CObj* pObj = new CTile;
		pObj->Initialize();
		pObj->SetPosition({ RenderVec.m_fX+ tInfo.fX ,RenderVec.m_fY + tInfo.fY });
		dynamic_cast<CTile*>(pObj)->SetImgKeyInt(tInfo.iTileNum);
		m_ObjectList[(unsigned int)EObjectType::OBSTACLE].push_back(pObj);
	}

	CloseHandle(hFile);
}

void CDungeonRoom::SettingCamera()
{
}

