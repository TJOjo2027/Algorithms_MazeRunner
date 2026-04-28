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
#include <queue>

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
	// BFS variables
	queue<point> pointQueue;

	// used to map the points to the path
	// point doesn't have a comparison operator, so we have to use a pair of ints to represent the point
	// the point is the parent point 
	map<pair<int,int>, pair<point, DIRECTION>> parentMap;
	bool isQueueInitialized = false;

	// direction array for BFS
	const DIRECTION directions[4] = {NORTH, SOUTH, EAST, WEST};


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

	DIRECTION BFSnextMove() {
		// initialize the point queue if this is the first BFS Run
		if (!isQueueInitialized) {
			point start = car->getLocation();
			pointQueue.push(start);
			parentMap[{start.x, start.y}] = {start, NORTH}; // dummy value to represent the start point
			isQueueInitialized = true;
		}

		// do a run of BFS, popping the front of the pointQueue and taking note of open spots
		point currentPoint = pointQueue.front();
		pointQueue.pop();

		const int DIRECTIONS = 4;
		for (int i = 0; i < DIRECTIONS; i++) {
			// case where the move is open
			if (!car->look(directions[i])) {
				// set nextPoint to currentPoint so we have a reference
				point nextPoint = currentPoint;
				if (directions[i] == EAST) {
					nextPoint.x++;
				} else if (directions[i] == SOUTH) {
					nextPoint.y++;
				} else if (directions[i] == WEST) {
					nextPoint.x--;
				} else if (directions[i] == NORTH) {
					nextPoint.y--;
				}

				// make sure we haven't already been to nextPoint
				pair<int, int> nextPointPair = make_pair(nextPoint.x, nextPoint.y);
				// case where we haven't been to nextPoint
				if (parentMap.find(nextPointPair) == parentMap.end()) {
					parentMap[nextPointPair] = {currentPoint, directions[i]};
					pointQueue.push(nextPoint);
				}
			}
		}

		// show the next move and return it
		point nextPoint = pointQueue.front();

		// this gives the next direction to take
		return parentMap[{nextPoint.x, nextPoint.y}].second;
	}
};


#endif /* RACECARDRIVER_H_ */
