#include "Tile.h"
#include"Camera.h"

CTile::CTile() : m_pComponent(nullptr)
{
}

CTile::CTile(ETileType _tileType , float _x, float _y , float _sizeX, float _sizeY)
{
	m_pComponent = nullptr;
	m_eObjType = EObjectType::OBSTACLE;
	m_eTileType = _tileType;
	m_tPosition.m_fX = _x;
	m_tPosition.m_fY = _y;

	m_tSize.m_fX = _sizeX;
	m_tSize.m_fY = _sizeY;


	
}

CTile::~CTile()
{
	Release();
}

void CTile::Initialize()
{
	m_eObjType = EObjectType::OBSTACLE;
	m_pComponent = new CComponent;

	m_tSize.m_fX = 50.f;
	m_tSize.m_fY = 50.f;

}

void CTile::Update()
{
}

void CTile::Render(HDC _hDC)
{

	if (ETileType::WALL != m_eTileType) {
		m_pComponent->RenderImage(m_strImgKey, _hDC, m_tPosition);
	}

}

void CTile::LateUpdate()
{
}

void CTile::Release()
{
	SAFE_DELETE<CComponent*>(m_pComponent);
}

void CTile::OnCollide(CObj* _pObj)
{
}

void CTile::SetImgKeyInt(int _keyNum)
{
	m_iTileNum = _keyNum;

	switch (_keyNum)
	{
	case 1:
		m_eTileType = ETileType::WALL;
		m_tSize = { 50.f,50.f };
		break;

	case 2:
		m_strImgKey = "TILE_HOLE_LONG";
		m_eTileType = ETileType::HOLE;
		m_tSize = { 400.f,110.f };
		break;
	case 3:
		m_strImgKey = "TILE_TENT";
		m_eTileType = ETileType::COLLISION_DECO;
		m_tSize = { 250.f,200.f };
		break;
	case 4:
		m_strImgKey = "DUNGEON1_FLOOR1";
		m_eTileType = ETileType::DECO;
		m_tSize = { 0.f,0.f };
		break;
	case 5:
		m_strImgKey = "TILE_ROCK";
		m_eTileType = ETileType::COLLISION_DECO;
		m_tSize = { 70.f,40.f };
		break;
	case 6:
		m_strImgKey = "TILE_BONE";
		m_eTileType = ETileType::COLLISION_DECO;
		m_tSize = { 55.f,55.f };

		break;
	case 7:
		m_strImgKey = "TILE_SLIMETRAP";
		m_eTileType = ETileType::SLOW;
		m_tSize = { 340.f,210.f };
		break;

	case 8:
		m_strImgKey = "Dungeon_HiddenWall";
		m_eTileType = ETileType::HIDDEN_WALL;
		m_tSize = { 190.f,130.f };
		break;

	case 9:
		m_strImgKey = "BOSS1_PUNCHCRACK";
		m_eTileType = ETileType::COLLISION_DECO;
		m_tSize = { 70.f,50.f };
		break;
	case 10:
		m_strImgKey = "TILE_DIRTY";
		m_eTileType = ETileType::DECO;
		m_tSize = { 0.f,0.f };
		break;
	case 11:
		m_strImgKey = "TILE_BONE2";
		m_eTileType = ETileType::COLLISION_DECO;
		m_tSize = { 60.f,60.f };
		break;
	case 12:
		m_strImgKey = "TILE_BOOK";
		m_eTileType = ETileType::DECO;
		m_tSize = { 0.f,0.f };
		break;
	case 13:
		m_strImgKey = "HIDDENSHOP_TILE";
		m_eTileType = ETileType::DECO;
		m_tSize = { 0.f,0.f };
		break;

	default:
		break;
	}

}
