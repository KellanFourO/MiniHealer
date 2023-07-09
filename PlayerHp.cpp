#include "PlayerHp.h"
#include "BmpMgr.h"
#include "ObjMgr.h"
#include "PlayerSKill.h"
#include "Player.h"

CPlayerHp::CPlayerHp() :m_iSelectMotion(0), m_bSelect(false), m_iIconMotion(0)
{
	ZeroMemory(&m_tHpBarRect, sizeof(RECT));
	ZeroMemory(&m_tHpBarInfo, sizeof(INFO));

	ZeroMemory(&m_tIconRect, sizeof(RECT));
	ZeroMemory(&m_tIconInfo, sizeof(INFO));

	ZeroMemory(&m_tCastingFrameRect, sizeof(RECT));
	ZeroMemory(&m_tCastingFrameInfo, sizeof(INFO));

	ZeroMemory(&m_tCastingProRect, sizeof(RECT));
	ZeroMemory(&m_tCastingProInfo, sizeof(INFO));

	ZeroMemory(&m_tSelectFrameRect, sizeof(RECT));
	ZeroMemory(&m_tSelectFrameInfo, sizeof(INFO));

	ZeroMemory(&m_tManaRect, sizeof(RECT));
	ZeroMemory(&m_tManaInfo, sizeof(INFO));
}

CPlayerHp::~CPlayerHp()
{
	Release();
}

void CPlayerHp::Initialize(void)
{
	m_tInfo.fCX = 455.f;
	m_tInfo.fCY = 90.f;

	m_tHpBarInfo.fCX = 364.f;
	m_tHpBarInfo.fCY = 18.f;
	
	m_tHpBarInfo.fX = m_tInfo.fX - 10;
	m_tHpBarInfo.fY = m_tInfo.fY;

	m_tIconInfo.fCX = 80.f;
	m_tIconInfo.fCY = 80.f;

	m_tIconInfo.fX = m_tInfo.fX - 220;
	m_tIconInfo.fY = m_tInfo.fY;

	m_tSelectFrameInfo.fCX = 300.f;
	m_tSelectFrameInfo.fCY = 300.f;
	m_tSelectFrameInfo.fX = m_tIconInfo.fX + 70;
	m_tSelectFrameInfo.fY = m_tIconInfo.fY + 75;

	m_tManaInfo.fCX = 112.f;
	m_tManaInfo.fCY = 105.f;
	m_tManaInfo.fX = 1050.f;
	m_tManaInfo.fY = 750.f;

	dynamic_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Get_VecSkill().front()->Set_Pos(400,750);


	Setting_Img();



	m_eRender = UI;

	Update_HpBarRect();
	Update_IconRect();
	Update_ManaRect();

}

int CPlayerHp::Update(void)
{
	if (m_pTarget == dynamic_cast<CPlayerSKill*>(CObjMgr::Get_Instance()->Get_Objects(SKILL).front())->Get_SkillTarget())
		m_bSelect = true;
	else
		m_bSelect = false;

	if (m_pTarget->Get_Dead())
	{
		m_iIconMotion = 1;
	}

	if (m_bSelect)
		m_iSelectMotion = 1;
	else
		m_iSelectMotion = 0;

	
	__super::Update_Rect();
	Update_SelectFrameRect();
	
	return OBJ_NOEVENT;
}

void CPlayerHp::Late_Update(void)
{
	if (m_pTarget->Get_Hp() <= 0)
		m_pTarget->Set_Dead();
}

