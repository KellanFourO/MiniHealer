#include "BattleResult.h"
#include "BmpMgr.h"
#include "Spoils.h"
#include "ObjMgr.h"
#include "KeyMgr.h"
#include "BasicStaff.h"

CBattleResult::CBattleResult()
	:m_fHeight(0), m_fDistance(0),
	m_pPlayer(nullptr), m_pBerserker(nullptr), m_pRanger(nullptr), m_pTanker(nullptr),
	m_bSpoilSwitch(false), m_ulRenderDelay(GetTickCount64()),m_bClick(false),
	m_iChestStart(0), m_iChestEnd(0), m_ulChestDelay(GetTickCount64()),
	m_pClick(nullptr)
{
	ZeroMemory(&m_tInvenRect, sizeof(RECT));
	ZeroMemory(&m_tInvenInfo, sizeof(INFO));


}

CBattleResult::~CBattleResult()
{
}

void CBattleResult::Initialize()
{
	m_tInvenInfo.fCX = 275.f;
	m_tInvenInfo.fCY = 450.f;
	m_tInvenInfo.fX = WINCX / 2;
	m_tInvenInfo.fY = WINCY / 2;
	
	m_pPlayer = CObjMgr::Get_Instance()->Get_Player();
	m_pBerserker = CObjMgr::Get_Instance()->Get_Berserker();
	m_pRanger = CObjMgr::Get_Instance()->Get_Ranger();
	m_pTanker = CObjMgr::Get_Instance()->Get_Tanker();

	m_pRanger->Set_PosX(50);
	m_pPlayer->Set_PosX(200);
	m_pBerserker->Set_PosX(350);
	m_pTanker->Set_PosX(500);


	m_fDistance = 70.f;
	m_fHeight = 100.f;

	m_iChestStart = 0;
	m_iChestEnd = 3;

	m_fBlackBgAlpha = 255.f;
	Update_InvenRect();

	Setting_Img();

	Spoil_SetPos();

	m_pTempClick = nullptr;


	
}

void CBattleResult::Update()
{
	CObjMgr::Get_Instance()->Update();

	for (int i = 0; i < m_vecSpoil.size(); ++i)
		m_vecSpoil[i]->Update();

	
	if (m_ulChestDelay + 300 < GetTickCount64() && m_iChestStart != m_iChestEnd && !m_bSpoilSwitch)
	{
		++m_iChestStart;

		m_ulChestDelay = GetTickCount64();
	}

	
	if (m_ulRenderDelay + 3000 < GetTickCount64() && !m_bSpoilSwitch)
	{
		m_bSpoilSwitch = true;
		
	}

	Mouse_EventResult();

	
	if (!m_bClick && m_pClick)
	{
		if(m_pClick->Get_ItemInfo().m_pName == L"스태프")
		
		
		
		
		
		m_pTempClick->Set_ItemName(m_pClick->Get_ItemInfo().m_pName);
		m_pTempClick->Set_FramePos(m_tInvenRect.left + 400, m_tInvenRect.top + 50);
		m_pTempClick->Set_Pos(m_tInvenRect.left + 400, m_tInvenRect.top + 50);
		m_pTempClick->Update();
		//m_tInvenRect.left + 400, m_tInvenRect.top + 50

		m_bClick = true;
	}


	
}

void CBattleResult::Late_Update()
{
	CObjMgr::Get_Instance()->Late_Update();
	for (int i = 0; i < m_vecSpoil.size(); ++i)
		m_vecSpoil[i]->Late_Update();
}

