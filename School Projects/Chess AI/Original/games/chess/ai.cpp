// AI
// This is where you build your AI

#include "ai.hpp"

// <<-- Creer-Merge: includes -->> - Code you add between this comment and the end comment will be preserved between Creer re-runs.
// You can add #includes here for your AI.
#include "Chess.h"

// <<-- /Creer-Merge: includes -->>



bool ready = false; //global boolean for whether or not the game has started
                    //needed because game_updated runs once with game not being initialized
                    //and this prevents seg faulting from accessing it too early
                    
GamePiece emptyPiece; //piece with no information, used for returning a piece when an out of 
                      //bounds piece is attempted to be accessed

Team myTeam;  //my team

Team otherTeam;

Board currBoard; //real game board

unsigned int mostHistory=0; //keeps track of how much of the move history I have processed

pos prevEnPassantPos; //store the position of the current turns previous en passant square for use in the next turns enemy move processing

int terminalCount; //max recursion depth for the DFS


bool giveUp;


namespace cpp_client
{

namespace chess
{

/// <summary>
/// This returns your AI's name to the game server.
/// Replace the string name.
/// </summary>
/// <returns>The name of your AI.</returns>
std::string AI::get_name() const
{
    // <<-- Creer-Merge: get-name -->> - Code you add between this comment and the end comment will be preserved between Creer re-runs.
    // REPLACE WITH YOUR TEAM NAME!
    return "Ed Bateman";
    // <<-- /Creer-Merge: get-name -->>
}


double prevTurnTime=0; //stores timeRemaining of last turn

/// <summary>
/// This is automatically called when the game first starts, once the game objects are created
/// </summary>
void AI::start()
{
    // <<-- Creer-Merge: start -->> - Code you add between this comment and the end comment will be preserved between Creer re-runs.
    // This is a good place to initialize any variables        
    srand(time(NULL)); //seed rand
    prevTurnTime = player->time_remaining;
    //terminalCount = 5; //use 5 recursion depth
    
    giveUp=false;
    
    cout << "I am the " << player->color << " team\n" << endl;
    if (player->color=="white") 
    {
      myTeam=White; 
      otherTeam=Black;
    }
    else 
    {
      myTeam=Black;                        //set my team's color
      otherTeam=White;
    }    
    
    ready=true;    //game_updated can now access game
    currBoard = parseFen(game->fen); //initialize board
    
    //currBoard = parseFen("8/4k3/4p3/3P4/8/8/8/4K3 w - - 0 1");    
    
    currBoard.printBoard(0);   

    //currBoard.getPiece(3,5).setMoved(true);
    
    
    
    // <<-- /Creer-Merge: start -->>
}

/// <summary>
/// This is automatically called the game (or anything in it) updates
/// </summary>






void AI::game_updated()
{
    // <<-- Creer-Merge: game-updated -->> - Code you add between this comment and the end comment will be preserved between Creer re-runs.
    // If a function you call triggers an update this will be called before it returns.    
    if (ready) //only do something once AI::start has ran, otherwise it will seg fault because game is uninitialized
    {
      if (game->history.size()>mostHistory) //there is a move to make
      {
        mostHistory=game->history.size();
        
        gameMove m;
        m.start.x = int(game->history[mostHistory-1][0]-'a');
        m.start.y = int(game->history[mostHistory-1][1]-'1');
        
        m.end.x = int(game->history[mostHistory-1][2]-'a');
        m.end.y = int(game->history[mostHistory-1][3]-'1'); //read in the move
        
        if (game->history[mostHistory-1].size()>4) //it is a promotional move
        {          
          currBoard.getPiece(m.start.x, m.start.y).setType(char2PieceType(game->history[mostHistory-1][4]));  //update pieces type to specified type                           
                    
          switch(char2PieceType(game->history[mostHistory-1][4]))
          {
            case Rook:
              if (currBoard.getPiece(m.start.x, m.start.y).getTeam()==White)
              {
                currBoard.whitePoints+=40;
              }
              else
              {
                currBoard.blackPoints+=40;
              }
              break;
            case Knight:
              if (currBoard.getPiece(m.start.x, m.start.y).getTeam()==White)
              {
                currBoard.whitePoints+=20;
              }
              else
              {
                currBoard.blackPoints+=20;
              }
              break;
            case Bishop:
              if (currBoard.getPiece(m.start.x, m.start.y).getTeam()==White)
              {
                currBoard.whitePoints+=20;
              }
              else
              {
                currBoard.blackPoints+=20;
              }
              break;
            case Queen:
              if (currBoard.getPiece(m.start.x, m.start.y).getTeam()==White)
              {
                currBoard.whitePoints+=80;
              }
              else
              {
                currBoard.blackPoints+=80;
              }
              break;  
            default: //not possible to promote to king or pawn
              break;              
          }
          
        }
        
        //if end space is the en passant space and the moved piece is a pawn, set m.enPassantMove true      
        
        if (currBoard.getPiece(m.start.x, m.start.y).getType()==Pawn && m.end.x==prevEnPassantPos.x && m.end.y==prevEnPassantPos.y)
        {
          m.enPassantMove=true;
        }
             
        if (currBoard.getPiece(m.start.x,m.start.y).getTeam()==myTeam)
        {
          cout << "\t\tI played: ";
        }
        else
        {
          cout << "\t\tThey played: ";
        }        
        cout << char(m.start.x+'a') << char(m.start.y+'1') << char(m.end.x+'a') << char(m.end.y+'1') << endl;;
        currBoard.procMove(m);       //process the move
        prevEnPassantPos = getEnPassantPos(game->fen); //update the en passant location
        currBoard.printBoard(0);
        //currBoard.enPassantPos = prevEnPassantPos;
      }
    }
    
    //give up if my team only has a king, and less than 3 pieces (not including king)
    
    if (!giveUp)
    {
      int myOtherPiecesCount = 0;      
      int myPawns = 0;
      
      int enemyOtherPiecesCount = 0;      
      int enemyPawns = 0;
      
      for (int j=0; j<8; j++)
      {
        for (int i=0; i<8; i++)
        {
          if (currBoard.getPiece(i,j).isActive())
          {
            
            if (currBoard.getPiece(i,j).getTeam() == myTeam)
            {            
              if (currBoard.getPiece(i,j).getType() == Pawn)
              {
                myPawns++;
              }
              else
              {
                myOtherPiecesCount++;
              }          
            }
            else
            {
              if (currBoard.getPiece(i,j).getType() == Pawn)
              {
                enemyPawns++;
              }
              else
              {
                enemyOtherPiecesCount++;
              }          
            }
          }        
        }
      }      
      if (myPawns < 4)
      {
        if ((myPawns/2) + myOtherPiecesCount < 4)
        {
          if ((myPawns + myOtherPiecesCount) < (enemyPawns + enemyOtherPiecesCount))
          {
            cout << "Stalemate is an acceptable outcome now" << endl;
            giveUp = true; //try to force a stalemate
          }
        }
      }
    }
    
    
    
    // <<-- /Creer-Merge: game-updated -->>
}

/// <summary>
/// This is automatically called when the game ends.
/// </summary>
/// <param name="won">true if you won, false otherwise</param>
/// <param name="reason">An explanation for why you either won or lost</param>
void AI::ended(bool won, const std::string& reason)
{
  
    //<<-- Creer-Merge: ended -->> - Code you add between this comment and the end comment will be preserved between Creer re-runs.
    // You can do any cleanup of your AI here.  The program ends when this function returns.
    
    cout << "Final board:" << endl;
    currBoard.printBoard(0);
    
    //<<-- /Creer-Merge: ended -->>
}

/// <summary>
/// This is called every time it is this AI.player's turn to make a move.
/// </summary>
/// <returns>A string in Universal Chess Inferface (UCI) or Standard Algebraic Notation (SAN) formatting for the move you want to make. If the move is invalid or not properly formatted you will lose the game.</returns>




std::string AI::make_move()
{
    // <<-- Creer-Merge: makeMove -->> - Code you add between this comment and the end comment will be preserved between Creer re-runs.
    // Put your game logic here for make_move here
    // <<-- /Creer-Merge: makeMove -->>
    
    
    //currBoard.printBoard(0);
    
    
    auto beginningTime = std::chrono::steady_clock::now();
    
    double timeDiff = prevTurnTime - player->time_remaining;
    
    //print remaining time
    if ((player->time_remaining/1000000000) > 60)
    {
      cout << "I have " << (player->time_remaining/1000000000)/60 << " minutes remaining" << endl;
    }
    else
    {
      cout << "I have " << (player->time_remaining/1000000000) << " seconds remaining" << endl;
    }
    //print previous time taken
    cout << "Previous turn took " << (timeDiff/1000000000) << " seconds" << endl;
    
    prevTurnTime = player->time_remaining;
    
    
    float percentAllowed=5; //normally allow 5% of remaining time for this move
    if (currBoard.moves<10)
    {
      percentAllowed = 1; //dont spend too much time thinking about the first moves since they are pretty deadset anyways
    }
    else if ((player->time_remaining/1000000000) < 30) //if less than 30 seconds left, only allow .8% of remaining time
    {
      percentAllowed=0.8;
    }
    else if ((player->time_remaining/1000000000) < 3*60) //if less than 3 minutes left, only allow 2% of remaining time
    {
      percentAllowed=2;
    }    
    
    //percentAllowed /= 5.0;
    
    double allowedTime = (player->time_remaining/1000000000) * (percentAllowed/100.0);
    
    cout << "I get " << allowedTime << " seconds to take my turn" << endl;
    
    
    
    int i=1; //begin at depth 1
    
    gameMove best; 
    best.start.x=0;
    best.start.y=0;
    best.end.x=0;
    best.end.y=0; //initialize to garbage to stop warnings
    
    gameMove newBest;
    
    std::chrono::duration<double> lastElapsed_seconds; //the time it took to do the previous iteration
    
    std::chrono::duration<double> elapsed_seconds; //the time it took to do this iteration
        
    vector<double> times = vector<double>();
        
    double remaining = 1; //time remaining in this turn
    do
    {
      terminalCount = i; //update recursion depth for minimax
      i++; //increment counter
      
      auto start = std::chrono::steady_clock::now(); //time at start of alg
      newBest = currBoard.maxChoice(currBoard, myTeam, beginningTime, allowedTime, best); //get best move
      auto end = std::chrono::steady_clock::now(); //time at end of alg
      elapsed_seconds = end-start;
      //cout << "elapsed time: " << elapsed_seconds.count() << "s" << endl;
      
      remaining = remainingTurnTime(beginningTime, allowedTime); //remaining time
      
      if (remaining<0 && i>2) break; //ran out of time, dont bother using the incomplete newBest
                                     //if i==1 and times up, then update anyways cuz its the only thing to go off of
      
      best = newBest; //if we didn't run out of time, update best move
      times.push_back(elapsed_seconds.count());
      if (i>2) //only bother with ratio stuff if this is the second iteration or higher, otherwise we'd be dividing by zero
      {        
       
        double nextTime = calculateNextTime(times);
        //cout << "Estimated next iteration: " << nextTime << endl;
       
        if (remaining - nextTime < 0) //likely wont finish the next iteration
        {
          //cout << "Stopping early because next iteration unlikely to finish" << endl;
          break;
        }       
      }
      
      //cout << "Still have " << remaining << " seconds" << endl;               
      
      
    } while (remaining>0 && i<=20); // i<20 because i run out of memory at around i=26
    
    
    
    //return "";
    stringstream s;
    
    s << char(best.start.x+'a') << char(best.start.y+'1') << char(best.end.x+'a') << char(best.end.y+'1');
    string o;    //run characters of movement into stringstream then convert to string and return
    s >> o;            
    cout << endl;
    
    return o;    
}

//<<-- Creer-Merge: methods -->> - Code you add between this comment and the end comment will be preserved between Creer re-runs.
// You can add additional methods here for your AI to call
//<<-- /Creer-Merge: methods -->>

} // chess

} // cpp_client
