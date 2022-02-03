#include "Chess.h"




double remainingTurnTime(std::chrono::time_point<std::chrono::steady_clock> beginningTime, double allowedTime)
{    
  return allowedTime - (((std::chrono::steady_clock::now() - beginningTime).count())/1000000000.0);
}

//value of board, myTeams score - other teams score at this state
int Board::utility(Team thisTeam)
{
  if (thisTeam==White)
  {
    return whitePoints-blackPoints;
  }
  return blackPoints-whitePoints;
}



int Board::minValue(Board currBoard, Team t, std::chrono::time_point<std::chrono::steady_clock> beginningTime, double allowedTime, int &alpha, int &beta)
{
  if (remainingTurnTime(beginningTime, allowedTime) < 0) //out of time
  {
    return 0; //doesnt matter what we return we just need to quit recursing so it will finish
  }  
  
  //find all states from this state
  vector<gameMove> allPotentialMoves = getLegalMoves(*this, otherTeam, enPassantPos);
  
  //if this state is in stalemate, return very bad score to discourage stalemating the game
  if (isInStalemate(allPotentialMoves.size())) 
  {
    if (giveUp)
    {
      //return -100000000;   
      cout << "\t\tStalemate possiblity seen" << endl;
      return 100000000;   
    }
    else
    {
      return -100000000;   
    }
  }
 
  //if terminal, minVal is just utility
  if (isTerminal(currBoard.moves+terminalCount))
  {
    //cout << "Util: " << utility(t) << endl;
    //cout << "A: " << alpha << endl;
    //cout << "B: " << beta << endl;
    //printBoard(0);    
    return utility(t);
  }
  
  int newAlpha = alpha;
  int newBeta = beta;
  
  
  Board testBoard;
  
  int minScore = 1000000000 - (moves - currBoard.moves); //min default is inf
  int testScore;
  for (auto move : allPotentialMoves)
  {
    testBoard = *this; //duplicate this board
        
    testBoard.procMove(move); //do the move on it
    
    testScore = testBoard.maxValue(currBoard, t, beginningTime, allowedTime, newAlpha, newBeta); //if its maxVal is less than previous min, overwrite it
    
    
    if (remainingTurnTime(beginningTime, allowedTime) < 0) //out of time
    {
      return 0; //doesnt matter what we return we just need to quit recursing so it will finish
    }
        
    
    if (testScore < minScore)
    {
      minScore = testScore;   
    }     
    
    if (minScore <= newAlpha) 
    {
      //cout << "Should return here" << endl;
      return minScore;
    }    
    else if (minScore < newBeta) 
    {
      newBeta = minScore;
      //cout << "New Beta: " << beta << endl;
      //testBoard.printBoard(0);
      //cout << endl;      
    }
    
    
    
    
  }  
  
  if (newBeta < alpha) alpha = newBeta;
  
  return minScore;
}



int Board::maxValue(Board currBoard, Team t, std::chrono::time_point<std::chrono::steady_clock> beginningTime, double allowedTime, int &alpha, int &beta)
{ 
  
  if (remainingTurnTime(beginningTime, allowedTime) < 0) //out of time
  {
    return 0; //doesnt matter what we return we just need to quit recursing so it will finish
  }
  
  //find all states from this state
  
  vector<gameMove> allPotentialMoves = getLegalMoves(*this, myTeam, enPassantPos);
  
  //if this state is in stalemate, return very bad score to discourage stalemating the game
  if (isInStalemate(allPotentialMoves.size())) 
  {    
    if (giveUp)
    {
      //return -100000000;   
      cout << "\t\tStalemate possiblity seen" << endl;
      return -1000000005; //make it worth more than regular checkmate to show the possibility of getting stalemate over just checkmate   
    }
    else
    {
      return 100000000;   
    } 
  }
  
  //if terminal, maxVal is just utility
  if (isTerminal(currBoard.moves+terminalCount))
  {
    //cout << "Util: " << utility(t) << endl;
    //cout << "A: " << alpha << endl;
    //cout << "B: " << beta << endl;
    //printBoard(0);    
    return utility(t);
  }
  
  
  int newAlpha = alpha;
  int newBeta = beta;
  
  
  Board testBoard;
  
  int maxScore = -1000000000; //max default is -inf
  int testScore;
  for (auto move : allPotentialMoves)
  {     
    
    testBoard = *this; //duplicate this board
   
    testBoard.procMove(move); //do the move on it
    
    testScore = testBoard.minValue(currBoard, t, beginningTime, allowedTime, newAlpha, newBeta);
    
    
    
    if (remainingTurnTime(beginningTime, allowedTime) < 0) //out of time
    {
      return 0; //doesnt matter what we return we just need to quit recursing so it will finish
    }
    
    if (testScore > maxScore) //if its minVal is more than previous max, overwrite it
    {
      maxScore = testScore;
    }     
    
    if (giveUp && testScore==-1000000005) return -1000000005; //stalemate is good for us now, try for it
    
    if (maxScore >= newBeta) 
    {
      //cout << "Should return here" << endl;      
      return maxScore;
    }    
    else if (maxScore > newAlpha) 
    {
      newAlpha = maxScore;
      //cout << "New Alpha: " << alpha << endl;
      //testBoard.printBoard(0);
      //cout << endl;
    }
    
    
  }

  if (newAlpha > beta) beta = newAlpha;
  
  return maxScore;
}


gameMove Board::maxChoice(Board currBoard, Team t, std::chrono::time_point<std::chrono::steady_clock> beginningTime, double allowedTime, gameMove bestLastTime)
{   
  //find all states from this state
  
  vector<gameMove> allPotentialMoves = getLegalMoves(*this, myTeam, enPassantPos);
  
  Board testBoard;
  
  int maxScore = -1000000001; //max default is -inf
  int testScore;
  vector<gameMove> bestMove = vector<gameMove>();
  
  
  //if this isn't the first iteration depth, start with the previous best first pick to increase pruning
  if (terminalCount>1)
  {
    //not the first iteration
    //put the best move from last time at front of list
    
    vector<gameMove> newList = vector<gameMove>();
    
    for (auto m : allPotentialMoves)
    {
      if (m.start.x==bestLastTime.start.x && m.start.y==bestLastTime.start.y &&
          m.end.x==bestLastTime.end.x && m.end.y==bestLastTime.end.y)
      {
        continue; //skip over the best move
      }
      
      //else, add it back in the list
      newList.push_back(m);
    }
    //then, put best move in front of list
    newList.insert(newList.begin(), bestLastTime);
    
    //then rewrite allPotentialMoves
    allPotentialMoves = newList;    
  }
  
  
  int alpha = -1000000000;
  int beta = 1000000000;
    
  
  for (auto move : allPotentialMoves)
  {
    testBoard = *this; //duplicate this board
    
    testBoard.procMove(move); //do the move on it
    
    
    testScore = testBoard.minValue(currBoard, t, beginningTime, allowedTime, alpha, beta);
    
    if (giveUp && testScore==-1000000005) 
    {
      testScore = 1000000005; //stalemate actually good
    }
    
    
    if (testScore > maxScore) //if its minVal is more than previous max, overwrite it
    {
      bestMove.clear();
      maxScore = testScore;
      bestMove.push_back(move);
    }
    else if (testScore == maxScore)
    {
      bestMove.push_back(move);
    }
    
    
    
    
    
    //cout << char(move.start.x+'a') << char(move.start.y+'1') << char(move.end.x+'a') << char(move.end.y+'1');
    //cout << ", now Alpha is " << alpha << " and Beta is " << beta << endl;
    
  }
  
  if (bestMove.size() > 0)
  {
  
    gameMove finalMove = bestMove.at(rand() % bestMove.size());
    
    if (remainingTurnTime(beginningTime, allowedTime) > 0)
    {
      cout << "Best score at depth " << terminalCount << ":" << maxScore << ", move: ";
      
      cout << char(finalMove.start.x+'a') << char(finalMove.start.y+'1') << char(finalMove.end.x+'a') << char(finalMove.end.y+'1') << endl;
      
    }
    return finalMove;
  }
  else
  {
    //this shouldn't be possible
    cout << "Somehow there were no best moves" << endl;
    
    gameMove m;
    m.start.x=0;
    m.start.y=0;
    m.end.x=0;
    m.end.y=0;
    return m;
  }  
}



