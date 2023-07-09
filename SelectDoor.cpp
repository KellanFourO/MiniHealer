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

	if (m_pBoss->Get_Name() == L"�ذ� ���")
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
		(int)m_tRect.left, // ���� ���� ��ġ X,Y ��ǥ
		(int)m_tRect.top,
		(int)m_tInfo.fCX,	// ���� ���� ����, ���� ����
		(int)m_tInfo.fCY,
		hMemDC,			// ��Ʈ�� �̹����� ��� �ִ� DC
		0,					// ��Ʈ���� ����� ���� X,Y��ǥ
		m_tFrame.iMotion * (int)m_tInfo.fCY,
		(int)m_tInfo.fCX,		// ����� ��Ʈ���� ����, ���� ������
		(int)m_tInfo.fCY,
		RGB(255, 0, 255)); // �����ϰ��� �ϴ� ����

	GdiTransparentBlt(hDC,
		(int)m_tRect.left + 70, // ���� ���� ��ġ X,Y ��ǥ
		(int)m_tRect.top + 135,
		117,	// ���� ���� ����, ���� ����
		124,
		hBossDC,			// ��Ʈ�� �̹����� ��� �ִ� DC
		0,					// ��Ʈ���� ����� ���� X,Y��ǥ
		0,
		117,		// ����� ��Ʈ���� ����, ���� ������
		124,
		RGB(255, 0, 255)); // �����ϰ��� �ϴ� ����


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

	CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/UI/Scene/Boss_Icon1.bmp", L"Boss_Icon1"); // ������Ʈ
	CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/UI/Scene/Boss_Icon3.bmp", L"Boss_Icon3"); // ��ũ�þ�
}
