#include "ResourceMgr.h"

CResourceMgr* CResourceMgr::m_pInstance = nullptr;


CResourceMgr::CResourceMgr()
{
}

CResourceMgr::~CResourceMgr()
{
	Release();
}

void CResourceMgr::Initialize(HWND _hwnd)
{
	m_hWnd = _hwnd;

	//MainMenu
	CreateResource("MAIN_BACKLAYER", 1280, 720, L"../Resource/Image/MainMenu/MAIN_BACKLAYER.bmp", 0, 15, 100);
	CreateResource("MAIN_BACKGROUND", 1280, 720, L"../Resource/Image/MainMenu/MAIN_BACKGROUND.bmp", 0,15, 100);
	CreateResource("MAIN_LOGO", 352, 280, L"../Resource/Image/MainMenu/MAIN_LOGO.bmp", 0, 0, 0);
	CreateResource("MAIN_START_FONT", 400, 200, L"../Resource/Image/MainMenu/MAIN_STARTTEXT.bmp", 0, 0, 0);
	
	CreateResource("BACKGROUND_LOADING", 1280, 720, L"../Resource/Image/BackGround/BACKGROUND_LOADING.bmp", 0, 0, 0);
	CreateResource("MAIN_ARROW", 28, 50, L"../Resource/Image/MainMenu/MAIN_ARROW.bmp", 0, 0, 0);

	PlayerDataLoad();
}

CMyResource* CResourceMgr::FindRes(string _findKey)
{
	auto iter = m_resList.find(_findKey);

	if (iter == m_resList.end()) {
		return nullptr;
	}

	return iter->second;
}

void CResourceMgr::CreateResource(string _keyName, int _sizeX, int sizeY, const TCHAR* _path , int _startFrame, int _EndFrame , DWORD _speed)
{
	CMyResource* tempRes = FindRes(_keyName);

	if (nullptr != tempRes)
		return;

	tempRes = new CMyResource;
	tempRes->Initialize(_sizeX, sizeY, _startFrame, _EndFrame ,_speed);
	tempRes->LoadResource(_path, m_hWnd);
	m_resList.insert({ _keyName , tempRes });

	if (m_IsDungeonRes) {
		m_DungeonKey.push_back(_keyName);
	}
}

void CResourceMgr::Release()
{
	for (auto& iter : m_resList) {
		SAFE_DELETE<CMyResource*>(iter.second);
	}


}

