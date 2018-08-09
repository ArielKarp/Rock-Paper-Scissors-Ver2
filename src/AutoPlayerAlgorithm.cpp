/*
 * AutoPlayerAlgorithm.cpp
 *
 *  Created on: May 3, 2018
 *      Author: gasha
 */

#include "AutoPlayerAlgorithm.h"

AutoPlayerAlgorithm::AutoPlayerAlgorithm(const int a_playerNum,
		std::vector<std::pair<char, int> >& a_piecesLimit, int a_cols,
		int a_rows) :
		m_playerNum(a_playerNum), m_piecesLimit(a_piecesLimit), m_cols(a_cols), m_rows(
				a_rows) {

}

void AutoPlayerAlgorithm::getInitialPositions(int player,
		std::vector<unique_ptr<PiecePosition>>& vectorToFill) {
	for (std::vector<std::pair<char, int> >::const_iterator it =
			m_piecesLimit.begin(); it != m_piecesLimit.end(); ++it) { //go over the limits
	    std::mt19937 rng;
	    rng.seed(std::random_device()());
	    std::uniform_int_distribution<std::mt19937::result_type> dist6(0,9); // distribution in range [0, 9]
		for (int i = 0; i < it->second; i++) { //create point
			int l_random_loc_x = int(dist6(rng));
			int l_random_loc_y = int(dist6(rng));
			PointImpl l_tmp_point = PointImpl(l_random_loc_x + 1, l_random_loc_y + 1);
			auto l_it = myPieceToFind(l_tmp_point); //find if there is a piece in this location
			while (l_it != m_algoPieces.end()) { // if so - select new cell for the piece
				l_random_loc_x = int(dist6(rng));
				l_random_loc_y = int(dist6(rng));
				l_tmp_point = PointImpl(l_random_loc_x + 1, l_random_loc_y + 1);
				l_it = myPieceToFind(l_tmp_point);
			}
			char l_jokerChar = PieceChar::JOKER;
			char l_bombChar = PieceChar::PAPER;
			char l_joker_rep = it->first != l_jokerChar ? NO_REP : l_bombChar; // joker rep
			unique_ptr<PiecePositionImpl> l_tmp_piece_ptr = std::make_unique<
					PiecePositionImpl>(l_tmp_point, it->first, l_joker_rep,
					player); //create piece
			vectorToFill.push_back(std::move(l_tmp_piece_ptr)); // push to vec
			m_algoPieces.push_back(
					PiecePositionImpl(l_tmp_point, it->first, l_joker_rep,
							player)); //push to player's vec
		}
	}
}

std::vector<oppPiece>::iterator AutoPlayerAlgorithm::oppPieceToFind(
		const Point& a_point){
	//goes over all opp pieces and checks whether there is there piece in a specific point
	std::vector<oppPiece>::iterator it = m_oppPiece.begin();
	for (; it != m_oppPiece.end(); ++it) {
		if (it->s_point == a_point) {
			return it;
		}
	}
	return it;
}

std::vector<PiecePositionImpl>::iterator AutoPlayerAlgorithm::myPieceToFind(
		const Point& a_point){
	//goes over all players pieces and checks whether there is there piece in a specific point
	std::vector<PiecePositionImpl>::iterator it = m_algoPieces.begin();
	for (; it != m_algoPieces.end(); ++it) {
		if (it->getPositionImpl() == a_point) {
			return it;
		}
	}
	return it;
}

void AutoPlayerAlgorithm::notifyOnInitialBoard(const Board& b,
		const std::vector<unique_ptr<FightInfo>>& fights) {
	for (int i = 1; i <= m_rows; i++) {
		for (int j = 1; j <= m_cols; j++) {
			PointImpl l_tmp_point = PointImpl(i, j);
			if (((b.getPlayer(l_tmp_point)) != m_playerNum)
					&& (b.getPlayer(l_tmp_point) != 0)) {
				m_oppPiece.push_back( { l_tmp_point, false, '#' });
			}
		}
	}

	for (auto const& l_fight : fights) {
		if (l_fight->getWinner() == m_playerNum) { // player won in the fight
			//remove from vec opp piece
			auto it = oppPieceToFind(l_fight->getPosition());
			if (it != m_oppPiece.end())
				m_oppPiece.erase(it);

		} else if (l_fight->getWinner() == TIE_NO_PLAYER) {
			// remove from vec opp piece
			auto l_it = oppPieceToFind(l_fight->getPosition());
			if (l_it != m_oppPiece.end())
				m_oppPiece.erase(l_it);
			//remove from my vector
			auto l_my_it = myPieceToFind(l_fight->getPosition());
			if (l_my_it != m_algoPieces.end())
				m_algoPieces.erase(l_my_it);
		} else { // player lost
				 //remove from my vector
			auto l_my_it = myPieceToFind(l_fight->getPosition());
			if (l_my_it != m_algoPieces.end())
				m_algoPieces.erase(l_my_it);
			auto l_opsIt = oppPieceToFind(l_fight->getPosition());
			if (l_opsIt != m_oppPiece.end()) {
				int l_opsNum = m_playerNum == 2 ? 1 : 2;
				(*l_opsIt).s_rep = l_fight->getPiece(l_opsNum);
			}
		}

	}
}

