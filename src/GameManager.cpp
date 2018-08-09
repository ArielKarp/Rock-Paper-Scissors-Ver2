/*
 * GameManager.cpp
 *
 *  Created on: Apr 30, 2018
 *      Author: gasha
 */

#include "GameManager.h"

void createEmptyPicCount(std::vector<std::pair<char, int> >& a_piecesLimit) {
	//the function initilalizes an empty pices limit for every player
	a_piecesLimit.push_back(std::make_pair(PieceChar::ROCK, 0));
	a_piecesLimit.push_back(std::make_pair(PieceChar::PAPER, 0));
	a_piecesLimit.push_back(std::make_pair(PieceChar::SCISSORS, 0));
	a_piecesLimit.push_back(std::make_pair(PieceChar::BOMB, 0));
	a_piecesLimit.push_back(std::make_pair(PieceChar::JOKER, 0));
	a_piecesLimit.push_back(std::make_pair(PieceChar::FLAG, 0));
}

GameManager::GameManager(int a_N, int a_M,
		std::vector<std::pair<char, int> >& a_piecesLimit,
		const std::string& a_player1PositionFileName,
		const std::string& a_player1MovesFileName,
		const std::string& a_player2PositionFileName,
		const std::string& a_player2MovesFileName,
		const std::string& a_outPutName) :
		m_piecesLimit(a_piecesLimit), m_Board(a_N, a_M), m_outFileName(
				a_outPutName) {
	// file-vs-file constructor
	m_player1 = std::make_shared<FilePlayerAlgorithm>(1,
			a_player1PositionFileName, a_player1MovesFileName);
	m_player2 = std::make_shared<FilePlayerAlgorithm>(2,
			a_player2PositionFileName, a_player2MovesFileName);
	m_status = GameStatus::CONTINUE;
	m_current_player = m_player1;
	m_current_player_num = FIRST_PLAYER;
	m_outFileStream = std::make_unique<std::ofstream>(m_outFileName);
	m_moves_no_fight = 0;
	createEmptyPicCount(m_player1Limit);
	createEmptyPicCount(m_player2Limit);

}

GameManager::GameManager(int a_N, int a_M,
		std::vector<std::pair<char, int> >& a_piecesLimit,
		const std::string& a_outPutName) :
		m_piecesLimit(a_piecesLimit), m_Board(a_N, a_M), m_outFileName(
				a_outPutName) {
	// auto-vs-auto constructor
	m_player1 = std::make_shared<AutoPlayerAlgorithm>(FIRST_PLAYER, m_piecesLimit, a_N,
			a_M);
	m_player2 = std::make_shared<AutoPlayerAlgorithm>(SECOND_PLAYER, m_piecesLimit, a_N,
			a_M);
	m_status = GameStatus::CONTINUE;
	m_current_player = m_player1;
	m_current_player_num = FIRST_PLAYER;
	m_outFileStream = std::make_unique<std::ofstream>(m_outFileName);
	m_moves_no_fight = 0;
	createEmptyPicCount(m_player1Limit);
	createEmptyPicCount(m_player2Limit);
}

GameManager::GameManager(bool a_bool, int a_N, int a_M,
		std::vector<std::pair<char, int> >& a_piecesLimit,
		const std::string& a_playerPositionFileName,
		const std::string& a_playerMovesFileName,
		const std::string& a_outPutName) :
		m_piecesLimit(a_piecesLimit), m_Board(a_N, a_M), m_outFileName(
				a_outPutName) {
	// if bool true: file-vs-auto, else auto-vs-file constructor
	if (a_bool) {
		m_player1 = std::make_shared<FilePlayerAlgorithm>(FIRST_PLAYER,
				a_playerPositionFileName, a_playerMovesFileName);
		m_player2 = std::make_shared<AutoPlayerAlgorithm>(SECOND_PLAYER, m_piecesLimit, a_N,
				a_M);
	} else {
		m_player1 = std::make_shared<AutoPlayerAlgorithm>(FIRST_PLAYER, m_piecesLimit, a_N,
				a_M);
		m_player2 = std::make_shared<FilePlayerAlgorithm>(SECOND_PLAYER,
				a_playerPositionFileName, a_playerMovesFileName);
	}
	m_status = GameStatus::CONTINUE;
	m_current_player = m_player1;
	m_current_player_num = FIRST_PLAYER;
	m_outFileStream = std::make_unique<std::ofstream>(m_outFileName);
	m_moves_no_fight = 0;
	createEmptyPicCount(m_player1Limit);
	createEmptyPicCount(m_player2Limit);
}

