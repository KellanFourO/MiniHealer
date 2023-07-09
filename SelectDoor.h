#pragma once
#include "Obj.h"

class CSelectDoor : public CObj
{
public:
	CSelectDoor();
	~CSelectDoor();

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;
	virtual void Setting_Img() override;


public:
	void		Set_Boss(CObj* _Boss) { m_pBoss = _Boss; }
	CObj*		Get_Boss() { return m_pBoss; }

	
private:
	CObj*		m_pBoss;
	

	CObj*	m_pStageInfo;

	int		m_iDoorBGStart;
	int		m_iDoorBGEnd;
	DWORD	m_dwDoorBGDelay;

	
};

