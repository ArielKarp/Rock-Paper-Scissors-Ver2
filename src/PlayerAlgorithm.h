/*
 * PlayerAlgorithm.h
 *
 *  Created on: Apr 23, 2018
 *      Author: ariel
 */

#ifndef PLAYERALGORITHM_H_
#define PLAYERALGORITHM_H_

#include <vector>
#include <memory> // for unique_ptr
#include "Point.h"
#include "PiecePosition.h"
#include "Board.h"
#include "FightInfo.h"
#include "Move.h"
#include "JokerChange.h"

using std::unique_ptr;

class PlayerAlgorithm {
public:
	virtual void getInitialPositions(int player, std::vector<unique_ptr<PiecePosition>>& vectorToFill) = 0;
	virtual void notifyOnInitialBoard(const Board& b, const std::vector<unique_ptr<FightInfo>>& fights) = 0;
	virtual void notifyOnOpponentMove(const Move& move) = 0; // called only on opponent's move
	virtual void notifyFightResult(const FightInfo& fightInfo) = 0; // called only if there was a fight
	virtual unique_ptr<Move> getMove() = 0;
	virtual unique_ptr<JokerChange> getJokerChange() = 0; // nullptr if no change is requested
	virtual ~PlayerAlgorithm() {}
};


#endif /* PLAYERALGORITHM_H_ */
