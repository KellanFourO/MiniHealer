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
		1000, // ���� ���� ��ġ X,Y ��ǥ
		160,
		250,	// ���� ���� ����, ���� ����
		550,
		hDoorDC,			// ��Ʈ�� �̹����� ��� �ִ� DC
		m_iDoorStart * 243,					// ��Ʈ���� ����� ���� X,Y��ǥ
		0,
		268,		// ����� ��Ʈ���� ����, ���� ������
		659,
		RGB(255, 0, 255)); // �����ϰ��� �ϴ� ����
}

void CDoor::Release(void)
{
}

void CDoor::Setting_Img()
{
}