void CBattleResult::Render(HDC hDC)
{
    HDC hMemDC = CBmpMgr::Get_Instance()->Find_Img(L"BossRoom");
    HDC hFloorDC = CBmpMgr::Get_Instance()->Find_Img(L"BossFloor");
    HDC hSpoilDC = CBmpMgr::Get_Instance()->Find_Img(L"Inventory_Small");
    HDC hSpoil1DC = CBmpMgr::Get_Instance()->Find_Img(L"Inventory_Small");
    HDC hSwordDC = CBmpMgr::Get_Instance()->Find_Img(L"Result_Icon");
    HDC hVictoryDC = CBmpMgr::Get_Instance()->Find_Img(L"Victory");
    HDC hChestDC = CBmpMgr::Get_Instance()->Find_Img(L"Chest_Open");
	HDC hTitleDC = CBmpMgr::Get_Instance()->Find_Img(L"TitleResult");

	TCHAR szBuff[32] = L"";

	HFONT hFont = CreateFont(25, 0, 0, 0, 0, 0, 0, 0, HANGUL_CHARSET, 0, 0, 0, VARIABLE_PITCH || FF_ROMAN, TEXT("PFStardust"));
	(HFONT)SelectObject(hDC, hFont);
	SetTextColor(hDC, RGB(255, 255, 255));
	DeleteObject(hFont);



    GdiTransparentBlt(hDC, 0, 0, WINCX, WINCY, hMemDC, 0, 0, 1280, 800, RGB(255, 0, 255));
    GdiTransparentBlt(hDC, 0, 0, WINCX, WINCY, hFloorDC, 0, 0, 1280, 800, RGB(255, 0, 255));


    if (m_bSpoilSwitch)
    {
        GdiTransparentBlt(hDC,
            m_tInvenRect.left,
            m_tInvenRect.top,
            m_tInvenInfo.fCX,
            m_tInvenInfo.fCY,
            hSpoilDC,
            0,
            0,
            m_tInvenInfo.fCX,
            m_tInvenInfo.fCY,
            RGB(255, 0, 255));

		GdiTransparentBlt(hDC,
			m_tInvenRect.left + 300,
			m_tInvenRect.top,
			m_tInvenInfo.fCX,
			m_tInvenInfo.fCY,
			hSpoil1DC,
			0,
			0,
			m_tInvenInfo.fCX,
			m_tInvenInfo.fCY,
			RGB(255, 0, 255));

		GdiTransparentBlt(hDC,
			m_tInvenRect.left + 300,
			m_tInvenRect.top,
			275,
			86,
			hTitleDC,
			0,
			0,
			275,
			86,
			RGB(255, 0, 255));
    }
	else
	{
		GdiTransparentBlt(hDC,
			WINCX / 2 - 100,
			WINCY / 2 - 350,
			199,
			187,
			hSwordDC,
			0,
			0,
			199,
			187,
			RGB(255, 0, 255));

		GdiTransparentBlt(hDC,
			WINCX / 2 - 220,
			WINCY / 2 - 100,
			462,
			95,
			hVictoryDC,
			0,
			0,
			462,
			95,
			RGB(255, 0, 255));

		GdiTransparentBlt(hDC,
			WINCX - 220,
			m_pPlayer->Get_Info().fY,
			120,
			120,
			hChestDC,
			m_iChestStart * 40,
			0,
			40,
			40,
			RGB(255, 0, 255));
	}
	
	if (m_bSpoilSwitch)
	{
		for (int i = 0; i < m_vecSpoil.size(); ++i)
		{
			m_vecSpoil[i]->Render(hDC);
		}

		swprintf_s(szBuff, L"전리품");
		TextOut(hDC, m_tInvenRect.left + 100, m_tInvenRect.top + 30, szBuff, lstrlen(szBuff));

		if (m_pClick)
		{
			

			swprintf_s(szBuff, m_pClick->Get_ItemInfo().m_pName);
			TextOut(hDC, m_tInvenRect.left + 400, m_tInvenRect.top + 50, szBuff, lstrlen(szBuff));
		}
		


	}
    

    CObjMgr::Get_Instance()->Render(hDC);

	
	if (m_pTempClick)
		m_pTempClick->Render(hDC);
}

void CBattleResult::Release()
{
}

void CBattleResult::Setting_Img()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/UI/Scene/Victory.bmp", L"Victory");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/UI/Scene/Result_Icon.bmp", L"Result_Icon");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/UI/Scene/Chest_Open.bmp", L"Chest_Open");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/UI/Public/Inventory_Small.bmp", L"Inventory_Small");

	
	CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/UI/Scene/Dividing_Line.bmp", L"Dividing_Line");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/UI/Scene/Result_Button.bmp", L"Result_Button");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/UI/Scene/Result_exp.bmp", L"Result_exp");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/UI/Scene/Result_Exp_BG.bmp", L"Result_Exp_BG");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/UI/Public/ItemTitle1.bmp", L"TitleResult");
}





void CBattleResult::Update_InvenRect()
{
	m_tInvenRect.left = LONG(m_tInvenInfo.fX - (m_tInvenInfo.fCX * 0.5f));
	m_tInvenRect.top = LONG(m_tInvenInfo.fY - (m_tInvenInfo.fCY * 0.5f));
	m_tInvenRect.right = LONG(m_tInvenInfo.fX + (m_tInvenInfo.fCX * 0.5f));
	m_tInvenRect.bottom = LONG(m_tInvenInfo.fY + (m_tInvenInfo.fCY * 0.5f));
}

void CBattleResult::Spoil_SetPos()
{
	for (int i = 0; i < m_vecSpoil.size(); ++i)
	{
		m_vecSpoil[i]->Set_FramePos(m_tInvenRect.left + m_fDistance, m_tInvenRect.top + m_fHeight);
		m_vecSpoil[i]->Set_Pos(m_tInvenRect.left + m_fDistance, m_tInvenRect.top + m_fHeight);
		m_fDistance += 70.f;
	}

	m_fDistance = 70.f;
}

void CBattleResult::Mouse_EventResult()
{
	POINT	pt{};
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);

	for (int i = 0; i < m_vecSpoil.size(); ++i)
	{
		if (PtInRect(&m_vecSpoil[i]->Get_Rect(), pt))
		{
			if (CKeyMgr::Get_Instance()->Key_Down(VK_LBUTTON))
				{
				if (m_pClick)
					Safe_Delete<CItem*>(m_pTempClick);


					m_pClick = m_vecSpoil[i];
				}
			
		}
	}

	
}








