#include "StageInfo.h"
#include "BmpMgr.h"
#include "KeyMgr.h"
#include "MyButton.h"
#include "ObjMgr.h"
#include "AbstractFactory.h"
#include "SceneMgr.h"

int CStageInfo::m_iClearTime = 0;
int CStageInfo::m_iKillCount = 0;

CStageInfo::CStageInfo():m_pBoss(nullptr),m_iDifficulty(0)
{
	ZeroMemory(&m_tExitRect, sizeof(RECT));
	ZeroMemory(&m_tExitInfo, sizeof(INFO));
}

CStageInfo::~CStageInfo()
{
    Release();
}

void CStageInfo::Initialize(void)
{
    m_tInfo.fCX = 610.f;
    m_tInfo.fCY = 679.f;
    Setting_Img();

	m_tInfo.fX = WINCX / 2;
	m_tInfo.fY = WINCY / 2;

	m_tExitInfo.fCX = 81.f;
	m_tExitInfo.fCY = 81.f;

	m_tStartBtnInfo.fCX = 104.f;
	m_tStartBtnInfo.fCY = 77.f;
	
	m_eRender = SUPER_UI;
	
	
	//dynamic_cast<CSelectDoor*>(CObjMgr::Get_Instance()->Get_SelectDoor())->Set_UI_ID(UI_CLOSE);
}

int CStageInfo::Update(void)
{
	POINT	pt{};
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);

	dynamic_cast<CSelectDoor*>(m_pTarget)->Get_Boss()->Set_Size(300, 258);
	dynamic_cast<CSelectDoor*>(m_pTarget)->Get_Boss()->Set_Pos((float)m_tRect.right - 150, (float)m_tRect.bottom - 200);
	dynamic_cast<CSelectDoor*>(m_pTarget)->Get_Boss()->Update();
	if (PtInRect(&m_tExitRect, pt))
	{
		if (CKeyMgr::Get_Instance()->Key_Down(VK_LBUTTON))
		{
			m_pTarget->Set_UI_ID(UI_CLOSE);
		}
		
	}
	else if (PtInRect(&m_tStartBtnRect, pt))
	{
		if (CKeyMgr::Get_Instance()->Key_Down(VK_LBUTTON))
		{
			m_pBoss = dynamic_cast<CSelectDoor*>(m_pTarget)->Get_Boss();
			CSceneMgr::Get_Instance()->Field_On(m_pBoss);
			//CSceneMgr::Get_Instance()->Get_Field()->Set_Target(m_pTarget);

		}
	}


	__super::Update_Rect();

	m_tExitInfo.fX = (float)m_tRect.left;
	m_tExitInfo.fY = (float)m_tRect.top;
	Update_ExitRect();

	m_tStartBtnInfo.fX = m_tInfo.fX;
	m_tStartBtnInfo.fY = (float)m_tRect.bottom - 20;
	Update_StartRect();

    return OBJ_NOEVENT;
}

void CStageInfo::Late_Update(void)
{

}

