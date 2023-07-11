#pragma once
#include "Obj.h"
#include "OBB_Collider.h"


class CBoneKnight :
    public CObj
{
public:
    CBoneKnight();
    virtual ~CBoneKnight();

public:



    // CBoss을(를) 통해 상속됨
    virtual void Initialize(void) override;

    virtual int Update(void) override;

    virtual void Late_Update(void) override;

    virtual void Render(HDC hDC) override;

    virtual void Release(void) override;

    virtual void Setting_Img() override;
    
  

private:
    void            Motion_Change();
    void            Boss_AI();
    void            Motion_Change2();
    void            Create_Collision();

    void            Chase_Target();
       
    CObj*            Create_Slam(DIRECTION _DIR);
    CObj*            Create_Slam2(DIRECTION _DIR);
    CObj*            Create_Slam3(DIRECTION _DIR);

    CObj*           Create_ThrowSword();

private:
    BONEKNIGHTSTATEID   m_eCurState;
    BONEKNIGHTSTATEID   m_ePreState;

    int                 iAttackCount;
    
    bool                m_bSlam;
    bool                m_bThrow;

    ULONGLONG           m_dwPatternDelay;
    ULONGLONG           m_ulAttackCountDelay;

    bool                m_bSwitch;

    int                 m_iSlamStart;
    int                 m_iSlamEnd;


};