string type2String(PieceType p)
{
  switch (p)
  {
    case Rook:
      return "Rook";
    case Knight:
      return "Knight";
    case Bishop:
      return "Bishop";
    case Queen:
      return "Queen";
    case King:
      return "King";
    case Pawn:
      return "Pawn";
    default:
      cout << "Invalid Piece Type" << endl;
      exit(1);
  }
}

PieceType char2PieceType(char c)
{
  switch (c)
  {
    case 'r':
    case 'R':
      return Rook;
    case 'n':
    case 'N':
      return Knight;
    case 'b':
    case 'B':
      return Bishop;
    case 'q':
    case 'Q':
      return Queen;
    case 'k':
    case 'K':
      return King;
    case 'p':
    case 'P':
      return Pawn;
    default:
      cout << "Invalid Piece Type" << endl;
      exit(1);
  }
}

GamePiece::GamePiece()
{
  active=false;
  hasMoved=false;
}

GamePiece::GamePiece(int x, int y, PieceType ty, Team te)
{
  p.x=x;
  p.y=y;
  type=ty;
  team=te;
  active=true;
  hasMoved=false;
}

string GamePiece::pieceRepr()
{
  if (!active) return "-"; //blank space for empty spaces
  if (getTeam()==White)
  {
    switch(type)
    {
      case Rook:
        return "R";
      case Knight:
        return "N";
      case Bishop:
        return "B";
      case Queen:
        return "Q";
      case King:
        return "K";
      case Pawn:
        return "P";
    }
  }
  else
  {
    switch(type)
    {
      case Rook:
        return "r";
      case Knight:
        return "n";
      case Bishop:
        return "b";
      case Queen:
        return "q";
      case King:
        return "k";
      case Pawn:
        return "p";
    }
  }
  cout << "Not a valid piece" << endl;
  exit(1);
}


//s is the number of moves that can be made by team currTurn on this board
bool Board::isInStalemate(int s)
{  
    if (s>0) return false; //there is a valid move so no stalemate

    //find king
    GamePiece kingPiece; //piece used to search for king
    for (int j=0; j<8; j++)
    {
      for (int i=0; i<8; i++)
      {
        kingPiece = getPiece(i,j);
        if (kingPiece.isActive() && kingPiece.getTeam()==currTurn && kingPiece.getType()==King)
        {          
          goto stopPieceSearchStalemate; //once king found, break out of doubly nested loop
        }
      }
    }
    stopPieceSearchStalemate:
    
    //check if the king is currently in check, because if he is, then it cannot be stalemate
    
    if (isInCheck(*this, kingPiece.getPos(), currTurn))
    {
      return false;
    }    
    
    //if it makes it here, the king isn't in check and there are no legal moves, so stalemate
    return true;
}


Board::Board(vector<string> pieces) //the 8 rows from the fen string init this
{    
  turnsSincePawnMove = 0;
  turnsSinceCapture = 0;

  lastEightMoves = vector<gameMove>();
  
  enPassantPos.x=-1;
  enPassantPos.y=-1;
  
  whitePoints=0; //score for each side
  blackPoints=0;
  moves=0; //moves counter
  currTurn=White; //basically not used, just to print out whose turn it is in the console
  for (int j=7; j>-1; j--) //starting from the top
  {
    int writePos=0;
    for (unsigned int i=0; i<pieces[j].size(); i++)
    {
      if (isdigit(pieces[j][i])) //number, blank
      {          
        writePos += ((pieces[j][i]-'0')-1); //skip that many spaces
      }
      else //letter
      {
        if (isupper(pieces[j][i])) //uppercase letter, white
        {
          board[j][writePos] = GamePiece(writePos,j,char2PieceType(pieces[j][i]), White);
        }
        else //lowercase letter, black
        {
          board[j][writePos] = GamePiece(writePos,j,char2PieceType(pieces[j][i]), Black);
        }
      }
      writePos++;
    }
  }
}

//board is terminal if it is at least terminalMoveCount moves ahead of the real board, or if one of the teams kings have been "captured"
//obviously the king cannot actually be captured but the algorithm thinks it can and thats how it tries to checkmate the opponent
bool Board::isTerminal(int terminalMoveCount)
{ 
  bool w=false;
  bool b=false;
  for (int i=0; i<8; i++)
  {
    for (int j=0; j<8; j++)
    {
      if (board[j][i].isActive())
      {
        if (board[j][i].getType()==King)
        {
          if (board[j][i].getTeam()==White)
          {
            w=true;
          }
          else
          {
            b=true;
          }
        }
      }
    }
  }
  if (!b || !w) return true;
  return (moves>=terminalMoveCount);
}

bool moveMatches(gameMove a, gameMove b)
{
  return a.start.x==b.start.x
         && a.start.y==b.start.y
         && a.end.x==b.end.x
         && a.end.y==b.end.y;
}