void CStageInfo::Render(HDC hDC)
{
	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Img(L"BossInfo_BG");
	HDC		hExitDC = CBmpMgr::Get_Instance()->Find_Img(L"Exit_Button");
	HDC		hStartDC = CBmpMgr::Get_Instance()->Find_Img(L"Boss_Start_Button1");
	HDC		hExpDC	= CBmpMgr::Get_Instance()->Find_Img(L"Result_exp");
	HDC		hCoinDC = CBmpMgr::Get_Instance()->Find_Img(L"Coin");
	HDC		hTimerDC = CBmpMgr::Get_Instance()->Find_Img(L"BossRoom_Timer");

	GdiTransparentBlt(hDC,
		(int)m_tRect.left, // 복사 받을 위치 X,Y 좌표
		(int)m_tRect.top,
		(int)m_tInfo.fCX,	// 복사 받을 가로, 세로 길이
		(int)m_tInfo.fCY,
		hMemDC,			// 비트맵 이미지를 담고 있는 DC
		0,					// 비트맵을 출력할 시작 X,Y좌표
		0,
		(int)m_tInfo.fCX,		// 출력할 비트맵의 가로, 세로 사이즈
		(int)m_tInfo.fCY,
		RGB(255, 0, 255)); // 제거하고자 하는 색상


	TCHAR	szBuff[32] = L"";


	SetTextColor(hDC, RGB(255, 255, 255));
	swprintf_s(szBuff, dynamic_cast<CSelectDoor*>(m_pTarget)->Get_Boss()->Get_Name());
	TextOut(hDC, (int)m_tInfo.fX - 44, (int)m_tRect.top + 10, szBuff, lstrlen(szBuff));

	

	if (m_pTarget->Get_UI_ID() == UI_OPEN)
	{
		GdiTransparentBlt(hDC,
			(int)m_tExitRect.left, // 복사 받을 위치 X,Y 좌표
			(int)m_tExitRect.top,
			(int)m_tExitInfo.fCX,	// 복사 받을 가로, 세로 길이
			(int)m_tExitInfo.fCY,
			hExitDC,			// 비트맵 이미지를 담고 있는 DC
			0,					// 비트맵을 출력할 시작 X,Y좌표
			0,
			(int)m_tExitInfo.fCX,		// 출력할 비트맵의 가로, 세로 사이즈
			(int)m_tExitInfo.fCY,
			RGB(255, 0, 255)); // 제거하고자 하는 색상

		HFONT hFont = CreateFont(15, 0, 0, 0, 0, 0, 0, 0, HANGUL_CHARSET, 0, 0, 0, VARIABLE_PITCH || FF_ROMAN, TEXT("PFStardust"));
		(HFONT)SelectObject(hDC, hFont);

		GdiTransparentBlt(hDC,
			(int)m_tStartBtnRect.left, // 복사 받을 위치 X,Y 좌표
			(int)m_tStartBtnRect.top,
			(int)m_tStartBtnInfo.fCX,	// 복사 받을 가로, 세로 길이
			(int)m_tStartBtnInfo.fCY,
			hStartDC,			// 비트맵 이미지를 담고 있는 DC
			0,					// 비트맵을 출력할 시작 X,Y좌표
			0,
			(int)m_tStartBtnInfo.fCX,		// 출력할 비트맵의 가로, 세로 사이즈
			(int)m_tStartBtnInfo.fCY,
			RGB(255, 0, 255)); // 제거하고자 하는 색상

		swprintf_s(szBuff, L"시작");
		TextOut(hDC, (int)m_tStartBtnRect.left + 38, (int)m_tStartBtnRect.top + 30, szBuff, lstrlen(szBuff));

		GdiTransparentBlt(hDC,
			(int)m_tRect.left + 50, // 복사 받을 위치 X,Y 좌표
			(int)m_tRect.top + 60,
			50,	// 복사 받을 가로, 세로 길이
			50,
			hExpDC,			// 비트맵 이미지를 담고 있는 DC
			0,					// 비트맵을 출력할 시작 X,Y좌표
			0,
			50,		// 출력할 비트맵의 가로, 세로 사이즈
			50,
			RGB(255, 0, 255));

		
		swprintf_s(szBuff, L"경험치 : %i", dynamic_cast<CSelectDoor*>(m_pTarget)->Get_Boss()->Get_Exp());
		TextOut(hDC, (int)m_tRect.left + 100, (int)m_tRect.top + 80,  szBuff, lstrlen(szBuff));

		GdiTransparentBlt(hDC,
			(int)m_tRect.left + 55, // 복사 받을 위치 X,Y 좌표
			(int)m_tRect.top + 120,
			40,	// 복사 받을 가로, 세로 길이
			40,
			hCoinDC,			// 비트맵 이미지를 담고 있는 DC
			0,					// 비트맵을 출력할 시작 X,Y좌표
			0,
			30,		// 출력할 비트맵의 가로, 세로 사이즈
			30,
			RGB(255, 0, 255));

		swprintf_s(szBuff, L"금 : %i", dynamic_cast<CSelectDoor*>(m_pTarget)->Get_Boss()->Get_Gold());
		TextOut(hDC, (int)m_tRect.left + 100, (int)m_tRect.top + 130, szBuff, lstrlen(szBuff));

		GdiTransparentBlt(hDC,
			(int)m_tRect.left + 50, // 복사 받을 위치 X,Y 좌표
			(int)m_tRect.top + 160,
			50,	// 복사 받을 가로, 세로 길이
			50,
			hTimerDC,			// 비트맵 이미지를 담고 있는 DC
			0,					// 비트맵을 출력할 시작 X,Y좌표
			0,
			35,		// 출력할 비트맵의 가로, 세로 사이즈
			35,
			RGB(255, 0, 255));

		int iHour = dynamic_cast<CSelectDoor*>(m_pTarget)->Get_Boss()->Get_ClearTime().m_iHour;
		int iMinute = dynamic_cast<CSelectDoor*>(m_pTarget)->Get_Boss()->Get_ClearTime().m_iMinute;
		int iSecond = (int)dynamic_cast<CSelectDoor*>(m_pTarget)->Get_Boss()->Get_ClearTime().m_lSecond;

		if (iHour == 0 && iMinute == 0 && iSecond == 0)
		{
			swprintf_s(szBuff, L"클리어 시간 : 없음");
			TextOut(hDC, (int)m_tRect.left + 100, (int)m_tRect.top + 177, szBuff, lstrlen(szBuff));
		}
		else
		{
			swprintf_s(szBuff, L"클리어 시간 : %d : %d : %d", iHour,iMinute,iSecond);
			TextOut(hDC, (int)m_tRect.left + 100, (int)m_tRect.top + 177, szBuff, lstrlen(szBuff));
		}
		
		
		dynamic_cast<CSelectDoor*>(m_pTarget)->Get_Boss()->Render(hDC);
	}
}

