////////////////////////////////////////////////////////
//   File Name	:	"Boss.cpp"
//
//   Author		:	Matthew Di Matteo (MD)
//
//   Purpose	:	To provide a game object to be used as a Boss emeny
//					against the user during the game.
////////////////////////////////////////////////////////

#include "Boss.h"
#include <math.h>
#include <ctime>
#include "Player.h"
#include "BattleMap.h"
#include "Tile.h"

int Random(int min, int max)
{
	int number = abs(max) - abs(min);
	return ((rand()%number) + abs(min));
}

CBoss::CBoss(void)
{
	srand(unsigned int(time(0)));
	m_nInRange = 0;
	m_nTurtle = 0;	
	m_nXChange = 0;
	m_nYChange = 0;
	m_bMoving = false;
	m_pPlayer = CPlayer::GetInstance();
	m_pTile = CBattleMap::GetInstance()->GetTiles();
	m_nType = OBJECT_BOSS;
	//m_vPath = 0;
	//m_ptStartXY =0;
	
}

CBoss::~CBoss(void)
{
}

void CBoss::FindPath(POINT begin, POINT end)
{
	m_vPath.clear();
	POINT ptCurr = begin; // begin point
	POINT ptTarget = end;	// end point
	int range = GetCurrAP();	// max distance moveable
	int pathWeight = 0;
	vector<int> pathX;
	vector<int> pathY;
	int oldX = ptCurr.x;
	int oldY = ptCurr.y;

	while (true)
	{
		if (pathWeight-4 > -1)
		{
			if ( (ptCurr.x == pathX[pathWeight-4]) && (ptCurr.y == pathY[pathWeight-4]) )
			{ pathWeight = 10000; break; }
		}
		if (pathWeight-1 > -1)
		{
			pathX.push_back(ptCurr.x);
			pathY.push_back(ptCurr.y);
			m_vPath.push_back(ptCurr);
			oldX = pathX[pathWeight-1];
			oldY = pathY[pathWeight-1];
		}
		++pathWeight;
		if (pathWeight*2 > GetCurrAP())
			break;
		if (ptTarget.x == ptCurr.x && ptTarget.y == ptCurr.y)
			break;
		if (pathWeight > CBattleMap::GetInstance()->GetNumCols())
		{pathWeight = 10000; break;}

		if (ptCurr.x < ptTarget.x && (oldX != ptCurr.x + 1) && 
			m_pTile[ptCurr.y * CBattleMap::GetInstance()->GetNumCols() + (ptCurr.x+1)].Flag() == FLAG_NONE &&
			!CBattleMap::GetInstance()->CheckTileOccupied(ptCurr.y * CBattleMap::GetInstance()->GetNumCols() + (ptCurr.x+1)))
		{ ++ptCurr.x; continue; }

		if (ptCurr.x > ptTarget.x && (oldX != ptCurr.x - 1) && 
			m_pTile[ptCurr.y * CBattleMap::GetInstance()->GetNumCols() + (ptCurr.x-1)].Flag() == FLAG_NONE &&
			!CBattleMap::GetInstance()->CheckTileOccupied(ptCurr.y * CBattleMap::GetInstance()->GetNumCols() + (ptCurr.x-1)))
		{ --ptCurr.x; continue; }

		if (ptCurr.y < ptTarget.y && (oldY != ptCurr.y + 1) && 
			m_pTile[(ptCurr.y+1) * CBattleMap::GetInstance()->GetNumCols() + ptCurr.x].Flag() == FLAG_NONE &&
			!CBattleMap::GetInstance()->CheckTileOccupied((ptCurr.y+1) * CBattleMap::GetInstance()->GetNumCols() + ptCurr.x))
		{ ++ptCurr.y; continue; }

		if (ptCurr.y > ptTarget.y && (oldY != ptCurr.y - 1) && 
			m_pTile[(ptCurr.y-1) * CBattleMap::GetInstance()->GetNumCols() + ptCurr.x].Flag() == FLAG_NONE &&
			!CBattleMap::GetInstance()->CheckTileOccupied((ptCurr.y-1) * CBattleMap::GetInstance()->GetNumCols() + ptCurr.x))
		{ --ptCurr.y; continue; }

		if (ptCurr.x == ptTarget.x)
		{
			if (oldX != ptCurr.x+1 && m_pTile[ptCurr.y * CBattleMap::GetInstance()->GetNumCols() + ptCurr.x+1].Flag() == FLAG_NONE &&
				!CBattleMap::GetInstance()->CheckTileOccupied(ptCurr.y * CBattleMap::GetInstance()->GetNumCols() + ptCurr.x+1) )
			{ ++ptCurr.x; continue; }
			if (oldX != ptCurr.x-1 && m_pTile[ptCurr.y * CBattleMap::GetInstance()->GetNumCols() + ptCurr.x-1].Flag() == FLAG_NONE &&
				!CBattleMap::GetInstance()->CheckTileOccupied(ptCurr.y * CBattleMap::GetInstance()->GetNumCols() + ptCurr.x-1))
			{ --ptCurr.x; continue; }
		}
		else if (ptCurr.y == ptTarget.y)
		{
			if (oldY != ptCurr.y+1 && m_pTile[(ptCurr.y+1) * CBattleMap::GetInstance()->GetNumCols() + ptCurr.x].Flag() == FLAG_NONE &&
				!CBattleMap::GetInstance()->CheckTileOccupied((ptCurr.y+1) * CBattleMap::GetInstance()->GetNumCols() + ptCurr.x))
			{ ++ptCurr.y; continue; }
			if (oldY != ptCurr.y-1 && m_pTile[(ptCurr.y-1) * CBattleMap::GetInstance()->GetNumCols() + ptCurr.x].Flag() == FLAG_NONE &&
				!CBattleMap::GetInstance()->CheckTileOccupied((ptCurr.y-1) * CBattleMap::GetInstance()->GetNumCols() + ptCurr.x))
			{ --ptCurr.y; continue; }
		}

		if ( (ptCurr.x > ptTarget.x) && (oldX != ptCurr.x+1) && m_pTile[ptCurr.y * CBattleMap::GetInstance()->GetNumCols() + (ptCurr.x+1)].Flag() == FLAG_NONE &&
			!CBattleMap::GetInstance()->CheckTileOccupied(ptCurr.y * CBattleMap::GetInstance()->GetNumCols() + (ptCurr.x+1)))
		{++ptCurr.x; continue;}
		else if (oldX != ptCurr.x-1 && m_pTile[ptCurr.y * CBattleMap::GetInstance()->GetNumCols() + (ptCurr.x-1)].Flag() == FLAG_NONE &&
			!CBattleMap::GetInstance()->CheckTileOccupied(ptCurr.y * CBattleMap::GetInstance()->GetNumCols() + (ptCurr.x-1)))
		{--ptCurr.x; continue;}

		if ( (ptCurr.y > ptTarget.y) && (oldY != ptCurr.y+1) && m_pTile[(ptCurr.y+1) * CBattleMap::GetInstance()->GetNumCols() + ptCurr.x].Flag() == FLAG_NONE &&
			!CBattleMap::GetInstance()->CheckTileOccupied((ptCurr.y+1) * CBattleMap::GetInstance()->GetNumCols() + ptCurr.x))
		{++ptCurr.y; continue;}
		else if (oldY != ptCurr.y-1 && m_pTile[(ptCurr.y-1) * CBattleMap::GetInstance()->GetNumCols() + ptCurr.x].Flag() == FLAG_NONE &&
			!CBattleMap::GetInstance()->CheckTileOccupied((ptCurr.y-1) * CBattleMap::GetInstance()->GetNumCols() + ptCurr.x))
		{--ptCurr.y; continue;}
		pathWeight = 10000; break;
	}
	if (m_vPath.size() > 0)
	{
		m_ptStartXY.x = GetPosX();
		m_ptStartXY.y = GetPosY();
		for (unsigned int i = 0; i < m_vPath.size(); ++i)
			m_pTile[m_vPath[i].y * CBattleMap::GetInstance()->GetNumCols() + m_vPath[i].x].SetAlpha(199);
	}
}

