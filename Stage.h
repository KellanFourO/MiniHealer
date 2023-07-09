#pragma once
#include "Scene.h"
#include "Monster.h"
#include "BoneKnight.h"
#include "SelectDoor.h"
#include "Map.h"
#include "Lamb.h"
#include "StageFire.h"

class CStage :
	public CScene
{
public:
	CStage();
	virtual ~CStage();

public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

	list<CObj*>		Get_SelectDoorList() { return m_pSelectDoorList; }

public:
	void		Setting_Img();
private:
	CObj*		m_pMap;
	list<CObj*>	m_pSelectDoorList; // �������� ��(����) ������Ʈ


	CObj*	m_pBoneKnight;


	list<CObj*>	m_pLambList; // �������� ��� ������Ʈ
	list<CObj*> m_pStageFireList; // �������� ��� �� ������Ʈ
	
	
};

