#include "Inventory.h"
#include "BmpMgr.h"

#include "AbstractFactory.h"
#include "BasicStaff.h"
#include "KeyMgr.h"
#include "CollisionMgr.h"
#include "ObjMgr.h"
#include "Player.h"

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
	Equip_Add_Initialize();
	
	
	CItem* pObj = new CBasicStaff;
	
	Get_Item(pObj);
}

int CInventory::Update(void)
{


	Mouse_Event();

	if (ClickItem)
	{
		Equip_Event();
	}

	if (m_bInvenStart) // �ѹ��� �����ϱ�����.
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

	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 2; ++j)
		{
			m_vecEquipInventory[i][j]->Update();
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
		(int)m_tRect.left, // ���� ���� ��ġ X,Y ��ǥ
		(int)m_tRect.top,
		(int)m_tInfo.fCX,	// ���� ���� ����, ���� ����
		(int)m_tInfo.fCY,
		hMemDC,			// ��Ʈ�� �̹����� ��� �ִ� DC
		0,					// ��Ʈ���� ����� ���� X,Y��ǥ
		0,
		(int)m_tInfo.fCX,		// ����� ��Ʈ���� ����, ���� ������
		(int)m_tInfo.fCY,
		RGB(255, 0, 255)); // �����ϰ��� �ϴ� ����

	GdiTransparentBlt(hDC,
		(int)m_tEquipRect.left, // ���� ���� ��ġ X,Y ��ǥ
		(int)m_tEquipRect.top,
		(int)m_tEquipInfo.fCX,	// ���� ���� ����, ���� ����
		(int)m_tEquipInfo.fCY,
		hEquipDC,			// ��Ʈ�� �̹����� ��� �ִ� DC
		0,					// ��Ʈ���� ����� ���� X,Y��ǥ
		0,
		(int)m_tEquipInfo.fCX,		// ����� ��Ʈ���� ����, ���� ������
		(int)m_tEquipInfo.fCY,
		RGB(255, 0, 255)); // �����ϰ��� �ϴ� ����

	GdiTransparentBlt(hDC,
		(int)m_tStatRect.left, // ���� ���� ��ġ X,Y ��ǥ
		(int)m_tStatRect.top,
		(int)m_tStatInfo.fCX,	// ���� ���� ����, ���� ����
		(int)m_tStatInfo.fCY,
		hStatDC,			// ��Ʈ�� �̹����� ��� �ִ� DC
		0,					// ��Ʈ���� ����� ���� X,Y��ǥ
		0,
		(int)m_tStatInfo.fCX,		// ����� ��Ʈ���� ����, ���� ������
		(int)m_tStatInfo.fCY,
		RGB(255, 0, 255)); // �����ϰ��� �ϴ� ����


	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			m_vecUnEquipInventory[i][j]->Render(hDC);
		}
	}
	
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 2; ++j)
		{
			m_vecEquipInventory[i][j]->Render(hDC);
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

				if (!ClickItem)  // Ŭ���� �������� ������
				{

					if (CKeyMgr::Get_Instance()->Key_Down(VK_LBUTTON))
					{
						ClickItem = m_vecUnEquipInventory[i][j];
						m_vecUnEquipInventory[i][j]->Set_ItemDrag(true);
						ClickIndexI = i;
						ClickIndexJ = j;
						m_pDragStart.x = ClickItem->Get_FrameInfo().fX;
						m_pDragStart.y = ClickItem->Get_FrameInfo().fY;
						m_pDragInfo.x = ClickItem->Get_Info().fX;
						m_pDragInfo.y = ClickItem->Get_Info().fY;
					}

				}

					else // Ŭ���� �������� ���� ��, �巡�� ���� ��
					{

						if (ClickItem == m_vecUnEquipInventory[i][j])
							continue;

						float fX = ClickItem->Get_FrameInfo().fX;
						float fY = ClickItem->Get_FrameInfo().fY;

						if (CCollisionMgr::Check_Rect(ClickItem, m_vecUnEquipInventory[i][j], &fX, &fY))
						{



							if (CKeyMgr::Get_Instance()->Key_Down(VK_LBUTTON))
							{
								float	TempX = ClickItem->Get_PrePosX();
								float	TempY = ClickItem->Get_PrePosY();

								m_pSwapObj = ClickItem;

								ClickItem->Set_FramePos(m_vecUnEquipInventory[i][j]->Get_FrameInfo().fX, m_vecUnEquipInventory[i][j]->Get_FrameInfo().fY);
								m_vecUnEquipInventory[i][j]->Set_FramePos(m_pDragStart.x, m_pDragStart.y);
								ClickItem->Set_Pos(m_vecUnEquipInventory[i][j]->Get_Info().fX, m_vecUnEquipInventory[i][j]->Get_Info().fY);

								m_vecUnEquipInventory[ClickIndexI][ClickIndexJ] = m_vecUnEquipInventory[i][j];
								m_vecUnEquipInventory[i][j] = m_pSwapObj;

								CObj* Test = m_vecUnEquipInventory[i][j];
								CObj* Test2 = m_vecUnEquipInventory[ClickIndexI][ClickIndexJ];
								m_pSwapObj = nullptr;
								ClickItem->Set_ItemDrag(false);
								ClickItem = nullptr;
							}

						}
					}
				
			}
		}
	}

} // �Լ� ����

