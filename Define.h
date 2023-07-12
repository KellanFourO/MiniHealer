#pragma once
#include "framework.h"

#define		WINCX		1280
#define		WINCY		800

#define		PURE		= 0
#define		PI			3.141592f

#define		OBJ_DEAD	 1
#define		OBJ_NOEVENT	 0

#define		VK_MAX		0xff


#define		TILEX		30
#define		TILEY		20

#define		TILECX		64
#define		TILECY		64

#define		DEG2RAD		PI / 180

typedef struct tagInfo
{
	float	fX;		// 중점 X
	float	fY;		// 중점 Y
	float	fCX;	// 가로 길이
	float	fCY;	// 세로 길이	

}INFO;

typedef struct PlayerInfo
{
	int			m_iHp;
	int			m_iMaxHp;
	float		m_iHpRecovery;		// 초당 체력 재생

	int			m_iMp;
	int			m_iMaxMp;
	float		m_iMpRecovery;		// 초당 마나 재생

	int		m_iAttack;			// 물리 피해
	int		m_iArmor;

	float	m_iAttackSpeed;		// 공격속도
	int		m_iCritical;		// 치명타율
	int		m_iCriticalDmg;		// 치명타 피해량

	float		m_iAvo;				// 회피율	

	int		m_iMoney;

}STAT;

struct SwordInfo
{
	float m_fLeftTop;
	float m_fRightTop;
	float m_fLeftBottom;
	float m_fRightBottom;

	float m_fTargetX;
	float m_fTargetY;
};

struct ItemInfo
{
	const TCHAR*	m_pName;
	const TCHAR*	m_pType;
	const TCHAR*	m_pApply;
	int				m_iMoney;
	int				m_iAttack;
	int				m_iArmor;
	int				m_iMana;
	int				m_iMaxMana;
	float			m_fHpRecovery;
	float			m_fMpRecovery;
	bool			m_bEquip;
};

struct ClearTime
{
	int m_iHour;
	int m_iMinute;
	long m_lSecond;
};

struct VECTOR
{
	double x, y;
};

struct SHAPE
{
	double top, left, height, width, rot;
};



enum class HEALERSTATEID { IDLE, WALK, JUMP, ATTACK, CAST, DEATH, HEALSTATE_END };
enum class RANGERSTATEID { IDLE, WALK, ATTACK, DEATH, RANGSTATE_END };
enum class BERSERKERSTATEID { IDLE, WALK, ATTACK, DEATH, BERSSTATE_END };
enum class TANKERSTATEID { IDLE, WALK, ATTACK, DEATH, TANKSTATE_END };

enum DIRECTION { LEFT, RIGHT, UP, DOWN, DIR_END };

enum OBB_DIRECTION { TOP_LEFT, TOP_RIGHT, BOTTOM_LEFT, BOTTOM_RIGHT, OBB_DIR_END};

enum OBJID {  PLAYER, BERSERKER, RANGER, TANKER,PLAYER_BULLET, MONSTER_BULLET,SKILL, DOOR, SELECT_DOOR, LAMB, HP_BAR,  MONSTER, BOSS, ITEM, BUTTON,  OBJID_END };
//ARROW,SKILL,
enum RENDERID {BACKGROUND, UI,GAMEOBJECT, EFFECT, SUPER_UI, RENDER_END };

enum SCENEID { SC_MENU, SC_EDIT, SC_LOBBY, SC_MAP, SC_STAGE, SC_FIELD, SC_END };

enum UI_ID {UI_OPEN, UI_CLOSE, UI_END};

enum CHANNELID { SOUND_EFFECT, SOUND_BGM,TITLE_BGM, LOBBY_BGM, STAGE_BGM, FIELD_BGM, MAXCHANNEL };

enum class BONEKNIGHTSTATEID { IDLE, ATTACK, SLAM, BLEEDING, THROW_SWORD, DEATH, STATE_END};

template<typename T>
void Safe_Delete(T& Temp)
{
	if (Temp)
	{
		delete Temp;
		Temp = nullptr;
	}
}

class CDeleteObj
{
public:
	template<typename T>
	void operator()(T& Temp)
	{
		if (Temp)
		{
			delete Temp;
			Temp = nullptr;
		}
	}
};
class CDeleteMap
{
public:
	template<typename T>
	void operator()(T& Pair)
	{
		if (Pair.second)
		{
			delete Pair.second;
			Pair.second = nullptr;
		}
	}
};

class CTag_Finder
{
public:
	CTag_Finder(const TCHAR* pString) : m_pString(pString) {}
public:
	template<typename T>
	bool operator()(T& Pair)
	{
		return !lstrcmp(m_pString, Pair.first);
	}

private:
	const TCHAR* m_pString;
};



typedef	struct tagLinePoint
{
	tagLinePoint() { ZeroMemory(this, sizeof(tagLinePoint)); }
	tagLinePoint(float _fX, float _fY) : fX(_fX), fY(_fY) {}

	float	fX;
	float	fY;

}LINEPOINT;

typedef struct tagLine
{
	tagLine() { ZeroMemory(this, sizeof(tagLine)); }
	tagLine(LINEPOINT& _tLpoint, LINEPOINT& _tRpoint)
		: tLpoint(_tLpoint), tRpoint(_tRpoint) { }

	LINEPOINT	tLpoint;
	LINEPOINT	tRpoint;

}LINE;


typedef struct tagFrame
{
	int			iFrameStart;
	int			iFrameEnd;
	int			iMotion;

	DWORD			dwSpeed;
	ULONGLONG		dwTime;

}FRAME;

extern HWND g_hWnd;
