#include "Camera.h"
#include"Obj.h"
#include"TimeMgr.h"
#include"Inventory.h"

CCamera* CCamera::_instance = nullptr;

CCamera::CCamera() :
	m_tCurrentLookAt(),
	m_tDiff(),
	m_tPrevLookAt(),
	m_pTarget(nullptr),
	m_fTime(1.5f),
	m_fAccTime(0.f)
{
}

CCamera::~CCamera()
{
}

void CCamera::Initialize()
{
}


void CCamera::Update()
{

	if (!m_pTarget) {
		m_tDiff = { 0.f,0.f };
	}
	else {
		if (Player == m_CurrentCamera) {
			PlayerOnTarget();
			Vector CenterVec = { WINCX * 0.5f, WINCY * 0.5f };
			CheckCameraEffectPlr();
			m_tDiff = m_tCurrentLookAt - CenterVec;
			m_tPrevLookAt = m_tCurrentLookAt;
			m_PrevTarget = m_pTarget->GetPosition();
			CameraLock();
		}
		else if (Dungeon == m_CurrentCamera) {

			DungeonOnTarget();
			Vector CenterVec = { WINCX * 0.5f, WINCY * 0.5f };
			CheckCameraEffect();
			m_tDiff = m_tCurrentLookAt - CenterVec;
			m_tPrevLookAt = m_tCurrentLookAt;
			m_PrevTarget = m_pTarget->GetPosition();
		}
	}

}

void CCamera::PlayerOnTarget()
{
	m_tCurrentLookAt = m_pTarget->GetPosition();

}

void CCamera::DungeonOnTarget()
{

	m_tCurrentLookAt = m_pTarget->GetPosition();
	Vector DirVec = m_tCurrentLookAt - m_tPrevLookAt;

	if (m_PrevTarget != m_pTarget->GetPosition()) {
		m_fSpeed = DirVec.Length() / m_fTime;
		m_fAccTime = 0.f;
	}

	if (DirVec.Length() < 1800) {


		if (m_fAccTime > m_fTime) {
			m_tCurrentLookAt = m_pTarget->GetPosition();
			m_fAccTime = 0.f;
			m_fSpeed = 0.f;
		//	IsMovingOn = false;
		}
		else {
			DirVec.Normalize();
			m_tCurrentLookAt = m_tPrevLookAt + DirVec * m_fSpeed * CTimeMgr::GetInstance()->GetDS();

		}
		m_fAccTime += CTimeMgr::GetInstance()->GetDS();

	}

}

void CCamera::CameraLock()
{
	Vector CenterVec = { WINCX * 0.5f, WINCY * 0.5f };

	if (m_pTarget->GetPosition().m_fX < m_currentMapSize.left + WINCX * 0.5f) {
		m_tDiff.m_fX = m_currentMapSize.left + WINCX * 0.5f - CenterVec.m_fX;
	}

	if (m_pTarget->GetPosition().m_fX > m_currentMapSize.right - WINCX * 0.5f) {
		m_tDiff.m_fX = m_currentMapSize.right - WINCX * 0.5f - CenterVec.m_fX;
	}

	if (m_pTarget->GetPosition().m_fY < m_currentMapSize.top + WINCY * 0.5f) {
		m_tDiff.m_fY = m_currentMapSize.top + WINCY * 0.5f - CenterVec.m_fY;
	}

	if (m_pTarget->GetPosition().m_fY > m_currentMapSize.bottom - WINCY * 0.5f) {
		m_tDiff.m_fY = m_currentMapSize.bottom - WINCY * 0.5f - CenterVec.m_fY;
	}


}

void CCamera::CheckCameraEffect()
{
	while (true)
	{
		if (m_EffectQueue.empty())
			return;

		tCamEffect& effect = m_EffectQueue.front();
		effect.fAddTime += CTimeMgr::GetInstance()->GetDS();

		// 이펙트 시간이 초과된 경우
		if (effect.fAddTime > effect.fEffectTime)
		{
			if (ECAM_EFFECT::VIBRATE == effect.eEffect)
				m_tCurrentLookAt = m_pTarget->GetPosition();

			m_EffectQueue.pop_front();
		}
		else
			break;
	}

	tCamEffect& effect = m_EffectQueue.front();

	// ============================
	//			Vibration
	// ============================

	if (ECAM_EFFECT::VIBRATE == effect.eEffect)
	{
		if (EDirection::RIGHT == m_eVibDir) //가로
		{
			if ((m_tOriginLookAt.m_fY + m_fRange) < m_tCurrentLookAt.m_fY)
				iVibSwitch = -1;
			else if ((m_tOriginLookAt.m_fY - m_fRange) > m_tCurrentLookAt.m_fY)
				iVibSwitch = 1;

			m_tCurrentLookAt.m_fY += iVibSwitch * m_fRange * m_fvSpeed * CTimeMgr::GetInstance()->GetDS();
		}
		if (EDirection::UP == m_eVibDir) //세로
		{
			if ((m_tOriginLookAt.m_fX + m_fRange) < m_tCurrentLookAt.m_fX)
				iVibSwitch = -1;
			else if ((m_tOriginLookAt.m_fX - m_fRange) > m_tCurrentLookAt.m_fX)
				iVibSwitch = 1;

			m_tCurrentLookAt.m_fX += iVibSwitch * m_fRange * m_fvSpeed * CTimeMgr::GetInstance()->GetDS();
		}

		return;
	}


}

void CCamera::CheckCameraEffectPlr()
{
	while (true)
	{
		if (m_EffectQueue.empty())
			return;

		tCamEffect& effect = m_EffectQueue.front();
		effect.fAddTime += CTimeMgr::GetInstance()->GetDS();

		// 이펙트 시간이 초과된 경우
		if (effect.fAddTime > effect.fEffectTime)
		{
			m_iCount = 1;
			if (ECAM_EFFECT::VIBRATE == effect.eEffect)
			{
				m_tCurrentLookAt = m_pTarget->GetPosition();
				m_fTotalRange = 0.f;
			}

			m_EffectQueue.pop_front();
		}
		else
			break;
	}

	if (1 == iVibSwitch) {
		if (m_fRange <= m_fTotalRange) {
			iVibSwitch = iVibSwitch * -1;
		}

	}
	else if (-1 == iVibSwitch) {
		if (m_fRange * -1 >= m_fTotalRange) {
			iVibSwitch = iVibSwitch * -1;
		}
	}

	m_fTotalRange += iVibSwitch * m_fRange * m_fvSpeed * CTimeMgr::GetInstance()->GetDS();

	tCamEffect& effect = m_EffectQueue.front();

	// ============================
	//			Vibration
	// ============================
	m_tOriginLookAt = m_tCurrentLookAt;

	if (ECAM_EFFECT::VIBRATE == effect.eEffect)
	{
		if (EDirection::RIGHT == m_eVibDir) //가로
		{
			m_tCurrentLookAt.m_fY += iVibSwitch * m_fRange * m_fvSpeed * CTimeMgr::GetInstance()->GetDS();
		}
		if (EDirection::UP == m_eVibDir) //세로                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                               
		{
			m_tCurrentLookAt.m_fX += iVibSwitch * m_fRange * m_fvSpeed * CTimeMgr::GetInstance()->GetDS();
		}

		return;
	}

}
