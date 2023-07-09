#include "Inventory.h"
#include "BmpMgr.h"

CInventory::CInventory():m_bInvenStart(true)
{
	ZeroMemory(&m_tExitRect, sizeof(RECT));
	ZeroMemory(&m_tExitInfo, sizeof(INFO));
}

CInventory::~CInventory()
{
}

void CInventory::Initialize(void)
{
	m_tInfo.fCX = 550.f;
	m_tInfo.fCY = 900.f;
	m_tInfo.fX = WINCX / 2;
	m_tInfo.fY = WINCY / 2;

	m_tExitInfo.fCX = 81.f;
	m_tExitInfo.fCY = 81.f;
		

	
}

int CInventory::Update(void)
{
	if (m_bInvenStart) // 한번만 실행하기위함.
	{
		m_tExitInfo.fX = m_tRect.left + 50;
		m_tExitInfo.fY = m_tRect.top + 50;
		UpdateExitRect();

		m_bInvenStart = false;
	}
	
	return 0;
}

void CInventory::Late_Update(void)
{
}

void CInventory::Render(HDC hDC)
{
}

void CInventory::Release(void)
{
}

void CInventory::Setting_Img()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/UI/Public/Inventory.bmp", L"Inventory");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/UI/Public/Item_Frame.bmp", L"Item_Frame");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/UI/Public/Public_Disabled.bmp", L"Public_Disabled");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/UI/Public/ItemTitle.bmp", L"ItemTitle");
}

void CInventory::EquipItem()
{
}

void CInventory::UnEquipItem()
{
}

void CInventory::UpdateExitRect()
{
}
