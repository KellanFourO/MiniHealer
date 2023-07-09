#include "framework.h"
#include "Ranger.h"
#include "AbstractFactory.h"
#include "ObjMgr.h"
#include "KeyMgr.h"
#include "SceneMgr.h"
#include "BmpMgr.h"
#include "BasicArrow.h"

CRanger::CRanger()
	: m_bJump(false)
	, m_fPower(0.f), m_fTime(0.f)
	, m_ulCreateBulletDelay(GetTickCount64())
{
}

CRanger::~CRanger()
{
	Release();
}

void CRanger::Initialize(void)
{
	m_pName = L"레인저";
	m_tInfo = { 500.f, 655.f, 114.f, 114.f };
	m_tStatus.m_iHp = 295;
	m_tStatus.m_iMaxHp = 295;
	m_tStatus.m_iAttack = 28;
	m_tStatus.m_iAttackSpeed = 1.33f;
	m_tStatus.m_iHpRecovery = 3.1;
	m_fSpeed = 3.f;
	m_fDistance = 500.f;
	m_fPower = 20.f;

	m_eDir = RIGHT;
	m_eRender = GAMEOBJECT;

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 2;
	m_tFrame.iMotion = 0;
	m_tFrame.dwSpeed = 200;
	m_tFrame.dwTime = GetTickCount64();

	m_pFrameKey = L"RangerIdleA";
	Setting_Img();

	m_iAttackCount = 0;

}

int CRanger::Update(void)
{
	if (Get_Start())
	{
		m_pFrameKey = L"RangerWalkA";
		m_tInfo.fX += m_fSpeed;
		m_eRangerCur = RANGERSTATEID::WALK;

	}

	if (CSceneMgr::Get_Instance()->Get_SceneID() == SC_LOBBY)
		Random_Move();

	if (CSceneMgr::Get_Instance()->Get_SceneID() == SC_FIELD)
	{
		AI_Target();
		Chase_Attack();
	}

	if (m_eRangerCur == RANGERSTATEID::ATTACK)
	{
		if (m_ulCreateBulletDelay + 1000 < GetTickCount64())
		{
			CObjMgr::Get_Instance()->Add_Object(PLAYER_BULLET, Create_Bullet());

			m_ulCreateBulletDelay = GetTickCount64();
			++m_iAttackCount;
		}
	}

	Motion_Change();
	__super::Move_Frame();
	__super::Update_Rect();

	return OBJ_NOEVENT;
}
void CRanger::Late_Update(void)
{
	Recovery();
}

void CRanger::Render(HDC hDC)
{
	//int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScollX();
	//int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScollY();

	//Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Img(m_pFrameKey);

	GdiTransparentBlt(hDC,
		(int)m_tRect.left, // 복사 받을 위치 X,Y 좌표
		(int)m_tRect.top,
		(int)m_tInfo.fCX,	// 복사 받을 가로, 세로 길이
		(int)m_tInfo.fCY,
		hMemDC,			// 비트맵 이미지를 담고 있는 DC
		m_tFrame.iFrameStart * (int)m_tInfo.fCX,					// 비트맵을 출력할 시작 X,Y좌표
		m_tFrame.iMotion * (int)m_tInfo.fCY,
		(int)m_tInfo.fCX,		// 출력할 비트맵의 가로, 세로 사이즈
		(int)m_tInfo.fCY,
		RGB(255, 0, 255)); // 제거하고자 하는 색상


}

void CRanger::Release(void)
{
}

