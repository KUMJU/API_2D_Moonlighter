#include "Item.h"
#include"Component.h"

CItem::CItem() : m_pComponent(nullptr)
{
}

CItem::~CItem()
{
	Release();
}

void CItem::Initialize()
{
	m_iRendNum = PROJ;
	m_tSize = { 50.f,50.f };
	m_pComponent = new CComponent;
	m_eObjType = EObjectType::ITEM;
}

void CItem::Update()
{
}

void CItem::Render(HDC _hDC)
{
	if (m_IsVisible) {
		if (30 == m_iRendCount) {
			m_iRendDir *= -1;
			m_iRendCount = 0;
		}

		m_tPosition.m_fY += 0.5f * (float)m_iRendDir;
		m_pComponent->RenderImage(m_strImgKey, _hDC, {m_tPosition.m_fX,m_tPosition.m_fY});

		++m_iRendCount;
	}
}

void CItem::LateUpdate()
{
}

void CItem::Release()
{
	SAFE_DELETE<CComponent*>(m_pComponent);
}

void CItem::SetItemInfo(int _typeNum)
{

	switch (_typeNum)
	{
	case 0:
		m_strImgKey = "UI_SWORD";
		m_strItemName = "±âº» ¼ô¼Òµå";
		m_eItemType = EItemType::WEAPON;
		break;

	case 1:
		m_strImgKey = "UI_BOW";
		m_strItemName = "±âº» È°";
		m_eItemType = EItemType::WEAPON;
		break;

	case 2:
		m_strImgKey = "UI_SPEAR";
		m_strItemName = "³ª¹« Ã¢";
		m_eItemType = EItemType::WEAPON;
		break;
	case 3:
		m_strImgKey = "ITEM_STEEL";
		m_strItemName = "°­Ã¶";
		m_eItemType = EItemType::STUFF;
		break;

	case 4:
		m_strImgKey = "ITEM_CORE";
		m_strItemName = "°ñ·½ ÄÚ¾î";
		m_eItemType = EItemType::STUFF;
		break;

	default:
		break;
	}

}

void CItem::OnCollide(CObj* _pObj)
{
}
