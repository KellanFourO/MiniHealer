#pragma once
#include "Obj.h"

class CItem :
    public CObj
{
public:
            CItem();
             CItem(const string& ItemName);
             CItem(const CItem& rhs);

    virtual ~CItem();

public:
    virtual void Initialize(void) override;
    virtual int Update(void) override;
    virtual void Late_Update(void) override;
    virtual void Render(HDC hDC) override;
    virtual void Release(void) override;
    virtual void Setting_Img() override;

public:
    void        ApplyEffect();
    ItemInfo    Get_ItemInfo() { return m_tItemInfo; }
    void        Set_ItemType(const TCHAR* _Type) { m_tItemInfo.m_pType = _Type; }
    void        Set_ItemName(const TCHAR* _Name) { m_tItemInfo.m_pName = _Name; }
    void        Set_ItemApply(const TCHAR* _Apply) { m_tItemInfo.m_pApply = _Apply; }
    void        Set_ItemDrag(bool _Drag) { m_bDrag = _Drag; }
    void        Set_Result(bool _Result) { m_bResult = _Result; }
    void        Set_Name(string _Name) { m_sName = _Name; }
    void        Set_Number(int _Number) { m_iItemNumber = _Number; }
    void        Set_MaxMana(int _MaxMana) { m_tItemInfo.m_iMaxMana = _MaxMana; }
    void        Set_ManaRecovery(float _Recorvery) { m_tItemInfo.m_fMpRecovery = _Recorvery; }

public:
    void        MouseChase();
    void        Update_FrameRect();
    INFO        Get_FrameInfo() { return m_tFrameInfo; }
    void        Set_FramePos(float _fX, float _fY) { m_tFrameInfo.fX = _fX; m_tFrameInfo.fY = _fY; }
    float       Get_PrePosX() { return m_fPreX; }
    float       Get_PrePosY() { return m_fPreY; }
    int         Get_Number() { return m_iItemNumber; }
    string      Get_ItemName() { return m_sName; }

protected:
    ItemInfo    m_tItemInfo;
    RECT        m_tFrameRect;
    INFO        m_tFrameInfo;

    float       m_fPreX;
    float       m_fPreY;
    
    bool        m_bResult;
    bool        m_bDrag;
    string      m_sName;

    int         m_iItemNumber;
};