void CResourceMgr::PlayerDataLoad()
{

	// Player IDLE
	CreateResource("Player00", 100, 82, L"../Resource/Image/Player/PLAYER_IDLE_UP.bmp", 0, 9, 200);
	CreateResource("Player01", 100, 82, L"../Resource/Image/Player/PLAYER_IDLE_DOWN.bmp", 0, 10, 200);
	CreateResource("Player02", 100, 80, L"../Resource/Image/Player/PLAYER_IDLE_LEFT.bmp", 0, 9, 200);
	CreateResource("Player03", 100, 80, L"../Resource/Image/Player/PLAYER_IDLE_RIGHT.bmp", 0, 9, 200);

	//Player Walk
	CreateResource("Player10", 100, 86, L"../Resource/Image/Player/PLAYER_WALK_UP.bmp", 0, 7, 200);
	CreateResource("Player11", 100, 78, L"../Resource/Image/Player/PLAYER_WALK_DOWN.bmp", 0, 7, 200);
	CreateResource("Player12", 100, 80, L"../Resource/Image/Player/PLAYER_WALK_LEFT.bmp", 0, 7, 200);
	CreateResource("Player13", 100, 80, L"../Resource/Image/Player/PLAYER_WALK_RIGHT.bmp", 0, 7, 200);

	//Player RollDown		   
	CreateResource("Player20", 100, 82, L"../Resource/Image/Player/PLAYER_ROLL_UP.bmp", 0, 7, 100);
	CreateResource("Player21", 100, 82, L"../Resource/Image/Player/PLAYER_ROLL_DOWN.bmp", 0, 7, 100);
	CreateResource("Player22", 100, 80, L"../Resource/Image/Player/PLAYER_ROLL_LEFT.bmp", 0, 7, 100);
	CreateResource("Player23", 100, 80, L"../Resource/Image/Player/PLAYER_ROLL_RIGHT.bmp", 0, 7, 100);

	//Player Attack Bow
	CreateResource("Player302", 100, 100, L"../Resource/Image/Player/PLAYER_ATTACK_UP_BOW.bmp", 0, 6, 70);
	CreateResource("Player312", 100, 100, L"../Resource/Image/Player/PLAYER_ATTACK_DOWN_BOW.bmp", 0, 6, 70);
	CreateResource("Player322", 100, 100, L"../Resource/Image/Player/PLAYER_ATTACK_LEFT_BOW.bmp", 0, 6, 70);
	CreateResource("Player332", 100, 100, L"../Resource/Image/Player/PLAYER_ATTACK_RIGHT_BOW.bmp", 0, 6, 70);

	//Player Attack Spear

	CreateResource("Player301", 260, 260, L"../Resource/Image/Player/PLAYER_ATTACK_UP_SPEAR.bmp", 0, 6, 70);
	CreateResource("Player311", 260, 260, L"../Resource/Image/Player/PLAYER_ATTACK_DOWN_SPEAR.bmp", 0, 6, 70);
	CreateResource("Player321", 260, 260, L"../Resource/Image/Player/PLAYER_ATTACK_LEFT_SPEAR.bmp", 0, 6, 70);
	CreateResource("Player331", 260, 260, L"../Resource/Image/Player/PLAYER_ATTACK_RIGHT_SPEAR.bmp", 0, 6, 70);

	//Player Attack Sword

	CreateResource("Player300", 260, 260, L"../Resource/Image/Player/PLAYER_ATTACK_UP_SWORD.bmp", 0, 6, 70);
	CreateResource("Player310", 260, 260, L"../Resource/Image/Player/PLAYER_ATTACK_DOWN_SWORD.bmp", 0, 6, 70);
	CreateResource("Player320", 260, 260, L"../Resource/Image/Player/PLAYER_ATTACK_LEFT_SWORD.bmp", 0, 6, 70);
	CreateResource("Player330", 260, 260, L"../Resource/Image/Player/PLAYER_ATTACK_RIGHT_SWORD.bmp", 0, 6, 70);
	
	//Player Swim
	CreateResource("Player40", 60, 60, L"../Resource/Image/Player/PLAYER_SWIM_UP.bmp", 0, 5, 200);
	CreateResource("Player41", 60, 60, L"../Resource/Image/Player/PLAYER_SWIM_DOWN.bmp", 0, 5,200);
	CreateResource("Player42", 60, 60, L"../Resource/Image/Player/PLAYER_SWIM_LEFT.bmp", 0, 5,200);
	CreateResource("Player43", 60, 60, L"../Resource/Image/Player/PLAYER_SWIM_RIGHT.bmp", 0, 5, 200);
	
	CreateResource("WEAPON_ARROW", 60, 60, L"../Resource/Image/Player/WEAPON_ARROW.bmp", 0, 0, 0);

	//bomb
	CreateResource("BOMB_KIRBY", 120, 120, L"../Resource/Image/Tile/BOMB_KIRBY.bmp", 0, 9, 100);
	CreateResource("PROJ_BOMB", 86, 86, L"../Resource/Image/Projectile/PROJ_BOMB.bmp", 0, 6, 110);
	
	//fireShield
	CreateResource("FIRESHIELD", 203, 203, L"../Resource/Image/Projectile/FIRESHIELD.bmp", 0, 4, 50);

}

