#pragma once

#include "BitMap.h"

class CBmpMgr
{
private:
	CBmpMgr();
	~CBmpMgr();

public:
	void		Insert_Bmp(const TCHAR* pFilePath, const TCHAR* pImgKey);
	HDC			Find_Img(const TCHAR* pImgKey);
	void		Release();
	HBITMAP     GetRotatedBitMap(HDC hDC, HBITMAP hBitmap, float radians, COLORREF clrBlack);
	HBITMAP		GetBitMap() { return m_mapBit.find(L"ManaImage")->second->Get_BitMap(); }

public:
	static CBmpMgr* Get_Instance()
	{
		if (!m_pInstance)
		{
			m_pInstance = new CBmpMgr;
		}

		return m_pInstance;	}
	static void		Destroy_Instance()
	{
		if (m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}

private:
	static CBmpMgr* m_pInstance;
	map<const TCHAR*, CBitMap*>			m_mapBit;

};

