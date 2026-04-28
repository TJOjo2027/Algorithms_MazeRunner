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
	DIRECTION currDir;

	point iterationCurrent(point currP) {
		switch(currDir){
			case EAST:  currP.x++; break;
			case SOUTH: currP.y++; break;
			case WEST:  currP.x--; break;
			case NORTH: currP.y--; break;
		}
		return currP;
	}

	void iterationAdvance(){
		switch(currDir){
			case EAST:  currDir = SOUTH; break;
			case SOUTH: currDir = WEST; break;
			case WEST:  currDir = NORTH; break;
			case NORTH: currDir = EAST; break;
		}
	}

	void iterationRetreat(){
		switch(currDir){
			case EAST:  currDir = NORTH; break;
			case SOUTH: currDir = EAST; break;
			case WEST:  currDir = SOUTH; break;
			case NORTH: currDir = WEST; break;
		}
	}

	bool iterationDone(DIRECTION trialDir, point location) const {
		return trialDir >= 4;
	}


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

		DIRECTION nextDir;
		for(int i = 0; i < 4; i++){

		

	}
	

	DIRECTION BFSNextMove() {

	}

	DIRECTION FloodFillNextMove() {
		
	}

	DIRECTION nextMoveTeamOne() {
		
	}

};


#endif /* RACECARDRIVER_H_ */
