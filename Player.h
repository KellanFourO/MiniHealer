#pragma once

#include "Npc.h"


class CPlayer final : public CNpc
{

public:
	CPlayer();
	virtual ~CPlayer();

public:
	virtual void Initialize(void)	override;
	virtual int  Update(void)		override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC)	override;
	virtual void Release(void)		override;
	virtual void Setting_Img()		override;
	
public:
		int		GetMana() { return m_tStatus.m_iMp; }
		void	SetMana(int _iMp) { m_tStatus.m_iMp += _iMp; }
		void	SetManaInit(int _iMp) { m_tStatus.m_iMp = _iMp; }

		vector<CObj*>	Get_VecSkill() { return m_vecSkill; }



private:
	void		Key_Input(void);
	void		Motion_Change();
	CObj*		Create_Bullet();
	
	void		Change_SkillTarget();
	void		BattleSetting();

private:
	bool				m_bJump;
	bool				m_bTest;
	float				m_fPower;
	float				m_fTime;

	ULONGLONG			m_ulCreateBulletDelay;
	vector<CObj*>		m_vecSkill;
};
