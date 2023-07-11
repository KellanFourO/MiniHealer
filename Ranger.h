#pragma once
#include "Npc.h"
class CRanger final :
	public CNpc
{
public:
	CRanger();
	virtual ~CRanger();

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
	CObj*		Create_Bullet();

private:
	bool				m_bJump;
	float				m_fPower;
	float				m_fTime;
	bool				m_bTest;

	ULONGLONG			m_ulCreateBulletDelay;

};

