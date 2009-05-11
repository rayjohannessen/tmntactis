////////////////////////////////////////////////////////////////////////////
//	File Name	:	"Messages.h"
//
//	Author		:	Matt DiMatteo (MD)
//
//	Purpose		:	This file contains all messages to be used throught the game.
//
////////////////////////////////////////////////////////////////////////////
#pragma once

typedef int MSGID;

enum eMsgTypes { MSG_NULL = 0, MSG_CREATE_ENEMY, MSG_CREATE_BULLET1,MSG_CREATE_BULLET2, 
				MSG_DESTROY_BULLET, MSG_DESTROY_ENEMY,MSG_DESTROY_PLAYER, 
				MSG_CREATE_PLAYER, MSG_CREATE_ENEMY2, MSG_CREATE_PWRUP,MSG_CREATE_PWRUP2, 
				MSG_DESTROY_PWRUP, MSG_DESTROY_PWRUP2,MSG_CREATE_BOSS, MSG_DESTROY_BOSS, 
				MSG_DESTROY_BULLET2, MSG_MAX };

class CEnemy;
class CPlayer;
class CBullet;
class CHealth;
class CBoss;
class WebBullet;
class CPoints;

class CBaseMessage
{
private:
	MSGID	m_msgID;

public:
	///////////////////////////////////////////////////////////////////
	//	Function:	"CBaseMessage(Constructor)"
	///////////////////////////////////////////////////////////////////
	CBaseMessage(MSGID msgID);

	///////////////////////////////////////////////////////////////////
	//	Function:	"~CBaseMessage(Destructor)"
	///////////////////////////////////////////////////////////////////
	virtual ~CBaseMessage(void);

	//////////////////////////////////////
	//	Function:	Accessors
	//	Purpose	:	To get the specified type
	///////////////////////////////////////
	inline MSGID GetMsgID(void)	{ return m_msgID; }
};

class CCreateEnemyMessage : public CBaseMessage
{
public:
	///////////////////////////////////////////////////////////////////
	//	Function:	"CCreateEnemyMessage(Constructor)"
	///////////////////////////////////////////////////////////////////
	CCreateEnemyMessage();

	///////////////////////////////////////////////////////////////////
	//	Function:	"~CCreateEnemyMessage(Destructor)"
	///////////////////////////////////////////////////////////////////
	~CCreateEnemyMessage();
};

class CCreateEnemyMessage2 : public CBaseMessage
{
public:
	///////////////////////////////////////////////////////////////////
	//	Function:	"CCreateEnemyMessage2(Constructor)"
	///////////////////////////////////////////////////////////////////
	CCreateEnemyMessage2();

	///////////////////////////////////////////////////////////////////
	//	Function:	"~CCreateEnemyMessage2(Destructor)"
	///////////////////////////////////////////////////////////////////
	~CCreateEnemyMessage2();
};


class CDestroyEnemyMessage  : public CBaseMessage
{
private:
	CEnemy* m_pEnemy;
public:
	///////////////////////////////////////////////////////////////////
	//	Function:	"CDestroyEnemyMessage(Constructor)"
	///////////////////////////////////////////////////////////////////
	CDestroyEnemyMessage(CEnemy* Enemy);

	///////////////////////////////////////////////////////////////////
	//	Function:	"~CDestroyEnemyMessage(Destructor)"
	///////////////////////////////////////////////////////////////////
	~CDestroyEnemyMessage();

	//////////////////////////////////////
	//	Function:	Accessors
	//	Purpose	:	To get the specified type
	///////////////////////////////////////
	inline CEnemy* GetEnemy() {return m_pEnemy;}
};

class CCreateBulletMessage : public CBaseMessage
{
	CPlayer*  m_pPlayer;
public:
	///////////////////////////////////////////////////////////////////
	//	Function:	"CCreateBulletMessage(Constructor)"
	///////////////////////////////////////////////////////////////////
	CCreateBulletMessage(CPlayer* pPlayer);

