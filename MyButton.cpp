#include "framework.h"
#include "MyButton.h"
#include "BmpMgr.h"
#include "KeyMgr.h"
#include "SceneMgr.h"
#include "ObjMgr.h"
#include "SelectDoor.h"

CMyButton::CMyButton() : m_iDrawID(0)
{
}

CMyButton::~CMyButton()
{
	Release();
}

void CMyButton::Initialize(void)
{
	m_tInfo.fCX = 120.f;
	m_tInfo.fCY = 70.f;

	
	m_eRender = UI;
}

int CMyButton::Update(void)
{

	__super::Update_Rect();

	return OBJ_NOEVENT;
}

void CMyButton::Late_Update(void)
{

	POINT	pt{};
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);

	if (PtInRect(&m_tRect, pt))
	{
		
		if (CKeyMgr::Get_Instance()->Key_Down(VK_LBUTTON))
		{

			if (!lstrcmp(L"Title_Start", m_pFrameKey))
			{
				m_bStartSwitch = true;
				CObjMgr::Get_Instance()->Get_Objects(DOOR).front()->Set_Start(true);

				CObjMgr::Get_Instance()->Get_Player()->Set_Start(true);
				CObjMgr::Get_Instance()->Get_Berserker()->Set_Start(true);
				CObjMgr::Get_Instance()->Get_Ranger()->Set_Start(true);
				CObjMgr::Get_Instance()->Get_Tanker()->Set_Start(true);


			}

			else if (!lstrcmp(L"Title_Setting", m_pFrameKey))
				CSceneMgr::Get_Instance()->Scene_Change(SC_EDIT);


			else if (!lstrcmp(L"LobbyArmory", m_pFrameKey))
			{
				CSceneMgr::Get_Instance()->Get_Lobby()->Set_OpenUI(true);
				CSceneMgr::Get_Instance()->Get_Lobby()->Set_OpenArmory(true);
			}
				
			
			else if (!lstrcmp(L"LobbySkill", m_pFrameKey))
				CSceneMgr::Get_Instance()->Scene_Change(SC_MAP);

			else if (!lstrcmp(L"LobbyAbility", m_pFrameKey))
				CSceneMgr::Get_Instance()->Scene_Change(SC_MAP);

			else if (!lstrcmp(L"LobbyDoor", m_pFrameKey))
			{
				CSceneMgr::Get_Instance()->Get_Lobby()->Set_OpenUI(true);
				CSceneMgr::Get_Instance()->Get_Lobby()->Set_OpenMap(true);
			}
			
			else if (!lstrcmp(L"LobbyPartyInfo", m_pFrameKey))
				CSceneMgr::Get_Instance()->Scene_Change(SC_MAP);

			else
				DestroyWindow(g_hWnd);

			return;
		}
		
		if(CSceneMgr::Get_Instance()->Get_SceneID() != SC_STAGE)
		m_iDrawID = 1;
	}
	else
		m_iDrawID = 0;


}


void CMyButton::Render(HDC hDC)
{
	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Img(m_pFrameKey);
	 
	
		GdiTransparentBlt(hDC,
			(int)m_tRect.left, // 복사 받을 위치 X,Y 좌표
			(int)m_tRect.top,
			(int)m_tInfo.fCX,	// 복사 받을 가로, 세로 길이
			(int)m_tInfo.fCY,
			hMemDC,			// 비트맵 이미지를 담고 있는 DC
			0,					// 비트맵을 출력할 시작 X,Y좌표
			m_iDrawID * (int)m_tInfo.fCY,
			(int)m_tInfo.fCX,		// 출력할 비트맵의 가로, 세로 사이즈
			(int)m_tInfo.fCY,
			RGB(255, 0, 255)); // 제거하고자 하는 색상

	
		
		
		

	
}

void CMyButton::Release(void)
{
	
}

void CMyButton::Setting_Img()
{
}

