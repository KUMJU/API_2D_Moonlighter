#include "CollisionMgr.h"
#include"Tile.h"
#include"Player.h"
#include"Projectile.h"
#include"Monster.h"
#include"GolemKing.h"
#include"Item.h"
#include"SoundMgr.h"

CCollisionMgr* CCollisionMgr::m_pInstance = nullptr;


CCollisionMgr::CCollisionMgr()
{
}

CCollisionMgr::~CCollisionMgr()
{
}

void CCollisionMgr::CollisionRect(list<CObj*> _srcList, list<CObj*> _dstList)
{
	RECT		rc{};

	for (auto& src : _srcList)
	{
		for (auto& dst : _dstList)
		{
			RECT tSrcRect = GetRect(src);
			RECT tDstRect = GetRect(dst);

			if (IntersectRect(&rc, &tSrcRect, &tDstRect))
			{
				src->OnCollide(dst);
				dst->OnCollide(src);

			}
		}
	}
}

void CCollisionMgr::CollisionRectEx(list<CObj*> _srcList, list<CObj*> _dstList)
{
	float	m_fX = 0.f, m_fY = 0.f;

	for (auto& src : _srcList)
	{
		for (auto& dst : _dstList)
		{
			if (CheckRect(src, dst, &m_fX, &m_fY))
			{
					// 상하 충돌
					if (m_fX > m_fY)
					{
						if (src->GetPosition().m_fY < dst->GetPosition().m_fY)
						{
							src->SetPosition({ src->GetPosition().m_fX, src->GetPosition().m_fY - m_fY });
						}
						else // 하 충돌
						{
							src->SetPosition({ src->GetPosition().m_fX, src->GetPosition().m_fY + m_fY });
						}
					}
					// 좌우 충돌
					else
					{
						if (src->GetPosition().m_fX < dst->GetPosition().m_fX)
						{
							src->SetPosition({ src->GetPosition().m_fX - m_fX, src->GetPosition().m_fY });
						}
						else // 우 충돌
						{
							src->SetPosition({ src->GetPosition().m_fX + m_fX, src->GetPosition().m_fY });
						}
					}

			}
		}
	}
}

bool CCollisionMgr::CheckRect(CObj* _pSrc, CObj* _pDst, float* pX, float* pY)
{
	float		fWidth = abs(_pDst->GetPosition().m_fX - _pSrc->GetPosition().m_fX);
	float		fHeight = abs(_pDst->GetPosition().m_fY - _pSrc->GetPosition().m_fY);

	float		fCX = (_pDst->GetSize().m_fX + _pSrc->GetSize().m_fX) * 0.5f;
	float		fCY = (_pDst->GetSize().m_fY + _pSrc->GetSize().m_fY) * 0.5f;

	if ((fCX >= fWidth) && (fCY >= fHeight))
	{
		*pX = fCX - fWidth;
		*pY = fCY - fHeight;

		return true;
	}

	return false;
}

bool CCollisionMgr::CheckSphere(CObj* _pSrc, CObj* _pDst)
{
	return false;
}

void CCollisionMgr::CollisionSphere(list<CObj*> _srcList, list<CObj*> _dstList)
{
}

RECT CCollisionMgr::GetRect(CObj* _pObj)
{
	RECT rc{};

	rc.left = LONG(_pObj->GetPosition().m_fX - (_pObj->GetSize().m_fX * 0.5f));
	rc.top = LONG(_pObj->GetPosition().m_fY - (_pObj->GetSize().m_fY * 0.5f));
	rc.right = LONG(_pObj->GetPosition().m_fX + (_pObj->GetSize().m_fX * 0.5f));
	rc.bottom = LONG(_pObj->GetPosition().m_fY + (_pObj->GetSize().m_fY * 0.5f));

	return rc;
}

