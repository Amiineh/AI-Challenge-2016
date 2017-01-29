#include "AI.h"

#include <vector>
#include <cstdlib>
#include <iostream>

std::vector<int> minRouteValue;

std::vector<int> minRouteValueForEmpt;

std::vector<bool> UsWithEn;

std::vector<bool> EnWithUs;

std::vector<bool> flag;

std::vector<bool> isAttack;

void MinRouteCalc ( Node* now , int myId )
{
	std::vector<Node*> neighbours = now->getNeighbours();
	for ( int i = 0 ; i < neighbours.size() ; i++ )
	{
		if ( neighbours[i]->getOwner() == myId )
		{
			if ( minRouteValue[neighbours[i]->getIndex()] > minRouteValue[now->getIndex()] + 1 )
			{
				minRouteValue[neighbours[i]->getIndex()] = minRouteValue[now->getIndex()] + 1;
				MinRouteCalc ( neighbours[i] , myId );
			}
		}
	}
	return;
}

void MinRouteCalcForEmpt ( Node* now , int myId )
{
	std::vector<Node*> neighbours = now->getNeighbours();
	for ( int i = 0 ; i < neighbours.size() ; i++ )
	{
		if ( neighbours[i]->getOwner() != myId )
		{
			if ( minRouteValueForEmpt[neighbours[i]->getIndex()] > minRouteValueForEmpt[now->getIndex()] + 1 )
			{
				minRouteValueForEmpt[neighbours[i]->getIndex()] = minRouteValueForEmpt[now->getIndex()] + 1;
				MinRouteCalcForEmpt ( neighbours[i] , myId );
			}
		}
	}
	return;
}

void UsWithEnAction ( std::vector<Node*> myNodesIndex , int myId )
{
	for (int i = 0 ; i < myNodesIndex.size() ; i++ )
	{
		if ( myNodesIndex[i]->getOwner() == myId )
		{
			std::vector<Node*> neighbours = myNodesIndex[i]->getNeighbours();
			for ( int j = 0 ; j < neighbours.size() ; j++)
			{
				if ( neighbours[j]->getOwner() != myId )
				{
					UsWithEn[i] = true;
					break;
				}
				else
				{
					UsWithEn[i] = false;
				}
			}
		}
		else
		{
			UsWithEn[i] = false;
		}
	}
}

void EnWithUsAction ( std::vector<Node*> myNodesIndex , int myId )
{
	for (int i = 0 ; i < myNodesIndex.size() ; i++ )
	{
		if ( myNodesIndex[i]->getOwner() != myId )
		{
			std::vector<Node*> neighbours = myNodesIndex[i]->getNeighbours();
			for ( int j = 0 ; j < neighbours.size() ; j++)
			{
				if ( neighbours[j]->getOwner() == myId )
				{
					EnWithUs[i] = true;
					break;
				}
				else
				{
					EnWithUs[i] = false;
				}
			}
		}
		else
		{
			EnWithUs[i] = false;
		}
	}
}


bool EndsUpWithEnemy ( Node* From , Node* To , int myId )
{
	flag[From->getIndex()] = true;
	if ( To->getOwner() == 1 - myId )
	{
		return true;
	}
	else
	{
		std::vector<Node*> neighbours = To->getNeighbours();
		for ( int i = 0 ; i < neighbours.size() ; i++ )
		{
			if ( !flag[neighbours[i]->getIndex()])
			{
				if ( EndsUpWithEnemy ( To , neighbours[i] , myId ) )
				{
					return true;
				}
			}
		}
		return false;
	}
}

Node* minTargetChoser ( Node* From , std::vector<Node*> allMinTargets , int myId )
{
	bool tempflag = false;
	for ( int i = 0 ; i < allMinTargets.size() ; i++ )
	{
		if ( allMinTargets[i]->getOwner() != myId)
		{
			tempflag = true;
			break;
		}
	}
	if ( !tempflag )
	{
		int maxDegree = 0;
		int bestMaxDegree = 0;
		Node* bestAns = NULL;
		Node* ans = NULL;
		for ( int i = 0 ; i < allMinTargets.size() ; i++)
		{
			if ( allMinTargets[i]->getNeighbours().size() > bestMaxDegree && !isAttack[allMinTargets[i]->getIndex()])
			{
				bestMaxDegree = allMinTargets[i]->getNeighbours().size();
				bestAns = allMinTargets[i];
			}
// 			else if ( allMinTargets[i]->getNeighbours().size() > maxDegree)
// 			{
// 				maxDegree = allMinTargets[i]->getNeighbours().size();
// 				ans = allMinTargets[i];
// 			}
// 			if ( allMinTargets[i]->getNeighbours().size() > maxDegree)
// 			{
// 				maxDegree = allMinTargets[i]->getNeighbours().size();
// 				ans = allMinTargets[i];
// 			}
		}
		if(bestAns != NULL)
			return bestAns;
		// else
// 			return ans;
	}

	for ( int i = 0 ; i < allMinTargets.size() ; i++ )
	{
		for ( int j = 0 ; j < flag.size() ; j++ )
		{
			flag[j] = false;
		}
		if ( !EndsUpWithEnemy( From , allMinTargets[i] , myId) )
		{
			return allMinTargets[i];
		}
	}
	tempflag = false;
	std::vector<Node*> emptyNodes;
	for ( int i = 0 ; i < allMinTargets.size() ; i++ )
	{
		if ( allMinTargets[i]->getOwner() == -1 )
		{
			emptyNodes.push_back(allMinTargets[i]);
			tempflag = true;
		}
	}
	if ( tempflag )
	{
		int maxDegree = 0;
		int bestMaxDegree = 0;
		Node* bestAns = NULL;
		Node* ans = NULL;
		for ( int i = 0 ; i < emptyNodes.size() ; i++ )
		{
			if ( allMinTargets[i]->getNeighbours().size() > bestMaxDegree && !isAttack[allMinTargets[i]->getIndex()])
			{
				bestMaxDegree = allMinTargets[i]->getNeighbours().size();
				bestAns = allMinTargets[i];
			}
			else if ( emptyNodes[i]->getNeighbours().size() > maxDegree)
			{
				maxDegree = emptyNodes[i]->getNeighbours().size();
				ans = emptyNodes[i];
			}
// 			if ( emptyNodes[i]->getNeighbours().size() > maxDegree)
// 			{
// 				maxDegree = emptyNodes[i]->getNeighbours().size();
// 				ans = emptyNodes[i];
// 			}
		}
		if(bestAns != NULL)
			return bestAns;
		else
	 		return ans;
	}
	//changes for attacking
// 		srand(time(NULL));
// 	 	return allMinTargets[rand() % allMinTargets.size()];
	else
	{
		int minDegree = INT_MAX;
		Node* ans = NULL;
		for ( int i = 0 ; i < allMinTargets.size() ; i++ )
		{
			if ( minDegree > allMinTargets[i]->getNeighbours().size())
			{
				minDegree = allMinTargets[i]->getNeighbours().size();
				ans = allMinTargets[i];
			}
		}
 		if(ans != NULL)
			return ans;
		else
		{
			srand(time(NULL));
 	 		return allMinTargets[rand() % allMinTargets.size()];
		}
	}
}

