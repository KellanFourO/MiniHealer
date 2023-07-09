#pragma once

#include "Obj.h"

template<typename T>
class CAbstractFactory
{
public:
	CAbstractFactory() {}
	~CAbstractFactory() {}

public:
	static CObj* Create()
	{
		CObj* pObj = new T;
		pObj->Initialize();

		return pObj;
	}

	static CObj* Create(float _fX, float _fY)
	{
		CObj* pObj = new T;
		pObj->Initialize();
		pObj->Set_Pos(_fX, _fY);

		return pObj;
	}
	
	static CObj* NonInit_Create(float _fX, float _fY)
	{
		CObj* pObj = new T;
		pObj->Set_Pos(_fX, _fY);

		return pObj;
	}

	static CObj* Create_SetDir(float _fX, float _fY, DIRECTION _Dir)
	{
		CObj* pObj = new T;
		pObj->Set_Dir(_Dir);
		pObj->Initialize();
		pObj->Set_Pos(_fX, _fY);
		return pObj;
	}
};

