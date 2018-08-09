/*
 * MoveImpl.cpp
 *
 *  Created on: Apr 23, 2018
 *      Author: ariel
 */

#include "MoveImpl.h"

MoveImpl::MoveImpl(int a_xFrom, int a_yFrom, int a_xTo, int a_yTo) :
		m_PointFrom(a_xFrom, a_yFrom), m_PointTo(a_xTo, a_yTo) {
}

MoveImpl::MoveImpl(const MoveImpl& a_MoveImpl) :
		m_PointFrom(a_MoveImpl.getFrom().getX(), a_MoveImpl.getFrom().getY()), m_PointTo(
				a_MoveImpl.getTo().getX(), a_MoveImpl.getTo().getY()) {
}

MoveImpl& MoveImpl::operator=(const MoveImpl& a_MoveImpl) {
	if (this == &a_MoveImpl) {
		return *this;
	}
	this->m_PointFrom = a_MoveImpl.getFrom();
	this->m_PointTo = a_MoveImpl.getTo();
	return *this;
}

void MoveImpl::setTo(PointImpl a_to){
	m_PointTo = a_to;
}
