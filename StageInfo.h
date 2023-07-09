#pragma once
#include "Obj.h"
#include "MyButton.h"

class CStageInfo :
    public CObj
{
public:
    CStageInfo();
    ~CStageInfo();

public:
    virtual void Initialize(void) override;
    virtual int Update(void) override;
    virtual void Late_Update(void) override;
    virtual void Render(HDC hDC) override;
    virtual void Release(void) override;
    virtual void Setting_Img() override;

public:
    void        Update_ExitRect();
    void        Update_StartRect();

private:
    CObj*        m_pBoss;

    int     m_iDifficulty;

    static int  m_iClearTime;
    static int  m_iKillCount;
    
    RECT        m_tExitRect;
    INFO        m_tExitInfo;
    
    RECT        m_tStartBtnRect;
    INFO        m_tStartBtnInfo;
};

