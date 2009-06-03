////////////////////////////////////////////////////////
//   File Name	:	"CAnimation.h"
//
//   Author		:	Matthew Di Matteo (MD)
//
//   Purpose	:	This file provides a way to set and control
//					the animations of the game objects 
////////////////////////////////////////////////////////

#ifndef ANIMATION_H
#define ANIMATION_H

#include <windows.h>
#include <string>
using std::string;

struct sFrame
{
	int nFrameX;
	int nFrameY;

	int nFrameWidth;
	int nFrameHeight;

	int nAnchorX;
	int nAnchorY;
};

class CAnimation
{
private:
	int m_nImageID;

	int m_nCurrFrame;
	int m_nTotalFrames;

	float m_fTimePerFrame;
	float m_fTimeWaited;

	float m_fDuration;

	string m_nAnimName;
	string m_nSheetFile;
	string m_nTriggerName;
	string m_nTriggerType;
	
	sFrame* m_pFrames;
	
	bool m_bIsPlaying;
	bool m_bIsLooping;

	float m_fSpeed;

	///////////////////////////////////////////////////////////////////
	// Function: �Reset�
	//
	// Purpose: Sets variables to their initial value.
	////////////////////////////////////////////////////////////////////
	void Reset();

public:
	///////////////////////////////////////////////////////////////////
	//	Function:	"CAnimation(Constructor)"
	///////////////////////////////////////////////////////////////////
	CAnimation(void);

	///////////////////////////////////////////////////////////////////
	//	Function:	"~CAnimation(Destructor)"
	///////////////////////////////////////////////////////////////////
	~CAnimation(void);

	///////////////////////////////////////////////////////////////////
	// Function: �Load�
	//
	// Purpose: Sets all data needed for the font.
	////////////////////////////////////////////////////////////////////
	void Load(const char* FileName, int numFrame);

	void Unload();

		////////////////////////////////////////////////////////////////////
	// Function: �Update�
	//
	// Purpose: Updates game objects based on time.
	////////////////////////////////////////////////////////////////////
	void Update(float fElapsedtime);

	///////////////////////////////////////////////////////////////////
	// Function: �Render�
	//
	// Purpose: Draws the animation frames to the screen at the specified location.
	////////////////////////////////////////////////////////////////////
	void Render(int posx, int posy, float posZ, float scale = 1.0f, bool bFacingleft = false, DWORD dwColor = NULL);

	///////////////////////////////////////////////////////////////////
	// Function: �Play�
	//
	// Purpose: Restarts the animation from the beginning.
	////////////////////////////////////////////////////////////////////
	void Play();

	///////////////////////////////////////////////////////////////////
	// Function: �Stop�
	//
	// Purpose: Stops the animation at the current frame.
	////////////////////////////////////////////////////////////////////
	void Stop();
	
	///////////////////////////////////////////////////////////////////
	// Function: �Resume�
	//
	// Purpose: Starts the animation at the current frame.
	////////////////////////////////////////////////////////////////////
	void Resume();

	///////////////////////////////////////////////////////////////////
	// Function: �IsAnimationPlaying�
	//
	// Purpose: Determine if the animation is currently playing or not.
	////////////////////////////////////////////////////////////////////
	bool IsAnimationPlaying() {return m_bIsPlaying;}

	//////////////////////////////////////////////////////////////////////////
	//	Accessors
	//////////////////////////////////////////////////////////////////////////
	sFrame* GetFrames() const {return m_pFrames;}

};

#endif