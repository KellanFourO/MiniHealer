#include "BoneKnightThrowSword.h"
#include "ObjMgr.h"
#include "BmpMgr.h"

CBoneKnightThrowSword::CBoneKnightThrowSword():m_dwDestroyDelay(GetTickCount64()),
m_dwDangerousDelay(GetTickCount64()), m_tDangerousSwitch(true)
{
    ZeroMemory(&m_tDangerousRect, sizeof(RECT));
    ZeroMemory(&m_tDangerousInfo, sizeof(INFO));
}

CBoneKnightThrowSword::~CBoneKnightThrowSword()
{
}

void CBoneKnightThrowSword::Initialize(void)
{
    m_tInfo.fCX = 80.f;
    m_tInfo.fCY = 200.f;
    m_fSpeed = 20.f;
    m_fAngle = 90.f;
    m_eRender = GAMEOBJECT;
    m_tStatus.m_iAttack = 300.f;


    m_tDangerousInfo.fCX = 135.f;
    m_tDangerousInfo.fCY = 135.f;
    

    m_tDangerousInfo.fX = CObjMgr::Get_Instance()->Get_Player()->Get_Info().fX;
    m_tDangerousInfo.fY = CObjMgr::Get_Instance()->Get_Player()->Get_Info().fY;
    UpdateDangerousRect();
    Setting_Img();
}

int CBoneKnightThrowSword::Update(void)
{
    if (m_bDead)
        return OBJ_DEAD;
    
    AngleAttack();
    
    return OBJ_NOEVENT;
}

void CBoneKnightThrowSword::Late_Update(void)
{
    if (m_dwDangerousDelay + 1000 < GetTickCount64() && m_tDangerousSwitch)
    {
        ZeroMemory(&m_tDangerousRect, sizeof(RECT));
        __super::Update_Rect();
        
        m_tDangerousSwitch = false;
    }

    if (m_dwDestroyDelay + 2000 < GetTickCount64())
    {
        m_bDead = true;
    }
}

void CBoneKnightThrowSword::Render(HDC hDC)
{
    HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Img(L"BoneKnightSwordDrop");
    HDC     hDangerDC = CBmpMgr::Get_Instance()->Find_Img(L"Danger");

    GdiTransparentBlt(hDC,
        (int)m_tDangerousRect.left, // 복사 받을 위치 X,Y 좌표
        (int)m_tDangerousRect.top,
        (int)m_tDangerousInfo.fCX,	// 복사 받을 가로, 세로 길이
        (int)m_tDangerousInfo.fCY,
        hDangerDC,			// 비트맵 이미지를 담고 있는 DC
        0,					// 비트맵을 출력할 시작 X,Y좌표
        0,
        (int)m_tDangerousInfo.fCX,		// 출력할 비트맵의 가로, 세로 사이즈
        (int)m_tDangerousInfo.fCY,
        RGB(255, 0, 255)); // 제거하고자 하는 색상

    GdiTransparentBlt(hDC,
        (int)m_tRect.left, // 복사 받을 위치 X,Y 좌표
        (int)m_tRect.top,
        (int)m_tInfo.fCX,	// 복사 받을 가로, 세로 길이
        (int)m_tInfo.fCY,
        hMemDC,			// 비트맵 이미지를 담고 있는 DC
        0,					// 비트맵을 출력할 시작 X,Y좌표
        0,
        (int)m_tInfo.fCX,		// 출력할 비트맵의 가로, 세로 사이즈
        (int)m_tInfo.fCY,
        RGB(255, 0, 255)); // 제거하고자 하는 색상

   
}

void CBoneKnightThrowSword::Release(void)
{
}

void CBoneKnightThrowSword::Setting_Img()
{

    CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/Boss/BoneKnightSwordDrop.bmp", L"BoneKnightSwordDrop");
    CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/Boss/Danger1.bmp", L"Danger");
}

void CBoneKnightThrowSword::UpdateDangerousRect()
{
    m_tDangerousRect.left = LONG(m_tDangerousInfo.fX - (m_tDangerousInfo.fCX * 0.5f));
    m_tDangerousRect.top = LONG(m_tDangerousInfo.fY - (m_tDangerousInfo.fCY * 0.5f));
    m_tDangerousRect.right = LONG(m_tDangerousInfo.fX + (m_tDangerousInfo.fCX * 0.5f));
    m_tDangerousRect.bottom = LONG(m_tDangerousInfo.fY + (m_tDangerousInfo.fCY * 0.5f));
}

void CBoneKnightThrowSword::AngleAttack()
{

    float dx = m_tDangerousInfo.fX - m_tInfo.fX;
    float dy = m_tDangerousInfo.fY - m_tInfo.fY;

    m_fAngle = atan2(dy, dx) * 180 / PI;

    // 플레이어 방향으로 적을 추격
    float distance = std::sqrt(dx * dx + dy * dy);
    float directionX = dx / distance;
    float directionY = dy / distance;

    // 추격 속도에 따라 이동
    float moveX = directionX * m_fSpeed;
    float moveY = directionY * m_fSpeed;

    // 적의 위치 갱신
    m_tInfo.fX += moveX;
    m_tInfo.fY += moveY;
}
