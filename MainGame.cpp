#include "framework.h"
#include "MainGame.h"
#include "AbstractFactory.h"
#include "Player.h"
#include "Monster.h"
#include "ObjMgr.h"
#include "KeyMgr.h"
#include "BmpMgr.h"
#include "SceneMgr.h"
#include "SoundMgr.h"
#include "CollisionMgr.h"

CMainGame::CMainGame() : m_dwTime(GetTickCount64()), m_iFPS(0)
{
	ZeroMemory(m_szFPS, sizeof(m_szFPS));
}

CMainGame::~CMainGame()
{
	Release();
}

void CMainGame::Initialize()
{
	m_hDC = GetDC(g_hWnd);

	CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/BackGround/Opening.bmp", L"Back");

	CSceneMgr::Get_Instance()->Scene_Change(SC_MENU);

	AddFontResource(L"./Font/PFStardust.ttf");

	
	CSoundMgr::Get_Instance()->Initialize();
	
}

void CMainGame::Update()
{
	CSceneMgr::Get_Instance()->Update();
}


void CMainGame::Late_Update()
{

	CSceneMgr::Get_Instance()->Late_Update();

	/*for (auto& iter : m_ObjList[PLAYER_BULLET])
	{
		 (CCollisionMgr::AABB_Collision(CObjMgr::Get_Instance()->Get_Player(), CObjMgr::Get_Instance()->Get_Player()->Get_Target()))
		{
			 

		}
	}*/
	
	//CCollisionMgr::AABB_Collision()
}

void CMainGame::Render()
{
	++m_iFPS;
	
	if (m_dwTime + 1000 < GetTickCount64())
	{
		swprintf_s(m_szFPS, L"FPS : %d", m_iFPS);
		SetWindowText(g_hWnd, m_szFPS);

		m_iFPS = 0;
		m_dwTime = GetTickCount64();
	}

	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Img(L"Back");

	SetBkMode(hMemDC, 1);
	SetTextColor(hMemDC, RGB(146, 93, 42));
	HFONT hFont;

	hFont = CreateFont(25, 0, 0, 0, 0, 0, 0, 0, HANGUL_CHARSET, 0, 0, 0, VARIABLE_PITCH || FF_ROMAN, TEXT("PFStardust"));
	(HFONT)SelectObject(hMemDC, hFont);
	CSceneMgr::Get_Instance()->Render(hMemDC);
	
	TCHAR	szBuff[32] = L"";

	POINT pt{};
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);

	

	BitBlt(m_hDC,	// 복사 받을 DC(최종적으로 그림을 그릴 DC공간)
		0, 0, WINCX, WINCY,
		hMemDC,			// 비트맵 이미지를 담고 있는 DC
		0,					// 비트맵을 출력할 시작 X,Y좌표
		0,
		SRCCOPY);

	SetBkMode(m_hDC, 1);
	SetTextColor(m_hDC, RGB(255, 255, 255));
	HFONT hTestFont;

	hTestFont = CreateFont(30, 0, 0, 0, 0, 0, 0, 0, HANGUL_CHARSET, 0, 0, 0, VARIABLE_PITCH || FF_ROMAN, TEXT("PFStardust"));
	(HFONT)SelectObject(m_hDC, hTestFont);

	/*swprintf_s(szBuff, L"Mouse X : %f", (float)pt.x);
	TextOut(m_hDC, 600, 50, szBuff, lstrlen(szBuff));
	swprintf_s(szBuff, L"Mouse Y : %f", (float)pt.y);
	TextOut(m_hDC, 600, 70, szBuff, lstrlen(szBuff));*/

	DeleteObject(hTestFont);
}

void CMainGame::Release()
{
	CSoundMgr::Destroy_Instance();
	CObjMgr::Destroy_Instance();
	CBmpMgr::Destroy_Instance();
	CKeyMgr::Destroy_Instance();
	CSceneMgr::Destroy_Instance();

	ReleaseDC(g_hWnd, m_hDC);
	RemoveFontResource(L"./Font/PFStardust.ttf");

}