void CResourceMgr::UIDataLoad()
{
	//UI
	CreateResource("HPBAR", 128, 24, L"../Resource/Image/UI/UI_HPBAR.bmp", 0, 0, 0);
	CreateResource("HEART", 32, 32, L"../Resource/Image/UI/UI_HPHEART.bmp", 0, 0, 0);
	CreateResource("HPCIRCLE", 48, 48, L"../Resource/Image/UI/UI_HPCIRCLE.bmp", 0, 0, 0);
	CreateResource("HPBAR_ROUND", 146, 44, L"../Resource/Image/UI/UI_HPBARROUND.bmp", 0, 0, 0);
	CreateResource("UI_BASICCIRCLE", 100, 100, L"../Resource/Image/UI/UI_BASIC_CIRCLE.bmp", 0, 0, 0);
	CreateResource("UI_BASICCIRCLEBACK", 100, 100, L"../Resource/Image/UI/UI_BASIC_CIRCLEBACK.bmp", 0, 0, 0);

	CreateResource("UI_BTN_X", 32, 32, L"../Resource/Image/UI/UI_BTN_X.bmp", 0, 0, 0);
	CreateResource("UI_BTN_I", 32, 32, L"../Resource/Image/UI/UI_BTN_I.bmp", 0, 0, 0);
	CreateResource("UI_SHOP_BUBBLE", 75, 45, L"../Resource/Image/UI/UI_SHOP_BUBBLE.bmp", 0, 0, 0);
	CreateResource("UI_BAG", 46, 52, L"../Resource/Image/UI/UI_BAG.bmp", 0, 0, 0);

	CreateResource("UI_BOSSHP", 884, 24, L"../Resource/Image/UI/BOSS_HPBAR.bmp", 0, 0, 0);
	CreateResource("UI_BOSSHP_ROUND", 884, 24, L"../Resource/Image/UI/BOSS_HPDECO.bmp", 0, 0, 0);

	//WEAPON
	CreateResource("UI_SWORD", 46, 52, L"../Resource/Image/UI/UI_SWORD.bmp", 0, 0, 0);
	CreateResource("UI_BOW", 46, 52, L"../Resource/Image/UI/UI_BOW.bmp", 0, 0, 0);
	CreateResource("UI_SPEAR", 46, 52, L"../Resource/Image/UI/UI_SPEAR.bmp", 0, 0, 0);

	CreateResource("UI_GOLD", 50, 56, L"../Resource/Image/UI/UI_GOLD.bmp", 0, 0, 0);
	CreateResource("UI_COIN", 18, 18, L"../Resource/Image/UI/UI_COIN.bmp", 0, 0, 0);

	CreateResource("BOSS_NAME1", 100, 50, L"../Resource/Image/UI/BOSS_NAME1.bmp", 0, 0, 0);
	CreateResource("BOSS_NAME2", 150, 50, L"../Resource/Image/UI/BOSS_NAME2.bmp", 0, 0, 0);

	CreateResource("DUNGEON1_NAME", 150, 50, L"../Resource/Image/UI/DUNGEON1_NAME.bmp", 0, 0, 0);
	CreateResource("DUNGEON2_NAME", 150, 50, L"../Resource/Image/UI/DUNGEON2_NAME.bmp", 0, 0, 0);

	CreateResource("SCROLL1", 390, 104, L"../Resource/Image/UI/SCROLL1.bmp", 0, 9, 150);
	CreateResource("SCROLL2", 390, 104, L"../Resource/Image/UI/SCROLL2.bmp", 0, 9, 150);
	
	CreateResource("INVENTORY", 1280, 720, L"../Resource/Image/UI/INVENTORY.bmp", 0, 0, 0);
	CreateResource("INVENTORY_CURSOR", 68, 68, L"../Resource/Image/UI/INVENTORY_CURSOR.bmp", 0, 0, 0);

	CreateResource("UI_SHOP", 1280, 720, L"../Resource/Image/UI/UI_SHOP.bmp", 0, 0, 0);

	//ITEM
	CreateResource("ITEM_CORE", 50, 50, L"../Resource/Image/Item/ITEM_CORE.bmp", 0, 0, 0);
	CreateResource("ITEM_STEEL", 50, 50, L"../Resource/Image/Item/ITEM_STEEL.bmp", 0, 0, 0);

	//Effect
	CreateResource("EFFECT_HIT", 200, 200, L"../Resource/Image/Effect/EFFECT_HIT.bmp", 0, 2, 100);
	CreateResource("EFFECT_MONDEAD", 221, 221, L"../Resource/Image/Effect/EFFECT_MONDEAD.bmp", 0, 5, 100);
	CreateResource("EFFECT_ROCK", 150, 150, L"../Resource/Image/Effect/EFFECT_ROCK.bmp", 0, 8, 100);

	CreateResource("Dungeon_HiddenWall", 250, 150, L"../Resource/Image/BackGround/Dungeon_HiddenWall.bmp", 0, 0, 0);

}

