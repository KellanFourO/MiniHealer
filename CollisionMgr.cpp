#include "framework.h"
#include "CollisionMgr.h"


CCollisionMgr::CCollisionMgr()
{
}


CCollisionMgr::~CCollisionMgr()
{
}



void CCollisionMgr::Collision_RectEx(list<CObj*> _Dst, list<CObj*> _Src)
{
	float fX = 0.f, fY = 0.f;


	for (auto& Dst : _Dst)
	{
		for (auto& Src : _Src)
		{
			//if (Check_Rect(Dst, Src, &fX, &fY))
			//{
			//	//// 상하 충돌
			//	//if (fX > fY)
			//	//{
			//	//	// 상 충돌
			//	//	if (Dst->Get_Info().fY < Src->Get_Info().fY)
			//	//	{
			//	//		Dst->Set_PosY(-fY);
			//	//	}
			//	//	// 하 충돌
			//	//	else
			//	//	{
			//	//		Dst->Set_PosY(fY);
			//	//	}
			//	//}
			//}
				// 좌우 충돌
				/*if
				{*/
					// 좌 충돌
					if (Dst->Get_Info().fX < Src->Get_Info().fX)
					{
						Dst->Set_PosX(-fX);
					}
					// 우 충돌
					else
					{
						Dst->Set_PosX(fX);
					}
				}
			}
		}
	//}


bool CCollisionMgr::Check_Rect(CObj* _Dst, CObj* _Src, float* _pX, float* _pY)
{
	float		fWidth = fabs(_Dst->Get_Info().fX - _Src->Get_Info().fX);
	float		fHeight = fabs(_Dst->Get_Info().fY - _Src->Get_Info().fY);

	float		fRadiusX = (_Dst->Get_Info().fCX + _Src->Get_Info().fCX) * 0.5f;
	float		fRadiusY = (_Dst->Get_Info().fCY + _Src->Get_Info().fCY) * 0.5f;

	if ((fRadiusX >= fWidth) && (fRadiusY >= fHeight))
	{
		*_pX = fRadiusX - fWidth;
		*_pY = fRadiusY - fHeight;

		return true;
	}

	return false;
}

bool CCollisionMgr::AABB_Collision(CObj* _Dst, CObj* _Src)
{
	if (_Dst->Get_Rect().right < _Src->Get_Rect().left || _Dst->Get_Rect().left > _Src->Get_Rect().right)
	{
		return false;
	}

	if (_Dst->Get_Rect().bottom < _Src->Get_Rect().top || _Dst->Get_Rect().top > _Src->Get_Rect().bottom)
	{
		return false;
	}
	
	return true;

}

bool CCollisionMgr::AABB_Collision_Weapon(CObj* _Dst, CObj* _Src)
{
	if (_Dst->Get_WeaponRect().right < _Src->Get_Rect().left || _Dst->Get_WeaponRect().left > _Src->Get_Rect().right)
	{
		return false;
	}

	if (_Dst->Get_WeaponRect().bottom < _Src->Get_Rect().top || _Dst->Get_WeaponRect().top > _Src->Get_Rect().bottom)
	{
		return false;
	}

	return true;
}


void CCollisionMgr::Collision_Sphere(list<CObj*> _Dst, list<CObj*> _Src)
{
	for (auto& Dst : _Dst)
	{
		for (auto& Src : _Src)
		{
			if (Check_Sphere(Dst, Src))
			{
				
			}
		}
	}

}

bool CCollisionMgr::Check_Sphere(CObj* _Dst, CObj* _Src)
{
	float	fWidth = abs(_Dst->Get_Info().fX - _Src->Get_Info().fX);
	float	fHeight = _Dst->Get_Info().fY - _Src->Get_Info().fY;

	float	fDiagonal = sqrt(fWidth * fWidth + fHeight * fHeight);

	float	fRadius = (_Dst->Get_Info().fCX + _Src->Get_Info().fCX) * 0.5f;

	return fDiagonal <= fRadius;
}
