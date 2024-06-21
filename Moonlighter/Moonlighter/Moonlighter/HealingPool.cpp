#include "HealingPool.h"

CHealingPool::CHealingPool()
{
}

CHealingPool::~CHealingPool()
{
}

void CHealingPool::Initialize()
{
	CTile::Initialize();
	m_tSize = { 100.f,100.f };
	m_eTileType = ETileType::HEALINGPOOL;

}

void CHealingPool::Update()
{
}

void CHealingPool::Render(HDC _hDC)
{
	m_pComponent->PlayAnim("HEALINGPOOL", _hDC, m_tPosition);
}

void CHealingPool::LateUpdate()
{
}

void CHealingPool::Release()
{
}
