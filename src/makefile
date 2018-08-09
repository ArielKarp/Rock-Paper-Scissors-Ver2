#COMP = g++
COMP = g++-5.3.0
#put all your object files here
OBJS = PointImpl.o PiecePositionImpl.o MoveImpl.o BoardImpl.o JokerChangeImpl.o \
FightInfoImpl.o AutoPlayerAlgorithm.o FilePlayerAlgorithm.o CommandAnalyzer.o MoveCommandAnalyzer.o \
PositionCommandAnalyzer.o GameManager.o main.o

#The executabel filename DON'T CHANGE
EXEC = ex2
CPP_COMP_FLAG = -std=c++14 -Wall -Wextra \
-Werror -pedantic-errors -DNDEBUG

$(EXEC): $(OBJS)
	$(COMP) $(OBJS) -o $@
PointImpl.o: PointImpl.h PointImpl.cpp Point.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
PiecePositionImpl.o: PiecePositionImpl.cpp PiecePositionImpl.h PiecePosition.h PointImpl.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
MoveImpl.o: MoveImpl.cpp MoveImpl.h PointImpl.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
BoardImpl.o: BoardImpl.cpp BoardImpl.h Board.h PiecePositionImpl.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
JokerChangeImpl.o: JokerChangeImpl.cpp JokerChangeImpl.h JokerChange.h PointImpl.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
FightInfoImpl.o: FightInfoImpl.cpp FightInfoImpl.h FightInfo.h PointImpl.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
CommandAnalyzer.o: CommandAnalyzer.h CommandAnalyzer.cpp PiecePositionImpl.h MoveImpl.h JokerChangeImpl.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
MoveCommandAnalyzer.o: MoveCommandAnalyzer.h MoveCommandAnalyzer.cpp CommandAnalyzer.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
PositionCommandAnalyzer.o: PositionCommandAnalyzer.h PositionCommandAnalyzer.cpp CommandAnalyzer.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
AutoPlayerAlgorithm.o: AutoPlayerAlgorithm.cpp AutoPlayerAlgorithm.h PlayerAlgorithm.h PiecePositionImpl.h MoveImpl.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
FilePlayerAlgorithm.o: FilePlayerAlgorithm.cpp FilePlayerAlgorithm.h PlayerAlgorithm.h MoveImpl.h JokerChangeImpl.h PositionCommandAnalyzer.h MoveCommandAnalyzer.h FightInfoImpl.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
GameManager.o: GameManager.h GameManager.cpp FilePlayerAlgorithm.h AutoPlayerAlgorithm.h BoardImpl.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
main.o: main.cpp PiecePositionImpl.h BoardImpl.h CommandAnalyzer.h GameManager.h PositionCommandAnalyzer.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
clean:
	rm -f $(OBJS) $(EXEC)