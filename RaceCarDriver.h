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
	set<pair<int,int>> visited;

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
	DIRECTION iterationFlipped(DIRECTION newDir){
		switch(newDir){
			case EAST:  newDir = WEST; break;
			case SOUTH: newDir = NORTH; break;
			case WEST:  newDir = EAST; break;
			case NORTH: newDir = SOUTH; break;
		}
		return newDir;
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
	DIRECTION RandomNextMove(){
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

		// Utilized to track that if all directions have been iterated through
		int directionsTried = 0;

		while (!iterationDone(directionsTried)) {
			// Getting the neighboring point in the current direction
			point neighbor = iterationCurrent(currLoc);

			// Check if the neighboring point is open and unvisited
			if (!car->look(currDir) && visited.find({neighbor.x, neighbor.y}) == visited.end()) {
				 DIRECTION moveDir = currDir; // Store the direction to move before modifying currDir

				// If it is, push the current direction to the stack and return it
				iterationBegin(); // Reset the current direction to EAST for the next iteration

				// Mark the current location as visited
				visited.insert({neighbor.x, neighbor.y});
				
				dfsPath.push(moveDir); // Push the direction to the stack before returning
				return moveDir;
			} 
			
			else {
				// If it isn't, advance to the next direction and increment the directionsTried counter
				iterationAdvance();
				directionsTried++;
			}
		}

		// If all directions have been tried, we need to backtrack
		if (!dfsPath.empty()) {
			DIRECTION backtrackDir = dfsPath.top();
			dfsPath.pop();
			return iterationFlipped(backtrackDir); // Return the direction to backtrack
		}

		// If the stack is empty, then we have backtracked all the way to the start and there are no more moves to make
		return EAST; // Default return value (can be changed as needed)

		

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

		// this case should never happen because the mazes have guaranteed solutions
		if (pointQueue.empty()) {
			assert(false);
			return EAST;
		}

		// take note of the real location of the car
		point realLocation = car->getLocation();

		point currentPoint = pointQueue.front();
		pointQueue.pop();

		// car is set to the current point so we can look around it and find its neighbors
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

		// set back to the real location of the car before returning the next move
		car->setLocation(realLocation);

		// this case should never happen because the mazes have guaranteed solutions
		if (pointQueue.empty()) {
			assert(false);
			return EAST;
		}

		point nextPoint = pointQueue.front();
		int displacementX = nextPoint.x - realLocation.x;
		int displacementY = nextPoint.y - realLocation.y;
		// based on the displacement, determine the direction to move
		// if there are no points, skip it
		if (displacementX == 1 && displacementY == 0) {
			return EAST;
		}
		else if (displacementX == -1 && displacementY == 0) {
			return WEST;
		}
		else if (displacementX == 0 && displacementY == 1) {
			return SOUTH;
		}
		else if (displacementX == 0 && displacementY == -1) {
			return NORTH;
		}
		else {
			pointQueue.pop();
			return BFSNextMove();
		}
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