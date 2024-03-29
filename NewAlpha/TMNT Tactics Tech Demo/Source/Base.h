////////////////////////////////////////////////////////
//   File Name	:	"Base.h"
//
//   Author		:	Matthew Di Matteo (MD)
//
//   Purpose	:	To encapsulate all shared data and functionality 
//					for our game objects
////////////////////////////////////////////////////////

#ifndef BASE_H
#define BASE_H

#include "IBaseInterface.h"

#include <windows.h>
#include "Animation.h"
#include <vector>
using std::vector;

enum TYPE{ OBJECT_WEAPON, OBJECT_BATTLEITEM, OBJECT_BOSS, OBJECT_NINJA, OBJECT_TURTLE};

struct MY_POINT_FLOAT
{
	float x;
	float y;
};

class CBase : public IBaseInterface
{
private:
	int m_nImageID;
	//int m_nState;

	char* m_szName;

	//////////////////////////////////////////////////////////////////////////
	//	Map variables: sizes, positions, velocity, etc..
	POINT m_ptAnchor;
	POINT m_ptMapCoord;
	float m_fPosX;
	float m_fPosY;
	float m_fPosZ;
	float m_fVelX;
	float m_fVelY;
	int   m_nCurrTileID;

	int m_nWidth;
	int m_nHeight;
	//////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////
	//	Stats:
	int m_nHealthMax;
	int m_nHealth;

	int m_nLevel;
	int m_nStrength;
	int m_nDefense;
	int m_nAccuracy;
	int m_nSpeed;
	int m_nRange;

	int m_nBasePoints;//ap points
	int m_nCurrPoints;//ap points

	int m_nExperience;
	int m_nSkillXP;


	//////////////////////////////////////////////////////////////////////////
	//CTile m_pTileArray;

protected:
	CBase* m_pOwner;
	int m_nType;
	DWORD m_dwColor;
	int m_nNumType;

	vector<CAnimation> m_vAnimations;
	int m_nCurrAnimation;
public:	
	///////////////////////////////////////////////////////////////////
	//	Function:	"Base(Constructor)"
	///////////////////////////////////////////////////////////////////
	CBase();

	///////////////////////////////////////////////////////////////////
	//	Function:	"~Base(Destructor)"
	///////////////////////////////////////////////////////////////////
	virtual ~CBase() {}

	//////////////////////////////////////
	//	Function:	Accessors
	//
	//	Purpose	:	To get the specified type
	///////////////////////////////////////
	inline int		GetImageID()const	{return m_nImageID;		}
	inline float	GetPosX()const		{return m_fPosX;		}
	inline float	GetPosY()const		{return m_fPosY;		}
	inline float	GetPosZ()const		{return m_fPosZ;		}
	inline float	GetVelX()const		{return m_fVelX;		}
	inline float	GetVelY()const		{return m_fVelY;		}
	inline int		GetWidth()const		{return m_nWidth;		}
	inline int		GetHeight()const	{return m_nHeight;		}
	inline int		GetType()			{return m_nType;		}
	inline POINT	GetAnchor()			{return m_ptAnchor;		}
	inline int		GetRange()			{return m_nRange;		}
	inline int		GetCurrTile()		{return m_nCurrTileID;	}
	inline POINT	GetMapCoord()		{return m_ptMapCoord;}
	inline char*	GetName()			{return m_szName;		}

	inline int		GetMaxHealth(void)	{return m_nHealthMax;	}
	inline int		GetHealth(void)		{return m_nHealth;		}
	inline int		GetLevel(void)		{return m_nLevel;		}
	inline int		GetStrength(void)	{return m_nStrength;	}
	inline int		GetDefense(void)	{return m_nDefense;		}
	inline int		GetAccuracy(void)	{return m_nAccuracy;	}
	inline int		GetSpeed(void)		{return m_nSpeed;		}
	inline int		GetBaseAP(void)		{return m_nBasePoints;	}
	inline int		GetCurrAP(void)		{return m_nCurrPoints;	}
	inline int		GetExperience(void)	{return m_nExperience;	}
	inline int		GetSkillXP(void)	{return m_nSkillXP;}
	inline int		GetNumType()		{return m_nNumType;}
	vector<CAnimation> GetAnimations()  {return m_vAnimations;}
	CAnimation*		GetCurrAnim()		{return &(m_vAnimations[m_nCurrAnimation]);}
	inline int		GetCurrAnimNum()	{return m_nCurrAnimation;}
	RECT			GetRect();

