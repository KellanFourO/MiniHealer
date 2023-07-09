#pragma once
#include "Obj.h"
class CBoneKnightThrowSword :
    public CObj
{
public:
             CBoneKnightThrowSword();
    virtual ~CBoneKnightThrowSword();

public:
    virtual void Initialize(void) override;
    virtual int Update(void) override;
    virtual void Late_Update(void) override;
    virtual void Render(HDC hDC) override;
    virtual void Release(void) override;
    virtual void Setting_Img() override;

public:
    void    UpdateDangerousRect();
    void    AngleAttack();

private:
    ULONGLONG   m_dwDestroyDelay;
    ULONGLONG   m_dwDangerousDelay;

    RECT    m_tDangerousRect;
    INFO    m_tDangerousInfo;

    bool    m_tDangerousSwitch;
};

