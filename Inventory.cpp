#include "Inventory.h"
#include "BmpMgr.h"

#include "AbstractFactory.h"
#include "BasicStaff.h"
#include "KeyMgr.h"
#include "CollisionMgr.h"
#include "ObjMgr.h"

CInventory::CInventory():m_bInvenStart(true),m_iSize(4),m_fHeight(0),m_iEquipSize(2),
ClickItem(nullptr), ClickIndexI(0), ClickIndexJ(0),m_pSwapObj(nullptr)
{
	ZeroMemory(&m_tEquipRect, sizeof(RECT));
	ZeroMemory(&m_tEquipInfo, sizeof(INFO));
	ZeroMemory(&m_pDragStart, sizeof(POINT));

	
	
}

CInventory::~CInventory()
{
}

void CInventory::Initialize(void)
{
	m_tInfo.fCX = 440.f;
	m_tInfo.fCY = 720.f;
	m_tInfo.fX = WINCX / 2 - 300;
	m_tInfo.fY = WINCY / 2;

	m_tEquipInfo.fCX = 275.f;
	m_tEquipInfo.fCY = 450.f;
	m_tEquipInfo.fX = WINCX / 2 + 50;
	m_tEquipInfo.fY = WINCY / 2 - 50;

	m_tStatInfo.fCX = 396.f;
	m_tStatInfo.fCY = 648.f;
	m_tStatInfo.fX = WINCX / 2 + 380;
	m_tStatInfo.fY = WINCY / 2 + 48;

	
	
	m_fDistance = 70.f;
	m_fHeight = 100.f;

	__super::Update_Rect();
	Update_EquipRect();
	Update_StatRect();

	m_eRender = UI;
	Setting_Img();

	UnEquip_Add_Initialize();
	
	
	
	CItem* pObj = new CBasicStaff;
	
	Get_Item(pObj);
}

int CInventory::Update(void)
{


	Mouse_Event();

	if (m_bInvenStart) // 한번만 실행하기위함.
	{
		m_bInvenStart = false;
	}
	

	
	CObjMgr::Get_Instance()->Update();

	__super::Update_Rect();

	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			m_vecUnEquipInventory[i][j]->Update();
		}
	}

	return OBJ_NOEVENT;
}

void CInventory::Late_Update(void)
{
	CObjMgr::Get_Instance()->Late_Update();

}

void CInventory::Render(HDC hDC)
{
	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Img(L"Inventory");
	HDC		hEquipDC = CBmpMgr::Get_Instance()->Find_Img(L"Inventory_Small");
	HDC		hStatDC = CBmpMgr::Get_Instance()->Find_Img(L"Inventory_Medium");
	HDC		hFrameDC = CBmpMgr::Get_Instance()->Find_Img(L"Item_Frame");
	
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

	GdiTransparentBlt(hDC,
		(int)m_tEquipRect.left, // 복사 받을 위치 X,Y 좌표
		(int)m_tEquipRect.top,
		(int)m_tEquipInfo.fCX,	// 복사 받을 가로, 세로 길이
		(int)m_tEquipInfo.fCY,
		hEquipDC,			// 비트맵 이미지를 담고 있는 DC
		0,					// 비트맵을 출력할 시작 X,Y좌표
		0,
		(int)m_tEquipInfo.fCX,		// 출력할 비트맵의 가로, 세로 사이즈
		(int)m_tEquipInfo.fCY,
		RGB(255, 0, 255)); // 제거하고자 하는 색상

	GdiTransparentBlt(hDC,
		(int)m_tStatRect.left, // 복사 받을 위치 X,Y 좌표
		(int)m_tStatRect.top,
		(int)m_tStatInfo.fCX,	// 복사 받을 가로, 세로 길이
		(int)m_tStatInfo.fCY,
		hStatDC,			// 비트맵 이미지를 담고 있는 DC
		0,					// 비트맵을 출력할 시작 X,Y좌표
		0,
		(int)m_tStatInfo.fCX,		// 출력할 비트맵의 가로, 세로 사이즈
		(int)m_tStatInfo.fCY,
		RGB(255, 0, 255)); // 제거하고자 하는 색상


	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			m_vecUnEquipInventory[i][j]->Render(hDC);
		}
	}
	
	//CObjMgr::Get_Instance()->Render(hDC);
}

void CInventory::Release(void)
{
}