void CPlayerHp::Render(HDC hDC)
{
	HDC hHpBar_DC = CBmpMgr::Get_Instance()->Find_Img(L"HP_Bar");
	HDC hHpFrame_DC = CBmpMgr::Get_Instance()->Find_Img(L"HP_Frame");
	
	HDC hIconDC = CBmpMgr::Get_Instance()->Find_Img(L"Tanker_Icon");
	HDC hSelectFrame_DC = CBmpMgr::Get_Instance()->Find_Img(L"Player_Select_Frame");

	HDC hManaFrame_DC = CBmpMgr::Get_Instance()->Find_Img(L"Empty_Mana");
	HDC hManaDC = CBmpMgr::Get_Instance()->Find_Img(L"ManaImage");
	HDC hManaEmptyDC = CBmpMgr::Get_Instance()->Find_Img(L"ManaImage_Empty");
	

	if (m_pTarget->Get_Name() == L"ÅÊÄ¿")
	{
		 hIconDC = CBmpMgr::Get_Instance()->Find_Img(L"Tanker_Icon");
	}
	else if (m_pTarget->Get_Name() == L"¹ö¼­Ä¿")
	{
		 hIconDC = CBmpMgr::Get_Instance()->Find_Img(L"Buseker_Icon");
	}

	else if (m_pTarget->Get_Name() == L"Èú·¯")
	{
		 hIconDC = CBmpMgr::Get_Instance()->Find_Img(L"Healer_Icon");
	}

	else if (m_pTarget->Get_Name() == L"·¹ÀÎÀú")
	{
		 hIconDC = CBmpMgr::Get_Instance()->Find_Img(L"Ranger_Icon");
	}

	float fPlayerHp = m_pTarget->Get_Status().m_iMaxHp;
	float fPlayerHpRatio = (static_cast<float>(m_pTarget->Get_Hp()) / fPlayerHp);

	

	GdiTransparentBlt(hDC,
		(int)m_tRect.left,
		(int)m_tRect.top,
		455,
		90,
		hHpFrame_DC,
		0,
		m_iSelectMotion * 90,
		455,
		90,
		RGB(255, 0, 255));

	GdiTransparentBlt(hDC,
		(int)m_tHpBarRect.left,
		(int)m_tHpBarRect.top,
		364 * fPlayerHpRatio,
		m_tHpBarInfo.fCY,
		hHpBar_DC,
		0,
		0,
		364 * fPlayerHpRatio,
		18,
		RGB(255, 255, 255));


	GdiTransparentBlt(hDC,
		(int)m_tSelectFrameRect.left,
		(int)m_tSelectFrameRect.top,
		150,
		150,
		hSelectFrame_DC,
		0,
		m_iSelectMotion * 300,
		300,
		300,
		RGB(255, 0, 255));

	GdiTransparentBlt(hDC,
		(int)m_tIconRect.left,
		(int)m_tIconRect.top,
		70,
		70,
		hIconDC,
		0,
		m_iIconMotion * 80,
		80,
		80,
		RGB(255, 0, 255));

	TCHAR szBuff[32] = L"";
	
	HFONT hFont = CreateFont(14, 0, 0, 0, 0, 0, 0, 0, HANGUL_CHARSET, 0, 0, 0, VARIABLE_PITCH || FF_ROMAN, TEXT("PFStardust"));
	(HFONT)SelectObject(hDC, hFont);

	SetTextColor(hDC, RGB(255, 255, 255));

	swprintf_s(szBuff, L"%d", m_pTarget->Get_Hp());
	TextOut(hDC, (int)m_tInfo.fX - 60, m_tInfo.fY - 8, szBuff, lstrlen(szBuff));

	swprintf_s(szBuff, L"/");
	TextOut(hDC, (int)m_tInfo.fX - 30, m_tInfo.fY - 8, szBuff, lstrlen(szBuff));

	swprintf_s(szBuff, L"%d", m_pTarget->Get_Status().m_iMaxHp);
	TextOut(hDC, (int)m_tInfo.fX, m_tInfo.fY - 8, szBuff, lstrlen(szBuff));

	DeleteObject(hFont);

	GdiTransparentBlt(hDC,
		(int)m_tManaRect.left,
		(int)m_tManaRect.top,
		m_tManaInfo.fCX,
		m_tManaInfo.fCY,
		hManaFrame_DC,
		0,
		0,
		m_tManaInfo.fCX,
		m_tManaInfo.fCY,
		RGB(255, 0, 255));

	GdiTransparentBlt(hDC,
		(int)m_tManaRect.left + 18,
		(int)m_tManaRect.top + 22,
		70,
		69,
		hManaEmptyDC,
		0,
		0,
		70,
		69,
		RGB(255, 0, 255));


//	float fPlayerHp = m_pTarget->Get_Status().m_iMaxHp;
//	float fPlayerHpRatio = (static_cast<float>(m_pTarget->Get_Hp()) / fPlayerHp);

	float fPlayerMp = CObjMgr::Get_Instance()->Get_Player()->Get_Status().m_iMaxMp;
	float fPlayerMpRatio = (static_cast<float>(CObjMgr::Get_Instance()->Get_Player()->Get_Status().m_iMp) / fPlayerMp);

	GdiTransparentBlt(hDC,
		(int)m_tManaRect.left + 18,
		(int)m_tManaRect.top + 22,
		70,
		69 * fPlayerMpRatio,
		hManaDC,
		0,
		0,
		70,
		69 * fPlayerMpRatio,
		RGB(255, 0, 255));

	

	hFont = CreateFont(14, 0, 0, 0, 0, 0, 0, 0, HANGUL_CHARSET, 0, 0, 0, VARIABLE_PITCH || FF_ROMAN, TEXT("PFStardust"));
	(HFONT)SelectObject(hDC, hFont);

	SetTextColor(hDC, RGB(255, 255, 255));

	swprintf_s(szBuff, L"%d", CObjMgr::Get_Instance()->Get_Player()->Get_Status().m_iMp);
	TextOut(hDC, (int)m_tManaInfo.fX - 20, m_tManaInfo.fY - 20, szBuff, lstrlen(szBuff));

	swprintf_s(szBuff, L"£þ£þ£þ£þ");
	TextOut(hDC, (int)m_tManaInfo.fX - 25, m_tManaInfo.fY, szBuff, lstrlen(szBuff));

	swprintf_s(szBuff, L"%.0f", fPlayerMp);
	TextOut(hDC, (int)m_tManaInfo.fX - 20, m_tManaInfo.fY + 10, szBuff, lstrlen(szBuff));

	DeleteObject(hFont);

}