void GameManager::changeCurrentPlayer() {
	if (m_current_player == m_player1) {
		m_current_player = m_player2;
		m_current_player_num = SECOND_PLAYER;
	} else {
		m_current_player = m_player1;
		m_current_player_num = FIRST_PLAYER;
	}
}

void GameManager::setPiecesOnBoard(int a_playerNum,
		std::vector<std::unique_ptr<PiecePosition>>& a_inPiecesVect,
		std::vector<std::unique_ptr<FightInfo>>& a_outFightVec) {
	// check if ops piece is in location
	// do fight - and add to a_outFight
	// set piece on board
	// iterate over a_inPieceVect
	for (auto& l_ptrPiece : a_inPiecesVect) {
		// if board is empty
		if (m_Board.getPlayer(l_ptrPiece->getPosition()) == NO_PLAYER) {
			m_Board.insertPiecePosition(a_playerNum, *l_ptrPiece);
		} else {  // position is valid, i.e., this is a fight
			std::shared_ptr<PiecePositionImpl> l_tempBoardPiece =
					m_Board.getPieceByLocation(l_ptrPiece->getPosition()); // ops piece
			std::unique_ptr<FightInfoImpl> l_tempFightPtr;
			int rc = commenceFight(*l_tempBoardPiece, *l_ptrPiece);
			if (rc == FIRST_PLAYER) {
				// player 1 won
				// change pointed piece on board
				// make sure old piece is not "dead"
				l_tempFightPtr = std::make_unique<FightInfoImpl>(
						l_ptrPiece->getPosition(), getRealPiece(*l_ptrPiece),
						getRealPiece(*l_tempBoardPiece), PLAYER_ONE);

			}
			if (rc == SECOND_PLAYER) {
				// create fightInfo
				l_tempFightPtr = std::make_unique<FightInfoImpl>(
						l_ptrPiece->getPosition(), getRealPiece(*l_ptrPiece),
						getRealPiece(*l_tempBoardPiece), PLAYER_TWO);
				m_Board.getPieceByLocation(l_ptrPiece->getPosition())->setNewLocation(
						l_tempBoardPiece->getPosition()); // set piece loc
				m_Board.removePiecePosition(l_tempBoardPiece->getPosition());
				m_Board.insertPiecePosition(PLAYER_TWO, *l_ptrPiece);

			}
			if (rc == TIE_NO_PLAYER) {
				// remove both players from board and return fight result
				m_Board.removePiecePosition(
						l_tempBoardPiece->getPositionImpl());
				l_tempFightPtr = std::make_unique<FightInfoImpl>(
						l_ptrPiece->getPosition(), getRealPiece(*l_ptrPiece),
						getRealPiece(*l_tempBoardPiece), NO_PLAYER);
				m_Board.removePiecePosition(l_tempBoardPiece->getPosition());

			}
			a_outFightVec.push_back(std::move(l_tempFightPtr));
		}
	}
}

int GameManager::fightResult(const char a_firstUpper,
		const char a_secondUpper) {
	//the func goes over all the potential fights and returns the result - 0 if tie, 1- if player 1 wins and 2 if player 2 wins
	if ((a_firstUpper == a_secondUpper) || (a_firstUpper == PieceChar::BOMB)
			|| (a_secondUpper == PieceChar::BOMB)) {
		return TIE_NO_PLAYER;
	} else if (a_secondUpper == PieceChar::FLAG) {
		return FIRST_PLAYER;
	} else if (a_firstUpper == PieceChar::FLAG) {
		return SECOND_PLAYER;
	} else if ((a_firstUpper == PieceChar::PAPER)
			&& (a_secondUpper == PieceChar::SCISSORS)) {
		return SECOND_PLAYER;
	} else if ((a_secondUpper == PieceChar::PAPER)
			&& (a_firstUpper == PieceChar::SCISSORS)) {
		return FIRST_PLAYER;
	} else if ((a_firstUpper == PieceChar::ROCK)
			&& (a_secondUpper == PieceChar::PAPER)) {
		return SECOND_PLAYER;
	} else if ((a_secondUpper == PieceChar::ROCK)
			&& (a_firstUpper == PieceChar::PAPER)) {
		return FIRST_PLAYER;
	} else if ((a_firstUpper == PieceChar::SCISSORS)
			&& (a_secondUpper == PieceChar::ROCK)) {
		return SECOND_PLAYER;
	} else { //supposed to get here only if the second player is scissors and the first is rock
		return FIRST_PLAYER;
	}
}

