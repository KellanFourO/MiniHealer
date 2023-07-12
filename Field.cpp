#include "framework.h"
#include "Field.h"
#include "BmpMgr.h"
#include "ObjMgr.h"
#include "AbstractFactory.h"
#include "CollisionMgr.h"
#include "OBB_Collider.h"
#include "KeyMgr.h"
#include "SoundMgr.h"
#include "SceneMgr.h"

#include "BasicStaff.h"


CField::CField():m_pTarget(nullptr),m_TestAngle(0), m_ulCollisionDelay(GetTickCount64()),
m_ulStartTime(GetTickCount64()), m_ulNowTime(GetTickCount64()), m_iHour(0), m_iMinute(0), m_lSecond(0),
m_ulResultChangeDelay(0),m_bBossDie(false),m_bStartChange(false)
{
	ZeroMemory(&m_tBossHpFrameRect, sizeof(RECT));
	ZeroMemory(&m_tBossHpFrameInfo, sizeof(INFO));

	ZeroMemory(&m_tBossHpBarRect, sizeof(RECT));
	ZeroMemory(&m_tBossHpBarInfo, sizeof(INFO));

	ZeroMemory(&m_tTimerRect, sizeof(RECT));
	ZeroMemory(&m_tTimerInfo, sizeof(INFO));
}

CField::~CField()
{
	Release();
}




void CField::Initialize()
{
	CSoundMgr::Get_Instance()->Initialize();
	CSoundMgr::Get_Instance()->StopSound(STAGE_BGM);
	CSoundMgr::Get_Instance()->PlaySoundW(L"BossRoom_bgm.wav",FIELD_BGM,1.f);

	m_pTarget->Initialize();

	CObjMgr::Get_Instance()->Add_Object(BOSS, m_pTarget);

	CObjMgr::Get_Instance()->Get_Ranger()->Set_PosX(100.f);
	CObjMgr::Get_Instance()->Get_Player()->Set_PosX(200.f);
	CObjMgr::Get_Instance()->Get_Berserker()->Set_PosX(300.f);
	CObjMgr::Get_Instance()->Get_Tanker()->Set_PosX(400.f);

	Setting_Img();
	
	m_pHp_UIList.push_back(CAbstractFactory<CPlayerHp>::NonInit_Create(300,150));
	m_pHp_UIList.back()->Set_Target(CObjMgr::Get_Instance()->Get_Tanker());
	m_pHp_UIList.back()->Initialize();

	CObjMgr::Get_Instance()->Add_Object(HP_BAR, m_pHp_UIList.back());

	m_pHp_UIList.push_back(CAbstractFactory<CPlayerHp>::NonInit_Create(300, 250));
	m_pHp_UIList.back()->Set_Target(CObjMgr::Get_Instance()->Get_Berserker());
	m_pHp_UIList.back()->Initialize();

	CObjMgr::Get_Instance()->Add_Object(HP_BAR, m_pHp_UIList.back());

	m_pHp_UIList.push_back(CAbstractFactory<CPlayerHp>::NonInit_Create(300, 350));
	m_pHp_UIList.back()->Set_Target(CObjMgr::Get_Instance()->Get_Player());
	m_pHp_UIList.back()->Initialize();

	CObjMgr::Get_Instance()->Add_Object(HP_BAR, m_pHp_UIList.back());
	
	m_pHp_UIList.push_back(CAbstractFactory<CPlayerHp>::NonInit_Create(300, 450));
	m_pHp_UIList.back()->Set_Target(CObjMgr::Get_Instance()->Get_Ranger());
	m_pHp_UIList.back()->Initialize();

	CObjMgr::Get_Instance()->Add_Object(HP_BAR, m_pHp_UIList.back());
		//CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/Player/Berserker/BerserkerIdleA.bmp", L"BerserkerIdleA");

	m_tBossHpFrameInfo.fCX = 721.f;
	m_tBossHpFrameInfo.fCY = 35.f;
	m_tBossHpFrameInfo.fX = 600.f;
	m_tBossHpFrameInfo.fY = 50.f;

	m_tBossHpBarInfo.fCX = 562.f;
	m_tBossHpBarInfo.fCY = 12.f;
	m_tBossHpBarInfo.fX = 580.f;
	m_tBossHpBarInfo.fY = 50.f;

	m_tTimerInfo.fCX = 35.f;
	m_tTimerInfo.fCY = 35.f;
	m_tTimerInfo.fX = 50.f;
	m_tTimerInfo.fY = 30.f;

	Update_BossHpFrameRect();
	Update_BossHpBarRect();
	Update_TimeRect();
}

void CField::Update()
{
	CObjMgr::Get_Instance()->Update();


}

