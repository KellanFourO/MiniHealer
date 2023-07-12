
#include "Obj.h"
#include "ObjMgr.h"


CObj::CObj() : m_fSpeed(0.f), m_eDir(DIR_END),m_pFrameKey(L""), m_eRender(RENDER_END),m_iStart(0),m_bStartSwitch(false),m_bEndSwitch(false),m_iEnd(0),m_bDead(false), m_eUI(UI_CLOSE),m_bLateDead(false)
{
	ZeroMemory(&m_tInfo, sizeof(m_tInfo));
	ZeroMemory(&m_tRect, sizeof(m_tRect));
	ZeroMemory(&m_tFrame, sizeof(m_tFrame));

	ZeroMemory(&m_tWeaponInfo, sizeof(INFO));
	ZeroMemory(&m_tWeaponRect, sizeof(RECT));
}

CObj::~CObj()
{
}

void CObj::Update_Rect()
{
	m_tRect.left = LONG(m_tInfo.fX - (m_tInfo.fCX * 0.5f)); 
	m_tRect.top = LONG(m_tInfo.fY - (m_tInfo.fCY * 0.5f));
	m_tRect.right = LONG(m_tInfo.fX + (m_tInfo.fCX * 0.5f));
	m_tRect.bottom = LONG(m_tInfo.fY + (m_tInfo.fCY * 0.5f));
}

void CObj::Update_WeaponRect()
{
	m_tWeaponRect.left = LONG(m_tWeaponInfo.fX - (m_tWeaponInfo.fCX * 0.5f));
	m_tWeaponRect.top = LONG(m_tWeaponInfo.fY - (m_tWeaponInfo.fCY * 0.5f));
	m_tWeaponRect.right = LONG(m_tWeaponInfo.fX + (m_tWeaponInfo.fCX * 0.5f));
	m_tWeaponRect.bottom = LONG(m_tWeaponInfo.fY + (m_tWeaponInfo.fCY * 0.5f));
}

void CObj::Move_Frame()
{
	if (m_tFrame.dwTime + m_tFrame.dwSpeed < GetTickCount64())
	{
		if (m_eDir == RIGHT)
		{
			++m_tFrame.iFrameStart;
			if (m_tFrame.iFrameStart > m_tFrame.iFrameEnd)
				m_tFrame.iFrameStart = 0;
		}
		else if(m_eDir == LEFT)
		{
			--m_tFrame.iFrameStart;
			if (m_tFrame.iFrameStart < m_tFrame.iFrameEnd)
				m_tFrame.iFrameStart = m_iStart;
		}
		
		m_tFrame.dwTime = GetTickCount64();
	}
}
