/*
 * RaceCarDriver.h
 *
 *  Created on: Spring, 2026
 *      Author: bill_booth
 */

#ifndef RACECARDRIVER_H_
#define RACECARDRIVER_H_

#include "Racer.h"
#include <vector>
using namespace std;

class RaceCarDriver{
private:
	Racer* car;

	// Stack used to track taken by car
	stack<DIRECTION> dfsPath;

	// Using a set to track visited locations
	set<point> visited;

	// Current direction of the car
	DIRECTION currDir = EAST;

	// Helper functions for DFS implementation /////////////////////////////////////////////////////////////////////////////////////////////////

	void iterationBegin(){
		currDir = EAST;
	}

	// Utilized for iterating through the current direction and returning the resulting point
	point iterationCurrent(point currP) {
		switch(currDir){
			case EAST:  currP.x++; break;
			case SOUTH: currP.y++; break;
			case WEST:  currP.x--; break;
			case NORTH: currP.y--; break;
		}
		return currP;
	}

	// Utilzied for iterating through directions in a clockwise manner
	void iterationAdvance(){
		switch(currDir){
			case EAST:  currDir = SOUTH; break;
			case SOUTH: currDir = WEST; break;
			case WEST:  currDir = NORTH; break;
			case NORTH: currDir = EAST; break;
		}
	}

	// Utilzied for backtracking when all directions have been iterated through in a counter-clockwise manner
	void iterationRetreat(){
		switch(currDir){
			case EAST:  currDir = NORTH; break;
			case SOUTH: currDir = EAST; break;
			case WEST:  currDir = SOUTH; break;
			case NORTH: currDir = WEST; break;
		}
	}

	// Check if the current direction has been fully iterated through
	bool iterationDone(int count) const {
		return count >= 4;
	}
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

public:
	RaceCarDriver(Racer* p = nullptr): car{p}{}



	// Booth's Random Next Move Implementation
	DIRECTION nextMove(){
		vector<DIRECTION> pool;

		if(!car->look(EAST))   pool.push_back(EAST);
		if(!car->look(SOUTH))  pool.push_back(SOUTH);
		if(!car->look(NORTH))  pool.push_back(NORTH);
		if(!car->look(WEST))   pool.push_back(WEST);

		return pool[rand() % pool.size()];
	}

	// Emeka's DFS Next Move Implementation
	DIRECTION DFSNextMove() {

		// Retrive the current location of the car
		point currLoc = car->getLocation();

		// Mark the current location as visited
		visited.insert(currLoc);

		// Utilized to track that if all directions have been iterated through
		int directionsTried = 0;

		while (!iterationDone(directionsTried)) {
			// Getting the neighboring point in the current direction
			point neighbor = iterationCurrent(currLoc);

			// 
		}

		

	}
	

	DIRECTION BFSNextMove() {

	}

	DIRECTION FloodFillNextMove() {
		
	}

	DIRECTION nextMoveTeamOne() {
		
	}

};


#endif /* RACECARDRIVER_H_ */
