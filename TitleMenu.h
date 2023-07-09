#pragma once

#include "Scene.h"

class CTitleMenu : public CScene
{
public:
	CTitleMenu();
	virtual ~CTitleMenu();

public:
	virtual void Initialize()		override;
	virtual void Update()			override;
	virtual void Late_Update()		override;
	virtual void Render(HDC hDC)	override;
	virtual void Release()			override;

private:
	
	bool	m_bSceneChange;
	ULONGLONG   m_dwStartDelay;
};