void CResourceMgr::Dungeon1DataLoad()
{
	m_IsDungeonRes = true;
	//BackGround

	CreateResource("BackGround1", 1280, 720, L"../Resource/Image/BackGround/Dungeon1_Ground.bmp", 0, 0, 0);
	CreateResource("Walls1", 1280, 720, L"../Resource/Image/BackGround/Dungeon1_Wall.bmp", 0, 0, 0);
	CreateResource("BackGround_Boss1", 2300, 1550, L"../Resource/Image/BackGround/Dungeon1_Boss.bmp", 0, 0, 0);

	CreateResource("TILE_HOLE", 50, 50, L"../Resource/Image/Tile/TILE_HOLE.bmp", 0, 0, 0);
	CreateResource("TILE_HOLE_LONG", 400, 110, L"../Resource/Image/Tile/TILE_HOLE_LONG.bmp", 0, 0, 0);
	CreateResource("DUNGEON1_FLOOR1", 120, 50, L"../Resource/Image/Tile/DUNGEON1_FLOOR1.bmp", 0, 0, 0);

	//Boss
	CreateResource("BOSS1_IDLE", 800, 800, L"../Resource/Image/Boss/BOSS1_IDLE.bmp", 0, 15, 100);
	CreateResource("BOSS1_IDLE_NOARM", 800, 800, L"../Resource/Image/Boss/BOSS_IDLE_NOARM.bmp", 0, 15, 100);
	CreateResource("BOSS1_ATTACK1", 800, 800, L"../Resource/Image/Boss/BOSS1_ATTACK1.bmp", 0, 37, 100);
	CreateResource("BOSS1_RECOVERARM", 800, 800, L"../Resource/Image/Boss/BOSS1_RECOVERARM.bmp", 0, 18, 100);
	CreateResource("BOSS1_ATTACK3_PREPARE", 800, 800, L"../Resource/Image/Boss/BOSS1_ATTACK3_PREPARE.bmp", 0, 15, 150);
	CreateResource("BOSS1_ATTACK3_END", 800, 800, L"../Resource/Image/Boss/BOSS1_ATTACK3_END.bmp", 0, 31, 100);
	CreateResource("BOSS1_ATTACK3_AIM", 800, 800, L"../Resource/Image/Boss/BOSS1_ATTACK3_AIM.bmp", 0, 15, 100);
	
	CreateResource("BOSS1_WAKEUP", 600, 600, L"../Resource/Image/Boss/BOSS1_WAKEUP.bmp", 0, 18, 150);

	CreateResource("BOSS1_ROCKSPAWN", 800, 800, L"../Resource/Image/Boss/BOSS1_ROCKATK.bmp", 0, 15, 120);
	CreateResource("BOSS1_CRACK", 478, 300, L"../Resource/Image/Boss/BOSS1_CRACK.bmp", 0, 0, 0);
	CreateResource("BOSS1_ROCK", 80, 80, L"../Resource/Image/Boss/BOSS1_ROCK.bmp", 0, 0, 0);
	CreateResource("BOSS1_DEAD", 600, 600, L"../Resource/Image/Boss/BOSS1_DEATH.bmp", 0, 42, 150 );

	CreateResource("PUNCHSHADOW", 128, 90, L"../Resource/Image/Boss/PUNCHSHADOW.bmp", 0, 0, 0);
	CreateResource("PROJ_PUNCH", 220, 220, L"../Resource/Image/Boss/PROJ_PUNCH.bmp", 0, 8, 100);

	CreateResource("SLIMEBULLET", 50, 52, L"../Resource/Image/Boss/SLIME_BULLET.bmp", 0, 1, 150);
	CreateResource("BOSS1_STICKYARM", 152, 148, L"../Resource/Image/Boss/BOSS1_STICKYARM.bmp", 0, 0, 0);


	//Basic Monster
	CreateResource("SOLDIER_IDLE_DOWN", 150, 150, L"../Resource/Image/Monster/SOLDIER_IDLE_DOWN.bmp", 0, 7, 100);
	CreateResource("SOLDIER_IDLE_UP", 150, 150, L"../Resource/Image/Monster/SOLDIER_IDLE_UP.bmp", 0, 7, 100);
	CreateResource("SOLDIER_IDLE_RIGHT", 150, 150, L"../Resource/Image/Monster/SOLDIER_IDLE_RIGHT.bmp", 0, 7, 100);
	CreateResource("SOLDIER_IDLE_LEFT", 150, 150, L"../Resource/Image/Monster/SOLDIER_IDLE_LEFT.bmp", 0, 7, 100);

	CreateResource("SOLDIER_ATK_UP", 150, 150, L"../Resource/Image/Monster/SOLDIER_ATK_UP.bmp", 0, 12, 100);
	CreateResource("SOLDIER_ATK_LEFT", 150, 150, L"../Resource/Image/Monster/SOLDIER_ATK_LEFT.bmp", 0, 12, 100);
	CreateResource("SOLDIER_ATK_DOWN", 150, 150, L"../Resource/Image/Monster/SOLDIER_ATK_DOWN.bmp", 0, 12, 100);
	CreateResource("SOLDIER_ATK_RIGHT", 150, 150, L"../Resource/Image/Monster/SOLDIER_ATK_RIGHT.bmp", 0, 12, 100);
	
	CreateResource("TURRET_ATK_RIGHT", 100, 100, L"../Resource/Image/Monster/TURRET_ATK_RIGHT.bmp", 0, 10, 100);
	CreateResource("TURRET_ATK_UP", 100, 100, L"../Resource/Image/Monster/TURRET_ATK_UP.bmp", 0, 10, 100);
	CreateResource("TURRET_ATK_LEFT", 100, 100, L"../Resource/Image/Monster/TURRET_ATK_LEFT.bmp", 0, 10, 100);
	CreateResource("TURRET_ATK_DOWN", 100, 100, L"../Resource/Image/Monster/TURRET_ATK_DOWN.bmp", 0, 10, 100);
	
	CreateResource("PROJ_TURRET_RIGHT",50, 50, L"../Resource/Image/Projectile/PROJ_TURRET_RIGHT.bmp", 0, 5, 100);
	CreateResource("PROJ_TURRET_UP",   50, 50, L"../Resource/Image/Projectile/PROJ_TURRET_UP.bmp", 0, 5, 100);
	CreateResource("PROJ_TURRET_LEFT", 50, 50, L"../Resource/Image/Projectile/PROJ_TURRET_LEFT.bmp", 0, 5, 100);
	CreateResource("PROJ_TURRET_DOWN", 50, 50, L"../Resource/Image/Projectile/PROJ_TURRET_DOWN.bmp", 0, 5, 100);
	CreateResource("SLIME_ANIM", 60, 60, L"../Resource/Image/Monster/SLIME_ANIM.bmp", 0, 7, 100);
	CreateResource("DUNGEON_HIDDEN", 2560, 720, L"../Resource/Image/BackGround/Dungeon1_HiddenMap.bmp", 0, 0, 0);


	CreateResource("HEALINGPOOL", 400, 400, L"../Resource/Image/Tile/HEALINGPOOL.bmp", 0, 5, 200);
	
	//Door
	CreateResource("DUNGEON1_DOOR_OPEN_ANIM", 200, 200, L"../Resource/Image/Tile/DUNGEON1_DOOR_OPEN_ANIM.bmp", 0, 4, 100);
	CreateResource("DUNGEON1_DOOR_CLOSE_ANIM",200, 200, L"../Resource/Image/Tile/DUNGEON1_DOOR_CLOSE_ANIM.bmp", 0, 6, 100);
	CreateResource("DUNGEON1_DOOR_OPEN",200, 200, L"../Resource/Image/Tile/DUNGEON1_DOOR_OPEN.bmp", 0, 0, 0);
	CreateResource("DUNGEON1_DOOR_CLOSE",200, 200, L"../Resource/Image/Tile/DUNGEON1_DOOR_CLOSE.bmp", 0, 0, 0);
	
	
	CreateResource("TILE_TENT",254, 206, L"../Resource/Image/Tile/TILE_TENT.bmp", 0, 0, 0);
	CreateResource("TILE_ROCK",74, 46, L"../Resource/Image/Tile/TILE_ROCK.bmp", 0, 0, 0);
	CreateResource("TILE_BONE",64, 64, L"../Resource/Image/Tile/TILE_BONE.bmp", 0, 0, 0);
	CreateResource("TILE_SLIMETRAP",405, 270, L"../Resource/Image/Tile/TILE_SLIMETRAP.bmp", 0, 0, 0);
	
	CreateResource("TILE_DIRTY",352, 318, L"../Resource/Image/Tile/TILE_DIRTY.bmp", 0, 0, 0);
	CreateResource("TILE_BONE2",64, 64, L"../Resource/Image/Tile/TILE_BONE2.bmp", 0, 0, 0);
	CreateResource("TILE_BOOK",390, 156, L"../Resource/Image/Tile/TILE_BOOK.bmp", 0, 0, 0);

	CreateResource("BOSS1_PUNCHCRACK",76, 54, L"../Resource/Image/Tile/BOSS1_PUNCHCRACK.bmp", 0, 0, 0);

	m_IsDungeonRes = false;
}

