/*
 * MoveCommandAnalyzer.cpp
 *
 *  Created on: Apr 3, 2018
 *      Author: ariel
 */

#include "MoveCommandAnalyzer.h"

MoveCommandAnalyzer::MoveCommandAnalyzer(std::string a_inputFilePath) :
		CommandAnalyzer(a_inputFilePath) {
}

FileStatus MoveCommandAnalyzer::getMoveCommand(std::unique_ptr<MoveImpl>& a_moveCommand,
		std::unique_ptr<JokerChangeImpl>& a_jokerChange, int a_playerNum) {
	std::string l_nextMove;
	if (!(isInpuFileStreamGood()))
		return NO_FILE;
	FileStatus file_status = getNextLine(l_nextMove);
	if (file_status != OK) {
		return file_status;
	}
	FileStatus parsing_result = parseMove(l_nextMove, a_moveCommand,
			a_jokerChange, a_playerNum);
	return parsing_result;
}

FileStatus MoveCommandAnalyzer::parseMove(const std::string& a_move,
		std::unique_ptr<MoveImpl>& a_moveCommand,
		std::unique_ptr<JokerChangeImpl>& a_jokerChange, int a_playerNum) {
	std::string sep(" ");
	std::vector<std::string> l_moveSplited;
	splitCommand(a_move, sep, l_moveSplited);
	int l_player = a_playerNum;
	// command is of the following format <from_x> <from_y> <to_x> <to_y> [J: <j_col> <j_row> <new_rep>]
	// check len of returned split
	if (l_moveSplited.size() != 8 && l_moveSplited.size() != 4) {
		std::cout
				<< "Has too many args! the input should be <FROM_X><FROM_Y><TO_X><TO_Y>[J:<JOKER_X><JOKER_Y><NEW_REP>, bad move file for player "
				<< l_player << std::endl;
		return ERROR; // failed, too many elements
	}

	for (int i = 0; i < MOVE_NUM_OF_ENTRIES; i++) {
		std::string l_temp_string = l_moveSplited[i];
		if (!std::all_of(l_temp_string.begin(), l_temp_string.end(),
				::isdigit)) { // all chars are digits
			std::cout
					<< "Not all chars are digits! the input should be <FROM_X><FROM_Y><TO_X><TO_Y>[J:<JOKER_X><JOKER_Y><NEW_REP> where X Y are digits, bad move file for player "
					<< l_player << std::endl;
			return ERROR;
		}
	}

	// check that location is legal
	int src_col = std::stoi(l_moveSplited[0]);
	int src_row = std::stoi(l_moveSplited[1]);
	int dest_col = std::stoi(l_moveSplited[2]);
	int dest_row = std::stoi(l_moveSplited[3]);


	MoveImpl l_tempMove(src_col, src_row, dest_col, dest_row);
	*a_moveCommand = l_tempMove;
	if (l_moveSplited.size() == 8) {
		 // size of move is 8, i.e. we have j position and rep
		// check for J:
		int l_j_location = 4;
		std::string j_string = l_moveSplited[l_j_location];
		if (j_string.size() < 2 || j_string[0] != 'J' || j_string[1] != ':') {
			std::cout
					<< "Wrong input the input should be <FROM_X><FROM_Y><TO_X><TO_Y>[J:<JOKER_X><JOKER_Y><NEW_REP>], bad move file for player "
					<< l_player << std::endl;
			return ERROR;
		}

		// check first two elements indicate location
		int l_starting_pos = 5;
		int l_end_pos = 7;
		for (int i = l_starting_pos; i < l_end_pos; i++) {
			std::string l_temp_string = l_moveSplited[i];
			if (!std::all_of(l_temp_string.begin(), l_temp_string.end(),
					::isdigit)) { // all chars are digits
				std::cout
						<< "Has too many args! the output should be <FROM_X><FROM_Y><TO_X><TO_Y>[J:<JOKER_X><JOKER_Y><NEW_REP>, bad move file for player "
						<< l_player << std::endl;
				return ERROR;
			}
		}
		// passed check
		int j_col = std::stoi(l_moveSplited[5]);
		int j_row = std::stoi(l_moveSplited[6]);

		// check that's a valid char
		char new_rep = l_moveSplited[MAX_NUM_ENTRIES - 1][0];
		if (!isValidChar(new_rep)) {
			std::cout
					<< "New rep is not a valid char! bad move file for player!"
					<< l_player << std::endl;
			return ERROR;
		}
		JokerChangeImpl l_tempJokerChange(PointImpl(j_col, j_row), new_rep);
		*a_jokerChange = l_tempJokerChange;

	}
	return OK;
}

bool MoveCommandAnalyzer::isValidChar(char a_inputChar) {
	// check if inputChar is one the allowed PieceChars
	bool is_valid_char = false;
	switch (a_inputChar) {
	case PieceChar::BOMB:
		is_valid_char = true;
		break;
	case PieceChar::PAPER:
		is_valid_char = true;
		break;
	case PieceChar::ROCK:
		is_valid_char = true;
		break;
	case PieceChar::SCISSORS:
		is_valid_char = true;
		break;
	}
	return is_valid_char;
}

bool MoveCommandAnalyzer::isValidMove(int a_src_col, int a_src_row,
		int a_dest_col, int a_dest_row) {
	// checks that the player can move those directions
	if (abs(a_dest_col - a_src_col) == 1 && a_src_row == a_dest_row) {
		return true;
	}
	if (a_src_col == a_dest_col && abs(a_dest_row - a_src_row) == 1) {
		return true;
	}
	return false;
}