//uses exponential regression to guess the time the next move would take
double calculateNextTime(vector<double> times)
{
    int n,i;
    float Y[20],sumx=0,sumy=0,sumxy=0,sumx2=0,y[20];
    float a,b,A;    
    
    n = times.size();    
    
    for(i=0;i<=n-1;i++)
    {        
        y[i] = times[i]*100; //multiply inputs by 100 so the numbers arent tiny
    }
    
    for(i=0;i<=n-1;i++)
    {
        Y[i]=log(y[i]);
    }
    
    for(i=0;i<=n-1;i++)
    {
        sumx += i;
        sumx2 += i*i;
        sumy += Y[i];
        sumxy += i*Y[i];
    }
    if ((n*sumx2-sumx*sumx)==0) return 10000; //dont want divide by zeros
    A=((sumx2*sumy -sumx*sumxy)*1.0/(n*sumx2-sumx*sumx)*1.0);
    b=((n*sumxy-sumx*sumy)*1.0/(n*sumx2-sumx*sumx)*1.0);
    a=exp(A);    
    
    return 0.8*(a*exp(b*(times.size()))/100); //divide answer by 100 so answer is back in real seconds
                                              //also multiply by .8 because real time is typically 80% of the estimate 
}



//gets list of all legal moves for a board state
vector<gameMove> getLegalMoves(Board b, Team t, pos enPassantPos)
{   
    GamePiece kingPiece; //piece used to search for king
    for (int j=0; j<8; j++)
    {
      for (int i=0; i<8; i++)
      {
        kingPiece = b.getPiece(i,j);
        if (kingPiece.isActive() && kingPiece.getTeam()==t && kingPiece.getType()==King)
        {          
          goto stopPieceSearch; //once king found, break out of doubly nested loop
        }
      }
    }
    stopPieceSearch:
    
    gameMove doNotDo;
    bool doNotRepeat=false;
    
    if (b.turnsSincePawnMove>6 && b.turnsSinceCapture>6)
    {     
      if (b.lastEightMoves.size()>7)
      {
        if (moveMatches(b.lastEightMoves[1],b.lastEightMoves[5])
         && moveMatches(b.lastEightMoves[2],b.lastEightMoves[6])
         && moveMatches(b.lastEightMoves[3],b.lastEightMoves[7]))
         { 
         /*
           cout << "CAN REPETITION" << endl;
           cout << "DO NOT DO ";
           cout << char(b.lastEightMoves[4].start.x+'a') << char(b.lastEightMoves[4].start.y+'1') << char(b.lastEightMoves[4].end.x+'a') << char(b.lastEightMoves[4].end.y+'1') << endl;
           
           cout << "Last Eight Moves:" << endl;
           for (auto le : b.lastEightMoves)
           {
             cout << char(le.start.x+'a') << char(le.start.y+'1') << char(le.end.x+'a') << char(le.end.y+'1') << endl;
           }
           */
           doNotRepeat=true;
           doNotDo.start.x = b.lastEightMoves[4].start.x;
           doNotDo.start.y = b.lastEightMoves[4].start.y;
           doNotDo.end.x = b.lastEightMoves[4].end.x;
           doNotDo.end.y = b.lastEightMoves[4].end.y;
         }         
      }      
      
    }
    if (b.turnsSincePawnMove>5 && b.turnsSinceCapture>5)
    {
      if (b.lastEightMoves.size()>7)
      {
        if (moveMatches(b.lastEightMoves[2],b.lastEightMoves[6])         
         && moveMatches(b.lastEightMoves[3],b.lastEightMoves[7]))
         { 
         /*
           cout << "CAN REPETITION 2" << endl;
           cout << "DO NOT DO ";
           cout << char(b.lastEightMoves[4].start.x+'a') << char(b.lastEightMoves[4].start.y+'1') << char(b.lastEightMoves[4].end.x+'a') << char(b.lastEightMoves[4].end.y+'1') << endl;
           
           cout << "Last Eight Moves:" << endl;
           for (auto le : b.lastEightMoves)
           {
             cout << char(le.start.x+'a') << char(le.start.y+'1') << char(le.end.x+'a') << char(le.end.y+'1') << endl;
           }
           */
           doNotRepeat=true;
           doNotDo.start.x = b.lastEightMoves[4].start.x;
           doNotDo.start.y = b.lastEightMoves[4].start.y;
           doNotDo.end.x = b.lastEightMoves[4].end.x;
           doNotDo.end.y = b.lastEightMoves[4].end.y;
         }         
      }
      
      
    }
    
    
    
    
    
    
        
    vector<gameMove> allPotentialMoves; //list of potential moves
    
    for (int j=0; j<8; j++)
    {
      for (int i=0; i<8; i++) //loop through every position
      {
        pos p;
        p.x=i;
        p.y=j;
        
        if (b.getPiece(i,j).isActive()) //first ensure a piece actually exists in this square
        {
          if (b.getPiece(i,j).getTeam()==t) //piece must be on my team
          {
            //gets all potentially legal moves and makes sure they don't violate check
            vector<gameMove> m = getPotentialMoves(b, p, enPassantPos); 
            
            Board testBoard; //board for testing check requirements
            pos kingPos; //projected king position, usually actual king pos but sometimes not if piece moving is actually the king
            for (auto mov : m) //for moves in potentialMoves for this piece
            {              
              if (mov.end.x>-1 && mov.end.y>-1 && mov.end.x<8 && mov.end.y<8)
              {
                testBoard = b; //start off test board with real board
                
                testBoard.procMove(mov); //do the "what-if" move on the test board
                kingPos = kingPiece.getPos(); //kingPos is the position of the real king               
                
                if (mov.start.x==kingPos.x && mov.start.y==kingPos.y) //unless the piece moving IS the king, then update it
                {
                  kingPos.x = mov.end.x;
                  kingPos.y = mov.end.y;
                }
                if (!isInCheck(testBoard, kingPos, t)) //finally, see if the king would be in check after this move
                {
                  allPotentialMoves.push_back(mov); //if the king is not left in check after this move, it is a valid move for this turn
                }
              }
            }
            
          }
        }       
        
      }
    }
    
    if (doNotRepeat)
    {
      if (allPotentialMoves.size()>1) //if only one move possible, it cant be avoided
      {        
        for (unsigned int i=0; i<allPotentialMoves.size(); i++)
        {
          if (moveMatches(allPotentialMoves[i], doNotDo))
          {
            allPotentialMoves.erase(allPotentialMoves.begin()+i);
            //deleted move
            //cout << "\t\t\t\tremoving possible repeat" << endl;
            break;
          }
        }
      }
    }
    
    
    
    
    //check castling ability
    
    //king and rook must not have moved
    //must be space between them
    //king cannot pass through check
       
    
    if (!kingPiece.getMoved()) //king cannot castle if he has already moved
    { 
      if (!isInCheck(b, kingPiece.getPos(), t)) //king cant be in check currently
      {
        
        //check queenside castle
        
        int diff=1; //differential position
        
          
        while (!b.getPiece(kingPiece.getPos().x-diff, kingPiece.getPos().y).isActive()) //everything between king and rook should be empty
        {          
          diff++;
          if (kingPiece.getPos().x-diff==0) break; //don't run off the board          
        }
        //when this breaks, the piece at x-diff,y should be the closest piece to the left of the king
        
        //make sure there is a piece, the piece is a rook, it is on my team, and has not moved
        if (b.getPiece(kingPiece.getPos().x-diff,kingPiece.getPos().y).isActive() && b.getPiece(kingPiece.getPos().x-diff,kingPiece.getPos().y).getType()==Rook && b.getPiece(kingPiece.getPos().x-diff,kingPiece.getPos().y).getTeam()==t && b.getPiece(kingPiece.getPos().x-diff,kingPiece.getPos().y).getMoved()==false)
        {
          //check if king passes through check
          
          Board testBoard = b; //get test board to check for check
          
          gameMove m;
          m.start.x = kingPiece.getPos().x;
          m.start.y = kingPiece.getPos().y;
          m.end.x = kingPiece.getPos().x-1;
          m.end.y = kingPiece.getPos().y;
          
          testBoard.procMove(m); //simulate the king moving one space to the left
          
          if (!isInCheck(testBoard, m.end, t)) //if he isn't in check, keep moving
          {
            m.start.x = kingPiece.getPos().x-1;
            m.start.y = kingPiece.getPos().y;
            m.end.x = kingPiece.getPos().x-2;
            m.end.y = kingPiece.getPos().y;
            
            testBoard.procMove(m); //simulate the king moving one more space to the left
            
            if (!isInCheck(testBoard, m.end, t)) //if he still isn't in check, then it is legal to do a queenside castle
            {              
              m.start.x = kingPiece.getPos().x;
              m.start.y = kingPiece.getPos().y;
              m.end.x = kingPiece.getPos().x-2;
              m.end.y = kingPiece.getPos().y;
              allPotentialMoves.push_back(m); //add long castle to list of moves
            }            
          }
        }
        
        //check kingside castle
        
        diff=1;
        
        while (!b.getPiece(kingPiece.getPos().x+diff, kingPiece.getPos().y).isActive()) //everything between king and rook should be empty
        {
          diff++;
          if (kingPiece.getPos().x+diff==7) break; //don't run off the board          
        }
        //when this breaks, the piece at x+diff,y should be the closest piece to the right of the king
        
        //make sure there is a piece, the piece is a rook, it is on my team, and has not moved
        if (b.getPiece(kingPiece.getPos().x+diff,kingPiece.getPos().y).getType()==Rook && b.getPiece(kingPiece.getPos().x+diff,kingPiece.getPos().y).getTeam()==t && b.getPiece(kingPiece.getPos().x+diff,kingPiece.getPos().y).getMoved()==false)
        {
          //check if king passes through check
          
          Board testBoard = b; //get test board to check for check
          
          gameMove m;
          m.start.x = kingPiece.getPos().x;
          m.start.y = kingPiece.getPos().y;
          m.end.x = kingPiece.getPos().x+1;
          m.end.y = kingPiece.getPos().y;
          
          testBoard.procMove(m); //simulate the king moving one space to the left
          
          if (!isInCheck(testBoard, m.end, t)) //if he isn't in check, keep moving
          {
            m.start.x = kingPiece.getPos().x+1;
            m.start.y = kingPiece.getPos().y;
            m.end.x = kingPiece.getPos().x+2;
            m.end.y = kingPiece.getPos().y;
            
            testBoard.procMove(m); //simulate the king moving one more space to the left
            
            if (!isInCheck(testBoard, m.end, t)) //if he still isn't in check, then it is legal to do a kingsideside castle
            {
              //legal queenside castle              
              
              m.start.x = kingPiece.getPos().x;
              m.start.y = kingPiece.getPos().y;
              m.end.x = kingPiece.getPos().x+2;
              m.end.y = kingPiece.getPos().y;
              allPotentialMoves.push_back(m); //add short castle to list of moves
            }            
          }
        }
      }      
    }

    return allPotentialMoves;
}






