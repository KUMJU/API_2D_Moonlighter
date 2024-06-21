#include "GameMgr.h"
#include"Define.h"
#include"Obj.h"

CGameMgr* CGameMgr::m_pInstance = nullptr;

CGameMgr::CGameMgr() :m_Player(nullptr)
{
}

CGameMgr::~CGameMgr()
{
	Release();
}

void CGameMgr::Release()
{
	SAFE_DELETE<CObj*>(m_Player);
}
