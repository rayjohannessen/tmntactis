//////////////////////////////////////////////////////////////////////////
//	Filename	:	CBattleMap.h
//
//	Author		:	Ramon Johannessen (RJ)
//
//	Purpose		:	To execute the individual battles that take place,
//					drawing the isometric tile map, updating, getting input, etc...
//////////////////////////////////////////////////////////////////////////
#ifndef BATTLEMAP_H
#define BATTLEMAP_H

#include <windows.h>
#include "Base.h"
#include <vector>
using std::vector;
#include <iostream>
using namespace std;

class CSGD_TextureManager;
class CSGD_DirectInput;
class CSGD_Direct3D;
class CGame;
class CAssets;
class CBitmapFont;
class CTile;
class CFreeTile;
class CAnimation;
class CParticleSystem;
class CCamera;
class CHUD;
class CPlayer;
class CNinja;
class CBox;

 // enum for tile flags
 enum {FLAG_NONE, FLAG_COLLISION, FLAG_OBJECT_EDGE, };
 enum {MOVE_MINUS_Y, MOVE_MINUS_X, MOVE_ADD_Y, MOVE_ADD_X, };

#include "Base.h"

 struct MY_POINT 
 {
	 int x;
	 int y;
 };
class CBattleMap
{
	struct sTileset 
	{
		string name;
		int id;
	};
	// characters, by default, render behind the OBJECTS layer (CHARACTER_BEHIND)
	struct DEPTH
	{
		float GROUND;
		float GROUNDL2;
		float SELECTION;
		float CHARACTER_BEHIND;
		float CHARACTER_AHEAD;
		float OBJECTS;
		float ARROW;
		float MENUS;
		DEPTH()
		{
			GROUND = 1.0f;
			GROUNDL2 = 0.9f;
			SELECTION = 0.8f;
			CHARACTER_BEHIND = 0.7f;
			OBJECTS = 0.6f;
			CHARACTER_AHEAD = 0.5f;
			ARROW = 0.49f;
			MENUS = 0.11f;
		}
	};
	POINT m_ptMouseScreenCoord;	// the mouse location, updated each Update() call
	int m_nCurrMousePtr;
	DEPTH depth;				// struct that holds all the z-depth draw values
	string m_strCurrVersion;

	// button selection
	int m_nCurrBtnSelected;
	bool m_bDisplaySpecialBox;
	bool m_bDisplayItemBox;
	CBox* m_bxActionBox;
	CBox* m_bxSkillBox;
	CBox* m_bxItemBox;

	// Times
	float m_fTimer;
	bool m_bNotEnoughAP;
	bool m_bOutOfRange;
	bool m_bExecuteSkill;

	// Map variables
	int m_nMapWidth;
	int m_nMapHeight;
	int m_nNumCols;
	int m_nNumRows;
	int m_nTileWidth;
	int m_nTileHeight;
	int m_nTotalNumTiles;
	int m_nCurrSelectedTile;	// where the mouse cursor is at on the map
	int m_nCurrMouseTileTarget;

	int m_nScrenWidth;
	int m_nScreenHeight;
	int m_nIsoCenterLeftY;
	int m_nIsoCenterTopX; 
	int m_nFreeTileCount;
	int m_nOffsetX;
	int m_nOffsetY;
	int m_nFreeTileOSx;
	int m_nfreeTileOSy;
	float m_fScrollX;
	float m_fScrollY;

	char* m_szMapName;
	char* m_szFileName;

	CTile* m_pTilesL1;			// all tiles on the map, used for drawing first layer
	CTile* m_pTilesL2;			// all tiles on the map, used for drawing first layer
	//CTile* m_pMoveableTiles;	// the open tiles, used for collision checking
	CFreeTile* m_pFreeTiles;
	sTileset m_pTilesets[4];	// keep track of the tileset info (struct)

	// Character variables
	CPlayer*	m_pPlayer;	// the player singleton pointer
	bool m_bIsMouseAttack;
	int m_nNumEnemiesLeft;
	int m_nNumEnemiesKilled;
	int m_nNumCharacters;
	int m_nHoverCharacter;
	int m_nOldHoverChar;
	int m_nCurrCharacter;
	int m_nCurrCharacterTile;
	int m_nCurrTarget;
	int m_ncurrTargetTile;
	int m_nDistanceToTarget;
	int m_nMoveDirection;
	int m_nCurrSkillCost;
	string m_sCurrSkillName;
	string m_sCurrSkillDisplay;
	vector<CBase> m_vCharacters; // all player characters that are on the current battle map
	vector<CBase*> m_vEnemies;	 // all enemy characters that are on the current battle map