	///////////////////////////////////////////////////////////////////
	//	Function:	"~CCreateBulletMessage(Destructor)"
	///////////////////////////////////////////////////////////////////
	~CCreateBulletMessage();

	//////////////////////////////////////
	//	Function:	Accessors
	//	Purpose	:	To get the specified type
	///////////////////////////////////////
	inline CPlayer * GetPlayer(){return m_pPlayer;}
};
class CCreateBulletMessage2 : public CBaseMessage
{
	CBoss*  m_pBoss;
public:
	///////////////////////////////////////////////////////////////////
	//	Function:	"CCreateBulletMessage2(Constructor)"
	///////////////////////////////////////////////////////////////////
	CCreateBulletMessage2(CBoss* pBoss);

	///////////////////////////////////////////////////////////////////
	//	Function:	"~CCreateBulletMessage2(Destructor)"
	///////////////////////////////////////////////////////////////////
	~CCreateBulletMessage2();

	//////////////////////////////////////
	//	Function:	Accessors
	//	Purpose	:	To get the specified type
	///////////////////////////////////////
	inline CBoss * GetBoss(){return m_pBoss;}
};

class CDestroyBulletMessage : public CBaseMessage
{
	CBullet*  m_pBullet;
public:
	///////////////////////////////////////////////////////////////////
	//	Function:	"CDestroyBulletMessage(Constructor)"
	///////////////////////////////////////////////////////////////////
	CDestroyBulletMessage(CBullet* pBullet);

	///////////////////////////////////////////////////////////////////
	//	Function:	"~CDestroyBulletMessage(Destructor)"
	///////////////////////////////////////////////////////////////////
	~CDestroyBulletMessage();

	//////////////////////////////////////
	//	Function:	Accessors
	//	Purpose	:	To get the specified type
	///////////////////////////////////////
	inline CBullet* GetBullet() {return m_pBullet;}
};
class CDestroyBulletMessage2 : public CBaseMessage
{
	WebBullet*  m_pBullet;
public:
	///////////////////////////////////////////////////////////////////
	//	Function:	"CDestroyBulletMessage2(Constructor)"
	///////////////////////////////////////////////////////////////////
	CDestroyBulletMessage2(WebBullet* pBullet);

	///////////////////////////////////////////////////////////////////
	//	Function:	"~CDestroyBulletMessage2(Destructor)"
	///////////////////////////////////////////////////////////////////
	~CDestroyBulletMessage2();

	//////////////////////////////////////
	//	Function:	Accessors
	//	Purpose	:	To get the specified type
	///////////////////////////////////////
	inline WebBullet* GetBullet() {return m_pBullet;}
};
class CCreatePlayerMessage : public CBaseMessage
{
public:
	///////////////////////////////////////////////////////////////////
	//	Function:	"CCreatePlayerMessage(Constructor)"
	///////////////////////////////////////////////////////////////////
	CCreatePlayerMessage();

	///////////////////////////////////////////////////////////////////
	//	Function:	"~CCreatePlayerMessage(Destructor)"
	///////////////////////////////////////////////////////////////////
	~CCreatePlayerMessage() {}
};

class CDestroyPlayerMessage : public CBaseMessage
{
private:
	CPlayer* m_pPlayer;
public:
	///////////////////////////////////////////////////////////////////
	//	Function:	"CDestroyPlayerMessage(Constructor)"
	///////////////////////////////////////////////////////////////////
	CDestroyPlayerMessage(CPlayer* player);

	///////////////////////////////////////////////////////////////////
	//	Function:	"~CDestroyPlayerMessage(Destructor)"
	///////////////////////////////////////////////////////////////////
	~CDestroyPlayerMessage();

	//////////////////////////////////////
	//	Function:	Accessors
	//	Purpose	:	To get the specified type
	///////////////////////////////////////
	inline CPlayer* GetPlayer() {return m_pPlayer;}

};

