#ifndef CHESS_H
#define CHESS_H


#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <ctype.h>
#include <algorithm>
#include <stdlib.h>
#include <time.h>
#include <chrono>
#include<math.h>

using namespace std;

enum PieceType {Rook, Knight, Bishop, Queen, King, Pawn};
enum Team {Black, White};

double calculateNextTime(vector<double> times);

double remainingTurnTime(std::chrono::time_point<std::chrono::steady_clock> beginningTime, double allowedTime);

struct pos
{
  int x;
  int y;  
};

class GamePiece
{
  bool active;
  Team team;
  pos p;
  PieceType type;
  bool hasMoved;
public:  
  
  GamePiece();  //gamePiece with no information, empty spot
  GamePiece(int x, int y, PieceType ty, Team te); //an actual gamepiece
  string pieceRepr(); //returns the representation of this game piece for use in printing the board
  bool isActive()
  {
    return active;
  }
  
  Team getTeam()
  {
    return team;
  }
  pos getPos() 
  {
    return p;
  }
  void setPos(int x, int y)
  {
    p.x=x;
    p.y=y;
  }
  bool getMoved()
  {
    return hasMoved;
  }
  void setMoved(bool s)
  {
    hasMoved=s;
  }
  PieceType getType()
  {
    return type;
  }
  void setType(PieceType t)
  {
    type = t;
  }
  
  
  
};

struct gameMove //stores a start and end position, and whether or not this move is the en passant move
{
  pos start;
  pos end;
  bool enPassantMove=false; //when passed to procMove, tells board to remove the piece that was en passant'd
};





extern int terminalCount;

extern bool giveUp;

extern Team myTeam;  //my team

extern Team otherTeam;

class Board; //forward declaration

vector<gameMove> getLegalMoves(Board b, Team t, pos enPassantPos);

class Board
{ 

  
  GamePiece board[8][8];
  
public:  
  int whitePoints; //score for each side
  int blackPoints;
  int moves;       //moves counter
  Team currTurn;
  
  int turnsSincePawnMove;
  int turnsSinceCapture;
  vector<gameMove> lastEightMoves;
  
  pos enPassantPos;
  
  Board() {}; //leave pieces as all blank
  
  Board(vector<string> pieces);
  
  bool isInStalemate(int s);
  
  void addPoints(GamePiece piece);
  
  void printBoard(int layer);
  
  GamePiece &getPiece(int x, int y);
  
  void procMove(gameMove m);
  
  bool isTerminal(int terminalMoveCount);
  
  int utility(Team thisTeam); //value of the board
  
  int minValue(Board currBoard, Team t, std::chrono::time_point<std::chrono::steady_clock> beginningTime, double allowedTime, int &alpha, int &beta); //minValue of minimax algorithm
  
  int maxValue(Board currBoard, Team t, std::chrono::time_point<std::chrono::steady_clock> beginningTime, double allowedTime, int &alpha, int &beta); //maxValue of minimax algorithm
  
  gameMove maxChoice(Board currBoard, Team t, std::chrono::time_point<std::chrono::steady_clock> beginningTime, double allowedTime, gameMove bestLastTime); //maxChoice of minimax algorithm
};


string type2String(PieceType p);

PieceType char2PieceType(char c);

pos getEnPassantPos(string fen);

vector<gameMove> getPotentialMoves(Board b, pos piecePosition, pos enPassant);

Board parseFen(string fen);

bool isInCheck(Board board, pos kingPos, Team t);



extern GamePiece emptyPiece; //piece with no information, used for returning a piece when an out of 
                      //bounds piece is attempted to be accessed


#endif