void CField::Late_Update()
{
	m_pTarget->Late_Update();

	CObjMgr::Get_Instance()->Late_Update();

	if (m_ulCollisionDelay + 250 < GetTickCount64())
	{
		
		Collision();

		m_ulCollisionDelay = GetTickCount64();
	}

	if (m_pTarget->Get_Dead() && !m_bStartChange)
	{
		m_pTarget->Set_ClearTime(m_iHour, m_iMinute, m_lSecond);
		m_bBossDie = true;
	}
	
	if (m_bBossDie)
	{
		m_ulResultChangeDelay = GetTickCount64();
		
		CObjMgr::Get_Instance()->Get_Player()->Set_FrameKey(L"HealerIdleA");
		CObjMgr::Get_Instance()->Get_Berserker()->Set_FrameKey(L"BerserkerIdleA");
		CObjMgr::Get_Instance()->Get_Ranger()->Set_FrameKey(L"RangerIdleA");
		CObjMgr::Get_Instance()->Get_Tanker()->Set_FrameKey(L"TankerIdleA");

		m_bBossDie = false;
		m_bStartChange = true;
	}

	if (m_bStartChange)
	{
		if (m_ulResultChangeDelay + 3000 < GetTickCount64())
		{
			m_bStartChange = false;
			CSceneMgr::Get_Instance()->Scene_Change(SC_Result);
			
		}
	}
	
	
	
}

void CField::Render(HDC hDC)
{
	HDC hMemDC = CBmpMgr::Get_Instance()->Find_Img(L"BossRoom");
	HDC hFloorDC = CBmpMgr::Get_Instance()->Find_Img(L"BossFloor");
	HDC hBossHpFrameDC = CBmpMgr::Get_Instance()->Find_Img(L"Boss_HP_Frame");
	HDC hBossHpBarDC = CBmpMgr::Get_Instance()->Find_Img(L"Boss_HP_ProgressBar");
	HDC hTimeDC = CBmpMgr::Get_Instance()->Find_Img(L"BossRoom_Timer");


	TCHAR szBuff[32] = L"";

	GdiTransparentBlt(hDC, 0, 0, WINCX, WINCY, hMemDC, 0, 0, 1280, 800, RGB(255, 0, 255));
	GdiTransparentBlt(hDC, 0, 0, WINCX, WINCY, hFloorDC, 0, 0, 1280, 800, RGB(255, 0, 255));

	
	

	CObjMgr::Get_Instance()->Render(hDC);

	m_pTarget->Render(hDC);

	GdiTransparentBlt(hDC,
		(int)m_tTimerRect.left,
		(int)m_tTimerRect.top,
		m_tTimerInfo.fX,
		m_tTimerInfo.fY,
		hTimeDC,
		0,
		0,
		35,
		35,
		RGB(255, 0, 255));

	TCHAR sTime[128] = _T("");

	HFONT hFont = CreateFont(14, 0, 0, 0, 0, 0, 0, 0, HANGUL_CHARSET, 0, 0, 0, VARIABLE_PITCH || FF_ROMAN, TEXT("PFStardust"));
	(HFONT)SelectObject(hDC, hFont);
	SetTextColor(hDC, RGB(255, 255, 255));

	m_ulEndTime = GetTickCount64();

	int iDeltaTime = m_ulEndTime - m_ulStartTime;

	m_lSecond = (iDeltaTime / 1000);
	m_iMinute = (m_lSecond % 3600) / 60;
	m_iHour = m_lSecond / 3600;


	swprintf_s(szBuff, L" %d : %d : %d", m_iHour, m_iMinute, m_lSecond);
	TextOut(hDC, (int)m_tTimerInfo.fX + 30, (int)m_tTimerInfo.fY - 10, szBuff, lstrlen(szBuff));
	

	DeleteObject(hFont);

	GdiTransparentBlt
	(hDC, 
	 m_tBossHpFrameRect.left, 
	 m_tBossHpFrameRect.top,
	 m_tBossHpFrameInfo.fCX, 
	 m_tBossHpFrameInfo.fCY, 
	 hBossHpFrameDC,
	 0, 
	 0, 
	 721, 
	 35, 
	 RGB(255, 0, 255));


	float iBossMaxHp = m_pTarget->Get_Status().m_iMaxHp;
	float fBossHpRatio = (static_cast<float>(m_pTarget->Get_Hp()) / iBossMaxHp);

	GdiTransparentBlt
	(hDC,
	m_tBossHpBarRect.left,
	m_tBossHpBarRect.top,
	m_tBossHpBarInfo.fCX * fBossHpRatio,
	m_tBossHpBarInfo.fCY,
	hBossHpBarDC,
	0,
	0,
	m_tBossHpBarInfo.fCX * fBossHpRatio,
	12,
	RGB(255, 0, 255));

	


	 hFont = CreateFont(20, 0, 0, 0, 0, 0, 0, 0, HANGUL_CHARSET, 0, 0, 0, VARIABLE_PITCH || FF_ROMAN, TEXT("PFStardust"));
	(HFONT)SelectObject(hDC, hFont);

	SetTextColor(hDC, RGB(255, 255, 255));
	swprintf_s(szBuff, m_pTarget->Get_Name());
	TextOut(hDC, (int)m_tBossHpFrameRect.left, m_tBossHpFrameInfo.fY - 40, szBuff, lstrlen(szBuff));

	
	swprintf_s(szBuff, L"%.0f", fBossHpRatio * 100);
	TextOut(hDC, (int)m_tBossHpFrameRect.right - 80, m_tBossHpFrameInfo.fY - 10, szBuff, lstrlen(szBuff));

	swprintf_s(szBuff, L"%%");
	TextOut(hDC, (int)m_tBossHpFrameRect.right - 40, m_tBossHpFrameInfo.fY - 10, szBuff, lstrlen(szBuff));
	DeleteObject(hFont);
}

