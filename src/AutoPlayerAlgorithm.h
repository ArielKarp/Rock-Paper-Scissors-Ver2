/*
 * AutoPlayerAlgorithm.h
 *
 *  Created on: Apr 30, 2018
 *      Author: gasha
 */

#ifndef AUTOPLAYERALGORITHM_H_
#define AUTOPLAYERALGORITHM_H_


#include <iostream>
#include <random>
#include "PiecePositionImpl.h"
#include "PlayerAlgorithm.h"
#include "MoveImpl.h"
#include "climits"

#define TOTAL_NUM_OF_PIECES 13
#define THRESHOLD_ONE 		3
#define THRESHOLD_TWO 		6
#define SCORE_HIGH 	  		1000
#define SCORE_MED			750
#define SCORE_LOW			250
#define SCORE_MAX			INT_MAX
#define SCORE_ZERO			0
#define SCORE_NEG			-1000
#define NO_REP				'#'

struct oppPiece {
    PointImpl s_point;
    bool s_is_moved;
    char s_rep;
};

class AutoPlayerAlgorithm: public PlayerAlgorithm {
public:
	AutoPlayerAlgorithm(const int a_playerNum, std::vector<std::pair<char, int> >& a_piecesLimit,  int a_cols, int a_rows);
	void getInitialPositions(int player, std::vector<unique_ptr<PiecePosition>>& vectorToFill);
	void notifyOnInitialBoard(const Board& b, const std::vector<unique_ptr<FightInfo>>& fights);
	void notifyOnOpponentMove(const Move& move); // called only on opponent's move
	void notifyFightResult(const FightInfo& fightInfo); // called only if there was a fight
	unique_ptr<Move> getMove();
	unique_ptr<JokerChange> getJokerChange(); // nullptr if no change is requested
	~AutoPlayerAlgorithm() {}
	std::vector<PiecePositionImpl>::iterator myPieceToFind(const Point& a_point) ;
	std::vector<oppPiece>::iterator oppPieceToFind(const Point& a_point) ;
	int getPlayerNum();
	void fillPossibleMoves(std::vector<std::pair<MoveImpl, int>>& a_possibleMoves, const PiecePositionImpl& a_pieceToMove);
	void fillPossibleMovesScore(std::vector<std::pair<MoveImpl, int>>& a_possibleMoves);
	std::pair<MoveImpl, int> getMaxMoveByScore(const std::vector<std::pair<MoveImpl, int>>& a_possibleMoves);
	int countNumOfStillPieces() const;
	int getScoreOfMove(const MoveImpl& a_move);
	int fightResult(const char a_firstUpper,
			const char a_secondUpper);
private:
	int m_playerNum;
	std::vector<std::pair<char, int> > m_piecesLimit;
	std::vector<PiecePositionImpl> m_algoPieces;
	int m_cols;
	int m_rows;
	std::vector<oppPiece> m_oppPiece;
};


#endif /* AUTOPLAYERALGORITHM_H_ */
