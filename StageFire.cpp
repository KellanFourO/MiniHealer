#include "StageFire.h"
#include "StageFire.h"
#include "BmpMgr.h"

CStageFire::CStageFire():m_iStageFireStart(0), m_iStageFireEnd(0), m_dwStageFireDelay(GetTickCount64())
{
}

CStageFire::~CStageFire()
{
	Release();
}

void CStageFire::Initialize(void)
{
	m_tInfo.fCX = 55.f;
	m_tInfo.fCY = 105.f;
	Setting_Img();
	m_eRender = UI;

	m_iStageFireStart = 0;
	m_iStageFireEnd = 7;
}

int CStageFire::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	if (m_dwStageFireDelay + 150 < GetTickCount64())
	{
		++m_iStageFireStart;
		m_dwStageFireDelay = GetTickCount64();
	}

	if (m_iStageFireStart == m_iStageFireEnd)
		m_iStageFireStart = 0;

	
	__super::Update_Rect();

	return OBJ_NOEVENT;
}

void CStageFire::Late_Update(void)
{
}

void CStageFire::Render(HDC hDC)
{
	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Img(L"FirePlace");

	GdiTransparentBlt(hDC,
		m_tRect.left,
		m_tRect.top,
		55,
		105,
		hMemDC,
		m_iStageFireStart * 120,
		0,
		120,
		180,
		RGB(255, 0, 255));
}

void CStageFire::Release(void)
{
}

void CStageFire::Setting_Img()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/BackGround/FirePlace.bmp", L"FirePlace");
}
