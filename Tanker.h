#pragma once
#include "Npc.h"
class CTanker final :
	public CNpc
{
public:
	CTanker();
	virtual ~CTanker();

public:
	virtual void Initialize(void)	override;
	virtual int Update(void)		override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC)	override;
	virtual void Release(void)		override;
	virtual void Setting_Img()		override;

private:
	void		Motion_Change(void);
	void		Random_Move();
	void        Create_Collision();

private:
	bool		m_bTest;
};

