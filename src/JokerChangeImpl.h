/*
 * JokerChangeImpl.h
 *
 *  Created on: Apr 25, 2018
 *      Author: ariel
 */

#ifndef JokerChangeImpl_H_
#define JokerChangeImpl_H_

#include "JokerChange.h"
#include "PointImpl.h"

class JokerChangeImpl: public JokerChange {
public:
	JokerChangeImpl(const PointImpl& a_jokerPoint = PointImpl(), char a_jokerRep = '*');
	JokerChangeImpl& operator=(const JokerChangeImpl& a_rhs);
	~JokerChangeImpl() = default;
	const Point& getJokerChangePosition() const override;
	char getJokerNewRep() const override; // R, P, S or B (but NOT J and NOT F)

private:
	PointImpl m_jokerPoint;
	char m_jokerRep;
};

#endif /* JokerChangeImpl_H_ */
