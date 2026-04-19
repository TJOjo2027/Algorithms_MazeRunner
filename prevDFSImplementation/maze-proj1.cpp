/**
* file: stack-proj1.cpp
* author: Aubrey Bedford
* course 3334
* assignment: Project 1 - Maze Solver
* due date: September 12, 2025
* version 1.2
*
* This is the implementation file for the maze class
*/

#include "maze-proj1.h"
#include <sstream>
#include <string>

const int MAX_MAZE_VALUE = 10000, MIN_MAZE_VALUE = 1;

/** Maze Constructor
 *
 * Sets default values for each maze.
 *
 */
Maze::Maze(void) {
  startLocation = Location();
  endLocation = Location();
  validLocations = nullptr;
  validLocationCount = 0;
}

/** Maze Destructor
 *
 * Deletes all valid locations
 */
Maze::~Maze() {
  delete [] validLocations;
}

/** getStartLocation
 *
 * Will return the protected startLocation member
 *
 */
Location Maze::getStartLocation(void) const {
  return startLocation;
}

/** isValidLocation
 *
 * Given a location, the function will search through the maze to find if
 * the location is inside of it.
 *
 *  Parameters:
 *    loc: A given location for searching
 *
 *  Return:
 *    True or False if the location is found in the maze.
 */
bool Maze::isValidLocation(const Location &loc) const {
  bool valid = false;
  for (int i = 0; i < validLocationCount; i++) {
    if (validLocations[i] == loc) {
      valid = true;
    }
  }
  return valid;
}

/** isEndLocation
 *
 * Checks if a given location is the end location
 *
 * Parameters:
 *  loc: A given location to check
 *
 * Return:
 *  True or False if the given location is the end location
 */
bool Maze::isEndLocation(const Location &loc) const {
  return loc == endLocation;
}

/** operator>>
 *
 * Automatically will take from standard input a maze like structure
 * and assign the appropriate members to the given values of locations
 * and integers.
 *
 * Parameters:
 *  is: An input stream
 *  m: The maze which is being inserted into
 *
 *  Return:
 *   All appropriate members are filled and the validLocations array is filled.
 */
istream &operator>>(istream &is, Maze &m) {
  delete [] m.validLocations;
  is >> m.validLocationCount;
  assert(m.validLocationCount >= MIN_MAZE_VALUE &&
    m.validLocationCount <= MAX_MAZE_VALUE);

  m.validLocations = new Location[m.validLocationCount];
  for (int i = 0; i < m.validLocationCount; i++) {
    is >> m.validLocations[i];
  }
  is >> m.startLocation;
  assert(m.isValidLocation(m.startLocation));
  is >> m.endLocation;
  assert(m.isValidLocation(m.endLocation));

  return is;
}