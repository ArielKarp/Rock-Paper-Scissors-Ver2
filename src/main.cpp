/*
 * main.cpp
 *
 *  Created on: Apr 23, 2018
 *      Author: ariel
 */

#include "PiecePositionImpl.h"
#include "BoardImpl.h"
#include "CommandAnalyzer.h"
#include "GameManager.h"
#include "PositionCommandAnalyzer.h"

#define NUM_OF_ROWS 10
#define NUM_OF_COLS 10
#define PLAYER1_BOARD_NAME "player1.rps_board"
#define PLAYER2_BOARD_NAME "player2.rps_board"
#define PLAYER1_MOVES_NAME "player1.rps_moves"
#define PLAYER2_MOVES_NAME "player2.rps_moves"
#define OUTPUT_FILE_NAME   "rps.output"

void fillPiecesCount(std::vector<std::pair<char, int> >& a_piecesLimit) {
	a_piecesLimit.push_back(std::make_pair(PieceChar::ROCK, 2));
	a_piecesLimit.push_back(std::make_pair(PieceChar::PAPER, 5));
	a_piecesLimit.push_back(std::make_pair(PieceChar::SCISSORS, 1));
	a_piecesLimit.push_back(std::make_pair(PieceChar::BOMB, 2));
	a_piecesLimit.push_back(std::make_pair(PieceChar::JOKER, 2));
	a_piecesLimit.push_back(std::make_pair(PieceChar::FLAG, 1));
}

bool checkPlayerFiles(int a_playerNum){
	auto board_file_name ="";
	board_file_name = (a_playerNum == 1)? PLAYER1_BOARD_NAME : PLAYER2_BOARD_NAME;
    std::ifstream infile(board_file_name);
    return infile.good();
}


bool checkFileExist(int a_num_flag){
	if (a_num_flag == 0)
		return checkPlayerFiles(1)&& checkPlayerFiles(2);
	if (a_num_flag == 1)
		return checkPlayerFiles(1);
	if (a_num_flag == 2)
		return checkPlayerFiles(2);
	return false; // should not get here
}

int main(int argc, char* argv[]) {
	if (argc < 2) {
		std::cout
				<< "Error! Invalid play mode, only file-vs-file, auto-vs-auto, file-vs-auto and auto-vs-file";
		return EXIT_FAILURE;
	}
	std::vector<std::string> l_cmdSplitted;
	std::string l_sep("-");
	CommandAnalyzer l_analyzer;
	l_analyzer.splitCommand(argv[1], l_sep, l_cmdSplitted);
	if ((l_cmdSplitted.size() != 3) || (l_cmdSplitted[1] != "vs"))
		std::cout
				<< "Error! Invalid play mode, only file-vs-file, auto-vs-auto, file-vs-auto and auto-vs-file";
	else if (((l_cmdSplitted[0] != "auto") && (l_cmdSplitted[0] != "file"))
			|| ((l_cmdSplitted[2] != "file") && (l_cmdSplitted[2] != "auto")))
		std::cout
				<< "Error! Invalid play mode, only file-vs-file, auto-vs-auto, file-vs-auto and auto-vs-file";
	else {
		std::vector<std::pair<char, int> > l_piecesLimit;
		fillPiecesCount(l_piecesLimit);
		if (((l_cmdSplitted[0]=="file")&&(l_cmdSplitted[2]=="file"))&&(checkFileExist(0))) {
			GameManager l_rsp(NUM_OF_COLS,NUM_OF_ROWS, l_piecesLimit,
					PLAYER1_BOARD_NAME,
					PLAYER1_MOVES_NAME,
					PLAYER2_BOARD_NAME,
					PLAYER2_MOVES_NAME,
					OUTPUT_FILE_NAME);
			l_rsp.startGame();

		}
		else if ((l_cmdSplitted[0]=="auto")&&(l_cmdSplitted[2]=="auto")) {
			GameManager l_rsp(NUM_OF_ROWS, NUM_OF_COLS, l_piecesLimit,
					OUTPUT_FILE_NAME);
			l_rsp.startGame();

		}
		else if (((l_cmdSplitted[0]=="auto")&&(l_cmdSplitted[2]=="file"))&&(checkFileExist(2))) {
			GameManager l_rsp(false, NUM_OF_ROWS, NUM_OF_COLS, l_piecesLimit,
					PLAYER2_BOARD_NAME,
					PLAYER2_MOVES_NAME,
					OUTPUT_FILE_NAME);
			l_rsp.startGame();

		}
		else if (((l_cmdSplitted[0]=="file")&&(l_cmdSplitted[2]=="auto"))&&(checkFileExist(1))){ // file-auto
				GameManager l_rsp(true,NUM_OF_ROWS, NUM_OF_COLS, l_piecesLimit,
						PLAYER1_BOARD_NAME,
						PLAYER1_MOVES_NAME,
						OUTPUT_FILE_NAME);
				l_rsp.startGame();

		}
		else{
			std::cout << "files required doesn't exist, game was not started";
		}
	}

}
