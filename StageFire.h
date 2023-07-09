#pragma once
#include "Obj.h"
class CStageFire :
    public CObj
{
public:
             CStageFire();
    virtual ~CStageFire();

public:
    virtual void Initialize(void) override;
    virtual int Update(void) override;
    virtual void Late_Update(void) override;
    virtual void Render(HDC hDC) override;
    virtual void Release(void) override;
    virtual void Setting_Img() override;

private:
    ULONGLONG	m_dwStageFireDelay;

    int		    m_iStageFireStart;
    int		    m_iStageFireEnd;
};