int GameManager::commenceFight(const PiecePosition& a_firstPlayer,
		const PiecePosition& a_secondPlayer) {
	// returns fight result after extracting the real char from all players
	char l_firstUpper, l_secondUpper;
	// check for joker
	if (a_firstPlayer.getJokerRep() == NOT_JOEKR) {
		l_firstUpper = toupper(a_firstPlayer.getPiece());
	} else {
		l_firstUpper = toupper(a_firstPlayer.getJokerRep());
	}
	if (a_secondPlayer.getJokerRep() == NOT_JOEKR) {
		l_secondUpper = toupper(a_secondPlayer.getPiece());
	} else {
		l_secondUpper = toupper(a_secondPlayer.getJokerRep());
	}
	int res = fightResult(l_firstUpper, l_secondUpper);
	return res;
}

bool GameManager::isPointOnBoard(int a_col, int a_row, int a_board_cols,
		int a_board_rows) {
	//checks whether the pos is between 1 and N and 1 and M returns true if so
	if (a_col < 1 || a_col > a_board_cols) {
		return false;
	}
	if (a_row < 1 || a_row > a_board_rows) {
		return false;
	}
	return true;
}

bool GameManager::checkTwoInSamePos(
		std::vector<std::unique_ptr<PiecePosition>>& a_inPiecesVect,
		const Point& a_point) {
	// checks whether the vec contains more than one piece in the same point in the vect. returns false if so
	int count = 0;
	for (auto& l_ptrPiece : a_inPiecesVect) {
		if ((a_point.getX() == l_ptrPiece->getPosition().getX())
				&& (a_point.getY() == l_ptrPiece->getPosition().getY()))
			count++;
	}
	if (count != 1)
		return false;
	return true;
}

bool GameManager::checkPosLimit(int a_player_num){
	// the func returns false if the player placed more figures than he can by the rules
	std::vector<std::pair<char, int> > l_vecPlayerLimit = (a_player_num == FIRST_PLAYER) ? m_player1Limit : m_player2Limit;
	{
		std::vector<std::pair<char, int> >::const_iterator it = m_piecesLimit.begin();
			for (; it != m_piecesLimit.end(); ++it) {
				char l_pieceType = it->first;
				int l_playersCount = getLimitByPiece(l_vecPlayerLimit, l_pieceType);
				int l_gameLimit = getLimitByPiece(m_piecesLimit, l_pieceType);
				if (l_playersCount > l_gameLimit) {
					// if more that limit were positioned
					return false;
				}
			}
			return true;
	}
}

bool GameManager::checkPositioning(int a_player_num,
		std::vector<std::unique_ptr<PiecePosition>>& a_inPiecesVect) {
	bool rc = false;
	int num_of_flags = 0;
	for (auto& l_ptrPiece : a_inPiecesVect) {
		// check location
		int col = l_ptrPiece->getPosition().getX();
		int row = l_ptrPiece->getPosition().getY();
		if (!isPointOnBoard(col, row, m_Board.getCols(), m_Board.getRows())) {
			return rc;
		}
		// check overriding self piece
		if (!(checkTwoInSamePos(a_inPiecesVect, l_ptrPiece->getPosition()))) {
			return rc;
		}
		if (m_Board.getPlayer(l_ptrPiece->getPosition()) == a_player_num) {
			return rc;
		}
		//count that there is enough flags
		if (toupper(getRealPiece(*l_ptrPiece)) == PieceChar::FLAG)
			num_of_flags += 1;
		increasePiecesCount(l_ptrPiece->getPiece(),a_player_num); // increase limit
	}
	if (!checkPosLimit(a_player_num)) // check piece limits is ok
		return rc;
	if (num_of_flags != ONE_FLAG) // check there is one flag
		return rc;
	rc = true;
	return rc;
}

