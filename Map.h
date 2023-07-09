#pragma once
#include "Obj.h"

class CMap : public CObj
{
public:
	CMap();
	virtual ~CMap();

public:

	virtual void Initialize() override;
	virtual int  Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
	virtual void Setting_Img() override;


public:
	bool	Select_Map();
	void	Set_MapInfo1(float fX, float fY) { m_tMapInfo[0].fX = fX; m_tMapInfo[0].fY = fY; }
	void	Set_MapInfo2(float fX, float fY) { m_tMapInfo[1].fX = fX; m_tMapInfo[1].fY = fY; }

	void	Set_MapInfoSize1(float fCX, float fCY) { m_tMapInfo[0].fCX = fCX; m_tMapInfo[0].fCY = fCY; }
	void	Set_MapInfoSize2(float fCX, float fCY) { m_tMapInfo[1].fCX = fCX; m_tMapInfo[1].fCY = fCY; }


	INFO	Get_MapInfo1() { return m_tMapInfo[0]; }
	INFO	Get_MapInfo2() { return m_tMapInfo[1]; }

private:
	RECT	m_tMapRect[2];
	INFO	m_tMapInfo[2];

};

