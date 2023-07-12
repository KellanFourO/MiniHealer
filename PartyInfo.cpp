#include "PartyInfo.h"
#include "BmpMgr.h"
#include "BmpMgr.h"

CPartyInfo::CPartyInfo()
{
}

CPartyInfo::~CPartyInfo()
{
}

void CPartyInfo::Initialize(void)
{
	m_tInfo.fCX = 900.f;
	m_tInfo.fCY = 1000.f;
}

int CPartyInfo::Update(void)
{
	return 0;
}

void CPartyInfo::Late_Update(void)
{
}

void CPartyInfo::Render(HDC hDC)
{
	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Img(L"PartyInfo");
}


void CPartyInfo::Release(void)
{
}

void CPartyInfo::Setting_Img()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/UI/Scene/Tanker_Icon.bmp", L"Tanker_Icon");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/UI/Scene/Buseker_Icon.bmp", L"Buseker_Icon");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/UI/Scene/Healer_Icon.bmp", L"Healer_Icon");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/UI/Scene/Ranger_Icon.bmp", L"Ranger_Icon");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/UI/Player/PartyInfo.bmp", L"PartyInfo");


}