void CInventory::Setting_Img()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/UI/Public/Inventory1.bmp", L"Inventory");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/UI/Public/Inventory2.bmp", L"Inventory_Medium");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/UI/Public/Inventory_Small.bmp", L"Inventory_Small");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/UI/Public/ItemTitle.bmp", L"ItemTitle");
}

void CInventory::EquipItem()
{

}

void CInventory::UnEquipItem()
{
}

void CInventory::IsFull_Item(CObj* _Item)
{
}

void CInventory::IsSell_Item(int _iInput, int* pMoney)
{
}

void CInventory::Get_Item(CItem* _Item)
{

	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			if (m_vecUnEquipInventory[i][j]->Get_ItemName() == "")
			{
				_Item->Initialize();
				_Item->Set_FramePos(m_vecUnEquipInventory[i][j]->Get_FrameInfo().fX, m_vecUnEquipInventory[i][j]->Get_FrameInfo().fY);
				_Item->Set_Pos(m_vecUnEquipInventory[i][j]->Get_FrameInfo().fX, m_vecUnEquipInventory[i][j]->Get_FrameInfo().fY);
				_Item->Update();
				m_vecUnEquipInventory[i][j] = _Item;
				return;
			}
		}
	}

}



void CInventory::Mouse_Event()
{
	POINT	pt{};
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);
	
	

	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			if (PtInRect(&m_vecUnEquipInventory[i][j]->Get_Rect(), pt))
			{
				if (!ClickItem)  // 클릭한 아이템이 없을때
				{
					if (CKeyMgr::Get_Instance()->Key_Down(VK_LBUTTON))
					{
						ClickItem = m_vecUnEquipInventory[i][j];
						m_vecUnEquipInventory[i][j]->Set_ItemDrag(true);
						ClickIndexI = i;
						ClickIndexJ = j;
						m_pDragStart = pt;
					}
				}


				else // 클릭한 아이템이 있을 때, 드래그 중일 때
				{
					if (ClickItem == m_vecUnEquipInventory[i][j])
						continue;

					if (PtInRect(&m_vecUnEquipInventory[i][j]->Get_Rect(), pt))
					{
						if (CKeyMgr::Get_Instance()->Key_Down(VK_LBUTTON))
						{
							
							float ClickPreX = ClickItem->Get_PrePosX();
							float ClickPreY = ClickItem->Get_PrePosY();
							
							float Test = m_vecUnEquipInventory[i][j]->Get_PrePosX();
							float Test2 = m_vecUnEquipInventory[i][j]->Get_PrePosY();
							

							ClickItem->Set_Pos(m_vecUnEquipInventory[i][j]->Get_PrePosX(),
										       m_vecUnEquipInventory[i][j]->Get_PrePosY());

							m_vecUnEquipInventory[i][j]->Set_Pos(ClickPreX, ClickPreY);
																
							m_vecUnEquipInventory[i][j]->Set_Name("테스트");
							int iTempnum = m_vecUnEquipInventory[i][j]->Get_Number();
							m_vecUnEquipInventory[i][j]->Set_Number(ClickItem->Get_Number());
							ClickItem->Set_Number(iTempnum);


							ClickItem->Set_ItemDrag(false);
						}
					}
				}
			}
		}
	}


	//for (int i = 0; i < 4; ++i)
	//{
	//	for (int j = 0; j < 4; ++j)
	//	{
	//		if (PtInRect(&m_vecUnEquipItems[i][j]->Get_Rect(), pt)) 
	//		{
	//			if(!ClickItem) // 클릭한 아이템이 없을때
	//			{
	//			if (CKeyMgr::Get_Instance()->Key_Down(VK_LBUTTON))
	//				{
	//					dynamic_cast<CItem*>(m_vecUnEquipItems[i][j])->Set_ItemDrag(true);
	//					ClickItem = m_vecUnEquipItems[i][j];
	//					ClickIndexI = i, ClickIndexJ = j;
	//					m_pDragStart = pt;
	//				}
	//			}

	//			else // 클릭한 아이템이 있을 때
	//			{
	//				if (ClickItem == m_vecUnEquipItems[i][j])
	//					continue;
	//				
	//				float fX = ClickItem->Get_Info().fX;
	//				float fY = ClickItem->Get_Info().fY;

	//				if (CCollisionMgr::Check_Rect(ClickItem, m_vecUnEquipItems[i][j], &fX, &fY))
	//				{
	//					// 클릭한 아이템이 다른 아이템과 충돌했을 때
	//					if (CKeyMgr::Get_Instance()->Key_Down(VK_LBUTTON))
	//					{
	//						// 다른 아이템과 충돌하고 클릭했을 때
	//						dynamic_cast<CItem*>(ClickItem)->Set_FramePos(dynamic_cast<CItem*>(m_vecUnEquipItems[i][j])->Get_PrePosX(), dynamic_cast<CItem*>(m_vecUnEquipItems[i][j])->Get_PrePosY());

	//						dynamic_cast<CItem*>(m_vecUnEquipItems[i][j])->Set_FramePos(dynamic_cast<CItem*>(ClickItem)->Get_PrePosX(), dynamic_cast<CItem*>(ClickItem)->Get_PrePosY());

	//						//swap(ClickItem, m_vecUnEquipItems[i][j]);

	//						m_pSwapObj = ClickItem;
	//						ClickItem = m_vecUnEquipI0tems[i][j];
	//						m_vecUnEquipItems[i][j] = m_pSwapObj;
	//						m_pSwapObj = nullptr;

	//						
	//						dynamic_cast<CItem*>(m_vecUnEquipItems[i][j])->Set_ItemDrag(false);
	//					}
	//				}

	//			}
	//		}
	//	}
	//}
	//

}

