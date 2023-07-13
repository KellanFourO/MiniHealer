#pragma once
#include "Obj.h"
#include "Item.h"

class CInventory :
    public CObj
{
public:
             CInventory();
    virtual ~CInventory();

public:
    virtual void Initialize(void) override;
    virtual int Update(void) override;
    virtual void Late_Update(void) override;
    virtual void Render(HDC hDC) override;
    virtual void Release(void) override;
    virtual void Setting_Img() override;

public:
    void    Get_Item(CItem* _Item);

    void    Mouse_Event();
    void    Equip_Event();
    void    Apply_Player();
    void    Exclude_Player();
    

public:
    bool    Maching_Item(CObj* _Item, CObj* _Click);
    void    Swap_Item(vector<CObj*>& _Inventory, int iIndex1, int iIndex2);
    CItem*  Get_UnEquipItem();
    vector<CItem*>* GeT_UnEquipInven() { return m_vecUnEquipInventory; }

public:
    //vector<CObj*>   Get_UnEquipItems() { return m_vecUnEquipItems; }
    //vector<CObj*>   Get_EquipItems() { return m_vecEquipItems; }

public:
    void            Update_EquipRect();
    void            Update_StatRect();

public:
    void            UnEquip_Add_Initialize();
    void            Equip_Add_Initialize();

private:
    vector<CItem*> m_vecUnEquipInventory[4];
    vector<CItem*> m_vecEquipInventory[3];
    //vector<CObj*>   m_vecEquipInventory;

private:
    bool            m_bInvenStart;
    const size_t    m_iSize;
    const size_t    m_iEquipSize;

    float           m_fHeight;
    
    RECT            m_tEquipRect;
    INFO            m_tEquipInfo;

    RECT            m_tStatRect;
    INFO            m_tStatInfo;
    
    CItem*           ClickItem;
    int             ClickIndexI;
    int             ClickIndexJ;

    CItem*           m_pSwapObj;

    bool            m_bDrag;
    POINT           m_pDragStart;
    POINT           m_pDragInfo;
};


/*float fX = ClickItem->Get_FrameInfo().fX;
                        float fY = ClickItem->Get_FrameInfo().fY;

                        if (CCollisionMgr::Check_Rect(ClickItem, m_vecUnEquipInventory[i][j], &fX, &fY));
                        {
                            if (CKeyMgr::Get_Instance()->Key_Down(VK_LBUTTON))
                            {
                                ClickItem->Set_FramePos(m_pDragStart.x, m_pDragStart.y);
                                ClickItem->Set_Pos(m_pDragInfo.x, m_pDragInfo.y);
                                ClickItem->Set_ItemDrag(false);
                                ClickItem = nullptr;
                            }
                            continue;
                        }*/


