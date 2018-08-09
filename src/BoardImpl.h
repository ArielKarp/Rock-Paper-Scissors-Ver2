/*
 * BoardImpl.h
 *
 *  Created on: Apr 26, 2018
 *      Author: ariel
 */

#ifndef BOARDIMPL_H_
#define BOARDIMPL_H_

#include "Board.h"
#include "PiecePositionImpl.h"
#include <vector>
#include <memory>

class BoardImpl: public Board {
public:
	BoardImpl(int a_rows, int a_cols);
	~BoardImpl() = default;
	int getPlayer(const Point& pos) const override;
	void insertPiecePosition(int a_playerNum, const PiecePosition& a_piecePos);
	friend std::ostream& operator<<(std::ostream& os, const BoardImpl& a_board);
	int getRows() { return m_rows; };
	int getCols() { return m_cols; };
	std::shared_ptr<PiecePositionImpl> getPieceByLocation(const Point& a_location) const;
	void removePiecePosition(const PointImpl& a_point);
	void movePieceLocationOnBoard(const Point& a_From, const Point& a_To);
private:
	std::vector<std::vector<std::shared_ptr<PiecePositionImpl>>> m_board;
	int m_rows;
	int m_cols;

};



#endif /* BOARDIMPL_H_ */
