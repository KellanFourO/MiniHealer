#pragma once
#include "Obj.h"
class CEnergyBolt :
    public CObj
{
public:
             CEnergyBolt();
    virtual ~CEnergyBolt();

public:


    virtual void Initialize(void) override;
    virtual int Update(void) override;
    virtual void Late_Update(void) override;
    virtual void Render(HDC hDC) override;
    virtual void Release(void) override;
    virtual void Setting_Img() override;

public:
    void ChaseTarget();

private:
    ULONGLONG       m_ulDestroyDelay;
    int             m_iEnergyBoltStart;
    int             m_iEnergyBoltEnd;

};

