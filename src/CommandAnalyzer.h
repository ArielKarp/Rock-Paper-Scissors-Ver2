/*
 * CommandAnalyzer.h
 *
 *  Created on: Apr 3, 2018
 *      Author: ariel
 */

#ifndef COMMANDANALYZER_H_
#define COMMANDANALYZER_H_

#include <fstream>
#include <vector>
#include <string.h>
#include <string>
#include <algorithm>
#include <unistd.h>
#include <map>
#include <memory>
#include <iostream>
#include "PiecePositionImpl.h"
#include "MoveImpl.h"
#include "JokerChangeImpl.h"

#define MOVE_NUM_OF_ENTRIES 4
#define MAX_NUM_ENTRIES 8
#define MAX_PATH_LEN 256

enum FileStatus { END_OF_FILE, ERROR, OK, NO_FILE };

class CommandAnalyzer {
public:
	CommandAnalyzer();
	CommandAnalyzer(std::string a_inputFileName);
	virtual ~CommandAnalyzer();
	FileStatus getNextLine(std::string& out_str);
	void splitCommand(const std::string& a_command, std::string& sep, std::vector<std::string>& a_outVec);
	virtual bool isValidChar(char a_inputChar);
	virtual bool isInpuFileStreamGood();
	CommandAnalyzer& operator=(const CommandAnalyzer& a_commandAnalyzer) = delete;
	CommandAnalyzer (const CommandAnalyzer& a_commandAnalyzer) = delete;

private:
	bool setCurrentWorkingDirectory();

	std::string m_inputFileName;
	std::string m_inputFilePath;
	std::string m_currentWorkingDir;
	std::unique_ptr<std::ifstream> m_inputFileStream;
};

#endif /* COMMANDANALYZER_H_ */
