/*
 * MoveCommandAnalyzer.h
 *
 *  Created on: Apr 3, 2018
 *      Author: ariel
 */

#ifndef MOVECOMMANDANALYZER_H_
#define MOVECOMMANDANALYZER_H_

#include "CommandAnalyzer.h"
#include <math.h>

class MoveCommandAnalyzer: public CommandAnalyzer {
public:
	MoveCommandAnalyzer(std::string a_inputFilePath);
	FileStatus getMoveCommand(std::unique_ptr<MoveImpl>& a_moveCommand, std::unique_ptr<JokerChangeImpl>& a_jokerChange, int a_playerNum);
	FileStatus parseMove(const std::string& a_move, std::unique_ptr<MoveImpl>& a_moveCommand, std::unique_ptr<JokerChangeImpl>& a_jokerChange, int a_playerNum);
	bool isValidChar(char a_inputChar) override;
	static bool isValidMove(int a_src_x, int a_src_y, int a_dest_x, int a_dest_y);
	MoveCommandAnalyzer& operator=(const MoveCommandAnalyzer& a_commandAnalyzer) = delete;
	MoveCommandAnalyzer (const MoveCommandAnalyzer& a_commandAnalyzer) = delete;
private:

};

#endif /* MOVECOMMANDANALYZER_H_ */
