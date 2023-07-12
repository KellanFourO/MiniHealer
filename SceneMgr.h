#pragma once


#include "TitleMenu.h"
#include "MyEdit.h"
#include "Stage.h"
#include "Lobby.h"
#include "Field.h"
#include "BattleResult.h"

class CSceneMgr
{
private:
	CSceneMgr();
	~CSceneMgr();

public:
	SCENEID				Get_SceneID() { return m_eCurScene; }
	CLobby*				Get_Lobby() { return dynamic_cast<CLobby*>(m_pScene); }
	CStage*				Get_Stage() { return dynamic_cast<CStage*>(m_pScene); }
	CField*				Get_Field() { return dynamic_cast<CField*>(m_pScene); }
	CBattleResult*		Get_BResult() { return dynamic_cast<CBattleResult*>(m_pScene); }

public:
	void		Scene_Change(SCENEID eScene);
	void		Update();
	void		Late_Update();
	void		Render(HDC hDC);
	void		Release();
	void		Field_On(CObj* _Boss);

public:
	static CSceneMgr* Get_Instance()
	{
		if (!m_pInstance)
		{
			m_pInstance = new CSceneMgr;
		}

		return m_pInstance;
	}
	static void		Destroy_Instance()
	{
		if (m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}

private:
	static CSceneMgr* m_pInstance;
	CScene*					m_pScene;

	SCENEID					m_eCurScene;
	SCENEID					m_ePreScene;
	
	
};

// state 패턴 : 객체는 자신이 취할 수 있는 유한한 개수를 갖고, 그 중 반드시 단 하나의 상태만을 취한다는 의미의 패턴

