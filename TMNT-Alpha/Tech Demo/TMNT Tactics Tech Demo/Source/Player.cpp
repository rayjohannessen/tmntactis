////////////////////////////////////////////////////////
//   File Name	:	"CPlayer.cpp"
//
//   Author		:	Matthew Di Matteo (MD)
//
//   Purpose	:	To provide a game object to be used as the player
//					being controlled by user during the game.
////////////////////////////////////////////////////////

#include "Player.h"
#include "Turtle.h"
#include "Factory.h"
#include "tinyxml/tinyxml.h"
#include "CSGD_TextureManager.h"
#include "Skill.h"
#include <string>
using std::string;

CPlayer::CPlayer(void)
{
	m_pLeonardo = Factory::CreateTurtle();
	m_pDonatello = Factory::CreateTurtle();
	m_pRaphael = Factory::CreateTurtle();
	m_pMikey = Factory::CreateTurtle();

}

CPlayer::~CPlayer(void)
{
}
CPlayer* CPlayer::GetInstance()
{
	static CPlayer instance;
	return &instance;
}


void CPlayer::NewGame()
{
	LoadNewSkills("Resources/XML/VG_TurtleSkills.xml");
	LoadTurtleStats("Resources/XML/VG_TurtleStats.xml");
}

void CPlayer::LoadNewSkills(const char* filename)
{
	TiXmlDocument doc;

	if (!doc.LoadFile(filename))
		{MessageBox(0, "Failed to load new skills.", "Error", MB_OK); return;}

	int type, dmg, range, cost, combAmt, numSkills, turtleID, skillID; string name;
	vector<CSkill> inactiveSkills;

	TiXmlElement* pRoot = doc.RootElement();
	TiXmlElement* pTurtle = pRoot->FirstChildElement("TURTLE");
	while (pTurtle)
	{
		pTurtle->Attribute("NumberOfSkills", &numSkills);
		pTurtle->Attribute("TurtleName", &turtleID);
		TiXmlElement* pSkill;
		pSkill = pTurtle->FirstChildElement("SKILL");
		for (int i = 0; i < numSkills; ++i)
		{
			char* tempName = (char*)pSkill->Attribute("Name");
			name = tempName;
			pSkill->Attribute("ID", &skillID);
			pSkill->Attribute("Type", &type);
			pSkill->Attribute("Dmg", &dmg);
			pSkill->Attribute("Range", &range);
			pSkill->Attribute("Cost", &cost);
			pSkill->Attribute("CombAmt", & combAmt);
			CSkill Skill = CSkill(name, type, skillID, dmg, range, cost, combAmt);
			inactiveSkills.push_back(Skill);
			pSkill = pSkill->NextSiblingElement();
		}

		switch (turtleID)
		{
		case DONATELLO:
			m_pDonatello->SetSkillsInactive(inactiveSkills);
			break;
		case LEONARDO:
			m_pLeonardo->SetSkillsInactive(inactiveSkills);
			break;
		case RAPHAEL:
			m_pRaphael->SetSkillsInactive(inactiveSkills);
			break;
		case MIKEY:
			m_pMikey->SetSkillsInactive(inactiveSkills);
			break;
		}
		inactiveSkills.clear();
		pTurtle = pTurtle->NextSiblingElement("TURTLE");
	}
}
bool CPlayer::LoadTurtleStats(const char* szXmlFileName)
{
	TiXmlDocument doc;
	int ap = 0, hp = 0, strength = 0, defense = 0, accuracy = 0, speed = 0, level = 0, experience = 0, range = 0;

	if(!doc.LoadFile(szXmlFileName))
		{MessageBox(0, "Failed to load turtle stats.", "Error",  MB_OK);return false;}

	TiXmlElement* pRoot = doc.RootElement();
	TiXmlElement* pLeo = pRoot->FirstChildElement("Leonardo");

	if(pLeo)
	{

		pLeo->Attribute("AP", &ap);
		pLeo->Attribute("HP", &hp);
		pLeo->Attribute("strength", &strength);
		pLeo->Attribute("defense", &defense);
		pLeo->Attribute("accuracy", &accuracy);
		pLeo->Attribute("speed", &speed);
		pLeo->Attribute("level", &level);
		pLeo->Attribute("exp", &experience);
		pLeo->Attribute("range", &range);

		m_pLeonardo->SetAttributes(ap,hp,strength,defense,accuracy,speed,level,experience,range);

	}
	TiXmlElement* pRaph = pLeo->NextSiblingElement("Raphael");
	if(pRaph)
	{
		pRaph->Attribute("AP", &ap);
		pRaph->Attribute("HP", &hp);
		pRaph->Attribute("strength", &strength);
		pRaph->Attribute("defense", &defense);
		pRaph->Attribute("accuracy", &accuracy);
		pRaph->Attribute("speed", &speed);
		pRaph->Attribute("level", &level);
		pRaph->Attribute("exp", &experience);
		pRaph->Attribute("range", &range);

		m_pRaphael->SetAttributes(ap,hp,strength,defense,accuracy,speed,level,experience,range);

	}
	TiXmlElement* pDon = pRaph->NextSiblingElement("Donatello");
	if(pDon)
	{
		pDon->Attribute("AP", &ap);
		pDon->Attribute("HP", &hp);
		pDon->Attribute("strength", &strength);
		pDon->Attribute("defense", &defense);
		pDon->Attribute("accuracy", &accuracy);
		pDon->Attribute("speed", &speed);
		pDon->Attribute("level", &level);
		pDon->Attribute("exp", &experience);
		pDon->Attribute("range", &range);

		m_pDonatello->SetAttributes(ap,hp,strength,defense,accuracy,speed,level,experience,range);

	}
	
	TiXmlElement* pMikey = pDon->NextSiblingElement("Michelangelo");
	if(pMikey)
	{
		pMikey->Attribute("AP", &ap);
		pMikey->Attribute("HP", &hp);
		pMikey->Attribute("strength", &strength);
		pMikey->Attribute("defense", &defense);
		pMikey->Attribute("accuracy", &accuracy);
		pMikey->Attribute("speed", &speed);
		pMikey->Attribute("level", &level);
		pMikey->Attribute("exp", &experience);
		pMikey->Attribute("range", &range);

		m_pMikey->SetAttributes(ap,hp,strength,defense,accuracy,speed,level,experience,range);

	}
	return true;
}