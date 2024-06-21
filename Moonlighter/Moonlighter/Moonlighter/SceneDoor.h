#pragma once
#include"Door.h"

class CSceneDoor : public CDoor
{
public:
	CSceneDoor();
	~CSceneDoor();

	void Initialize() override;
	void Update() override;
	void Render(HDC _hDC) override;
	void LateUpdate() override;
	void Release() override;

public:
	void OnCollide(CObj* _pObj);
	void SetNextScene(ESceneType _scene);

private:

	ESceneType m_eNextScene;


};

