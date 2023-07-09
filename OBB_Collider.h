#pragma once
#include "Define.h"

class COBB_Collider

{
    
public:
    COBB_Collider();
   ~COBB_Collider();

public:
    
    

    bool        OBB_Collision(SHAPE _ShapeA, SHAPE _ShapeB);                // OBB �浹 �˻� �Լ�

    VECTOR      Add_Vector(VECTOR _VectorA, VECTOR _VectorB);               // ���� ���� ����

    VECTOR      Get_DistanceVector(SHAPE _ShapeA, SHAPE _ShapeB);           // �Ÿ� ����

    VECTOR      Get_HeightVector(SHAPE _ShapeA);                            // ���� ����

    VECTOR      Get_WidthVector(SHAPE _ShapeA);                             // �ʺ� ����

    VECTOR      Get_UnitVector(VECTOR _VectorA);                            // ���� ����

    
    double      Get_RectRoot(RECT _Rect) 
    {
        double C = pow(_Rect.left, 2) + pow(_Rect.bottom, 2);
        double rot = sqrt(C);

        return rot;
    }

    double      Abs_DiagonalVector(VECTOR _VectorA, VECTOR _VectorB)        // ���� ���� ���밪
    {
        return abs(_VectorA.x * _VectorB.x + _VectorA.y * _VectorB.y);     
    };
    
    double      DegToRadian(double _Deg)                                    // Degree�� Radian���� ��ȯ
    { 
        return _Deg / 180 * PI; 
    }

};

/*

Add_Vector�� ������ ���� ����
Abs_DiagonalVector�� ������ ������ ���밪

DegToRadian�� degree�� radian���� ��ȯ

Get_DistanceVector�� �Ÿ�����
Get_UnitVector�� ��������
Get_WidthVector�� �ʺ���
Get_HeightVector�� ���̺���


    

*/