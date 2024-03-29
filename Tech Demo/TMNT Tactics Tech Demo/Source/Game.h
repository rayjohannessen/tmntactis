#pragma once

#include "windows.h"
#include "IGameState.h"

//class CBitmapFont;
class CSGD_DirectInput;
class CBattleMap;
class CSGD_Direct3D;
class CSGD_TextureManager;
class CAssets;
//class ParticleSystem;

class CGame
{
private:
	//pointers to other classes
	IGameState*			m_pCurrentState;
	CSGD_Direct3D*		m_pD3D;
	CSGD_TextureManager* m_pTM;
	CSGD_DirectInput*   m_pDI;
	CAssets*			m_pAssets;
	//ParticleSystem* m_pParticleSystem;
	//MessageSystem* m_pMessageSystem;
	//ObjectFactory* m_pObjectFactory;
	//FMOD::System* m_pFMODSystem;
	//FMOD::Channel m_FMChannel1;
	//FMOD::Channel m_FMChannel2;

	// variables
	bool m_bIsRunning;
	int m_nSFXVolume;
	int m_nMusicVolume;
	float m_fElapsedTime;
	int m_nScreenWidth;
	int m_nScreenHeight;
	//PLAYERINFO m_PlayerInfo;

	//Constructor
	CGame(void);
	//Copy Constructor
	CGame(const CGame&);
	//Assignment Operator
	CGame& operator=(const CGame&);
	//Destructor
	~CGame(void);

public:
	///////////////////////////////////////////////
	//	Function:	ChangeState
	//
	//	Purpose:	Change the State of the Game
	///////////////////////////////////////////////
	void ChangeState(IGameState* pGameState);
	/////////////////////////////////////////////////////////////////
	//	Function:	Main
	//
	//	Purpose:	To run while the game runs from start to finish
	////////////////////////////////////////////////////////////////
	bool Main(POINT mouse);
	////////////////////////////////////////////////////////////////
	//	Function:	Shutdown
	//
	//	Purpose:	Clean up all memory 
	////////////////////////////////////////////////////////////////
	void Shutdown(void);
	////////////////////////////////////////////////////////////
	//	Function:	Initialize
	//
	//	Purpose:	Initialize the game
	////////////////////////////////////////////////////////////
	void Initialize(HWND hWnd, HINSTANCE hInstance, int nScreenWidth, int nScreenHeight, bool bIsWindowed);
	///////////////////////////////////////////////////////
	//	Function:	GetInstance
	//
	//	Purpose:	Gets the instance of CGame
	///////////////////////////////////////////////////////
	static CGame* GetInstance(void);
	///////////////////////////////////////////////////////
	//	Function:	LoadSettings
	//
	//	Purpose:	To load the game settings
	///////////////////////////////////////////////////////
	void LoadSettings(void);
	////////////////////////////////////////////////////////
	//	Function: GetFMODSystem
	//
	//	Purpose: Return the FMODSystem pointer
	////////////////////////////////////////////////////////
	//FMOD::System* GetFMODSystem(void);

	//////////////////////////////////////////////////////////////////////////
	// Accessors
	//////////////////////////////////////////////////////////////////////////
	//RECT GetBackGroundSize(void){ return m_rectBackGroundSize; }
 	int  GetScreenWidth ()		{return m_nScreenWidth;}
 	int  GetScreenHeight ()		{return m_nScreenHeight;}
	// 	bool GetIsPaused()			{return m_bIsPaused;}
	bool GetIsRunning()			{return m_bIsRunning;}
	// 	int  GetSFXVolume()			{return m_nSFXVolume;}
	// 	int  GetMusicVolume()		{return m_nMusicVolume;}
	// 	int  GetPanning()			{return m_nPanning;}

	//////////////////////////////////////////////////////////////////////////
	// Mutators
	//////////////////////////////////////////////////////////////////////////
	//	void SetIsPaused	()					{m_bIsPaused = !m_bIsPaused;}
	void SetIsRunning	(bool _bIsRunning)		{m_bIsRunning = _bIsRunning;}
	// 	void SetLastScore	(int _nLastScore)		{m_nLastScore = _nLastScore;}
	// 	void SetSFXVolume	(int _nSFXVolume);
	// 	void SetMusicVolume	(int _nMusicVolume);
	// 	void SetPanning		(int _nPanning);
};