/*
 * PointImpl.cpp
 *
 *  Created on: Apr 24, 2018
 *      Author: ariel
 */


#include "PointImpl.h"

PointImpl::PointImpl(int a_x, int a_y) : x(a_x), y(a_y) {}

PointImpl::PointImpl(const PointImpl& a_PointImpl) { x = a_PointImpl.getX(); y = a_PointImpl.getY(); }
PointImpl::PointImpl(const Point& a_Point) { x = a_Point.getX(); y = a_Point.getY(); }

PointImpl& PointImpl::operator=(const PointImpl& a_point) { if (this == &a_point) return *this; this->x = a_point.getX(); this->y = a_point.getY(); return *this; }

PointImpl& PointImpl::operator=(const Point& a_point) { if (this == &a_point) return *this; this->x = a_point.getX(); this->y = a_point.getY(); return *this; }

int PointImpl::getX() const { return x; }

int PointImpl::getY() const { return y; }

void PointImpl::setX(int a_x) { x = a_x; }

void PointImpl::setY(int a_y) { y = a_y; }

bool operator==(const Point& a_lhs, const Point& a_rhs) {
	if (a_lhs.getX() == a_rhs.getX() && a_lhs.getY() == a_rhs.getY()) {
		return true;
	}
	return false;
}
