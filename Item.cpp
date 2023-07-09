#include "Item.h"
#include "BmpMgr.h"
#include "ObjMgr.h"

CItem::CItem()
{
	ZeroMemory(&m_tItemInfo, sizeof(ItemInfo));
	
}

CItem::CItem(const CItem& rhs)
{
	ZeroMemory(&m_tItemInfo, sizeof(ItemInfo));
}

CItem::~CItem()
{
}



void CItem::Setting_Img()
{
	
}

void CItem::ApplyEffect()
{
	if (m_tItemInfo.m_bEquip)
	{
		CObjMgr::Get_Instance()->Get_Player()->Set_Attack(m_tItemInfo.m_iAttack);
	}
	
	
}
