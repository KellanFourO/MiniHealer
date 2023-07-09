#include "framework.h"
#include "MyEdit.h"
#include "KeyMgr.h"
#include "ScrollMgr.h"

CMyEdit::CMyEdit()
{
}

CMyEdit::~CMyEdit()
{
	Release();
}

void CMyEdit::Initialize()
{

}

void CMyEdit::Update()
{
	Key_Input();


}

void CMyEdit::Late_Update()
{

}

void CMyEdit::Render(HDC hDC)
{

}

void CMyEdit::Release()
{
}

void CMyEdit::Key_Input(void)
{
	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_LEFT))
		CScrollMgr::Get_Instance()->Set_ScrollX(5.f);

	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_RIGHT))
		CScrollMgr::Get_Instance()->Set_ScrollX(-5.f);

	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_UP))
		CScrollMgr::Get_Instance()->Set_ScrollY(5.f);

	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_DOWN))
		CScrollMgr::Get_Instance()->Set_ScrollY(-5.f);

	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_LBUTTON))
	{
		POINT	pt;
		GetCursorPos(&pt);
		ScreenToClient(g_hWnd, &pt);

		pt.x -= (int)CScrollMgr::Get_Instance()->Get_ScollX();
		pt.y -= (int)CScrollMgr::Get_Instance()->Get_ScollY();


	}



}
