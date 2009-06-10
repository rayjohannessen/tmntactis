////////////////////////////////////////////////////////
//   File Name	:	"ObjectManager.h"
//
//   Author		:	Matthew Di Matteo (MD)
//
//   Purpose	:	Manages all objects in the game
////////////////////////////////////////////////////////

#ifndef OBJECTMANAGER_H
#define OBJECTMANAGER_H


#include <Windows.h>
#include <vector>
using std::vector;

class CBase;

class ObjectManager
{
private:	
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
		DEPTH()
		{
			GROUND = 1.0f;
			GROUNDL2 = 0.9f;
			SELECTION = 0.8f;
			CHARACTER_BEHIND = 0.7f;
			OBJECTS = 0.6f;
			CHARACTER_AHEAD = 0.5f;
			ARROW = 0.49f;
		}
	};
	DEPTH depth;
	vector<CBase*> m_vObjects;

	///////////////////////////////////////////////////////////////////
	//	Function:	"ObjectManager(Constructor)"
	///////////////////////////////////////////////////////////////////
	ObjectManager(void);
	ObjectManager& operator=(const ObjectManager&);
	ObjectManager(const ObjectManager&);

	///////////////////////////////////////////////////////////////////
	//	Function:	"~ObjectManager(Destructor)"
	///////////////////////////////////////////////////////////////////
	~ObjectManager(void);
	
public:

	///////////////////////////////////////////////////////////////////
	// Function: "GetInstance"
	//
	//  Purpose: Gets instance to the only instance of the class.
	///////////////////////////////////////////////////////////////////
	static ObjectManager* GetInstance();

	////////////////////////////////////////////////////////////////////
	// Function: “UpdateObjects”
	//
	// Purpose: Calls all game objects update based on time.
	////////////////////////////////////////////////////////////////////
	void UpdateObjects(float fElapsedTime);

	////////////////////////////////////////////////////////////////////
	// Function: “RenderObjects”
	//
	// Purpose: Calls all game objects render functions.
	////////////////////////////////////////////////////////////////////
	void RenderObjects(void);

	////////////////////////////////////////////////////////////////////
	// Function: “Add”
	//
	// Purpose: Adds a pointer to an object to the vector of objects
	////////////////////////////////////////////////////////////////////
	void Add(CBase* pObj);
	////////////////////////////////////////////////////////////////////
	// Function: “Remove”
	//
	// Purpose: Remove object from vector of objects
	////////////////////////////////////////////////////////////////////
	void Remove(CBase* pObj);

	////////////////////////////////////////////////////////////////////
	// Function: “RemoveAll”
	//
	// Purpose: Clears the vector of objects
	////////////////////////////////////////////////////////////////////
	void RemoveAll(void);

	////////////////////////////////////////////////////////////////////
	// Function: “CheckObjectsToAlpha”
	//
	// Purpose: Determines if the passed in free tile object needs to be
	//			alpha'd out
	////////////////////////////////////////////////////////////////////
	bool CheckObjectsToAlpha(RECT* mapObjectRect);

	//////////////////////////////////////////////////////////////////////////
	//  Function	:	GetZdepthDraw
	//
	//	Purpose		:	To determine if a character object should be rendered
	//					in front of a map object (free placed object)
	//
	//	Return		:	returns the z depth(float) for the character to be drawn at
	//////////////////////////////////////////////////////////////////////////
	float GetZdepthDraw(int x, int y, int currTileID = -1);

	void CheckCollisions(void);

};

#endif