//prints the board and various important information about the state
void Board::printBoard(int layer)
{    
  for (int k=0; k<layer; k++)
  {
    cout << "\t";
  }
  cout << " abcdefgh" << endl; //print the column names
  for (int j=7; j>-1; j--)
  {
    for (int k=0; k<layer; k++)
    {
      cout << "\t";
    }
    cout << (j+1); //print this row's number
    for (int i=0; i<8; i++)
    {
      cout << board[j][i].pieceRepr(); //print the representation of all 8 pieces on this row
    }
    cout <<(j+1); //print this row's number again
    cout << endl;
  }
  for (int k=0; k<layer; k++)
  {
    cout << "\t";
  }
  cout << " abcdefgh" << endl; //print column names again
  if (currTurn==White)
  {
    cout << "White's turn" << endl;
  }
  else
  {
    cout << "Black's turn" << endl;
  }
  cout << moves << " moves made" << endl;
  cout << "W: " << whitePoints << endl;
  cout << "B: " << blackPoints << endl;  
  cout << "EPP: ";
  if (enPassantPos.x==-1)
  {
    cout << "None" << endl;
  }
  else
  {
    cout << char(enPassantPos.x+'a') << char(enPassantPos.y+'1') << endl;
  }
  cout << "TSPM: " << turnsSincePawnMove << endl;  
  cout << "TSC: " << turnsSinceCapture << endl;  
  /*
  cout << "Last eight moves:" << endl;
  for (auto lem : lastEightMoves)
  {
    cout << char(lem.start.x+'a') << char(lem.start.y+'1') << char(lem.end.x+'a') << char(lem.end.y+'1') << endl;
  }
  */
  cout << endl;
}

GamePiece &Board::getPiece(int x, int y)
{
  if (x>=0 && x<8 && y>=0 && y<8) //if its a valid position, return that piece by reference
    return board[y][x];
  else return emptyPiece; //otherwise return the emptyPiece
}



//adds points to the board for whichever team is opposite to the removed piece
//P:1 B:3 N:3 R:5 Q:5
//kings cannot actually be captured, but the algorithm assumes they can. That way, i can assign a large point value,
//and the pieces will naturally prefer to put the king in checkmate
void Board::addPoints(GamePiece piece)
{  
  if (piece.isActive())
  {
    if (piece.getTeam()==White)
    {
      switch(piece.getType())
      {
        case Rook:
          blackPoints+=50;
          return;
        case Knight:
          blackPoints+=30;
          return;
        case Bishop:
          blackPoints+=30;
          return;
        case Queen:
          blackPoints+=90;
          return;
        case Pawn:
          blackPoints+=10;          
          if (piece.getPos().y==6) //if pawn is one away from promotion, increase worth
            blackPoints+=80;          
          return;
        case King:
          blackPoints+=1000;
        default:
          return;
      }
    }
    else
    {
      switch(piece.getType())
      {
        case Rook:
          whitePoints+=50;
          return;
        case Knight:
          whitePoints+=30;
          return;
        case Bishop:
          whitePoints+=30;
          return;
        case Queen:
          whitePoints+=90;
          return;
        case Pawn:
          whitePoints+=10;
          if (piece.getPos().y==1) //if pawn is one away from promotion, increase worth
            whitePoints+=80;
          return;
        case King:
          whitePoints+=1000;
        default:
          return;
      }
    }
  }
}