void CField::Release()
{
	CSoundMgr::Get_Instance()->StopSound(FIELD_BGM);
	m_pTarget->Set_HpInit(m_pTarget->Get_Status().m_iMaxHp);

	for (auto iter : m_pHp_UIList)
	{
		iter->Set_Dead();
	}

	Create_Spoil();
	m_pTarget->Set_LateDead();

	m_pHp_UIList.clear();
}

void CField::Setting_Img()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/BackGround/BossRoom.bmp", L"BossRoom");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/BackGround/BossRoomFloor.bmp", L"BossFloor");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/UI/Public/common_bg.bmp", L"common_bg");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/UI/Public/BossRoom_Timer.bmp", L"BossRoom_Timer");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/BackGround/BossRoomFloor.bmp", L"BossRoomFloor");
	
	CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/UI/Boss/Boss_Passive_Frame.bmp", L"Boss_Passive_Frame");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/UI/Boss/Boss_Target.bmp", L"Boss_Target");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/UI/Boss/CastingBG.bmp", L"CastingBG");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/UI/Boss/CastingBar.bmp", L"CastingBar");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/UI/Boss/DeBuff_Abled.bmp", L"DeBuff_Abled");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/UI/Boss/DeBuff_Red_Abled.bmp", L"DeBuff_Red_Abled");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/UI/Boss/Boss_HP_Frame1.bmp", L"Boss_HP_Frame");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/UI/Boss/Boss_HP_ProgressBar1.bmp", L"Boss_HP_ProgressBar");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/UI/Player/Buff_Frame.bmp", L"Buff_Frame");

	
	CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/UI/Player/Select_Frame.bmp", L"Select_Frame");

	
	CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/UI/Player/Player_Target.bmp", L"Player_Target");

	
	CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/UI/Public/Public_Skill_Disabled.bmp", L"Public_Skill_Disabled");
}