	//////////////////////////////////////////////////////////////////////////
	//	Turn variables
	bool m_bIsPlayersTurn;

	// temp particles
	CParticleSystem* m_pParticleSys;
	// temp ninja

	//////////////////////////////////////////////////////////////////////////
	// Pointers to singletons
	CAssets*			m_pAssets;
	CSGD_TextureManager* m_pTM;
	CSGD_Direct3D*		m_pD3D;
	CSGD_DirectInput*	m_pDI;
	CGame*				m_pGame;
	CCamera*			m_pCamera;
	CBitmapFont*		m_pBitmapFont;
	CHUD*				m_pHUD;
	//FMOD::System*		m_pFMODsys;
	//////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////
	//	Function	:	Reset
	//
	//	Purpose		:	Resets all variables and gets ready for another level
	//					to be made
	//////////////////////////////////////////////////////////////////////////
	void Reset();
	//////////////////////////////////////////////////////////////////////////
	//	Function	:	CreateEnemies
	//
	//	Purpose		:	Make and place the m_nNumEnemiesLeft amount of enemies
	//					to the battle map
	//////////////////////////////////////////////////////////////////////////
	void CreateEnemies();
	//////////////////////////////////////////////////////////////////////////
	//	Function	:	LoadMapInfo
	//
	//	Purpose		:	Load in the new map, set up all of the members
	//////////////////////////////////////////////////////////////////////////
	void LoadMapInfo();
	//////////////////////////////////////////////////////////////////////////
	//	Function	:	IsoTilePlot
	//
	//	Purpose		:	Determines at which pixel on the screen the given map
	//					ID (xID, yID = pt.x, pt.y) should be drawn
	//
	//	Return		:	The pixel point to draw at
	//////////////////////////////////////////////////////////////////////////
	MY_POINT IsoTilePlot(MY_POINT pt, int xOffset, int yOffset);

	//////////////////////////////////////////////////////////////////////////
	//	Function	:	"IsMousePosValid"
	//
	//	Purpose		:	Determines if the user has clicked on a valid object
	//					to select
	//
	//	Return		:	The current index into the character array, if not a 
	//					valid click, returns -1
	//////////////////////////////////////////////////////////////////////////
	int IsMousePosValid(POINT mousePt);

	//////////////////////////////////////////////////////////////////////////
	//	Function	:	"CalculateRanges"
	//
	//	Purpose		:	Determines the attack and move range of the current character
	//////////////////////////////////////////////////////////////////////////
	void CalculateRanges();

	//////////////////////////////////////////////////////////////////////////
	//	Function	:	"DrawHover"
	//
	//	Purpose		:	Draws the rectangle showing which character is currently
	//					being hovered over
	//////////////////////////////////////////////////////////////////////////
	void DrawHover();

	//////////////////////////////////////////////////////////////////////////
	//	Function	:	"HandleKeyBoardInput"
	//
	//	Purpose		:	Determine which keys are pressed and handle accordingly
	//
	//  Returns		:	True if the user is not exiting
	//////////////////////////////////////////////////////////////////////////
	bool HandleKeyBoardInput(float fElapsedTime);

	//////////////////////////////////////////////////////////////////////////
	//	Function	:	"HandleMouseInput"
	//
	//	Purpose		:	Determine which mouse buttons are pressed and handle accordingly
	//
	//  Returns		:	True if the user is not exiting
	//////////////////////////////////////////////////////////////////////////
	void HandleMouseInput(float fElapsedTime, POINT mouse, int xID, int yID);

	void HandleButton();
	//////////////////////////////////////////////////////////////////////////
	//	Function	:	"UpdatePositions"
	//
	//	Purpose		:	Updates all characters' positions, used primarily for
	//					camera movement
	//////////////////////////////////////////////////////////////////////////
	void UpdatePositions();

	//////////////////////////////////////////////////////////////////////////
	//  Function	:	DrawDebugInfo
	//
	//	Purpose		:	Draws any useful information for debugging to the screen
	//////////////////////////////////////////////////////////////////////////
	void DrawDebugInfo();

	//////////////////////////////////////////////////////////////////////////
	//  Function	:	PerformAttack
	//
	//	Purpose		:	Executes the attack depending on who attacks, any skills
	//					they use, and what the specific stats are for each character
	//////////////////////////////////////////////////////////////////////////
	void PerformAttack();

