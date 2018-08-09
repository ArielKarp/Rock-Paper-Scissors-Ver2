/*
 * PiecePosition.h
 *
 *  Created on: Apr 23, 2018
 *      Author: ariel
 */

#ifndef PIECEPOSITION_H_
#define PIECEPOSITION_H_

class Point;

class PiecePosition {
public:
	virtual const Point& getPosition() const = 0;
	virtual char getPiece() const = 0; // R, P, S, B, J or F
	virtual char getJokerRep() const = 0; // ONLY for Joker: R, P, S or B -- non-Joker may return #
	virtual ~PiecePosition() {}
};

#endif /* PIECEPOSITION_H_ */
