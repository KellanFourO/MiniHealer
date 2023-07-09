#include "BoneKnight.h"
#include "BmpMgr.h"
#include "KeyMgr.h"
#include "ObjMgr.h"
#include "CollisionMgr.h"
#include "SceneMgr.h"
#include "BoneKnightSlam.h"
#include "BoneKnightThrowSword.h"
#include "AbstractFactory.h"


CBoneKnight::CBoneKnight()
	:m_dwPatternDelay(GetTickCount64()), m_ulAttackCountDelay(GetTickCount64()),
	m_bThrow(false), m_bSlam(false), m_bSwitch(true),
	iAttackCount(0), m_iSlamStart(0), m_iSlamEnd(0)
{
}


CBoneKnight::~CBoneKnight()
{
}

void CBoneKnight::Initialize(void)
{
	m_tInfo.fCX = 357.f;
	m_tInfo.fCY = 315.f;

	m_tInfo.fX = 850.f;
	m_tInfo.fY = 565.f;
	 
	m_tWeaponInfo.fCX = 150.f;
	m_tWeaponInfo.fCY = 150.f;

	m_tWeaponInfo.fX = m_tInfo.fX - 100; // 최하단
	m_tWeaponInfo.fY = m_tInfo.fY + 80; // 최하단

	m_fAngle = 0.f;

	Setting_Img();


	m_ePreState = BONEKNIGHTSTATEID::STATE_END;
	m_eCurState = BONEKNIGHTSTATEID::IDLE;
	m_eRender = GAMEOBJECT;
	
	m_pName = L"해골 기사";
	m_iNumber = 1;
	m_iExp = 195;
	m_iGold = 24;
	m_tClearTime.m_iHour = 0;
	m_tClearTime.m_iMinute = 0;
	m_tClearTime.m_lSecond = 0;
	

	m_tStatus.m_iHp = 2520;
	m_tStatus.m_iMaxHp = 2520;
	m_tStatus.m_iAttack = 38;
	m_tStatus.m_iAttackSpeed = 0.80f;


	
	m_fAngle = 0.f;
	iAttackCount = 0;
	m_bSwitch = true;

	m_eDir = LEFT;
	m_pFrameKey = L"BoneKnight";
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 6;
	m_tFrame.dwSpeed = 100;
	m_tFrame.iMotion = 0;
	m_tFrame.dwTime = GetTickCount64();

	if (CSceneMgr::Get_Instance()->Get_SceneID() == SC_STAGE)
	{
		m_bSwitch = false;
	}

	
}

int CBoneKnight::Update(void)
{
	if (m_bDead)
		m_eCurState = BONEKNIGHTSTATEID::DEATH;

	if (m_bSlam)
	{
		CObjMgr::Get_Instance()->Add_Object(MONSTER_BULLET,Create_Slam(LEFT));
		CObjMgr::Get_Instance()->Add_Object(MONSTER_BULLET, Create_Slam(RIGHT));
		
		CObjMgr::Get_Instance()->Add_Object(MONSTER_BULLET, Create_Slam2(LEFT));
		CObjMgr::Get_Instance()->Add_Object(MONSTER_BULLET, Create_Slam2(RIGHT));

		CObjMgr::Get_Instance()->Add_Object(MONSTER_BULLET, Create_Slam3(LEFT));
		CObjMgr::Get_Instance()->Add_Object(MONSTER_BULLET, Create_Slam3(RIGHT));
		
		

		m_bSlam = false;
	}

	if(m_bThrow)
	{
		CObjMgr::Get_Instance()->Add_Object(MONSTER_BULLET, Create_ThrowSword());
		
		m_bThrow = false;
	}

	Boss_AI();

	Motion_Change();

	if (CKeyMgr::Get_Instance()->Key_Pressing('A'))
	{
		m_fAngle += 5;
	}

	__super::Move_Frame();
	__super::Update_Rect();
	Create_Collision();


	return OBJ_NOEVENT;
}