bool GameManager::isValidMove(int a_src_col, int a_src_row, int a_dest_col,
		int a_dest_row) {
	//returns true if there is only one cell move vertically or horizontally
	if (abs(a_dest_col - a_src_col) == 1 && a_src_row == a_dest_row) {
		return true;
	}
	if (a_src_col == a_dest_col && abs(a_dest_row - a_src_row) == 1) {
		return true;
	}
	return false;
}

bool GameManager::canMove(char a_pieceChar) {
	// the func returns false if the piece is flag bomb or there is no piece
	if ((toupper(a_pieceChar) == PieceChar::BOMB)
			|| (toupper(a_pieceChar) == PieceChar::EMPTY)
			|| (toupper(a_pieceChar) == PieceChar::FLAG)) {
		return false;
	}
	return true;
}

FightInfoImpl GameManager::doMove(int a_playerNum,
		std::unique_ptr<Move>& a_move,
		std::unique_ptr<JokerChange>& a_jokerChange) {
	FightInfoImpl l_fight;
	if (m_Board.getPieceByLocation(a_move->getTo()) == nullptr) { //the piece moves to an empty place
		m_Board.movePieceLocationOnBoard(a_move->getFrom(), a_move->getTo()); // move piece on board
		m_Board.getPieceByLocation(a_move->getTo())->setNewLocation(
				a_move->getTo()); // update pieces new loc
		return l_fight;
	} else { // there is a fight
		char l_first_player_char;
		char l_second_player_char;
		std::shared_ptr<PiecePositionImpl> l_opsPiece =
		m_Board.getPieceByLocation(a_move->getTo());// ops piece
		std::shared_ptr<PiecePositionImpl> l_myPiece =
		m_Board.getPieceByLocation(a_move->getFrom());// my piece
		std::unique_ptr<FightInfoImpl> l_tempFightPtr;
		int l_isFirstPlayer = a_playerNum == FIRST_PLAYER ? FIRST_PLAYER : SECOND_PLAYER;// first player num
		int l_opPlayerNum = a_playerNum == FIRST_PLAYER ? SECOND_PLAYER : FIRST_PLAYER;// op player num
		int l_fight_result = -1;
		if (m_current_player_num == FIRST_PLAYER) { // send correctly to the func according to player
			l_first_player_char = getRealPiece(*l_myPiece);
			l_second_player_char = getRealPiece(*l_opsPiece);
			l_fight_result = commenceFight(*l_myPiece, *l_opsPiece);
		} else {
			l_first_player_char = getRealPiece(*l_opsPiece);
			l_second_player_char = getRealPiece(*l_myPiece);
			l_fight_result = commenceFight(*l_opsPiece, *l_myPiece);
		}
		if (l_fight_result == TIE_NO_PLAYER) { // tie
			m_Board.removePiecePosition(a_move->getTo());// remove opp piece
			m_Board.removePiecePosition(a_move->getFrom());// remove player piece
			l_fight = FightInfoImpl(a_move->getTo(), l_first_player_char,
					l_second_player_char, 0);// create fightinfo
		} else if (l_fight_result == a_playerNum) { // player won the fight
			m_Board.removePiecePosition(a_move->getTo());// remove the opp piece
			m_Board.getPieceByLocation(a_move->getFrom())->setNewLocation(
					a_move->getTo());// set piece loc
			m_Board.movePieceLocationOnBoard(a_move->getFrom(),
					a_move->getTo());// move the piece to new loc
			l_fight = FightInfoImpl(a_move->getTo(), l_first_player_char,
					l_second_player_char, l_isFirstPlayer);// create fight info
		} else { //player lost
			m_Board.removePiecePosition(a_move->getFrom());// remove his piece
			l_fight = FightInfoImpl(a_move->getTo(), l_first_player_char,
					l_second_player_char, l_opPlayerNum);
		}
	}
	if (a_jokerChange != nullptr) { // there is a jok change
		m_Board.getPieceByLocation(a_jokerChange->getJokerChangePosition())->setNewRep(
				a_jokerChange->getJokerNewRep());
	}
	return l_fight;
}