class CCreatePowerUp : public CBaseMessage
{
	CEnemy* m_pEnemy;
public:
	///////////////////////////////////////////////////////////////////
	//	Function:	"CCreatePowerUp(Constructor)"
	///////////////////////////////////////////////////////////////////
	CCreatePowerUp(CEnemy* pEnemy);

	///////////////////////////////////////////////////////////////////
	//	Function:	"~CCreatePowerUp(Destructor)"
	///////////////////////////////////////////////////////////////////
	~CCreatePowerUp();

	//////////////////////////////////////
	//	Function:	Accessors
	//	Purpose	:	To get the specified type
	///////////////////////////////////////
	inline CEnemy* GetEnemy() {return m_pEnemy;}
	


};
class CDestroyPowerUp : public CBaseMessage
{
	CHealth* m_pHealth;
public:
	///////////////////////////////////////////////////////////////////
	//	Function:	"CDestroyPowerUp(Constructor)"
	///////////////////////////////////////////////////////////////////
	CDestroyPowerUp(CHealth* pHealth);

	///////////////////////////////////////////////////////////////////
	//	Function:	"~CDestroyPowerUp(Destructor)"
	///////////////////////////////////////////////////////////////////
	~CDestroyPowerUp();

	//////////////////////////////////////
	//	Function:	Accessors
	//	Purpose	:	To get the specified type
	///////////////////////////////////////
	inline CHealth* GetPwrup() {return m_pHealth;}
};
class CCreatePowerUp2 : public CBaseMessage
{
	CEnemy* m_pEnemy;
public:
	///////////////////////////////////////////////////////////////////
	//	Function:	"CCreatePowerUp2(Constructor)"
	///////////////////////////////////////////////////////////////////
	CCreatePowerUp2(CEnemy* pEnemy);

	///////////////////////////////////////////////////////////////////
	//	Function:	"~CCreatePowerUp2(Destructor)"
	///////////////////////////////////////////////////////////////////
	~CCreatePowerUp2();

	//////////////////////////////////////
	//	Function:	Accessors
	//	Purpose	:	To get the specified type
	///////////////////////////////////////
	inline CEnemy* GetEnemy() {return m_pEnemy;}
};
class CDestroyPowerUp2 : public CBaseMessage
{
	CPoints* m_pPoints;
public:
	///////////////////////////////////////////////////////////////////
	//	Function:	"CDestroyPowerUp2(Constructor)"
	///////////////////////////////////////////////////////////////////
	CDestroyPowerUp2(CPoints* pPoints);

	///////////////////////////////////////////////////////////////////
	//	Function:	"~CDestroyPowerUp2(Destructor)"
	///////////////////////////////////////////////////////////////////
	~CDestroyPowerUp2();

	//////////////////////////////////////
	//	Function:	Accessors
	//	Purpose	:	To get the specified type
	///////////////////////////////////////
	inline CPoints* GetPwrup() {return m_pPoints;}

};

class CCreateBossMessage : public CBaseMessage
{
public:
	///////////////////////////////////////////////////////////////////
	//	Function:	"CCreateBossMessage(Constructor)"
	///////////////////////////////////////////////////////////////////
	CCreateBossMessage();

	///////////////////////////////////////////////////////////////////
	//	Function:	"~CCreateBossMessage(Destructor)"
	///////////////////////////////////////////////////////////////////
	~CCreateBossMessage();
};


class CDestroyBossMessage  : public CBaseMessage
{
private:
	CBoss* m_pBoss;
public:
	///////////////////////////////////////////////////////////////////
	//	Function:	"CDestroyBossMessage(Constructor)"
	///////////////////////////////////////////////////////////////////
	CDestroyBossMessage(CBoss* pBoss);

	///////////////////////////////////////////////////////////////////
	//	Function:	"~CDestroyBossMessage(Destructor)"
	///////////////////////////////////////////////////////////////////
	~CDestroyBossMessage();

	//////////////////////////////////////
	//	Function:	Accessors
	//	Purpose	:	To get the specified type
	///////////////////////////////////////
	inline CBoss* GetBoss() {return m_pBoss;}
};