void CBoneKnight::Late_Update(void)
{
	if (m_tStatus.m_iHp == 0)
	{
		m_bDead = true;
	}

	if (m_eCurState == BONEKNIGHTSTATEID::ATTACK)
	{
		if (m_ulAttackCountDelay + 100 < GetTickCount64())
		{
			if (m_tFrame.iFrameStart == 0)
				++iAttackCount;

			m_ulAttackCountDelay = GetTickCount64();
		}
	}

}

void CBoneKnight::Render(HDC hDC)
{
	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Img(m_pFrameKey);

	SelectObject(hDC, GetStockObject(DC_PEN));
	SetDCPenColor(hDC, RGB(255, 255, 255));

	Rectangle(hDC, m_tWeaponRect.left, m_tWeaponRect.top, m_tWeaponRect.right, m_tWeaponRect.bottom);

	GdiTransparentBlt(hDC,
		(int)m_tRect.left, // 복사 받을 위치 X,Y 좌표
		(int)m_tRect.top,
		(int)m_tInfo.fCX,	// 복사 받을 가로, 세로 길이
		(int)m_tInfo.fCY,
		hMemDC,			// 비트맵 이미지를 담고 있는 DC
		m_tFrame.iFrameStart * 357,					// 비트맵을 출력할 시작 X,Y좌표
		m_tFrame.iMotion * 315,
		357,		// 출력할 비트맵의 가로, 세로 사이즈
		315,
		RGB(255, 0, 255)); // 제거하고자 하는 색상
}

void CBoneKnight::Release(void)
{
}

void CBoneKnight::Setting_Img()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/Boss/BoneKnight.bmp", L"BoneKnight");
}

void CBoneKnight::Motion_Change()
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case BONEKNIGHTSTATEID::IDLE:
			if (m_eDir == LEFT)
			{
				m_iStart = 5;
				m_tFrame.iMotion = 0;
				m_tFrame.iFrameStart = 5;
				m_tFrame.iFrameEnd = 0;
				m_tFrame.dwSpeed = 120;
				m_tFrame.dwTime = GetTickCount64();
			}
			else
			{
				m_tFrame.iMotion = 1;
				m_tFrame.iFrameStart = 6;
				m_tFrame.iFrameEnd = 11;
				m_tFrame.dwSpeed = 120;
				m_tFrame.dwTime = GetTickCount64();
			}
			break;

		
		case BONEKNIGHTSTATEID::ATTACK:
			if (m_eDir == LEFT)
			{
				m_tFrame.iMotion = 2;
				m_iStart = 9;
				m_tFrame.iFrameStart = 9;
				m_tFrame.iFrameEnd = 0;
				m_tFrame.dwSpeed = 120;
				m_tFrame.dwTime = GetTickCount64();
			}
			else
			{
				m_tFrame.iMotion = 3;
				m_tFrame.iFrameStart = 0;
				m_tFrame.iFrameEnd = 9;
				m_tFrame.dwSpeed = 120;
				m_tFrame.dwTime = GetTickCount64();
			}
			break;

		case BONEKNIGHTSTATEID::SLAM:
			if (m_eDir == LEFT)
			{
				m_tFrame.iMotion = 2;
				m_iStart = 9;
				m_iSlamStart = 9;
				m_iSlamEnd = 0;
				m_tFrame.dwSpeed = 120;
				m_tFrame.dwTime = GetTickCount64();
			}
			else
			{
				m_tFrame.iMotion = 3;
				m_iSlamStart = 2;
				m_iSlamEnd = 11;
				m_tFrame.dwSpeed = 120;
				m_tFrame.dwTime = GetTickCount64();
			}
			break;

		case BONEKNIGHTSTATEID::BLEEDING:
			if (m_eDir == LEFT)
			{
				m_tFrame.iMotion = 4;
				m_iStart = 11;
				m_tFrame.iFrameStart = 11;
				m_tFrame.iFrameEnd = 0;
				m_tFrame.dwSpeed = 120;
				m_tFrame.dwTime = GetTickCount64();
			}
			else
			{
				m_tFrame.iMotion = 5;
				m_tFrame.iFrameStart = 0;
				m_tFrame.iFrameEnd = 11;
				m_tFrame.dwSpeed = 120;
				m_tFrame.dwTime = GetTickCount64();
			}

			break;

		case BONEKNIGHTSTATEID::THROW_SWORD:
			if (m_eDir == LEFT)
			{
				m_tFrame.iMotion = 4;
				m_iStart = 11;
				m_tFrame.iFrameStart = 11;
				m_tFrame.iFrameEnd = 0;
				m_tFrame.dwSpeed = 120;
				m_tFrame.dwTime = GetTickCount64();
			}
			else
			{
				m_tFrame.iMotion = 5;
				m_tFrame.iFrameStart = 0;
				m_tFrame.iFrameEnd = 11;
				m_tFrame.dwSpeed = 120;
				m_tFrame.dwTime = GetTickCount64();
			}
			break;

		case BONEKNIGHTSTATEID::DEATH:
			if (m_eDir == LEFT)
			{
				m_iStart = 5;
				m_tFrame.iFrameStart = 5;
				m_tFrame.iFrameEnd = 0;
				m_tFrame.dwSpeed = 120;
				m_tFrame.dwTime = GetTickCount64();
			}
			else
			{
				m_tFrame.iFrameStart = 11;
				m_tFrame.iFrameEnd = 6;
				m_tFrame.dwSpeed = 120;
				m_tFrame.dwTime = GetTickCount64();
			}
			break;
		}
		m_ePreState = m_eCurState;
	}
}

