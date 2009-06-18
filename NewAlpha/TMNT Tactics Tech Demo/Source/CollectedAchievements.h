////////////////////////////////////////////////////////////////
// Filename	: CollectedAchievements.h
// Author	: Jose Sierra(JS)
// Purpose	: The collected achievements of the player
////////////////////////////////////////////////////////////////

#ifndef COLLECTEDACHIEVEMENT_H	
#define COLLECTEDACHIEVEMENT_H

#include "BaseMenuState.h"
#include <windows.h>
#include <iostream>
#include "Player.h"
using namespace std;

class CCollectedAchievements : public CBaseMenuState
{
private:
	CCollectedAchievements(void);
	//Trilogy
	~CCollectedAchievements(void);
	CCollectedAchievements(const CCollectedAchievements&);
	CCollectedAchievements& operator=(const CCollectedAchievements&);
	
	int m_nAlpha[10];
	CPlayer* m_pPlayer;
	RECT m_rRect;

public:
	/////////////////////////////////////////////////////////////////
	//	Function	:	GetInstances
	//
	//	Purpose		:	To Return the instance of the singleton
	////////////////////////////////////////////////////////////////
	static CCollectedAchievements* GetInstance();
	////////////////////////////////////////////////////////////////
	//	Function	:	Render
	//
	//	Purpose		:	Render the collected achievements
	///////////////////////////////////////////////////////////////
	void Render();
	///////////////////////////////////////////////////////////////
	//	Function	:	Input
	//
	//	Purpose		:	Handle the users input
	//////////////////////////////////////////////////////////////
	bool Input(float fElapsedTime, POINT mousePT);
	//////////////////////////////////////////////////////////////
	//	Function	:	Enter
	//
	//	Purpose		:	Set up achievement state
	//////////////////////////////////////////////////////////////
	void Enter();
	//////////////////////////////////////////////////////////////////
	//	Function	:	Exit
	//
	//	Purpose		:	Exit the current state
	///////////////////////////////////////////////////////////////////
	void Exit();
	///////////////////////////////////////////////////////////////////
	// Function : Update
	//
	// Purpose : To update the achievement State
	///////////////////////////////////////////////////////////////////
	void Update(float fElapsedTime);
	

};

#endif