void CRanger::Motion_Change(void)
{
	if (m_eRangerPre != m_eRangerCur)
	{
		switch (m_eRangerCur)
		{
		case RANGERSTATEID::IDLE:
			if (m_eDir == LEFT)
			{
				m_tFrame.iMotion = 1;
				m_iStart = 2;
				m_tFrame.iFrameStart = 2;
				m_tFrame.iFrameEnd = 0;
				m_tFrame.dwSpeed = 200;
				m_tFrame.dwTime = GetTickCount64();
			}
			else
			{
				m_tFrame.iMotion = 0;
				m_tFrame.iFrameStart = 0;
				m_tFrame.iFrameEnd = 2;
				m_tFrame.dwSpeed = 200;
				m_tFrame.dwTime = GetTickCount64();
			}
			break;

		case RANGERSTATEID::WALK:
			if (m_eDir == LEFT)
			{
				m_tFrame.iMotion = 1;
				m_iStart = 3;
				m_tFrame.iFrameStart = 3;
				m_tFrame.iFrameEnd = 0;
				m_tFrame.dwSpeed = 200;
				m_tFrame.dwTime = GetTickCount64();
			}
			else
			{
				m_tFrame.iMotion = 0;
				m_tFrame.iFrameStart = 0;
				m_tFrame.iFrameEnd = 3;
				m_tFrame.dwSpeed = 200;
				m_tFrame.dwTime = GetTickCount64();
			}
			break;

		case RANGERSTATEID::ATTACK:
			if (m_eDir == LEFT)
			{
				m_tFrame.iMotion = 1;
				m_iStart = 3;
				m_tFrame.iFrameStart = 3;
				m_tFrame.iFrameEnd = 0;
				m_tFrame.dwSpeed = 200;
				m_tFrame.dwTime = GetTickCount64();
			}
			else
			{
				m_tFrame.iMotion = 0;
				m_tFrame.iFrameStart = 0;
				m_tFrame.iFrameEnd = 3;
				m_tFrame.dwSpeed = 200;
				m_tFrame.dwTime = GetTickCount64();
			}

			break;


		case RANGERSTATEID::DEATH:
			if (m_eDir == LEFT)
			{
				m_tFrame.iMotion = 1;
				m_iStart = 4;
				m_tFrame.iFrameStart = 4;
				m_tFrame.iFrameEnd = 0;
				m_tFrame.dwSpeed = 200;
				m_tFrame.dwTime = GetTickCount64();
			}
			else
			{
				m_tFrame.iMotion = 0;
				m_tFrame.iFrameStart = 0;
				m_tFrame.iFrameEnd = 4;
				m_tFrame.dwSpeed = 200;
				m_tFrame.dwTime = GetTickCount64();
			}
			break;
		}
		m_eRangerPre = m_eRangerCur;
	}

}

void CRanger::Random_Move()
{
	if (m_bMoveSwitch)
	{
		m_pFrameKey = L"RangerWalkA";
		m_eRangerCur = RANGERSTATEID::WALK;

		if (m_tInfo.fX >= 1260)
		{
			m_eDir = LEFT;
			m_tFrame.iMotion = 1;
		}

		if (m_tInfo.fX <= 20)
		{
			m_eDir = RIGHT;
			m_tFrame.iMotion = 0;
		}

		if (m_eDir)
			m_tInfo.fX += 2.f;
		else
			m_tInfo.fX -= 2.f;

		if (m_dwNpcMoveDelay + 2000 < GetTickCount64())
		{
			if (rand() % 2)
				m_eDir = RIGHT;
			else
				m_eDir = LEFT;

			m_bMoveSwitch = false;
			m_eRangerCur = RANGERSTATEID::IDLE;
			m_dwNpcMoveDelay = GetTickCount64();
		}
	}
	else
	{
			m_pFrameKey = L"RangerIdleA";
		if (m_dwNpcMoveDelay + 2000 < GetTickCount64())
		{
			m_dwNpcMoveDelay = GetTickCount64();
			m_bMoveSwitch = true;
		}
	}
}

CObj* CRanger::Create_Bullet()
{
	CObj* pObj = CAbstractFactory<CBasicArrow>::Create(m_tInfo.fX, m_tInfo.fY);
	pObj->Set_Target(m_pTarget);


	return pObj;
}

void CRanger::Setting_Img()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/Player/Ranger/RangerIdleA.bmp", L"RangerIdleA");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/Player/Ranger/RangerWalkA.bmp", L"RangerWalkA");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/Player/Ranger/RangerAtk.bmp", L"RangerAtk");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/Player/Ranger/RangerDeath.bmp", L"RangerDeath");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/Player/Ranger/RangerJumpA.bmp", L"RangerJumpA");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/Player/Ranger/RangerJumpB.bmp", L"RangerJumpB");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/Player/Ranger/RangerCast.bmp", L"RangerCast");
}
