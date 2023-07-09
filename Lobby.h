#pragma once
#include "Scene.h"
#include "Map.h"

class CLobby :
    public CScene
{
public:
    CLobby();
    virtual ~CLobby();

public:

    // CScene을(를) 통해 상속됨
    virtual void Initialize() override;

    virtual void Update() override;

    virtual void Late_Update() override;

    virtual void Render(HDC hDC) override;

    virtual void Release() override;


public:
    void    Set_OpenUI(bool _SetOpen) { m_bOpenUI = _SetOpen; }
    void    Set_OpenMap(bool _SetMap) { m_bOpenMap = _SetMap; }
    void    Set_OpenArmory(bool _SetArmory) { m_bOpenArmory = _SetArmory; }
    void    Set_OpenSkill(bool _SetSkill) { m_bOpenSkill = _SetSkill; }
    void    Set_OpenAbility(bool _SetAbility) { m_bOpenAbility = _SetAbility; }
    void    Set_OpenInfo(bool _SetOpenInfo) { m_bOpenInfo = _SetOpenInfo; }


private:
    int     m_iFireStart;
    int     m_iFireEnd;
    ULONGLONG   m_dwFireDelay;



    ULONGLONG   m_dwLunariaDelay;
    int     m_iTestStart;
    int     m_iTestMotion;
    int     m_iTestEnd;

    ULONGLONG   m_dwNpcMoveDelay;
    bool    m_bMoveSwitch;

    RECT    m_tUIExitBtnRect;
    INFO    m_tUIExitInfo;

    bool    m_bOpenUI;
    bool    m_bOpenMap;
    bool    m_bOpenArmory;
    bool    m_bOpenSkill;
    bool    m_bOpenAbility;
    bool    m_bOpenInfo;

    CMap*   m_pMap;


};

