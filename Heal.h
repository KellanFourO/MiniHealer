#pragma once
#include "PlayerSKill.h"

class CHeal :
    public CPlayerSKill
{
public: 
             CHeal();
    virtual ~CHeal();

public:
    virtual void Initialize(void) override;

    virtual int Update(void) override;

    virtual void Late_Update(void) override;

    virtual void Render(HDC hDC) override;

    virtual void Release(void) override;

    virtual void Setting_Img() override;

    virtual void Active_Skill() override;

public:
    void        Start_SkillTarget();
    void        Update_FrameRect();
/*
    »ó¼Ó 

    int           m_iSkillNumber;

    ULONGLONG     m_ulCastingDelay;
    float         m_fCastingTime;
    float         m_fCoolTime;
    int           m_iMana;
*/
   
private:
    float        m_fHealAmount;
    
    RECT         m_tFrameRect;
    INFO         m_tFrameInfo;

};

