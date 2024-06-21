#pragma once
#include"Obj.h"

class CCollisionMgr
{
private:
	CCollisionMgr();
	~CCollisionMgr();

public:

	static CCollisionMgr* GetInstance()
	{
		if (!m_pInstance)
		{
			m_pInstance = new CCollisionMgr();
		}

		return m_pInstance;
	}
	static void DestroyInstance()
	{
		if (m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}
	
public:
	static void	CollisionRect(list<CObj*> _srcList, list<CObj*> _dstList);
	static void	CollisionRectEx(list<CObj*> _srcList, list<CObj*> _dstList);
	static bool	CheckRect(CObj* _pSrc, CObj* _pDst, float* pX, float* pY);

	static bool	CheckSphere(CObj* _pSrc, CObj* _pDst);
	static void CollisionSphere(list<CObj*> _srcList, list<CObj*> _dstList);

	static RECT GetRect(CObj* _pSrc);
	static void PlrObstacleCollision(list<CObj*> _srcList, list<CObj*> _dstList);
	static void WallCollision(CObj* src, CObj* dst, float m_fX, float m_fY);
	static void PlrMonProjCollide(list<CObj*> _srcList, list<CObj*> _dstList);
	static void PlrProjMonsterCollision(list<CObj*> _srcList, list<CObj*> _dstList);
	static void WallProjCollision(list<CObj*> _srcList, list<CObj*> _dstList);
	static void PlrDoorCollision(list<CObj*> _srcList, list<CObj*> _dstList);

	static void ProjToProjCollision(list<CObj*> _srcList, list<CObj*> _dstList);

	static void PlrMonsterCollision(list<CObj*> _srcList, list<CObj*> _dstList);
	static void MonsterWallCollision(list<CObj*> _srcList, list<CObj*> _dstList);
	
	static void PlayerItemCollision(list<CObj*> _srcList, list<CObj*> _dstList);

private:

	static CCollisionMgr* m_pInstance;

};

