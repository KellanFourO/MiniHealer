#pragma once
#include "Obj.h"
class CNpc :
    public CObj
{
public:
             CNpc();
    virtual ~CNpc();

public:
    virtual void Initialize(void) PURE;
    virtual int Update(void) PURE;
    virtual void Late_Update(void) PURE;
    virtual void Render(HDC hDC) PURE;
    virtual void Release(void) PURE;

protected:
    void    Start_Target();
    void    Target_Change();
    void    Chase_Attack();
    void    AI_Target();
    void    Recovery();
   
    ULONGLONG           m_ulHpRecoveryDelay;
    ULONGLONG           m_ulMpRecoveryDelay;

    int                 m_iAttackCount;
    ULONGLONG           m_ulAttackCountDelay;

    float               m_fMoveDistance;

    ULONGLONG           m_dwNpcMoveDelay;
    bool                m_bMoveSwitch;

    bool                m_bFieldSwitch;
    
    HEALERSTATEID		m_eHealerCur;
    HEALERSTATEID		m_eHealerPre;

    RANGERSTATEID       m_eRangerCur;
    RANGERSTATEID       m_eRangerPre;

    BERSERKERSTATEID    m_eBerserCur;
    BERSERKERSTATEID    m_eBerserPre;

    TANKERSTATEID       m_eTankerCur;
    TANKERSTATEID       m_eTankerPre;




};

/*
    NPC가 가지고 있는 사정거리 안의
    몬스터 또는 보스가 들어 올 시에
    공격상태로 바뀌며, 공격상태로 바뀐후
    검을 휘두르며, 그 범위에대한 콜라이더 영역이 생긴다
    콜라이더 영역안에 보스나 몬스터가 있을시
    특정 딜레이가 되면 충돌이 된 것으로 한다.

    레인저 같은 경우에는 특정 상태가 됐을 경우에
    화살을 생성시키며, 화살에 대한 충돌처리를 해준다.

    사정거리안의 적이 들어올때 까지 적을 추격한다.




*/
