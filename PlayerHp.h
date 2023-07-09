#pragma once
#include "Obj.h"
class CPlayerHp :
    public CObj
{
public:
             CPlayerHp();
    virtual ~CPlayerHp();

public:


    // CObj을(를) 통해 상속됨
    virtual void Initialize(void) override;

    virtual int Update(void) override;

    virtual void Late_Update(void) override;

    virtual void Render(HDC hDC) override;

    virtual void Release(void) override;

    virtual void Setting_Img() override;

public:
    bool        Get_Select() { return m_bSelect; }
    void        Set_Select(bool _Select) { m_bSelect = _Select; }

public:
    void        Update_HpBarRect();
    void        Update_SelectFrameRect();
    void        Update_IconRect();
    void        Update_CastingProRect();
    void        Update_ManaRect();



private:
    RECT    m_tHpBarRect;
    INFO    m_tHpBarInfo;

    RECT    m_tSelectFrameRect;
    INFO    m_tSelectFrameInfo;

    RECT    m_tIconRect;
    INFO    m_tIconInfo;

    RECT    m_tCastingFrameRect;
    INFO    m_tCastingFrameInfo;

    RECT    m_tCastingProRect;
    INFO    m_tCastingProInfo;

    RECT    m_tTimerRect;
    INFO    m_tTimerInfo;

    RECT    m_tManaRect;
    INFO    m_tManaInfo;

    int     m_iSelectMotion; // 선택되지않았다면 0 , 선택됐다면 1, 
    int     m_iIconMotion; // 살아있다면 0 , 죽었다면 1

    bool    m_bSelect;


};