void CResourceMgr::Dungeon2DataLoad()
{
	m_IsDungeonRes = true;
	//Dungeon2

	CreateResource("BackGround_Boss2", 2300, 1440, L"../Resource/Image/BackGround/Dungeon2_Boss.bmp", 0, 0, 0);
	CreateResource("BOSS2_TENTACLE_IDLE", 600, 400, L"../Resource/Image/Boss/BOSS2_TENTACLE_IDLE.bmp", 0, 6, 100);
	CreateResource("BOSS2_BUD_IDLE", 400, 400, L"../Resource/Image/Boss/BOSS2_BUD_IDLE.bmp", 0, 7, 100);
	CreateResource("BOSS2_SEED", 20, 20, L"../Resource/Image/Projectile/BOSS2_SEED.bmp", 0, 0, 0);
	CreateResource("BOSS2_BUD_SHOOTING", 400, 400, L"../Resource/Image/Boss/BOSS2_BUD_SHOOTING.bmp", 0, 29, 100);
	CreateResource("BOSS2_TENTACLE_ATTACK", 600, 400, L"../Resource/Image/Boss/BOSS2_TENTACLE_ATTACK.bmp", 0, 47, 100);
	CreateResource("BOSS2_BUD_POT", 400, 400, L"../Resource/Image/Boss/BOSS2_BUD_POT.bmp", 0, 39, 100);

	CreateResource("BOSS_BUD_WAKEUP1", 800, 800, L"../Resource/Image/Boss/BOSS_BUD_WAKEUP1.bmp", 0, 8, 120);
	CreateResource("BOSS_BUD_WAKEUP2", 800, 800, L"../Resource/Image/Boss/BOSS_BUD_WAKEUP2.bmp", 0, 8, 120);
	CreateResource("BOSS_BUD_WAKEUP3", 800, 800, L"../Resource/Image/Boss/BOSS_BUD_WAKEUP3.bmp", 0, 7, 120);
	CreateResource("BOSS_BUD_WAKEUP4", 800, 800, L"../Resource/Image/Boss/BOSS_BUD_WAKEUP4.bmp", 0, 7, 120);
	
	CreateResource("BOSS_BUD_DEAD", 540, 500, L"../Resource/Image/Boss/BOSS_BUD_DEAD.bmp", 0, 11, 120);
	CreateResource("BOSS_TENTACLE_DEAD", 600, 400, L"../Resource/Image/Boss/BOSS_TENTACLE_DEAD.bmp", 0, 11, 120);

	CreateResource("ROOT1_IDLE", 100, 120, L"../Resource/Image/Projectile/ROOT1_IDLE.bmp", 0, 6, 200);
	CreateResource("ROOT1_START", 100, 120, L"../Resource/Image/Projectile/ROOT1_START.bmp", 0, 6, 50);
	CreateResource("ROOT1_FIN", 100, 120, L"../Resource/Image/Projectile/ROOT1_FIN.bmp", 0, 21, 50);

	CreateResource("CUTTING_TEST", 58, 70, L"../Resource/Image/Monster/CUTTING_TEST.bmp", 0, 0, 0);

	CreateResource("CUTTING_IDLE", 60, 60, L"../Resource/Image/Monster/CUTTING_IDLE.bmp", 0, 0, 0);
	CreateResource("CUTTING_SHOT", 80, 80, L"../Resource/Image/Monster/CUTTING_SHOT.bmp", 0, 14, 100);
	CreateResource("CUTTING_GLOWUP", 80, 80, L"../Resource/Image/Monster/CUTTING_GLOWUP.bmp", 0, 14, 100);

	//jump
	CreateResource("BOSS2_JUMP1", 540, 500, L"../Resource/Image/Boss/BOSS2_JUMP1.bmp", 0, 7, 100);
	CreateResource("BOSS2_JUMP2", 540, 500, L"../Resource/Image/Boss/BOSS2_JUMP2.bmp", 0, 6, 200);
	CreateResource("BOSS2_JUMP3", 540, 500, L"../Resource/Image/Boss/BOSS2_JUMP3.bmp", 0, 11, 100);

	CreateResource("BUD_JUMP1", 400, 400, L"../Resource/Image/Boss/BUD_JUMP1.bmp", 0, 7, 100);
	CreateResource("BUD_JUMP2", 400, 400, L"../Resource/Image/Boss/BUD_JUMP2.bmp", 0, 6, 150);
	CreateResource("BUD_JUMP3", 400, 400, L"../Resource/Image/Boss/BUD_JUMP3.bmp", 0, 11, 100);

	CreateResource("BackGround2", 1280, 720, L"../Resource/Image/BackGround/Dungeon2_Ground.bmp", 0, 0, 0);

	//monster
	CreateResource("FRUIT_ATK_LEFT", 120, 120, L"../Resource/Image/Monster/FRUIT_ATK_LEFT.bmp", 0, 29, 100);
	CreateResource("FRUIT_WALK_LEFT", 120, 120, L"../Resource/Image/Monster/FRUIT_WALK_LEFT.bmp", 0, 4, 100);
	CreateResource("FRUIT_WALK_RIGHT", 120, 120, L"../Resource/Image/Monster/FRUIT_WALK_RIGHT.bmp", 0, 4, 100);
	CreateResource("FRUIT_ATK_RIGHT", 120, 120, L"../Resource/Image/Monster/FRUIT_ATK_RIGHT.bmp", 0, 29, 100);

	CreateResource("MUSH_CRASH", 100, 100, L"../Resource/Image/Monster/MUSH_CRASH.bmp", 0, 25, 100);
	CreateResource("MUSH_IDLE", 100, 100, L"../Resource/Image/Monster/MUSH_CYCLE.bmp", 0, 5, 100);
	CreateResource("MUSH_PRE", 100, 100, L"../Resource/Image/Monster/MUSH_SPIN.bmp", 0, 11, 100);

	CreateResource("WINDLEAF_ATK_DOWN", 120, 120, L"../Resource/Image/Monster/WINDLEAF_ATK_DOWN.bmp", 0, 19, 130);
	CreateResource("WINDLEAF_ATK_UP", 120, 120, L"../Resource/Image/Monster/WINDLEAF_ATK_UP.bmp", 0, 19, 130);
	CreateResource("WINDLEAF_ATK_LEFT", 120, 120, L"../Resource/Image/Monster/WINDLEAF_ATK_LEFT.bmp", 0, 19, 130);
	CreateResource("WINDLEAF_ATK_RIGHT", 120, 120, L"../Resource/Image/Monster/WINDLEAF_ATK_RIGHT.bmp", 0, 19, 130);

	CreateResource("WINDLEAF_WALK_DOWN", 120, 120, L"../Resource/Image/Monster/WINDLEAF_WALK_DOWN.bmp", 0, 9, 100);
	CreateResource("WINDLEAF_WALK_UP", 120, 120, L"../Resource/Image/Monster/WINDLEAF_WALK_UP.bmp", 0, 9, 100);
	CreateResource("WINDLEAF_WALK_LEFT", 120, 120, L"../Resource/Image/Monster/WINDLEAF_WALK_LEFT.bmp", 0, 9, 100);
	CreateResource("WINDLEAF_WALK_RIGHT", 120, 120, L"../Resource/Image/Monster/WINDLEAF_WALK_RIGHT.bmp", 0, 9, 100);

	CreateResource("PROJ_WINDBALL", 50, 50, L"../Resource/Image/Projectile/PROJ_WINDBALL.bmp", 0, 3, 60);

	CreateResource("DUNGEON2_DOOR_OPEN_ANIM", 260, 260, L"../Resource/Image/Tile/DUNGEON2_DOOR_OPEN_ANIM.bmp", 0, 6, 100);
	CreateResource("DUNGEON2_DOOR_CLOSE_ANIM", 260, 260, L"../Resource/Image/Tile/DUNGEON2_DOOR_CLOSE_ANIM.bmp", 0, 6, 100);
	CreateResource("DUNGEON2_DOOR_OPEN", 260, 260, L"../Resource/Image/Tile/DUNGEON2_DOOR_OPEN.bmp", 0, 0, 0);
	CreateResource("DUNGEON2_DOOR_CLOSE", 260, 260, L"../Resource/Image/Tile/DUNGEON2_DOOR_CLOSE.bmp", 0, 0, 0);

	//hidden shop
	CreateResource("DUNGEON_HIDDEN2", 2560, 720, L"../Resource/Image/BackGround/Dungeon2_HiddenMap.bmp", 0, 0, 0);
	CreateResource("HIDDENSHOP_NPC", 94, 80, L"../Resource/Image/Tile/HIDDENSHOP_NPC.bmp", 0, 7, 250);
	CreateResource("HIDDENSHOP_TILE", 52, 52, L"../Resource/Image/Tile/HIDDENSHOP_TILE.bmp", 0, 0, 0);
	CreateResource("HIDDEN_ITEM", 60, 60, L"../Resource/Image/Tile/HIDDEN_ITEM.bmp", 0, 0, 0);
	CreateResource("ITEM_BUBLE", 188, 113, L"../Resource/Image/Tile/ITEM_BUBLE.bmp", 0, 0, 0);
	
	//PuzzleRoom
	CreateResource("NPC_PIANO", 138, 148, L"../Resource/Image/Tile/NPC_PIANO.bmp", 0, 0, 0);
	CreateResource("PIANO_BUBBLE", 188, 113, L"../Resource/Image/Tile/PIANO_BUBBLE.bmp", 0, 0, 0);
	CreateResource("MUSICBOX_IDLE", 130, 150, L"../Resource/Image/Tile/MUSICBOX_IDLE.bmp", 0, 0, 0);
	CreateResource("MUSICBOX_BUBBLE", 75, 45, L"../Resource/Image/UI/MUSICBOX_BUBBLE.bmp", 0, 0, 0);
	CreateResource("MUSICBOX_ANIM", 130, 150, L"../Resource/Image/Tile/MUSICBOX_ANIM.bmp", 0, 4, 100);


	m_IsDungeonRes = false;
}

