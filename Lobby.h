#pragma once
#include "Scene.h"
#include "Inventory.h"
#include "Map.h"

class CLobby :
    public CScene
{
public:
    CLobby();
    virtual ~CLobby();

public:

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
    
    bool    Get_OpenArmory() { return m_bOpenArmory; }
    bool    Get_OpenUI() { return m_bOpenUI; }

public:
    void    Create_Inventory();
    void    Create_Map();
    void    Create_Button();
    void    Armory_Init();
    void    Door_Init();
    void    Setting_Img();

public:
    void    MouseEvent();
    
    CInventory* Get_Inventory() { return m_pInventory; };

public:
    void    Update_ArmoryRect();
    void    Update_DoorRect(); 
    void    Update_ExitRect();



private:
    int     m_iFireStart;
    int     m_iFireEnd;
    ULONGLONG   m_dwFireDelay;


    ULONGLONG   m_dwNpcMoveDelay;
    bool    m_bMoveSwitch;

    RECT    m_tUIExitBtnRect;
    INFO    m_tUIExitInfo;

    RECT    m_tArmoryRect;
    INFO    m_tArmoryInfo;

    RECT    m_tDoorRect;
    INFO    m_tDoorInfo;

    bool    m_bOpenUI;
    bool    m_bOpenMap;
    bool    m_bOpenArmory;
    bool    m_bOpenSkill;
    bool    m_bOpenAbility;
    bool    m_bOpenInfo;

    CMap*           m_pMap;
    CInventory*     m_pInventory;
    
   
    int     m_iArmoryDrawID;
    int     m_iDoorDrawID;
    
};

