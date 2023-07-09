#pragma once
#include "Obj.h"
class CPlayerSKill :
    public CObj
{
public:
             CPlayerSKill();
    virtual ~CPlayerSKill();

public:


    // CObj을(를) 통해 상속됨
    virtual void Initialize(void) PURE;
    virtual int Update(void) PURE;
    virtual void Late_Update(void) PURE;
    virtual void Render(HDC hDC) PURE;
    virtual void Release(void) PURE;
    virtual void Setting_Img() PURE;
    virtual void Active_Skill() PURE;
    

public:
    void    Set_SkillNumber(char _cNumber) { m_iSkillNumber = _cNumber; }
    void    Set_SkillTarget(CObj* _SkillTarget) { m_pSkillTarget = _SkillTarget; }
    CObj*    Get_SkillTarget() { return m_pSkillTarget; }

protected:
    int           m_iSkillNumber;

    ULONGLONG     m_ulCastingDelay;
    float         m_fCastingTime;
    float         m_fCoolTime;
    int           m_iMana;

    CObj*         m_pSkillTarget;
};

