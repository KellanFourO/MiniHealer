#include "framework.h"
#include "BmpMgr.h"

CBmpMgr* CBmpMgr::m_pInstance = nullptr;

CBmpMgr::CBmpMgr()
{
}


CBmpMgr::~CBmpMgr()
{
	Release();
}

void CBmpMgr::Insert_Bmp(const TCHAR* pFilePath, const TCHAR* pImgKey)
{
	auto iter = find_if(m_mapBit.begin(), m_mapBit.end(), CTag_Finder(pImgKey));

	if (iter == m_mapBit.end())
	{
		CBitMap* pBmp = new CBitMap;
		pBmp->Load_Bmp(pFilePath);

		m_mapBit.insert({ pImgKey, pBmp });
	}


}

HDC CBmpMgr::Find_Img(const TCHAR* pImgKey)
{
	auto iter = find_if(m_mapBit.begin(), m_mapBit.end(), CTag_Finder(pImgKey));

	if (iter == m_mapBit.end())
		return nullptr;

	return iter->second->Get_MemDC();
}

void CBmpMgr::Release()
{
	for_each(m_mapBit.begin(), m_mapBit.end(), CDeleteMap());
	m_mapBit.clear();
}

HBITMAP CBmpMgr::GetRotatedBitMap(HDC hDC, HBITMAP hBitmap, float radians, COLORREF clrBlack)
{
    // Create a memory DC compatible with the display
    HDC sourceDC, destDC;
    BITMAP bm;

    HBITMAP hbmResult;
    HBITMAP hbmOldSource;
    HBITMAP hbmOldDest;
    HBRUSH hbrBack;
    HBRUSH hbrOld;

    XFORM xform;

    float cosine, sine;
    int x1, y1, x2, y2, x3, y3, minx, miny, maxx, maxy, w, h;


    sourceDC = CreateCompatibleDC(hDC);
    destDC = CreateCompatibleDC(hDC);



    // Get logical coordinates
    GetObject(hBitmap, sizeof(bm), &bm);

    cosine = cos(radians);
    sine = sin(radians);



    //회전된 이미지의 영역을 구한다.
    // Compute dimensions of the resulting bitmap
    // First get the coordinates of the 3 corners other than origin
    x1 = (int)(bm.bmHeight * sine);
    y1 = (int)(bm.bmHeight * cosine);
    x2 = (int)(bm.bmWidth * cosine + bm.bmHeight * sine);
    y2 = (int)(bm.bmHeight * cosine - bm.bmWidth * sine);
    x3 = (int)(bm.bmWidth * cosine);
    y3 = (int)(-bm.bmWidth * sine);

    minx = min(0, min(x1, min(x2, x3)));
    miny = min(0, min(y1, min(y2, y3)));
    maxx = max(0, max(x1, max(x2, x3)));
    maxy = max(0, max(y1, max(y2, y3)));

    w = maxx - minx;
    h = maxy - miny;



    // Create a bitmap to hold the result
    hbmResult = CreateCompatibleBitmap(hDC, w, h);

    hbmOldSource = (HBITMAP)SelectObject(sourceDC, hBitmap);
    hbmOldDest = (HBITMAP)SelectObject(destDC, hbmResult);



    // Draw the background color before we change mapping mode
    hbrBack = CreateSolidBrush(clrBlack);
    hbrOld = (HBRUSH)SelectObject(destDC, hbrBack);
    PatBlt(destDC, 0, 0, w, h, PATCOPY);
    DeleteObject(SelectObject(destDC, hbrOld));



    // We will use world transform to rotate the bitmap
    SetGraphicsMode(destDC, GM_ADVANCED);
    xform.eM11 = cosine;
    xform.eM12 = -sine;
    xform.eM21 = sine;
    xform.eM22 = cosine;
    xform.eDx = (float)-minx;
    xform.eDy = (float)-miny;

    SetWorldTransform(destDC, &xform);



    // Now do the actual rotating - a pixel at a time
    BitBlt(destDC, 0, 0, bm.bmWidth, bm.bmHeight, sourceDC, 0, 0, SRCCOPY);



    // Restore DCs
    SelectObject(sourceDC, hbmOldSource);
    SelectObject(destDC, hbmOldDest);

    DeleteDC(sourceDC);
    DeleteDC(destDC);



    return hbmResult;
}
