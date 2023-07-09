#include "PlayerSKill.h"
#include "KeyMgr.h"
#include "ObjMgr.h"

CPlayerSKill::CPlayerSKill() :m_iSkillNumber(0), m_iMana(0)
, m_ulCastingDelay(GetTickCount64())
, m_fCoolTime(0.f),m_pSkillTarget(nullptr)
{
}

CPlayerSKill::~CPlayerSKill()
{
}