bool GameManager::checkMove(std::unique_ptr<Move>& a_move,
		std::unique_ptr<JokerChange>& a_jokerChange) {
	bool rc = false;
	// the point to on board
	int l_from_col = a_move->getFrom().getX();
	int l_from_row = a_move->getFrom().getY();
	if (!isPointOnBoard(l_from_col, l_from_row, m_Board.getCols(),
					m_Board.getRows())) {
		std::cout << "the point to is not on board. Got invalid move!";
		return rc;
	}
	// the point from on board
	int l_to_col = a_move->getTo().getX();
	int l_to_row = a_move->getTo().getY();
	if (!isPointOnBoard(l_to_col, l_to_row, m_Board.getCols(),
					m_Board.getRows())) {
		std::cout << "the point from is not on board. Got invalid move!";
		return rc;
	}
	// the move is only one to every direction
	if (!isValidMove(l_from_col, l_from_row, l_to_col, l_to_row)) {
		std::cout << "the move is not one cell to every direction!";
		return rc;
	}
	// the piece can move from to
	if (m_Board.getPieceByLocation(a_move->getFrom()) != nullptr && !canMove(getRealPiece(*m_Board.getPieceByLocation(a_move->getFrom())))) {
		std::cout << "the piece cannot move!!";
		return rc;
	}
	// the piece is mine + there is a piece
	if (m_Board.getPieceByLocation(a_move->getFrom()) == nullptr) {
		std::cout << "the piece is not mine!!";
		return rc;
	}
	if (!(m_Board.getPieceByLocation(a_move->getFrom())->getPlayerNum() == m_current_player_num)) {
		std::cout << "the piece is not mine!!";
		return rc;
	}
	// not overriding self piece
	if (m_Board.getPieceByLocation(a_move->getTo()) != nullptr && (m_Board.getPieceByLocation(a_move->getTo())->getPlayerNum())
			== m_current_player_num) {
		std::cout << "overriding self piece";
		return rc;
	}
	/**Checking Joker**/
	// the joker is on board
	if (a_jokerChange != nullptr) {
		int l_j_col = a_jokerChange->getJokerChangePosition().getX();
		int l_j_row = a_jokerChange->getJokerChangePosition().getY();
		if (!isPointOnBoard(l_j_col, l_j_row, m_Board.getCols(),
						m_Board.getRows())) {
			return rc;
		}
		// there is a joker there ??
		PointImpl l_joker_position;
		l_joker_position = a_jokerChange->getJokerChangePosition();
		if (m_Board.getPieceByLocation(l_joker_position) == nullptr) {
			std::cout << "no joker there";
			return rc;
		}
		if (!((toupper(m_Board.getPieceByLocation(l_joker_position)->getPiece()))
						== PieceChar::JOKER)) { // if i'm not a joker
			if (!((l_joker_position == a_move->getTo())
							&& ((toupper(
													m_Board.getPieceByLocation(a_move->getFrom())->getPiece()))
									== PieceChar::JOKER)&&(l_joker_position == a_move->getTo()))) { // i moved to the joker rep
				std::cout << "joker rep is not fine !!!";
				return rc;
			}
		}
	}
	rc = true;
	return rc;
}

int GameManager::winnerNumByStatus() const {
	// the func get the winner according to the enum of the status message
	switch (m_status) {
	case PLAYER1_WIN_FLAGS:
		return FIRST_PLAYER;
	case PLAYER2_WIN_FLAGS:
		return SECOND_PLAYER;
	case PLAYER1_WIN_MOVING_PIECES:
		return FIRST_PLAYER;
	case PLAYER2_WIN_MOVING_PIECES:
		return SECOND_PLAYER;
	case TIE:
		return TIE_NO_PLAYER;
	case TIE_NO_FLAGS:
		return TIE_NO_PLAYER;
	case PLAYER1_LOSE_BAD_POS:
		return SECOND_PLAYER;
	case PLAYER2_LOSE_BAD_POS:
		return FIRST_PLAYER;
	case TIE_BAD_POS:
		return TIE_NO_PLAYER;
	case PLAYER1_LOSE_BAD_MOVE:
		return SECOND_PLAYER;
	case PLAYER2_LOSE_BAD_MOVE:
		return FIRST_PLAYER;
	case OPEN_FAIL_FAILED:
		return TIE_NO_PLAYER;
	case TIE_NO_MOVING:
		return TIE_NO_PLAYER;
	case TIE_NO_FIGHT:
		return TIE_NO_PLAYER;
	case CONTINUE:
		return TIE_NO_PLAYER;

	}
	return TIE_NO_PLAYER;
}

