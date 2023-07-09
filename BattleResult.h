#pragma once
#include "Scene.h"
#include "Obj.h"

class BattleResult :
    public CScene
{
public:
             BattleResult();
    virtual ~BattleResult();

public:
    virtual void Initialize() override;
    virtual void Update() override;
    virtual void Late_Update() override;
    virtual void Render(HDC hDC) override;
    virtual void Release() override;
    
public:
    void        Setting_Img();
    void        Produce_Spoil();

    void        Set_Boss(CObj* _Boss) { m_pBoss = _Boss; }
    CObj*       Get_Boss() { return m_pBoss; }

private:
    vector<CObj*>      m_vecSpoil;
    CObj*              m_pBoss;
};

