#pragma once
#include"pch.h"
#include"Types.h"
#include"Define.h"

class CObj;

enum ECameraMode {
	Player,
	Dungeon,
	END
};

enum class ECAM_EFFECT
{
	NONE,
	FADEIN,
	FADEOUT,
	VIBRATE,


	END
};

struct tCamEffect
{
	ECAM_EFFECT eEffect;
	float		fEffectTime;
	float		fAddTime;

};

class CCamera
{

private:
	CCamera();
	~CCamera();

public:

	static CCamera* GetInstance()
	{
		if (nullptr == _instance)
		{
			_instance = new CCamera();
		}

		return _instance;
	}

	static void DestroyInstance()
	{
		if (_instance)
		{
			delete _instance;
			_instance = nullptr;
		}
	}

public:

	void Initialize();
	void Update();

public:

	void SetTarget(CObj* _target) { m_pTarget = _target; };
	Vector GetRenderPos(Vector _pos) { return _pos - m_tDiff; }

	void PlayerOnTarget();
	void DungeonOnTarget();

	void SetCameraMode(int _type) {
		if (1 == _type)
			m_CurrentCamera = Player;
		else if(2 == _type)
			m_CurrentCamera = Dungeon;
	}

	void CameraLock();
	void SetCurrentMapSize(RECT _rect) { m_currentMapSize = _rect; }
	void CheckCameraEffect();
	void CheckCameraEffectPlr();
	
public:
	void Vibration(float _fRange/*진폭*/, float _fTime/*진동유지시간*/, float _fSpeed/*진동속도*/, EDirection _dir /*진동방향*/)
	{
		tCamEffect effect = {};
		effect.eEffect = ECAM_EFFECT::VIBRATE;
		effect.fEffectTime = _fTime;
		effect.fAddTime = 0.f;
		m_fRange = _fRange;
		m_fvSpeed = _fSpeed;
		m_eVibDir = _dir;
		m_tOriginLookAt = m_tCurrentLookAt;

		m_EffectQueue.push_back(effect);
	}

private:

	static CCamera* _instance;
	
	Vector m_tCurrentLookAt;
	Vector m_tDiff;
	Vector m_tPrevLookAt;

	float m_fTime;
	float m_fAccTime;
	float m_fSpeed;

	float m_fCheckingTime;

	Vector m_PrevTarget;
	CObj* m_pTarget; 
	ECameraMode m_CurrentCamera;
	bool IsMovingOn = false;

	RECT m_currentMapSize = {0,0,0,0};
	list<tCamEffect> m_EffectQueue;
	//effect
	int m_iCount = 1;

	float m_fRange;
	float m_fvSpeed;
	EDirection m_eVibDir;
	Vector m_tOriginLookAt;
	int iVibSwitch = 1;

	float m_fTotalRange = 0.f;

};