void AutoPlayerAlgorithm::notifyOnOpponentMove(const Move& move) {
	// find ops piece by point
	// change is piece moved to true
	auto l_it = oppPieceToFind(move.getFrom());
	if (l_it != m_oppPiece.end()) {
		(*l_it).s_point = move.getTo();
		(*l_it).s_is_moved = true;
	}
}

void AutoPlayerAlgorithm::notifyFightResult(const FightInfo& fightInfo) {
	// check if i won
	// if lost - update my pieces
	// update opps piece with char
	// if won - remove ops piece
	if (fightInfo.getWinner() == m_playerNum) { // I won
		auto l_it = oppPieceToFind(fightInfo.getPosition());
		if (l_it != m_oppPiece.end()) { // remove ops piece from my vec
			m_oppPiece.erase(l_it);
		}
	}
	else if (fightInfo.getWinner() == TIE_NO_PLAYER){
		// remove both pieces
		// auto player lost
		auto  l_it = myPieceToFind(fightInfo.getPosition());
		if (l_it != m_algoPieces.end()) { // remove my piece
			m_algoPieces.erase(l_it);
		}
		auto l_oppIt = oppPieceToFind(fightInfo.getPosition());
		if (l_oppIt != m_oppPiece.end())
			m_oppPiece.erase(l_oppIt);
	}
	else {
		// auto player lost
		auto  l_it = myPieceToFind(fightInfo.getPosition());
		if (l_it != m_algoPieces.end()) { // remove my piece
			m_algoPieces.erase(l_it);
		}
		auto l_opsIt = oppPieceToFind(fightInfo.getPosition());
		if (l_opsIt != m_oppPiece.end()) {
			int l_opsNum = m_playerNum == SECOND_PLAYER ? FIRST_PLAYER : SECOND_PLAYER;
			(*l_opsIt).s_rep = fightInfo.getPiece(l_opsNum);
		}
	}
}

unique_ptr<JokerChange> AutoPlayerAlgorithm::getJokerChange() {
	//algo is not changing the joker
	return nullptr;
}

int AutoPlayerAlgorithm::getPlayerNum(){
	return m_playerNum;
}


unique_ptr<Move> AutoPlayerAlgorithm::getMove() {
	// for each piece
	// check all possible moves
	// for each move - calculate scoring function
	// choose highest score
	std::vector<std::pair<MoveImpl, int>> l_possibleMoves;
	for (const auto& l_algoPiece: m_algoPieces) { // fill vec of all possible moves
		char l_algoPieceRep = l_algoPiece.getJokerRep() == NO_REP ? l_algoPiece.getPiece() : l_algoPiece.getJokerRep();
		if (l_algoPieceRep != PieceChar::FLAG && l_algoPieceRep != PieceChar::BOMB) {
			fillPossibleMoves(l_possibleMoves, l_algoPiece);
		}
	}

	// get scores for moves
	fillPossibleMovesScore(l_possibleMoves);
	std::pair<MoveImpl, int> l_maxMove = getMaxMoveByScore(l_possibleMoves);
	// move internal piece
	auto l_chosenPiece = myPieceToFind(l_maxMove.first.getFrom());
	l_chosenPiece->setNewLocation(l_maxMove.first.getTo());
	return std::make_unique<MoveImpl>(l_maxMove.first);
}


