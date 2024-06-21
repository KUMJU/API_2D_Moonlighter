#include "PositionDoor.h"
#include"Camera.h"

CPositionDoor::CPositionDoor() : m_WarpMapsize({})
{
}

CPositionDoor::~CPositionDoor()
{
}

void CPositionDoor::Initialize()
{
	CDoor::Initialize();
}

void CPositionDoor::Update()
{
}

void CPositionDoor::Render(HDC _hDC)
{
	CDoor::Render(_hDC);


}

void CPositionDoor::LateUpdate()
{
}

void CPositionDoor::Release()
{
}

void CPositionDoor::OnCollide(CObj* _pObj)
{
	if (_pObj->GetObjType() == EObjectType::PLAYER) {
		_pObj->SetPosition(m_WarpPos);
		CCamera::GetInstance()->SetCurrentMapSize(m_WarpMapsize);
		
	}


}
