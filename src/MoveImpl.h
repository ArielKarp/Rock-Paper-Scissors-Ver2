/*
 * MoveImpl.h
 *
 *  Created on: Apr 23, 2018
 *      Author: ariel
 */

#ifndef MOVEIMPL_H_
#define MOVEIMPL_H_

#include "Move.h"
#include "PointImpl.h"

class MoveImpl: public Move {
public:
	MoveImpl(int a_xFrom = 0, int a_yFrom = 0, int a_xTo = 0, int a_yTo = 0);
	MoveImpl(const MoveImpl& a_MoveImpl);
	~MoveImpl() = default;
	MoveImpl& operator=(const MoveImpl& a_MoveImpl);
	const Point& getFrom() const override { return m_PointFrom; };
	const Point& getTo() const override { return m_PointTo; };
	void setTo(PointImpl a_to);
private:
	PointImpl m_PointFrom;
	PointImpl m_PointTo;
};



#endif /* MOVEIMPL_H_ */
