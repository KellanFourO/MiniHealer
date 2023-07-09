#pragma once
#include "Obj.h"
class CPlayerHp :
    public CObj
{
public:
             CPlayerHp();
    virtual ~CPlayerHp();

public:


    // CObj��(��) ���� ��ӵ�
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

    int     m_iSelectMotion; // ���õ����ʾҴٸ� 0 , ���õƴٸ� 1, 
    int     m_iIconMotion; // ����ִٸ� 0 , �׾��ٸ� 1

    bool    m_bSelect;


};

