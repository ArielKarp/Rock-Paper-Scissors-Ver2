/*
 * PiecePositionImpl.cpp
 *
 *  Created on: Apr 26, 2018
 *      Author: ariel
 */

#include "PiecePositionImpl.h"

PiecePositionImpl::PiecePositionImpl(const PointImpl& a_piecePos,
		char a_pieceChar, char a_jokerRep, int a_playerNum) :
		m_pieceLoc(a_piecePos), m_pieceChar(a_pieceChar), m_jokerRep(a_jokerRep), m_playerNum(a_playerNum) {
}

PiecePositionImpl::PiecePositionImpl(const PiecePositionImpl& a_piecePos): m_pieceLoc(a_piecePos.m_pieceLoc) {
		m_pieceChar = a_piecePos.getPiece();
		m_jokerRep = a_piecePos.getJokerRep();
		m_playerNum = a_piecePos.getPlayerNum();
}

PiecePositionImpl::PiecePositionImpl(int a_playerNum, const PiecePosition& a_piecePos) : m_pieceLoc(a_piecePos.getPosition()) {
	m_pieceChar = a_piecePos.getPiece();
	m_jokerRep = a_piecePos.getJokerRep();
	m_playerNum = a_playerNum;
}

const Point& PiecePositionImpl::getPosition() const {
	return m_pieceLoc;
}

const PointImpl& PiecePositionImpl::getPositionImpl() const {
	return m_pieceLoc;
}

char PiecePositionImpl::getPiece() const {
	return m_pieceChar;
}

char PiecePositionImpl::getJokerRep() const {
	return m_jokerRep;
}

int PiecePositionImpl::getPlayerNum() const {
	return m_playerNum;
}


PiecePositionImpl& PiecePositionImpl::operator=(const PiecePositionImpl& a_rhs) {
	if (this == &a_rhs) {
		return *this;
	}
	m_pieceLoc = a_rhs.getPosition();
	m_pieceChar = a_rhs.getPiece();
	m_jokerRep = a_rhs.getJokerRep();
	m_playerNum = a_rhs.getPlayerNum();
	return *this;
}

void PiecePositionImpl::setNewLocation(const PointImpl& a_newLoc) {
	m_pieceLoc = a_newLoc;
}

void PiecePositionImpl::setNewRep(const char a_newRep){
	m_jokerRep = a_newRep;
}

void PiecePositionImpl::setPlayerNum(int a_playerNum) {
	m_playerNum = a_playerNum;
}

std::ostream& operator<<(std::ostream& os, const PiecePositionImpl& a_piece) {
	// prints the symbol - if the symbol is empty - prints a space
	if (a_piece.getPiece() == PieceChar::EMPTY){
		os << " ";
	}
	else{
		// prints the symbol (case sensitive)
		if (a_piece.getPlayerNum() == FIRST_PLAYER){
			os << char(toupper(a_piece.getPiece()));
		}
		else{
			os << char(tolower(a_piece.getPiece()));
		}
	}
	return os;
}