void CCollisionMgr::PlrObstacleCollision(list<CObj*> _srcList, list<CObj*> _dstList)
{
	float	m_fX = 0.f, m_fY = 0.f;

	for (auto& src : _srcList)
	{
		for (auto& dst : _dstList)
		{
			if (static_cast<CTile*>(dst)->GetTileType() == ETileType::WALL || 
				static_cast<CTile*>(dst)->GetTileType() == ETileType::HIDDEN_WALL||
				static_cast<CTile*>(dst)->GetTileType() == ETileType::ROCK ||
				static_cast<CTile*>(dst)->GetTileType() == ETileType::COLLISION_DECO||
				static_cast<CTile*>(dst)->GetTileType() == ETileType::MUSICBOX) {
				if (CheckRect(src, dst, &m_fX, &m_fY)) {
					WallCollision(src, dst, m_fX, m_fY);
				}
			}
			else if (static_cast<CTile*>(dst)->GetTileType() == ETileType::HOLE) {
				if (CheckRect(src, dst, &m_fX, &m_fY) && static_cast<CPlayer*>(src)->GetPlayerState() != EPlayerState::ROLLDOWN) {
					
					if (src->GetBottomPos() > dst->GetPosition().m_fY - dst->GetSize().m_fY *0.5f + 6.f &&
						src->GetBottomPos() < dst->GetPosition().m_fY + dst->GetSize().m_fY * 0.5f -6.f&&
						src->GetPosition().m_fX + src->GetSize().m_fX  < dst->GetPosition().m_fX + dst->GetSize().m_fX * 0.5f -6.f&&
						src->GetPosition().m_fX - src->GetSize().m_fX > dst->GetPosition().m_fX - dst->GetSize().m_fX * 0.5f + 6.f) {
						
						src->OnCollide(dst);
						WallCollision(src, dst, m_fX, m_fY);
					}
					else {
						WallCollision(src, dst, m_fX, m_fY);

					}
					
				}			
			}
			else if (static_cast<CTile*>(dst)->GetTileType() == ETileType::HEALINGPOOL ||
				static_cast<CTile*>(dst)->GetTileType() == ETileType::SLOW) {
				if (CheckRect(src, dst, &m_fX, &m_fY) && static_cast<CPlayer*>(src)->GetPlayerState() != EPlayerState::ROLLDOWN) {
					src->OnCollide(dst);
				}

			}
		}
	}

}

void CCollisionMgr::WallCollision(CObj* src, CObj* dst, float m_fX, float m_fY)
{
		// 상하 충돌
	if (m_fX > m_fY)
	{
		if (src->GetPosition().m_fY < dst->GetPosition().m_fY)
		{
			src->SetPosition({ src->GetPosition().m_fX, src->GetPosition().m_fY - m_fY });
		}
		else // 하 충돌
		{	
			src->SetPosition({ src->GetPosition().m_fX, src->GetPosition().m_fY + m_fY });
		}
	}
		// 좌우 충돌
	else
	{
		if (src->GetPosition().m_fX < dst->GetPosition().m_fX)
		{
			src->SetPosition({ src->GetPosition().m_fX - m_fX, src->GetPosition().m_fY });
		}
		else // 우 충돌
		{
			src->SetPosition({ src->GetPosition().m_fX + m_fX, src->GetPosition().m_fY });
		}
	}

}

void CCollisionMgr::PlrMonProjCollide(list<CObj*> _srcList, list<CObj*> _dstList)
{
	float	m_fX = 0.f, m_fY = 0.f;

	for (auto& src : _srcList)
	{
		for (auto& dst : _dstList)
		{
			if (CheckRect(src, dst, &m_fX, &m_fY)){

				if (static_cast<CProjectile*>(dst)->GetProjType() == EProjectileType::GOLEMPUNCH
					|| static_cast<CProjectile*>(dst)->GetProjType() == EProjectileType::TENTACLE) {

					static_cast<CPlayer*>(src)->OnAttacked(static_cast<CProjectile*>(dst)->GetDamage());
				}
				else {
					static_cast<CPlayer*>(src)->OnAttacked(static_cast<CProjectile*>(dst)->GetDamage());
					dst->SetIsDead();
				}
			}			
		}
	}
}

void CCollisionMgr::PlrProjMonsterCollision(list<CObj*> _srcList, list<CObj*> _dstList)
{
	float	m_fX = 0.f, m_fY = 0.f;

	for (auto& src : _srcList)
	{
		for (auto& dst : _dstList)
		{
			if (EProjectileType::SHIELD != static_cast<CProjectile*>(src)->GetProjType()) {
				if (CheckRect(src, dst, &m_fX, &m_fY)) {
					dst->OnAttacked(static_cast<CProjectile*>(src)->GetDamage());
					src->SetIsDead();
				}
			}
		}
	}
}

