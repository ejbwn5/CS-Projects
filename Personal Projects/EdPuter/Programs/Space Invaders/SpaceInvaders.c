int multx, multy, multtemp, multacc; //variables for multiplication function

int N,D; //variables for division function
int Q,R;

int a,b,c; //multipurpose variables
int x, y, col, dir;

//bitmaps of invaders
const int invader[54] = {0,0,1,0,0,0,1,0,0,0,0,1,1,1,1,1,0,0,0,1,0,1,1,1,0,1,0,1,0,1,1,1,1,1,0,1,1,0,1,0,0,0,1,0,1,0,0,1,0,0,0,1,0,0};
const int invader2[54] = {0, 0, 0, 12, 12, 12, 0, 0, 0, 0, 0, 12, 12, 12, 12, 12, 0, 0, 0, 12, 0, 12, 12, 12, 0, 12, 0, 0, 12, 12, 12, 12, 12, 12, 12, 0, 0, 0, 12, 0, 12, 0, 12, 0, 0, 0, 12, 0, 12, 0, 12, 0, 12, 0};
const int invader3[54] = {0, 0, 0, 12, 0, 12, 0, 0, 0, 12, 0, 12, 12, 12, 12, 12, 0, 12, 12, 12, 12, 0, 12, 0, 12, 12, 12, 0, 12, 12, 12, 12, 12, 12, 12, 0, 0, 12, 0, 12, 0, 12, 0, 12, 0, 12, 12, 0, 0, 0, 0, 0, 12, 12};

//bitmap of player ship
const int player[52] = {0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,0};


int drawX,drawY,drawPos,drawAddr; //variables for draw functions

int writeNum; //number to write with write functions

//bitmap of numbers
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

//bitmap of heart
const int heartSprite[1] = {0, 16, 16, 0, 16, 16, 0, 16, 32, 32, 16, 32, 32, 16, 32, 48, 48, 32, 48, 48, 32, 16, 32, 48, 48, 48, 32, 16, 0, 16, 48, 48, 48, 16, 0, 0, 0, 16, 32, 16, 0, 0, 0, 0, 0, 16, 0, 0, 0};

const mid = 4530;
const invaderYDiff = 896;

int invaderFrameCounter;

const playerY=63; //player Y position
const randAdd = 457;
int alienType;
int rand;
int amt;
int bulletsX[10]; //there can be 10 "bullets" on screen at once
int bulletsY[10];
int bulletsDir[10];
int bulletsSpd[10];

int newBullX,newBullY,newBullDir, newBullSpd;

const int invaderColorChoices[7] = {12, 28, 14, 29, 8, 4, 24};

int invaderX;
int invaderDir;

int bulletSearch;

int invadersRow1[9];
int invadersRow2[9];
int invadersRow3[9];

int invadersRow1Col[9];
int invadersRow2Col[9];
int invadersRow3Col[9];

int invadersRow1Type;
int invadersRow2Type;
int invadersRow3Type;


const threeninefour = 394;

//whole bunch of random variables used in gameplay
int address,address2;
int io;
int playerX;
int times;
int shoot, shootLast;
int lives;
int invaderInd;
int x2,y2;
int score;
int framesTillEnemyShoot;
int level;
int num2Draw;
int padNumWith2Zeroes;
int maxLevelAlien;


