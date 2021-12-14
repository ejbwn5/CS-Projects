
int multx, multy, multtemp, multacc; //variables for multiplication function

int N,D; //variables for division function
int Q,R;

int a,b,c;

int col;

int num2Draw;

int drawX,drawY,drawPos,drawAddr; //variables for draw functions

const eightNinetySix = 896;

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



int padNumWith2Zeroes;

const fortyThousand = 40000;

int num;
int num2;
int temp;

int counter;

int series;


int main()
{
  num = 1;
  num2 = 0;
  series=0;
  counter = 0;
  padNumWith2Zeroes=0;
  
  while (1)
  {
    col=16; //red
    clearScreen();
    drawX = 75;
    drawY=50;    
    num2Draw = num;  //fibonacci
    drawNum();  
    
    col=4;    
    drawX = 75;
    drawY=32;    
    num2Draw = series;  //series sum
    drawNum();     
    
    col=20;
    drawX = 75;
    drawY = 15;
    num2Draw = counter; //counter
    drawNum();
    
    
    //flip buffer
    flip;
    
    counter = counter + 1; //increment counter
    
    series = series + counter; //add counter to series sum
    
    
    
    //reset fibonacci if it gets too high
    if (num > fortyThousand)
    {
      num = 1;
      num2 = 0;
    }   
    else //otherwise, calc next fibonacci number
    {
      temp = num2;
      num2 = num;
      num = num + temp;
    }    
  }
  
  return 0;
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