void CResourceMgr::TownDataLoad()
{
	CreateResource("TOWN_DUNGEON", 2400, 2000, L"../Resource/Image/BackGround/TOWN_DUNGEON.bmp", 0, 0, 0);
	CreateResource("TOWN_MAIN", 2602, 2134, L"../Resource/Image/BackGround/TOWN_MAIN.bmp", 0, 0, 0);
	//TOWN
	CreateResource("NPC_BLACKSMITH", 70, 90, L"../Resource/Image/Tile/NPC_BLACKSMITH.bmp", 0, 5, 200);
	CreateResource("UI_SWORD_INFO", 207, 55, L"../Resource/Image/UI/UI_SWORD_INFO.bmp", 0, 0, 0);
	CreateResource("UI_BOW_INFO", 207, 55, L"../Resource/Image/UI/UI_BOW_INFO.bmp", 0, 0, 0);
	CreateResource("UI_SPEAR_INFO", 207, 55, L"../Resource/Image/UI/UI_SPEAR_INFO.bmp", 0, 0, 0);
	CreateResource("UI_SLOTBASE", 60, 60, L"../Resource/Image/UI/UI_SLOTBASE.bmp", 0, 0, 0);

	CreateResource("HOMESHOP", 1280, 720, L"../Resource/Image/BackGround/HOMESHOP.bmp", 0, 0, 0);
	CreateResource("UI_HOMESHOP", 1280, 720, L"../Resource/Image/UI/UI_HOMESHOP.bmp", 0, 0, 0);

	CreateResource("MERCHANT_IDLE", 70, 90, L"../Resource/Image/Tile/MERCHANT_IDLE.bmp", 0, 0, 0);
	CreateResource("MERCHANT_ANIM", 70, 90, L"../Resource/Image/Tile/MERCHANT_ANIM.bmp", 0, 7, 100);
	CreateResource("MERCHANT_ANIM2", 70, 90, L"../Resource/Image/Tile/MERCHANT_ANIM2.bmp", 0, 7, 100);
	
	CreateResource("HOMESHOP_STATE", 520, 88, L"../Resource/Image/UI/HOMESHOP_STATE.bmp", 0, 0, 0);
	CreateResource("SHOP_EMOTION", 60, 60, L"../Resource/Image/UI/SHOP_EMOTION.bmp", 0, 6, 200);
	CreateResource("BASE_EMOTION", 80, 80, L"../Resource/Image/UI/BASE_EMOTION.bmp", 0, 0, 0);
	CreateResource("UI_SHOP_SELECTOR", 279, 242, L"../Resource/Image/UI/UI_SHOP_SELECTOR.bmp", 0, 0, 0);

}

void CResourceMgr::HomeDataLoad()
{
	CreateResource("HOMESHOP", 1280, 720, L"../Resource/Image/BackGround/HOMESHOP.bmp", 0, 0, 0);


}

//필요없는 리소스 데이터 삭제
void CResourceMgr::ReleasePrevData()
{
	for (auto& iter : m_DungeonKey) {
		auto it = m_resList.find(iter);

		if (it != m_resList.end()) {
			SAFE_DELETE<CMyResource*>(it->second);
			m_resList.erase(it);
		}
	}

}