	//////////////////////////////////////////////////////////////////////////
	//  Function	:	FindPathToTarget
	//
	//	Purpose		:	Determines how to get to the target
	//////////////////////////////////////////////////////////////////////////
	void FindPathToTarget();

	void MoveCamLeft(float fElapsedTime);
	void MoveCamRight(float fElapsedTime);
	void MoveCamDown(float fElapsedTime);
	void MoveCamUp(float fElapsedTime);
	void CenterCam(float fElapsedTime);

public:
	void DrawBoxes();

	CBattleMap(void);
	~CBattleMap(void);
	static CBattleMap* GetInstance();
	//////////////////////////////////////////////////////////////////////////
	//	Function	:	Enter
	//
	//	Purpose		:	Set up the new battle map, load file, set numEnemies...
	//////////////////////////////////////////////////////////////////////////
	void Enter(char* szFileName, char* szMapName = "Test", int nNumEnemies = 0);
	//////////////////////////////////////////////////////////////////////////
	//	Function	:	Exit
	//
	//	Purpose		:	Clean up
	//////////////////////////////////////////////////////////////////////////
	void Exit();
	//////////////////////////////////////////////////////////////////////////
	//	Function	:	Update
	//
	//	Purpose		:	Update the Battle Map
	//////////////////////////////////////////////////////////////////////////
	void Update(float fElapsedTime);
	//////////////////////////////////////////////////////////////////////////
	//	Function	:	Render
	//
	//	Purpose		:	Render the Map and all objects on it
	//////////////////////////////////////////////////////////////////////////
	void Render();
	//////////////////////////////////////////////////////////////////////////
	//	Function	:	Input
	//
	//	Purpose		:	Handle any user input for the battle, mouse and/or keyboard 
	//
	//	Return		:	true/false, false if we are exiting the game
	//////////////////////////////////////////////////////////////////////////
	bool Input(float, POINT);

	//////////////////////////////////////////////////////////////////////////
	//  Function	:	GetZdepthDraw
	//
	//	Purpose		:	To determine if a character object should be rendered
	//					in front of a map object (free placed object)
	//
	//	Return		:	returns the z depth(float) for the character to be drawn at
	//////////////////////////////////////////////////////////////////////////
	float GetZdepthDraw(int x, int y, int currTileID = -1);

	//////////////////////////////////////////////////////////////////////////
	//	Accessors
	//////////////////////////////////////////////////////////////////////////
	int GetCurrSelectedTile() const {return m_nCurrSelectedTile;}
	int GetNumCols()	const		{return m_nNumCols;}
	int GetTileHeight() const		{return m_nTileHeight;}
	int GetTileWidth()  const		{return m_nTileWidth;}
	int GetOffsetX()	const		{return m_nOffsetX;}
	int GetOffsetY()	const		{return m_nOffsetY;}
	int GetFreeTileXos()const		{return m_nFreeTileOSx;}
	int GetFreeTileYos()const		{return m_nfreeTileOSy;}
	int GetCurrActive() const		{return m_nCurrCharacter;}
	int GetCurrTarget() const		{return m_nCurrTarget;}
	int GetMousePtr()   const		{return m_nCurrMousePtr;}
	CBase* GetCurrEnemyTarget()		{return &m_vCharacters[m_nCurrTarget];}
	vector<CBase*>* GetEnemies()	{return &m_vEnemies;}
	CBase* GetChars()	{return &m_vCharacters[m_nCurrCharacter];}
	CTile* GetTiles()	const		{return m_pTilesL1;}

	//////////////////////////////////////////////////////////////////////////
	//	Mutators
	//////////////////////////////////////////////////////////////////////////
	void SetCurrSelectedTile(const int selectedTile){m_nCurrSelectedTile = selectedTile;}
	void SetOffsetX(const int offsetX)				{m_nOffsetX = offsetX;}
	void SetOffsetY(const int offsetY)				{m_nOffsetY = offsetY;}
	void SetFTosX(const int osX)					{m_nFreeTileOSx = osX;}
	void SetFTosY(const int osY)					{m_nfreeTileOSy = osY;}
	void SetMousePtr(const int mouseID)				{m_nCurrMousePtr = mouseID;}
	void SetTurn(bool IsPlayersTurn)				{m_bIsPlayersTurn = IsPlayersTurn;}
	void SetStartPositions();
};

#endif