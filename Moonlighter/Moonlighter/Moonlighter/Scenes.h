#pragma once
#include"Obj.h"
#include"Define.h"
#include"Camera.h"

class CScenes
{
public:
	CScenes();
	virtual ~CScenes();

public:

	virtual void Initialize();
	virtual void Update();
	virtual void Render(HDC _hDC);
	virtual void LateUpdate();
	virtual void Release();


protected:

	list<CObj*> m_objLists[static_cast<unsigned int>(EObjectType::ENUM_END)];
	ESceneType m_eSceneType = ESceneType::ENUM_END;

	list<CObj*> m_RenderList[RENDER_END];

};

