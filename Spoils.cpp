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
        (int)m_tRect.left, // ���� ���� ��ġ X,Y ��ǥ
        (int)m_tRect.top,
        (int)m_tInfo.fCX,	// ���� ���� ����, ���� ����
        (int)m_tInfo.fCY,
        hCoinFrameDC,			// ��Ʈ�� �̹����� ��� �ִ� DC
        0,					// ��Ʈ���� ����� ���� X,Y��ǥ
        0,
        (int)m_tInfo.fCX,		// ����� ��Ʈ���� ����, ���� ������
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
