/*
 * PositionCommandAnalyzer.cpp
 *
 *  Created on: Apr 3, 2018
 *      Author: ariel
 */

#include "PositionCommandAnalyzer.h"

PositionCommandAnalyzer::PositionCommandAnalyzer(std::string a_inputFilePath) :
		CommandAnalyzer(a_inputFilePath) {
}

FileStatus PositionCommandAnalyzer::getPosCommand(
	std::unique_ptr<PiecePositionImpl>& a_piecePos, int a_playerNum) {
	std::string l_nextPos;
	//gets next line
	FileStatus file_status = getNextLine(l_nextPos);
	if (file_status != OK) {
		return file_status;
	}
	// returns the struct filled!
	if (!parsePosition(l_nextPos, a_piecePos, a_playerNum)) {
		return ERROR;
	}
	return OK;
}

bool PositionCommandAnalyzer::isValidChar(char a_inputChar, bool a_isJoker) {
	// checks whether it is a valid char for pos command -
	switch (a_inputChar) {
	case PieceChar::FLAG:
		if (a_isJoker == true) {
			return false;
		} else {
			return true;
		}
	case PieceChar::BOMB:
		return true;
	case PieceChar::PAPER:
		return true;
	case PieceChar::ROCK:
		return true;
	case PieceChar::SCISSORS:
		return true;
	}
	return false;
}

bool PositionCommandAnalyzer::parsePosition(const std::string& a_position,
		std::unique_ptr<PiecePositionImpl>& a_piecePos, int a_playerNum) {
	int l_player = a_playerNum;
	std::string sep(" ");
	std::vector<std::string> l_posSplited;
	// seperates the command according to the separator
	splitCommand(a_position, sep, l_posSplited);

	// command has the following two formats
	// 1. <piece_char> <x_pos> <y_pos>
	// 2. J <x_pos> <y_pos> <piece_char>
	if (l_posSplited.size() != 3 && l_posSplited.size() != 4) {
		std::cout
				<< "Has too many args! the output should be <PIECE CHAR><X><Y> or J<X><Y><PIECE CHAR>, bad position file for player "
				<< l_player << std::endl;
		return false; // failed, too many elements
	}

	bool l_jokerCommand = false;
	if (l_posSplited.size() == 4) { // second type
		if (l_posSplited[0][0] != 'J') {
			std::cout
					<< "wrong format, no J in the begging! the output should be J<X><Y><PIECE CHAR>, bad position file for player "
					<< l_player << std::endl;
			return false;
		}
		l_jokerCommand = true;

	}

	//checks whether all char are digits
	int starting_indx = 1;
	for (int i = starting_indx; i < (starting_indx + 2); i++) {
		std::string l_temp_string = l_posSplited[i];
		if (!std::all_of(l_temp_string.begin(), l_temp_string.end(),
				::isdigit)) { // all chars are digits
			std::cout
					<< "Not all chars are digits! the output should be <PIECE CHAR><X><Y> or J<X><Y><PIECE CHAR> where X Y are digits, bad position file for player "
					<< l_player << std::endl;
			return false;
		}
	}

	uint sizeOfSplitted = 3;
	char piece_char =
			l_posSplited.size() == sizeOfSplitted ?
					l_posSplited[0][0] : l_posSplited[sizeOfSplitted][0];

	if (!isalpha(piece_char)) {
		std::cout
				<< "PieceChar is not a char the output should be <PIECE CHAR><X><Y> or J<X><Y><PIECE CHAR>, bad position file for player "
				<< l_player << std::endl;
		return false;  // piece char is not char
	}

	if (!isValidChar(piece_char, l_jokerCommand)) {
		// piece char is not valid
		std::cout
				<< "Piece char is not valid! you placed  a piece that cannot move! bad position file for player "
				<< l_player << std::endl;
		return false;
	}

	int l_piece_col = std::stoi(l_posSplited[starting_indx]);
	int l_piece_row = std::stoi(l_posSplited[starting_indx + 1]);

	PointImpl l_tempPoint(l_piece_col, l_piece_row);

	if (l_jokerCommand) {
		PiecePositionImpl l_tempPiece(l_tempPoint, PieceChar::JOKER, piece_char,
				l_player);
		*a_piecePos = l_tempPiece;
	} else {
		// not a joker command
		PiecePositionImpl l_tempPiece(l_tempPoint, piece_char, '#', l_player);
		*a_piecePos = l_tempPiece;
	}

	return true;
}
