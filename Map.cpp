
#include "Map.h"
#include "BmpMgr.h"
#include "ObjMgr.h"
#include "SceneMgr.h"
#include "KeyMgr.h"

CMap::CMap()
{
	ZeroMemory(&m_tMapRect, sizeof(RECT));
	ZeroMemory(&m_tMapInfo, sizeof(INFO));

}

CMap::~CMap()
{
}

void CMap::Initialize()
{
	Setting_Img();
	m_eRender = SUPER_UI;
	//m_eCurrentScene = CSceneMgr::Get_Instance()->Get_SceneID();

	for (int i = 0; i < 2; ++i)
	{
		m_tMapInfo[i].fCX = 100.f;
		m_tMapInfo[i].fCY = 70.f;
	}
	
	m_tMapInfo[0].fX = 680;
	m_tMapInfo[0].fY = 150;
	m_tMapInfo[1].fX = 580;
	m_tMapInfo[1].fY = 220;

	m_tMapRect[0].left = LONG(m_tMapInfo[0].fX - (m_tMapInfo[0].fCX * 0.5f));
	m_tMapRect[0].top = LONG(m_tMapInfo[0].fY - (m_tMapInfo[0].fCY * 0.5f));
	m_tMapRect[0].right = LONG(m_tMapInfo[0].fX + (m_tMapInfo[0].fCX * 0.5f));
	m_tMapRect[0].bottom = LONG(m_tMapInfo[0].fY + (m_tMapInfo[0].fCY * 0.5f));


	m_tMapRect[1].left = LONG(m_tMapInfo[1].fX - (m_tMapInfo[1].fCX * 0.5f));
	m_tMapRect[1].top = LONG(m_tMapInfo[1].fY - (m_tMapInfo[1].fCY * 0.5f));
	m_tMapRect[1].right = LONG(m_tMapInfo[1].fX + (m_tMapInfo[1].fCX * 0.5f));
	m_tMapRect[1].bottom = LONG(m_tMapInfo[1].fY + (m_tMapInfo[1].fCY * 0.5f));

}

int CMap::Update()
{
	Select_Map();

	m_tMapRect[0].left = LONG(m_tMapInfo[0].fX - (m_tMapInfo[0].fCX * 0.5f));
	m_tMapRect[0].top = LONG(m_tMapInfo[0].fY - (m_tMapInfo[0].fCY * 0.5f));
	m_tMapRect[0].right = LONG(m_tMapInfo[0].fX + (m_tMapInfo[0].fCX * 0.5f));
	m_tMapRect[0].bottom = LONG(m_tMapInfo[0].fY + (m_tMapInfo[0].fCY * 0.5f));


	m_tMapRect[1].left = LONG(m_tMapInfo[1].fX - (m_tMapInfo[1].fCX * 0.5f));
	m_tMapRect[1].top = LONG(m_tMapInfo[1].fY - (m_tMapInfo[1].fCY * 0.5f));
	m_tMapRect[1].right = LONG(m_tMapInfo[1].fX + (m_tMapInfo[1].fCX * 0.5f));
	m_tMapRect[1].bottom = LONG(m_tMapInfo[1].fY + (m_tMapInfo[1].fCY * 0.5f));

	__super::Update_Rect();

	return OBJ_NOEVENT;

}

void CMap::Late_Update()
{
}


