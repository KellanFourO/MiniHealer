#include "framework.h"
#include "SceneMgr.h"


CSceneMgr* CSceneMgr::m_pInstance = nullptr;

CSceneMgr::CSceneMgr()
	: m_eCurScene(SC_MENU), m_ePreScene(SC_END), m_pScene(nullptr)
{
}

CSceneMgr::~CSceneMgr()
{
	Release();
}

void CSceneMgr::Scene_Change(SCENEID eScene)
{
	m_eCurScene = eScene;
	
	vector<CItem*> Tempvector;

	if (m_ePreScene == SC_FIELD)
	{ 
		Tempvector = dynamic_cast<CField*>(m_pScene)->Create_Spoil();
	}
		



	if (m_ePreScene != m_eCurScene)
	{
		Safe_Delete(m_pScene);

		switch (m_eCurScene)
		{

		case SC_MENU:
			m_pScene = new CTitleMenu;
			break;

		case SC_EDIT:
			m_pScene = new CMyEdit;
			break;

		case SC_LOBBY:
			m_pScene = new CLobby;
			break;

		case SC_STAGE:
			m_pScene = new CStage;
			break;

		case SC_FIELD:
			m_pScene = new CField;
			break;

		case SC_Result:

			m_pScene = new CBattleResult;
			dynamic_cast<CBattleResult*>(m_pScene)->Add_Spoil(Tempvector);
			break;
		

		}

		m_pScene->Initialize();

		m_ePreScene = m_eCurScene;

	}

}



void CSceneMgr::Update()
{
	m_pScene->Update();
}

void CSceneMgr::Late_Update()
{
	m_pScene->Late_Update();
}

void CSceneMgr::Render(HDC hDC)
{
	m_pScene->Render(hDC);
}

void CSceneMgr::Release()
{
	Safe_Delete(m_pScene);
}

void CSceneMgr::Field_On(CObj* _Boss)
{

	if (m_ePreScene != m_eCurScene)
	{
		Safe_Delete(m_pScene);
	}

	
	m_eCurScene = SC_FIELD;

	m_pScene = new CField;

	_Boss->Initialize();
	dynamic_cast<CField*>(m_pScene)->Set_Target(_Boss);
	m_pScene->Initialize();

	m_ePreScene = m_eCurScene;
}
