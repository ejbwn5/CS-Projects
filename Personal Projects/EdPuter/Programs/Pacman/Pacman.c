int multx, multy, multtemp, multacc; //variables for multiplication function

int N,D; //variables for division function
int Q,R;

int a,b,c,d; //multipurpose variables

int col; //color for draw functions
int drawX,drawY,drawPos,drawAddr; //variables for draw functions

int pacmanMouth; // determines when mouth should open and close

int pacmanDir; //facing direction

int temp;
int addr;
int x,y,dx,dy;


int redTarg[2]; //x,y target vectors for the ghosts
int blueTarg[2];
int pinkTarg[2];
int orangeTarg[2];

int redPos[2]; //x,y position vectors for the ghosts
int bluePos[2];
int pinkPos[2];
int orangePos[2];

int redDir; //moving direction for the ghosts
int blueDir;
int pinkDir;
int orangeDir;

int dirForOpp;
int dist;
int e,f;

const houseExitX=49; //position of the spawn point for the ghosts
const houseExitY=30;

const maxInt = 65535;

//array of all of the VRAM addresses for the dots
const int dotsPos[1] = {1046, 1049, 1052, 1055, 1058, 1061, 1064, 1067, 1070, 1076, 1079, 1082, 1085, 1088, 1091, 1094, 1097, 1100, 1442, 1454, 1460, 1472, 1814, 1826, 1838, 1844, 1856, 1868, 2198, 2201, 2204, 2207, 2210, 2213, 2216, 2219, 2222, 2225, 2228, 2231, 2234, 2237, 2240, 2243, 2246, 2249, 2252, 2582, 2594, 2600, 2618, 2624, 2636, 2966, 2969, 2972, 2975, 2978, 2984, 2987, 2990, 2996, 2999, 3002, 3008, 3011, 3014, 3017, 3020, 3362, 3392, 3746, 3776, 4130, 4160, 4514, 4544, 4898, 4928, 5282, 5312, 5666, 5696, 6038, 6041, 6044, 6047, 6050, 6053, 6056, 6059, 6062, 6068, 6071, 6074, 6077, 6080, 6083, 6086, 6089, 6092, 6422, 6434, 6446, 6452, 6464, 6476, 6809, 6818, 6821, 6824, 6827, 6830, 6836, 6839, 6842, 6845, 6848, 6857, 7193, 7202, 7208, 7226, 7232, 7241, 7574, 7577, 7580, 7583, 7586, 7592, 7595, 7598, 7604, 7607, 7610, 7616, 7619, 7622, 7625, 7628, 7958, 7982, 7988, 8012, 8342, 8345, 8348, 8351, 8354, 8357, 8360, 8363, 8366, 8369, 8372, 8375, 8378, 8381, 8384, 8387, 8390, 8393, 8396};

//array of booleans for whether or not a dot has been eaten
int dotExist[164];


//a list of rectangles to draw the map
//startx, starty, endx, endy, color
const int map[1] = {19,5,61,64,2,
                    20,6,59,62,3,
                    21,7,27,3,0,
                    21,10,3,15,0,
                    24,16,54,3,0,
                    51,7,27,3,0,
                    33,10,3,6,0,
                    45,10,3,6,0,
                    51,10,3,6,0,
                    63,10,3,6,0,
                    75,10,3,15,0,
                    33,19,3,42,0,
                    24,22,9,3,0,
                    39,19,3,6,0,
                    42,22,6,3,0,
                    51,22,9,3,0,
                    57,19,3,3,0,
                    63,19,3,42,0,
                    66,22,9,3,0,
                    60,34,20,3,0,
                    19,27,12,5,0,
                    19,34,20,3,0,
                    39,28,21,3,0,
                    45,25,3,3,0,
                    51,25,3,3,0,
                    39,31,3,15,0,
                    57,31,3,15,0,
                    43,32,13,7,2,
                    44,33,11,5,0,
                    42,40,15,3,0,
                    19,39,12,5,0,
                    68,27,12,5,0,
                    68,39,12,5,0,
                    21,46,27,3,0,
                    51,46,27,3,0,
                    36,52,27,3,0,
                    21,49,3,6,0,
                    24,52,3,6,0,
                    21,58,12,3,0,
                    21,61,3,3,0,
                    21,64,57,3,0,
                    39,55,3,6,0,
                    42,58,6,3,0,
                    45,61,3,3,0,
                    51,58,3,6,0,
                    54,58,6,3,0,
                    57,55,3,3,0,
                    45,49,3,3,0,
                    51,49,3,3,0,
                    66,58,12,3,0,
                    75,49,3,6,0,
                    72,52,3,6,0,
                    75,61,3,3,0,
                    20,38,12,1,2,
                    31,39,1,6,2,
                    20,44,11,1,2,
                    20,26,12,1,2,
                    31,27,1,6,2,
                    20,32,11,1,2,
                    20,56,3,1,2,
                    76,56,3,1,2,
                    67,44,12,1,2,
                    67,38,1,6,2,
                    68,38,11,1,2,
                    67,32,12,1,2,
                    67,26,1,6,2,
                    68,26,11,1,2,
                    49,6,1,9,2,
                    48,31,3,2,20,
                    25,11,7,4,2,
                    37,11,7,4,2,
                    55,11,7,4,2,
                    67,11,7,4,2,
                    25,20,7,1,2,
                    67,20,7,1,2,
                    43,20,13,1,2,
                    49,21,1,6,2,
                    37,20,1,13,2,
                    38,26,6,1,2,
                    55,26,6,1,2,
                    61,20,1,13,2,
                    37,38,1,7,2,
                    61,38,1,7,2,
                    43,44,13,1,2,
                    49,45,1,6,2,
                    25,50,3,1,2,
                    28,50,4,7,2,
                    37,50,7,1,2,
                    55,50,7,1,2,
                    67,50,4,7,2,
                    71,50,3,1,2,
                    25,62,19,1,2,
                    37,56,1,6,2,
                    43,56,13,1,2,
                    49,57,1,6,2,
                    55,62,19,1,2,
                    61,56,1,6,2};
                    
