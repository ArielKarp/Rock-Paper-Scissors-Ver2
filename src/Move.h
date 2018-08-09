/*
 * Move.h
 *
 *  Created on: Apr 23, 2018
 *      Author: ariel
 */

#ifndef MOVE_H_
#define MOVE_H_

class Point;

class Move{
public:
	virtual const Point& getFrom() const = 0;
	virtual const Point& getTo() const = 0;
	virtual ~Move() {}

};

#endif /* MOVE_H_ */
