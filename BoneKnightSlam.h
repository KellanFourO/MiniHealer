#pragma once
#include "Obj.h"
class CBoneKnightSlam :
    public CObj
{
public:
    CBoneKnightSlam();
    virtual ~CBoneKnightSlam();

public:
    virtual void Initialize(void) override;

    virtual int  Update(void) override;

    virtual void Late_Update(void) override;

    virtual void Render(HDC hDC) override;

    virtual void Release(void) override;

    virtual void Setting_Img() override;

public:
    void    Set_Distance(float _Distance) { m_fDestroyDistance = _Distance; }

private:
    float   m_fDestroyDistance;
    ULONGLONG   m_dwDestroyDelay;
    

};

