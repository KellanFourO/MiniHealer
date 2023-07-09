#pragma once
#include "Obj.h"
class CItem :
    public CObj
{
public:
             CItem();
             CItem(const CItem& rhs);
    virtual ~CItem();

public:
    virtual void Initialize(void) PURE;
    virtual int Update(void) PURE;
    virtual void Late_Update(void) PURE;
    virtual void Render(HDC hDC) PURE;
    virtual void Release(void) PURE;
    virtual void Setting_Img() PURE;

public:
    void        ApplyEffect();
    ItemInfo    Get_ItemInfo() { return m_tItemInfo; }


protected:
    ItemInfo    m_tItemInfo;
    
};

