#pragma once
#include "Scene.h"
#include "Obj.h"
#include "Item.h"

class CBattleResult :
    public CScene
{
public:
             CBattleResult();
    virtual ~CBattleResult();

public:
    virtual void Initialize() override;
    virtual void Update() override;
    virtual void Late_Update() override;
    virtual void Render(HDC hDC) override;
    virtual void Release() override;
    
public:
    void        Setting_Img();
    vector<CItem*>  Get_vecSpoil() { return m_vecSpoil; }
    

public:
    void        Update_InvenRect();
    void        Add_Spoil(vector<CItem*> _vector) { m_vecSpoil.swap(_vector); }
    void        Spoil_SetPos();
    void        Mouse_EventResult();

   
    

private:
    vector<CItem*>      m_vecSpoil;
    

    RECT               m_tInvenRect;
    INFO               m_tInvenInfo;

    CObj*               m_pPlayer;
    CObj*               m_pBerserker;
    CObj*               m_pRanger;
    CObj*               m_pTanker;

    bool                m_bSpoilSwitch;
    bool                m_bClick;

    float               m_fHeight;
    float               m_fDistance;

    ULONGLONG           m_ulRenderDelay;

    int                 m_iChestStart;
    int                 m_iChestEnd;
    ULONGLONG           m_ulChestDelay;

    float                m_fBlackBgAlpha;

    CItem*              m_pClick;
    CItem*              m_pTempClick;
};

