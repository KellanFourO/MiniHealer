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
			(int)m_tRect.left, // ���� ���� ��ġ X,Y ��ǥ
			(int)m_tRect.top,
			(int)m_tInfo.fCX,	// ���� ���� ����, ���� ����
			(int)m_tInfo.fCY,
			hMemDC,			// ��Ʈ�� �̹����� ��� �ִ� DC
			0,					// ��Ʈ���� ����� ���� X,Y��ǥ
			m_iDrawID * (int)m_tInfo.fCY,
			(int)m_tInfo.fCX,		// ����� ��Ʈ���� ����, ���� ������
			(int)m_tInfo.fCY,
			RGB(255, 0, 255)); // �����ϰ��� �ϴ� ����

	
		
		
		

	
}

void CMyButton::Release(void)
{
	
}

void CMyButton::Setting_Img()
{
}

