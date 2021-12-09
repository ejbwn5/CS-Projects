int offset;
int offset2;
int offset3;
int timer;

int main()
{
  //initialize variables
  offset = 0;
  offset2 = 0;
  offset3 = 0;
  timer = 0;
  
  while (1) //loop forever
  {
    
    if (timer < 10) //draw the first pattern for 10 frames
    {
      draw1();
    }
    else
    {
      if (timer < 20) //then 10 frames of the second pattern
      {
        draw2();
      }
      else
      {
       if (timer < 30) //then third
       {
         draw3();
       }
       else //then fourth
       {
         draw4();
       } 
      }
    }
    
    
    flip; //flip buffer after drawing
    offset = offset + 1; //increment offset and timer
    timer = timer + 1;    
    if (timer > 39) //loop back around
    {
      timer = 0;
    }    
  }  
  return 0;
}

int x, y;
int addr;
int col;

void draw1() //pattern 1
{  
  y = 0;
  addr = 0;
  
  while (y < 75)
  {    
    x = 0;
    while (x < 100)
    {      
      vrammar(addr);
      write(x + y + offset);
      addr = addr + 1;
      x = x + 1;
    }
    addr = addr + 28;
    y = y + 1;
  }
  return void;
}

void draw2()
{  
  y = 0;
  addr = 0;
  col = 0;
  
  while (y < 75)
  {    
    x = 0;
    while (x < 100)
    {      
      vrammar(addr);
      write(col+offset);
      addr = addr + 1;
      x = x + 1;
    }
    addr = addr + 28;
    y = y + 1;
    col = col + 3;
  }
  return void;
}

void draw3()
{  
  y = 0;
  addr = 0;
  
  while (y < 75)
  {    
    x = 0;
    while (x < 100)
    {      
      vrammar(addr);
      write(x + x + y + offset2);
      addr = addr + 1;
      x = x + 1;
    }
    addr = addr + 28;
    y = y + 1;    
  }  
  offset2 = offset2 - 4;
  
  return void;
}

void draw4()
{  
  y = 0;
  addr = 0;
  col = 0;
  
  while (y < 75)
  {    
    x = 0;
    while (x < 100)
    {      
      vrammar(addr);
      write(x + offset + col + offset3);
      addr = addr + 1;
      x = x + 1;
    }
    addr = addr + 28;
    y = y + 1;
    col = col + 32;
  }  
  offset3 = offset3 + 32;
  
  return void;
}
