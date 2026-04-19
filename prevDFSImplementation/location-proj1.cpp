/**
* file: location-proj1.cpp
* author: Aubrey Bedford
* course 3334
* assignment: Project 1 - Maze Solver
* due date: September 12, 2025
* version 1.1
*
* This is the implementation file for the location class
*/



#include "location-proj1.h"
#include <cassert>

const int MAX_VALUE = 5000, MIN_VALUE = -5000;

/* Location Constructor
 *
 * Sets the base values of a location class.
 *
 */
Location::Location() {
    row = 0;
    col = 0;
    nextDirection = RIGHT;
}

/* iterationBegin()
 *
 * Sets/Resets the iteration status of a location object
 *
 * Return:
 *  The location objects nextDirection is set to RIGHT
 *
 */
void Location::iterationBegin() {
    this->nextDirection = RIGHT;
}

/* iterationCurrent
 *
 * Will output a neighboring location of the given location based upon
 * that locations nextDirection. Produces a copy of the Location to accomplish
 * this task
 *
 * Return:
 *  A neighboring location to the given location
 *
 */
Location Location::iterationCurrent() const {
    Location newLoc;
    //Copies the current location
    newLoc.row = row;
    newLoc.col = col;

    //Modifies it to get the neighbor (if there is one)
    if (!iterationDone()) {
        if (nextDirection == RIGHT) {
            newLoc.col++;
        }
        else if (nextDirection == DOWN) {
            newLoc.row++;
        }
        else if (nextDirection == LEFT) {
            newLoc.col--;
        }
        else if (nextDirection == UP) {
            newLoc.row--;
        }
    }

    return newLoc;
}
/* iterationAdvance
 *
 * Increments the iteration status of a location object. If a location
 * object is already done, it will roll back to its default state.
 *
 * Return:
 *  The incremented next direction
 *
 */
void Location::iterationAdvance() {
    if (iterationDone()) { //Rolls over if iterationDone is true
        iterationBegin();
    }
    else {
        this->nextDirection++;
    }
}
/* iterationDone
 *
 * Checks if the iteration has finished its cycle
 *
 * Returns:
 *  The iteration status of the location object
 *
 */
bool Location::iterationDone() const {
    return this->nextDirection == DONE;
}

/* operator==
 *
 * Checks if the position of two location objects is the same. The iteration
 * status has no bearing on the comparison
 *
 * Parameters:
 *  loc: A second location object for comparison
 * Returns:
 *  Whether the position of the two given location objects is the same
 *
 *
 *
 */
bool Location::operator==(const Location &loc) const {
    return this->row == loc.row && this->col == loc.col;
}

/* operator<<
 *
 * Overloaded to output the row and col of a given location object (temporarily
 * outputting next direction for debugging purposes).
 *
 * Parameters:
 *  os: Any given output stream
 *  loc: A location object for streaming
 * Returns:
 * The output stream with the proper data streamed
 *
 *
 *
 */
ostream &operator<<(ostream &os, const Location &loc) {
    os << loc.row << " " << loc.col;
    return os;
}
/* operator>>
 *
 * Overloaded to take a row and col from standard input and set the location
 * objects corresponding members to these values.
 *
 * Parameters:
 *  os: Any given input stream
 *  loc: A location object for streaming
 * Returns:
 *  The location object with a newly set row and col
 *
 *
 *
 */
istream &operator>>(istream &is, Location &loc) {
    is >> loc.row >> loc.col;
    assert(loc.row >= MIN_VALUE && loc.row <= MAX_VALUE);
    assert(loc.col >= MIN_VALUE && loc.col <= MAX_VALUE);
    return is;
}

