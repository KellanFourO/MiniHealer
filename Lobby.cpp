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
	m_dwNpcMoveDelay(0),m_bMoveSwitch(true),
	m_bOpenUI(false),m_bOpenMap(false),m_bOpenArmory(false),m_bOpenSkill(false),
	m_bOpenAbility(false),m_bOpenInfo(false),
	m_pMap(nullptr), m_pInventory(nullptr),
	m_iArmoryDrawID(0), m_iDoorDrawID(0)
{
	ZeroMemory(&m_tUIExitBtnRect, sizeof(RECT));
	ZeroMemory(&m_tUIExitInfo,    sizeof(INFO));

	ZeroMemory(&m_tArmoryRect, sizeof(RECT));
	ZeroMemory(&m_tArmoryInfo, sizeof(INFO));

	ZeroMemory(&m_tDoorRect, sizeof(RECT));
	ZeroMemory(&m_tDoorInfo, sizeof(INFO));

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

	

	Setting_Img();
	Create_Inventory();
	Create_Map();
	//Create_Button();
	Armory_Init();
	Door_Init();

	m_iFireStart = 0;
	m_iFireEnd = 7;

	m_bOpenArmory = false;
	
	

	Update_ArmoryRect();
	Update_DoorRect();
}

void CLobby::Update()
{
	if (m_dwFireDelay + 150 < GetTickCount64())
	{
		++m_iFireStart;
		m_dwFireDelay = GetTickCount64();
	}

	if (m_iFireStart == m_iFireEnd)
		m_iFireStart = 0;

	MouseEvent();

	CObjMgr::Get_Instance()->Update();
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

	HDC		HBtn_DC = CBmpMgr::Get_Instance()->Find_Img(L"UI_Exit");

	HDC		hColnDC = CBmpMgr::Get_Instance()->Find_Img(L"Coin");
	HDC		hColnFrameDC = CBmpMgr::Get_Instance()->Find_Img(L"CoinFrame");
	HDC		hColnBGDC = CBmpMgr::Get_Instance()->Find_Img(L"Coin_BackGround");

	HDC		hLabelDC = CBmpMgr::Get_Instance()->Find_Img(L"Label");
	HDC		hLevelBarDC = CBmpMgr::Get_Instance()->Find_Img(L"LevelBar");
	HDC		hExpBarDC = CBmpMgr::Get_Instance()->Find_Img(L"Exp_ProgressBar");

	HDC		hArmoryDC = CBmpMgr::Get_Instance()->Find_Img(L"LobbyArmory");
	HDC		hDoorDC = CBmpMgr::Get_Instance()->Find_Img(L"LobbyDoor");
	
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

	GdiTransparentBlt(hDC,
		m_tArmoryRect.left,
		m_tArmoryRect.top,
		m_tArmoryInfo.fCX,
		m_tArmoryInfo.fCY,
		hArmoryDC,
		0,
		m_iArmoryDrawID* m_tArmoryInfo.fCY,
		m_tArmoryInfo.fCX,
		m_tArmoryInfo.fCY,
		RGB(255, 0, 255));

	GdiTransparentBlt(hDC,
		m_tDoorRect.left,
		m_tDoorRect.top,
		m_tDoorInfo.fCX,
		m_tDoorInfo.fCY,
		hDoorDC,
		0,
		m_iDoorDrawID * m_tDoorInfo.fCY,
		m_tDoorInfo.fCX,
		m_tDoorInfo.fCY,
		RGB(255, 0, 255));
	


	CObjMgr::Get_Instance()->Render(hDC);



	if (m_bOpenUI)
	{
		//HDC hOpenDC = CBmpMgr::Get_Instance()->Find_Img(L"Common_Bg");
		//BitBlt(hDC, 0, 0, WINCX, WINCY, hOpenDC, 0, 0, SRCCOPY);
		
		if (m_bOpenMap)
		{
			m_tUIExitInfo.fX = 480.f;
			m_tUIExitInfo.fY = 50.f;
			Update_ExitRect();

			m_pMap->Render(hDC);
			m_pMap->Update();
		}

		else if (m_bOpenArmory)
		{
			m_tUIExitInfo.fX = 50.f;
			m_tUIExitInfo.fY = 50.f;
			Update_ExitRect();
			
			
		}

		
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
			RGB(255, 0, 255));
	}



}

void CLobby::Release()
{
	CObjMgr::Get_Instance()->Delete_ID(BUTTON);
	Safe_Delete<CMap*>(m_pMap);
	

	CSoundMgr::Get_Instance()->StopSound(LOBBY_BGM);
}

void CLobby::Create_Inventory()
{
	//m_pInventory = new CInventory;
	//m_pInventory->Initialize();
	//CObjMgr::Get_Instance()->Add_Object(PLAYER, CAbstractFactory<CInventory>::Create());
	CObjMgr::Get_Instance()->Add_Object(INVENTORY, CAbstractFactory<CInventory>::Create());

	
}

void CLobby::Create_Map()
{
	m_pMap = new CMap;
	m_pMap->Initialize();
}

