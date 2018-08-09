/*
 * PiecePositionImpl.h
 *
 *  Created on: Apr 26, 2018
 *      Author: ariel
 */

#ifndef PIECEPOSITIONIMPL_H_
#define PIECEPOSITIONIMPL_H_

#include "PiecePosition.h"
#include "PointImpl.h"
#include <iostream>

#define FIRST_PLAYER 1
#define SECOND_PLAYER 2
#define TIE_NO_PLAYER 0

//enum representing all possible pieces on the board, including an empty one
enum PieceChar {
	FLAG = 'F', JOKER = 'J', BOMB = 'B', SCISSORS = 'S', PAPER = 'P', ROCK = 'R', EMPTY = ' '
};

class PiecePositionImpl: public PiecePosition {
public:
	PiecePositionImpl(const PointImpl& a_piecePos = PointImpl(), char a_pieceChar = PieceChar::EMPTY, char a_jokerRep = '*', int a_playerNum = 0);
	PiecePositionImpl(const PiecePositionImpl& a_piecePos);
	PiecePositionImpl(int a_playerNum, const PiecePosition& a_piecePos);
	~PiecePositionImpl() = default;
	const Point& getPosition() const override;
	const PointImpl& getPositionImpl() const;
	char getPiece() const override;
	char getJokerRep() const override;
	int getPlayerNum() const;
	void setPlayerNum(int a_playerNum);
	PiecePositionImpl& operator=(const PiecePositionImpl& a_rhs);
	void setNewLocation(const PointImpl& a_newLoc);
	void setNewRep(const char a_newRep);
	friend std::ostream& operator<<(std::ostream& os, const PiecePositionImpl& a_piece);
private:
	PointImpl m_pieceLoc;
	char m_pieceChar;
	char m_jokerRep;
	int m_playerNum;
};


#endif /* PIECEPOSITIONIMPL_H_ */
