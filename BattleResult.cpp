#include "BattleResult.h"
#include "BmpMgr.h"
#include "Spoils.h"
#include "ObjMgr.h"
#include "KeyMgr.h"
#include "BasicStaff.h"
#include "SceneMgr.h"
#include "Inventory.h"

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
	
	m_tBtnInfo.fCX = 241.f;
	m_tBtnInfo.fCY = 50.f;
	
	

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
	m_tBtnInfo.fX = m_tInvenInfo.fX;
	m_tBtnInfo.fY = WINCY - 200;

	Update_BtnRect();

	Setting_Img();

	Spoil_SetPos();

	/*for (int i = 0; i < m_vecSpoil.size(); ++i)
	{
		CSceneMgr::Get_Instance()->Get_Lobby()->Get_Inventory()->Get_UnEquipItem() = m_vecSpoil[i];
	}*/
	vector<CItem*>* TempVector = CSceneMgr::Get_Instance()->Get_Lobby()->Get_Inventory()->GeT_UnEquipInven();

	for (int i = 0; i < TempVector->size(); ++i)
	{
		for (int j = 0; j < TempVector[i].size(); ++j)
		{
			if (TempVector[i][j]->Get_ItemInfo().m_pName == L"없음")
			{

			}
		}
	}

	AddFontResource(L"./Font/Galmuri11.ttf");
	
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
	HDC hFrameDC = CBmpMgr::Get_Instance()->Find_Img(L"Empty_Frame");
	HDC hBtnDC = CBmpMgr::Get_Instance()->Find_Img(L"Result_Button"); 
	

	TCHAR szBuff[256] = L"";

	HFONT hFont = CreateFont(20, 0, 0, 0, 0, 0, 0, 0, HANGUL_CHARSET, 0, 0, 0, VARIABLE_PITCH || FF_ROMAN, TEXT("Galmuri11"));
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

		GdiTransparentBlt(hDC,
			m_tBtnRect.left,
			m_tBtnRect.top,
			m_tBtnInfo.fCX,
			m_tBtnInfo.fCY,
			hBtnDC,
			0,
			0,
			m_tBtnInfo.fCX,
			m_tBtnInfo.fCY,
			RGB(255, 0, 255));

		swprintf_s(szBuff, L"은신처로 돌아가기");
		TextOut(hDC, m_tBtnRect.left + 35, m_tBtnInfo.fY - 10, szBuff, lstrlen(szBuff));
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
	
	hFont = CreateFont(25, 0, 0, 0, 0, 0, 0, 0, HANGUL_CHARSET, 0, 0, 0, VARIABLE_PITCH || FF_ROMAN, TEXT("Galmuri11"));
	(HFONT)SelectObject(hDC, hFont);
	DeleteObject(hFont);

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
			TextOut(hDC, m_tInvenRect.left + 400, m_tInvenRect.top + 100, szBuff, lstrlen(szBuff));


			hFont = CreateFont(20, 0, 0, 0, 0, 0, 0, 0, HANGUL_CHARSET, 0, 0, 0, VARIABLE_PITCH || FF_ROMAN, TEXT("Galmuri11"));
			(HFONT)SelectObject(hDC, hFont);
			DeleteObject(hFont);

			if (m_pClick->Get_ItemInfo().m_pType == L"무기")
			{
				swprintf_s(szBuff, L"공격력 : %d", m_pClick->Get_ItemInfo().m_iAttack); // 멧린얼
				TextOut(hDC, m_tInvenRect.left + 380, m_tInvenRect.top + 150, szBuff, lstrlen(szBuff));
			}

			else if (m_pClick->Get_ItemInfo().m_pType == L"방어구")
			{
				swprintf_s(szBuff, L"방어력 : %d", m_pClick->Get_ItemInfo().m_iArmor); // 멧린얼
				TextOut(hDC, m_tInvenRect.left + 380, m_tInvenRect.top + 150, szBuff, lstrlen(szBuff));
			}
			
			else if (m_pClick->Get_ItemInfo().m_pType == L"장신구")
			{
				swprintf_s(szBuff, L"마나 증가량 : %d", m_pClick->Get_ItemInfo().m_iMaxMana); // 멧린얼
				TextOut(hDC, m_tInvenRect.left + 380, m_tInvenRect.top + 150, szBuff, lstrlen(szBuff));

				swprintf_s(szBuff, L"마나 회복속도 증가량 : %f", m_pClick->Get_ItemInfo().m_fMpRecovery); // 멧린얼
				TextOut(hDC, m_tInvenRect.left + 380, m_tInvenRect.top + 200, szBuff, lstrlen(szBuff));
			}

		}
		


	}
    

    CObjMgr::Get_Instance()->Render(hDC);

	if (m_pClick)
	{
		HDC hFindDC = CBmpMgr::Get_Instance()->Find_Img(m_pClick->Get_FrameKey());
		if (m_pClick->Get_ItemName() == "목제 지팡이")
		{
			GdiTransparentBlt(hDC,
				m_tInvenRect.left + 420,
				m_tInvenRect.top + 20,
				m_pClick->Get_Info().fCX + 15,
				m_pClick->Get_Info().fCY + 15,
				hFindDC,
				0,
				0,
				m_pClick->Get_Info().fCX,
				m_pClick->Get_Info().fCY,
				RGB(255, 0, 255));
		}
	}
	
	
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

void CBattleResult::Update_BtnRect()
{
	m_tBtnRect.left = LONG(m_tBtnInfo.fX - (m_tBtnInfo.fCX * 0.5f));
	m_tBtnRect.top = LONG(m_tBtnInfo.fY - (m_tBtnInfo.fCY * 0.5f));
	m_tBtnRect.right = LONG(m_tBtnInfo.fX + (m_tBtnInfo.fCX * 0.5f));
	m_tBtnRect.bottom = LONG(m_tBtnInfo.fY + (m_tBtnInfo.fCY * 0.5f));
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

void CBattleResult::Mouse_BtnEvent()
{
	POINT	pt{};
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);

	if (PtInRect(&m_tBtnRect, pt))
	{
		if (CKeyMgr::Get_Instance()->Key_Down(VK_LBUTTON))
		{
			CSceneMgr::Get_Instance()->Scene_Change(SC_LOBBY);
		}
	}
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

					m_pClick = m_vecSpoil[i];
				}
			
		}
	}

	
}