void CLobby::Create_Button()
{
	//CObj* pObj = CAbstractFactory<CMyButton>::Create(350.f, 340.f);
	//pObj->Set_Size(200, 200);
	//pObj->Set_FrameKey(L"LobbyArmory");
	//CObjMgr::Get_Instance()->Add_Object(BUTTON, pObj);

	/*CObj* pObj = CAbstractFactory<CMyButton>::Create(100.f, 600.f);
	pObj->Set_Size(220, 220);
	pObj->Set_FrameKey(L"LobbySkill");
	CObjMgr::Get_Instance()->Add_Object(BUTTON, pObj);

	pObj = CAbstractFactory<CMyButton>::Create(300.f, 600.f);
	pObj->Set_Size(220, 220);
	pObj->Set_FrameKey(L"LobbyAbility");
	CObjMgr::Get_Instance()->Add_Object(BUTTON, pObj);*/

	/*pObj = CAbstractFactory<CMyButton>::Create(850.f, 540.f);
	pObj->Set_Size(440, 440);
	pObj->Set_FrameKey(L"LobbyDoor");
	CObjMgr::Get_Instance()->Add_Object(BUTTON, pObj);*/

	/*pObj = CAbstractFactory<CMyButton>::Create(1050.f, 300.f);
	pObj->Set_Size(176, 132);
	pObj->Set_FrameKey(L"LobbyPartyInfo");
	CObjMgr::Get_Instance()->Add_Object(BUTTON, pObj);

	pObj = CAbstractFactory<CMyButton>::Create(1230.f, 440.f);
	pObj->Set_Size(176, 264);
	pObj->Set_FrameKey(L"LobbySetting");
	CObjMgr::Get_Instance()->Add_Object(BUTTON, pObj);*/
}

void CLobby::Armory_Init()
{
	m_tArmoryInfo.fCX = 200.f;
	m_tArmoryInfo.fCY = 200.f;
	m_tArmoryInfo.fX = 350.f;
	m_tArmoryInfo.fY = 340.f;
}

void CLobby::Door_Init()
{
	m_tDoorInfo.fCX = 440.f;
	m_tDoorInfo.fCY = 440.f;
	m_tDoorInfo.fX = 850.f;
	m_tDoorInfo.fY = 540.f;
}



void CLobby::Setting_Img()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/BackGround/Lobby.bmp", L"Lobby");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/UI/Public/common_bg.bmp", L"Common_Bg");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/BackGround/LobbyFire.bmp", L"LobbyFire");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/BackGround/LobbyStair.bmp", L"LobbyStair");


	CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/UI/Scene/Lobby/Armory_Activity1.bmp", L"LobbyArmory");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/UI/Scene/Lobby/Skill_Activity1.bmp", L"LobbySkill");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/UI/Scene/Lobby/Ability_Activity1.bmp", L"LobbyAbility");

	
	CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/UI/Scene/Lobby/PartyInfo_Activity1.bmp", L"LobbyPartyInfo");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/UI/Scene/Lobby/Setting_Activity1.bmp", L"LobbySetting");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/UI/Scene/Lobby/Select_Door_Activity1.bmp", L"LobbyDoor");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/UI/Scene/Lobby/MiniMap1.bmp", L"LobbyMap");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/UI/Scene/Lobby/Exit_Button1.bmp", L"UI_Exit");


	CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/UI/Public/Coin.bmp", L"Coin");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/UI/Public/Coin_Frame.bmp", L"CoinFrame");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/UI/Public/Coin_BackGround.bmp", L"Coin_BackGround");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/UI/Player/Label.bmp", L"Label");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/UI/Player/LevelBar.bmp", L"LevelBar");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/UI/Player/Exp_ProgressBar.bmp", L"Exp_ProgressBar");

}

void CLobby::MouseEvent()
{
	POINT	pt{};
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);

	if (!m_bOpenUI)
	{

		if (PtInRect(&m_tArmoryRect, pt))
		{

			if (CKeyMgr::Get_Instance()->Key_Down(VK_LBUTTON))
			{
				m_bOpenUI = true;
				m_bOpenArmory = true;
			}

			m_iArmoryDrawID = 1;
		}
		else
			m_iArmoryDrawID = 0;


		if (PtInRect(&m_tDoorRect, pt))
		{

			if (CKeyMgr::Get_Instance()->Key_Down(VK_LBUTTON))
			{
				m_bOpenUI = true;
				m_bOpenMap = true;
			}

			m_iDoorDrawID = 1;
		}
		else
			m_iDoorDrawID = 0;
	}
	else if (m_bOpenUI)
	{
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

void CLobby::Update_ArmoryRect()
{
	m_tArmoryRect.left = LONG(m_tArmoryInfo.fX - (m_tArmoryInfo.fCX * 0.5f));
	m_tArmoryRect.top = LONG(m_tArmoryInfo.fY - (m_tArmoryInfo.fCY * 0.5f));
	m_tArmoryRect.right = LONG(m_tArmoryInfo.fX + (m_tArmoryInfo.fCX * 0.5f));
	m_tArmoryRect.bottom = LONG(m_tArmoryInfo.fY + (m_tArmoryInfo.fCY * 0.5f));
}

void CLobby::Update_DoorRect()
{
	m_tDoorRect.left = LONG(m_tDoorInfo.fX - (m_tDoorInfo.fCX * 0.5f));
	m_tDoorRect.top = LONG(m_tDoorInfo.fY - (m_tDoorInfo.fCY * 0.5f));
	m_tDoorRect.right = LONG(m_tDoorInfo.fX + (m_tDoorInfo.fCX * 0.5f));
	m_tDoorRect.bottom = LONG(m_tDoorInfo.fY + (m_tDoorInfo.fCY * 0.5f));
}

void CLobby::Update_ExitRect()
{
	m_tUIExitBtnRect.left = LONG(m_tUIExitInfo.fX - (m_tUIExitInfo.fCX * 0.5f));
	m_tUIExitBtnRect.top = LONG(m_tUIExitInfo.fY - (m_tUIExitInfo.fCY * 0.5f));
	m_tUIExitBtnRect.right = LONG(m_tUIExitInfo.fX + (m_tUIExitInfo.fCX * 0.5f));
	m_tUIExitBtnRect.bottom = LONG(m_tUIExitInfo.fY + (m_tUIExitInfo.fCY * 0.5f));
}