void CField::Collision()
{
	if (CCollisionMgr::AABB_Collision_Weapon(m_pTarget,CObjMgr::Get_Instance()->Get_Player()))
	{
		if (!CObjMgr::Get_Instance()->Get_Player()->Get_Dead())
		{
			CObjMgr::Get_Instance()->Get_Player()->Set_Hp(-m_pTarget->Get_Attack());
		}
	}

	if (CCollisionMgr::AABB_Collision_Weapon(m_pTarget,CObjMgr::Get_Instance()->Get_Berserker())) 
	{
		if (!CObjMgr::Get_Instance()->Get_Berserker()->Get_Dead())
		{
			CObjMgr::Get_Instance()->Get_Berserker()->Set_Hp(-m_pTarget->Get_Attack());
		}
	}

	if (CCollisionMgr::AABB_Collision_Weapon(m_pTarget, CObjMgr::Get_Instance()->Get_Ranger())) 
	{
		if (!CObjMgr::Get_Instance()->Get_Ranger()->Get_Dead())
		{
			CObjMgr::Get_Instance()->Get_Ranger()->Set_Hp(-m_pTarget->Get_Attack());
		}
	}

	if (CCollisionMgr::AABB_Collision_Weapon(m_pTarget, CObjMgr::Get_Instance()->Get_Tanker())) 
	{
		if (!CObjMgr::Get_Instance()->Get_Tanker()->Get_Dead())
		{
			CObjMgr::Get_Instance()->Get_Tanker()->Set_Hp(-m_pTarget->Get_Attack());
		}
	}

	if (CCollisionMgr::AABB_Collision_Weapon(CObjMgr::Get_Instance()->Get_Tanker(), m_pTarget))
	{
		if (!m_pTarget->Get_Dead())
		{
			m_pTarget->Set_Hp(-CObjMgr::Get_Instance()->Get_Tanker()->Get_Attack());
		}
	}

	if (CCollisionMgr::AABB_Collision_Weapon(CObjMgr::Get_Instance()->Get_Berserker(), m_pTarget))
	{
		if (!m_pTarget->Get_Dead())
		{
			m_pTarget->Set_Hp(-CObjMgr::Get_Instance()->Get_Berserker()->Get_Attack());
		}
	}

	for (auto& iter : CObjMgr::Get_Instance()->Get_Objects(PLAYER_BULLET))
	{
		if (CCollisionMgr::AABB_Collision(iter, m_pTarget))
		{
			if (!m_pTarget->Get_Dead())
			{
				m_pTarget->Set_Hp(-iter->Get_Attack());
			}
		}
	}

	for (auto& iter : CObjMgr::Get_Instance()->Get_Objects(MONSTER_BULLET))
	{
		if (CCollisionMgr::AABB_Collision(iter, CObjMgr::Get_Instance()->Get_Tanker()))
		{

			if (!CObjMgr::Get_Instance()->Get_Tanker()->Get_Dead())
			{
				
				CObjMgr::Get_Instance()->Get_Tanker()->Set_Hp(-iter->Get_Attack());
				
			}
		}

		if (CCollisionMgr::AABB_Collision(iter, CObjMgr::Get_Instance()->Get_Player()))
		{
			if (!CObjMgr::Get_Instance()->Get_Player()->Get_Dead())
			{
				CObjMgr::Get_Instance()->Get_Player()->Set_Hp(-iter->Get_Attack());
			}
		}

		if (CCollisionMgr::AABB_Collision(iter, CObjMgr::Get_Instance()->Get_Berserker()))
		{
			if (!CObjMgr::Get_Instance()->Get_Berserker()->Get_Dead())
			{
				CObjMgr::Get_Instance()->Get_Berserker()->Set_Hp(-iter->Get_Attack());
			}
		}

		if (CCollisionMgr::AABB_Collision(iter, CObjMgr::Get_Instance()->Get_Ranger()))
		{
			if (!CObjMgr::Get_Instance()->Get_Ranger()->Get_Dead())
			{
				CObjMgr::Get_Instance()->Get_Ranger()->Set_Hp(-iter->Get_Attack());
			}
		}
	}
}

vector<CItem*> CField::Create_Spoil()
{
	vector<CItem*> TempVector;

	int iRandom = 2; //rand() % 6 + 1;
	int	iLoofCount = rand() % 3 + 1;
	
	// 1 == 검, 2 == 스태프, 3 == 도끼 , 4 == 활, 5 == 방어구 , 6 == 장신구

	for (int i = 0; i < iLoofCount; ++i)
	{
		if (m_pTarget->Get_Name() == L"해골 기사")
		{
			switch (iRandom)
			{
			case 1:

				break;

			case 2:
				TempVector.push_back(new CBasicStaff);
				TempVector.back()->Initialize();
				break;

			case 3:

				break;

			case 4:

				break;

			case 5:

				break;

			case 6:

				break;

			}
		}
	}

	


	return TempVector;
}

void CField::Update_BossHpFrameRect()
{
	m_tBossHpFrameRect.left = LONG(m_tBossHpFrameInfo.fX - (m_tBossHpFrameInfo.fCX * 0.5f));
	m_tBossHpFrameRect.top = LONG(m_tBossHpFrameInfo.fY - (m_tBossHpFrameInfo.fCY * 0.5f));
	m_tBossHpFrameRect.right = LONG(m_tBossHpFrameInfo.fX + (m_tBossHpFrameInfo.fCX * 0.5f));
	m_tBossHpFrameRect.bottom = LONG(m_tBossHpFrameInfo.fY + (m_tBossHpFrameInfo.fCY * 0.5f));
}

void CField::Update_BossHpBarRect()
{
	m_tBossHpBarRect.left = LONG(m_tBossHpBarInfo.fX - (m_tBossHpBarInfo.fCX * 0.5f));
	m_tBossHpBarRect.top = LONG(m_tBossHpBarInfo.fY - (m_tBossHpBarInfo.fCY * 0.5f));
	m_tBossHpBarRect.right = LONG(m_tBossHpBarInfo.fX + (m_tBossHpBarInfo.fCX * 0.5f));
	m_tBossHpBarRect.bottom = LONG(m_tBossHpBarInfo.fY + (m_tBossHpBarInfo.fCY * 0.5f));
}

void CField::Update_TimeRect()
{
	m_tTimerRect.left = LONG(m_tTimerInfo.fX - (m_tTimerInfo.fCX * 0.5f));
	m_tTimerRect.top = LONG(m_tTimerInfo.fY - (m_tTimerInfo.fCY * 0.5f));
	m_tTimerRect.right = LONG(m_tTimerInfo.fX + (m_tTimerInfo.fCX * 0.5f));
	m_tTimerRect.bottom = LONG(m_tTimerInfo.fY + (m_tTimerInfo.fCY * 0.5f));
}