//list of rectangles which define legal x,y positions to be on
//startx, starty, dx, dy  
const int legalSpaces[1] = {22,65,55,1,
                            23,17,54,1,
                            34,9,1,51,
                            22,8,25,1,
                            22,9,1,15,
                            64,8,1,52,
                            22,47,25,1,
                            52,47,25,1,
                            20,35,21,1,
                            58,35,21,1,
                            52,8,25,1,
                            76,9,1,15,
                            23,23,11,1,
                            65,23,11,1,
                            46,9,1,8,
                            52,9,1,8,
                            40,18,1,6,
                            58,18,1,6,
                            41,23,6,1,
                            52,23,6,1,
                            46,24,1,5,
                            52,24,1,5,
                            40,29,19,1,
                            40,30,1,17,
                            58,30,1,17,
                            41,41,17,1,
                            35,53,29,1,
                            46,48,1,5,
                            52,48,1,5,
                            22,48,1,6,
                            76,48,1,6,
                            23,53,3,1,
                            73,53,3,1,
                            22,59,12,1,
                            65,59,12,1,
                            25,54,1,5,
                            40,54,1,5,
                            58,54,1,5,
                            73,54,1,5,
                            40,59,7,1,
                            52,59,7,1,
                            22,60,1,5,
                            46,60,1,5,
                            52,60,1,5,
                            76,60,1,5};   

//bitmap for numbers                            
const int numZero[1] =  {0, 3, 3, 2, 0, 3, 0, 0, 3, 0, 3, 0, 0, 3, 1, 3, 0, 0, 3, 1, 3, 0, 0, 3, 1, 3, 2, 2, 3, 0, 0, 3, 3, 1, 0};
const int numOne[1] =   {0, 0, 2, 2, 0, 1, 3, 2, 1, 2, 2, 2, 0, 0, 2, 2, 0, 0, 2, 2, 0, 0, 2, 2, 0, 0, 2, 2};
const int numTwo[1] =   {0, 1, 3, 2, 1, 1, 3, 1, 1, 2, 0, 0, 0, 1, 2, 0, 0, 1, 3, 1, 0, 1, 3, 2, 0, 0, 2, 2, 0, 0, 1, 3, 3, 3, 2};
const int numThree[1] = {0, 3, 3, 0, 3, 2, 2, 3, 0, 0, 2, 3, 0, 3, 3, 2, 0, 0, 2, 3, 3, 1, 2, 3, 0, 3, 3, 0};
const int numFour[1] =  {0, 0, 0, 3, 0, 0, 0, 2, 3, 1, 0, 0, 3, 3, 1, 0, 2, 2, 3, 1, 0, 3, 0, 3, 1, 2, 3, 3, 3, 3, 0, 0, 0, 3, 0};
const int numFive[1] =  {0, 3, 3, 3, 0, 2, 3, 0, 0, 0, 2, 3, 3, 2, 0, 0, 0, 1, 3, 1, 0, 0, 0, 3, 2, 3, 2, 0, 3, 1, 0, 3, 3, 2, 0};
const int numSix[1] =   {0, 2, 3, 2, 0, 1, 3, 0, 3, 0, 2, 3, 0, 0, 0, 2, 3, 3, 3, 0, 2, 3, 0, 3, 2, 1, 3, 0, 3, 2, 0, 2, 3, 3, 0};
const int numSeven[1] = {2, 3, 3, 3, 2, 0, 0, 0, 3, 1, 0, 0, 1, 3, 0, 0, 0, 3, 2, 0, 0, 1, 3, 0, 0, 0, 2, 3, 0, 0, 0, 2, 3, 0, 0};
const int numEight[1] = {0, 2, 3, 3, 0, 1, 3, 0, 2, 3, 1, 3, 0, 2, 3, 0, 2, 3, 3, 0, 1, 3, 0, 2, 3, 1, 3, 0, 2, 3, 0, 2, 3, 3, 0};
const int numNine[1] =  {0, 3, 3, 0, 3, 0, 2, 3, 3, 0, 2, 3, 0, 3, 3, 3, 0, 0, 1, 3, 3, 1, 2, 3, 0, 3, 3, 0};


const eightNinetySix = 896; //this number shows up occasionally and would be less efficient to calculate multiple times,
                            //and is too big of a number to fit in an argument, so make it a const
                            
const randAdd = 457;

int rand; //random number
int io; //io input
int eaten; //how many dots eaten
int score;
int num2Draw; //used by number drawing functions
int padNumWith1Zeroes; //boolean to tell number drawing function to have leading zeroes

int playerX,playerY; //player position

int blueReleased; //boolean for if these ghosts should be released
int orangeReleased;

int up,dn,lf,rt; //booleans for if a direction was input via IO

int lastDir; //0 is none, 1 up, 2 right, 3 down, 4 left
int moved;

int testX,testY,testAddr;

int ghostMode; //0 is scatter, 1 is chase, 2 is frightened

const timeMultiplier=105;
const timeMultiplier2=75;
const timeMultiplier3=300;

int frameCounter;

int stage; //0, scatter 7 seconds, chase 20
             //1, scatter 7, chase 20
             //2, scatter 5, chase 20
             //3, scatter 5, chase forever

             
             
