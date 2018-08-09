/*
 * Board.h
 *
 *  Created on: Apr 23, 2018
 *      Author: ariel
 */

#ifndef BOARD_H_
#define BOARD_H_

class Point;

class Board {
public:
	virtual int getPlayer(const Point& pos) const = 0; // 1 for player 1's piece, 2 for 2, 0 if empty
	virtual ~Board() {}
};

#endif /* BOARD_H_ */
