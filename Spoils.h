#pragma once
#include "Obj.h"
class CSpoils :
    public CObj
{
public:
             CSpoils();
    virtual ~CSpoils();

public:
    virtual void Initialize(void) override;
    virtual int  Update(void) override;
    virtual void Late_Update(void) override;
    virtual void Render(HDC hDC) override;
    virtual void Release(void) override;
    virtual void Setting_Img() override;

public:
    void    UpdateItemRect();

private:
    RECT    m_tItemRect;
    INFO    m_tItemeInfo;
    
};