void CStageInfo::Release(void)
{
}

void CStageInfo::Setting_Img()
{
   CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/UI/Scene/BossInfo_BGSmall.bmp", L"BossInfo_BG"); // 인포 백그라운드
   CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/UI/Scene/BossInfo_Category_Abled.bmp", L"BossInfo_Category_Abled"); //클릭한 카테고리
   CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/UI/Scene/BossInfo_Category_Disabled.bmp", L"BossInfo_Category_Disabled"); // 클릭하지 않은 카테고리

   CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/UI/Scene/BossInfo_Icon.bmp", L"BossInfo_Icon"); // 보스 정보 보기 버튼
   CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/UI/Scene/BossInfo_Select_Frame.bmp", L"BossInfo_Select_Frame"); //  선택한 보스 프레임, 선택하지 않은 보스 프레임
   CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/UI/Scene/BossInfo_Skill_Frame.bmp", L"BossInfo_Skill_Frame"); // 보스 스킬 프레임

   CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/UI/Scene/Boss_Start_Button1.bmp", L"Boss_Start_Button1"); // 보스 시작 버튼

   CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/UI/Scene/BossInfo.bmp", L"BossInfo"); // 보스 스탯 UI
   CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/UI/Scene/Boss_Difficulty1.bmp", L"Boss_Difficulty1"); // 보스 난이도 1
   CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/UI/Scene/Boss_Difficulty2.bmp", L"Boss_Difficulty2"); // 보스 난이도 2
   CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/UI/Scene/Boss_Difficulty3.bmp", L"Boss_Difficulty3"); // 보스 난이도 3
   CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/UI/Scene/Boss_DifficultyStar.bmp", L"Boss_DifficultyStar"); // 보스 난이도 별 UI
   CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/UI/Scene/Result_exp.bmp", L"Result_exp"); // 얻는 경험치 UI
   CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/UI/Public/BossRoom_Timer.bmp", L"BossRoom_Timer"); // 가장 빠른 클리어 시간 UI
   CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/UI/Public/Coin.bmp", L"Coin"); // 얻는 골드 UI
   CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/UI/Public/Exit_Button.bmp", L"Exit_Button"); // 나가기 버튼

}

void CStageInfo::Update_ExitRect()
{
	m_tExitRect.left = LONG(m_tExitInfo.fX - (m_tExitInfo.fCX * 0.5f));
	m_tExitRect.top = LONG(m_tExitInfo.fY - (m_tExitInfo.fCY * 0.5f));
	m_tExitRect.right = LONG(m_tExitInfo.fX + (m_tExitInfo.fCX * 0.5f));
	m_tExitRect.bottom = LONG(m_tExitInfo.fY + (m_tExitInfo.fCY * 0.5f));
}

void CStageInfo::Update_StartRect()
{
	m_tStartBtnRect.left = LONG(m_tStartBtnInfo.fX - (m_tStartBtnInfo.fCX * 0.5f));
	m_tStartBtnRect.top = LONG(m_tStartBtnInfo.fY - (m_tStartBtnInfo.fCY * 0.5f));
	m_tStartBtnRect.right = LONG(m_tStartBtnInfo.fX + (m_tStartBtnInfo.fCX * 0.5f));
	m_tStartBtnRect.bottom = LONG(m_tStartBtnInfo.fY + (m_tStartBtnInfo.fCY * 0.5f));
}
