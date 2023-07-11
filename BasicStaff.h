#pragma once
#include "Item.h"
class CBasicStaff :
    public CItem
{
public:
             CBasicStaff();
    virtual ~CBasicStaff();

public:
    virtual void Initialize(void) override;
    virtual int  Update(void) override;
    virtual void Late_Update(void) override;
    virtual void Render(HDC hDC) override;
    virtual void Release(void) override;
    virtual void Setting_Img() override;

    

};

