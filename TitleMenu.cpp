#include "framework.h"
#include "TitleMenu.h"
#include "BmpMgr.h"
#include "AbstractFactory.h"
#include "MyButton.h"
#include "ObjMgr.h"
#include "Player.h"
#include "Berserker.h"
#include "Ranger.h"
#include "Tanker.h"
#include "Door.h"
#include "SceneMgr.h"
#include "SoundMgr.h"


CTitleMenu::CTitleMenu() :m_dwStartDelay(GetTickCount64()), m_bSceneChange(true)
{
}

CTitleMenu::~CTitleMenu()
{
	Release();
}

void CTitleMenu::Initialize()
{
	CSoundMgr::Get_Instance()->Initialize();

	CSoundMgr::Get_Instance()->PlaySoundW(L"MainMenu_bgm.wav",TITLE_BGM, 1.f);

	CObjMgr::Get_Instance()->Add_Object(RANGER, CAbstractFactory<CRanger>::Create());
	CObjMgr::Get_Instance()->Add_Object(PLAYER, CAbstractFactory<CPlayer>::Create());
	CObjMgr::Get_Instance()->Add_Object(BERSERKER, CAbstractFactory<CBerserker>::Create());
	CObjMgr::Get_Instance()->Add_Object(TANKER, CAbstractFactory<CTanker>::Create());
	CObjMgr::Get_Instance()->Add_Object(DOOR, CAbstractFactory<CDoor>::Create());

	CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/BackGround/MainMap.bmp", L"Menu");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/UI/Scene/Title_Start.bmp", L"Title_Start");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/UI/Scene/Title_Setting.bmp", L"Title_Setting");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/UI/Scene/Title_Exit.bmp", L"Title_Exit");

	
	CObj* pObj = CAbstractFactory<CMyButton>::Create(540, 350);
	pObj->Set_FrameKey(L"Title_Start");
	CObjMgr::Get_Instance()->Add_Object(BUTTON, pObj);


	pObj = CAbstractFactory<CMyButton>::Create(550, 450);
	pObj->Set_FrameKey(L"Title_Setting");
	CObjMgr::Get_Instance()->Add_Object(BUTTON, pObj);



	pObj = CAbstractFactory<CMyButton>::Create(550, 550);
	pObj->Set_FrameKey(L"Title_Exit");
	CObjMgr::Get_Instance()->Add_Object(BUTTON, pObj);



	
}

void CTitleMenu::Update()
{
	CObjMgr::Get_Instance()->Update();
	

	if (CObjMgr::Get_Instance()->Get_Objects(DOOR).front()->Get_End())
	{
		CSceneMgr::Get_Instance()->Scene_Change(SC_LOBBY);
		CObjMgr::Get_Instance()->Get_Objects(DOOR).front()->Set_End(false);
	}

	//CSoundMgr::Get_Instance()->PlaySoundW()
}

void CTitleMenu::Late_Update()
{
	CObjMgr::Get_Instance()->Late_Update();

	
}

void CTitleMenu::Render(HDC hDC)
{

	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Img(L"Menu");
	GdiTransparentBlt(hDC, 0, 0, WINCX, WINCY, hMemDC, 0, 0, 1280, 800, RGB(255, 0, 255));

	
	CObjMgr::Get_Instance()->Render(hDC);

}

void CTitleMenu::Release()
{

	//CObjMgr::Get_Instance()->Delete_ID(PLAYER);
	CObjMgr::Get_Instance()->Delete_ID(BUTTON);
	//CObjMgr::Get_Instance()->Delete_ID(DOOR);
	/*CObjMgr::Get_Instance()->Delete_ID(BUTTON);
	CObjMgr::Get_Instance()->Delete_ID(PLAYER);*/
	CSoundMgr::Get_Instance()->StopSound(TITLE_BGM);
}

