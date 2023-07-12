#pragma once
#include "Scene.h"
#include "Obj.h"
#include "PlayerHp.h"
#include "Item.h"

class CField :
    public CScene
{
public:
             CField();
    virtual ~CField();

public:
    virtual void Initialize() override;
    virtual void Update() override;
    virtual void Late_Update() override;
    virtual void Render(HDC hDC) override;
    virtual void Release() override;

public:
    CObj*   Get_Target() { return m_pTarget; }
    void    Set_Target(CObj* _Target) { m_pTarget = _Target; }
    void    Setting_Img();
    void    Collision();
    vector<CItem*>    Create_Spoil();

public:
    void        Update_BossHpFrameRect();
    void        Update_BossHpBarRect();
    void        Update_TimeRect();

private:
    CObj*       m_pTarget;
    float       m_TestAngle;
    bool        m_bBossDie;
    bool        m_bStartChange;

    ULONGLONG   m_ulCollisionDelay;
    ULONGLONG   m_ulResultChangeDelay;

    RECT    m_tBossHpFrameRect;
    INFO    m_tBossHpFrameInfo;

    RECT    m_tBossHpBarRect;
    INFO    m_tBossHpBarInfo;

    RECT    m_tTimerRect;
    INFO    m_tTimerInfo;

    list<CObj*>       m_pHp_UIList;

    ULONGLONG       m_ulStartTime;
    ULONGLONG       m_ulNowTime;
    ULONGLONG       m_ulEndTime;

    int          m_iHour;
    int          m_iMinute;
    long         m_lSecond;
};