void AI::doTurn(World *world)
{
	flag.clear();
	UsWithEn.clear();
	minRouteValue.clear();
	EnWithUs.clear();
	Graph* map = world->getMap();
	std::vector<Node*> AllNodes = map->getNodes();
	isAttack.clear();
	int size = AllNodes.size();
	for ( int i = 0 ; i < size ; i++ )
	{
		isAttack.push_back(false);
		EnWithUs.push_back(false);
		flag.push_back(false);
		UsWithEn.push_back(false);
		minRouteValue.push_back(INT_MAX);
		minRouteValueForEmpt.push_back(INT_MAX);
	} //initializing vectors
	int myId = world->getMyId();
	UsWithEnAction( AllNodes , myId ); // figuring out our nodes with enemy or empty neighbours
	for ( int i = 0 ; i < size ; i++ )
	{
		flag[i] = false;
	}
	EnWithUsAction( AllNodes , myId );
    for ( int i = 0 ; i < size ; i++ )
    {
        if ( UsWithEn[i] )
        {
            minRouteValue[i] = 1 ;
        }
        if ( EnWithUs[i] )
        {
        	minRouteValue[i] = 0 ;
        }
        if ( AllNodes[i]->getOwner() == 1 - myId )
        {
        	minRouteValueForEmpt[i] = 0;
        }
    }
	for ( int i = 0 ; i < size ; i++ )
	{
		if  ( UsWithEn[i] )
		{
			MinRouteCalc( AllNodes[i] , myId );
		}
		if ( AllNodes[i]->getOwner() == 1 - myId )
		{
			MinRouteCalcForEmpt ( AllNodes[i] , myId );
		}

	}
	for ( int i = 0 ; i < AllNodes.size() ; i++ )
	{
		if ( AllNodes[i]->getOwner() == myId )
		{
			Node* armyTarget;
			int minRoute = INT_MAX;
			std::vector<Node*> neighbours = AllNodes[i]->getNeighbours();
			for ( int j = 0 ; j < neighbours.size() ; j++ )
			{
				if ( minRouteValue[neighbours[j]->getIndex()] < minRoute)
				{
					minRoute = minRouteValue[neighbours[j]->getIndex()];
					armyTarget = neighbours[j];
				}
			}
			for ( int j = 0 ; j < flag.size() ; j++ )
			{
				flag[j] = false ;
			}
			std::vector<Node*> allMinTargets;
			for ( int j = 0 ; j < neighbours.size() ; j++ )
			{
				if ( minRoute == minRouteValue[neighbours[j]->getIndex()] )
				{
					allMinTargets.push_back(neighbours[j]);
				}
			}
			armyTarget = minTargetChoser ( AllNodes[i] , allMinTargets , myId );
			for ( int j = 0 ; j < flag.size() ; j++ )
			{
				flag[j] = false ;
			}
			if ( EndsUpWithEnemy( AllNodes[i] , armyTarget , myId ) )
			{
				if ( minRouteValue[armyTarget->getIndex()] == 0 && armyTarget->getOwner() == -1 )
				{
					int min = minRouteValueForEmpt[armyTarget->getIndex()];
					isAttack[armyTarget->getIndex()] = true;
				 	world->moveArmy( AllNodes[i] , armyTarget , ( min - 0.5 ) * AllNodes[i]->getArmyCount() / min );
				//	world->moveArmy( AllNodes[i] , armyTarget , AllNodes[i]->getArmyCount() );
				}
				else
				{

					isAttack[armyTarget->getIndex()] = true;
					world->moveArmy( AllNodes[i] , armyTarget , AllNodes[i]->getArmyCount() );
				}
			}
			else
			{
				isAttack[armyTarget->getIndex()] = true;
				world->moveArmy( AllNodes[i] , armyTarget , 1 );
			}
		}
 	}
}
