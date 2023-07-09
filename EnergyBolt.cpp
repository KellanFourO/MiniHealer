#include "EnergyBolt.h"
#include "BmpMgr.h"
#include "CollisionMgr.h"
#include "ObjMgr.h"

CEnergyBolt::CEnergyBolt():m_ulDestroyDelay(GetTickCount64()),m_iEnergyBoltStart(0),m_iEnergyBoltEnd(0)
{
}

CEnergyBolt::~CEnergyBolt()
{
}

void CEnergyBolt::Initialize(void)
{
	m_tInfo.fCX = 64.f;
	m_tInfo.fCY = 64.f;
	m_tStatus.m_iAttack = CObjMgr::Get_Instance()->Get_Player()->Get_Attack();
	m_fSpeed = 5.f;
	
	m_tFrame.iMotion = 7;
	m_iEnergyBoltStart = 0;
	m_iEnergyBoltEnd = 7;
	m_tFrame.dwSpeed = 50.f;

	m_eRender = GAMEOBJECT;
	Setting_Img();
}

int CEnergyBolt::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	ChaseTarget();
	

	__super::Update_Rect();
	return OBJ_NOEVENT;
}

void CEnergyBolt::Late_Update(void)
{
	if (CCollisionMgr::AABB_Collision(this, m_pTarget))
	{
		if (m_ulDestroyDelay + m_tFrame.dwSpeed < GetTickCount64())
		{
			if(m_iEnergyBoltStart < m_iEnergyBoltEnd)
				++m_iEnergyBoltStart;
			else 
				m_bDead = true;
			

			m_ulDestroyDelay = GetTickCount64();
		}
	}
}

void CEnergyBolt::Render(HDC hDC)
{
	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Img(L"EnergyBolt");
	
	GdiTransparentBlt(hDC,
		(int)m_tRect.left, // ���� ���� ��ġ X,Y ��ǥ
		(int)m_tRect.top,
		(int)m_tInfo.fCX,	// ���� ���� ����, ���� ����
		(int)m_tInfo.fCY,
		hMemDC,			// ��Ʈ�� �̹����� ��� �ִ� DC
		m_iEnergyBoltStart * (int)m_tInfo.fCX,					// ��Ʈ���� ����� ���� X,Y��ǥ
		m_tFrame.iMotion * (int)m_tInfo.fCY,
		(int)m_tInfo.fCX,		// ����� ��Ʈ���� ����, ���� ������
		(int)m_tInfo.fCY,
		RGB(255, 0, 255)); // �����ϰ��� �ϴ� ����
}

void CEnergyBolt::Release(void)
{
}

void CEnergyBolt::Setting_Img()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"./Image/Effect/EnergyBolt.bmp", L"EnergyBolt");
}

void CEnergyBolt::ChaseTarget()
{
	
	if (m_pTarget->Get_Info().fX < m_tInfo.fX) {
		m_eDir = LEFT;
	}
	else {
		m_eDir = RIGHT;
	}

	float dx = m_pTarget->Get_Info().fX - m_tInfo.fX;
	float dy = m_pTarget->Get_Info().fY - m_tInfo.fY;

	// �÷��̾� �������� ���� �߰�
	float distance = std::sqrt(dx * dx + dy * dy);
	float directionX = dx / distance;
	float directionY = dy / distance;

	// �߰� �ӵ��� ���� �̵�
	float moveX = directionX * m_fSpeed;
	float moveY = directionY * m_fSpeed;

	// ���� ��ġ ����
	m_tInfo.fX += moveX;
	m_tInfo.fY += moveY;
}
