#include "Lamb.h"
#include "BmpMgr.h"


CLamb::CLamb()
{
}

CLamb::~CLamb()
{
	Release();
}

void CLamb::Initialize(void)
{
    m_tInfo.fCX = 50.f;
    m_tInfo.fCY = 100.f;
	Setting_Img();
	m_eRender = UI;
}

int CLamb::Update(void)
{
    if (m_bDead)
        return OBJ_DEAD;
    
	__super::Update_Rect();

    return OBJ_NOEVENT;
}

void CLamb::Late_Update(void)
{
}

void CLamb::Render(HDC hDC)
{
    HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Img(L"LampPole");

	GdiTransparentBlt(hDC,
		m_tRect.left,
		m_tRect.top,
		50,
		100,
		hMemDC,
		0,
		0,
		113,
		222,
		RGB(255, 0, 255));
}

void CLamb::Release(void)
{
}

void CLamb::Setting_Img()
{
    CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/BackGround/LampPole.bmp", L"LampPole");
}
