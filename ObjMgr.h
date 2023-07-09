#pragma once

#include "Define.h"
#include "Obj.h"
#include "SelectDoor.h"

class CObjMgr
{
private:
	CObjMgr();
	~CObjMgr();

public:
	CObj* Get_Player()    { return m_ObjList[PLAYER].front(); }
	CObj* Get_Berserker() { return m_ObjList[BERSERKER].front(); }
	CObj* Get_Ranger()    { return m_ObjList[RANGER].front(); }
	CObj* Get_Tanker()    { return m_ObjList[TANKER].front(); }
	
	//CObj* Get_SelectDoor() { return m_ObjList[SELECT_DOOR].front(); }
	

	void Set_Player(CObj* _CopyPlayer)    { m_ObjList[PLAYER].front() = _CopyPlayer; }
	void Set_Berserker(CObj* _CopyPlayer) { m_ObjList[BERSERKER].front() = _CopyPlayer; }
	void Set_Ranger(CObj* _CopyPlayer)	  { m_ObjList[RANGER].front() = _CopyPlayer; }
	void Set_Tanker(CObj* _CopyPlayer)    { m_ObjList[TANKER].front() = _CopyPlayer; }

	CObj* Get_Target(OBJID eID, CObj* pInstance);

	list<CObj*> Get_Objects(OBJID eID) { return m_ObjList[eID]; }

public:
	void		Add_Object(OBJID eID, CObj* pInstance);
	int			Update();
	void		Late_Update();
	void		Render(HDC hDC);
	void		Release();

	void		Delete_ID(OBJID eID);

public:
	static CObjMgr* Get_Instance()
	{
		if (!m_pInstance)
		{
			m_pInstance = new CObjMgr;
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
	list<CObj*>	m_ObjList[OBJID_END];
	list<CObj*>	m_RenderList[RENDER_END];

	static CObjMgr* m_pInstance;
};

// 1. 유도 미사일 만들기(가장 가까운 객체를 탐색하여 삭제)

// 2. 선을 그리고 중점 좌표를 기준으로 직선 타기를 구현하라
// '두 점을 지나는 직선의 방정식' 참고할 것