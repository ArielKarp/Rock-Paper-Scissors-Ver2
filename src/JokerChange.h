/*
 * JokerChange.h
 *
 *  Created on: Apr 23, 2018
 *      Author: ariel
 */

#ifndef JOKERCHANGE_H_
#define JOKERCHANGE_H_

class Point;

class JokerChange {
public:
	virtual const Point& getJokerChangePosition() const = 0;
	virtual char getJokerNewRep() const = 0; // R, P, S or B (but NOT J and NOT F)
	virtual ~JokerChange() {}
};

#endif /* JOKERCHANGE_H_ */
