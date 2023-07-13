#include "BasicStaff.h"
#include "BmpMgr.h"

CBasicStaff::CBasicStaff()
{
}

CBasicStaff::~CBasicStaff()
{
}

CBasicStaff::CBasicStaff(const CBasicStaff& rhs)
{
}

void CBasicStaff::Initialize(void)
{
	m_bDrag = false;

	m_tFrameInfo.fCX = 63.f;
	m_tFrameInfo.fCY = 63.f;

	m_tInfo.fCX = 24.f;
	m_tInfo.fCY = 25.f;

	m_tItemInfo.m_iAttack = 5;
	m_tItemInfo.m_iMoney = 500;
	m_tItemInfo.m_pName = L"스태프";
	m_tItemInfo.m_pType = L"무기";
	m_sName = "목제 지팡이";
	m_pFrameKey = L"BasicStaff";

	m_eRender = GAMEOBJECT;
	Setting_Img();

	
}

int CBasicStaff::Update(void)
{
	MouseChase();

	__super::Update_Rect();
	Update_FrameRect();

	return OBJ_NOEVENT;
}

void CBasicStaff::Late_Update(void)
{
}

void CBasicStaff::Render(HDC hDC)
{
	HDC hFrameDC = CBmpMgr::Get_Instance()->Find_Img(L"Empty_Frame");
	HDC hMemDC = CBmpMgr::Get_Instance()->Find_Img(L"BasicStaff");

	GdiTransparentBlt(hDC,
		(int)m_tFrameRect.left,
		(int)m_tFrameRect.top,
		m_tFrameInfo.fCX,
		m_tFrameInfo.fCY,
		hFrameDC,
		0,
		0,
		m_tFrameInfo.fCX,
		m_tFrameInfo.fCY,
		RGB(255, 0, 255));

	GdiTransparentBlt(hDC,
		(int)m_tRect.left,
		(int)m_tRect.top,
		m_tInfo.fCX,
		m_tInfo.fCY,
		hMemDC,
		0,
		0,
		m_tInfo.fCX,
		m_tInfo.fCY,
		RGB(255, 0, 255));
}

void CBasicStaff::Release(void)
{
}

void CBasicStaff::Setting_Img()
{
	
}