void CBoss::AI()
{
	//check distance
	SetCurrAP(16);
	
	//set temporary ranges
	int tempRange1 = abs(GetMapCoord().x - m_pPlayer->GetTurtles()[MIKEY]->GetMapCoord().x) + 
						abs(GetMapCoord().y - m_pPlayer->GetTurtles()[MIKEY]->GetMapCoord().y);
	int tempRange2 = abs(GetMapCoord().x - m_pPlayer->GetTurtles()[LEONARDO]->GetMapCoord().x) +
						abs(GetMapCoord().y - m_pPlayer->GetTurtles()[LEONARDO]->GetMapCoord().y );
	int tempRange3 = abs(GetMapCoord().x - m_pPlayer->GetTurtles()[DONATELLO]->GetMapCoord().x) +
						abs(GetMapCoord().y - m_pPlayer->GetTurtles()[DONATELLO]->GetMapCoord().y);
	int tempRange4 = abs(GetMapCoord().x - m_pPlayer->GetTurtles()[RAPHAEL]->GetMapCoord().x) +
						abs(GetMapCoord().y - m_pPlayer->GetTurtles()[RAPHAEL]->GetMapCoord().y);


	//set range to 100 if turtle is dead
	if( m_pPlayer->GetTurtles()[MIKEY]->GetAlive() == false)
	{
		tempRange1 = 100;
	}
	if(m_pPlayer->GetTurtles()[LEONARDO]->GetAlive() == false)
	{
		tempRange2 = 100;
	}
	if( m_pPlayer->GetTurtles()[DONATELLO]->GetAlive() == false)
	{
		tempRange3 = 100;
	}
	if( m_pPlayer->GetTurtles()[RAPHAEL]->GetAlive() == false)
	{
		tempRange4 = 100;
	}

	//checking if mikey is closest
	if( m_pPlayer->GetTurtles()[MIKEY]->GetAlive() == true)
	{
		if(tempRange1 < tempRange2)
		{
			if(tempRange1 < tempRange3)
			{
				if(tempRange1 < tempRange4)
				{
					m_nInRange = tempRange1;
					m_nXChange = m_pPlayer->GetTurtles()[MIKEY]->GetMapCoord().x - GetMapCoord().x;
					m_nYChange = m_pPlayer->GetTurtles()[MIKEY]->GetMapCoord().y - GetMapCoord().y ; 
					m_nTurtle = MIKEY;
				}
			}
		}
	}
	
	//check if leo is closest
	if( m_pPlayer->GetTurtles()[LEONARDO]->GetAlive() == true)
	{
		if(tempRange2 < tempRange1)
		{
			if(tempRange2 < tempRange3)
			{
				if(tempRange2 < tempRange4)
				{
					m_nInRange = tempRange2;
					m_nXChange =  m_pPlayer->GetTurtles()[LEONARDO]->GetMapCoord().x - GetMapCoord().x;
					m_nYChange =  m_pPlayer->GetTurtles()[LEONARDO]->GetMapCoord().y - GetMapCoord().y;
					m_nTurtle = LEONARDO;
				}
			}
		}
	}

	//check if donny is closest
	if( m_pPlayer->GetTurtles()[DONATELLO]->GetAlive() == true)
	{
		if(tempRange3 < tempRange1)
		{
			if(tempRange3 < tempRange2)
			{
				if(tempRange3 < tempRange4)
				{
					m_nInRange = tempRange3;
					m_nXChange =  m_pPlayer->GetTurtles()[DONATELLO]->GetMapCoord().x - GetMapCoord().x;
					m_nYChange =  m_pPlayer->GetTurtles()[DONATELLO]->GetMapCoord().y - GetMapCoord().y; 
					m_nTurtle = DONATELLO;
				}
			}
		}
	}

	//check if raph is closest
	if( m_pPlayer->GetTurtles()[RAPHAEL]->GetAlive() == true)
	{
		if(tempRange4 < tempRange1)
		{
			if(tempRange4 < tempRange2)
			{
				if(tempRange4 < tempRange3)
				{
					m_nInRange = tempRange4;
					m_nXChange = m_pPlayer->GetTurtles()[RAPHAEL]->GetMapCoord().x - GetMapCoord().x ;
					m_nYChange =  m_pPlayer->GetTurtles()[RAPHAEL]->GetMapCoord().y - GetMapCoord().y; 
					m_nTurtle = RAPHAEL;
				}
			}
		}
	}

	POINT begin = GetMapCoord();
	//safe check to see if turtle is chosen
	if(m_nTurtle <= -1)
	{
		m_nTurtle = 0;
	}
	POINT end;
	POINT mapPt;
	//switch case for distance 0 - 8

	switch(m_nInRange)
	{
		//on turtle
	case 0:
		{
			//16 ap always
			// attack four times (4ap * 4 = 16)
			//m_pPlayer->GetTurtles()[m_nTurtle]->SetHealth(m_pPlayer->GetTurtles()[m_nTurtle]->GetHealth() - (20 * 4)); 
			//end turn
			//SetCurrAP(0);
			//TODO::wait till attack is done to end the turn? would require actually decrementing AP when the attack animation was played
			/*CBattleMap::GetInstance()->UpdatePositions();
			CBattleMap::GetInstance()->NinjaMoveComplete();
			CBattleMap::GetInstance()->SetTurn(true);*/

		}
		break;
		//one tile away from  turtle
	case 1:
		{
			//attack four times(4ap * 4 = 16)
			//m_pPlayer->GetTurtles()[m_nTurtle]->SetHealth(m_pPlayer->GetTurtles()[m_nTurtle]->GetHealth() - (20 * 4));
			//end turn
			//SetCurrAP(0);
			//TODO::wait till attack is done to end the turn? would require actually decrementing AP when the attack animation was played
			/*CBattleMap::GetInstance()->UpdatePositions();
			CBattleMap::GetInstance()->NinjaMoveComplete();
			CBattleMap::GetInstance()->SetTurn(true);*/
			switch(GetCurrAP())
				{
					SetCurrAnim(2);
				case 4:
					{
						m_pPlayer->GetTurtles()[m_nTurtle]->SetHealth(m_pPlayer->GetTurtles()[m_nTurtle]->GetHealth() - (20));	
					}
					break;
				case 6:
					{
						//use skill low punch , sweep
						//do 40+ damage 
						int damage = Random(30, 50);//damage
						m_pPlayer->GetTurtles()[m_nTurtle]->SetHealth(m_pPlayer->GetTurtles()[m_nTurtle]->GetHealth() - damage);

						

					}
					break;
				case 8:
					{
						m_pPlayer->GetTurtles()[m_nTurtle]->SetHealth(m_pPlayer->GetTurtles()[m_nTurtle]->GetHealth() - (20 * 2));
					}
					break;
				case 10:
					{
						//use skill punch, kick
						//do 60+ damage
						int damage = Random(45, 65);//damage
						m_pPlayer->GetTurtles()[m_nTurtle]->SetHealth(m_pPlayer->GetTurtles()[m_nTurtle]->GetHealth() - damage);
					}
					break;
				case 12:
					{
						m_pPlayer->GetTurtles()[m_nTurtle]->SetHealth(m_pPlayer->GetTurtles()[m_nTurtle]->GetHealth() - (20 * 3));
					}
					break;
				case 16:
					{
						//use skill low punch, sweep then use skill punck, kick
						int damage = Random(80, 100);
						m_pPlayer->GetTurtles()[m_nTurtle]->SetHealth(m_pPlayer->GetTurtles()[m_nTurtle]->GetHealth() - damage);
					}
					break;
				default:
					{
					}
					break;
				}
				//end shredder turn
				CBattleMap::GetInstance()->UpdatePositions();
				CBattleMap::GetInstance()->NinjaMoveComplete();
				CBattleMap::GetInstance()->SetTurn(true);

		}
		break;
		//two tiles away from turtle 1 out of range
	case 2:
		{
			//move in 1 tile (2ap)
			switch(abs(m_nXChange))
			{
			case 0:
				mapPt.x = GetMapCoord().x;
				//if(x == 0) y == 2
				if(m_nYChange > 0)
				{
					mapPt.y = GetMapCoord().y + (m_nYChange -1);
				}
				else 
				{
					mapPt.y = GetMapCoord().y + (m_nYChange +1);
				}
				break;
			case 1:
				mapPt.x = GetMapCoord().x + m_nXChange;
				mapPt.y = GetMapCoord().y;
				break;
			case 2:
				if(m_nXChange > 0)
				{
					mapPt.x = GetMapCoord().x + (m_nXChange -1);
					mapPt.y = GetMapCoord().y;
				}
				else
				{
					mapPt.x = GetMapCoord().x + (m_nXChange +1);
					mapPt.y = GetMapCoord().y;
				}
				break;
			}
			end = mapPt;
			m_bMoving = true;
			FindPath(begin, end);
			/*SetCurrTile(mapPt, CBattleMap::GetInstance()->GetOffsetX(), CBattleMap::GetInstance()->GetOffsetY(), 
				CBattleMap::GetInstance()->GetTileWidth(), CBattleMap::GetInstance()->GetTileHeight(), 
				CBattleMap::GetInstance()->GetNumCols(), true);*/

			//attack 3 times (4ap * 3 = 12)
			//m_pPlayer->GetTurtles()[m_nTurtle]->SetHealth(m_pPlayer->GetTurtles()[m_nTurtle]->GetHealth() - (20 * 3));
			//end turn
			
			//CBattleMap::GetInstance()->SetTurn(true);
		}
		break;
		//three tiles, move in two tiles
	case 3:
		{
			
			//move in two tiles(4ap)
			switch(abs(m_nXChange))
			{
			case 0://if x = 0, y = 3
				if(m_nYChange > 0)
				{
					mapPt.x = GetMapCoord().x;
					mapPt.y = GetMapCoord().y + (m_nYChange -1);
				}
				else
				{
					mapPt.x = GetMapCoord().x;
					mapPt.y = GetMapCoord().y + (m_nYChange +1);
				}
				break;
			case 1://if x = 1, y = 2
				mapPt.x = GetMapCoord().x;
				mapPt.y = GetMapCoord().y + m_nYChange;
				break;
			case 2://if x = 2, y = 1
				mapPt.x = GetMapCoord().x + m_nXChange;
				mapPt.y = GetMapCoord().y;
				break;
			case 3://if x = 3, y = 0
				if(m_nXChange > 0)
				{
					mapPt.x = GetMapCoord().x + (m_nXChange -1);
					mapPt.y = GetMapCoord().y;
				}
				else
				{
					mapPt.x = GetMapCoord().x + (m_nXChange +1);
					mapPt.y = GetMapCoord().y;
				}
				break;
			}
			end = mapPt;
			/*SetCurrTile(mapPt, CBattleMap::GetInstance()->GetOffsetX(), CBattleMap::GetInstance()->GetOffsetY(), 
				CBattleMap::GetInstance()->GetTileWidth(), CBattleMap::GetInstance()->GetTileHeight(), 
				CBattleMap::GetInstance()->GetNumCols(), true);*/

			m_bMoving = true;
			FindPath(begin, end);

			//attack three times(12ap)= 16ap
			//m_pPlayer->GetTurtles()[m_nTurtle]->SetHealth(m_pPlayer->GetTurtles()[m_nTurtle]->GetHealth() - ( 20 * 3));
			//end turn
			
		}
		break;
		//four tiles, move in three tiles
	case 4:
		{
			//move in three tiles(6ap)
			switch(abs(m_nXChange))
			{
			case 0://if x = 0, y = 4
				if(m_nYChange > 0)
				{
					mapPt.x = GetMapCoord().x;
					mapPt.y = GetMapCoord().y + (m_nYChange -1);
				}
				else
				{
					mapPt.x = GetMapCoord().x;
					mapPt.y = GetMapCoord().y + (m_nYChange +1);
				}
				break;
			case 1://if x1 y3
				mapPt.x = GetMapCoord().x;
				mapPt.y = GetMapCoord().y + m_nYChange;
				break;
			case 2://if x2 y2
				mapPt.x = GetMapCoord().x + m_nXChange;
				if(m_nYChange >0)
				{
					mapPt.y = GetMapCoord().y + (m_nYChange -1);
				}
				else 
				{
					mapPt.y = GetMapCoord().y + (m_nYChange +1);
				}
				break;
			case 3://if x3 y1
				mapPt.x = GetMapCoord().x + m_nXChange;
				mapPt.y = GetMapCoord().y;
				break;
			case 4://if x4 y0
				if(m_nXChange > 0)
				{
					mapPt.x = GetMapCoord().x + (m_nXChange -1);
				}
				else
				{
					mapPt.x = GetMapCoord().x + (m_nXChange +1);
				}
				mapPt.y = GetMapCoord().y;
				break;
			}
			end = mapPt;
			/*SetCurrTile(mapPt, CBattleMap::GetInstance()->GetOffsetX(), CBattleMap::GetInstance()->GetOffsetY(), 
				CBattleMap::GetInstance()->GetTileWidth(), CBattleMap::GetInstance()->GetTileHeight(), 
				CBattleMap::GetInstance()->GetNumCols(), true);*/
			
			m_bMoving = true;
			FindPath(begin, end);

			//attack twice(8ap) = 14ap
			//m_pPlayer->GetTurtles()[m_nTurtle]->SetHealth(m_pPlayer->GetTurtles()[m_nTurtle]->GetHealth() - (20 * 2));
			//end turn
		}
		break;
		//five tiles, move four
	case 5:
		{
			//move four tiles(8ap)
			switch(abs(m_nXChange))
			{
			case 0://if x0 y5
				if(m_nYChange > 0)
				{
					mapPt.y = GetMapCoord().y + (m_nYChange -1);
				}
				else
				{
					mapPt.y = GetMapCoord().y + (m_nYChange +1);
				}
				mapPt.x = GetMapCoord().x;
				break;
			case 1://if x1 y4
				mapPt.x = GetMapCoord().x;
				mapPt.y = GetMapCoord().y + m_nYChange;
				break;
			case 2://if x2 y3
				mapPt.x = GetMapCoord().x + m_nXChange;
				if(m_nYChange > 0)
				{
					mapPt.y = GetMapCoord().y + (m_nYChange -1);
				}
				else
				{
					mapPt.y = GetMapCoord().y + (m_nYChange +1);
				}
				break;
			case 3://if x3 y2
				mapPt.y = GetMapCoord().y + m_nYChange;
				if(m_nXChange > 0)
				{
					mapPt.x = GetMapCoord().x + (m_nXChange -1);
				}
				else
				{
					mapPt.x = GetMapCoord().x + (m_nXChange +1);
				}
				break;
			case 4://if x4 y1
				mapPt.y = GetMapCoord().y;
				mapPt.x = GetMapCoord().x + m_nXChange;
				break;
			case 5://if x5 y0
				if(m_nXChange > 0)
				{
					mapPt.x = GetMapCoord().x + (m_nXChange -1);
				}
				else
				{
					mapPt.x = GetMapCoord().x + (m_nXChange +1);
				}
				mapPt.y = GetMapCoord().y;
				break;
			}
			end = mapPt;
			/*SetCurrTile(mapPt, CBattleMap::GetInstance()->GetOffsetX(), CBattleMap::GetInstance()->GetOffsetY(), 
				CBattleMap::GetInstance()->GetTileWidth(), CBattleMap::GetInstance()->GetTileHeight(), 
				CBattleMap::GetInstance()->GetNumCols(), true);*/

			m_bMoving = true;
			FindPath(begin, end);

			//attack twice(8ap) = 16ap
			//m_pPlayer->GetTurtles()[m_nTurtle]->SetHealth(m_pPlayer->GetTurtles()[m_nTurtle]->GetHealth() - (20 * 2));
			//end turn
		}
		break;
		//six tiles, move five
	case 6:
		{
			//move 5 tiles(10ap)
			switch(abs(m_nXChange))
			{
			case 0://if x0 y6
				if(m_nYChange > 0)
				{
					mapPt.y = GetMapCoord().y + (m_nYChange -1);
				}
				else
				{
					mapPt.y = GetMapCoord().y + (m_nYChange -1);
				}
				mapPt.x = GetMapCoord().x;
				break;
			case 1://if x1 y5
				mapPt.x = GetMapCoord().x;
				mapPt.y = GetMapCoord().y + m_nYChange;
				break;
			case 2://if x2 y4
				mapPt.x = GetMapCoord().x + m_nXChange;
				if(m_nYChange > 0)
				{
					mapPt.y = GetMapCoord().y + (m_nYChange -1);
				}
				else
				{
					mapPt.y = GetMapCoord().y + (m_nYChange +1);
				}
				break;
			case 3://if x3 y3
				mapPt.x = GetMapCoord().x + m_nXChange;
				if(m_nYChange > 0)
				{
					mapPt.y = GetMapCoord().y + (m_nYChange -1);
				}
				else
				{
					mapPt.y = GetMapCoord().y + (m_nYChange +1);
				}
				break;
			case 4://if x4 y2
				mapPt.y = GetMapCoord().y + m_nYChange;
				if(m_nXChange > 0)
				{
					mapPt.x = GetMapCoord().x + (m_nXChange -1);
				}
				else
				{
					mapPt.x = GetMapCoord().x + (m_nXChange +1);
				}
				break;
			case 5://if x5 y1
				mapPt.y = GetMapCoord().y;
				mapPt.x = GetMapCoord().x + m_nXChange;
				break;
			case 6://if x6 y0
				mapPt.y = GetMapCoord().y;
				if(m_nXChange > 0)
				{
					mapPt.x = GetMapCoord().x + (m_nXChange -1);
				}
				else
				{
					mapPt.x = GetMapCoord().x + (m_nXChange +1);
				}
				break;
			}
			end = mapPt;
			/*SetCurrTile(mapPt, CBattleMap::GetInstance()->GetOffsetX(), CBattleMap::GetInstance()->GetOffsetY(), 
				CBattleMap::GetInstance()->GetTileWidth(), CBattleMap::GetInstance()->GetTileHeight(), 
				CBattleMap::GetInstance()->GetNumCols(), true);*/
			
			m_bMoving = true;
			FindPath(begin, end);

			//attack one(4ap) = 14ap
			//m_pPlayer->GetTurtles()[m_nTurtle]->SetHealth(m_pPlayer->GetTurtles()[m_nTurtle]->GetHealth() - (20));
			//end turn
		}
		break;
		//7 tiles, move 6
	case 7:
		{
			//move 6 tiles(12ap)
			switch(abs(m_nXChange))
			{
			case 0://if x0 y7
				if(m_nYChange > 0)
				{
					mapPt.y = GetMapCoord().y + (m_nYChange -1);
				}
				else
				{
					mapPt.y = GetMapCoord().y + (m_nYChange +1);
				}
				mapPt.x = GetMapCoord().x;
				break;
			case 1://if x1 y6
				mapPt.x = GetMapCoord().x;
				mapPt.y = GetMapCoord().y + m_nYChange;
				break;
			case 2://if x2 y5
				mapPt.x = GetMapCoord().x + m_nXChange;
				if(m_nYChange > 0)
				{
					mapPt.y = GetMapCoord().y + (m_nYChange -1);
				}
				else
				{
					mapPt.y = GetMapCoord().y + (m_nYChange +1);
				}
				break;
			case 3://if x3 y4
				mapPt.x = GetMapCoord().x + m_nXChange;
				if(m_nYChange > 0)
				{
					mapPt.y = GetMapCoord().y + (m_nYChange -1);
				}
				else
				{
					mapPt.y = GetMapCoord().y + (m_nYChange +1);
				}
				break;
			case 4://if x4 y3
				mapPt.y = GetMapCoord().y + m_nYChange;
				if(m_nXChange > 0)
				{
					mapPt.x = GetMapCoord().x + (m_nXChange -1);
				}
				else
				{
					mapPt.x = GetMapCoord().x + (m_nXChange +1);
				}
				break;
			case 5://if x5 y2
				mapPt.y = GetMapCoord().y + m_nYChange;
				if(m_nXChange > 0)
				{
					mapPt.x = GetMapCoord().x + (m_nXChange -1);
				}
				else
				{
					mapPt.x = GetMapCoord().x + (m_nXChange +1);
				}
				break;
			case 6://if x6 y1
				mapPt.y = GetMapCoord().y;
				mapPt.x = GetMapCoord().x + m_nXChange;
				break;
			case 7://if x7 y0
				mapPt.y = GetMapCoord().y;
				if(m_nXChange > 0)
				{
					mapPt.x = GetMapCoord().x + (m_nXChange -1);
				}
				else
				{
					mapPt.x = GetMapCoord().x + (m_nXChange +1);
				}
				break;
			}
			end = mapPt;
			/*SetCurrTile(mapPt, CBattleMap::GetInstance()->GetOffsetX(), CBattleMap::GetInstance()->GetOffsetY(), 
				CBattleMap::GetInstance()->GetTileWidth(), CBattleMap::GetInstance()->GetTileHeight(), 
				CBattleMap::GetInstance()->GetNumCols(), true);*/

			m_bMoving = true;
			FindPath(begin, end);

			//attack once(4ap) = 16ap
			//m_pPlayer->GetTurtles()[m_nTurtle]->SetHealth(m_pPlayer->GetTurtles()[m_nTurtle]->GetHealth() - (20));
			//end turn
		}
		break;
		//8 tiles, move 7
	case 8:
		{
			//move 7 tiles(14ap)
			switch(abs(m_nXChange))
			{
			case 0://if x0 y8
				if(m_nYChange > 0)
				{
					mapPt.y = GetMapCoord().y + (m_nYChange -1);
				}
				else
				{
					mapPt.y = GetMapCoord().y + (m_nYChange +1);
				}
				mapPt.x = GetMapCoord().x;
				break;
			case 1://if x1 y7
				mapPt.x = GetMapCoord().x;
				mapPt.y = GetMapCoord().y + m_nYChange;
				break;
			case 2://if x2 y6
				mapPt.x = GetMapCoord().x + m_nXChange;
				if(m_nYChange > 0)
				{
					mapPt.y = GetMapCoord().y + (m_nYChange -1);
				}
				else
				{
					mapPt.y = GetMapCoord().y + (m_nYChange +1);
				}
				break;
			case 3://if x3 y5
				mapPt.x = GetMapCoord().x + m_nXChange;
				if(m_nYChange > 0)
				{
					mapPt.y = GetMapCoord().y + (m_nYChange -1);
				}
				else
				{
					mapPt.y = GetMapCoord().y + (m_nYChange +1);
				}
				break;
			case 4://if x4 y4
				mapPt.x = GetMapCoord().x + m_nXChange;
				if(m_nYChange > 0)
				{
					mapPt.y = GetMapCoord().y + (m_nYChange -1);
				}
				else
				{
					mapPt.y = GetMapCoord().y + (m_nYChange +1);
				}
				break;
			case 5://if x5 y3
				mapPt.y = GetMapCoord().y + m_nYChange;
				if(m_nXChange > 0)
				{
					mapPt.x = GetMapCoord().x + (m_nXChange -1);
				}
				else
				{
					mapPt.x = GetMapCoord().x + (m_nXChange +1);
				}
				break;
			case 6://if x6 y2
				mapPt.y = GetMapCoord().y + m_nYChange;
				if(m_nXChange > 0)
				{
					mapPt.x = GetMapCoord().x + (m_nXChange -1);
				}
				else
				{
					mapPt.x = GetMapCoord().x + (m_nXChange +1);
				}
				break;
			case 7://if x7 y1
				mapPt.x = GetMapCoord().x + m_nXChange;
				mapPt.y = GetMapCoord().y;
				break;
			case 8://if x8 y0
				if(m_nXChange > 0)
				{
					mapPt.x = GetMapCoord().x + (m_nXChange -1);
				}
				else
				{
					mapPt.x = GetMapCoord().x + (m_nXChange +1);
				}
				mapPt.y = GetMapCoord().y;
				break;
			}

			end = mapPt;

			/*SetCurrTile(mapPt, CBattleMap::GetInstance()->GetOffsetX(), CBattleMap::GetInstance()->GetOffsetY(), 
				CBattleMap::GetInstance()->GetTileWidth(), CBattleMap::GetInstance()->GetTileHeight(), 
				CBattleMap::GetInstance()->GetNumCols(), true);*/

			m_bMoving = true;
			
			FindPath(begin, end);

		}
		break;
	default:
		{
			//end turn
			//SetCurrAP(0);
			////TODO::wait till attack is done to end the turn? would require actually decrementing AP when the attack animation was played
			//CBattleMap::GetInstance()->UpdatePositions();
			//CBattleMap::GetInstance()->NinjaMoveComplete();
			CBattleMap::GetInstance()->SetTurn(true);
		}
		break;
		}


}
void CBoss::Update(float fElapsedTime)
{
	//CBase::Update(fElapsedTime);
	if(!GetCurrAnim()->IsAnimationPlaying())
		SetCurrAnim(1);
	m_vAnimations[m_nCurrAnimation].Update(fElapsedTime);
	// a ninja has been moved...execute the animation and position change over time
	if (m_bMoving == true)
	{
		if (m_vPath.size() > 0)
		{
			// grab the next move and take it out of the vector..if the previous move is complete
			POINT newPoint = m_vPath[0];
			// set up variables
			POINT currPoint= GetMapCoord();
			MY_POINT_FLOAT currPos; 
			currPos.x = GetPosX(); currPos.y = GetPosY();

			// NORTHWEST
			if ( newPoint.x < currPoint.x && abs(m_ptStartXY.x - currPos.x) < 32 && abs(m_ptStartXY.y - currPos.y) < 16)
			{
				SetCurrAnimFacing(true);

				currPos.x -= GetVelX() * fElapsedTime;
				currPos.y -= GetVelY() * fElapsedTime;
				SetPosPtF(currPos);
			}
			// SOUTHEAST
			else if ( newPoint.x > currPoint.x && abs(m_ptStartXY.x - currPos.x) < 32 && abs(m_ptStartXY.y - currPos.y) < 16)
			{
				SetCurrAnimFacing(false);

				currPos.x += GetVelX() * fElapsedTime;
				currPos.y += GetVelY() * fElapsedTime;
				SetPosPtF(currPos);
			}
			// NORTHEAST
			if ( newPoint.y < currPoint.y && abs(m_ptStartXY.x - currPos.x) < 32 && abs(m_ptStartXY.y - currPos.y) < 16)
			{
				SetCurrAnimFacing(false);

				currPos.y -= GetVelY() * fElapsedTime;
				currPos.x += GetVelX() * fElapsedTime;
				SetPosPtF(currPos);
			}
			// SOUTHWEST
			else if ( newPoint.y > currPoint.y && abs(m_ptStartXY.x - currPos.x) < 32 && abs(m_ptStartXY.y - currPos.y) < 16)
			{
				SetCurrAnimFacing(true);

				currPos.y += GetVelY() * fElapsedTime;
				currPos.x -= GetVelX() * fElapsedTime;
				SetPosPtF(currPos);
			}
			// check to see if this current tile move is complete
			if ( abs(m_ptStartXY.x - currPos.x) >= 32 && abs(m_ptStartXY.y - currPos.y) >= 16)
			{
				vector<POINT>::iterator first = m_vPath.begin();
				m_vPath.erase(first);
				SetCurrTile(newPoint, CBattleMap::GetInstance()->GetOffsetX(), CBattleMap::GetInstance()->GetOffsetY(), CBattleMap::GetInstance()->GetTileWidth(),
					CBattleMap::GetInstance()->GetTileHeight(), CBattleMap::GetInstance()->GetNumCols());
// 				SetCurrTile(newPoint, CBattleMap::GetInstance()->GetOffsetX(), CBattleMap::GetInstance()->GetOffsetY(), CBattleMap::GetInstance()->GetTileWidth(),
// 					CBattleMap::GetInstance()->GetTileHeight(), CBattleMap::GetInstance()->GetNumCols());
				
 				DecrementCurrAP(2);
				m_ptStartXY.x = GetPosX();
				m_ptStartXY.y = GetPosY();
			}
		}
		else // movement is done
		{
			SetCurrAP(GetCurrAP());
			m_bMoving = false;
			//SetCurrAnim(3);

			if(m_nInRange == 1)
			{
				//skills punch, kick
				//skills low punch, sweep
				switch(GetCurrAP())
				{
				case 4:
					{
						m_pPlayer->GetTurtles()[m_nTurtle]->SetHealth(m_pPlayer->GetTurtles()[m_nTurtle]->GetHealth() - (20));	
					}
					break;
				case 6:
					{
						//use skill low punch , sweep
						//do 40+ damage 
						int damage = Random(30, 50);//damage
						m_pPlayer->GetTurtles()[m_nTurtle]->SetHealth(m_pPlayer->GetTurtles()[m_nTurtle]->GetHealth() - damage);
					}
					break;
				case 8:
					{
						m_pPlayer->GetTurtles()[m_nTurtle]->SetHealth(m_pPlayer->GetTurtles()[m_nTurtle]->GetHealth() - (20 * 2));
					}
					break;
				case 10:
					{
						//use skill punch, kick
						//do 60+ damage
						int damage = Random(45, 65);//damage
						m_pPlayer->GetTurtles()[m_nTurtle]->SetHealth(m_pPlayer->GetTurtles()[m_nTurtle]->GetHealth() - damage);
					}
					break;
				case 12:
					{
						m_pPlayer->GetTurtles()[m_nTurtle]->SetHealth(m_pPlayer->GetTurtles()[m_nTurtle]->GetHealth() - (20 * 3));
					}
					break;
				case 16:
					{
						//use skill low punch, sweep then use skill punck, kick
						int damage = Random(80, 100);
						m_pPlayer->GetTurtles()[m_nTurtle]->SetHealth(m_pPlayer->GetTurtles()[m_nTurtle]->GetHealth() - damage);
					}
					break;
				default:
					{
					}
					break;
				}
				//end shredder turn
				CBattleMap::GetInstance()->SetTurn(true);
			}
			//TODO::wait till attack is done to end the turn? would require actually decrementing AP when the attack animation was played
			CBattleMap::GetInstance()->UpdatePositions();
			CBattleMap::GetInstance()->NinjaMoveComplete();
			CBattleMap::GetInstance()->SetTurn(true);
		}
	}

	if( GetExperience() >= 100)
	{
		SetExperience( GetExperience() - (100* GetLevel()) );
		SetLevel(GetLevel()+1);
		SetHealthMax((int)((float)GetMaxHealth() * 1.25f));
		SetBaseAP(GetBaseAP()+2);
		SetStrength( (int)( (float)GetStrength() * 1.2f ) );
		SetDefense( (int) ( (float)GetDefense() * 1.2f ) );
		SetAccuracy( (int) ( (float)GetAccuracy() * 1.2f ) );
		SetSpeed( (int) ( (float)GetSpeed() * 1.2f ) );
	}
}
void CBoss::Render()
{
	m_vAnimations[m_nCurrAnimation].Render((int)GetPosX(), (int)GetPosY(), GetPosZ(), 1, m_dwColor);

}