/*
 * GameManager.h
 *
 *  Created on: Apr 30, 2018
 *      Author: gasha
 */

#ifndef GAMEMANAGER_H_
#define GAMEMANAGER_H_

#include "FilePlayerAlgorithm.h"
#include "AutoPlayerAlgorithm.h"
#include "BoardImpl.h"

#define PLAYER_ONE 1
#define PLAYER_TWO 2
#define NO_PLAYER  0
#define NOT_JOEKR  '#'
#define ONE_FLAG   1
#define MAX_MOVES 100

enum GameStatus {
	PLAYER1_WIN_FLAGS,
	PLAYER2_WIN_FLAGS,
	PLAYER1_WIN_MOVING_PIECES,
	PLAYER2_WIN_MOVING_PIECES,
	TIE,
	TIE_NO_FLAGS,
	PLAYER1_LOSE_BAD_POS,
	PLAYER2_LOSE_BAD_POS,
	TIE_BAD_POS,
	PLAYER1_LOSE_BAD_MOVE,
	PLAYER2_LOSE_BAD_MOVE,
	OPEN_FAIL_FAILED,
	CONTINUE,
	TIE_NO_MOVING,
	TIE_NO_FIGHT
};


class GameManager{
public:
	GameManager(int a_N, int a_M, std::vector<std::pair<char, int> >& a_piecesLimit,
			const std::string& a_player1PositionFileName,
			const std::string& a_player1MovesFileName,
			const std::string& a_player2PositionFileName,
			const std::string& a_player2MovesFileName,
			const std::string& a_outPutName); // file-vs-file
	GameManager(int a_N, int a_M, std::vector<std::pair<char, int> >& a_piecesLimit,
			const std::string& a_outPutName); // auto-vs-auto
	GameManager(bool a_bool, int a_N, int a_M, std::vector<std::pair<char, int> >& a_piecesLimit,
			const std::string& a_playerPositionFileName,
			const std::string& a_playerMovesFileName,
			const std::string& a_outPutName); // if bool true: file-vs-auto, else auto-vs-file
	~GameManager() = default;
	void changeCurrentPlayer();
	void setPiecesOnBoard(int a_playerNum, std::vector<std::unique_ptr<PiecePosition>>& a_inPiecesVect, std::vector<std::unique_ptr<FightInfo>>& a_outFightVec);
	bool checkPositioning(int a_playerNum, std::vector<std::unique_ptr<PiecePosition>>& a_inPiecesVect);
	bool checkMove(std::unique_ptr<Move>& a_move, std::unique_ptr<JokerChange>& a_jokerChange);
	int winnerNumByStatus() const;
	std::string reasonByStatus() const;
	bool isPointOnBoard(int a_col, int a_row, int a_board_cols, int a_board_rows);
	bool isValidMove(int a_src_col, int a_src_row,
			int a_dest_col, int a_dest_row);
	bool canMove(char a_pieceChar);
	FightInfoImpl doMove(int a_playerNum, std::unique_ptr<Move>& a_move, std::unique_ptr<JokerChange>& a_jokerChange);
	void initGame();
	void startGame();
	int fightResult(const char a_firstUpper, const char a_secondUpper);
	GameManager(const GameManager& a_game) = delete;
	GameManager& operator=(const GameManager& a_game) = delete;
	friend std::ostream& operator<<(std::ostream& os, const GameManager& a_game);
	int commenceFight(const PiecePosition& a_firstPlayer, const PiecePosition& a_secondPlayer);
	void checkStatus();
	char getRealPiece(const PiecePosition& a_piecePos) const;
	bool checkTwoInSamePos(std::vector<std::unique_ptr<PiecePosition>>& a_inPiecesVect, const Point& a_point);
	void increasePiecesCount(const char a_pieceRep, int a_playerNum);
	int findVecPieceIndex(const char a_pieceRep, std::vector<std::pair<char, int> > a_vec);
	bool checkPosLimit(int a_player_num);
	int getLimitByPiece(const std::vector<std::pair<char, int> >& a_piecesLimit, const char& a_lookup);




private:
	std::vector<std::pair<char, int> > m_piecesLimit;
	std::vector<std::pair<char, int> > m_player1Limit;
	std::vector<std::pair<char, int> > m_player2Limit;
	BoardImpl m_Board;
	std::shared_ptr<PlayerAlgorithm> m_player1;
	std::shared_ptr<PlayerAlgorithm> m_player2;
	std::shared_ptr<PlayerAlgorithm> m_current_player;
	int m_current_player_num;
	//std::unique_ptr<BoardImpl> m_boardPtr;
	GameStatus m_status;
	std::unique_ptr<std::ofstream> m_outFileStream;
	std::string m_outFileName;
	int m_moves_no_fight;

};



#endif /* GAMEMANAGER_H_ */