void CBoneKnight::Boss_AI()
{
	if (m_bSwitch && CObjMgr::Get_Instance()->Get_Tanker()->Get_Info().fX >= m_tInfo.fX - 100)
	{
		m_eCurState = BONEKNIGHTSTATEID::ATTACK;
		m_bSwitch = false;
	}

	

	if (iAttackCount == 3 && !m_bSlam)
	{
		m_eCurState = BONEKNIGHTSTATEID::SLAM;
		m_bSlam = true;
	}
	
	if (m_eCurState == BONEKNIGHTSTATEID::SLAM)
	{
		if (m_dwPatternDelay + 2000 < GetTickCount64())
		{

			++iAttackCount;

			m_dwPatternDelay = GetTickCount64();
		}
	}

	if (iAttackCount == 6 && !m_bThrow)
	{
		m_bSlam = false;
		m_eCurState = BONEKNIGHTSTATEID::THROW_SWORD;
		
	}


	
}


void CBoneKnight::Motion_Change2()
{
	if (m_bSwitch && CObjMgr::Get_Instance()->Get_Player()->Get_Info().fX >= m_tInfo.fX - 100)
	{
		m_eCurState = BONEKNIGHTSTATEID::ATTACK;
		m_bSwitch = false;
	}

	
}

void CBoneKnight::Create_Collision()
{
	

	if (m_eCurState == BONEKNIGHTSTATEID::ATTACK)
	{
		if (m_tFrame.iFrameStart > 7)
		{
			Update_WeaponRect();
		}
		else
		{
			ZeroMemory(&m_tWeaponRect, sizeof(RECT));
		}
	}
	else
		ZeroMemory(&m_tWeaponRect, sizeof(RECT));
	
		
}

CObj* CBoneKnight::Create_Slam(DIRECTION _DIR)
{
	CObj* pObj = CAbstractFactory<CBoneKnightSlam>::Create_SetDir(m_tInfo.fX - 100, m_tInfo.fY + 80,_DIR);
	pObj->Set_Target(m_pTarget);

	return pObj;
}

CObj* CBoneKnight::Create_Slam2(DIRECTION _DIR)
{
	CObj* pObj = CAbstractFactory<CBoneKnightSlam>::Create_SetDir(m_tInfo.fX - 20, m_tInfo.fY + 80, _DIR);
	pObj->Set_Target(m_pTarget);

	return pObj;
}

CObj* CBoneKnight::Create_Slam3(DIRECTION _DIR)
{
	CObj* pObj = CAbstractFactory<CBoneKnightSlam>::Create_SetDir(m_tInfo.fX + 40, m_tInfo.fY + 80, _DIR);
	pObj->Set_Target(m_pTarget);

	return pObj;
}

CObj* CBoneKnight::Create_ThrowSword()
{
	CObj* pObj = CAbstractFactory<CBoneKnightThrowSword>::Create(m_tInfo.fX, m_tInfo.fY - 400);
	
	return pObj;
}