int main()
{ 
  //initialize player and ghost variables

  ghostMode=0;
  stage=0;
  playerX=49;
  playerY=53;
  lastDir=0;
  pacmanMouth=0;
  frameCounter=0;
  
  redDir=3;
  blueDir=3;
  pinkDir=3;
  orangeDir=3;
  
  redPos[0]=49;
  redPos[1]=29;
  
  pinkPos[0]=49;
  pinkPos[1]=35;
  
  bluePos[0]=45;
  bluePos[1]=35;
  
  orangePos[0]=53;
  orangePos[1]=35;
  
  calcRedTarget();
  calcPinkTarget();
  calcBlueTarget();
  calcOrangeTarget();
  
  blueReleased=0;
  orangeReleased=0;
  
  x=0;
  while (x<164) // initialize all dots to existing
  {
    dotExist[x]=1;
    x=x+1;
  }
  eaten=0;
  score=0;
  
  pacmanDir=0; //0 is none, 1 up, 2 right, 3 down, 4 left
  
  
  
  
  
  drawMap();
    
  drawDots();
  
  x=redPos[0];
  y=redPos[1];
  col=48;
  drawGhost();
  
  x=bluePos[0];
  y=bluePos[1];
  col=15;
  drawGhost();
  
  x=pinkPos[0];
  y=pinkPos[1];
  col=59;
  drawGhost();
  
  x=orangePos[0];
  y=orangePos[1];
  col=52;
  drawGhost();
  
  drawPlayer();
  
  
  //draw score
  
  drawX=95;
  drawY=0;
  col=20;
  padNumWith1Zeroes=1;
  num2Draw=score;
  drawNum(); 
  flip;  
  
  //wait for input
  
  ioin(io);
  
  while (io==0) 
  {
    ioin(io);
  }
  
  
  while (1)
  {    

    //check input
    //clearScreen();
    
    
    x=65;
    y=0;
    dx=35;
    dy=7;
    col=0;
    drawRect(); //wipe score
    
    
    //see if dot should be eaten
    multx=128;
    multy=playerY;
    addr = mult()+playerX;
    
    x=0;
    while (x<164)
    {
      if (dotExist[x]) //check every dot
      {
        if (dotsPos[x]==addr)
        {        
          //pacman on dot
          dotExist[x]=0;
          eaten=eaten+1;
          score=score+1;
          goto dotCheckExit; //quit out early since only one dot can every be eaten at once
        }
      }
      x=x+1;
    }
    dotCheckExit:
    
    moved=0;
    
    refreshInput();
    testX=playerX; //test if squares in direction trying to move in are valid
    testY=playerY;
    if (up)
    {
      tryUp:
      testY=testY-1;
      if (isValidSpace())
      {
        playerY=playerY-1;
        lastDir=1;
        moved=1;
        pacmanDir=1;
      }
    }
    if (moved==0)
    {
      testX=playerX;
      testY=playerY;
      
      if (dn)
      {
        tryDn:
        testY=testY+1;
        if (isValidSpace())
        {
          playerY=playerY+1;
          lastDir=3;
          moved=1;
          pacmanDir=3;
        }
      }
    }
    if (moved==0)
    {
      testX=playerX;
      testY=playerY;
      if (rt)
      {
        tryRt:
        testX=testX+1;
        if (isValidSpace())
        {
          playerX=playerX+1;
          lastDir=2;
          moved=1;
          pacmanDir=2;
        }
      }
    }
    if (moved==0)
    {
      testX=playerX;
      testY=playerY;
      if (lf)
      {
        tryLf:
        testX=testX-1;
        if (isValidSpace())
        {
          playerX=playerX-1;
          lastDir=4;
          moved=1;
          pacmanDir=4;
        }
      }    
    }
    
   
    //no moves            
    if (moved==0)
    {
      if (lastDir!=0)
      {
        //try lastDir
        testX=playerX;
        testY=playerY;
        up=1; //to skip next time
        
        if (lastDir==1)
        {
          //up
          lastDir=0;
          goto tryUp; 
        }
        if(lastDir==2)
        {
          lastDir=0;
          goto tryRt;
        }
        if (lastDir==3)
        {
          lastDir=0;
          goto tryDn;
        }
        lastDir=0;
        goto tryLf;              
      }
    }    
    
    
    
    
    //do tunnel
    
    //check if the player or any ghosts are at the tunnel warp points
    if (redPos[0]==20)
    {
      //wrap to right
      redPos[0] = 78; 
    }
    else
    {
      if (redPos[0]==78)
      {
        //wrap to right
        redPos[0] = 20; 
      }
    }
    
    if (bluePos[0]==20)
    {
      //wrap to right
      bluePos[0] = 78; 
    }
    else
    {
      if (bluePos[0]==78)
      {
        //wrap to right
        bluePos[0] = 20; 
      }
    }
    
    if (orangePos[0]==20)
    {
      //wrap to right
      orangePos[0] = 78; 
    }
    else
    {
      if (orangePos[0]==78)
      {
        //wrap to right
        orangePos[0] = 20; 
      }
    }
    
    if (pinkPos[0]==20)
    {
      //wrap to right
      pinkPos[0] = 78; 
    }
    else
    {
      if (pinkPos[0]==78)
      {
        //wrap to right
        pinkPos[0] = 20; 
      }
    }
    
    if (playerX==20)
    {
      //wrap to right
      playerX = 78; 
    }
    else
    {
      if (playerX==78)
      {
        //wrap to right
        playerX = 20; 
      }
    }
    
    
    //see if ghost is capable of turning
    
  
      dist = maxInt;
      
      //check for smaller distances
      
      dirForOpp = redDir;
      dirForOpp = getOppositeDir();
      
      
      
      e=0;
      while (e<4)
      {          
        //try every dir
        if (e!=dirForOpp)
        {
          //valid dir
          testX=redPos[0];
          testY=redPos[1];
          
          if (e==0)
          {
            //up
            testY=testY-1;
          }
          else
          {
            if (e==1)
            {
              //right
              testX=testX+1;
            }
            else
            {
              if (e==2)
              {
                //down
                testY=testY+1;
              }
              else
              {
                //left
                testX=testX-1;
              }
            }
          }
          
          if (isValidSpace())
          {            
            //valid direction to turn, see if distance to target is better
            if (e!=redDir)
              calcRedTarget();
            
            a=testX;
            c=redTarg[0];
            b=testY;
            d=redTarg[1];
            
            temp=getDist();
            
            if (temp<dist)
            {
              dist=temp;
              redDir=e;
            }                
          }
        }
        e=e+1;
      }
      
      dist = maxInt;
      
      //check for smaller distances
      
      dirForOpp = pinkDir;
      dirForOpp = getOppositeDir();
      
      
      
      e=0;
      while (e<4)
      {          
       
        
        //try every dir
        if (e!=dirForOpp)
        {
          //valid dir
          testX=pinkPos[0];
          testY=pinkPos[1];
          
          if (e==0)
          {
            //up
            testY=testY-1;
          }
          else
          {
            if (e==1)
            {
              //right
              testX=testX+1;
            }
            else
            {
              if (e==2)
              {
                //down
                testY=testY+1;
              }
              else
              {
                //left
                testX=testX-1;
              }
            }
          }
          
          if (isValidSpace())
          {
            if (e!=pinkDir)
              calcPinkTarget();
            
            
            
            //valid direction to turn, see if distance to target is better
            
            a=testX;
            c=pinkTarg[0];
            b=testY;
            d=pinkTarg[1];
            
            temp=getDist();
            
            if (temp<dist)
            {
              dist=temp;
              pinkDir=e;
            }                
          }
        }
        e=e+1;
      }

      //blue
            
      
      dist = maxInt;
      
      //check for smaller distances
      
      dirForOpp = blueDir;
      dirForOpp = getOppositeDir();
      
      
      
      e=0;
      while (e<4)
      {          
       
        
        //try every dir
        if (e!=dirForOpp)
        {
          //valid dir
          testX=bluePos[0];
          testY=bluePos[1];
          
          if (e==0)
          {
            //up
            testY=testY-1;
          }
          else
          {
            if (e==1)
            {
              //right
              testX=testX+1;
            }
            else
            {
              if (e==2)
              {
                //down
                testY=testY+1;
              }
              else
              {
                //left
                testX=testX-1;
              }
            }
          }
          
          if (isValidSpace())
          {
            
            if (e!=blueDir)
              calcBlueTarget();
            
            
            //valid direction to turn, see if distance to target is better
            
            a=testX;
            c=blueTarg[0];
            b=testY;
            d=blueTarg[1];
            
            temp=getDist();
            
            if (temp<dist)
            {
              dist=temp;
              blueDir=e;
            }                
          }
        }
        e=e+1;
      }
      
 
      
      dist = maxInt;
      
      //check for smaller distances
      
      dirForOpp = orangeDir;
      dirForOpp = getOppositeDir();
      
            
            
      e=0;
      while (e<4)
      {          
       
        
        //try every dir
        if (e!=dirForOpp)
        {
          //valid dir
          testX=orangePos[0];
          testY=orangePos[1];
          
          if (e==0)
          {
            //up
            testY=testY-1;
          }
          else
          {
            if (e==1)
            {
              //right
              testX=testX+1;
            }
            else
            {
              if (e==2)
              {
                //down
                testY=testY+1;
              }
              else
              {
                //left
                testX=testX-1;
              }
            }
          }
          
          if (isValidSpace())
          {
            if (e!=orangeDir)
              calcOrangeTarget();
            //valid direction to turn, see if distance to target is better
            
            a=testX;
            c=orangeTarg[0];
            b=testY;
            d=orangeTarg[1];
            
            temp=getDist();
            
            if (temp<dist)
            {
              dist=temp;
              orangeDir=e;
            }                
          }
        }
        e=e+1;
      }
         
    
    //move ghosts
    
    //red
    testX=redPos[0];
    testY=redPos[1];
    
    if (redDir==0)
    {
      //up
      testY=testY-1;
    }
    else
    {
      if (redDir==1)
      {
        //right
        testX=testX+1;
      }
      else
      {
        if (redDir==2)
        {
          //down
          testY=testY+1;
        }
        else
        {
          //left
          testX=testX-1;
        }
      }
    }
    
    if (isValidSpace())
    {
      redPos[0] = testX;
      redPos[1] = testY;
    }
    
    //blue
    testX=bluePos[0];
    testY=bluePos[1];
    
    if (blueDir==0)
    {
      //up
      testY=testY-1;
    }
    else
    {
      if (blueDir==1)
      {
        //right
        testX=testX+1;
      }
      else
      {
        if (blueDir==2)
        {
          //down
          testY=testY+1;
        }
        else
        {
          //left
          testX=testX-1;
        }
      }
    }
    
    if (isValidSpace())
    {
      bluePos[0] = testX;
      bluePos[1] = testY;
    }
    
    
    //pink
    testX=pinkPos[0];
    testY=pinkPos[1];
    
    if (pinkDir==0)
    {
      //up
      testY=testY-1;
    }
    else
    {
      if (pinkDir==1)
      {
        //right
        testX=testX+1;
      }
      else
      {
        if (pinkDir==2)
        {
          //down
          testY=testY+1;
        }
        else
        {
          //left
          testX=testX-1;
        }
      }
    }
    
    if (isValidSpace())
    {
      pinkPos[0] = testX;
      pinkPos[1] = testY;
    }
    
    //orange
    testX=orangePos[0];
    testY=orangePos[1];
    
    if (orangeDir==0)
    {
      //up
      testY=testY-1;
    }
    else
    {
      if (orangeDir==1)
      {
        //right
        testX=testX+1;
      }
      else
      {
        if (orangeDir==2)
        {
          //down
          testY=testY+1;
        }
        else
        {
          //left
          testX=testX-1;
        }
      }
    }
    
    if (isValidSpace())
    {
      orangePos[0] = testX;
      orangePos[1] = testY;
    }
    
    
    
    if (blueReleased==0) //check if blue should be released
    {
      if (eaten==20)
      {
        bluePos[0] = houseExitX;
        bluePos[1] = houseExitY;
        blueReleased=1;
      }
    }
    
    if (orangeReleased==0) //check if orange should be released
    {
      if (eaten==55)
      {
        orangePos[0] = houseExitX;
        orangePos[1] = houseExitY;
        orangeReleased=1;
      }
    }
    
    if (ghostMode!=2)
    {
      //dont increment if in panic mode
      frameCounter=frameCounter+1;
      
      if (ghostMode==0)
      {
        if (stage==0)
        {
          if (frameCounter==7) 
          {
            //release pink
            pinkPos[0] = houseExitX;
            pinkPos[1] = houseExitY;
          }
        }
        //we in scatter mode, find out stage
        
        if (stage<2)
        {
          //scatter for 7 seconds
          
          if (frameCounter>timeMultiplier)
          {
            ghostMode=1;  //switch modes
            frameCounter=0;
          }          
        }
        else
        {            
           if (frameCounter>timeMultiplier2)
           {
             ghostMode=1;  //switch modes
             frameCounter=0;
           }
        }
        
      }
      else
      {
        //in chase mode
        if (stage<3)
        {
          
          //only switch back if under stage 4
          if (frameCounter>timeMultiplier3)
          {
             ghostMode=0;  //switch modes
             frameCounter=0;
             stage=stage+1;
          }
        }
      }      
    }
    
    //draw frame
   
    drawMap();
    
    drawDots();
    
    x=redPos[0];
    y=redPos[1];
    col=48;
    drawGhost();
    
    x=bluePos[0];
    y=bluePos[1];
    col=15;
    drawGhost();
    
    x=pinkPos[0];
    y=pinkPos[1];
    col=59;
    drawGhost();
    
    x=orangePos[0];
    y=orangePos[1];
    col=52;
    drawGhost();
    
    drawPlayer();
    
    
    //draw score
    
    drawX=95;
    drawY=0;
    col=20;
    padNumWith1Zeroes=1;
    num2Draw=score;
    drawNum();
        
    //drawTargets();
    
    //drawValidSpaces();
    
    //frame complete, flip vram buffer
    flip;   
    
    
    
    
    
    
    pacmanMouth=pacmanMouth+1;
    if (pacmanMouth>5)
    {
      pacmanMouth=0;
    }
  }
  return 0;
}