void CInventory::Equip_Event()
{
	POINT	pt{};
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);

		for (int i = 0; i < 3; ++i)
		{
			for (int j = 0; j < 2; ++j)
			{
				if (PtInRect(&m_vecEquipInventory[i][j]->Get_Rect(), pt))
				{
					float fX = ClickItem->Get_FrameInfo().fX;
					float fY = ClickItem->Get_FrameInfo().fY;

					if (CCollisionMgr::Check_Rect(ClickItem, m_vecEquipInventory[i][j], &fX, &fY))
					{
						if (CKeyMgr::Get_Instance()->Key_Down(VK_LBUTTON) && ClickItem->Get_ItemInfo().m_pType == m_vecEquipInventory[i][j]->Get_ItemInfo().m_pType)
						{
							Exclude_Player();

							CItem* TempObj = ClickItem;

							ClickItem->Set_FramePos(m_vecEquipInventory[i][j]->Get_FrameInfo().fX, m_vecEquipInventory[i][j]->Get_FrameInfo().fY);
							m_vecEquipInventory[i][j]->Set_FramePos(m_pDragStart.x, m_pDragStart.y);
							ClickItem->Set_Pos(m_vecEquipInventory[i][j]->Get_Info().fX, m_vecEquipInventory[i][j]->Get_Info().fY);

							m_vecUnEquipInventory[ClickIndexI][ClickIndexJ] = m_vecEquipInventory[i][j];
							m_vecEquipInventory[i][j] = TempObj;

							ClickItem = m_vecEquipInventory[i][j];
							m_vecEquipInventory[i][j] = TempObj;




							TempObj = nullptr;
							ClickItem->Set_ItemDrag(false);
							ClickItem = nullptr;

							Apply_Player();
						}
					}

				}
			}
		}
}

void CInventory::Apply_Player()
{
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 2; ++j)
		{
			if (m_vecUnEquipInventory[i][j])
			{ 
			
				if (m_vecEquipInventory[i][j]->Get_ItemName() == "������")
				{
					CObjMgr::Get_Instance()->Get_Player()->Set_Attack(m_vecEquipInventory[i][j]->Get_ItemInfo().m_iAttack);
				}
			
				else if (m_vecEquipInventory[i][j]->Get_ItemName() == "Ȱ")
				{
					CObjMgr::Get_Instance()->Get_Ranger()->Set_Attack(m_vecEquipInventory[i][j]->Get_ItemInfo().m_iAttack);
				}
			
				else if (m_vecEquipInventory[i][j]->Get_ItemName() == "����")
				{
					CObjMgr::Get_Instance()->Get_Berserker()->Set_Attack(m_vecEquipInventory[i][j]->Get_ItemInfo().m_iAttack);
				}
			
				else if (m_vecEquipInventory[i][j]->Get_ItemName() == "��")
				{
					CObjMgr::Get_Instance()->Get_Tanker()->Set_Attack(m_vecEquipInventory[i][j]->Get_ItemInfo().m_iAttack);
				}

				else if (m_vecEquipInventory[i][j]->Get_ItemName() == "��")
				{
					CObjMgr::Get_Instance()->Get_Player()->Set_Armor(m_vecEquipInventory[i][j]->Get_ItemInfo().m_iArmor);
					CObjMgr::Get_Instance()->Get_Ranger()->Set_Armor(m_vecEquipInventory[i][j]->Get_ItemInfo().m_iArmor);
					CObjMgr::Get_Instance()->Get_Berserker()->Set_Armor(m_vecEquipInventory[i][j]->Get_ItemInfo().m_iArmor);
					CObjMgr::Get_Instance()->Get_Tanker()->Set_Armor(m_vecEquipInventory[i][j]->Get_ItemInfo().m_iArmor);
				}

				else if (m_vecEquipInventory[i][j]->Get_ItemName() == "��ű�")
				{
					dynamic_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->SetMaxMana(m_vecEquipInventory[i][j]->Get_ItemInfo().m_iMaxMana);
					dynamic_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->SetManaRecovery(m_vecEquipInventory[i][j]->Get_ItemInfo().m_fMpRecovery);
				}
			}


		}
	}
}

