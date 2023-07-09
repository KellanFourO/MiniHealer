#pragma once
#include "Obj.h"
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

public:
    void    UpdateExitRect();

private:
    vector<CObj*>   m_vecItems;
    RECT            m_tExitRect;
    INFO            m_tExitInfo;
    bool            m_bInvenStart;
};