void drawDots()
{
  
  x=0;
  while (x<164)
  {
    if (dotExist[x]) 
    {
      //draw dot
      vrammar(dotsPos[x]);
      write(63); 
    }
    x=x+1;
  }
  return(void);
}


/*
void drawTargets()
{
  
  //red
  multx=128;
  multy=redTarg[1];
  addr=mult()+redTarg[0];
  
  vrammar(addr);
  write(48);
  
  //blue
  multx=128;
  multy=blueTarg[1];
  addr=mult()+blueTarg[0];
  
  vrammar(addr);
  write(15);
  
  //pink
  multx=128;
  multy=pinkTarg[1];
  addr=mult()+pinkTarg[0];
  
  vrammar(addr);
  write(55);
  
  
  //orange
  
  multx=128;
  multy=orangeTarg[1];
  addr=mult()+orangeTarg[0];
  
  vrammar(addr);
  write(52);
  
  
}
*/


void drawMap()
{ 
  a=0;
  
  while (a<97)
  {
    
    
    multx=5;
    multy=a;
    
    addr=mult();
    
    x = map[addr];
    addr=addr+1;
    y = map[addr];
    addr=addr+1;
    dx = map[addr];
    addr=addr+1;
    dy = map[addr];
    addr=addr+1;
    col= map[addr];

    drawRect();
    
    a=a+1;
  }
  
  return(void);
}

