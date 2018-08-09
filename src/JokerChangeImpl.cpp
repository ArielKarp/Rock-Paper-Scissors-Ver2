/*
 * JokerChangeImpl.cpp
 *
 *  Created on: Apr 26, 2018
 *      Author: ariel
 */

#include "JokerChangeImpl.h"

JokerChangeImpl::JokerChangeImpl(const PointImpl& a_jokerPoint, char a_jokerRep): m_jokerPoint(a_jokerPoint), m_jokerRep(a_jokerRep) {}

const Point& JokerChangeImpl::getJokerChangePosition() const {
	return m_jokerPoint;
}

char JokerChangeImpl::getJokerNewRep() const { // R, P, S or B (but NOT J and NOT F)
	return m_jokerRep;
}

JokerChangeImpl& JokerChangeImpl::operator=(const JokerChangeImpl& a_rhs) {
	if (this == &a_rhs) {
		return *this;
	}
	m_jokerPoint = a_rhs.getJokerChangePosition();
	m_jokerRep = a_rhs.getJokerNewRep();
	return *this;
}
