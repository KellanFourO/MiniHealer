#include "BattleResult.h"
#include "BmpMgr.h"
#include "Spoils.h"

BattleResult::BattleResult()
{
}

BattleResult::~BattleResult()
{
}

void BattleResult::Initialize()
{
	
}

void BattleResult::Update()
{
}

void BattleResult::Late_Update()
{
}

void BattleResult::Render(HDC hDC)
{
	HDC hMemDC = CBmpMgr::Get_Instance()->Find_Img(L"BossRoom");
	HDC hFloorDC = CBmpMgr::Get_Instance()->Find_Img(L"BossFloor");


	GdiTransparentBlt(hDC, 0, 0, WINCX, WINCY, hMemDC, 0, 0, 1280, 800, RGB(255, 0, 255));
	GdiTransparentBlt(hDC, 0, 0, WINCX, WINCY, hFloorDC, 0, 0, 1280, 800, RGB(255, 0, 255));

}

void BattleResult::Release()
{
}

void BattleResult::Setting_Img()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/UI/Scene/Victory.bmp", L"Victory");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/UI/Scene/Result_Icon.bmp", L"Result_Icon");


	
	CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/UI/Scene/Dividing_Line.bmp", L"Dividing_Line");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/UI/Scene/Result_Button.bmp", L"Result_Button");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/UI/Scene/Result_exp.bmp", L"Result_exp");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/UI/Scene/Result_Exp_BG.bmp", L"Result_Exp_BG");
	


}

void BattleResult::Produce_Spoil()
{
	
}