/*
void drawValidSpaces()
{ 
  a=0;
  col=48;
  while (a<45)
  { 
    multx=4;
    multy=a;
    
    addr=mult();
    
    x = legalSpaces[addr];
    addr=addr+1;
    y = legalSpaces[addr];
    addr=addr+1;
    dx = legalSpaces[addr];
    addr=addr+1;
    dy = legalSpaces[addr];    
    drawRect();    
    a=a+1;
  }
  return(void);
}

*/


int isValidSpace()
{
  
  multx=128;
  multy=testY;
  testAddr=mult()+testX;
  
  a=0;
  col=48;
  while (a<45)
  { 
    multx=4;
    multy=a;
    
    addr=mult();
    
    x = legalSpaces[addr];
    addr=addr+1;
    y = legalSpaces[addr];
    addr=addr+1;
    dx = legalSpaces[addr];
    addr=addr+1;
    dy = legalSpaces[addr];    
        
    multx=y;
    multy=128;
    addr=mult()+x;
    
    c=0;
    while (c<dy)
    {
      b=0;
      while (b<dx)
      {
        if (addr==testAddr)
        {
          return 1;
        }       
        
        addr=addr+1;
        b=b+1;
      }
      addr=addr+128-dx;
      c=c+1;
    }
        
        
    a=a+1;
  }
  return 0;
}



