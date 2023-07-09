#include "framework.h"
#include "Lobby.h"
#include "BmpMgr.h"
#include "SceneMgr.h"
#include "Player.h"
#include "Berserker.h"
#include "Ranger.h"
#include "Tanker.h"
#include "ObjMgr.h"
#include "AbstractFactory.h"
#include "MyButton.h"
#include "KeyMgr.h"
#include "SoundMgr.h"

CLobby::CLobby()
	:m_iFireStart(0),m_iFireEnd(0),m_dwFireDelay(GetTickCount64()),
	m_iTestStart(0),m_iTestEnd(0), m_dwLunariaDelay(0),
	m_dwNpcMoveDelay(0),m_bMoveSwitch(true),m_bOpenUI(false),m_iTestMotion(0),
	m_bOpenMap(false),m_bOpenArmory(false),m_bOpenSkill(false),m_bOpenAbility(false),
	m_bOpenInfo(false),m_pMap(nullptr)
{
	ZeroMemory(&m_tUIExitBtnRect, sizeof(RECT));
	ZeroMemory(&m_tUIExitInfo,    sizeof(INFO));
}

CLobby::~CLobby()
{
	Release();
}

void CLobby::Initialize()
{
	
	CSoundMgr::Get_Instance()->Initialize();

	CSoundMgr::Get_Instance()->PlaySoundW(L"Lobby_bgm.wav",LOBBY_BGM, 1.f);

	m_tUIExitInfo.fCX = 81.f;
	m_tUIExitInfo.fCY = 81.f;

	CObj* pPlayer = CObjMgr::Get_Instance()->Get_Player();
	CObj* pBerserker = CObjMgr::Get_Instance()->Get_Berserker();
	CObj* pRanger = CObjMgr::Get_Instance()->Get_Ranger();
	CObj* pTanker = CObjMgr::Get_Instance()->Get_Tanker();

	pPlayer->Set_Pos(800.f, 649.f);
	pBerserker->Set_Pos(950.f, 649.f);
	pRanger->Set_Pos(200.f, 649.f);
	pTanker->Set_Pos(1100.f, 649.f);

	pPlayer->Set_Start(false);
	pBerserker->Set_Start(false);
	pRanger->Set_Start(false);
	pTanker->Set_Start(false);

	if (!m_pMap)
	{
		m_pMap = new CMap;
		m_pMap->Initialize();

	}

	
	CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/BackGround/Lobby.bmp", L"Lobby");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/UI/Public/common_bg.bmp", L"Common_Bg");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/BackGround/LobbyFire.bmp", L"LobbyFire");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/BackGround/LobbyStair.bmp", L"LobbyStair");


	CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/UI/Scene/Lobby/Armory_Activity1.bmp", L"LobbyArmory");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/UI/Scene/Lobby/Skill_Activity1.bmp", L"LobbySkill");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/UI/Scene/Lobby/Ability_Activity1.bmp", L"LobbyAbility");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/UI/Scene/Lobby/Select_Door_Activity1.bmp", L"LobbyDoor");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/UI/Scene/Lobby/PartyInfo_Activity1.bmp", L"LobbyPartyInfo");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/UI/Scene/Lobby/Setting_Activity1.bmp", L"LobbySetting");
	

	CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/UI/Scene/Lobby/MiniMap1.bmp", L"LobbyMap");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/UI/Scene/Lobby/Exit_Button1.bmp", L"UI_Exit");


	CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/UI/Public/Coin.bmp", L"Coin");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/UI/Public/Coin_Frame.bmp", L"CoinFrame");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/UI/Public/Coin_BackGround.bmp", L"Coin_BackGround");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/UI/Player/Label.bmp", L"Label");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/UI/Player/LevelBar.bmp", L"LevelBar");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/UI/Player/Exp_ProgressBar.bmp", L"Exp_ProgressBar");


	CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/Boss2/Luna_Final.bmp", L"Luna");

	
	

	CObj* pObj = CAbstractFactory<CMyButton>::Create(350.f, 340.f);
	pObj->Set_Size(200, 200);
	pObj->Set_FrameKey(L"LobbyArmory");
	CObjMgr::Get_Instance()->Add_Object(BUTTON, pObj);

	pObj = CAbstractFactory<CMyButton>::Create(100.f, 600.f);
	pObj->Set_Size(220, 220);
	pObj->Set_FrameKey(L"LobbySkill");
	CObjMgr::Get_Instance()->Add_Object(BUTTON, pObj);

	pObj = CAbstractFactory<CMyButton>::Create(300.f, 600.f);
	pObj->Set_Size(220, 220);
	pObj->Set_FrameKey(L"LobbyAbility");
	CObjMgr::Get_Instance()->Add_Object(BUTTON, pObj);

	pObj = CAbstractFactory<CMyButton>::Create(850.f, 540.f);
	pObj->Set_Size(440, 440);
	pObj->Set_FrameKey(L"LobbyDoor");
	CObjMgr::Get_Instance()->Add_Object(BUTTON, pObj);

	pObj = CAbstractFactory<CMyButton>::Create(1050.f, 300.f);
	pObj->Set_Size(176, 132);
	pObj->Set_FrameKey(L"LobbyPartyInfo");
	CObjMgr::Get_Instance()->Add_Object(BUTTON, pObj);

	pObj = CAbstractFactory<CMyButton>::Create(1230.f, 440.f);
	pObj->Set_Size(176, 264);
	pObj->Set_FrameKey(L"LobbySetting");
	CObjMgr::Get_Instance()->Add_Object(BUTTON, pObj);

	m_iFireEnd = 7;

	m_iTestStart = 13;
	m_iTestEnd = 18;
	
}

