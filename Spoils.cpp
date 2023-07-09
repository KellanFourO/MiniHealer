#include "Spoils.h"
#include "BmpMgr.h"

CSpoils::CSpoils()
{
    ZeroMemory(&m_tItemRect, sizeof(RECT));
    ZeroMemory(&m_tItemeInfo, sizeof(INFO));
}

CSpoils::~CSpoils()
{
}

void CSpoils::Initialize(void)
{
    m_tInfo.fCX = 60.f;
    m_tInfo.fCY = 60.f;
    m_eRender = UI;

    Setting_Img();
}

int CSpoils::Update(void)
{
    
    __super::Update_Rect();

    return OBJ_NOEVENT;
}

void CSpoils::Late_Update(void)
{
}

void CSpoils::Render(HDC hDC)
{
    HDC hCoinFrameDC = CBmpMgr::Get_Instance()->Find_Img(L"CoinFrame");

    GdiTransparentBlt(hDC,
        (int)m_tRect.left, // 복사 받을 위치 X,Y 좌표
        (int)m_tRect.top,
        (int)m_tInfo.fCX,	// 복사 받을 가로, 세로 길이
        (int)m_tInfo.fCY,
        hCoinFrameDC,			// 비트맵 이미지를 담고 있는 DC
        0,					// 비트맵을 출력할 시작 X,Y좌표
        0,
        (int)m_tInfo.fCX,		// 출력할 비트맵의 가로, 세로 사이즈
        (int)m_tInfo.fCY,
        RGB(255, 0, 255));

}

void CSpoils::Release(void)
{
}

void CSpoils::Setting_Img()
{
}

void CSpoils::UpdateItemRect()
{
}