void Board::procMove(gameMove m) //process the move
{
  if (m.start.x<0 || m.start.x>7 || m.start.y<0 || m.start.y>7 || m.end.x<0 || m.end.x>7 || m.end.y<0 || m.end.y>7) 
  {
    cout << "Invalid move" << endl;    
    exit(1);
  }
  
  turnsSincePawnMove++;
  turnsSinceCapture++;
  
  //if en passant, remove piece which was en passant'd
  if (m.enPassantMove)
  {
    turnsSinceCapture=0;
    if (board[m.start.y][m.start.x].getTeam()==White)
    {
      //if moving piece is White, piece to remove is below the end space,
      addPoints(board[m.end.y-1][m.end.x]);
      board[m.end.y-1][m.end.x] = GamePiece();
    }
    else
    {
      //if moving piece is Black, piece to remove is above the end space
      addPoints(board[m.end.y+1][m.end.x]);
      board[m.end.y+1][m.end.x] = GamePiece();
    }
  } 
  
  if (board[m.end.y][m.end.x].isActive())
  {
    //if active piece at end zone, piece capture
    turnsSinceCapture=0;
  }
  
  
  //add points for removed piece, if any
  addPoints(board[m.end.y][m.end.x]);
  board[m.end.y][m.end.x] = board[m.start.y][m.start.x]; //copy the piece from start to end
  board[m.end.y][m.end.x].setPos(m.end.x,m.end.y);   //update that piece's coordinates
  board[m.end.y][m.end.x].setMoved(true);      //update his move bool  
  board[m.start.y][m.start.x] = GamePiece();  //remove the piece at his old position
  
  //check if the move would allow en passant
  
  enPassantPos.x = -1;
  enPassantPos.y = -1; //reset enPassantPos
  
  if (board[m.end.y][m.end.x].getType()==Pawn)
  {
    turnsSincePawnMove=0;
    
    if (board[m.end.y][m.end.x].getTeam()==White)
    {
      if (myTeam==White)
        whitePoints+=1;
    }
    else
    {
      if (myTeam==Black)
        blackPoints+=1;
    }
    
    
    if (m.end.y-m.start.y == 2)
    {
      //white pawn double move
      //update enPassantPos to space one below end spot
      enPassantPos.x = m.end.x;
      enPassantPos.y = m.end.y-1;
      if (myTeam==White)
        whitePoints+=1;
    }
    else if (m.end.y-m.start.y == -2)
    {
      //black pawn double move
      //update enPassantPos to space one above end spot
      enPassantPos.x = m.end.x;
      enPassantPos.y = m.end.y+1;
      if (myTeam==Black)
        blackPoints+=1;
    }    
  }
  
  
  if (m.end.y==7 && board[m.end.y][m.end.x].getType()==Pawn)
  {
    //cout << "White Promotion" << endl;
    whitePoints+=80;
    board[m.end.y][m.end.x].setType(Queen);
  }
  else if(m.end.y==0 && board[m.end.y][m.end.x].getType()==Pawn)
  {
    //cout << "Black Promotion" << endl;
    blackPoints+=80;
    board[m.end.y][m.end.x].setType(Queen);
  }
  
  //if moving piece was a king, see if move was a castle
  if (board[m.end.y][m.end.x].getType()==King && m.start.y==m.end.y) //king only moved horizontally
  {
    if (m.start.x+2==m.end.x) //if king moved 2 spaces right, kingside castle
    {
      //move rook on right side to left of king
            
      board[m.end.y][m.end.x-1] = board[m.start.y][7]; //get rook at x pos 7 and move it to left of king
      board[m.end.y][m.end.x-1].setPos(m.end.x-1,m.end.y); 
      //update that rooks coords
      board[m.end.y][m.end.x-1].setMoved(true);    //he has now moved
      board[m.start.y][7] = GamePiece();          //delete piece at old position
      
    }
    else if (m.start.x-2==m.end.x) ////if king moved 2 spaces left, queenside castle
    {
      //move rook on left side to right of king
      board[m.end.y][m.end.x+1] = board[m.start.y][0];//get rook at x pos 0 and move it to right of king
      board[m.end.y][m.end.x+1].setPos(m.end.x+1,m.end.y); //update that rooks coords
      board[m.end.y][m.end.x+1].setMoved(true);    //he has now moved
      board[m.start.y][0] = GamePiece();          //delete piece at old position
      
    } //else, it was a regular king move 1 space to the side
  }  
  
  moves++;
  if (currTurn==White)
  {
    currTurn=Black;
  }
  else
  {
    currTurn=White;
  }
  
  lastEightMoves.push_back(m);
  
  if (lastEightMoves.size()>8)
  {
    lastEightMoves.erase(lastEightMoves.begin());
  }
  
}

pos getEnPassantPos(string fen) //takes in fen string and returns the position where en passant is possible, or -1,-1 if it isnt
{
  stringstream ss;
  
  ss << fen;
  string token;
  
  vector<string> v;
  
  while (getline(ss,token,' '))
  {    
    v.push_back(token);
  }
  
  pos ret;
  
  if (v[3]!="-")
  {
    //en passant possibility
    ret.x = int(v[3][0]-'a');
    ret.y = int(v[3][1]-'1');    
  }  
  else 
  {
    ret.x=-1;
    ret.y=-1;
  }
  
  return ret;
}

