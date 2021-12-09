









int offset;


int main()
{
  offset = 0;
  
  while (1)
  {
    
    draw();
    flip;
    offset = offset + 1;
  }  
  return 0;
}




int x, y;
int addr;


void drawDiag()
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













