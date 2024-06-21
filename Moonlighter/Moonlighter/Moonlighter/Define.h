#pragma once
#include"pch.h"
#include"Enums.h"

#define WINCX	1280
#define WINCY	720
#define	PI		3.14f

#define VK_MAX	0xff

#define DS CTimeMgr::GetInstance()->GetDS()

enum CHANNELID { SOUND_EFFECT, SOUND_EFFECT2,MONSTER_EFFECT, PLAYER_EFFECT,BOSS_EFFECT, DAMAGE_EFFECT, SOUND_BGM, MAXCHANNEL };
enum RENDERID { BACKGROUND, GAMEOBJECT, PROJ ,EFFECT, RENDER_END };

struct ItemViewInfo {
	string strKeyName;
	int iPrice;
	int iSlotNum;
};

struct AnimInfo
{
	int iSizeX;
	int iSizeY;
	int iFrameStart;
	int iFrameEnd;
	unsigned long long Framespeed;
};


template<typename T>
void SAFE_DELETE(T& _ptr)
{
	if (_ptr)
	{
		delete _ptr;
		_ptr = nullptr;
	}
}

struct SAFE_DELETE_FUNCTOR
{
	template<typename T>
	void operator()(T& _ptr)
	{
		if (_ptr)
		{
			delete _ptr;
			_ptr = nullptr;
		}
	}
};


struct TileInfo {
	float fX;
	float fY;
	int iTileNum= 0;
};