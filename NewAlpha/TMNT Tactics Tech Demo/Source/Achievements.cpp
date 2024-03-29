#include "Achievements.h"
#include "CSGD_TextureManager.h"
#include "Assets.h"
#include "CSGD_Direct3D.h"
#include "BattleMap.h"
#include "Game.h"
#include "CSGD_FModManager.h"

CAchievements::CAchievements()
{
	m_pTM = CSGD_TextureManager::GetInstance();
	m_pAssets = CAssets::GetInstance();
	m_pD3D = CSGD_Direct3D::GetInstance();
	m_fTimer = 0.0f;
	SetToLocked();
	m_nImageWidth = 422; m_nImageHeight = 68;
	m_pAcheivements[ACH_NEWGAME].imageID =			m_pAssets->aPartyTime;		// DONE
	m_pAcheivements[ACH_LVLUP].imageID =			m_pAssets->aCowabunga;		// DONE
	m_pAcheivements[ACH_TURTLESDEAD].imageID =		m_pAssets->aFlipNow;		// DONE
	m_pAcheivements[ACH_ALLUNLOCKED].imageID =		m_pAssets->aBreakGame;		// DONE
	m_pAcheivements[ACH_FIRSTMAPCOMPLETE].imageID = m_pAssets->aStrikeHard;		// DONE
	m_pAcheivements[ACH_KILL30].imageID =			m_pAssets->aLessonInPain;	// DONE
	m_pAcheivements[ACH_MEGAKILL].imageID =			m_pAssets->aMegaKill;		// DONE
	m_pAcheivements[ACH_KILL_SHREDDER].imageID=		m_pAssets->aAvenged;		// DONE
	m_pAcheivements[ACH_UNLOCKSKILLS].imageID =		m_pAssets->aTrueNinja;		// DONE
	m_pAcheivements[ACH_QUICKFINGERS].imageID =		m_pAssets->aQuickFingers;	// DONE

	m_pAcheivements[ACH_NEWGAME].title =		"PARTY TIME";
	m_pAcheivements[ACH_LVLUP].title =			"COWABUNGA";
	m_pAcheivements[ACH_TURTLESDEAD].title =	"FLIPS NOW";
	m_pAcheivements[ACH_ALLUNLOCKED].title =	"YOU'RE GONNA BREAK THE GAME";
	m_pAcheivements[ACH_FIRSTMAPCOMPLETE].title = "STRIKE HARD AND FADE AWAY";
	m_pAcheivements[ACH_KILL30].title =			"A LESSON IN PAIN";
	m_pAcheivements[ACH_MEGAKILL].title =		"MEGA KILL";
	m_pAcheivements[ACH_KILL_SHREDDER].title =	"AVENGED";
	m_pAcheivements[ACH_UNLOCKSKILLS].title =	"TRUE NINJA";
	m_pAcheivements[ACH_QUICKFINGERS].title =	"QUICK FINGERS";

	m_pAcheivements[ACH_NEWGAME].description =			"Started a new game!";
	m_pAcheivements[ACH_LVLUP].description =			"First turtle leveled up.";
	m_pAcheivements[ACH_TURTLESDEAD].description =		"All turtles dead...good job.";
	m_pAcheivements[ACH_ALLUNLOCKED].description =		"All achievements unlocked.";
	m_pAcheivements[ACH_FIRSTMAPCOMPLETE].description = "First victory in a battle!";
	m_pAcheivements[ACH_KILL30].description =			"Killed 30 enemies!";
	m_pAcheivements[ACH_MEGAKILL].description =			"One turtle killed 3 enemies on a map!";
	m_pAcheivements[ACH_KILL_SHREDDER].description =	"Shredder has been defeated.";
	m_pAcheivements[ACH_UNLOCKSKILLS].description =		"All skills unlocked.";
	m_pAcheivements[ACH_QUICKFINGERS].description =		"A perfect skill execution.";
}

CAchievements::~CAchievements()
{
	m_pTM = NULL;
	m_pAssets = NULL;
	m_pD3D = NULL;
}

void CAchievements::Update(float fElapsedTime)
{
	if (m_nCurrUnlocked > -1)
	{
		if (m_fTimer == 0.0f)
			CBattleMap::GetInstance()->PlaySFX(m_pAssets->aBMpickupSnd);
		m_fTimer += fElapsedTime;
	}
}

bool CAchievements::Render()
{
	// only renders something if an achievement has recently been unlocked
	if (m_nCurrUnlocked > -1)
	{
		if (m_fTimer < 3.0f)
		{
			// display achievement image
			int centerX;//, centerY;
			centerX = ((CGame::GetInstance()->GetScreenWidth()>>1)-(m_nImageWidth>>1));
			//centerY = ((CGame::GetInstance()->GetScreenHeight()>>1)-(m_nImageHeight>>1));
			m_pTM->DrawWithZSort(m_pAcheivements[m_nCurrUnlocked].imageID, centerX, 650/*centerY*/, 0.0f);
			return true;
		}
		else
		{m_fTimer = 0.0f; m_nCurrUnlocked=-1;}
	}
	return false;
}

void CAchievements::LoadUnlock(int id)
{
	m_pAcheivements[id].bUnlocked = true;
	m_nCurrUnlocked = -1;
	m_nUnlockCount++;
}

void CAchievements::SetToLocked()
{
	for (int i = 0; i < 10; ++i)
		m_pAcheivements[i].bUnlocked = false;
	m_nCurrUnlocked = -1;
	m_nUnlockCount = 0;
}


void CAchievements::Unlock(int id)
{
	m_pAcheivements[id].bUnlocked = true;
	m_nCurrUnlocked = id;
	if (id == ACH_FIRSTMAPCOMPLETE)
		CBattleMap::GetInstance()->PlaySFX(m_pAssets->aStrikeHardSnd);
	else if (id == ACH_KILL30)
		CBattleMap::GetInstance()->PlaySFX(m_pAssets->aLessonInPainSnd);
	else if (id == ACH_KILL_SHREDDER)
		CBattleMap::GetInstance()->PlaySFX(m_pAssets->aBMwillBeOthersSnd);
	else if (id == ACH_MEGAKILL)
		CBattleMap::GetInstance()->PlaySFX(m_pAssets->aMegaKillSnd);
	else if (id == ACH_QUICKFINGERS)
		CBattleMap::GetInstance()->PlaySFX(m_pAssets->aQuickFingersSnd);
	++m_nUnlockCount;
	if (m_nUnlockCount == 10)
		m_pAcheivements[ACH_ALLUNLOCKED].bUnlocked = true;
}