//takes a board b, a position, and the position where enPassant is possible and gets a list of all POTENTIAL moves not accounting for whether or not the king
//will be in check after it
vector<gameMove> getPotentialMoves(Board b, pos piecePosition, pos enPassant)
{
  
  GamePiece *thisPiece = &b.getPiece(piecePosition.x,piecePosition.y); //get pointer to the piece at the specified position
  
  vector<gameMove> moves; //list of moves
  pos p = thisPiece->getPos();
  if (thisPiece->getType()==Pawn)
  { 
    //pawn
    if (thisPiece->getTeam()==White)
    {
      gameMove m;
      m.start = piecePosition;
      
      if ((b.getPiece(m.start.x-1,m.start.y+1).isActive() && b.getPiece(m.start.x-1,m.start.y+1).getTeam()==Black) || (m.start.x-1==enPassant.x && m.start.y+1==enPassant.y))
      {
        //if the space to the upper left has a black piece or is the en passant position
        m.end.x=m.start.x-1;
        m.end.y=m.start.y+1;        
        m.enPassantMove = (m.start.x-1==enPassant.x && m.start.y+1==enPassant.y);         
        moves.push_back(m);     //add to list        
      }
      
      if ((b.getPiece(m.start.x+1,m.start.y+1).isActive() && b.getPiece(m.start.x+1,m.start.y+1).getTeam()==Black) || (m.start.x+1==enPassant.x && m.start.y+1==enPassant.y))
      {        
        //if the space to the upper right has a black piece or is the en passant position
        m.end.x=m.start.x+1;
        m.end.y=m.start.y+1;
        m.enPassantMove = (m.start.x+1==enPassant.x && m.start.y+1==enPassant.y);
        moves.push_back(m); //add to list
      }
      m.end.x = thisPiece->getPos().x;
      m.end.y = thisPiece->getPos().y+1; //space directly ahead
      
      if (!b.getPiece(m.end.x,m.end.y).isActive()) //if the space is empty, add it to the list
      {
        moves.push_back(m);     
      
        //if the space 1 ahead is empty, see if the pawn has not moved and the space two ahead is blank, if so it can double move
        if (!b.getPiece(m.start.x,m.start.y).getMoved())
        {
          //double move        
          m.end.y = thisPiece->getPos().y+2;
          if (!b.getPiece(m.end.x,m.end.y).isActive())
            moves.push_back(m);             
        }
      }
    }
    else //same thing, only in downwards direction because the pawns are on black team    
    {    //I should simplify this soon because a decent amount is the same, only some values differ
      gameMove m;
      m.start = piecePosition;
      
      if ((b.getPiece(m.start.x-1,m.start.y-1).isActive() && b.getPiece(m.start.x-1,m.start.y-1).getTeam()==White) || (m.start.x-1==enPassant.x && m.start.y-1==enPassant.y))
      {
        //can overtake
        m.end.x=m.start.x-1;
        m.end.y=m.start.y-1;
        m.enPassantMove = (m.start.x-1==enPassant.x && m.start.y-1==enPassant.y);
        moves.push_back(m);             
      }
      
      if ((b.getPiece(m.start.x+1,m.start.y-1).isActive() && b.getPiece(m.start.x+1,m.start.y-1).getTeam()==White) || (m.start.x+1==enPassant.x && m.start.y-1==enPassant.y))
      {
        //can overtake
        m.end.x=m.start.x+1;
        m.end.y=m.start.y-1;
        m.enPassantMove = (m.start.x+1==enPassant.x && m.start.y-1==enPassant.y);
        moves.push_back(m);             
      }
      
      m.end.x = thisPiece->getPos().x;
      m.end.y = thisPiece->getPos().y-1;
      
      if (!b.getPiece(m.end.x,m.end.y).isActive())
      {
        moves.push_back(m); 
      
        if (!b.getPiece(m.start.x,m.start.y).getMoved())
        {
          //double move        
          m.end.y = thisPiece->getPos().y-2;
          if (!b.getPiece(m.end.x,m.end.y).isActive())
            moves.push_back(m);             
        }
      }      
    }    
  }
  else if (thisPiece->getType()==Knight)
  {
    vector<pos> destinations;
    
    destinations.push_back({p.x-2,p.y+1});
    destinations.push_back({p.x-2,p.y-1});
    destinations.push_back({p.x-1,p.y-2});
    destinations.push_back({p.x+1,p.y-2});
    destinations.push_back({p.x+2,p.y-1});
    destinations.push_back({p.x+2,p.y+1});
    destinations.push_back({p.x+1,p.y+2});
    destinations.push_back({p.x-1,p.y+2}); //these are the eight possible spaces a knight can jump to
    
    gameMove gm;
    gm.start.x=p.x;
    gm.start.y=p.y; 
    
    
    for (auto d : destinations) //for all of these spaces
    {
      if (d.x>-1 && d.x<8 && d.y>-1 && d.y<8) //ensure the end space is on the board
      { 
        if (!b.getPiece(d.x,d.y).isActive() || (b.getPiece(d.x,d.y).isActive() && b.getPiece(d.x,d.y).getTeam()!=thisPiece->getTeam())) //if the piece is empty, or if it is the opposite team
        {
          //valid
          gm.end.x=d.x;
          gm.end.y=d.y;
          moves.push_back(gm); //add the move to the list
        }        
      }
    }
  }
  else if(thisPiece->getType()==King)
  {
    vector<pos> destinations;
    
    for (int x=-1;x<2;x++)
    {
      for (int y=-1;y<2;y++)
      {
        if (x==0 && y==0) continue; //skip the center space        
        destinations.push_back({p.x+x,p.y+y}); //add all 8 spaces around the king 
      }
    }
    
    gameMove gm;
    gm.start.x=p.x;
    gm.start.y=p.y;
    
    for (auto d : destinations)
    {
      if (d.x>-1 && d.x<8 && d.y>-1 && d.y<8)
      {
        //in bounds of board
        
        if (!b.getPiece(d.x,d.y).isActive() || (b.getPiece(d.x,d.y).isActive() && b.getPiece(d.x,d.y).getTeam()!=thisPiece->getTeam()))
        {
          //valid
          gm.end.x=d.x;
          gm.end.y=d.y;
          moves.push_back(gm);
        }        
      }
    }
  }
  else
  {
    
    if(thisPiece->getType()==Rook || thisPiece->getType()==Queen) //if rook or queen, add every horizontal and vertical line spaces from the piece
    {
      
      gameMove gm;
      gm.start.x=p.x;
      gm.start.y=p.y;
      
      //horizontal left
      for (int i=1;i<8; i++)
      {
        if (p.x-i<0) break;
        
        if (b.getPiece(p.x-i, p.y).isActive())
        {        
          if (b.getPiece(p.x-i, p.y).getTeam()==thisPiece->getTeam()) break;
          gm.end.x=p.x-i;
          gm.end.y=p.y;        
          moves.push_back(gm);
          break;        
        }
        else
        {
          gm.end.x=p.x-i;
          gm.end.y=p.y;        
          moves.push_back(gm);        
        }
      }
      
      //horizontal right
      for (int i=1;i<8; i++)
      {
        if (p.x+i>7) break;
        
        if (b.getPiece(p.x+i, p.y).isActive())
        {        
          if (b.getPiece(p.x+i, p.y).getTeam()==thisPiece->getTeam()) break;
          gm.end.x=p.x+i;
          gm.end.y=p.y;        
          moves.push_back(gm);
          break;        
        }
        else
        {
          gm.end.x=p.x+i;
          gm.end.y=p.y;        
          moves.push_back(gm);        
        }
      }
      
      //vertical down
      for (int i=1;i<8; i++)
      {
        if (p.y-i<0) break;
        
        if (b.getPiece(p.x, p.y-i).isActive())
        {        
          if (b.getPiece(p.x, p.y-i).getTeam()==thisPiece->getTeam()) break;
          gm.end.x=p.x;
          gm.end.y=p.y-i;        
          moves.push_back(gm);
          break;        
        }
        else
        {
          gm.end.x=p.x;
          gm.end.y=p.y-i;        
          moves.push_back(gm);        
        }
      }
      
      //vertical up
      for (int i=1;i<8; i++)
      {
        if (p.y+i>7) break;
        
        if (b.getPiece(p.x, p.y+i).isActive())
        {        
          if (b.getPiece(p.x, p.y+i).getTeam()==thisPiece->getTeam()) break;
          gm.end.x=p.x;
          gm.end.y=p.y+i;        
          moves.push_back(gm);
          break;        
        }
        else
        {
          gm.end.x=p.x;
          gm.end.y=p.y+i;        
          moves.push_back(gm);        
        }
      }           
    }
    if(thisPiece->getType()==Bishop || thisPiece->getType()==Queen) //if bishop or queen, add all diagonal line spaces to list
    {
      
      gameMove gm;
      gm.start.x=p.x;
      gm.start.y=p.y;
      
      //lower left diagonal
      for (int i=1;i<8; i++)
      {
        if (p.x-i<0 || p.y-i<0) break;
        
        if (b.getPiece(p.x-i, p.y-i).isActive())
        {        
          if (b.getPiece(p.x-i, p.y-i).getTeam()==thisPiece->getTeam()) break;
          gm.end.x=p.x-i;
          gm.end.y=p.y-i;        
          moves.push_back(gm);
          break;        
        }
        else
        {
          gm.end.x=p.x-i;
          gm.end.y=p.y-i;        
          moves.push_back(gm);        
        }
      }
      
      //lower right diagonal
      for (int i=1;i<8; i++)
      {
        if (p.x+i>7 || p.y-i<0) break;
        
        if (b.getPiece(p.x+i, p.y-i).isActive())
        {        
          if (b.getPiece(p.x+i, p.y-i).getTeam()==thisPiece->getTeam()) break;
          gm.end.x=p.x+i;
          gm.end.y=p.y-i;        
          moves.push_back(gm);
          break;        
        }
        else
        {
          gm.end.x=p.x+i;
          gm.end.y=p.y-i;        
          moves.push_back(gm);        
        }
      }
      
      //upper left diagonal
      for (int i=1;i<8; i++)
      {
        if (p.x-i<0 || p.y+i>7) break;
        
        if (b.getPiece(p.x-i, p.y+i).isActive())
        {        
          if (b.getPiece(p.x-i, p.y+i).getTeam()==thisPiece->getTeam()) break;
          gm.end.x=p.x-i;
          gm.end.y=p.y+i;        
          moves.push_back(gm);
          break;        
        }
        else
        {
          gm.end.x=p.x-i;
          gm.end.y=p.y+i;        
          moves.push_back(gm);        
        }
      }
      
      //upper right diagonal
      for (int i=1;i<8; i++)
      {
        if (p.x+i>7 || p.y+i>7) break;
        
        if (b.getPiece(p.x+i, p.y+i).isActive())
        {        
          if (b.getPiece(p.x+i, p.y+i).getTeam()==thisPiece->getTeam()) break;
          gm.end.x=p.x+i;
          gm.end.y=p.y+i;        
          moves.push_back(gm);
          break;        
        }
        else
        {
          gm.end.x=p.x+i;
          gm.end.y=p.y+i;        
          moves.push_back(gm);        
        }
      }      
    }
  }
  return moves;
}

