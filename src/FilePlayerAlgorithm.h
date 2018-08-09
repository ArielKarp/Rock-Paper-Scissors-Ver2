/*
 * FilePlayerAlgorithm.h
 *
 *  Created on: Apr 30, 2018
 *      Author: ariel
 */

#ifndef FILEPLAYERALGORITHM_H_
#define FILEPLAYERALGORITHM_H_

#include "PlayerAlgorithm.h"
#include "MoveImpl.h"
#include "JokerChangeImpl.h"
#include "PositionCommandAnalyzer.h"
#include "MoveCommandAnalyzer.h"
#include "FightInfoImpl.h"

class FilePlayerAlgorithm: public PlayerAlgorithm {
public:
	FilePlayerAlgorithm(const int a_playerNum, const std::string a_positionFileName, const std::string a_moveFileName);
	void getInitialPositions(int player, std::vector<unique_ptr<PiecePosition>>& vectorToFill);
	void notifyOnInitialBoard(const Board& b, const std::vector<unique_ptr<FightInfo>>& fights){ (void)fights; (void)b; return;};
	void notifyOnOpponentMove(const Move& move) { (void)move; return; } // called only on opponent's move
	void notifyFightResult(const FightInfo& fightInfo) { (void)fightInfo; return; } // called only if there was a fight
	std::unique_ptr<Move> getMove();
	std::unique_ptr<JokerChange> getJokerChange(); // nullptr if no change is requested
	int getPlayerNum();
	~FilePlayerAlgorithm() {}
private:
	int m_playerNum;
	std::unique_ptr<PositionCommandAnalyzer> m_positionAnalyzer;
	std::unique_ptr<MoveCommandAnalyzer> m_moveAnalyzer;
	std::shared_ptr<JokerChangeImpl> m_jokerChange;

};

#endif /* FILEPLAYERALGORITHM_H_ */
