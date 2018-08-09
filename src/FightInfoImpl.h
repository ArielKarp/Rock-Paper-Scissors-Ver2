/*
 * ReFightInfo.h
 *
 *  Created on: Apr 26, 2018
 *      Author: ariel
 */

#ifndef FIGHTINFOIMPL_H_
#define FIGHTINFOIMPL_H_

#include "FightInfo.h"
#include "PointImpl.h"

#define PLAYER_1_FIGHT 1

class FightInfoImpl: public FightInfo {
public:
	FightInfoImpl(const PointImpl& a_fightPoint = PointImpl(), char a_player1Piece = '*', char a_player2Piece = '*', int a_winner = 0);
	FightInfoImpl(const Point& a_fightPoint, char a_player1Piece, char a_player2Piece, int a_winner);
	~FightInfoImpl() {}
	const Point& getPosition() const override;
	const PointImpl& getPositionImpl() const;
	char getPiece(int player) const override; // R, P, S, B or F (but NOT J)
	int getWinner() const override; // 0 - both lost, 1 - player 1 won, 2 - player 2 won
private:
	PointImpl m_fightPoint;
	char m_player1Piece;
	char m_player2Piece;
	int m_winner;
};


#endif /* FIGHTINFOIMPL_H_ */
