/*
 * FightInfo.h
 *
 *  Created on: Apr 23, 2018
 *      Author: ariel
 */

#ifndef FIGHTINFO_H_
#define FIGHTINFO_H_

class Point;

class FightInfo {
public:
	virtual const Point& getPosition() const = 0;
	virtual char getPiece(int player) const = 0; // R, P, S, B or F (but NOT J)
	virtual int getWinner() const = 0; // 0 - both lost / tie, 1 - player 1 won, 2 - player 2 won
	virtual ~FightInfo() {}
};

#endif /* FIGHTINFO_H_ */
