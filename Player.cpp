#include "framework.h"
#include "Player.h"
#include "AbstractFactory.h"
#include "ObjMgr.h"
#include "KeyMgr.h"
#include "SceneMgr.h"
#include "BmpMgr.h"
#include "EnergyBolt.h"
#include "PlayerSKill.h"
#include "Heal.h"

CPlayer::CPlayer()
	: m_bJump(false)
	, m_fPower(0.f), m_fTime(0.f)
	, m_ulCreateBulletDelay(GetTickCount64())
{
}

CPlayer::~CPlayer()
{
	Release();
} 

void CPlayer::Initialize(void)
{
	m_pName = L"힐러";
	m_tInfo = { 600.f, 655.f, 114.f, 114.f };
	
	m_tStatus.m_iHp = 330;
	m_tStatus.m_iMaxHp = 330;
	m_tStatus.m_iHpRecovery = 7;
	
	m_tStatus.m_iMp = 1000;
	m_tStatus.m_iMaxMp = 1000;
	m_tStatus.m_iMpRecovery = 8;
	m_tStatus.m_iAttack = 7;
	m_tStatus.m_iAttackSpeed = 1;
	
	m_fSpeed = 3.f;
	m_fDistance = 400.f;
	m_fPower = 20.f;

	m_eRender = GAMEOBJECT;
	m_eDir = RIGHT;
	
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 2;
	m_tFrame.iMotion = 0;
	m_tFrame.dwSpeed = 200;
	m_tFrame.dwTime = GetTickCount64();

	m_pFrameKey = L"HealerIdleA";
	Setting_Img();
	m_bFieldSwitch = true;

	m_iAttackCount = 0;

	
	CObjMgr::Get_Instance()->Add_Object(SKILL,CAbstractFactory<CHeal>::Create());	
	m_vecSkill.push_back(CObjMgr::Get_Instance()->Get_Objects(SKILL).back());
	
	/*
		이니셜라이즈 때 생성한다.

		
		렌더도 마찬가지로 필드에있을 경우에만 
		필드에 있을 경우에만 사용할 수 있게 한다.
	
	*/
	
}

int CPlayer::Update(void)
{



	if (CSceneMgr::Get_Instance()->Get_SceneID() == SC_FIELD)
	{
		if (m_bFieldSwitch)
		{
			Start_Target();
		}

		Chase_Attack();
		Change_SkillTarget();
	}

	if (Get_Start())
	{
		m_tInfo.fX += m_fSpeed;
		m_pFrameKey = L"HealerWalkA";
		m_eHealerCur = HEALERSTATEID::WALK;
	}

	
		if (m_eHealerCur == HEALERSTATEID::ATTACK)
		{
			if (m_ulCreateBulletDelay + 1000 < GetTickCount64())
			{
				CObjMgr::Get_Instance()->Add_Object(PLAYER_BULLET, Create_Bullet());

				m_ulCreateBulletDelay = GetTickCount64();
				++m_iAttackCount;
				
			}
		}
	
	


	if (CSceneMgr::Get_Instance()->Get_SceneID() != SC_MENU && CSceneMgr::Get_Instance()->Get_SceneID() != SC_STAGE)
		Key_Input();

	if (CKeyMgr::Get_Instance()->Key_Down(VK_TAB))
	{
		Target_Change();
	}
	
	//Jump();
	Motion_Change();

	
	__super::Update_Rect();
	__super::Move_Frame();

	

	return OBJ_NOEVENT;
}
void CPlayer::Late_Update(void)
{
	


	Recovery();
}

