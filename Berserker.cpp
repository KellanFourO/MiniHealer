#include "framework.h"
#include "Berserker.h"
#include "AbstractFactory.h"
#include "ObjMgr.h"
#include "KeyMgr.h"
#include "SceneMgr.h"
#include "BmpMgr.h"

CBerserker::CBerserker()
	: m_bJump(false)
	, m_fPower(0.f), m_fTime(0.f)
{
}

CBerserker::~CBerserker()
{
	Release();
}

void CBerserker::Initialize(void)
{

	m_tInfo = { 700.f, 655.f, 114.f, 114.f };

	m_pName = L"버서커";
	m_tStatus.m_iHp = 430;
	m_tStatus.m_iMaxHp = 430;
	m_tStatus.m_iHpRecovery = 3.1f;
	m_tStatus.m_iAttack = 70;
	m_tStatus.m_iAttackSpeed = 0.37f;
	
	m_fSpeed = 3.f;
	m_fDistance = 70.f;
	m_eDir = RIGHT;
	m_eRender = GAMEOBJECT;

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 2;
	m_tFrame.iMotion = 0;
	m_tFrame.dwSpeed = 200;
	m_tFrame.dwTime = GetTickCount64();
	m_pFrameKey = L"BerserkerIdleA";

	m_tWeaponInfo.fCX = 50.f;
	m_tWeaponInfo.fCY = 60.f;

	m_iAttackCount = 0;
	Setting_Img();
}

int CBerserker::Update(void)
{
	if (Get_Start())
	{

		m_pFrameKey = L"BerserkerWalkA";
		m_tInfo.fX += m_fSpeed;
		m_eBerserCur = BERSERKERSTATEID::WALK;

	}
	
	Create_Collision();

	if (CSceneMgr::Get_Instance()->Get_SceneID() == SC_LOBBY)
		Random_Move();
	
	if (CSceneMgr::Get_Instance()->Get_SceneID() == SC_FIELD)
	{
		AI_Target();
		Chase_Attack();
	}

	Motion_Change();
	__super::Move_Frame();
	__super::Update_Rect();

	return OBJ_NOEVENT;
}
void CBerserker::Late_Update(void)
{
	if (m_eDir == LEFT)
	{
		m_tWeaponInfo.fX = m_tInfo.fX - 30;
		m_tWeaponInfo.fY = m_tInfo.fY + 30;
	}
	else
	{
		m_tWeaponInfo.fX = m_tInfo.fX + 30;
		m_tWeaponInfo.fY = m_tInfo.fY + 30;
	}

	if (m_eBerserCur == BERSERKERSTATEID::ATTACK)
	{
		if (m_ulAttackCountDelay + 100 < GetTickCount64())
		{
			if (m_tFrame.iFrameStart == 0)
				++m_iAttackCount;

			m_ulAttackCountDelay = GetTickCount64();
		}
	}

	Recovery();
}

void CBerserker::Render(HDC hDC)
{
	//int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScollX();
	//int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScollY();

	//Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Img(m_pFrameKey);

	SelectObject(hDC, GetStockObject(DC_PEN));
	SetDCPenColor(hDC, RGB(255, 255, 255));

	Rectangle(hDC, m_tWeaponRect.left, m_tWeaponRect.top, m_tWeaponRect.right, m_tWeaponRect.bottom);
	
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

void CBerserker::Release(void)
{
}

void CBerserker::Motion_Change(void)
{
	if (m_eBerserPre != m_eBerserCur)
	{
		switch (m_eBerserCur)
		{
		case BERSERKERSTATEID::IDLE:
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

		case BERSERKERSTATEID::WALK:
			if (m_eDir == LEFT)
			{

				m_tFrame.iMotion = 1;
				m_iStart = 3;
				m_tFrame.iFrameStart = 3;

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
				m_tFrame.iFrameEnd = 3;

				m_tFrame.iFrameStart = 0;
				m_tFrame.iFrameEnd = 4;

				m_tFrame.dwSpeed = 200;
				m_tFrame.dwTime = GetTickCount64();
			}
			break;

		case BERSERKERSTATEID::ATTACK:
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


		case BERSERKERSTATEID::DEATH:
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
		m_eBerserPre = m_eBerserCur;
	}

}


void CBerserker::Random_Move()
{
	if (m_bMoveSwitch)
	{
		m_pFrameKey = L"BerserkerWalkA";
		m_eBerserCur = BERSERKERSTATEID::WALK;

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
			m_eBerserCur = BERSERKERSTATEID::IDLE;
			m_dwNpcMoveDelay = GetTickCount64();
		}
	}
	else
	{
		m_pFrameKey = L"BerserkerIdleA";
		if (m_dwNpcMoveDelay + 2000 < GetTickCount64())
		{
			m_bMoveSwitch = true;
			m_dwNpcMoveDelay = GetTickCount64();
		}
	}
}

void CBerserker::Create_Collision()
{
	if (m_eBerserCur == BERSERKERSTATEID::ATTACK)
	{
		if (m_tFrame.iFrameStart > 2)
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


void CBerserker::Setting_Img()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/Player/Berserker/BerserkerIdleA.bmp", L"BerserkerIdleA");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/Player/Berserker/BerserkerWalkA.bmp", L"BerserkerWalkA");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/Player/Berserker/BerserkerAtk.bmp", L"BerserkerAtk");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/Player/Berserker/BerserkerDeath.bmp", L"BerserkerDeath");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/Player/Berserker/BerserkerJumpA.bmp", L"BerserkerJumpA");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/Player/Berserker/BerserkerJumpB.bmp", L"BerserkerJumpB");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/Player/Berserker/BerserkerCast.bmp", L"BerserkerCast");

}