int main()
{ 

  rand=0; //seed 
  
  ioin(io);
  
  while (io==0) //wait for input
  {
    ioin(io);
  }
  
  //at this point, the input is nonzero
  
  while (io) //wait for input to release
  {
    rand=rand+1; //count how long it takes button to release and use that for random seed
    ioin(io);
  }
  

  reset:
  score=0;
  level=1;  
  genRand();
  lives=2;  
  
  genNewLevel:
  lives = lives+1;
  if (lives>5) lives=5;
  invaderFrameCounter=0;
  
  N=rand;
  D=8;
  divide();
  framesTillEnemyShoot=32+R;
  genRand();  

  y=0;
  while(y<10) //initialize bullets to not exist
  {
    bulletsX[y] = 255;
    bulletsY[y] = 255;
    bulletsDir[y] = 0;
    y=y+1;
  }


  invaderDir=1;
  invaderX=0;
  playerX=45;
  y=0;
  shoot=0;
  shootLast=0;
  while (y<9) //spawn all invaders
  {
    invadersRow1[y] = 1; 
    invadersRow2[y] = 1;
    invadersRow3[y] = 1;      
    y = y + 1;
  }
  
  //randomize their colors  
  y=0;
  while (y<9)
  {
    N=rand;
    D=7;
    divide();
    invadersRow1Col[y] = invaderColorChoices[R]; 
    genRand();    
    y = y + 1;
  }
  y=0;
  while (y<9)
  {
    N=rand;
    D=7;
    divide();
    invadersRow2Col[y] = invaderColorChoices[R];
    genRand();
    y = y + 1;
  }
  y=0;
  while (y<9)
  {
    N=rand;
    D=7;
    divide();
    invadersRow3Col[y] = invaderColorChoices[R];
    genRand();
    y = y + 1;
  }
  
  
  maxLevelAlien=level;
  
  if (maxLevelAlien>3)
    maxLevelAlien=3;
  
  N=rand;
  D=maxLevelAlien;
  divide();
  invadersRow1Type=R;
  genRand();
  N=rand;
  
  divide();
  invadersRow2Type=R;
  genRand();
  N=rand;
  
  divide();
  invadersRow3Type=R;
  genRand();  
  
  
  
  
  goBack:
  
  N=rand;
  D=8;
  divide();
  framesTillEnemyShoot=32+R;
  genRand();
  
  
  while (1)
  {
    
    //clear screen
    clearScreen();
    
    
    
    
    
    ioin(io);
    
    N = io;
    D = 2;
    divide();
    N = Q;
    if (R==1)
    {
      //left button
      if (playerX>0)
        playerX=playerX-1;
      
    }
    
    divide();
    
    if (R==1)
    {      
      //right button
      if (playerX<87)
        playerX=playerX+1;
    }
    N = Q;
    shootLast=shoot;
    shoot=0;
    divide();    
    if (R==1)
    {      
      //shoot button
      shoot=1;
    }
    
    
    if (shoot)
    {
      if (shootLast!=1)
      {
        //shoot on this frame
        
        
        newBullX = playerX+6;
        newBullY = playerY-1;
        newBullDir = 255;
        newBullSpd=2;
        addBullet();
        
        
        /*
        newBullX = invaderX+36;
        newBullY = 29;
        newBullDir = 1;
        addBullet();
        */
        
      }
    }
    
    
    //decide if enemies should shoot this frame
    
    
    if (framesTillEnemyShoot==0)
    {
      //someones shooting
      
      N=rand;
      D=8;
      divide();
      framesTillEnemyShoot=16+R-level;
      if (framesTillEnemyShoot>50)
      {
        framesTillEnemyShoot=1;
      }
      genRand();
      
      //find someone to shoot
      
      newBullDir=1;
      
      N=rand;
      D=9;
      divide();
      if(invadersRow3[R])
      {
        //him
        
        multx=R;
        multy=10;
        
        newBullX = invaderX+mult()+6;
        newBullY = 29;
        
        if (invadersRow3Type==0)
        {
          newBullSpd=1;
        }
        else
        {
          if (invadersRow3Type==1)
          {
            newBullSpd=2;  
          }
          else
          {
            newBullSpd=3;
          }
        }
        
        addBullet();
      }
      else
      {
        if(invadersRow2[R])
        {
          //him
          multx=R;
          multy=10;
          
          newBullX = 14-invaderX+mult();
          newBullY = 21;
          
          if (invadersRow2Type==0)
          {
            newBullSpd=1;
          }
          else
          {
            if (invadersRow2Type==1)
            {
              newBullSpd=2;  
            }
            else
            {
              newBullSpd=3;
            }
          }
          
          addBullet();
        }
        else
        {
          if(invadersRow1[R])
          {
            //him
            multx=R;
            multy=10;
            
            newBullX = invaderX+mult()+6;
            newBullY = 14;
            if (invadersRow1Type==0)
            {
              newBullSpd=1;
            }
            else
            {
              if (invadersRow1Type==1)
              {
                newBullSpd=2;  
              }
              else
              {
                newBullSpd=3;
              }
            }
            addBullet();
          }
        }
      }
      
      //check bottom up
      
    }
    
    
    
    bulletSearch=0;
    while (bulletSearch<10)
    {      
      if (bulletsX[bulletSearch]!=255)
      {        
      
        x = bulletsX[bulletSearch];
        y = bulletsY[bulletSearch];
        dir = bulletsDir[bulletSearch];
        
        
        if (dir==1)
        {
          //enemy shot
          multy=128;
          multx=y;
          y=mult();        
          vrammar(y+x);
          write(12);
          y=y-128;
          
          vrammar(y+x);
          write(8);
          y=y-128;
          
          vrammar(y+x);
          write(8);
          y=y-128;
          
          vrammar(y+x);
          write(4);
          y=y-128;
          
          vrammar(y+x);
          write(4);
          
          
          //check for hit
          
          if (bulletsY[bulletSearch]>playerY+1)
          {
            if (bulletsY[bulletSearch]<playerY+8)
            {
              //check X bounds
              
              if (bulletsX[bulletSearch]>=playerX)
              {
                if (bulletsX[bulletSearch]<playerX+13)
                {
                  //hit
                  
                  goto playerHit;
                  
                }
              }
              
            }
          }
          else
          {
            //check for tip
            if (bulletsY[bulletSearch]>=playerY)
            {
              //check X bounds
              if (bulletsX[bulletSearch]>=playerX+5)
              {
                if (bulletsX[bulletSearch]<playerX+8)
                {
                  //hit
                  
                  goto playerHit;
                  
                }
              }
            }
          }
          
          
          bulletsY[bulletSearch] = bulletsY[bulletSearch] + bulletsSpd[bulletSearch];
        }
        else
        {
          
          //check for hits on enemies
          
          
          if (bulletsY[bulletSearch]<30) //dont bother checking if not in range where hitting is possible
          {
            
            if (bulletsY[bulletSearch]>=24) //chance to hit bottom row
            {
              invaderInd=0;
              x2=invaderX+2;
              y2=24;
              while (invaderInd<9)
              {
                if (invadersRow3[invaderInd])
                {
                  //check if this one hit
                  
                  //hitbox is x<=projX<=x+8
                  
                  if (x2<=bulletsX[bulletSearch])
                  {
                    if (x2+8>=bulletsX[bulletSearch])
                    {
                      //hit
                      
                       bulletsX[bulletSearch]=255;
                       bulletsY[bulletSearch]=255;
                       
                       invadersRow3[invaderInd]=0;
                       score=score+level+invadersRow3Type;
                       goto nextBullet;
                      
                    }
                  }
                }
                invaderInd=invaderInd+1;
                x2=x2+10;
                
              }
            }
            
            //didnt hit anything in bottom row, look for second row
            if (bulletsY[bulletSearch]<=22) //dont bother checking if not in range where hitting is possible
            {
              if (bulletsY[bulletSearch]>=17) //chance to hit bottom row
              {
                invaderInd=0;
                x2=9-invaderX;
                y2=17;
                while (invaderInd<9)
                {
                  if (invadersRow2[invaderInd])
                  {
                    //check if this one hit
                    
                    //hitbox is x<=projX<=x+8
                    
                    if (x2<=bulletsX[bulletSearch])
                    {
                      if (x2+8>=bulletsX[bulletSearch])
                      {
                        //hit
                        
                         bulletsX[bulletSearch]=255;
                         bulletsY[bulletSearch]=255;
                         
                         invadersRow2[invaderInd]=0;
                         score=score+level+level+invadersRow2Type;
                         goto nextBullet;
                        
                      }
                    }
                  }
                  invaderInd=invaderInd+1;
                  x2=x2+10;
                  
                }
              }
            }
            
            //didnt hit anything in second row, look for top row
            
            if (bulletsY[bulletSearch]<=15)
            {
              if (bulletsY[bulletSearch]>=10) //chance to hit top row
              {
                invaderInd=0;
                x2=invaderX+2;
                y2=10;
                while (invaderInd<9)
                {
                  if (invadersRow1[invaderInd])
                  {
                    //check if this one hit
                    
                    //hitbox is x<=projX<=x+8
                    
                    if (x2<=bulletsX[bulletSearch])
                    {
                      if (x2+8>=bulletsX[bulletSearch])
                      {
                        //hit
                        
                         bulletsX[bulletSearch]=255;
                         bulletsY[bulletSearch]=255;
                         
                         invadersRow1[invaderInd]=0;
                         score=score+level+level+level+invadersRow1Type;
                         goto nextBullet;
                        
                      }
                    }
                  }
                  invaderInd=invaderInd+1;
                  x2=x2+10;
                  
                }
              }
            }
            
            
          }
          
          //no enemies hit, draw bullet
          
          multy=128;
          multx=y;
          y=mult();        
          vrammar(y+x);
          write(48);
          y=y+128;
          
          vrammar(y+x);
          write(32);
          y=y+128;
          
          vrammar(y+x);
          write(32);
          y=y+128;
          
          vrammar(y+x);
          write(16);
          y=y+128;
          
          vrammar(y+x);
          write(16);
          
          
          //add bullet speed
          bulletsY[bulletSearch] = bulletsY[bulletSearch] - bulletsSpd[bulletSearch];
        }
        
        if (bulletsY[bulletSearch]>79)
        {
          bulletsX[bulletSearch]=255;
          bulletsY[bulletSearch]=255;
        }
      
      }
    /*  else
      {
        vrammar(bulletSearch);
        write(48);
      }
    */
    
    
      nextBullet:
      bulletSearch=bulletSearch+1;
    }
    
    
    
    //draw Invaders
    
    x=2+invaderX;
    y=10;    
    
    multx=128;
    multy=y;
    y=mult();
    
    invaderInd=0;
    
    while (invaderInd<9)
    {
      //draw invader
      if (invadersRow1[invaderInd])
      {
        col = invadersRow1Col[invaderInd];
        
        alienType=invadersRow1Type;
        
        drawInvader();
      }
      x=x+10;
      invaderInd=invaderInd+1;
    }
    
    
    x=9-invaderX;
    y=y+invaderYDiff;
    invaderInd=0;
    
    while (invaderInd<9)
    {
      //draw invader
      if (invadersRow2[invaderInd])
      {
        col = invadersRow2Col[invaderInd];
        
        alienType=invadersRow2Type;
        
        drawInvader();
      }
      x=x+10;
      invaderInd=invaderInd+1;
    }
    
    x=2+invaderX;
    y=y+invaderYDiff;
    invaderInd=0;
    
    while (invaderInd<9)
    {
      //draw invader
      if (invadersRow3[invaderInd])
      {
        col = invadersRow3Col[invaderInd];
        
        alienType=invadersRow3Type;
        
        drawInvader();
      }
      x=x+10;
      invaderInd=invaderInd+1;
    }
    
    
    
    //draw Player
    
    col = 63; 
    
    y=playerY;
    x=playerX;
    drawPlayer();
    
    //draw hud
    
    col=20;
    padNumWith2Zeroes=1;
    drawX=93;
    drawY=2;    
    num2Draw=score;
    drawNum();
    
    
    y=0;
    x2=0;
    y2=129;
    while (y<7)
    {
      x=0;
      while (x<7)
      {
        if (heartSprite[x2]>0)
        {
          vrammar(y2);
          write(heartSprite[x2]);
        }
        x=x+1;
        x2=x2+1;
        y2=y2+1;
      }
      y2=y2+121;
      y=y+1;
    }
    
    col=16;
    padNumWith2Zeroes=0;
    drawX=10;
    drawY=1;    
    num2Draw=lives;
    drawNum();
    
    
    
    flip; //done drawing frame, flip buffer
    
    
    //check for next level
    
    y=0;
    while (y<9) //see if all invaders dead
    {
      if (invadersRow1[y])
      {
        goto notNextLevel;
      }
      if (invadersRow2[y])
      {
        goto notNextLevel;
      }
      if (invadersRow3[y])
      {
        goto notNextLevel;
      }
      
      y=y+1;
    }
    //next level
    level=level+1;
    goto genNewLevel;
    
    notNextLevel:
    
    invaderFrameCounter=invaderFrameCounter+1;
    framesTillEnemyShoot=framesTillEnemyShoot-1;
    amt=12-level;
    if (amt>14) amt=0;
    if (invaderFrameCounter>amt)
    {
      invaderFrameCounter=0;
      
      if (invaderDir==1)
      {
        invaderX=invaderX+1;
        if (invaderX==7)
        {        
          invaderDir=0;
        }
      }
      else
      {
        invaderX=invaderX-1;
        if (invaderX==0)
        {        
          invaderDir=1;
        }
      }    
      
    }
    
    
    
    
    
    
  }
  
  playerHit:
  
  lives=lives-1; //lose a life
  if (lives>0)
  {
    //reset
    
    bulletSearch=0;
    while (bulletSearch<9)
    {
      bulletsX[bulletSearch] = 255;
      bulletsY[bulletSearch] = 255;
      bulletsDir[bulletSearch] = 0;
      bulletSearch=bulletSearch+1;      
    }
    playerX=45;    
    y=0;
    while (y<50)
    {
      clearScreen();
      flip;
      y=y+1;
    }
    
    goto goBack;
  }
 
  //game over
  
  
  clearScreen();
  
  col=20;
  padNumWith2Zeroes=1;
  drawX=93;
  drawY=2;    
  num2Draw=score;
  drawNum();
  
  y=0;
  x2=0;
  y2=129;
  while (y<7)
  {
    x=0;
    while (x<7)
    {
      if (heartSprite[x2]>0)
      {
        vrammar(y2);
        write(heartSprite[x2]);
      }
      x=x+1;
      x2=x2+1;
      y2=y2+1;
    }
    y2=y2+121;
    y=y+1;
  }
  
  col=16;
  padNumWith2Zeroes=0;
  drawX=10;
  drawY=1;    
  num2Draw=lives;
  drawNum();
  
  flip;
  ioin(io);
  while (io)
  {
    ioin(io);
  }
  while (io==0)
  {
    ioin(io);
  }
  goto reset;
  return 0;
}





