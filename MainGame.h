#pragma once
#include "Obj.h"
#include "Define.h"


class CMainGame
{
public:
	CMainGame();
	~CMainGame();

public:
	void		Initialize();
	void		Update();
	void		Late_Update();
	void		Render();
	void		Release();

private:
	HDC			m_hDC;

#pragma region ����

	//CObj*		m_pPlayer;
	//list<CObj*>	m_BulletList;

#pragma endregion ����
	list<CObj*>	m_ObjList[OBJID_END];

	ULONGLONG		m_dwTime;
	int			m_iFPS;
	TCHAR		m_szFPS[32];

};