void CLobby::Update()
{


	


	CObjMgr::Get_Instance()->Update();

	if (m_dwFireDelay + 150 < GetTickCount64())
	{
		++m_iFireStart;
		m_dwFireDelay = GetTickCount64();
	}

	if (m_dwLunariaDelay + 80 < GetTickCount64())
	{
		++m_iTestStart;
		m_dwLunariaDelay = GetTickCount64();
	}
	

	if (m_iFireStart == m_iFireEnd)
		m_iFireStart = 0; 

	if(m_iTestStart == m_iTestEnd)
		m_iTestStart = 0;



	CObj* pPlayer = CObjMgr::Get_Instance()->Get_Player();
	CObj* pBerserker = CObjMgr::Get_Instance()->Get_Berserker();
	CObj* pRanger = CObjMgr::Get_Instance()->Get_Ranger();
	CObj* pTanker = CObjMgr::Get_Instance()->Get_Tanker();

	
		

}

void CLobby::Late_Update()
{
	CObjMgr::Get_Instance()->Late_Update();
}

void CLobby::Render(HDC hDC)
{

	
	
	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Img(L"Lobby");
	BitBlt(hDC, 0, 0, WINCX, WINCY, hMemDC, 0, 0, SRCCOPY);
	

	
	HDC     hFireDC = CBmpMgr::Get_Instance()->Find_Img(L"LobbyFire");
	HDC		hStairDC = CBmpMgr::Get_Instance()->Find_Img(L"LobbyStair");

	HDC     hLunaDC = CBmpMgr::Get_Instance()->Find_Img(L"Luna");
	HDC		HBtn_DC = CBmpMgr::Get_Instance()->Find_Img(L"UI_Exit");

	HDC		hColnDC = CBmpMgr::Get_Instance()->Find_Img(L"Coin");
	HDC		hColnFrameDC = CBmpMgr::Get_Instance()->Find_Img(L"CoinFrame");
	HDC		hColnBGDC = CBmpMgr::Get_Instance()->Find_Img(L"Coin_BackGround");

	HDC		hLabelDC = CBmpMgr::Get_Instance()->Find_Img(L"Label");
	HDC		hLevelBarDC = CBmpMgr::Get_Instance()->Find_Img(L"LevelBar");
	HDC		hExpBarDC = CBmpMgr::Get_Instance()->Find_Img(L"Exp_ProgressBar");
	
	GdiTransparentBlt(hDC,
		30,
		30,
		300,
		55,
		hColnBGDC,
		0,
		0,
		400,
		55,
		RGB(255, 0, 255));
	
	GdiTransparentBlt(hDC,
		10,
		30,
		60,
		60,
		hColnFrameDC,
		0,
		0,
		60,
		60,
		RGB(255, 0, 255));

	GdiTransparentBlt(hDC,
		25,
		45,
		30,
		30,
		hColnDC,
		0,
		0,
		30,
		30,
		RGB(255, 0, 255));


	GdiTransparentBlt(hDC,
		370,
		35,
		877,
		55,
		hLevelBarDC,
		0,
		0,
		877,
		55,
		RGB(255, 0, 255));

	GdiTransparentBlt(hDC,
		390,
		41,
		550,
		40,
		hExpBarDC,
		0,
		0,
		550,
		36,
		RGB(255, 0, 255));

	GdiTransparentBlt(hDC,
		350,
		15,
		80,
		90,
		hLabelDC,
		0,
		0,
		80,
		90,
		RGB(255, 0, 255));

	BitBlt(hDC, 0, 0, WINCX, WINCY, hMemDC, 0, 0, SRCCOPY);


	GdiTransparentBlt(hDC,
		525,
		605,
		60,
		93,
		hFireDC,
		m_iFireStart * 60,
		0,
		60,
		93,
		RGB(255, 0, 255));


	/*GdiTransparentBlt(hDC,
		100,
		50,
		670,
		670,
		hLunaDC,
		m_iTestStart * 670,
		670 * 9,
		670,
		670,
		RGB(0, 0, 0));*/


	GdiTransparentBlt(hDC,
		600,
		300,
		271,
		196,
		hLunaDC,
		m_iTestStart * 271,
		0,
		271,
		196,
		RGB(255, 0, 255));
	

	//GdiTransparentBlt(hDC,
	//	(int)m_tRect.left + iScrollX, // 복사 받을 위치 X,Y 좌표
	//	(int)m_tRect.top + iScrollY,
	//	(int)m_tInfo.fCX,	// 복사 받을 가로, 세로 길이
	//	(int)m_tInfo.fCY,
	//	hMemDC,			// 비트맵 이미지를 담고 있는 DC
	//	m_tFrame.iFrameStart * (int)m_tInfo.fCX,					// 비트맵을 출력할 시작 X,Y좌표
	//	m_tFrame.iMotion * (int)m_tInfo.fCY,
	//	(int)m_tInfo.fCX,		// 출력할 비트맵의 가로, 세로 사이즈
	//	(int)m_tInfo.fCY,
	//	RGB(0, 0, 0)); // 제거하고자 하는 색상

	CObjMgr::Get_Instance()->Render(hDC);


	if (m_bOpenUI)
	{

		m_tUIExitBtnRect.left =   LONG(m_tUIExitInfo.fX - (m_tUIExitInfo.fCX * 0.5f));
		m_tUIExitBtnRect.top =    LONG(m_tUIExitInfo.fY - (m_tUIExitInfo.fCY * 0.5f));
		m_tUIExitBtnRect.right =  LONG(m_tUIExitInfo.fX + (m_tUIExitInfo.fCX * 0.5f));
		m_tUIExitBtnRect.bottom = LONG(m_tUIExitInfo.fY + (m_tUIExitInfo.fCY * 0.5f));

		HDC hOpenDC = CBmpMgr::Get_Instance()->Find_Img(L"Common_Bg");
		BitBlt(hDC, 0, 0, WINCX, WINCY, hOpenDC, 0, 0, SRCCOPY);


		if (m_bOpenMap)
		{
			
			
			

			m_tUIExitInfo.fX = 480.f;
			m_tUIExitInfo.fY = 50.f;

			GdiTransparentBlt(hDC,
				(int)m_tUIExitBtnRect.left, // 복사 받을 위치 X,Y 좌표
				(int)m_tUIExitBtnRect.top,
				(int)m_tUIExitInfo.fCX,	// 복사 받을 가로, 세로 길이
				(int)m_tUIExitInfo.fCY,
				HBtn_DC,			// 비트맵 이미지를 담고 있는 DC
				0,					// 비트맵을 출력할 시작 X,Y좌표
				0,
				(int)m_tUIExitInfo.fCX,		// 출력할 비트맵의 가로, 세로 사이즈
				(int)m_tUIExitInfo.fCY,
				RGB(255, 0, 255)); // 제거하고자 하는 색상

			
			m_pMap->Render(hDC);
			m_pMap->Select_Map();
			
			POINT	pt{};
			GetCursorPos(&pt);
			ScreenToClient(g_hWnd, &pt);

			if (PtInRect(&m_tUIExitBtnRect, pt))
			{
				if (CKeyMgr::Get_Instance()->Key_Down(VK_LBUTTON))
				{
					m_bOpenUI = false;
					m_bOpenArmory = false;

					m_bOpenAbility = false;
					m_bOpenSkill = false;
					m_bOpenInfo = false;
					m_bOpenMap = false;
				}
			}
			
		}


		
		
	}



}

void CLobby::Release()
{
	CObjMgr::Get_Instance()->Delete_ID(BUTTON);
	Safe_Delete<CMap*>(m_pMap);

	CSoundMgr::Get_Instance()->StopSound(LOBBY_BGM);
}