//using x,y,dx,dy,col
void drawRect()
{
  //draw rectangle
    
    multx=y;
    multy=128;
    addr=mult()+x;
    
    c=0;
    while (c<dy)
    {
      b=0;
      while (b<dx)
      {
        
        vrammar(addr);
        write(col);
        
        addr=addr+1;
        b=b+1;
      }
      addr=addr+128-dx;
      c=c+1;
    }
  return(void);
}




void refreshInput()
{
  
  ioin(io);
  
  
  N = io;
  D = 2;
  divide();
  N = Q;
  
  up=0;
  dn=0;
  lf=0;
  rt=0;
  
  if (R==1)
  {    
    //up
    up=1;
  }  
  divide();  
  if (R==1)
  {      
    //rt
    rt=1;
  }
  N = Q;
  divide();    
  if (R==1)
  {      
    //dn
    dn=1;
  }
  N = Q;
  divide();    
  if (R==1)
  {      
    //lf
    lf=1;
  }
  return(void);  
}


void drawGhost()
{ 
  multx=128;
  multy=y;
  
  addr = mult()+x;
  
  addr=addr-129;
  
  a=0;
  while (a<3)
  {
    b=0;
    while (b<3)
    { 
      vrammar(addr);
      write(col);      
      addr=addr+1;
      b=b+1;
    }
    addr=addr+125;
    a=a+1;
  }
  return(void);
}











void drawPlayer()
{
  
  //if pacmanDir==1, dont print the top center pixel, etc..
  
  
  multx=128;
  multy=playerY;
  
  addr = mult()+playerX;
  
  addr=addr-129;
  
  a=0;
  while (a<3)
  {
    b=0;
    while (b<3)
    {
      if (a==0)
      {
        if (b==1)
        {
          if (pacmanDir==1)
          {
            if (pacmanMouth>2)
              goto skipPacmanPixel;
          }
        }
      }
      if (a==1)
      {
        if (b==0)
        {
          if (pacmanDir==4)
          {
            if (pacmanMouth>2)
              goto skipPacmanPixel;
          }
        }
        if (b==2)
        {
          if (pacmanDir==2)
          {
            if (pacmanMouth>2)
              goto skipPacmanPixel;
          }
        }
      }
      if (a==2)
      {
        if (b==1)
        {
          if (pacmanDir==3)
          {
            if (pacmanMouth>2)
              goto skipPacmanPixel;
          }
        }
      }
      
      
      vrammar(addr);
      write(60);
      skipPacmanPixel:
      addr=addr+1;
      b=b+1;
    }
    addr=addr+125;
    a=a+1;
  }
  return(void);
}

void calcRedTarget()
{
  
  if (ghostMode==0)
  {
    //go to corner
    redTarg[0]=75;
    redTarg[1]=2;
    return(void);
  }
  if(ghostMode==1)
  {
    //chase
    redTarg[0]=playerX;
    redTarg[1]=playerY;    
  }
  return(void);
}

void calcPinkTarget()
{
  
  if (ghostMode==0)
  {
    //go to corner
    pinkTarg[0]=23;
    pinkTarg[1]=2;
    return(void);
  }
  if(ghostMode==1)
  {
    //chase
    pinkTarg[0]=playerX;
    pinkTarg[1]=playerY;   
    
    //find four spaces in front of him
    
    if (pacmanDir)
    {
      if (pacmanDir==1)
      {
        //up
        pinkTarg[1]=pinkTarg[1]-16;
        
        if (pinkTarg[1]>76)
        {
          //overflow
          //add 75 to make it wrap back around
          pinkTarg[1]=pinkTarg[1]+75;  
        }
        
        pinkTarg[0]=pinkTarg[0]-16; //replicate the orignal bug in the game
        return(void);
      }
      if (pacmanDir==2)
      {
        //rt
        pinkTarg[0]=pinkTarg[0]+16;
        return(void);
      }
      if (pacmanDir==3)
      {
        //dn
        pinkTarg[1]=pinkTarg[1]+16;
        return(void);
      }
      if (pacmanDir==4)
      {
        //lf
        pinkTarg[0]=pinkTarg[0]-16;
      }
    }
  }
  return(void);
}



int getOppositeDir()
{ 
  if (dirForOpp==0)
  {
    return 2;
  }
  if (dirForOpp==1)
  {
    return 3;
  }
  if (dirForOpp==2)
  {
    return 0;
  }
  if (dirForOpp==3)
  {
    return 1;
  }
  return 5;
}


void calcBlueTarget()
{
  if (ghostMode==0)
  {
    //go to corner
    blueTarg[0]=79;
    blueTarg[1]=70;
    return(void);
  }
  if(ghostMode==1)
  {
    //chase
    blueTarg[0]=playerX;
    blueTarg[1]=playerY;   
    
    //find four spaces in front of him
    
    if (pacmanDir)
    {
      if (pacmanDir==1)
      {
        //up
        blueTarg[1]=blueTarg[1]-8;
        
        if (blueTarg[1]>76)
        {
          //overflow
          //add 75 to make it wrap back around
          blueTarg[1]=blueTarg[1]+75;  
        }
        
        blueTarg[0]=blueTarg[0]-8; //replicate the orignal bug in the game
        goto blueTargNextStep;
      }
      if (pacmanDir==2)
      {
        //rt
        blueTarg[0]=blueTarg[0]+8;
        goto blueTargNextStep;
      }
      if (pacmanDir==3)
      {
        //dn
        blueTarg[1]=blueTarg[1]+8;
        goto blueTargNextStep;
      }
      if (pacmanDir==4)
      {
        //lf
        blueTarg[0]=blueTarg[0]-8;
      }
    }
    blueTargNextStep:
    //now blueTarg is 2 in front of pacman,
    //get dx,dy of red's position
    
    dx = blueTarg[0] - redPos[0];
    dy = blueTarg[1] - redPos[1];    
    
    blueTarg[0] = blueTarg[0]+dx;
    blueTarg[1] = blueTarg[1]+dy;    
    
  }
  return(void);  
}

