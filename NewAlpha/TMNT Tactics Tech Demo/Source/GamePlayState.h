//////////////////////////////////////////////////////////////////////////
//	Filename	:	GamePlayState.h
//
//	Author		:	Ramon Johannessen (RJ)
//
//	Purpose		:	To define the CGamePlayState class. This state handles
//					all gameplay code.
//////////////////////////////////////////////////////////////////////////
#ifndef GAMEPLAYSTATE_H
#define GAMEPLAYSTATE_H

#include "IGameState.h"
#include "BattleMap.h"

enum {MAP_WORLD, MAP_BATTLE, MAP_NULL };

class CBaseMenuState;
class CBaseMenuState;
class CAnimation;
class CPlayer;
class CHUD;
class CWorldMap;

class CGamePlayState : public IGameState
{
private:
// 	struct Acheivement 
// 	{
// 		bool bUnlocked;
// 		int imageID;
// 		string title;
// 		char* description;
// 	};
	CBaseMenuState* m_pCurrentMenuState;
	CBattleMap*		m_pBattleMap;
	CPlayer*		m_pPlayer;
	CHUD*			m_pHUD;
	CWorldMap*		m_pWorldMap;

	bool m_bChangingMap;
	float m_fTimer;

	bool m_bIsPaused;

	int m_nCurrentMap;
	int m_nMapID;	
	bool m_bIsOnWorldMap;

	// Constructor
	CGamePlayState(void);
	// Copy Constructor
	CGamePlayState(const CGamePlayState&);
	// Assignment Operator
	CGamePlayState& operator=(const CGamePlayState&);
	//Destructor
	~CGamePlayState(void);
public:
	///////////////////////////////////////////////////////////////////
	//	Function: GetInstance
	//
	//	Purpose: Init the instance and return a pointer to the instance
	///////////////////////////////////////////////////////////////////
	static CGamePlayState* GetInstance(void);
  
	inline bool GetPaused(){return m_bIsPaused;}
	inline void SetPaused(bool p){m_bIsPaused = p;}

	//////////////////////////////////////////////////////////////////////////
	//	Function: ChangeMap
	//
	//	Purpose : to change from one map to another...e.g., going into a battle
	//				from the world map
	//////////////////////////////////////////////////////////////////////////
	void ChangeMap(bool bWorldMap = true, int mapID = 0 /*LOC_SIMUSA*/);

	///////////////////////////////////////////////////////////////////
	//	Function:	Enter
	//
	//	Purpose:	Enter and initialize the current state
	//////////////////////////////////////////////////////////////////
	void Enter(void);
	//////////////////////////////////////////////////////////////////
	//	Function: Exit
	//
	//	Purpose: Cleans up all the state info
	///////////////////////////////////////////////////////////////////
	void Exit(void);
	///////////////////////////////////////////////////////////////////
	//	Function: Input
	//
	//	Purpose: Read the input from the user
	/////////////////////////////////////////////////////////////////
	bool Input(float, POINT);
	/////////////////////////////////////////////////////////////////
	//	Function:	Update
	//
	//	Purpose:	Update the state objects
	////////////////////////////////////////////////////////////////
	void Update(float fElapsedTime);
	////////////////////////////////////////////////////////////////
	//	Function:	Render
	//
	//	Purpose:	Render the objects of the state
	////////////////////////////////////////////////////////////////
	void Render(void);
	////////////////////////////////////////////////////////////////
	//	Function:	SaveGame
	//
	//	Purpose:	Saves the current game to a binary file
	////////////////////////////////////////////////////////////////
	void SaveGame(const char* fileName);
	////////////////////////////////////////////////////////////////
	//	Function:	LoadGame
	//
	//	Purpose:	Loads the selected game from a binary file
	////////////////////////////////////////////////////////////////
	void LoadGame(const char* fileName);
	////////////////////////////////////////////////////////////////
	//	Function:	MessageProc
	//
	//	Purpose:	Retrieves and handles the messages
	////////////////////////////////////////////////////////////////
	//static friend void MessageProc(CBaseMessage* pMsg);
};
#endif