void AutoPlayerAlgorithm::fillPossibleMoves(std::vector<std::pair<MoveImpl, int>>& a_possibleMoves, const PiecePositionImpl& a_pieceToMove) {
	//check which move is possible and fill vector with it
	int col = a_pieceToMove.getPosition().getX();
	int row = a_pieceToMove.getPosition().getY();
	if (col + 1 <= m_cols && myPieceToFind(PointImpl(col + 1, row)) == m_algoPieces.end()) {
		a_possibleMoves.push_back(std::make_pair(MoveImpl(col, row, col + 1, row), 0));
	}
	if (col - 1 >= 1 && myPieceToFind(PointImpl(col - 1, row)) == m_algoPieces.end()) {
		a_possibleMoves.push_back(std::make_pair(MoveImpl(col, row, col - 1, row), 0));
	}
	if (row + 1 <= m_rows && myPieceToFind(PointImpl(col, row + 1)) == m_algoPieces.end()) {
		a_possibleMoves.push_back(std::make_pair(MoveImpl(col, row, col, row + 1), 0));
	}
	if (row -1 >= 1 && myPieceToFind(PointImpl(col, row - 1)) == m_algoPieces.end()) {
		a_possibleMoves.push_back(std::make_pair(MoveImpl(col, row, col, row - 1), 0));
	}
}

void AutoPlayerAlgorithm::fillPossibleMovesScore(std::vector<std::pair<MoveImpl, int>>& a_possibleMoves) {
	std::vector<std::pair<MoveImpl, int>>::iterator it = a_possibleMoves.begin();
	for(; it != a_possibleMoves.end(); ++it) {
		it->second = getScoreOfMove(it->first);
	}
}

std::pair<MoveImpl, int> AutoPlayerAlgorithm::getMaxMoveByScore(const std::vector<std::pair<MoveImpl, int>>& a_possibleMoves) {
	//gives every move a score
	std::vector<std::pair<MoveImpl, int>>::const_iterator it = a_possibleMoves.begin();
	std::pair<MoveImpl, int> l_maxMoveScore = std::make_pair(MoveImpl(-1,-1,-1,-1), -INT_MAX);
	for(; it != a_possibleMoves.end(); ++it) {
		if (it->second > l_maxMoveScore.second) {
			l_maxMoveScore.first = it->first;
			l_maxMoveScore.second = it->second;
		}
	}
	return l_maxMoveScore;
}


int AutoPlayerAlgorithm::getScoreOfMove(const MoveImpl& a_move) {
	auto l_oppIt = oppPieceToFind(a_move.getTo());
	auto l_myPieceIt = myPieceToFind(a_move.getFrom());
	if (l_oppIt != m_oppPiece.end()) {
		// attacking a piece
		if (l_oppIt->s_is_moved == false) {
			int numOfStillPieces = countNumOfStillPieces();
			if (numOfStillPieces < THRESHOLD_ONE) {
				// only two or less flags left
				return SCORE_MAX;
			} else if (numOfStillPieces < THRESHOLD_TWO) {
				return SCORE_HIGH;
			} else {
				return SCORE_MED;
			}
		} else {
			// piece that moved
			// if unknown piece
			if (l_oppIt->s_rep == NO_REP) {
				return SCORE_MED;
			}
			// known opp piece rep
			char myRep = l_myPieceIt->getJokerRep() == NO_REP ? l_myPieceIt->getPiece() : l_myPieceIt->getJokerRep();
			int l_winnerPiece = fightResult(toupper(myRep), toupper(l_oppIt->s_rep));
			if (l_winnerPiece == FIRST_PLAYER) {
				return SCORE_HIGH;
			} else if (l_winnerPiece == SECOND_PLAYER)  {
				return SCORE_NEG;
			} else {
				// Tie
				int l_countMyPieces = m_algoPieces.size();
				int l_countOppPieces = m_oppPiece.size();
				if ((l_countMyPieces - l_countOppPieces) < 0) {
					return SCORE_LOW;
				}
				else {
					return SCORE_MED;
				}
			}
		}
	}
	//get random val for move
    std::mt19937 rng;
    rng.seed(std::random_device()());
    std::uniform_int_distribution<std::mt19937::result_type> dist6(0,9); // distribution in range [0, 9]
	return int(dist6(rng));
}

int AutoPlayerAlgorithm::fightResult(const char a_firstUpper,
		const char a_secondUpper) {
	// gets the number of player who won the fight
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

int AutoPlayerAlgorithm::countNumOfStillPieces() const {
	// checks for every piece if it was moved, if no - counter is raised up
	int l_outNum = 0;
	for(const auto& opsPiece: m_oppPiece) {
		if (opsPiece.s_is_moved == false) {
			l_outNum++;
		}
	}
	return l_outNum;
}