void CInventory::Exclude_Player()
{
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 2; ++j)
		{
			if (m_vecUnEquipInventory[i][j])
			{

				if (m_vecEquipInventory[i][j]->Get_ItemName() == "������")
				{
					CObjMgr::Get_Instance()->Get_Player()->Set_Attack(-m_vecEquipInventory[i][j]->Get_ItemInfo().m_iAttack);
				}

				else if (m_vecEquipInventory[i][j]->Get_ItemName() == "Ȱ")
				{
					CObjMgr::Get_Instance()->Get_Ranger()->Set_Attack(-m_vecEquipInventory[i][j]->Get_ItemInfo().m_iAttack);
				}

				else if (m_vecEquipInventory[i][j]->Get_ItemName() == "����")
				{
					CObjMgr::Get_Instance()->Get_Berserker()->Set_Attack(-m_vecEquipInventory[i][j]->Get_ItemInfo().m_iAttack);
				}

				else if (m_vecEquipInventory[i][j]->Get_ItemName() == "��")
				{
					CObjMgr::Get_Instance()->Get_Tanker()->Set_Attack(-m_vecEquipInventory[i][j]->Get_ItemInfo().m_iAttack);
				}

				else if (m_vecEquipInventory[i][j]->Get_ItemName() == "��")
				{
					CObjMgr::Get_Instance()->Get_Player()->Set_Armor(-m_vecEquipInventory[i][j]->Get_ItemInfo().m_iArmor);
					CObjMgr::Get_Instance()->Get_Ranger()->Set_Armor(-m_vecEquipInventory[i][j]->Get_ItemInfo().m_iArmor);
					CObjMgr::Get_Instance()->Get_Berserker()->Set_Armor(-m_vecEquipInventory[i][j]->Get_ItemInfo().m_iArmor);
					CObjMgr::Get_Instance()->Get_Tanker()->Set_Armor(-m_vecEquipInventory[i][j]->Get_ItemInfo().m_iArmor);
				}

				else if (m_vecEquipInventory[i][j]->Get_ItemName() == "��ű�")
				{
					dynamic_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->SetMaxMana(-m_vecEquipInventory[i][j]->Get_ItemInfo().m_iMaxMana);
					dynamic_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->SetManaRecovery(-m_vecEquipInventory[i][j]->Get_ItemInfo().m_fMpRecovery);
				}
			}


		}
	}
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
		m_vecUnEquipInventory[0].back()->Set_ItemType(L"����");

		m_vecUnEquipInventory[1].push_back(new CItem);
		m_vecUnEquipInventory[1].back()->Initialize();
		m_vecUnEquipInventory[1].back()->Set_ItemType(L"����");

		m_vecUnEquipInventory[2].push_back(new CItem);
		m_vecUnEquipInventory[2].back()->Initialize();
		m_vecUnEquipInventory[2].back()->Set_ItemType(L"����");

		m_vecUnEquipInventory[3].push_back(new CItem);
		m_vecUnEquipInventory[3].back()->Initialize();
		m_vecUnEquipInventory[3].back()->Set_ItemType(L"����");

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

	// �κ��丮�� ���� �� ��� ó���ϴ� ������ �߰��� �� �ֽ��ϴ�.
}

void CInventory::Equip_Add_Initialize()
{
	m_vecEquipInventory[0].reserve(m_iSize);
	m_vecEquipInventory[1].reserve(m_iSize);
	m_vecEquipInventory[2].reserve(m_iSize);

	for (int i = 0; i < 2; ++i)
	{
		m_vecEquipInventory[0].push_back(new CItem);
		m_vecEquipInventory[0].back()->Initialize();
		m_vecEquipInventory[0].back()->Set_ItemType(L"����");

		m_vecEquipInventory[1].push_back(new CItem);
		m_vecEquipInventory[1].back()->Initialize();
		m_vecEquipInventory[1].back()->Set_ItemType(L"��");

		m_vecEquipInventory[2].push_back(new CItem);
		m_vecEquipInventory[2].back()->Initialize();
		m_vecEquipInventory[2].back()->Set_ItemType(L"��ű�");
	}

	int TempNumber = 1;

	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 2; ++j)
		{
			if (m_vecEquipInventory[i][j])
			{
				m_vecEquipInventory[i][j]->Initialize();
				m_vecEquipInventory[i][j]->Set_FramePos(m_tEquipRect.left + m_fDistance, m_tEquipRect.top + m_fHeight);
				m_vecEquipInventory[i][j]->Set_Pos(m_tEquipRect.left + m_fDistance, m_tEquipRect.top + m_fHeight);
				m_vecEquipInventory[i][j]->Set_Number(TempNumber);
				++TempNumber;
			}
			m_fDistance += 100;
		}
		m_fDistance = 70.f;
		m_fHeight += 100.f;
	}

	m_fHeight = 100.f;
}


