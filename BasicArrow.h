#pragma once
#include "Obj.h"
class CBasicArrow :
    public CObj
{
public:
             CBasicArrow();
    virtual ~CBasicArrow();

public:
    virtual void Initialize(void) override;
    virtual int Update(void) override;
    virtual void Late_Update(void) override;
    virtual void Render(HDC hDC) override;
    virtual void Release(void) override;
    virtual void Setting_Img() override;


public:
    void            ChaseTarget();

private:
    ULONGLONG       m_ulDestroyDelay;
    



};