void calcOrangeTarget()
{
  
  if (ghostMode==0)
  {
    //go to corner
    orangeTarg[0]=19;
    orangeTarg[1]=70;
    return(void);
  }
  if(ghostMode==1)
  {
    //get distance to player
       
       
    a=orangePos[0];
    c=playerX;
    b=orangePos[1];
    d=playerY;
    
    a=getDist();
    
    if (a<225)
    {
      //go away
      orangeTarg[0]=19;
      orangeTarg[1]=70;
    }
    else
    {
      //chase him like red does
      orangeTarg[0]=playerX;
      orangeTarg[1]=playerY;
    }
  }
  return(void);
}


//using a,b,c,d
int getDist()
{   
  if (a<c)
  {
    temp=a;
    a=c;
    c=temp;
  }
  if (b<d)
  {
    temp=b;
    b=d;
    d=temp;
  }    
  
  //a and b bigger
  
  multx=a-c;
  multy=multx;
  a=mult();
  
  multx=b-d;
  multy=multx;
  
  return a+mult();    
}





//psuedorandom number gen
void genRand()
{
  
  multx=239;
  multy=rand;
  rand=mult()+randAdd;
  return(void);  
}
/*
void clearScreen()
{  
  b=0;
  c=0;
  while (b<75)
  {
    a=0;
    while (a<100)
    {
      vrammar(c);
      write(0);
      c=c+1;
      a=a+1;
    }
    c=c+28;
    b=b+1;
  }  
  return(void);
}
*/

//uses multx, multy
int mult()
{  
  if (multx==0)
  {
    return 0;
  }
  else
  {
    if (multy==0)
    {
      return 0;
    }
  }
  
  if (multx > multy)
  {
    multtemp = multx;
    multx = multy;
    multy = multtemp;
  }
  
  //smaller number is multx
  
  multacc = 0;
  while (multx>0)
  {
    multacc = multacc + multy;
    multx = multx - 1;
  }
  return multacc;
}



void divide()
{
  Q=0;
  R=N;
  
  while (R >= D)
  {
    Q = Q+1;
    R = R - D;
  }  
  
  return(void);
}


int singleCounter;
void zero()
{
  drawAddr=drawAddr-1;
  singleCounter=0;
  drawY=0;  
  
  while (drawY<7)
  {
    drawX=0;
    while (drawX<5)
    {
      if (numZero[singleCounter]>0)
      {
        multx=numZero[singleCounter];
        multy=col;
        mult();
        vrammar(drawAddr);
        write(multacc);
      }
      
      singleCounter=singleCounter+1;
      drawAddr=drawAddr+1;
      drawX=drawX+1;
    }    
    
    drawAddr=drawAddr+123;
    drawY=drawY+1;
  }
  
  drawAddr=drawAddr-eightNinetySix;
  drawAddr=drawAddr-5;
  
  
  
  return(void);
}


void one()
{
  singleCounter=0;
  drawY=0;  
  
  while (drawY<7)
  {
    drawX=0;
    while (drawX<4)
    {
      if (numOne[singleCounter]>0)
      {
        multx=numOne[singleCounter];
        multy=col;
        mult();
        vrammar(drawAddr);
        write(multacc);
      }
      
      singleCounter=singleCounter+1;
      drawAddr=drawAddr+1;
      drawX=drawX+1;
    }    
    
    drawAddr=drawAddr+124;
    drawY=drawY+1;
  }
  
  drawAddr=drawAddr-eightNinetySix;
  drawAddr=drawAddr-5;
  
  
  
  return(void);
}

void two()
{
  drawAddr=drawAddr-1;
  singleCounter=0;
  drawY=0;  
  
  while (drawY<7)
  {
    drawX=0;
    while (drawX<5)
    {
      if (numTwo[singleCounter]>0)
      {
        multx=numTwo[singleCounter];
        multy=col;
        mult();
        vrammar(drawAddr);
        write(multacc);
      }
      
      singleCounter=singleCounter+1;
      drawAddr=drawAddr+1;
      drawX=drawX+1;
    }    
    
    drawAddr=drawAddr+123;
    drawY=drawY+1;
  }
  
  drawAddr=drawAddr-eightNinetySix;
  drawAddr=drawAddr-5;
  
  
  
  return(void);
}

void three()
{
  singleCounter=0;
  drawY=0;  
  
  while (drawY<7)
  {
    drawX=0;
    while (drawX<4)
    {
      if (numThree[singleCounter]>0)
      {
        multx=numThree[singleCounter];
        multy=col;
        mult();
        vrammar(drawAddr);
        write(multacc);
      }
      
      singleCounter=singleCounter+1;
      drawAddr=drawAddr+1;
      drawX=drawX+1;
    }    
    
    drawAddr=drawAddr+124;
    drawY=drawY+1;
  }
  
  drawAddr=drawAddr-eightNinetySix;
  drawAddr=drawAddr-5;
  
  
  
  return(void);
}


void four()
{
  drawAddr=drawAddr-1;
  singleCounter=0;
  drawY=0;  
  
  while (drawY<7)
  {
    drawX=0;
    while (drawX<5)
    {
      if (numFour[singleCounter]>0)
      {
        multx=numFour[singleCounter];
        multy=col;
        mult();
        vrammar(drawAddr);
        write(multacc);
      }
      
      singleCounter=singleCounter+1;
      drawAddr=drawAddr+1;
      drawX=drawX+1;
    }    
    
    drawAddr=drawAddr+123;
    drawY=drawY+1;
  }
  
  drawAddr=drawAddr-eightNinetySix;
  drawAddr=drawAddr-5;
  
  
  
  return(void);
}