std::string GameManager::reasonByStatus() const {
	// gets the reason to be printed according to the status of the player
	switch (m_status) {
	case PLAYER1_WIN_FLAGS:
		return "All flags of the opponent are captured";
	case PLAYER2_WIN_FLAGS:
		return "All flags of the opponent are captured";
	case PLAYER1_WIN_MOVING_PIECES:
		return "All moving PIECEs of the opponent are eaten";
	case PLAYER2_WIN_MOVING_PIECES:
		return "All moving PIECEs of the opponent are eaten";
	case TIE:
		return "A tie - both Moves input done without a winner";
	case TIE_NO_MOVING:
		return "A tie - all moving pieces are eaten";
	case TIE_NO_FLAGS:
		return "A tie - all flags are eaten by both players in the positioning";
	case PLAYER1_LOSE_BAD_POS:
		return "Bad Positioning input for player 1";
	case PLAYER2_LOSE_BAD_POS:
		return "Bad Positioning input for player 2";
	case TIE_BAD_POS:
		return "Bad Positioning input for both players";
	case PLAYER1_LOSE_BAD_MOVE:
		return "Bad Moves input for player 1";
	case PLAYER2_LOSE_BAD_MOVE:
		return "Bad Moves input for player 2";
	case OPEN_FAIL_FAILED:
		return "Fail to open files !!!";
	case TIE_NO_FIGHT:
		return "100 moves without a fight";
	default:  // default handling - shouldn't get here
		return "This is default";
	}
	return NULL;
}

void GameManager::initGame() {
	std::vector<std::unique_ptr<FightInfo>> l_outFightVec;
	std::vector<unique_ptr<PiecePosition>> l_vectorToFill_player_1;
	m_player1->getInitialPositions(FIRST_PLAYER, l_vectorToFill_player_1); // get pos
	bool l_position_1 = checkPositioning(FIRST_PLAYER, l_vectorToFill_player_1); // check pos
	if (l_position_1 == false) // bad pos - change status
		m_status = PLAYER1_LOSE_BAD_POS;
	else { // the pos is file - place it
		setPiecesOnBoard(1, l_vectorToFill_player_1, l_outFightVec);
	}
	std::vector<unique_ptr<PiecePosition>> l_vectorToFill_player_2;
	m_player2->getInitialPositions(SECOND_PLAYER, l_vectorToFill_player_2); // get pos
	bool l_position_2 = checkPositioning(SECOND_PLAYER,
			l_vectorToFill_player_2); // check pos
	if ((l_position_1 == false) && (l_position_2 == false)) // both pos invalid
		m_status = TIE_BAD_POS;
	else if (l_position_2 == false)
		m_status = PLAYER2_LOSE_BAD_POS;
	else { // the positioning is fine
		setPiecesOnBoard(2, l_vectorToFill_player_2, l_outFightVec);
		m_player2->notifyOnInitialBoard(m_Board, l_outFightVec);
		m_player1->notifyOnInitialBoard(m_Board, l_outFightVec);
	}
}

void GameManager::checkStatus() {
	// the func checks if there was a change in the status according to the move done
	int l_player1_flags = 0;
	int l_player2_flags = 0;
	int l_player1_move_pieces = 0;
	int l_player2_move_pieces = 0;
	for (int j=1; j<=m_Board.getRows();j++) {
		for (int i=1; i<=m_Board.getCols();i++) {
			std::shared_ptr<PiecePositionImpl> l_tmp_piece = m_Board.getPieceByLocation(PointImpl(i,j));
			if (l_tmp_piece !=nullptr) {
				if ((l_tmp_piece->getPlayerNum() == FIRST_PLAYER) && (toupper(getRealPiece(*l_tmp_piece))==PieceChar::FLAG)) {
					l_player1_flags+=1;
				}
				else if ((l_tmp_piece->getPlayerNum() == SECOND_PLAYER) && (toupper(getRealPiece(*l_tmp_piece))==PieceChar::FLAG)) {
					l_player2_flags+=1;
				}
				else if ((l_tmp_piece->getPlayerNum() == FIRST_PLAYER) && (!(toupper(getRealPiece(*l_tmp_piece))==PieceChar::BOMB))) {
					l_player1_move_pieces+=1;
				}
				else if ((l_tmp_piece->getPlayerNum() == SECOND_PLAYER) && (!(toupper(getRealPiece(*l_tmp_piece))==PieceChar::BOMB))) {
					l_player2_move_pieces+=1;

				}
			}
		}
	}
	if ((l_player1_flags == 0)&& (l_player2_flags==0))
	m_status = TIE_NO_FLAGS;
	else if (l_player1_flags == 0)
	m_status = PLAYER2_WIN_FLAGS;
	else if (l_player2_flags == 0)
	m_status = PLAYER1_WIN_FLAGS;
	else if ((l_player1_move_pieces == 0) && (l_player2_move_pieces == 0))
	m_status = TIE_NO_MOVING;
	else if (l_player1_move_pieces == 0)
	m_status = PLAYER2_WIN_MOVING_PIECES;
	else if (l_player2_move_pieces == 0)
	m_status = PLAYER1_WIN_MOVING_PIECES;
	else if (m_moves_no_fight == MAX_MOVES)
	m_status = TIE_NO_FIGHT;
}

