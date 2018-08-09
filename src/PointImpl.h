/*
 * PointImpl.h
 *
 *  Created on: Apr 23, 2018
 *      Author: ariel
 */

#ifndef POINTIMPL_H_
#define POINTIMPL_H_

#include "Point.h"

class PointImpl: public Point {
public:
	PointImpl(int a_x = -1, int a_y = -1);
	PointImpl(const PointImpl& a_PointImpl);
	PointImpl(const Point& a_Point);
	~PointImpl() = default;
	PointImpl& operator=(const PointImpl& a_point);
	PointImpl& operator=(const Point& a_point);
	friend bool operator==(const Point& a_lhs, const Point& a_rhs);
	int getX() const override;
	int getY() const override;
	void setX(int a_x);
	void setY(int a_y);
private:
	int x;
	int y;
};



#endif /* POINTIMPL_H_ */