void CCollisionMgr::WallProjCollision(list<CObj*> _srcList, list<CObj*> _dstList)
{
	float	m_fX = 0.f, m_fY = 0.f;

	for (auto& src : _srcList)
	{
		for (auto& dst : _dstList)
		{
			if (EProjectileType::SHIELD != static_cast<CProjectile*>(src)->GetProjType()) {

				if (static_cast<CTile*>(dst)->GetTileType() == ETileType::HIDDEN_WALL) {
					if (static_cast<CProjectile*>(src)->GetProjType() == EProjectileType::BOMB) {
						dst->SetIsDead();
						CSoundMgr::Get_Instance()->StopSound(MONSTER_EFFECT);
						CSoundMgr::Get_Instance()->PlaySound(L"sfx_secretfound.wav", MONSTER_EFFECT, 2.f);
					}
				}
				else if (static_cast<CTile*>(dst)->GetTileType() == ETileType::WALL) {
					if (CheckRect(src, dst, &m_fX, &m_fY)) {
						if (static_cast<CProjectile*>(src)->GetProjType() != EProjectileType::GOLEMPUNCH
							&& static_cast<CProjectile*>(src)->GetProjType() != EProjectileType::TENTACLE) {
							src->SetIsDead();
						}
					}
				}
				else if (static_cast<CTile*>(dst)->GetTileType() == ETileType::ROCK) {
					if (static_cast<CProjectile*>(src)->GetProjType() == EProjectileType::PLAYER) {
						if (CheckRect(src, dst, &m_fX, &m_fY)) {
							dst->OnCollide(src);
							src->SetIsDead();
						}
					}
				}
				else if (static_cast<CTile*>(dst)->GetTileType() == ETileType::MUSICBOX) {
					if (static_cast<CProjectile*>(src)->GetProjType() == EProjectileType::PLAYER) {
						if (CheckRect(src, dst, &m_fX, &m_fY)) {
							dst->OnCollide(src);
							src->SetIsDead();
						}
					}
				}
			}
		}
	}
}

void CCollisionMgr::PlrDoorCollision(list<CObj*> _srcList, list<CObj*> _dstList)
{
	float	m_fX = 0.f, m_fY = 0.f;

	for (auto& src : _srcList)
	{
		for (auto& dst : _dstList)
		{
			if (CheckRect(src, dst, &m_fX, &m_fY)) {
				WallCollision(src, dst, m_fX, m_fY);
				dst->OnCollide(src);
			}
		}
	}
}

void CCollisionMgr::ProjToProjCollision(list<CObj*> _srcList, list<CObj*> _dstList)
{

	float	m_fX = 0.f, m_fY = 0.f;

	for (auto& src : _srcList)
	{
		for (auto& dst : _dstList)
		{
			if (EProjectileType::SHIELD == static_cast<CProjectile*>(src)->GetProjType()) {
				if (CheckRect(src, dst, &m_fX, &m_fY)) {
					dst->SetIsDead();
				}
			}
		}
	}


}

void CCollisionMgr::PlrMonsterCollision(list<CObj*> _srcList, list<CObj*> _dstList)
{
	float	m_fX = 0.f, m_fY = 0.f;

	for (auto& src : _srcList)
	{
		for (auto& dst : _dstList)
		{
			if (CheckRect(src, dst, &m_fX, &m_fY)) {
				src->OnAttacked(static_cast<CMonster*>(dst)->GetDamage());
				WallCollision(src, dst, m_fX, m_fY);
			}
		}
	}

}

void CCollisionMgr::MonsterWallCollision(list<CObj*> _srcList, list<CObj*> _dstList)
{
	float	m_fX = 0.f, m_fY = 0.f;

	for (auto& src : _srcList)
	{
		for (auto& dst : _dstList)
		{
			if (static_cast<CTile*>(dst)->GetTileType() == ETileType::WALL ||
				static_cast<CTile*>(dst)->GetTileType() == ETileType::HOLE ||
				static_cast<CTile*>(dst)->GetTileType() == ETileType::COLLISION_DECO) {
				if (CheckRect(src, dst, &m_fX, &m_fY)) {
					WallCollision(src, dst, m_fX, m_fY);
					src->OnCollide(dst);
				}
			}
		}
	}
}

void CCollisionMgr::PlayerItemCollision(list<CObj*> _srcList, list<CObj*> _dstList)
{
	float	m_fX = 0.f, m_fY = 0.f;

	for (auto& src : _srcList)
	{
		for (auto& dst : _dstList)
		{
			if (CheckRect(src, dst, &m_fX, &m_fY)) {
				src->OnCollide(dst);
				dynamic_cast<CItem*>(dst)->SetVisible();
			}
		}
	}
}
