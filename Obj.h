#pragma once
#include "Define.h"

class CObj {
public:
	CObj();
	virtual ~CObj();

public:
	RECT			Get_Rect() { return m_tRect; }
	INFO			Get_Info() { return m_tInfo; }

	RECT			Get_WeaponRect() { return m_tWeaponRect; }
	INFO			Get_WeaponInfo() { return m_tWeaponInfo; }

	STAT			Get_Status() { return m_tStatus; }
	int				Get_Hp() { return m_tStatus.m_iHp; }
	int				Get_MaxHp() { return m_tStatus.m_iMaxHp; }
	void			Set_HpInit(float _Hp) { m_tStatus.m_iHp = _Hp; }
	void			Set_Hp(float _Hp) { m_tStatus.m_iHp += _Hp; }

	int				Get_Attack() { return m_tStatus.m_iAttack; }
	void			Set_Attack(int _Attack) { m_tStatus.m_iAttack += _Attack; }

	void			Set_Size(float _fCX, float _fCY)
	{
		m_tInfo.fCX = _fCX;
		m_tInfo.fCY = _fCY;
	}

	void			Set_Pos(float _fX, float _fY)
	{
		m_tInfo.fX = _fX;
		m_tInfo.fY = _fY;
	}


	DIRECTION		Get_Dir()					{ return m_eDir; }
	void			Set_Dir(DIRECTION eDir)		{ m_eDir = eDir; }
	
	bool			Get_Start() { return m_bStartSwitch; }
	void			Set_Start(bool _Start) { m_bStartSwitch = _Start; }

	bool			Get_End() { return m_bEndSwitch; }
	void			Set_End(bool _End) { m_bEndSwitch = _End; }
	
	CObj*			Get_Target()				{ return m_pTarget; }
	void			Set_Target(CObj* _pTarget)	{ m_pTarget = _pTarget; }

	void			Set_PosX(float _fX)			{ m_tInfo.fX = _fX; }
	void			Set_PosY(float _fY)			{ m_tInfo.fY = _fY; }

	bool			Get_Dead() { return m_bDead; }
	void			Set_Dead() { m_bDead = true; }

	void			Set_FrameKey(const TCHAR* pFrameKey) { m_pFrameKey = pFrameKey; }

	RENDERID		Get_RenderID() { return m_eRender; }
	void			Set_RenderID(RENDERID _eRender) { m_eRender = _eRender; }

public:
	virtual void		Initialize(void)	PURE;
	virtual int			Update(void)		PURE;
	virtual void		Late_Update(void)	PURE;
	virtual void		Render(HDC hDC)		PURE;
	virtual void		Release(void)		PURE;
	virtual void		Setting_Img()		PURE;

public:
	void			Set_UI_ID(UI_ID _UI_ID) { m_eUI = _UI_ID; }
	UI_ID			Get_UI_ID() { return m_eUI; }
	int				Get_Number() { return m_iNumber; }
	const TCHAR*	Get_Name() { return m_pName; }
	int				Get_Exp() { return m_iExp; }
	int				Get_Gold() { return m_iGold; }

	void			Set_ClearTime(int _Hour, int _Minute, long _Second) 
	{ 
		m_tClearTime.m_iHour = _Hour;
		m_tClearTime.m_iMinute = _Minute;
		m_tClearTime.m_lSecond = _Second;
	}
	
	ClearTime	Get_ClearTime() { return m_tClearTime; }
	

protected:
	void				Update_Rect();
	void				Update_WeaponRect();
	void				Move_Frame();
	
	

protected:
	float					m_fSpeed;
	float					m_fAngle;
	float					m_fDistance;
	bool					m_bDead;
	bool					m_bStartSwitch;
	bool					m_bEndSwitch;

	int						m_iStart;
	int						m_iEnd;
	int						m_iMotion;

	INFO					m_tInfo;
	RECT					m_tRect;

	INFO					m_tWeaponInfo;
	RECT					m_tWeaponRect;

	DIRECTION				m_eDir;
	FRAME					m_tFrame;
	RENDERID				m_eRender; // 렌더링 순서를 두기위해 열거체 사용

	CObj*					m_pTarget;
	const TCHAR*			m_pFrameKey; // 문자열 프레임키
	

	UI_ID					m_eUI;
	STAT					m_tStatus;

	const TCHAR*			m_pName;
	int						m_iNumber;

	int						m_iExp;
	int						m_iGold;

	ClearTime				m_tClearTime;

	int						m_iHour;
	int						m_iMinute;
	long					m_lSecond;


};

