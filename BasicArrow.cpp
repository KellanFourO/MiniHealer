#include "BasicArrow.h"
#include "BmpMgr.h"
#include "CollisionMgr.h"
#include "ObjMgr.h"

CBasicArrow::CBasicArrow():m_ulDestroyDelay(GetTickCount64())
{
}

CBasicArrow::~CBasicArrow()
{
}

void CBasicArrow::Initialize(void)
{
	m_tInfo.fCX = 64.f;
	m_tInfo.fCY = 64.f;
	m_tStatus.m_iAttack = CObjMgr::Get_Instance()->Get_Ranger()->Get_Attack();
	m_fSpeed = 7.f;

	m_eRender = GAMEOBJECT;
	Setting_Img();
}

int CBasicArrow::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	ChaseTarget();


	__super::Update_Rect();
	return OBJ_NOEVENT;
}

void CBasicArrow::Late_Update(void)
{
	if (CCollisionMgr::AABB_Collision(this, m_pTarget))
	{
		if (m_ulDestroyDelay + 700 < GetTickCount64())
		{
			m_bDead = true;
		}
	}
}

void CBasicArrow::Render(HDC hDC)
{
	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Img(L"BasicArrow");

	GdiTransparentBlt(hDC,
		(int)m_tRect.left, // 복사 받을 위치 X,Y 좌표
		(int)m_tRect.top,
		(int)m_tInfo.fCX,	// 복사 받을 가로, 세로 길이
		(int)m_tInfo.fCY,
		hMemDC,			// 비트맵 이미지를 담고 있는 DC
		(int)m_tInfo.fCX,					// 비트맵을 출력할 시작 X,Y좌표
		(int)m_tInfo.fCY,
		(int)m_tInfo.fCX,		// 출력할 비트맵의 가로, 세로 사이즈
		(int)m_tInfo.fCY,
		RGB(255, 0, 255)); // 제거하고자 하는 색상
}

void CBasicArrow::Release(void)
{
}

void CBasicArrow::Setting_Img()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/Effect/Arrow.bmp", L"BasicArrow");
}

void CBasicArrow::ChaseTarget()
{
	if (m_pTarget->Get_Info().fX < m_tInfo.fX) {
		m_eDir = LEFT;
	}
	else {
		m_eDir = RIGHT;
	}

	float dx = m_pTarget->Get_Info().fX - m_tInfo.fX;
	float dy = m_pTarget->Get_Info().fY - m_tInfo.fY;

	// 플레이어 방향으로 적을 추격
	float distance = std::sqrt(dx * dx + dy * dy);
	float directionX = dx / distance;
	float directionY = dy / distance;

	// 추격 속도에 따라 이동
	float moveX = directionX * m_fSpeed;
	float moveY = directionY * m_fSpeed;

	// 적의 위치 갱신
	m_tInfo.fX += moveX;
	m_tInfo.fY += moveY;
}
