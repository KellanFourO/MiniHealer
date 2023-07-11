#include "framework.h"
#include "Stage.h"
#include "ObjMgr.h"
#include "BmpMgr.h"
#include "AbstractFactory.h"
#include "Player.h"
#include "SoundMgr.h"

CStage::CStage():m_pBoneKnight(nullptr),m_pMap(nullptr)
{
}

CStage::~CStage()
{
	Release();
}

void CStage::Initialize()
{
	CSoundMgr::Get_Instance()->Initialize();
	CSoundMgr::Get_Instance()->PlaySoundW(L"SelectRoom_bgm.wav",STAGE_BGM, 1.f);

	CObjMgr::Get_Instance()->Get_Ranger()->Set_PosX(250.f);
	CObjMgr::Get_Instance()->Get_Player()->Set_PosX(350.f);
	CObjMgr::Get_Instance()->Get_Berserker()->Set_PosX(450.f);
	CObjMgr::Get_Instance()->Get_Tanker()->Set_PosX(550.f);
	


	Setting_Img();
	
	if (!m_pBoneKnight)
	{
		m_pBoneKnight = new CBoneKnight;
		m_pBoneKnight->Initialize();
	}

	if (!m_pMap)
	{
		m_pMap = new CMap;
		m_pMap->Initialize();
		m_pMap->Set_Size(470, 970);
	}

	m_pMap->Set_Pos(100, 10);
	dynamic_cast<CMap*>(m_pMap)->Set_MapInfo1(90, 125);
	dynamic_cast<CMap*>(m_pMap)->Set_MapInfoSize1(80, 70);
	
	dynamic_cast<CMap*>(m_pMap)->Set_MapInfo2(20, 225);
	dynamic_cast<CMap*>(m_pMap)->Set_MapInfoSize2(80, 70);
	


	m_pSelectDoorList.push_back(CAbstractFactory<CSelectDoor>::Create(500.f, 225.f));
	dynamic_cast<CSelectDoor*>(m_pSelectDoorList.back())->Set_Boss(m_pBoneKnight);
	m_pSelectDoorList.back()->Initialize();
	
	m_pLambList.push_back(CAbstractFactory<CLamb>::Create(300.f, 300.f));
	m_pLambList.back()->Initialize();
	m_pLambList.back()->Update();

	m_pStageFireList.push_back(CAbstractFactory<CStageFire>::Create(m_pLambList.back()->Get_Info().fX + 2, m_pLambList.back()->Get_Info().fY - 110));
	m_pStageFireList.back()->Initialize();

}

void CStage::Update()
{
	

	for (auto& iter : m_pSelectDoorList)
	{
		iter->Update();
	}


	for (auto& iter : m_pStageFireList)
	{
		iter->Update();
	}
	
	m_pMap->Update();
	
	
	CObjMgr::Get_Instance()->Update();

	

}

void CStage::Late_Update()
{
	
	CObjMgr::Get_Instance()->Late_Update();
	m_pMap->Late_Update();
}

void CStage::Render(HDC hDC)
{

	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Img(L"bossSelectRoom");
	
	BitBlt(hDC, 0, 0, WINCX, WINCY, hMemDC, 0, 0, SRCCOPY);

	
	

	CObjMgr::Get_Instance()->Render(hDC);

	for (auto& iter : m_pSelectDoorList)
	{
		iter->Render(hDC);
	}

	m_pMap->Render(hDC);

	for (auto& iter : m_pLambList)
	{
		iter->Render(hDC);
	}

	for (auto& iter : m_pStageFireList)
	{
		iter->Render(hDC);
	}
	
}

void CStage::Release()
{
	CSoundMgr::Get_Instance()->StopSound(STAGE_BGM);

	for_each(m_pSelectDoorList.begin(), m_pSelectDoorList.end(), Safe_Delete<CObj*>);
	m_pSelectDoorList.clear();

	for_each(m_pLambList.begin(), m_pLambList.end(), Safe_Delete<CObj*>);
	m_pLambList.clear();

	for_each(m_pStageFireList.begin(), m_pStageFireList.end(), Safe_Delete<CObj*>);
	m_pStageFireList.clear();

	Safe_Delete<CObj*>(m_pBoneKnight);

}

void CStage::Setting_Img()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/BackGround/bossSelectRoom.bmp", L"bossSelectRoom");
	
	CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/BackGround/FirePlace.bmp", L"FirePlace");

}
