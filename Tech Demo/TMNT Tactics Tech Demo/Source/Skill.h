////////////////////////////////////////////////////////
//   File Name	:	"Skill.h"
//
//   Author		:	Matthew Di Matteo (MD)
//
//   Purpose	:	To provide the player with a skill 
//					to deal more damage to the opponent
////////////////////////////////////////////////////////

#ifndef SKILL_H
#define SKILL_H



enum {SKILL_DAMAGE, SKILL_HEAL, SKILL_CREATE, };

class CBaseSkill
{
private:
	char* m_szName;		// The name of the skill
	int m_nType;		// what type of skill: e.g. Damage, Healing, Creation
	int m_nDamage;
	int m_nRange;
	int m_nSkillCost;
	int	m_nCurrAmountSuccessful;
	int m_nMaxCombinationAmount;
	CBaseSkill()
	{
		m_szName = "";
		m_nType = -1;
		m_nDamage = 0;
		m_nRange = 0;
		m_nCurrAmountSuccessful = -1;
		m_nMaxCombinationAmount = 0;
		m_nSkillCost = 0;
	}
	CBaseSkill(char* name, int type, int dmg, int range, int cost, int combAmt)
	{
		m_szName = name;
		m_nType = type;
		m_nDamage = dmg;
		m_nRange = range;
		m_nSkillCost = cost;
		m_nMaxCombinationAmount = combAmt;
	}
};

class CKnockbackSkill : public CBaseSkill
{
	CKnockbackSkill() : CBaseSkill("Knockback", SKILL_DAMAGE, 0, 0, 0, 0);


};

#endif