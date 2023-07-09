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
		(int)m_tRect.left, // ���� ���� ��ġ X,Y ��ǥ
		(int)m_tRect.top,
		(int)m_tInfo.fCX,	// ���� ���� ����, ���� ����
		(int)m_tInfo.fCY,
		hMemDC,			// ��Ʈ�� �̹����� ��� �ִ� DC
		0,					// ��Ʈ���� ����� ���� X,Y��ǥ
		0,
		(int)m_tInfo.fCX,		// ����� ��Ʈ���� ����, ���� ������
		(int)m_tInfo.fCY,
		RGB(255, 0, 255)); // �����ϰ��� �ϴ� ����


	TCHAR	szBuff[32] = L"";


	SetTextColor(hDC, RGB(255, 255, 255));
	swprintf_s(szBuff, dynamic_cast<CSelectDoor*>(m_pTarget)->Get_Boss()->Get_Name());
	TextOut(hDC, (int)m_tInfo.fX - 44, (int)m_tRect.top + 10, szBuff, lstrlen(szBuff));

	

	if (m_pTarget->Get_UI_ID() == UI_OPEN)
	{
		GdiTransparentBlt(hDC,
			(int)m_tExitRect.left, // ���� ���� ��ġ X,Y ��ǥ
			(int)m_tExitRect.top,
			(int)m_tExitInfo.fCX,	// ���� ���� ����, ���� ����
			(int)m_tExitInfo.fCY,
			hExitDC,			// ��Ʈ�� �̹����� ��� �ִ� DC
			0,					// ��Ʈ���� ����� ���� X,Y��ǥ
			0,
			(int)m_tExitInfo.fCX,		// ����� ��Ʈ���� ����, ���� ������
			(int)m_tExitInfo.fCY,
			RGB(255, 0, 255)); // �����ϰ��� �ϴ� ����

		HFONT hFont = CreateFont(15, 0, 0, 0, 0, 0, 0, 0, HANGUL_CHARSET, 0, 0, 0, VARIABLE_PITCH || FF_ROMAN, TEXT("PFStardust"));
		(HFONT)SelectObject(hDC, hFont);

		GdiTransparentBlt(hDC,
			(int)m_tStartBtnRect.left, // ���� ���� ��ġ X,Y ��ǥ
			(int)m_tStartBtnRect.top,
			(int)m_tStartBtnInfo.fCX,	// ���� ���� ����, ���� ����
			(int)m_tStartBtnInfo.fCY,
			hStartDC,			// ��Ʈ�� �̹����� ��� �ִ� DC
			0,					// ��Ʈ���� ����� ���� X,Y��ǥ
			0,
			(int)m_tStartBtnInfo.fCX,		// ����� ��Ʈ���� ����, ���� ������
			(int)m_tStartBtnInfo.fCY,
			RGB(255, 0, 255)); // �����ϰ��� �ϴ� ����

		swprintf_s(szBuff, L"����");
		TextOut(hDC, (int)m_tStartBtnRect.left + 38, (int)m_tStartBtnRect.top + 30, szBuff, lstrlen(szBuff));

		GdiTransparentBlt(hDC,
			(int)m_tRect.left + 50, // ���� ���� ��ġ X,Y ��ǥ
			(int)m_tRect.top + 60,
			50,	// ���� ���� ����, ���� ����
			50,
			hExpDC,			// ��Ʈ�� �̹����� ��� �ִ� DC
			0,					// ��Ʈ���� ����� ���� X,Y��ǥ
			0,
			50,		// ����� ��Ʈ���� ����, ���� ������
			50,
			RGB(255, 0, 255));

		
		swprintf_s(szBuff, L"����ġ : %i", dynamic_cast<CSelectDoor*>(m_pTarget)->Get_Boss()->Get_Exp());
		TextOut(hDC, (int)m_tRect.left + 100, (int)m_tRect.top + 80,  szBuff, lstrlen(szBuff));

		GdiTransparentBlt(hDC,
			(int)m_tRect.left + 55, // ���� ���� ��ġ X,Y ��ǥ
			(int)m_tRect.top + 120,
			40,	// ���� ���� ����, ���� ����
			40,
			hCoinDC,			// ��Ʈ�� �̹����� ��� �ִ� DC
			0,					// ��Ʈ���� ����� ���� X,Y��ǥ
			0,
			30,		// ����� ��Ʈ���� ����, ���� ������
			30,
			RGB(255, 0, 255));

		swprintf_s(szBuff, L"�� : %i", dynamic_cast<CSelectDoor*>(m_pTarget)->Get_Boss()->Get_Gold());
		TextOut(hDC, (int)m_tRect.left + 100, (int)m_tRect.top + 130, szBuff, lstrlen(szBuff));

		GdiTransparentBlt(hDC,
			(int)m_tRect.left + 50, // ���� ���� ��ġ X,Y ��ǥ
			(int)m_tRect.top + 160,
			50,	// ���� ���� ����, ���� ����
			50,
			hTimerDC,			// ��Ʈ�� �̹����� ��� �ִ� DC
			0,					// ��Ʈ���� ����� ���� X,Y��ǥ
			0,
			35,		// ����� ��Ʈ���� ����, ���� ������
			35,
			RGB(255, 0, 255));

		int iHour = dynamic_cast<CSelectDoor*>(m_pTarget)->Get_Boss()->Get_ClearTime().m_iHour;
		int iMinute = dynamic_cast<CSelectDoor*>(m_pTarget)->Get_Boss()->Get_ClearTime().m_iMinute;
		int iSecond = (int)dynamic_cast<CSelectDoor*>(m_pTarget)->Get_Boss()->Get_ClearTime().m_lSecond;

		if (iHour == 0 && iMinute == 0 && iSecond == 0)
		{
			swprintf_s(szBuff, L"Ŭ���� �ð� : ����");
			TextOut(hDC, (int)m_tRect.left + 100, (int)m_tRect.top + 177, szBuff, lstrlen(szBuff));
		}
		else
		{
			swprintf_s(szBuff, L"Ŭ���� �ð� : %d : %d : %d", iHour,iMinute,iSecond);
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
   CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/UI/Scene/BossInfo_BGSmall.bmp", L"BossInfo_BG"); // ���� ��׶���
   CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/UI/Scene/BossInfo_Category_Abled.bmp", L"BossInfo_Category_Abled"); //Ŭ���� ī�װ�
   CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/UI/Scene/BossInfo_Category_Disabled.bmp", L"BossInfo_Category_Disabled"); // Ŭ������ ���� ī�װ�

   CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/UI/Scene/BossInfo_Icon.bmp", L"BossInfo_Icon"); // ���� ���� ���� ��ư
   CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/UI/Scene/BossInfo_Select_Frame.bmp", L"BossInfo_Select_Frame"); //  ������ ���� ������, �������� ���� ���� ������
   CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/UI/Scene/BossInfo_Skill_Frame.bmp", L"BossInfo_Skill_Frame"); // ���� ��ų ������

   CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/UI/Scene/Boss_Start_Button1.bmp", L"Boss_Start_Button1"); // ���� ���� ��ư

   CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/UI/Scene/BossInfo.bmp", L"BossInfo"); // ���� ���� UI
   CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/UI/Scene/Boss_Difficulty1.bmp", L"Boss_Difficulty1"); // ���� ���̵� 1
   CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/UI/Scene/Boss_Difficulty2.bmp", L"Boss_Difficulty2"); // ���� ���̵� 2
   CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/UI/Scene/Boss_Difficulty3.bmp", L"Boss_Difficulty3"); // ���� ���̵� 3
   CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/UI/Scene/Boss_DifficultyStar.bmp", L"Boss_DifficultyStar"); // ���� ���̵� �� UI
   CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/UI/Scene/Result_exp.bmp", L"Result_exp"); // ��� ����ġ UI
   CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/UI/Public/BossRoom_Timer.bmp", L"BossRoom_Timer"); // ���� ���� Ŭ���� �ð� UI
   CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/UI/Public/Coin.bmp", L"Coin"); // ��� ��� UI
   CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/UI/Public/Exit_Button.bmp", L"Exit_Button"); // ������ ��ư

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
