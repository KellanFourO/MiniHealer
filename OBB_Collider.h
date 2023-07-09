#pragma once
#include "Define.h"

class COBB_Collider

{
    
public:
    COBB_Collider();
   ~COBB_Collider();

public:
    
    

    bool        OBB_Collision(SHAPE _ShapeA, SHAPE _ShapeB);                // OBB 충돌 검사 함수

    VECTOR      Add_Vector(VECTOR _VectorA, VECTOR _VectorB);               // 벡터 덧셈 연산

    VECTOR      Get_DistanceVector(SHAPE _ShapeA, SHAPE _ShapeB);           // 거리 벡터

    VECTOR      Get_HeightVector(SHAPE _ShapeA);                            // 높이 벡터

    VECTOR      Get_WidthVector(SHAPE _ShapeA);                             // 너비 벡터

    VECTOR      Get_UnitVector(VECTOR _VectorA);                            // 단위 벡터

    
    double      Get_RectRoot(RECT _Rect) 
    {
        double C = pow(_Rect.left, 2) + pow(_Rect.bottom, 2);
        double rot = sqrt(C);

        return rot;
    }

    double      Abs_DiagonalVector(VECTOR _VectorA, VECTOR _VectorB)        // 벡터 내적 절대값
    {
        return abs(_VectorA.x * _VectorB.x + _VectorA.y * _VectorB.y);     
    };
    
    double      DegToRadian(double _Deg)                                    // Degree를 Radian으로 변환
    { 
        return _Deg / 180 * PI; 
    }

};

/*

Add_Vector는 벡터의 덧셈 연산
Abs_DiagonalVector는 벡터의 내적의 절대값

DegToRadian은 degree를 radian으로 변환

Get_DistanceVector는 거리벡터
Get_UnitVector는 단위벡터
Get_WidthVector는 너비벡터
Get_HeightVector는 높이벡터


    

*/