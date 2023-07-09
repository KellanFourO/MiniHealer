#include "SelectDoor.h"
#include "BmpMgr.h"
#include "KeyMgr.h"
#include "StageInfo.h"
#include "ObjMgr.h"

#include "BoneKnight.h"

CSelectDoor::CSelectDoor():m_pBoss(nullptr),m_pStageInfo(nullptr),m_iDoorBGStart(0),m_iDoorBGEnd(0),m_dwDoorBGDelay(GetTickCount64())
{
}

CSelectDoor::~CSelectDoor()
{
}

void CSelectDoor::Initialize(void)
{
	m_tInfo.fCX = 250.f;
	m_tInfo.fCY = 300.f;
	 
	Setting_Img();
	m_tFrame.iMotion = 0;

	m_iDoorBGStart = 0;
	m_iDoorBGEnd = 7;


	if (!m_pStageInfo)
	{
		m_pStageInfo = new CStageInfo;
		m_pStageInfo->Set_Target(this);
		m_pStageInfo->Initialize();
		
	}


}

int CSelectDoor::Update(void)
 {
	if (m_bDead)
		return OBJ_DEAD;

	if (m_pBoss->Get_Name() == L"해골 기사")
		m_pFrameKey = L"Boss_Icon1";
	
	/*if (m_pBoss->Get_Number() == 1)
		m_pFrameKey = L"Boss_Icon1";*/
	

	if (m_dwDoorBGDelay + 150 < GetTickCount64())
	{
		++m_iDoorBGStart;
		m_dwDoorBGDelay = GetTickCount64();
	}

	if (m_iDoorBGStart == m_iDoorBGEnd)
		m_iDoorBGStart = 0;

	POINT	pt{};
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);

	if (m_eUI == UI_CLOSE)
	{
		if (PtInRect(&m_tRect, pt))
		{
			if (CKeyMgr::Get_Instance()->Key_Down(VK_LBUTTON))
			{
				m_eUI = UI_OPEN;
			}
			m_tFrame.iMotion = 1;
		}
		else
			m_tFrame.iMotion = 0;
	}
	else
	{
		m_pStageInfo->Update();
	}
		
	
		
	
	
	
	__super::Update_Rect();

	return OBJ_NOEVENT;
}

void CSelectDoor::Late_Update(void)
{
	
}

void CSelectDoor::Render(HDC hDC)
{
	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Img(L"Door_Activity");
	HDC		hBGDC = CBmpMgr::Get_Instance()->Find_Img(L"Select_Door_BG2");
	HDC		hBossDC = CBmpMgr::Get_Instance()->Find_Img(m_pFrameKey);
	
	GdiTransparentBlt(hDC,
		m_tRect.left + 50,
		m_tRect.top + 66,
		162,
		210,
		hBGDC,
		m_iDoorBGStart * 162,
		0,
		162,
		270,
		RGB(255, 0, 255));

	GdiTransparentBlt(hDC,
		(int)m_tRect.left, // 복사 받을 위치 X,Y 좌표
		(int)m_tRect.top,
		(int)m_tInfo.fCX,	// 복사 받을 가로, 세로 길이
		(int)m_tInfo.fCY,
		hMemDC,			// 비트맵 이미지를 담고 있는 DC
		0,					// 비트맵을 출력할 시작 X,Y좌표
		m_tFrame.iMotion * (int)m_tInfo.fCY,
		(int)m_tInfo.fCX,		// 출력할 비트맵의 가로, 세로 사이즈
		(int)m_tInfo.fCY,
		RGB(255, 0, 255)); // 제거하고자 하는 색상

	GdiTransparentBlt(hDC,
		(int)m_tRect.left + 70, // 복사 받을 위치 X,Y 좌표
		(int)m_tRect.top + 135,
		117,	// 복사 받을 가로, 세로 길이
		124,
		hBossDC,			// 비트맵 이미지를 담고 있는 DC
		0,					// 비트맵을 출력할 시작 X,Y좌표
		0,
		117,		// 출력할 비트맵의 가로, 세로 사이즈
		124,
		RGB(255, 0, 255)); // 제거하고자 하는 색상


	if (m_eUI == UI_OPEN)
	{
		m_pStageInfo->Render(hDC);
	}
}

void CSelectDoor::Release(void)
{
}

void CSelectDoor::Setting_Img()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/UI/Scene/Door_Activity1.bmp", L"Door_Activity");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/UI/Scene/Select_Door_BG2.bmp", L"Select_Door_BG2");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/UI/Scene/Boss_Icon1.bmp", L"Boss_Icon1"); // 본나이트
	CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/UI/Scene/Boss_Icon3.bmp", L"Boss_Icon3"); // 이크시어
}