void five()
{
  drawAddr=drawAddr-1;
  singleCounter=0;
  drawY=0;  
  
  while (drawY<7)
  {
    drawX=0;
    while (drawX<5)
    {
      if (numFive[singleCounter]>0)
      {
        multx=numFive[singleCounter];
        multy=col;
        mult();
        vrammar(drawAddr);
        write(multacc);
      }
      
      singleCounter=singleCounter+1;
      drawAddr=drawAddr+1;
      drawX=drawX+1;
    }    
    
    drawAddr=drawAddr+123;
    drawY=drawY+1;
  }
  
  drawAddr=drawAddr-eightNinetySix;
  drawAddr=drawAddr-5;
  return(void);
}

void six()
{
  drawAddr=drawAddr-1;
  singleCounter=0;
  drawY=0;  
  
  while (drawY<7)
  {
    drawX=0;
    while (drawX<5)
    {
      if (numSix[singleCounter]>0)
      {
        multx=numSix[singleCounter];
        multy=col;
        mult();
        vrammar(drawAddr);
        write(multacc);
      }
      
      singleCounter=singleCounter+1;
      drawAddr=drawAddr+1;
      drawX=drawX+1;
    }    
    
    drawAddr=drawAddr+123;
    drawY=drawY+1;
  }
  
  drawAddr=drawAddr-eightNinetySix;
  drawAddr=drawAddr-5;
  return(void);
}

void seven()
{
  drawAddr=drawAddr-1;
  singleCounter=0;
  drawY=0;  
  
  while (drawY<7)
  {
    drawX=0;
    while (drawX<5)
    {
      if (numSeven[singleCounter]>0)
      {
        multx=numSeven[singleCounter];
        multy=col;
        mult();
        vrammar(drawAddr);
        write(multacc);
      }
      
      singleCounter=singleCounter+1;
      drawAddr=drawAddr+1;
      drawX=drawX+1;
    }    
    
    drawAddr=drawAddr+123;
    drawY=drawY+1;
  }
  
  drawAddr=drawAddr-eightNinetySix;
  drawAddr=drawAddr-5;
  return(void);
}


void eight()
{
  drawAddr=drawAddr-1;
  singleCounter=0;
  drawY=0;  
  
  while (drawY<7)
  {
    drawX=0;
    while (drawX<5)
    {
      if (numEight[singleCounter]>0)
      {
        multx=numEight[singleCounter];
        multy=col;
        mult();
        vrammar(drawAddr);
        write(multacc);
      }
      
      singleCounter=singleCounter+1;
      drawAddr=drawAddr+1;
      drawX=drawX+1;
    }    
    
    drawAddr=drawAddr+123;
    drawY=drawY+1;
  }
  
  drawAddr=drawAddr-eightNinetySix;
  drawAddr=drawAddr-5;
  return(void);
}

void nine()
{
  singleCounter=0;
  drawY=0;  
  
  while (drawY<7)
  {
    drawX=0;
    while (drawX<4)
    {
      if (numNine[singleCounter]>0)
      {
        multx=numNine[singleCounter];
        multy=col;
        mult();
        vrammar(drawAddr);
        write(multacc);
      }
      
      singleCounter=singleCounter+1;
      drawAddr=drawAddr+1;
      drawX=drawX+1;
    }    
    
    drawAddr=drawAddr+124;
    drawY=drawY+1;
  }
  
  drawAddr=drawAddr-eightNinetySix;
  drawAddr=drawAddr-5;
  return(void);
}


//uses drawX, drawY, and col, writes num2Draw
void drawNum()
{
  
  multx=drawY;
  multy=128;
  drawAddr=mult()+drawX;  
  
  if (padNumWith1Zeroes==1)
  {
    zero();    
  }
  
  N=num2Draw;
  D=10;  
  divide();
  if (Q==0)
  {
    if (R==0)
    {
      //num was 0
      zero();
      return(void);
    }
  }
  while (Q>0)
  {
    //print current digit, divide again
    
    if (R==0)
    {
      zero();
      goto drawNumAgain;
    }
    if (R==1)
    {
      one();
      goto drawNumAgain;
    }
    if (R==2)
    {
      two();
      goto drawNumAgain;
    }
    if (R==3)
    {
      three();
      goto drawNumAgain;
    }
    if (R==4)
    {
      four();
      goto drawNumAgain;
    }
    if (R==5)
    {
      five();
      goto drawNumAgain;
    }
    if (R==6)
    {
      six();
      goto drawNumAgain;
    }
    if (R==7)
    {
      seven();
      goto drawNumAgain;
    }
    if (R==8)
    {
      eight();
      goto drawNumAgain;
    }
    else
    {
      nine();      
    }
    drawNumAgain:
    
    N=Q;
    divide();
  }
  //last digit
  if (R==0)
  {
    zero();
    return(void);
  }
  if (R==1)
  {
    one();
    return(void);
  }
  if (R==2)
  {
    two();
    return(void);
  }
  if (R==3)
  {
    three();
    return(void);
  }
  if (R==4)
  {
    four();
    return(void);
  }
  if (R==5)
  {
    five();
    return(void);
  }
  if (R==6)
  {
    six();
    return(void);
  }
  if (R==7)
  {
    seven();
    return(void);
  }
  if (R==8)
  {
    eight();
    return(void);
  }
  else
  {
    nine();      
  }
  
  
  
  return(void);
}











