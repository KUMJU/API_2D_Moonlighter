#pragma once

enum class EGameState {
	DEFAULT,
	PAUSE,
	ENUM_END
};

enum class EObjectType 
{
	OBSTACLE,
	DOOR,
	MONSTER,
	PLAYER,
	ITEM,
	MON_PROJ,
	PLR_PROJ,
	EFFECT,
	ENUM_END
};


enum class EDirection {
	UP,
	DOWN,
	LEFT,
	RIGHT,
	ENUM_END
};

enum class EPlayerState
{
	IDLE,
	WALK,
	ROLLDOWN,
	ATTACK,
	SWIM,
	DEAD,
	ENUM_END
};

enum class EMonsterState
{
	IDLE,
	WALK,
	ATTACK,
	ONATTACKED,
	ENUM_END
};

enum class EWeaponType 
{
	SWORD,
	SPEAR,
	BOW,
	ENUM_END
};

enum class ESceneType 
{
	MAINMENU,
	GOLEM_DUNGEON,
	FOREST_DUNGEON,
	VILLAGE,
	HOME,
	EDITOR,
	LOADING,
	ENUM_END

};

enum class ETileType {

	WALL,
	ROCK,
	HOLE,
	SLOW,
	COLLISION_DECO,
	DECO,
	NPC,
	HEALINGPOOL,
	HIDDEN_WALL,
	MUSICBOX,
	ENUM_END

};


enum class EProjectileType {
	BASIC,
	PLAYER,
	GOLEMPUNCH,
	TENTACLE,
	BOMB,
	SHIELD,
	ENUM_END
};


enum class EItemType {
	WEAPON,
	STUFF,
	ENUM_END
};