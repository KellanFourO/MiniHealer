#include "BasicStaff.h"
#include "BmpMgr.h"

CBasicStaff::CBasicStaff()
{
}

CBasicStaff::~CBasicStaff()
{
}

void CBasicStaff::Initialize(void)
{
	m_tInfo.fCX = 24.f;
	m_tInfo.fCY = 25.f;

	m_tItemInfo.m_iAttack = 5;
	m_tItemInfo.m_iMoney = 500;

	m_eRender = GAMEOBJECT;
	Setting_Img();
}

int CBasicStaff::Update(void)
{
	

	__super::Update_Rect();
	return OBJ_NOEVENT;
}

void CBasicStaff::Late_Update(void)
{
}

void CBasicStaff::Render(HDC hDC)
{
	HDC hMemDC = CBmpMgr::Get_Instance()->Find_Img(L"BossRoom");

	GdiTransparentBlt(hDC,
		(int)m_tRect.left,
		(int)m_tRect.top,
		m_tInfo.fX,
		m_tInfo.fY,
		hMemDC,
		0,
		0,
		35,
		35,
		RGB(255, 0, 255));
}

void CBasicStaff::Release(void)
{
}

void CBasicStaff::Setting_Img()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/UI/Item/Staff.bmp", L"BasicStaff");
}
