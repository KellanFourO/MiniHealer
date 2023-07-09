#pragma once
#include "Obj.h"
class CLamb :
    public CObj
{
public:
            CLamb();
    virtual ~CLamb();

public:
    virtual void Initialize(void) override;
    virtual int  Update(void) override;
    virtual void Late_Update(void) override;
    virtual void Render(HDC hDC) override;
    virtual void Release(void) override;
    virtual void Setting_Img() override;

};

