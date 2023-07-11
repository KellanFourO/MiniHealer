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
    void    EquipItem();
    void    UnEquipItem();
    void    IsFull_Item(CObj* _Item);
    void    IsSell_Item(int _iInput, int* pMoney);

    void    Get_Item(CObj* _Item);

    CObj*    Create_Item();
    void     Mouse_Event();

public:
    bool    Maching_Item(CObj* _Item, CObj* _Click);
    void    Swap_Item(vector<CObj*>& _Inventory, int iIndex1, int iIndex2);

public:
    //vector<CObj*>   Get_UnEquipItems() { return m_vecUnEquipItems; }
    //vector<CObj*>   Get_EquipItems() { return m_vecEquipItems; }

public:
    void            Update_EquipRect();
    void            Update_StatRect();

public:
    void            UnEquip_Initialize();
    void            UnEquip_AddItem(CItem* item);

private:
    vector<vector<CItem*>> m_vecUnEquipInventory;
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
    
    CObj*           ClickItem;
    int             ClickIndexI;
    int             ClickIndexJ;

    CObj*           m_pSwapObj;

    bool            m_bDrag;
    POINT           m_pDragStart;
};