bool CInventory::Maching_Item(CObj* _Item, CObj* _Click)
{
	if (CCollisionMgr::AABB_Collision(_Click, _Item))
	{
		
	}

	return false;
}

void CInventory::Swap_Item(vector<CObj*>& _Inventory, int iIndex1, int iIndex2)
{
	swap(_Inventory[iIndex1], _Inventory[iIndex2]);
}

void CInventory::Update_EquipRect()
{
	m_tEquipRect.left = LONG(m_tEquipInfo.fX - (m_tEquipInfo.fCX * 0.5f));
	m_tEquipRect.top = LONG(m_tEquipInfo.fY - (m_tEquipInfo.fCY * 0.5f));
	m_tEquipRect.right = LONG(m_tEquipInfo.fX + (m_tEquipInfo.fCX * 0.5f));
	m_tEquipRect.bottom = LONG(m_tEquipInfo.fY + (m_tEquipInfo.fCY * 0.5f));
}

void CInventory::Update_StatRect()
{
	m_tStatRect.left = LONG(m_tStatInfo.fX - (m_tStatInfo.fCX * 0.5f));
	m_tStatRect.top = LONG(m_tStatInfo.fY - (m_tStatInfo.fCY * 0.5f));
	m_tStatRect.right = LONG(m_tStatInfo.fX + (m_tStatInfo.fCX * 0.5f));
	m_tStatRect.bottom = LONG(m_tStatInfo.fY + (m_tStatInfo.fCY * 0.5f));
}


void CInventory::UnEquip_Add_Initialize()
{
	m_vecUnEquipInventory[0].reserve(m_iSize);
	m_vecUnEquipInventory[1].reserve(m_iSize);
	m_vecUnEquipInventory[2].reserve(m_iSize);
	m_vecUnEquipInventory[3].reserve(m_iSize);

	for (int i = 0; i < 4; ++i)
	{
		m_vecUnEquipInventory[0].push_back(new CItem);
		m_vecUnEquipInventory[0].back()->Initialize();

		m_vecUnEquipInventory[1].push_back(new CItem);
		m_vecUnEquipInventory[1].back()->Initialize();

		m_vecUnEquipInventory[2].push_back(new CItem);
		m_vecUnEquipInventory[2].back()->Initialize();

		m_vecUnEquipInventory[3].push_back(new CItem);
		m_vecUnEquipInventory[3].back()->Initialize();
	}

	int TempNumber = 1;

	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			if (m_vecUnEquipInventory[i][j])
			{
				m_vecUnEquipInventory[i][j]->Initialize();
				m_vecUnEquipInventory[i][j]->Set_FramePos(m_tRect.left + m_fDistance, m_tRect.top + m_fHeight);
				m_vecUnEquipInventory[i][j]->Set_Pos(m_tRect.left + m_fDistance, m_tRect.top + m_fHeight);
				m_vecUnEquipInventory[i][j]->Set_Number(TempNumber);
				++TempNumber;
			}
			m_fDistance += 100;
		}
		m_fDistance = 70.f;
		m_fHeight += 100.f;
	}

	m_fHeight = 100.f;

	// 인벤토리가 가득 찬 경우 처리하는 로직을 추가할 수 있습니다.
}


