#pragma once
#include "Scene.h"
class CMyEdit : public CScene
{
public:
	CMyEdit();
	virtual ~CMyEdit();

public:
	// CScene을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

public:
	void		Save_Tile(void);

private:
	void	Key_Input(void);
};

