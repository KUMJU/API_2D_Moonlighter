#include"pch.h"
#include "Scenes.h"
#include"Player.h"
#include"CollisionMgr.h"
#include"Tile.h"
#include"UIMgr.h"
#include"GameMgr.h"
#include"SoundMgr.h"
#include"Item.h"

CScenes::CScenes()
{
}

CScenes::~CScenes()
{
	Release();
}

void CScenes::Initialize()
{
	CSoundMgr::Get_Instance()->StopSound(SOUND_BGM);

	if (!CGameMgr::GetInstance()->isPlayerExist()) {
		CObj* mPlayer = new CPlayer;
		CGameMgr::GetInstance()->SetPlayer(mPlayer);
		CGameMgr::GetInstance()->GetPlayer()->Initialize();

		m_objLists[(unsigned int)EObjectType::PLAYER].push_back(mPlayer);
		dynamic_cast<CPlayer*>(m_objLists[(unsigned int)EObjectType::PLAYER].front())->SetProjList(&(m_objLists[(unsigned int)EObjectType::PLR_PROJ]));
		dynamic_cast<CPlayer*>(m_objLists[(unsigned int)EObjectType::PLAYER].front())->SetObsList(&(m_objLists[(unsigned int)EObjectType::OBSTACLE]));

	}
	else {
		m_objLists[(unsigned int)EObjectType::PLAYER].push_back(CGameMgr::GetInstance()->GetPlayer());
		dynamic_cast<CPlayer*>(m_objLists[(unsigned int)EObjectType::PLAYER].front())->SetProjList(&(m_objLists[(unsigned int)EObjectType::PLR_PROJ]));
		dynamic_cast<CPlayer*>(m_objLists[(unsigned int)EObjectType::PLAYER].front())->SetObsList(&(m_objLists[(unsigned int)EObjectType::OBSTACLE]));

	}
}

void CScenes::Update()
{

	for (auto& list : m_objLists)
	{
		for (auto it = list.begin(); it != list.end(); ++it)
		{
			(*it)->Update();
			m_RenderList[(*it)->GetRendNum()].push_back((*it));
		}
	}

	CUIMgr::GetInstance()->Update();
	CCamera::GetInstance()->Update();

}

void CScenes::Render(HDC _hDC)
{

	for (size_t i = 0; i < RENDER_END; ++i)
	{	
		if (i == GAMEOBJECT) {
			m_RenderList[i].sort([](CObj* pDst, CObj* pSrc) ->bool
				{
					return pDst->GetBottomPos() < pSrc->GetBottomPos();
				});
		}

		for (auto& iter : m_RenderList[i])
			iter->Render(_hDC);

		m_RenderList[i].clear();
	}



	//for (auto& list : m_objLists)
	//{
	//	for (auto it = list.begin(); it != list.end(); ++it)
	//	{
	//		(*it)->Render(_hDC);
	//	}
	//}

	CUIMgr::GetInstance()->Render(_hDC);

}

void CScenes::LateUpdate()
{
	CCollisionMgr::PlrObstacleCollision(m_objLists[(unsigned int)EObjectType::PLAYER], m_objLists[(unsigned int)EObjectType::OBSTACLE]);
	CCollisionMgr::PlrMonProjCollide(m_objLists[(unsigned int)EObjectType::PLAYER], m_objLists[(unsigned int)EObjectType::MON_PROJ]);
	CCollisionMgr::PlrProjMonsterCollision(m_objLists[(unsigned int)EObjectType::PLR_PROJ], m_objLists[(unsigned int)EObjectType::MONSTER]);
	CCollisionMgr::ProjToProjCollision(m_objLists[(unsigned int)EObjectType::PLR_PROJ], m_objLists[(unsigned int)EObjectType::MON_PROJ]);

	//벽 - 발사체
	CCollisionMgr::WallProjCollision(m_objLists[(unsigned int)EObjectType::PLR_PROJ], m_objLists[(unsigned int)EObjectType::OBSTACLE]);
	CCollisionMgr::WallProjCollision(m_objLists[(unsigned int)EObjectType::MON_PROJ], m_objLists[(unsigned int)EObjectType::OBSTACLE]);
	
	CCollisionMgr::MonsterWallCollision(m_objLists[(unsigned int)EObjectType::MONSTER], m_objLists[(unsigned int)EObjectType::OBSTACLE]);
	CCollisionMgr::PlrMonsterCollision(m_objLists[(unsigned int)EObjectType::PLAYER], m_objLists[(unsigned int)EObjectType::MONSTER]);
	CCollisionMgr::PlayerItemCollision(m_objLists[(unsigned int)EObjectType::PLAYER], m_objLists[(unsigned int)EObjectType::ITEM]);
	
	for (size_t i = 0; i < (unsigned int)EObjectType::ENUM_END; ++i) {
		for (auto it = m_objLists[i].begin(); it != m_objLists[i].end();)
		{
			if ((unsigned int)EObjectType::ITEM == i) {

				if (false == dynamic_cast<CItem*>(*it)->GetIsVisible()) {
					it = m_objLists[i].erase(it);
					continue;
				}
			}

			(*it)->LateUpdate();

			if ((*it)->GetIsDead())
			{
				SAFE_DELETE<CObj*>(*it);
				it = m_objLists[i].erase(it);
			}
			else {
				++it;
			}
		}
	}

	CCollisionMgr::PlrDoorCollision(m_objLists[(unsigned int)EObjectType::PLAYER], m_objLists[(unsigned int)EObjectType::DOOR]);

}

void CScenes::Release()
{

	for (size_t i = 0; i < (unsigned int)EObjectType::ENUM_END; ++i) {
		if ((unsigned int)EObjectType::PLAYER != i) {

			std::for_each(m_objLists[i].begin(), m_objLists[i].end(), [](auto& _objPtr) {
				SAFE_DELETE<CObj*>(_objPtr);
				});

			m_objLists[i].clear();
		}
		else {
			m_objLists[i].clear();
		}
	}
}
