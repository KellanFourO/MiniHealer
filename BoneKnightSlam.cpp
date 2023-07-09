#include "BoneKnightSlam.h"
#include "BmpMgr.h"

CBoneKnightSlam::CBoneKnightSlam():m_fDestroyDistance(0), m_dwDestroyDelay(GetTickCount64())
{
}

CBoneKnightSlam::~CBoneKnightSlam()
{
}

void CBoneKnightSlam::Initialize(void)
{
	m_tInfo.fCX = 142.f;
	m_tInfo.fCY = 186.f;

	m_tStatus.m_iAttack = 25.f;
	m_fSpeed = 5.f;
	m_eRender = GAMEOBJECT;

	if (m_eDir == LEFT)
	{
		m_tFrame.iMotion = 0;
		m_tFrame.dwSpeed = 200.f;
		m_iStart = 5;
		m_tFrame.iFrameStart = 5;
		m_tFrame.iFrameEnd = 0;

	}
	else if (m_eDir == RIGHT)
	{
		m_tFrame.iMotion = 1;
		m_tFrame.dwSpeed = 200.f;
		m_tFrame.iFrameStart = 0;
		m_tFrame.iFrameEnd = 5;

	
	}

	Setting_Img();
}

int CBoneKnightSlam::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;


	if (m_eDir == LEFT)
	{
		m_tInfo.fX -= m_fSpeed;
	}
	else if (m_eDir == RIGHT)
	{
		m_tInfo.fX += m_fSpeed;
	}



	__super::Update_Rect();

	__super::Move_Frame();
	return OBJ_NOEVENT;
}

void CBoneKnightSlam::Late_Update(void)
{
	if (m_dwDestroyDelay + 1000 < GetTickCount64())
	{
		m_bDead = true;

		m_dwDestroyDelay = GetTickCount64();
	}
	
}

void CBoneKnightSlam::Render(HDC hDC)
{
	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Img(L"BoneKnightSlam");

	GdiTransparentBlt(hDC,
		(int)m_tRect.left, // ���� ���� ��ġ X,Y ��ǥ
		(int)m_tRect.top,
		(int)m_tInfo.fCX,	// ���� ���� ����, ���� ����
		(int)m_tInfo.fCY,
		hMemDC,			// ��Ʈ�� �̹����� ��� �ִ� DC
		m_tFrame.iFrameStart * m_tInfo.fCX,					// ��Ʈ���� ����� ���� X,Y��ǥ
		m_tFrame.iMotion * m_tInfo.fCY,
		m_tInfo.fCX,		// ����� ��Ʈ���� ����, ���� ������
		m_tInfo.fCY,
		RGB(255, 0, 255)); // �����ϰ��� �ϴ� ����

}

void CBoneKnightSlam::Release(void)
{
}

void CBoneKnightSlam::Setting_Img()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/Boss/BoneKnightSkill.bmp", L"BoneKnightSlam");
}
