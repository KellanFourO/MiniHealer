#include "Item.h"
#include "BmpMgr.h"
#include "ObjMgr.h"

CItem::CItem():m_fPreX(0),m_fPreY(0),
			   m_bResult(false),m_bDrag(false),
			   m_sName(""),m_iItemNumber(0)
{
	ZeroMemory(&m_tItemInfo, sizeof(ItemInfo));
	ZeroMemory(&m_tFrameRect, sizeof(RECT));
	ZeroMemory(&m_tFrameInfo, sizeof(INFO));
}

CItem::CItem(const string& ItemName):m_sName(ItemName)
{
	ZeroMemory(&m_tItemInfo, sizeof(ItemInfo));
	ZeroMemory(&m_tFrameRect, sizeof(RECT));
	ZeroMemory(&m_tFrameInfo, sizeof(INFO));
}



CItem::CItem(const CItem& rhs)
{
	ZeroMemory(&m_tItemInfo, sizeof(ItemInfo));
	ZeroMemory(&m_tFrameRect, sizeof(RECT));
	ZeroMemory(&m_tFrameInfo, sizeof(INFO));
}



CItem::~CItem()
{
}

void CItem::Initialize(void)
{
	m_tFrameInfo.fCX = 63.f;
	m_tFrameInfo.fCY = 63.f;

	m_tInfo.fCX = 24.f;
	m_tInfo.fCY = 25.f;

	m_eRender = UI;
	Setting_Img();

	m_bDrag = false;
	m_bResult = false;
	m_fPreX = 0;
	m_fPreY = 0;
	m_sName = "";
	m_iItemNumber = 0;
}

int CItem::Update(void)
{
	

	MouseChase();

	__super::Update_Rect();
	Update_FrameRect();
	
	if (m_bDrag)
	{
		m_fPreX = m_tInfo.fX;
		m_fPreY = m_tInfo.fY;
	}
	else
	{
		m_tInfo.fX = m_tFrameInfo.fX;
		m_tInfo.fY = m_tFrameInfo.fY;
	}


	return OBJ_NOEVENT;
}

void CItem::Late_Update(void)
{
}

void CItem::Render(HDC hDC)
{
	HDC hMemDC = CBmpMgr::Get_Instance()->Find_Img(L"Empty_Frame");
	HDC hFindDC = CBmpMgr::Get_Instance()->Find_Img(L"BasicStaff");
	
	if (m_sName == "°Ë")
	{

	}

	TCHAR szBuff[32] = L"";

		GdiTransparentBlt(hDC,
		(int)m_tFrameRect.left,
		(int)m_tFrameRect.top,
		m_tFrameInfo.fCX,
		m_tFrameInfo.fCY,
		hMemDC,
		0,
		0,
		m_tFrameInfo.fCX,
		m_tFrameInfo.fCY,
		RGB(255, 0, 255));

		if (m_sName != "")
		{
			GdiTransparentBlt(hDC,
				(int)m_tRect.left,
				(int)m_tRect.top,
				m_tInfo.fCX,
				m_tInfo.fCY,
				hFindDC,
				0,
				0,
				m_tInfo.fCX,
				m_tInfo.fCY,
				RGB(255, 0, 255));
		}
		


	HFONT hFont = CreateFont(14, 0, 0, 0, 0, 0, 0, 0, HANGUL_CHARSET, 0, 0, 0, VARIABLE_PITCH || FF_ROMAN, TEXT("PFStardust"));
	(HFONT)SelectObject(hDC, hFont);
	SetTextColor(hDC, RGB(255, 255, 255));

	swprintf_s(szBuff, L" %d", m_iItemNumber);
	TextOut(hDC, (int)m_tFrameInfo.fX, (int)m_tFrameInfo.fY, szBuff, lstrlen(szBuff));


	DeleteObject(hFont);

	
	/*SelectObject(hDC, GetStockObject(DC_PEN));
	SetDCPenColor(hDC, RGB(255, 255, 255));
	Rectangle(hDC,m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);*/
	
}

void CItem::Release(void)
{
}

void CItem::Setting_Img()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/UI/Public/Item_Frame.bmp", L"Item_Frame");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/UI/Inventory/Empty_Frame1.bmp", L"Empty_Frame");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/UI/Public/Public_Disabled.bmp", L"Public_Disabled");


	CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/UI/Item/Staff.bmp", L"BasicStaff");

}

void CItem::ApplyEffect()
{
	if (m_tItemInfo.m_bEquip)
	{
		CObjMgr::Get_Instance()->Get_Player()->Set_Attack(m_tItemInfo.m_iAttack);
	}
}

void CItem::MouseChase()
{
	
	POINT	pt{};
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);


	if (m_bDrag)
	{
		m_tInfo.fX = pt.x;
		m_tInfo.fY = pt.y;	
	}

	//if (!m_bResult)
	//{
	//	m_tInfo.fX = m_fPreX;
	//	m_tInfo.fY = m_fPreY;
	//}
	



}

void CItem::Update_FrameRect()
{
	m_tFrameRect.left = LONG(m_tFrameInfo.fX - (m_tFrameInfo.fCX * 0.5f));
	m_tFrameRect.top = LONG(m_tFrameInfo.fY - (m_tFrameInfo.fCY * 0.5f));
	m_tFrameRect.right = LONG(m_tFrameInfo.fX + (m_tFrameInfo.fCX * 0.5f));
	m_tFrameRect.bottom = LONG(m_tFrameInfo.fY + (m_tFrameInfo.fCY * 0.5f));
}

