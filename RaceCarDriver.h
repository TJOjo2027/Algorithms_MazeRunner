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

	DIRECTION nextMove(){
		vector<DIRECTION> pool;

		if(!car->look(EAST))   pool.push_back(EAST);
		if(!car->look(SOUTH))  pool.push_back(SOUTH);
		if(!car->look(NORTH))  pool.push_back(NORTH);
		if(!car->look(WEST))   pool.push_back(WEST);

		return pool[rand() % pool.size()];
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
