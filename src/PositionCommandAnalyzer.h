/*
 * PositionCommandAnalyzer.h
 *
 *  Created on: Apr 3, 2018
 *      Author: ariel
 */

#ifndef POSITIONCOMMANDANALYZER_H_
#define POSITIONCOMMANDANALYZER_H_

#include "CommandAnalyzer.h"

class PositionCommandAnalyzer: public CommandAnalyzer {
public:

	PositionCommandAnalyzer(std::string a_inputFilePath);
	FileStatus getPosCommand(std::unique_ptr<PiecePositionImpl>& a_piecePos, int a_playerNum);
	bool parsePosition(const std::string& a_position, std::unique_ptr<PiecePositionImpl>& a_piecePos, int a_playerNum);
	bool isValidChar(char a_inputChar, bool a_isJoker);
	PositionCommandAnalyzer& operator=(const PositionCommandAnalyzer& a_commandAnalyzer) = delete;
	PositionCommandAnalyzer (const PositionCommandAnalyzer& a_commandAnalyzer) = delete;

private:
};

#endif /* POSITIONCOMMANDANALYZER_H_ */
