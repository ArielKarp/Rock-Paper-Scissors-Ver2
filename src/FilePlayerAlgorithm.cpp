/*
 * FilePlayerAlgorithm.cpp
 *
 *  Created on: May 3, 2018
 *      Author: gasha
 */


#include "FilePlayerAlgorithm.h"

FilePlayerAlgorithm::FilePlayerAlgorithm(const int a_playerNum, const std::string a_positionFileName, const std::string a_moveFileName):
m_playerNum(a_playerNum) {
	m_positionAnalyzer = std::make_unique<PositionCommandAnalyzer>(a_positionFileName);
	m_moveAnalyzer = std::make_unique<MoveCommandAnalyzer>(a_moveFileName);
	m_jokerChange = nullptr;
}

void FilePlayerAlgorithm::getInitialPositions(int player, std::vector<unique_ptr<PiecePosition>>& vectorToFill){
	FileStatus l_fs = FileStatus::OK;
	while(l_fs == FileStatus::OK){ //get next line from file
		unique_ptr<PiecePositionImpl> l_tmp_piece = std::make_unique<PiecePositionImpl>();
		l_fs = m_positionAnalyzer->getPosCommand(l_tmp_piece, player);
		l_tmp_piece->setPlayerNum(player);
		if (l_fs == FileStatus::ERROR){
			l_tmp_piece->setNewLocation(PointImpl());
		}
		if (l_fs != FileStatus::END_OF_FILE) {  // push to vector if not eof
			vectorToFill.push_back(std::move(l_tmp_piece));
		}
	}
}

std::unique_ptr<Move> FilePlayerAlgorithm::getMove(){
	// fille move and joker change. return move
	unique_ptr<MoveImpl> l_move = std::make_unique<MoveImpl>();
	unique_ptr<JokerChangeImpl> l_joker = std::make_unique<JokerChangeImpl>(PointImpl(), '#');
	FileStatus l_fs = m_moveAnalyzer->getMoveCommand(l_move, l_joker, m_playerNum);
	if ((l_fs == FileStatus::ERROR)||(l_fs == FileStatus::NO_FILE)){
		l_move->setTo(PointImpl());
		m_jokerChange = nullptr;

	}
	else{
		if (l_joker->getJokerNewRep()=='#'){
			m_jokerChange = nullptr;
		}
		else
			m_jokerChange = std::move(l_joker);
	}
	return l_move;


}
std::unique_ptr<JokerChange> FilePlayerAlgorithm::getJokerChange(){
	if (m_jokerChange==nullptr)
		return nullptr;
	return std::make_unique<JokerChangeImpl>(*m_jokerChange);
}

int FilePlayerAlgorithm::getPlayerNum(){
	return m_playerNum;
}
