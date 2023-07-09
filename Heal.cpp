#include "Heal.h"
#include "KeyMgr.h"
#include "ObjMgr.h"
#include "BmpMgr.h"
#include "Player.h"
#include "SceneMgr.h"
CHeal::CHeal():m_fHealAmount(0)
{
	ZeroMemory(&m_tFrameRect, sizeof(RECT));
	ZeroMemory(&m_tFrameInfo, sizeof(INFO));
}

CHeal::~CHeal()
{
}


void CHeal::Initialize(void)
{
	m_tInfo.fCX = 31.f;
	m_tInfo.fCY = 31.f;
	m_iSkillNumber = '1'; // 정수형 변수에 문자형 데이터를 넣어 아스키코드변환
	
	
	m_fCastingTime = 1230;
	m_fCoolTime = 0.10f;
	m_iMana = 100;
	
	m_fHealAmount = 200;

	
	m_tFrameInfo.fCX = 40.f;
	m_tFrameInfo.fCY = 40.f;
	
	
	m_bStartSwitch = true;
	m_eRender = GAMEOBJECT;
	Setting_Img();
}

int CHeal::Update(void)
{
	if (CSceneMgr::Get_Instance()->Get_SceneID() == SC_FIELD)
	{
		if (m_bStartSwitch)
		{
			Start_SkillTarget();
			
		}
		
		if (CKeyMgr::Get_Instance()->Key_Down((char)m_iSkillNumber) && dynamic_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->GetMana() >= m_iMana)
		{
			if (m_ulCastingDelay + m_fCastingTime < GetTickCount64())
			{
				Active_Skill();
				m_ulCastingDelay = GetTickCount64();
			}
		}
	}

	
	__super::Update_Rect();
	Update_FrameRect();


	return OBJ_NOEVENT;
}

void CHeal::Late_Update(void)
{
}

void CHeal::Render(HDC hDC)
{
	if (CSceneMgr::Get_Instance()->Get_SceneID() == SC_FIELD)
	{
		HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Img(L"Heal");
		HDC		hFrame_DC = CBmpMgr::Get_Instance()->Find_Img(L"Skill_Frame");

		GdiTransparentBlt(hDC,
			(int)m_tFrameRect.left- 3, // 복사 받을 위치 X,Y 좌표
			(int)m_tFrameRect.top - 3,
			(int)m_tFrameInfo.fCX + 7,	// 복사 받을 가로, 세로 길이
			(int)m_tFrameInfo.fCY + 7,
			hFrame_DC,			// 비트맵 이미지를 담고 있는 DC
			0,					// 비트맵을 출력할 시작 X,Y좌표
			0,
			(int)m_tFrameInfo.fCX,		// 출력할 비트맵의 가로, 세로 사이즈
			(int)m_tFrameInfo.fCY,
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

		TCHAR szBuff[32] = L"";

		HFONT hFont = CreateFont(13, 0, 0, 0, 0, 0, 0, 0, HANGUL_CHARSET, 0, 0, 0, VARIABLE_PITCH || FF_ROMAN, TEXT("PFStardust"));
		(HFONT)SelectObject(hDC, hFont);

		SetTextColor(hDC, RGB(255, 255, 255));

		swprintf_s(szBuff, L"%c", m_iSkillNumber);
		TextOut(hDC, (int)m_tInfo.fX - 3, m_tInfo.fY + 22, szBuff, lstrlen(szBuff));

		DeleteObject(hFont);
	}
}

void CHeal::Release(void)
{
}

void CHeal::Setting_Img()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/Icon/Heal.bmp", L"Heal");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/UI/Public/Skill_Frame.bmp", L"Skill_Frame");
}

void CHeal::Active_Skill()
{
	if (m_pSkillTarget->Get_Hp() + m_fHealAmount > m_pSkillTarget->Get_MaxHp())
	{
		m_pSkillTarget->Set_HpInit(m_pSkillTarget->Get_MaxHp());
	}
	else
	m_pSkillTarget->Set_Hp(m_fHealAmount);

	dynamic_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->SetMana(-m_iMana);
		
}

void CHeal::Start_SkillTarget()
{
	m_pSkillTarget = CObjMgr::Get_Instance()->Get_Tanker();
	m_bStartSwitch = false;
}

void CHeal::Update_FrameRect()
{
	m_tFrameInfo.fX = m_tInfo.fX;
	m_tFrameInfo.fY = m_tInfo.fY;
	m_tFrameRect.left = LONG(m_tFrameInfo.fX - (m_tFrameInfo.fCX * 0.5f));
	m_tFrameRect.top = LONG(m_tFrameInfo.fY - (m_tFrameInfo.fCY * 0.5f));
	m_tFrameRect.right = LONG(m_tFrameInfo.fX + (m_tFrameInfo.fCX * 0.5f));
	m_tFrameRect.bottom = LONG(m_tFrameInfo.fY + (m_tFrameInfo.fCY * 0.5f));
}
