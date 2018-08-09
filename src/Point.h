/*
 * Point.h
 *
 *  Created on: Apr 23, 2018
 *      Author: ariel
 */

#ifndef POINT_H_
#define POINT_H_

class Point {
public:
	virtual int getX() const = 0;
	virtual int getY() const = 0;
	virtual ~Point() {}
};

#endif /* POINT_H_ */
