#include "Npc.h"
#include "ObjMgr.h"
#include "KeyMgr.h"
#include "SceneMgr.h"
#include <ctime>

CNpc::CNpc() :m_fMoveDistance(0.f), m_dwNpcMoveDelay(0), m_bMoveSwitch(true),
m_eHealerCur(HEALERSTATEID::IDLE),m_eHealerPre(HEALERSTATEID::HEALSTATE_END),
m_eRangerCur(RANGERSTATEID::IDLE),m_eRangerPre(RANGERSTATEID::RANGSTATE_END),
m_eBerserCur(BERSERKERSTATEID::IDLE),m_eBerserPre(BERSERKERSTATEID::BERSSTATE_END),
m_eTankerCur(TANKERSTATEID::IDLE),m_eTankerPre(TANKERSTATEID::TANKSTATE_END),
m_iAttackCount(0),m_ulAttackCountDelay(GetTickCount64()),
m_ulHpRecoveryDelay(GetTickCount64()),m_ulMpRecoveryDelay(GetTickCount64())
{
	srand(unsigned(time(NULL)));
}

CNpc::~CNpc()
{
}


void CNpc::Start_Target()
{
	if (CObjMgr::Get_Instance()->Get_Objects(BOSS).empty())
		return;
	
	m_pTarget = CSceneMgr::Get_Instance()->Get_Field()->Get_Target();
	
	m_bFieldSwitch = false;
}

void CNpc::Target_Change()
{
	if (!CObjMgr::Get_Instance()->Get_Objects(MONSTER).empty())
	{
		for (auto& iter : CObjMgr::Get_Instance()->Get_Objects(MONSTER))
		{
			if (CObjMgr::Get_Instance()->Get_Player()->Get_Info().fX < iter->Get_Info().fX
				|| CObjMgr::Get_Instance()->Get_Player()->Get_Info().fX > iter->Get_Info().fX)
			{
				if (m_pTarget == iter)
					continue;
				else
					m_pTarget = iter;
			}
		}
	}
	
	else
		m_pTarget = CSceneMgr::Get_Instance()->Get_Field()->Get_Target();
	
}

void CNpc::Chase_Attack()
{
	if (m_pTarget)
	{
		m_eDir = RIGHT;
		if (m_pTarget->Get_Info().fX > m_tInfo.fX + m_fDistance)
		{
			if (m_pName == L"탱커")
			{

				m_tInfo.fX += m_fSpeed;
				m_eTankerCur = TANKERSTATEID::WALK;
				m_pFrameKey = L"TankerWalkA";
			}
			
			else if (m_pName == L"버서커")
			{
				m_tInfo.fX += m_fSpeed;
				m_eBerserCur = BERSERKERSTATEID::WALK;
				m_pFrameKey = L"BerserkerWalkA";
			}

			else if (m_pName == L"힐러")
			{
				m_tInfo.fX += m_fSpeed;
				m_eHealerCur = HEALERSTATEID::WALK;
				m_pFrameKey = L"HealerWalkA";
			}

			else if (m_pName == L"레인저")
			{
				m_tInfo.fX += m_fSpeed;
				m_eRangerCur = RANGERSTATEID::WALK;
				m_pFrameKey = L"RangerWalkA";
			}
		}

		else
		{
			if (m_pName == L"탱커")
			{
				m_eTankerCur = TANKERSTATEID::ATTACK;
				m_pFrameKey = L"TankerAtk";
			}
			else if (m_pName == L"버서커")
			{
				m_eBerserCur = BERSERKERSTATEID::ATTACK;
				m_pFrameKey = L"BerserkerAtk";
			}
			else if (m_pName == L"힐러")
			{
				m_eHealerCur = HEALERSTATEID::ATTACK;
				m_pFrameKey = L"HealerAtk";
			}
			else if (m_pName == L"레인저")
			{
				m_eRangerCur = RANGERSTATEID::ATTACK;
				m_pFrameKey = L"RangerAtk";
			}

		}
	}
	

	/*
		보스가 사정거리 안의 들어왔을 시에 행동 작성
		

		 
		
	
	*/
}

void CNpc::AI_Target()
{
	m_pTarget = CObjMgr::Get_Instance()->Get_Player()->Get_Target();
}

void CNpc::Recovery()
{
		if (m_bDead)
			return;
	
	if (m_tStatus.m_iHp < m_tStatus.m_iMaxHp)
	{
		if (m_ulHpRecoveryDelay + 1500 < GetTickCount64())
		{
			if (m_tStatus.m_iHp + m_tStatus.m_iHpRecovery < m_tStatus.m_iMaxHp)
				m_tStatus.m_iHp += m_tStatus.m_iHpRecovery;
			else
				m_tStatus.m_iHp = m_tStatus.m_iMaxHp;
			m_ulHpRecoveryDelay = GetTickCount64();
		}
	}


	if (m_tStatus.m_iMp < m_tStatus.m_iMaxMp)
	{
		if (m_ulMpRecoveryDelay + 500 < GetTickCount64())
		{
			if (m_tStatus.m_iMp + m_tStatus.m_iMpRecovery < m_tStatus.m_iMaxMp)
				m_tStatus.m_iMp += m_tStatus.m_iMpRecovery;
			else
				m_tStatus.m_iMp = m_tStatus.m_iMaxMp;
			
			m_ulMpRecoveryDelay = GetTickCount64();
		}
	}

}