void genRand()
{
  
  multx=239;
  multy=rand;
  rand=mult()+randAdd;
  return(void);  
}

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




void addBullet()
{
  bulletSearch=0;
  while (bulletSearch<10)
  {
    if (bulletsX[bulletSearch]==255)
    {
      //valid space
      
      bulletsX[bulletSearch] = newBullX;
      bulletsY[bulletSearch] = newBullY;
      bulletsDir[bulletSearch] = newBullDir;
      bulletsSpd[bulletSearch] = newBullSpd;
      
      return(void);
    }
    
    
    bulletSearch=bulletSearch+1;
  }
  return(void);
}



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


//use alienType
void drawInvader()
{
  
  
  drawPos=0;  
  drawY=0;
 
  drawAddr=y;
  
  while (drawY<6)
  {
    drawX=0;
    while (drawX<9)
    {
      //get type
      if (alienType==1)
      {        
        if (invader[drawPos])
        {
          //draw pixel
          vrammar(drawAddr+x);
          write(col);
        }
      }
      else
      {
        if (alienType==0)
        {
          if (invader2[drawPos])
          {
            //draw pixel
            vrammar(drawAddr+x);
            write(col);
          }
        }
        else
        {
          if (invader3[drawPos])
          {
            //draw pixel
            vrammar(drawAddr+x);
            write(col);
          }
        }
      }
      
      drawPos=drawPos+1;
      drawAddr=drawAddr+1;
      drawX=drawX+1;
    }
    drawAddr=drawAddr-9+128;
    drawY = drawY + 1;
  }
  return(void);
}

