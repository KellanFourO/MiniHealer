#include "OBB_Collider.h"



bool COBB_Collider::OBB_Collision(SHAPE _ShapeA, SHAPE _ShapeB)
{
	VECTOR Vector_Distance = Get_DistanceVector(_ShapeA, _ShapeB);
	VECTOR Vector_Total[4] = 
	{ 
		Get_HeightVector (_ShapeA), // 꼭지점 A의 높이 
		Get_HeightVector (_ShapeB), // 꼭지점 B의 높이
		Get_WidthVector  (_ShapeA),  // 꼭지점 A의 너비
		Get_WidthVector  (_ShapeB)   // 꼭지점 B의 너비
	};

	VECTOR Vector_Unit;

	for (int i = 0; i < 4; ++i)
	{
		double dSum = 0;
		Vector_Unit = Get_UnitVector(Vector_Total[i]);
		
		for (int j = 0; j < 4; ++j)
		{
			dSum += Abs_DiagonalVector(Vector_Total[j], Vector_Unit);
		}
		
		if (Abs_DiagonalVector(Vector_Distance, Vector_Unit) > dSum)
			return false;
	}

	return true;
}

VECTOR COBB_Collider::Add_Vector(VECTOR _VectorA, VECTOR _VectorB)
{
	VECTOR Vector_Result;

	Vector_Result.x = _VectorA.x + _VectorB.x;
	Vector_Result.y = _VectorA.y + _VectorB.y;
	
	return Vector_Result;
}

VECTOR COBB_Collider::Get_DistanceVector(SHAPE _ShapeA, SHAPE _ShapeB)
{
	VECTOR Vector_Result;

	Vector_Result.x = ( (_ShapeA.left + _ShapeA.width) * 0.5f) - ( (_ShapeB.left + _ShapeB.width) * 0.5f);
	Vector_Result.y = ( (_ShapeA.top + _ShapeA.height) * 0.5f) - ( (_ShapeB.top + _ShapeB.height) * 0.5f);

	return Vector_Result;
}

VECTOR COBB_Collider::Get_HeightVector(SHAPE _ShapeA)
{
	VECTOR Vector_Result;

	Vector_Result.x = _ShapeA.height * cosf(DegToRadian(_ShapeA.rot - 90) )* 0.5;
	Vector_Result.y = _ShapeA.height * sinf(DegToRadian(_ShapeA.rot - 90)) * 0.5;

	return Vector_Result;
}

VECTOR COBB_Collider::Get_WidthVector(SHAPE _ShapeA)
{
	VECTOR Vector_Result;

	Vector_Result.x = _ShapeA.width * cosf( DegToRadian(_ShapeA.rot) ) * 0.5;	
	Vector_Result.y	= _ShapeA.width	* sinf( DegToRadian(_ShapeA.rot) ) * 0.5;

	return Vector_Result;
}

VECTOR COBB_Collider::Get_UnitVector(VECTOR _VectorA)
{
	VECTOR Vector_Result;
	double dSize;

	dSize = sqrt( pow(_VectorA.x, 2) + pow(_VectorA.y, 2) );

	Vector_Result.x = _VectorA.x / dSize;
	Vector_Result.y	= _VectorA.y / dSize;

	return Vector_Result;
}

COBB_Collider::COBB_Collider()
{
}

COBB_Collider::~COBB_Collider()
{
}
