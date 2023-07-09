#include "Door.h"
#include "BmpMgr.h"
#include "SceneMgr.h"

CDoor::CDoor():m_iDoorStart(0),m_iDoorEnd(0),m_dwDoorDelay(GetTickCount64())
{
}

CDoor::~CDoor()
{
}

void CDoor::Initialize(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/BackGround/MainDoor.bmp", L"MainDoor");
	m_iDoorStart = 0;
	m_iDoorEnd = 8;
	
	m_eRender = GAMEOBJECT;
}

int CDoor::Update(void)
{
	return OBJ_NOEVENT;
}

void CDoor::Late_Update(void)
{
	if (Get_Start())
	{
		if (m_iDoorStart < 9 && m_dwDoorDelay + 200 < GetTickCount64())
		{
			++m_iDoorStart;
			m_dwDoorDelay = GetTickCount64();
			
		}

		
	}
	
	if (m_iDoorStart == 9)
	{
		m_bStartSwitch = false;
		m_bEndSwitch = true;
	}

	
		

}

void CDoor::Render(HDC hDC)
{
	HDC     hDoorDC = CBmpMgr::Get_Instance()->Find_Img(L"MainDoor");
	GdiTransparentBlt(hDC,
		1000, // 복사 받을 위치 X,Y 좌표
		160,
		250,	// 복사 받을 가로, 세로 길이
		550,
		hDoorDC,			// 비트맵 이미지를 담고 있는 DC
		m_iDoorStart * 243,					// 비트맵을 출력할 시작 X,Y좌표
		0,
		268,		// 출력할 비트맵의 가로, 세로 사이즈
		659,
		RGB(255, 0, 255)); // 제거하고자 하는 색상
}

void CDoor::Release(void)
{
}

void CDoor::Setting_Img()
{
}
