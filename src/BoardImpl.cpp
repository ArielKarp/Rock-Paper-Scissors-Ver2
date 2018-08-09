/*
 * BoardImpl.cpp
 *
 *  Created on: Apr 26, 2018
 *      Author: ariel
 */

#include "BoardImpl.h"


BoardImpl::BoardImpl(int a_rows, int a_cols) :
		m_rows(a_rows), m_cols(a_cols) {
	m_board.resize(m_rows,
			std::vector<std::shared_ptr<PiecePositionImpl>>(m_cols, nullptr));
}

int BoardImpl::getPlayer(const Point& pos) const {
	//returns num of player of the piece in the cell
	int row = pos.getY() - 1;
	int col = pos.getX() - 1;
	if (m_board[row][col] == nullptr) {
		return 0;  // loc is empty
	}
	return m_board[row][col]->getPlayerNum();
}

void BoardImpl::insertPiecePosition(int a_playerNum, const PiecePosition& a_piecePos) {
	//insert the piece of the player in the place
	int row = a_piecePos.getPosition().getY() - 1;
	int col = a_piecePos.getPosition().getX() - 1;
	m_board[row][col] = std::make_shared < PiecePositionImpl > (a_playerNum, a_piecePos);
}

void BoardImpl::removePiecePosition(const PointImpl& a_point) {
	//remove the piece of the player in the place
	int row = a_point.getY() - 1;
	int col = a_point.getX() - 1;
	m_board[row][col] = nullptr;
}

std::ostream& operator<<(std::ostream& os, const BoardImpl& a_board) {
	//prints the board according to the instructions
	std::vector<std::vector<std::shared_ptr<PiecePositionImpl>>>::const_iterator it = a_board.m_board.begin();
	for(; it != a_board.m_board.end(); ++it) {
		std::vector<std::shared_ptr<PiecePositionImpl>>::const_iterator inner_it = it->begin();
		for(; inner_it != it->end(); ++inner_it) {
			if (*inner_it == nullptr) {
				os << " ";
			} else {
				if ((*inner_it)->getPlayerNum()==FIRST_PLAYER)
					os << (*inner_it)->getPiece();
				else{
					char low_char = tolower((*inner_it)->getPiece());
					os << low_char;
				}
			}
		}
		os << std::endl;
	}
	return os;
}

std::shared_ptr<PiecePositionImpl> BoardImpl::getPieceByLocation(const Point& a_location) const {
	int col = a_location.getX()  - 1;
	int row = a_location.getY() - 1;
	return m_board[row][col];
}

void BoardImpl::movePieceLocationOnBoard(const Point& a_From, const Point& a_To) {
	// move piece on the board
	m_board[a_To.getY() - 1][a_To.getX() - 1] = m_board[a_From.getY() - 1][a_From.getX() - 1];
	m_board[a_From.getY() - 1][a_From.getX() - 1] = nullptr;

}
