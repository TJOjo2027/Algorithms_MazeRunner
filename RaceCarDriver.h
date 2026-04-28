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
	const DIRECTION directions[4] = {EAST, SOUTH, NORTH, WEST};


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
	
	// TJ's BFS Next Move Implementation

	void initializeBFS() {
		point start = car->getLocation();
		pointQueue.push(start);
		parentMap[{start.x, start.y}] = {start, NORTH}; // dummy value to represent the start point
		isQueueInitialized = true;
	}

	DIRECTION BFSNextMove() {
		// initialize the point queue if this is the first BFS Run
		if (!isQueueInitialized) {
			initializeBFS();
		}

		// case where queue is empty before looking for next move
		if (pointQueue.empty()) {
			return EAST;
		}

		// do a run of BFS, popping the front of the pointQueue and taking note of open spots
		point currentPoint = pointQueue.front();
		pointQueue.pop();

		// set the racer's location to the location of the BFS actions and store the previous location for when its reset
		point realLocation = car->getLocation();
		car->setLocation(currentPoint);

		const int DIRECTIONS = 4;

		for (int i = 0; i < DIRECTIONS; i++) {
			// case where the move is open
			if (!car->look(directions[i])) {
				// set nextPoint to currentPoint so we have a reference
				point neighbor = currentPoint;
				if (directions[i] == EAST) {
					neighbor.x++;
				} else if (directions[i] == SOUTH) {
					neighbor.y++;
				} else if (directions[i] == WEST) {
					neighbor.x--;
				} else if (directions[i] == NORTH) {
					neighbor.y--;
				}

				// make sure we haven't already been to nextPoint
				pair<int, int> neighborPair = make_pair(neighbor.x, neighbor.y);
				// case where we haven't been to neighbor
				if (parentMap.find(neighborPair) == parentMap.end()) {
					parentMap[neighborPair] = {currentPoint, directions[i]};
					pointQueue.push(neighbor);
				}
			}
		}

		car->setLocation(realLocation);

		// case where queue is empty after looking for neighbors
		if (pointQueue.empty()) {
			return EAST;
		}

		// show the next move and return it
		point nextPoint = pointQueue.front();

		// this gives the next direction to take
		return parentMap[{nextPoint.x, nextPoint.y}].second;
	}

	// this is gievn that we keep track of the start and end points of the maze
	vector<DIRECTION> reconstructPath(point start, point end) {
		vector<DIRECTION> path;
		point current = end;

		while (!(current.x == start.x && current.y == start.y)) {
			pair<point, DIRECTION> parent = parentMap[{current.x, current.y}];
			path.push_back(parent.second);
			current = parent.first;
		}

		reverse(path.begin(), path.end());
		return path;
	}

	
	DIRECTION FloodFillNextMove() {
		
	}

	DIRECTION nextMoveTeamOne() {
		
	}

};


#endif /* RACECARDRIVER_H_ */