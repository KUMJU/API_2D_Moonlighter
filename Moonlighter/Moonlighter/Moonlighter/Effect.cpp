#include "Effect.h"
#include"Component.h"

CEffect::CEffect() : m_pComponent(nullptr)
{
}

CEffect::CEffect(string _key, DWORD _time, EDirection _dir) : m_strAnimKey(_key), 
				m_dwExistTime(_time), 
				m_pComponent(nullptr)
{
	m_eDir = _dir;
}

CEffect::~CEffect()
{
	Release();
}

void CEffect::Initialize() 
{
	m_iRendNum = EFFECT;
	m_pComponent = new CComponent;
	m_dwCreateTime = (DWORD)GetTickCount64();
}

void CEffect::Update()
{
}

void CEffect::Render(HDC _hDC)
{
	m_pComponent->PlayAnimGetRow(m_strAnimKey, _hDC, m_tPosition, (int)m_eDir);

}

void CEffect::LateUpdate()
{
	if (m_dwCreateTime + m_dwExistTime <= (DWORD)GetTickCount64()) {
		m_bIsDead = true;
	}

}

void CEffect::Release()
{
	SAFE_DELETE<CComponent*>(m_pComponent);
}

void CEffect::OnCollide(CObj* _pObj)
{
}
