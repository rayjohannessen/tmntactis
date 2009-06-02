////////////////////////////////////////////////////////
//   File Name	:	"Factory.h"
//
//   Author		:	Matthew Di Matteo (MD)
//
//   Purpose	:	Creates base objects
////////////////////////////////////////////////////////

#ifndef FACTORY_H
#define FACTORY_H

class CNinja;
class CBoss;
class CTurtle;
class CBattleItem;

class Factory
{
private:

public:	
	///////////////////////////////////////////////////////////////////
	//	Function:	"Factory(Constructor)"
	///////////////////////////////////////////////////////////////////
	Factory(void);

	///////////////////////////////////////////////////////////////////
	//	Function:	"~Factory(Destructor)"
	///////////////////////////////////////////////////////////////////
	~Factory(void);
	

	///////////////////////////////////////////////////////////////////
	// Function: �CreateNinja�
	//
	// Purpose: Creates a pointer to the ninja object
	////////////////////////////////////////////////////////////////////
	static CNinja* CreateNinja();

	///////////////////////////////////////////////////////////////////
	// Function: �CreateBoss�
	//
	// Purpose: Creates a pointer to the boss object
	////////////////////////////////////////////////////////////////////
	static CBoss* CreateBoss();

	///////////////////////////////////////////////////////////////////
	// Function: �CreateTurtle�
	//
	// Purpose: Creates a pointer to the turtle object
	////////////////////////////////////////////////////////////////////
	static CTurtle* CreateTurtle();

	///////////////////////////////////////////////////////////////////
	// Function: �CBattleItem�
	//
	// Purpose: Creates a pointer to the BattleItem object
	////////////////////////////////////////////////////////////////////
	static CBattleItem* CreateBattleItem();


	
};

#endif