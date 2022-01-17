#include <vector>
#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;


struct mov
{
public:
  int start;
  int finish;
};


//keep a vector of winning games
vector<vector<mov>> solutions[15];

//also keep a vector of the worst games
vector<vector<mov>> worstGames[15];
int worstGame=1;

long totalSolutions=0;
long totalGames=0;

//whether or not a peg slot is capable of jumping to another                    
bool canJump[15][15] = {{0,0,0,1,0,1,0,0,0,0,0,0,0,0,0},
                        {0,0,0,0,0,0,1,0,1,0,0,0,0,0,0},
                        {0,0,0,0,0,0,0,1,0,1,0,0,0,0,0},
                        {1,0,0,0,0,1,0,0,0,0,1,0,1,0,0},
                        {0,0,0,0,0,0,0,0,0,0,0,1,0,1,0},
                        {1,0,0,1,0,0,0,0,0,0,0,0,1,0,1},
                        {0,1,0,0,0,0,0,0,1,0,0,0,0,0,0},
                        {0,0,1,0,0,0,0,0,0,1,0,0,0,0,0},
                        {0,1,0,0,0,0,1,0,0,0,0,0,0,0,0},
                        {0,0,1,0,0,0,0,1,0,0,0,0,0,0,0},
                        {0,0,0,1,0,0,0,0,0,0,0,0,1,0,0},
                        {0,0,0,0,1,0,0,0,0,0,0,0,0,1,0},
                        {0,0,0,1,0,1,0,0,0,0,1,0,0,0,1},
                        {0,0,0,0,1,0,0,0,0,0,0,1,0,0,0},
                        {0,0,0,0,0,1,0,0,0,0,0,0,1,0,0}};

//counts how many pegs remain in the list
int count(bool *pegs)
{
  int cnt=0;
  for (int i=0; i<15; i++)
  {
    if (pegs[i]==1) cnt++;
  }
  return cnt;
}

bool cannotMove(bool *pegs)
{
  for (int p=0; p<15; p++)
  {
    for (int choice=0; choice<15; choice++)
    {
      if (canJump[p][choice]!=0 && pegs[p]==1 && pegs[choice]==0 && pegs[(p+choice)/2]==1)
      {
        return false;
      }
    }
  }
  return true;
}


int pegN=0; //used to keep track of the starting peg for the current run

//uses recursive backtracking to simulate every possible move in peg game
void peg(bool* pegs, vector<mov> moves)
{
  for (int p=0; p<15; p++) //try every peg
  {
    for (int choice=0; choice<15; choice++) //try jumping to every other peg
    {
      if (canJump[p][choice]!=0 && pegs[p]==1 && pegs[choice]==0 && pegs[(p+choice)/2]==1) //if this is a valid move
      {
        pegs[p]=0; //remove the peg from the jumping slot
        pegs[choice]=1; //set the slot its jumping into
        pegs[(p+choice)/2]=0; //remove the jumped piece (which so happens to always be the average of the two pegs, rounded down)
        mov newMove;
        newMove.start=p;
        newMove.finish=choice;
        moves.push_back(newMove); //add this move to the list
        
        if (count(pegs)==1) //did we win?
        {
          totalGames++; 
          totalSolutions++;
          solutions[pegN].push_back(moves); //add list of moves to the list of solutions
          
          moves.pop_back(); //backtrack to find more solutions, undo previous move
          pegs[p]=1; 
          pegs[choice]=0;
          pegs[(p+choice)/2]=1;
        }
        else //not a winner, keep going
        {
          peg(pegs, moves); //recursively call peg function
          
         if (cannotMove(pegs)) //if this move makes it impossible to move anything, this is a loser
         {
            totalGames++;
            if (count(pegs)>worstGame) //current worst game
            {
              worstGame=count(pegs); //overwrite previous worst games
              
              for (int d=0; d<15; d++)
              {
                worstGames[d].clear();
              }
              
              worstGames[pegN].push_back(moves); //add to list
            }
            else if ((count(pegs)==worstGame)) //if this game ties for the worst, add it to the list of worst games
            {
               worstGames[pegN].push_back(moves);
            }
         }                              
          //backtrack
          pegs[p]=1;
          pegs[choice]=0;
          pegs[(p+choice)/2]=1;
          moves.pop_back();
        }
      }
    }
  }
  //no solution found
  return;
}

int main()
{ 
  bool pegs[15]; //the 15 pegs to use
  for (int i=0; i<15; i++) //try starting with each hole as the initial empty hole
  {
    for (int j=0; j<15; j++) pegs[j]=1; //fill all holes
    pegs[i]=0; //remove the initial hole
    
    vector<mov> m; //make new empty list to pass to function
    pegN=i; //starting hole
    peg(pegs, m); //find solutions    
  }
  
  //Print stats
  
  cout << "Number of solutions:" << endl;
  for (int i=0; i<15;i++)
  {    
    cout << "For starting hole #" <<i << ": " << solutions[i].size() << endl;
  }
  cout << endl; 
  
  cout << "Total possible finished games: " << totalGames << endl << endl;
  cout << "Total possible won games: " << totalSolutions << endl << endl;
  cout << "Worst Score Possible: ";
  cout << worstGame << " pegs left" << endl << endl;
  
  //Show how to get the worst score possible
  cout << "Worst games:" << endl << endl; 
  
  for (int i=0; i<15;i++)
  {    
    if (worstGames[i].size()>0)
    {
      cout << "Starting hole: " << i << endl << endl;     
      
      for (int game = 0; game < worstGames[i].size(); game++)
      {
        cout << "Game " << (game+1) << ":" << endl;
        for (auto h : worstGames[i][game])
        {
          cout << h.start << ":" << h.finish << endl;
        }
        cout << endl;      
      }
    }
  }
  cout << endl; 
  
  //Print random solutions to the game as long as user keeps entering text input
  
  srand(time(0)); //seed random number generator  
  
  cout << "Solutions:" << endl << endl; 
  
  cout << "Type anything to print out random solutions" << endl;
  cout << "Type 'q' to quit" << endl;
  string q;
  while (true)
  {   
    cin >> q;   
    
    int l= rand() % 15; //get random starting peg
    int c = rand() % solutions[l].size(); //get random solution index
    
    if (q=="q") break; //quit if user typed 'q'
    
    cout << endl << "Solution #" << c << ", starting with hole #" << l << " empty"<< endl;  
  
    for (auto m : solutions[l][c])
    {
      cout << "Hole " << m.start << " to hole " << m.finish << endl;
    }
    cout << endl << endl;
  }
  
  return 0;
}
