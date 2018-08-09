/*
 * CommandAnalyzer.cpp
 *
 *  Created on: Apr 3, 2018
 *      Author: ariel
 */

#include "CommandAnalyzer.h"


CommandAnalyzer::CommandAnalyzer(std::string a_inputFileName): m_inputFileName(a_inputFileName), m_inputFilePath(""), m_currentWorkingDir(""){
	//m_inputFileStream = NULL;
	setCurrentWorkingDirectory();
	m_inputFileStream = std::make_unique<std::ifstream>(m_inputFilePath.c_str());
}

CommandAnalyzer::CommandAnalyzer() {
	setCurrentWorkingDirectory();
	m_inputFileName = "";
	m_inputFilePath = "";
	m_currentWorkingDir = "";
	m_inputFileStream = nullptr;
}

CommandAnalyzer::~CommandAnalyzer() {}

void CommandAnalyzer::splitCommand(const std::string& a_command, std::string& sep, std::vector<std::string>& a_outVec) {
	// split the string, C-style
	char* cstr = const_cast<char*>(a_command.c_str());
	char* current;
	current = strtok(cstr, sep.c_str());
	while (current != NULL) {
		a_outVec.push_back(current);
		current = strtok(NULL, sep.c_str());
	}
}

bool CommandAnalyzer::setCurrentWorkingDirectory() {
	char temp[MAX_PATH_LEN];
	if (!getcwd(temp, MAX_PATH_LEN)) {
		return false;
	}
	// got cwd, update paths
	m_currentWorkingDir = temp;
	if (m_inputFilePath == "") { // first update of input file path
		m_inputFilePath = m_currentWorkingDir + "/" + m_inputFileName;
	}
	return true;
}


FileStatus CommandAnalyzer::getNextLine(std::string& out_str) {
	while (std::getline(*m_inputFileStream, out_str)) {
		// successful read
		// check that line is not empty
		if (out_str.find_first_not_of("\t\n ") != std::string::npos) {
			// line is not empty (contains a char different from \t \n or space
			break;
		}
	}
	// failed to read
	// check inputfilestream
    if((*m_inputFileStream).bad()){
		std::cout
				<< "bad file, unexpected error"
				<< std::endl;
        return ERROR;
    }
    if((*m_inputFileStream).eof()){
    	if (out_str.size() > 0) {
    		return OK; // got to eof after read, but out_str contains data
    	} else {
    		return END_OF_FILE;
    	}
    }
    // otherwise
    return OK;
}

bool CommandAnalyzer::isValidChar(char a_inputChar) {
	// check if inputChar is one of the 6 allowed PieceChars
	bool is_valid_char = false;
	switch(a_inputChar){
		case PieceChar::FLAG:
			is_valid_char = true;
			break;
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
		case PieceChar::JOKER:
			is_valid_char = true;
			break;
	}
	return is_valid_char;
}

bool CommandAnalyzer::isInpuFileStreamGood() {
	return m_inputFileStream->good();

}