void CMap::Render(HDC hDC)
{
	HDC hMapDC = CBmpMgr::Get_Instance()->Find_Img(L"LobbyMap");
	HDC hObjectDC = CBmpMgr::Get_Instance()->Find_Img(L"Map_Object");
	HDC hRoadVerDC = CBmpMgr::Get_Instance()->Find_Img(L"Map_Road_Side");
	HDC hRoadHorDC = CBmpMgr::Get_Instance()->Find_Img(L"Map_Road_UPDOWN");
	HDC hIconDC = CBmpMgr::Get_Instance()->Find_Img(L"Healer_MiniMap_Icon");

	HDC hStageObjectDC = CBmpMgr::Get_Instance()->Find_Img(L"Map_Object_Stage");
	
	TCHAR	szBuff[32] = L"";


	


	if (CSceneMgr::Get_Instance()->Get_SceneID() == SC_LOBBY)
	{
		GdiTransparentBlt(hDC,
			550,
			20,
			250,
			750,
			hMapDC,
			0,
			0,
			470,
			970,
			RGB(255, 0, 255));
	}
	else if (CSceneMgr::Get_Instance()->Get_SceneID() == SC_STAGE)
	{
		GdiTransparentBlt(hDC,
			0,
			20,
			200,
			750,
			hMapDC,
			0,
			0,
			470,
			970,
			RGB(255, 0, 255));
	}
	
	if (CSceneMgr::Get_Instance()->Get_SceneID() == SC_LOBBY)
	{
		GdiTransparentBlt(hDC,
			(int)m_tMapInfo[0].fX,
			(int)m_tMapInfo[0].fY,
			(int)m_tMapInfo[0].fCX,
			(int)m_tMapInfo[0].fCY,
			hObjectDC,
			0,
			0,
			120,
			70,
			RGB(255, 0, 255)
		);

		GdiTransparentBlt(hDC,
			(int)m_tMapInfo[0].fX + 40,
			(int)m_tMapRect[0].bottom + 20,
			20,
			60,
			hRoadHorDC,
			0,
			0,
			20,
			60,
			RGB(255, 0, 255)
		);

		GdiTransparentBlt(hDC,
			(int)m_tMapInfo[0].fX - 20,
			(int)m_tMapRect[0].bottom + 60,
			70,
			20,
			hRoadVerDC,
			0,
			0,
			90,
			20,
			RGB(255, 0, 255)
		);

		GdiTransparentBlt(hDC,
			(int)m_tMapInfo[1].fX,
			(int)m_tMapInfo[1].fY,
			(int)m_tMapInfo[1].fCX,
			(int)m_tMapInfo[1].fCY,
			hObjectDC,
			0,
			0,
			120,
			70,
			RGB(255, 0, 255)
		);
	}
	else if (CSceneMgr::Get_Instance()->Get_SceneID() == SC_STAGE)
	{
		GdiTransparentBlt(hDC,
			(int)m_tMapInfo[0].fX,
			(int)m_tMapInfo[0].fY,
			(int)m_tMapInfo[0].fCX,
			(int)m_tMapInfo[0].fCY,
			hStageObjectDC,
			0,
			0,
			80,
			70,
			RGB(255, 0, 255)
		);

		GdiTransparentBlt(hDC,
			(int)m_tMapInfo[0].fX + 40,
			(int)m_tMapRect[0].bottom + 20,
			20,
			82,
			hRoadHorDC,
			0,
			0,
			20,
			60,
			RGB(255, 0, 255)
		);

		GdiTransparentBlt(hDC,
			(int)m_tMapInfo[0].fX - 20,
			(int)m_tMapRect[0].bottom + 80,
			70,
			20,
			hRoadVerDC,
			0,
			0,
			90,
			20,
			RGB(255, 0, 255)
		);

		GdiTransparentBlt(hDC,
			(int)m_tMapInfo[1].fX,
			(int)m_tMapInfo[1].fY,
			(int)m_tMapInfo[1].fCX,
			(int)m_tMapInfo[1].fCY,
			hStageObjectDC,
			0,
			0,
			80,
			70,
			RGB(255, 0, 255)
		);
	}


	if (CSceneMgr::Get_Instance()->Get_SceneID() == SC_LOBBY)
	{
		GdiTransparentBlt(hDC,
			(int)m_tMapInfo[0].fX + 35,
			(int)m_tMapInfo[0].fY + 20,
			30,
			30,
			hIconDC,
			0,
			0,
			60,
			60,
			RGB(255, 0, 255)
		);
	}
	else if (CSceneMgr::Get_Instance()->Get_SceneID() == SC_STAGE)
	{
		GdiTransparentBlt(hDC,
			(int)m_tMapInfo[1].fX + 35,
			(int)m_tMapInfo[1].fY + 20,
			30,
			30,
			hIconDC,
			0,
			0,
			60,
			60,
			RGB(255, 0, 255)
		);
	}
	
	
	if (CSceneMgr::Get_Instance()->Get_SceneID() == SC_LOBBY)
	{
		swprintf_s(szBuff, L" ³³°ñ´ç Áöµµ");
		TextOut(hDC, WINCX / 2 - 25, 50, szBuff, lstrlen(szBuff));

		SetBkMode(hDC, 1);
		SetTextColor(hDC, RGB(101, 92, 80));

		HFONT hFont;

		hFont = CreateFont(18, 0, 0, 0, 0, 0, 0, 0, HANGUL_CHARSET, 0, 0, 0, VARIABLE_PITCH || FF_ROMAN, TEXT("PFStardust"));
		(HFONT)SelectObject(hDC, hFont);

		swprintf_s(szBuff, L"³³°ñ´ç ³» ¾îµð·Îµç ÀÌµ¿ÇÏ·Á");
		TextOut(hDC, WINCX / 2 - 60, 80, szBuff, lstrlen(szBuff));
		swprintf_s(szBuff, L"¸é Å¬¸¯ÇÏ½Ê½Ã¿À");
		TextOut(hDC, WINCX / 2 - 60, 100, szBuff, lstrlen(szBuff));
		DeleteObject(hFont);

		hFont = CreateFont(18, 0, 0, 0, 0, 0, 0, 0, HANGUL_CHARSET, 0, 0, 0, VARIABLE_PITCH || FF_ROMAN, TEXT("PFStardust"));
		SetTextColor(hDC, RGB(146, 93, 42));
		(HFONT)SelectObject(hDC, hFont);
		swprintf_s(szBuff, L"Àº½ÅÃ³");
		TextOut(hDC, (int)m_tMapInfo[0].fX + 40, (int)m_tMapInfo[0].fY - 20, szBuff, lstrlen(szBuff));
		swprintf_s(szBuff, L"³³°ñ´ç ÀÔ±¸");
		TextOut(hDC, (int)m_tMapInfo[1].fX + 20, (int)m_tMapInfo[1].fY - 20, szBuff, lstrlen(szBuff));
		DeleteObject(hFont);
	}
	else if (CSceneMgr::Get_Instance()->Get_SceneID() == SC_STAGE)
	{
		swprintf_s(szBuff, L" ³³°ñ´ç Áöµµ");
		TextOut(hDC, 35, 50, szBuff, lstrlen(szBuff));

		SetBkMode(hDC, 1);
		SetTextColor(hDC, RGB(101, 92, 80));

		HFONT hFont;

		hFont = CreateFont(15, 0, 0, 0, 0, 0, 0, 0, HANGUL_CHARSET, 0, 0, 0, VARIABLE_PITCH || FF_ROMAN, TEXT("PFStardust"));
		(HFONT)SelectObject(hDC, hFont);

		swprintf_s(szBuff, L"³³°ñ´ç ³» ¾îµð·Îµç ÀÌµ¿ÇÏ·Á");
		TextOut(hDC, 22, 80, szBuff, lstrlen(szBuff));
		swprintf_s(szBuff, L"¸é Å¬¸¯ÇÏ½Ê½Ã¿À");
		TextOut(hDC, 22, 100, szBuff, lstrlen(szBuff));
		DeleteObject(hFont);

		hFont = CreateFont(15, 0, 0, 0, 0, 0, 0, 0, HANGUL_CHARSET, 0, 0, 0, VARIABLE_PITCH || FF_ROMAN, TEXT("PFStardust"));
		SetTextColor(hDC, RGB(146, 93, 42));
		(HFONT)SelectObject(hDC, hFont);
		swprintf_s(szBuff, L"Àº½ÅÃ³");
		TextOut(hDC, (int)m_tMapInfo[0].fX + 40, (int)m_tMapInfo[0].fY - 20, szBuff, lstrlen(szBuff));
		swprintf_s(szBuff, L"³³°ñ´ç ÀÔ±¸");
		TextOut(hDC, (int)m_tMapInfo[1].fX + 20, (int)m_tMapInfo[1].fY - 20, szBuff, lstrlen(szBuff));
		DeleteObject(hFont);
	}
}

	