void GameManager::startGame() {
	initGame();
	bool valid_move = true;
	if (m_status == CONTINUE)
		checkStatus();
	while (m_status == CONTINUE) {
		unique_ptr<Move> l_current_move = m_current_player->getMove();
		unique_ptr<JokerChange> l_current_joker_change =
		m_current_player->getJokerChange();
		valid_move = checkMove(l_current_move, l_current_joker_change);
		if (valid_move) {
			FightInfoImpl l_fight = doMove(m_current_player_num, l_current_move, l_current_joker_change);
			if (l_fight.getPiece(PLAYER_ONE)) { // there was no fight
				m_moves_no_fight++;
			}
			checkStatus();
			m_current_player->notifyFightResult(l_fight);
			changeCurrentPlayer();
			m_current_player->notifyOnOpponentMove(*l_current_move);
			m_current_player->notifyFightResult(l_fight);
		}
		else {
			if (m_current_player_num == FIRST_PLAYER)
			m_status = PLAYER1_LOSE_BAD_MOVE;
			else
			m_status = PLAYER2_LOSE_BAD_MOVE;
		}
	}
	*m_outFileStream << *this;
}
std::ostream& operator<<(std::ostream& os, const GameManager& a_game) {
	int winner = a_game.winnerNumByStatus();
	std::string reason = a_game.reasonByStatus();
	os << "Winner: " << winner << std::endl;
	os << "Reason: " << reason << std::endl;
	os << std::endl;
	os << a_game.m_Board;
	return os;
}

char GameManager::getRealPiece(const PiecePosition& a_piecePos) const {
	//gets the real piece rep
	char l_realRep =
			a_piecePos.getJokerRep() == NO_REP ?
					a_piecePos.getPiece() : a_piecePos.getJokerRep();
	return l_realRep;
}

void GameManager::increasePiecesCount(const char a_pieceRep, int a_playerNum) {
	//increases the piece count of the player
	int index = 0;
	std::vector<std::pair<char, int> > l_playersLimit = (a_playerNum == 1)?  m_player1Limit: m_player2Limit;
	index = findVecPieceIndex(a_pieceRep,l_playersLimit);
	if (a_playerNum == 1) {
		m_player1Limit[index].second++;
	} else {
		m_player2Limit[index].second++;
	}
}

int GameManager::findVecPieceIndex(const char a_pieceRep, std::vector<std::pair<char, int> > a_vec) {
	//finds a piece in the pieces vec
	std::vector<std::pair<char, int> >::const_iterator it = a_vec.begin();
	int index = 0;
	for (; it != a_vec.end(); ++it) {
		if (it->first == a_pieceRep) {
			return index;
		}
		index++;
	}
	return index;
}

int GameManager::getLimitByPiece(const std::vector<std::pair<char, int> >& a_piecesLimit, const char& a_lookup) {
	// gets the limit of a piece by player
	std::vector<std::pair<char, int> >::const_iterator it = a_piecesLimit.begin();
	int l_limit = 0;
	for (; it != a_piecesLimit.end(); ++it) {
		if (it->first == a_lookup) {
			l_limit += it->second;
		}
	}
	return l_limit;
}