void drawPlayer()
{
  drawPos=0;  
  drawY=0;
  
  multx = y+drawY;
  multy=128;
  
  drawAddr=mult();
  
  while (drawY<8)
  {
    drawX=0;
    while (drawX<13)
    {
      if (drawY<4)
      {
        if (player[drawPos])
        {
          //draw pixel
          
          vrammar(drawAddr+x);
          write(col);
        }
      }
      else
      {
        //all filled
        
        
        vrammar(drawAddr+x);
        write(col);
        
      }
      
      drawAddr=drawAddr+1;
      drawPos=drawPos+1;
      drawX=drawX+1;
    }
    drawAddr=drawAddr+128-13;
    drawY = drawY + 1;
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
  
  drawAddr=drawAddr-invaderYDiff;
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
  
  drawAddr=drawAddr-invaderYDiff;
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
  
  drawAddr=drawAddr-invaderYDiff;
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
  
  drawAddr=drawAddr-invaderYDiff;
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
  
  drawAddr=drawAddr-invaderYDiff;
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
  
  drawAddr=drawAddr-invaderYDiff;
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
  
  drawAddr=drawAddr-invaderYDiff;
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
  
  drawAddr=drawAddr-invaderYDiff;
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
  
  drawAddr=drawAddr-invaderYDiff;
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
  
  drawAddr=drawAddr-invaderYDiff;
  drawAddr=drawAddr-5;
  return(void);
}


//uses drawX, drawY, and col, writes num2Draw
void drawNum()
{
  
  multx=drawY;
  multy=128;
  drawAddr=mult()+drawX;  
  
  if (padNumWith2Zeroes==1)
  {
    zero();
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