void CPlayer::Render(HDC hDC)
{

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

void CPlayer::Release(void)
{
	for (int i = 0; i < m_vecSkill.size(); ++i)
	{
		Safe_Delete<CObj*>(m_vecSkill[i]);
	}

	m_vecSkill.clear();
}

void CPlayer::Key_Input(void)
{
	float	fY = 0.f;


		if (CKeyMgr::Get_Instance()->Key_Pressing(VK_LEFT))
		{
			m_tInfo.fX -= m_fSpeed;
			m_pFrameKey = L"HealerWalkA";
			m_eDir = LEFT;
			m_tFrame.iMotion = 1;
			m_eHealerCur = HEALERSTATEID::WALK;
		}

		if (CKeyMgr::Get_Instance()->Key_Pressing(VK_RIGHT))
		{
			m_tInfo.fX += m_fSpeed;
			m_pFrameKey = L"HealerWalkA";
			m_eDir = RIGHT;
			m_tFrame.iMotion = 0;
			m_eHealerCur = HEALERSTATEID::WALK;
		}
		

		else if (CKeyMgr::Get_Instance()->Key_Pressing('O'))
		{
			if (m_eDir == LEFT)
			{
				m_eHealerCur = HEALERSTATEID::DEATH;
				m_pFrameKey = L"HealerDeath";
			}
			else
			{
				m_eHealerCur = HEALERSTATEID::DEATH;
				m_pFrameKey = L"HealerDeath";
				m_tFrame.iMotion = 0;
			}
		}

		else if (CKeyMgr::Get_Instance()->Key_Pressing('P'))
		{
			if (m_eDir == LEFT)
			{
				m_eHealerCur = HEALERSTATEID::ATTACK;
				m_pFrameKey = L"HealerAtk";
				m_tFrame.iMotion = 1;
			}
			else
			{
				m_eHealerCur = HEALERSTATEID::ATTACK;
				m_pFrameKey = L"HealerAtk";
				m_tFrame.iMotion = 0;
			}

		}
		else if (CKeyMgr::Get_Instance()->Key_Pressing('I'))
		{
			if (m_eDir == LEFT)
			{
				m_eHealerCur = HEALERSTATEID::CAST;
				m_pFrameKey = L"HealerCast";
				m_tFrame.iMotion = 1;
			}
			else
			{
				m_eHealerCur = HEALERSTATEID::CAST;
				m_pFrameKey = L"HealerCast";
				m_tFrame.iMotion = 0;
			}

		}

		else if (CKeyMgr::Get_Instance()->Key_Pressing(VK_SPACE))
				m_bJump = true;

		else if (CKeyMgr::Get_Instance()->Key_Down(VK_TAB))
				Target_Change();


		else if (m_eDir == LEFT )
		{
			m_pFrameKey = L"HealerIdleA";
			m_tFrame.iMotion = 1;
			m_eHealerCur = HEALERSTATEID::IDLE;
		}
		else if (m_eDir == RIGHT)
		{
			m_pFrameKey = L"HealerIdleA";
			m_tFrame.iMotion = 0;
			m_eHealerCur = HEALERSTATEID::IDLE;
		}


}


void CPlayer::Motion_Change(void)
{
	if (m_eHealerPre != m_eHealerCur)
	{
		switch (m_eHealerCur)
		{
		case HEALERSTATEID::IDLE:
			if(m_eDir == LEFT)
			{
				m_iStart = 2;
				m_tFrame.iFrameStart = 2;
				m_tFrame.iFrameEnd = 0;
				m_tFrame.dwSpeed = 200;
				m_tFrame.dwTime = GetTickCount64();
			}
			else
			{
				m_tFrame.iFrameStart = 0;
				m_tFrame.iFrameEnd = 2;
				m_tFrame.dwSpeed = 200;
				m_tFrame.dwTime = GetTickCount64();
			}
			break;

		case HEALERSTATEID::WALK:
			if (m_eDir == LEFT)
			{
				m_iStart = 4;
				m_tFrame.iFrameStart = 4;
				m_tFrame.iFrameEnd = 0;
				m_tFrame.dwSpeed = 200;
				m_tFrame.dwTime = GetTickCount64();
			}
			else
			{
				m_tFrame.iFrameStart = 0;
				m_tFrame.iFrameEnd = 4;
				m_tFrame.dwSpeed = 200;
				m_tFrame.dwTime = GetTickCount64();
			}		
			break;

		case HEALERSTATEID::JUMP:
			m_iStart = 0;
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 0;
			m_tFrame.dwSpeed = 0;
			m_tFrame.dwTime = GetTickCount64();
			break;
		

		case HEALERSTATEID::ATTACK:
			if (m_eDir == LEFT)
			{
				m_iStart = 3;
				m_tFrame.iFrameStart = 3;
				m_tFrame.iFrameEnd = 0;
				m_tFrame.dwSpeed = 200;
				m_tFrame.dwTime = GetTickCount64();
			}
			else
			{
				m_tFrame.iFrameStart = 0;
				m_tFrame.iFrameEnd = 3;
				m_tFrame.dwSpeed = 200;
				m_tFrame.dwTime = GetTickCount64();
			}
			
			break;

		case HEALERSTATEID::CAST:
			if (m_eDir == LEFT)
			{
				m_iStart = 4;
				m_tFrame.iFrameStart = 4;
				m_tFrame.iFrameEnd = 0;
				m_tFrame.dwSpeed = 200;
				m_tFrame.dwTime = GetTickCount64();
			}
			else
			{
				m_tFrame.iFrameStart = 0;
				m_tFrame.iFrameEnd = 4;
				m_tFrame.dwSpeed = 200;
				m_tFrame.dwTime = GetTickCount64();
			}
			break;

		case HEALERSTATEID::DEATH:
			if (m_eDir == LEFT)
			{
				m_iStart = 4;
				m_tFrame.iFrameStart = 4;
				m_tFrame.iFrameEnd = 0;
				m_tFrame.dwSpeed = 200;
				m_tFrame.dwTime = GetTickCount64();
			}
			else
			{
				m_tFrame.iFrameStart = 0;
				m_tFrame.iFrameEnd = 4;
				m_tFrame.dwSpeed = 200;
				m_tFrame.dwTime = GetTickCount64();
			}
			break;
		}
		m_eHealerPre = m_eHealerCur;
	}

}

CObj* CPlayer::Create_Bullet()
{
	CObj* pObj = CAbstractFactory<CEnergyBolt>::Create(m_tInfo.fX, m_tInfo.fY);
	pObj->Set_Target(m_pTarget);
	

	return pObj;
}

void CPlayer::Change_SkillTarget()
{
	if (CKeyMgr::Get_Instance()->Key_Down('Q'))
	{
		for (int i = 0; i < m_vecSkill.size(); ++i)
		{
			dynamic_cast<CPlayerSKill*>(m_vecSkill[i])->Set_SkillTarget(CObjMgr::Get_Instance()->Get_Tanker());
		}
	}
	else if (CKeyMgr::Get_Instance()->Key_Down('W'))
	{
		for (int i = 0; i < m_vecSkill.size(); ++i)
		{
			dynamic_cast<CPlayerSKill*>(m_vecSkill[i])->Set_SkillTarget(CObjMgr::Get_Instance()->Get_Berserker());
		}
	}
	else if (CKeyMgr::Get_Instance()->Key_Down('E'))
	{
		for (int i = 0; i < m_vecSkill.size(); ++i)
		{
			dynamic_cast<CPlayerSKill*>(m_vecSkill[i])->Set_SkillTarget(this);
		}
	}
	else if (CKeyMgr::Get_Instance()->Key_Down('R'))
	{
		for (int i = 0; i < m_vecSkill.size(); ++i)
		{
			dynamic_cast<CPlayerSKill*>(m_vecSkill[i])->Set_SkillTarget(CObjMgr::Get_Instance()->Get_Ranger());
		}
	}
}

void CPlayer::BattleSetting()
{
}

void CPlayer::Setting_Img()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/Player/Healer/HealerIdleA.bmp",   L"HealerIdleA");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/Player/Healer/HealerWalkA.bmp",   L"HealerWalkA");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/Player/Healer/HealerAtk.bmp",		L"HealerAtk");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/Player/Healer/HealerDeath.bmp",   L"HealerDeath");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/Player/Healer/HealerJumpA.bmp",   L"HealerJumpA");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/Player/Healer/HealerJumpB.bmp", L"HealerJumpB");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/Player/Healer/HealerCast.bmp",    L"HealerCast");

	
	
}

