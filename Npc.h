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
    NPC�� ������ �ִ� �����Ÿ� ����
    ���� �Ǵ� ������ ��� �� �ÿ�
    ���ݻ��·� �ٲ��, ���ݻ��·� �ٲ���
    ���� �ֵθ���, �� ���������� �ݶ��̴� ������ �����
    �ݶ��̴� �����ȿ� ������ ���Ͱ� ������
    Ư�� �����̰� �Ǹ� �浹�� �� ������ �Ѵ�.

    ������ ���� ��쿡�� Ư�� ���°� ���� ��쿡
    ȭ���� ������Ű��, ȭ�쿡 ���� �浹ó���� ���ش�.

    �����Ÿ����� ���� ���ö� ���� ���� �߰��Ѵ�.




*/
