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
        (int)m_tDangerousRect.left, // ���� ���� ��ġ X,Y ��ǥ
        (int)m_tDangerousRect.top,
        (int)m_tDangerousInfo.fCX,	// ���� ���� ����, ���� ����
        (int)m_tDangerousInfo.fCY,
        hDangerDC,			// ��Ʈ�� �̹����� ��� �ִ� DC
        0,					// ��Ʈ���� ����� ���� X,Y��ǥ
        0,
        (int)m_tDangerousInfo.fCX,		// ����� ��Ʈ���� ����, ���� ������
        (int)m_tDangerousInfo.fCY,
        RGB(255, 0, 255)); // �����ϰ��� �ϴ� ����

    GdiTransparentBlt(hDC,
        (int)m_tRect.left, // ���� ���� ��ġ X,Y ��ǥ
        (int)m_tRect.top,
        (int)m_tInfo.fCX,	// ���� ���� ����, ���� ����
        (int)m_tInfo.fCY,
        hMemDC,			// ��Ʈ�� �̹����� ��� �ִ� DC
        0,					// ��Ʈ���� ����� ���� X,Y��ǥ
        0,
        (int)m_tInfo.fCX,		// ����� ��Ʈ���� ����, ���� ������
        (int)m_tInfo.fCY,
        RGB(255, 0, 255)); // �����ϰ��� �ϴ� ����

   
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

    // �÷��̾� �������� ���� �߰�
    float distance = std::sqrt(dx * dx + dy * dy);
    float directionX = dx / distance;
    float directionY = dy / distance;

    // �߰� �ӵ��� ���� �̵�
    float moveX = directionX * m_fSpeed;
    float moveY = directionY * m_fSpeed;

    // ���� ��ġ ����
    m_tInfo.fX += moveX;
    m_tInfo.fY += moveY;
}