//parse fen and return the initial board
Board parseFen(string fen)
{
  stringstream ss;
  
  ss << fen;
  string token;
  
  vector<string> v;
  
  while (getline(ss,token,' ')) //split the fen by spaces
  {    
    v.push_back(token);
  }
  
  stringstream ss2;
  ss2 << v[0];
  vector<string> pieces;
  while (getline(ss2,token,'/')) //split the first fen info by /'s, aka row
  {    
    pieces.push_back(token);
  }
  std::reverse(pieces.begin(), pieces.end()); //invert the rows
  
  Board b = Board(pieces);
  if (v[1]=="b") b.currTurn=Black;
  
  return b; //initialize a board with these pieces and return it
}

//determine if the space kingPos of team t is in check with board board
bool isInCheck(Board board, pos kingPos, Team t)
{
  //check horizonal positions from king
  
  for (int i=1; i<8; i++)
  {
    if (kingPos.x-i<0) break; //stop at edge
    if (board.getPiece(kingPos.x-i,kingPos.y).isActive() && board.getPiece(kingPos.x-i,kingPos.y).getTeam()==t)
    {
      //hit own team's piece, so stop searching in this dir
      break;
    }
    if (board.getPiece(kingPos.x-i,kingPos.y).isActive()) //enemy piece
    {
      //check piece's role to see if in check
      if (board.getPiece(kingPos.x-i,kingPos.y).getType()==Rook || board.getPiece(kingPos.x-i,kingPos.y).getType()==Queen)
      {
        //check
        return true;
      }
      if (i>1) break;
      if (board.getPiece(kingPos.x-i,kingPos.y).getType()==King) //if only one piece away, also check if the piece is also a king
      {
          return true;
      }
      break;
    }
  }
  
  for (int i=1; i<8; i++)
  {
    if (kingPos.x+i>7) break;
    if (board.getPiece(kingPos.x+i,kingPos.y).isActive() && board.getPiece(kingPos.x+i,kingPos.y).getTeam()==t)
    {
      //hit own team's piece, so stop searching in this dir
      break;
    }
    if (board.getPiece(kingPos.x+i,kingPos.y).isActive()) //enemy piece
    {
      //check piece's role to see if in check
      
      if (board.getPiece(kingPos.x+i,kingPos.y).getType()==Rook || board.getPiece(kingPos.x+i,kingPos.y).getType()==Queen)
      {
        //check
        return true;
      }
      if (i>1) break;
      if (board.getPiece(kingPos.x+i,kingPos.y).getType()==King) //if only one piece away, also check if the piece is also a king   
      {
          return true;
      }
      break;
    }
  }
  //check vertical positions from king
  for (int i=1; i<8; i++)
  {
    if (kingPos.y-i<0) break;
    if (board.getPiece(kingPos.x,kingPos.y-i).isActive() && board.getPiece(kingPos.x,kingPos.y-i).getTeam()==t)
    {
      //hit own team's piece, so stop searching in this dir
      break;
    }
    if (board.getPiece(kingPos.x,kingPos.y-i).isActive()) //enemy piece
    {
      //check piece's role to see if in check
      
      if (board.getPiece(kingPos.x,kingPos.y-i).getType()==Rook || board.getPiece(kingPos.x,kingPos.y-i).getType()==Queen)
      {
        //check
        return true;
      }
      if (i>1) break;
      if (board.getPiece(kingPos.x,kingPos.y-i).getType()==King) //if only one piece away, also check if the piece is also a king        
      {
          return true;
      }
      break;
    }
  }
  
  for (int i=1; i<8; i++)
  {
    if (kingPos.y+i>7) break;
    if (board.getPiece(kingPos.x,kingPos.y+i).isActive() && board.getPiece(kingPos.x,kingPos.y+i).getTeam()==t)
    {
      //hit own team's piece, so stop searching in this dir
      break;
    }
    if (board.getPiece(kingPos.x,kingPos.y+i).isActive()) //enemy piece
    {
      //check piece's role to see if in check
      
      if (board.getPiece(kingPos.x,kingPos.y+i).getType()==Rook || board.getPiece(kingPos.x,kingPos.y+i).getType()==Queen)
      {
        //check
        return true;
      }
      if (i>1) break;
      if (board.getPiece(kingPos.x,kingPos.y+i).getType()==King) //if only one piece away, also check if the piece is also a king        
      {
          return true;
      }
      break;
    }
  }
  //check diagonal positions from king
  
  for (int i=1; i<8; i++)
  {
    if (kingPos.x-i<0 || kingPos.y-i<0) break;
    if (board.getPiece(kingPos.x-i,kingPos.y-i).isActive() && board.getPiece(kingPos.x-i,kingPos.y-i).getTeam()==t)
    {
      //hit own team's piece, so stop searching in this dir
      break;
    }
    if (board.getPiece(kingPos.x-i,kingPos.y-i).isActive()) //enemy piece
    {
      //check piece's role to see if in check
      
      if (board.getPiece(kingPos.x-i,kingPos.y-i).getType()==Bishop || board.getPiece(kingPos.x-i,kingPos.y-i).getType()==Queen)
      {
        //check
        return true;
      }
      //otherwise, check if a pawn can capture
      if (t==Black)
      {
        if (i==1) 
        {          
          if (board.getPiece(kingPos.x-i,kingPos.y-i).getType()==Pawn)        
          {
              return true;
          }
        }
      }
      if (i>1) break;
      if (board.getPiece(kingPos.x-i,kingPos.y-i).getType()==King) //if only one piece away, also check if the piece is also a king        
      {
          return true;
      }
      break;
    }
  }
  
  for (int i=1; i<8; i++)
  {
    if (kingPos.x+i>7 || kingPos.y-i<0) break;
    if (board.getPiece(kingPos.x+i,kingPos.y-i).isActive() && board.getPiece(kingPos.x+i,kingPos.y-i).getTeam()==t)
    {
      //hit own team's piece, so stop searching in this dir
      break;
    }
    if (board.getPiece(kingPos.x+i,kingPos.y-i).isActive()) //enemy piece
    {
      //check piece's role to see if in check
      
      if (board.getPiece(kingPos.x+i,kingPos.y-i).getType()==Bishop || board.getPiece(kingPos.x+i,kingPos.y-i).getType()==Queen)
      {
        //check
        return true;
      }
      //otherwise, check if a pawn can capture
      if (t==Black)
      {
        if (i==1)
        { 
          if (board.getPiece(kingPos.x+i,kingPos.y-i).getType()==Pawn) //if only one piece away, also check if the piece is also a king                
          {
              return true;
          }
        }
      }
      if (i>1) break;
      if (board.getPiece(kingPos.x+i,kingPos.y-i).getType()==King)        
      {
          return true;
      }
      break;
    }
  }
  
  
  for (int i=1; i<8; i++)
  {
    if (kingPos.x-i<0 || kingPos.y+i>7) break;
    if (board.getPiece(kingPos.x-i,kingPos.y+i).isActive() && board.getPiece(kingPos.x-i,kingPos.y+i).getTeam()==t)
    {
      //hit own team's piece, so stop searching in this dir
      break;
    }
    if (board.getPiece(kingPos.x-i,kingPos.y+i).isActive()) //enemy piece
    {
      //check piece's role to see if in check
      
      if (board.getPiece(kingPos.x-i,kingPos.y+i).getType()==Bishop || board.getPiece(kingPos.x-i,kingPos.y+i).getType()==Queen)
      {
        //check
        return true;
      }
      //otherwise, check if a pawn can capture
      if (t==White)
      {
        if (i==1)
        { 
          if (board.getPiece(kingPos.x-i,kingPos.y+i).getType()==Pawn)        
          {
              return true;
          }
        }
      }
      if (i>1) break;
      if (board.getPiece(kingPos.x-i,kingPos.y+i).getType()==King) //if only one piece away, also check if the piece is also a king               
      {
          return true;
      }
      break;
    }
  }
  
  for (int i=1; i<8; i++)
  {
    if (kingPos.x+i>7 || kingPos.y+i>7) break;
    if (board.getPiece(kingPos.x+i,kingPos.y+i).isActive() && board.getPiece(kingPos.x+i,kingPos.y+i).getTeam()==t)
    {
      //hit own team's piece, so stop searching in this dir
      break;
    }
    if (board.getPiece(kingPos.x+i,kingPos.y+i).isActive()) //enemy piece
    {
      //check piece's role to see if in check
      
      if (board.getPiece(kingPos.x+i,kingPos.y+i).getType()==Bishop || board.getPiece(kingPos.x+i,kingPos.y+i).getType()==Queen)
      {
        //check
        return true;
      }
      //otherwise, check if a pawn can capture
      if (t==White)
      {
        if (i==1)
        { 
          if (board.getPiece(kingPos.x+i,kingPos.y+i).getType()==Pawn)        
          {
              return true;
          }
        }
      }
      if (i>1) break;
      if (board.getPiece(kingPos.x+i,kingPos.y+i).getType()==King) //if only one piece away, also check if the piece is also a king               
      {
          return true;
      }
      break;
    }
  }
    
  //for all 8 spaces where a knight could put the king in danger, test if an enemy knight is there
  GamePiece p = board.getPiece(kingPos.x-2, kingPos.y-1);
  if (p.isActive() && p.getTeam()!=t && p.getType()==Knight) return true;    
  p = board.getPiece(kingPos.x-2, kingPos.y+1);
  if (p.isActive() && p.getTeam()!=t && p.getType()==Knight) return true;  
  p = board.getPiece(kingPos.x-1, kingPos.y+2);
  if (p.isActive() && p.getTeam()!=t && p.getType()==Knight) return true;  
  p = board.getPiece(kingPos.x+1, kingPos.y+2);
  if (p.isActive() && p.getTeam()!=t && p.getType()==Knight) return true;  
  p = board.getPiece(kingPos.x+2, kingPos.y+1);
  if (p.isActive() && p.getTeam()!=t && p.getType()==Knight) return true; 
  p = board.getPiece(kingPos.x+2, kingPos.y-1);
  if (p.isActive() && p.getTeam()!=t && p.getType()==Knight) return true; 
  p = board.getPiece(kingPos.x+1, kingPos.y-2);
  if (p.isActive() && p.getTeam()!=t && p.getType()==Knight) return true; 
  p = board.getPiece(kingPos.x-1, kingPos.y-2);
  if (p.isActive() && p.getTeam()!=t && p.getType()==Knight) return true;
  
  return false; //otherwise, king is safe at this position
}