void CPlayerHp::Release(void)
{
	KillTimer(g_hWnd, 1);
	
}

void CPlayerHp::Setting_Img()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/UI/Player/HP_Frame.bmp", L"HP_Frame");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/UI/Player/HP_Bar.bmp", L"HP_Bar");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/UI/Scene/Tanker_Icon.bmp", L"Tanker_Icon");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/UI/Scene/Buseker_Icon.bmp", L"Buseker_Icon");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/UI/Scene/Healer_Icon.bmp", L"Healer_Icon");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/UI/Scene/Ranger_Icon.bmp", L"Ranger_Icon");
	
	CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/UI/Scene/Player_Select_Frame.bmp", L"Player_Select_Frame");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/UI/Player/Player_Casting_Frame.bmp", L"Player_Casting_Frame");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/UI/Player/Player_Casting_ProgressBar.bmp", L"Player_Casting_ProgressBar");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/UI/Player/ManaImage1.bmp",	   L"ManaImage");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/UI/Player/Empty_Mana1.bmp",	   L"Empty_Mana");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/UI/Player/ManaImage_Empty1.bmp", L"ManaImage_Empty");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/UI/Player/Name_Plate.bmp", L"Name_Plate");
}

void CPlayerHp::Update_HpBarRect()
{
	m_tHpBarRect.left = LONG(m_tHpBarInfo.fX - (m_tHpBarInfo.fCX * 0.5f));
	m_tHpBarRect.top = LONG(m_tHpBarInfo.fY - (m_tHpBarInfo.fCY * 0.5f));
	m_tHpBarRect.right = LONG(m_tHpBarInfo.fX + (m_tHpBarInfo.fCX * 0.5f));
	m_tHpBarRect.bottom = LONG(m_tHpBarInfo.fY + (m_tHpBarInfo.fCY * 0.5f));
}

void CPlayerHp::Update_SelectFrameRect()
{
	m_tSelectFrameRect.left = LONG(m_tSelectFrameInfo.fX - (m_tSelectFrameInfo.fCX * 0.5f));
	m_tSelectFrameRect.top = LONG(m_tSelectFrameInfo.fY - (m_tSelectFrameInfo.fCY * 0.5f));
	m_tSelectFrameRect.right = LONG(m_tSelectFrameInfo.fX + (m_tSelectFrameInfo.fCX * 0.5f));
	m_tSelectFrameRect.bottom = LONG(m_tSelectFrameInfo.fY + (m_tSelectFrameInfo.fCY * 0.5f));
}

void CPlayerHp::Update_IconRect()
{
	m_tIconRect.left = LONG(m_tIconInfo.fX - (m_tIconInfo.fCX * 0.5f));
	m_tIconRect.top = LONG(m_tIconInfo.fY - (m_tIconInfo.fCY * 0.5f));
	m_tIconRect.right = LONG(m_tIconInfo.fX + (m_tIconInfo.fCX * 0.5f));
	m_tIconRect.bottom = LONG(m_tIconInfo.fY + (m_tIconInfo.fCY * 0.5f));
}

void CPlayerHp::Update_CastingProRect()
{
}

void CPlayerHp::Update_ManaRect()
{
	m_tManaRect.left = LONG(m_tManaInfo.fX - (m_tManaInfo.fCX * 0.5f));
	m_tManaRect.top = LONG(m_tManaInfo.fY - (m_tManaInfo.fCY * 0.5f));
	m_tManaRect.right = LONG(m_tManaInfo.fX + (m_tManaInfo.fCX * 0.5f));
	m_tManaRect.bottom = LONG(m_tManaInfo.fY + (m_tManaInfo.fCY * 0.5f));
}