void CMap::Release()
{
	
}


void CMap::Setting_Img()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/UI/Scene/Lobby/MiniMap1.bmp", L"LobbyMap");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/UI/Scene/Map_Object.bmp", L"Map_Object");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/UI/Scene/Map_Road_Side.bmp", L"Map_Road_Side");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/UI/Scene/Map_Road_UPDOWN.bmp", L"Map_Road_UPDOWN");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/UI/Scene/Healer_MiniMap_Icon.bmp", L"Healer_MiniMap_Icon");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/UI/Scene/Map_Object_Stage.bmp", L"Map_Object_Stage");
}

bool CMap::Select_Map()
{
	POINT	pt{};
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);

	if (PtInRect(&m_tMapRect[0], pt))
	{
		m_tMapInfo[0].fCX = 120.f;
		m_tMapInfo[0].fCY = 90.f;
		if (CKeyMgr::Get_Instance()->Key_Down(VK_LBUTTON))
		{
			if (CSceneMgr::Get_Instance()->Get_SceneID() != SC_LOBBY)
			{
				CSceneMgr::Get_Instance()->Scene_Change(SC_LOBBY);
				return true;
			}
				
		}
	}
	else if (PtInRect(&m_tMapRect[1], pt))
	{
		m_tMapInfo[1].fCX = 120.f;
		m_tMapInfo[1].fCY = 90.f;
		if (CKeyMgr::Get_Instance()->Key_Down(VK_LBUTTON))
		{
			if (CSceneMgr::Get_Instance()->Get_SceneID() != SC_STAGE)
			{
				CSceneMgr::Get_Instance()->Scene_Change(SC_STAGE);
				return true;
			}
				
		}
	}
	else
	{
		if (CSceneMgr::Get_Instance()->Get_SceneID() == SC_LOBBY)
		{
			m_tMapInfo[0].fCX = 100.f;
			m_tMapInfo[0].fCY = 70.f;
			m_tMapInfo[1].fCX = 100.f;  
			m_tMapInfo[1].fCY = 70.f;
		}
		else
		{
			m_tMapInfo[0].fCX = 80.f;
			m_tMapInfo[0].fCY = 70.f;
			m_tMapInfo[1].fCX = 80.f;
			m_tMapInfo[1].fCY = 70.f;
		}
		
	}

	return false;
}


