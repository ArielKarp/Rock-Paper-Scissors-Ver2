/*
 * FightInfoImpl.cpp
 *
 *  Created on: Apr 26, 2018
 *      Author: ariel
 */

#include "FightInfoImpl.h"

FightInfoImpl::FightInfoImpl(const PointImpl& a_fightPoint, char a_player1Piece, char a_player2Piece, int a_winner):
		m_fightPoint(a_fightPoint), m_player1Piece(a_player1Piece), m_player2Piece(a_player2Piece) ,m_winner(a_winner){

}


FightInfoImpl::FightInfoImpl(const Point& a_fightPoint, char a_player1Piece, char a_player2Piece, int a_winner) :
		m_fightPoint(a_fightPoint), m_player1Piece(a_player1Piece), m_player2Piece(a_player2Piece) ,m_winner(a_winner) {
}

const Point& FightInfoImpl::getPosition() const {
	return m_fightPoint;
}

const PointImpl& FightInfoImpl::getPositionImpl() const {
	return m_fightPoint;
}

char FightInfoImpl::getPiece(int player) const { // R, P, S, B or F (but NOT J)
	if (player == PLAYER_1_FIGHT) {
		return m_player1Piece;
	} else {
		return m_player2Piece;
	}
}

int FightInfoImpl::getWinner() const { // 0 - both lost, 1 - player 1 won, 2 - player 2 won
	return m_winner;
}
