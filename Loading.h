#pragma once
#include "Scene.h"
class CLoading :
    public CScene
{
public:
             CLoading();
    virtual ~CLoading();

public:


    // CScene��(��) ���� ��ӵ�
    virtual void Initialize() override;

    virtual void Update() override;

    virtual void Late_Update() override;

    virtual void Render(HDC hDC) override;

    virtual void Release() override;

};