	//////////////////////////////////////
	//	Function:	Mutators
	//
	//	Purpose	:	To set the specified type
	///////////////////////////////////////
	void SetCurrAnimFacing(bool IsLeft)     {m_vAnimations[m_nCurrAnimation].SetFacingLeft(IsLeft);}
	void SetCurrAnim(int animID, bool play = true);	
	inline void SetImageID(int nImageID)	{m_nImageID = nImageID;}
	inline void SetAnchor(POINT pt)			{m_ptAnchor = pt;}
	inline void SetMapCoord(POINT mapCoord) {m_ptMapCoord = mapCoord;}
	inline void SetPosX(float fPosX)		{m_fPosX = fPosX-m_vAnimations[0].GetFrames()[0].nAnchorX;}
	inline void SetPosY(float fPosY)		{m_fPosY = fPosY-m_vAnimations[0].GetFrames()[0].nAnchorY;}
	inline void SetPosPt(POINT pos)			{m_fPosX = (float)pos.x; m_fPosY = (float)pos.y;}
	inline void SetPosPtF(MY_POINT_FLOAT pos){m_fPosX = pos.x; m_fPosY = pos.y;}
	inline void SetPosZ(float fPosZ)		{m_fPosZ = fPosZ;}
	inline void SetVelX(float fVelX)		{m_fVelX = fVelX;}
	inline void SetVelY(float fVelY)		{m_fVelY = fVelY;}
	inline void SetWidth(int nWidth)		{m_nWidth = nWidth;}
	inline void SetHeight(int nHeight)		{m_nHeight = nHeight;}
	inline void SetBaseAP(int nAP)			{m_nBasePoints = nAP;}
	inline void SetCurrAP(int nAP)			{m_nCurrPoints = nAP;}
	inline void DecrementCurrAP(int nDecrem){m_nCurrPoints -= nDecrem;}
	inline void SetHealthMax(int nHealthMax){m_nHealthMax = nHealthMax;}
	inline void SetHealth(int nHealth)		{m_nHealth = nHealth;}
	inline void DecrementHealth(int nHealth){m_nHealth -= nHealth;}
	inline void SetStrength(int nStrength)	{m_nStrength = nStrength;}
	inline void SetDefense(int nDefense)	{m_nDefense = nDefense;}
	inline void SetAccuracy(int nAccuracy)	{m_nAccuracy = nAccuracy;}
	inline void SetSpeed(int nSpeed)		{m_nSpeed = nSpeed;}
	virtual void SetLevel(int nLevel)		{m_nLevel = nLevel;}
	inline void SetRange(int nRange)		{m_nRange = nRange;}
	inline void SetName(char* name)			{m_szName = name;}
	inline void SetType(int type)			{m_nType = type;}
	inline void SetExperience(int nExperience){m_nExperience = nExperience;}
	inline void SetSkillXP(int nSkillXp)	{m_nSkillXP = nSkillXp;}
	inline void SetNumType(int type)		{m_nNumType = type;}

	void SetCurrTile(POINT mapPt, int offSetX, int offSetY, int tileWidth, int tileHeight, int numCols, bool anchor = true);	// auto-sets position

	void AddAnim(CAnimation& a){ m_vAnimations.push_back(a);}

	////////////////////////////////////////////////////////////////////
	// Function: �Update�
	//
	// Purpose: Updates game objects based on time.
	////////////////////////////////////////////////////////////////////
	virtual void Update(float fElapsedTime);
	
	////////////////////////////////////////////////////////////////////
	// Function: �Render�
	//
	// Purpose: Draws game objects to the screen.
	////////////////////////////////////////////////////////////////////
	virtual void Render();

	////////////////////////////////////////////////////////////////////
	// Function: �Release�
	//
	// Purpose: Decrements the count varible. If the variable reaches zero,
	//			the pointer is no longer needed and is deleted.
	////////////////////////////////////////////////////////////////////
	void Release(){}

	////////////////////////////////////////////////////////////////////
	// Function: �Pathfind�
	//
	// Purpose: Will be used by all derived objects to do path finding.
	//
	////////////////////////////////////////////////////////////////////
	//vector<CTile> Pathfind(void);

	////////////////////////////////////////////////////////////////////
	// Function: �Colorize�
	//
	// Purpose: To provide feedback to the user that a character is selectable
	//
	////////////////////////////////////////////////////////////////////
	void Colorize(bool bColorize = true);
	
	void SetWeapon(char* name, int attack, int defense, int imageID, int numType);

};

#endif