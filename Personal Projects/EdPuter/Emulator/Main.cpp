#include <iostream>
#include <fstream>
#include <string>
#include "Libs\SDL.h"
#include "Libs\SDL_image.h"
#include "Libs\SDL_timer.h" 
#include <iomanip>
#include <sstream>
#include <chrono>
#include <direct.h>
#include <stdio.h>
#include <map>
#define GetCurrentDir _getcwd

using namespace std;

//Double buffered SDL surfaces

SDL_Surface* surface = NULL;
SDL_Surface* surface2 = NULL;
SDL_Surface* winsurface = NULL;

//which buffer to use
bool VRAMToggle = false;

//array to act as the RAM for Edputer
unsigned short RAM[131072];

//memory address registers for VRAM and regular RAM
unsigned short VRAMMAR, MAR;

//registers
unsigned short A, B, C, IR, SP, ALU, IOL, IOH, PC, Subcounter;

//the actual board has physical switches to determine direction of the IO
bool IOLDir = 0; //0 is in, 1 is out
bool IOHDir = 0;


//deprecated
//array for the CPU instruction decoding bitmap
//this was horribly inefficient so I now use emulation optimizations
//by doing the operation based entirely on opcode alone
//unsigned int CPU[32768];

//the PROM is what hold the program's code
unsigned short PROM[16384];
char PROMCode[16384];
char PROMArgs[16384];


unsigned int CPUAddr;

//bitmask for all the control bits
int CRF = 0b1;
int IRinF = 0b10;
int IRoutF = 0b100;
int CPU4F = 0b1000;
int VRinF = 0b10000;
int HLTF = 0b100000;
int CPU1F = 0b1000000;
int VRAMWriteF = 0b10000000;

int CPU3F = 0b100000000;
int CPU2F = 0b1000000000;
int SPDirF = 0b10000000000;
int SPGoF = 0b100000000000;
int CPU8F = 0b1000000000000;
int CPU6F = 0b10000000000000;
int IOF = 0b100000000000000;
int CPU7F = 0b1000000000000000;

int BinF = 0b10000000000000000;
int AoutF = 0b100000000000000000;
int ALUOutF = 0b1000000000000000000;
int BoutF = 0b10000000000000000000;
int AinF = 0b100000000000000000000;
int FlagsWriteF = 0b1000000000000000000000;
int SubF = 0b10000000000000000000000;
int CPU5F = 0b100000000000000000000000;

//cpu flags
bool zeroFlag = false;
bool carryFlag = false;

//this cpu flag is currently unused
bool unknownFlag = false;


unsigned short addr = 0;

//debugging purposes
void disp()
{
	cout << "CF: " << carryFlag << endl;
	cout << "ZF: " << zeroFlag << endl;
	cout << "A: " << A << endl;
	cout << "B: " << B << endl;
	cout << "C: " << C << endl;
	cout << "IO: " << (IOL | ((IOH << 8) & 0xFF00)) << endl;
	cout << "Stack Pointer: " << SP << endl;
	cout << "Program Counter: " << addr << endl;
	cout << "VRAM Mem Addr Reg: " << VRAMMAR << endl << endl;

}

//write to an SDL surface
void writeSurface(int addr, int val, SDL_Surface* surf)
{
	int x = addr % 128; //get x coord and y coord depending on address value
	int y = addr / 128; // each row is 128 pixels long

	if (x > 99) return; //off screen, so skip it for performance boost
	if (y > 74) return;

	int b = val & 0b11; //bitmask out the color channels
	int g = (val & 0b1100) >> 2;
	int r = (val & 0b110000) >> 4;

	Uint16 * const target_pixel = (Uint16 *)((Uint8 *)surf->pixels + y * surf->pitch + x * surf->format->BytesPerPixel); //get desired pixel
	
	//write to that pixel using color data
	//the 85s are because each pixel has 4 different color options, and 255 / 3 = 85
	//so each channel can be either 0, 85, 170, or 255	
	*target_pixel = SDL_MapRGB(surf->format, 85 * r, 85 * g, 85 * b); 
}



void reset()
{
	//reset all the registers and stuff
	addr = 0;
	A = 0;
	B = 0;
	C = 0;
	IR = 0;
	SP = 0;
	PC = 0;
	Subcounter = 0;
	MAR = 0;
	VRAMMAR = 0;
	VRAMToggle = false;

	for (char y = 0; y < 75; y++)
	{
		for (char x = 0; x < 100; x++)
		{
			writeSurface(128 * y + x, 0, surface);
			writeSurface(128 * y + x, 0, surface2);
		}
	}

}





bool debug = false;
bool trace = false;
bool single = false;
bool clk = true;

//bools for simulating input
bool leftB = false;
bool rightB = false;
bool shootB = false;
bool upB = false;
bool dnB = false;
bool leftUp = false;
bool rightUp = false;
bool leftDown = false;
bool rightDown = false;





//control scheme for space invaders
int defaultControlScheme(SDL_Event &e)
{
	while (true) //try all valid polls
	{
		if (SDL_PollEvent(&e) != 0) //some event triggered
		{
			if (e.type == SDL_QUIT) //quit out
			{
				return 1;
			}
			else if (e.type == SDL_KEYDOWN)
			{
				if (e.key.repeat == 0)
				{
					switch (e.key.keysym.sym)
					{
					case SDLK_f:
						single = !single;
						break;
					case SDLK_r:
						reset();
						return 2;
						break;
					}
				}
			}
		}
		else
		{
			break;
		}
	}
	return 0;
}



//control scheme for pong
int pongInputLayout(SDL_Event &e)
{
	while (true) //try all valid polls
	{		
		if (SDL_PollEvent(&e) != 0) //some event triggered
		{
			if (e.type == SDL_QUIT) //quit out
			{
				return 1;
			}
			else if (e.type == SDL_KEYDOWN)
			{
				if (e.key.repeat == 0) //only on keydown
				{
					//Select surfaces based on key press
					switch (e.key.keysym.sym) //see if key pressed is in this control scheme
					{
					//up and down for left pole
					case SDLK_w:
						leftUp = true;
						break;
					case SDLK_s:
						leftDown = true;
						break;

					//up and down for right pole
					case SDLK_UP:
						rightUp = true;
						break;
					case SDLK_DOWN:
						rightDown = true;
						break;

					//toggle debug single instruction mode
					case SDLK_f:
						single = !single;
						break;

					//reset computer
					case SDLK_r:
						reset();
						return 2;
						break;
					}
				}
			}
			else if (e.type == SDL_KEYUP)
			{
				if (e.key.repeat == 0)
				{
					switch (e.key.keysym.sym) //see if key raised is in this control scheme
					{
					case SDLK_w:
						leftUp = false;
						break;
					case SDLK_s:
						leftDown = false;
						break;
					case SDLK_UP:
						rightUp = false;
						break;
					case SDLK_DOWN:
						rightDown = false;
						break;
					}
				}

			}
		}
		else
		{
			IOL = 0 | ((leftUp) & 1) | ((leftDown << 1) & 2) | ((rightUp << 2) & 4) | ((rightDown << 3) & 8); //shift bits to appropriate io lines and set register
			break;
		}
	}
	return 0;
}


//control scheme for space invaders
int spaceInvadersInputLayout(SDL_Event &e)
{
	while (true) //try all valid polls
	{
		if (SDL_PollEvent(&e) != 0) //some event triggered
		{
			if (e.type == SDL_QUIT) //quit out
			{
				return 1;
			}
			else if (e.type == SDL_KEYDOWN)
			{
				if (e.key.repeat == 0)
				{					
					switch (e.key.keysym.sym)
					{
					//A and D move left and right
					case SDLK_a:
						leftB = true;
						break;
					case SDLK_d:
						rightB = true;
						break;
					case SDLK_f:
						single = !single;
						break;
					//spacebar shoots
					case SDLK_SPACE:
						shootB = true;				
						break;
					case SDLK_r:
						reset();
						return 2;
						break;
					}
				}
			}
			else if (e.type == SDL_KEYUP)
			{
				if (e.key.repeat == 0)
				{
					switch (e.key.keysym.sym)
					{
					case SDLK_a:
						leftB = false;
						break;
					case SDLK_d:
						rightB = false;
						break;
					case SDLK_SPACE:
						shootB = false;
						break;
					}
				}

			}
		}
		else
		{
			IOL = 0 | ((leftB) & 1) | ((rightB << 1) & 2) | ((shootB << 2) & 4); //shift the bits according to the control scheme and write to IO register
			break;
		}
	}
	return 0;
}

//control scheme for pacman
int pacmanInputLayout(SDL_Event &e)
{
	while (true) //try all valid polls
	{
		if (SDL_PollEvent(&e) != 0) //some event triggered
		{
			if (e.type == SDL_QUIT) //quit out
			{
				return 1;
			}
			else if (e.type == SDL_KEYDOWN)
			{
				if (e.key.repeat == 0)
				{
					//Select surfaces based on key press
					switch (e.key.keysym.sym)
					{
					//arrow keys move
					case SDLK_UP:
						upB = true;
						break;
					case SDLK_DOWN:
						dnB = true;
						break;
					case SDLK_RIGHT:
						rightB = true;
						break;
					case SDLK_LEFT:
						leftB = true;
						break;					
					case SDLK_f:
						single = !single;
						break;					
					case SDLK_r:
						reset();
						return 2;
						break;
					}
				}
			}
			else if (e.type == SDL_KEYUP)
			{
				if (e.key.repeat == 0)
				{
					switch (e.key.keysym.sym)
					{
					case SDLK_UP:
						upB = false;
						break;
					case SDLK_DOWN:
						dnB = false;
						break;
					case SDLK_RIGHT:
						rightB = false;
						break;
					case SDLK_LEFT:
						leftB = false;
						break;
					}
				}

			}		
		}
		else
		{
			IOL = 0 | ((leftB << 3) & 8) | ((dnB << 2) & 4) | ((rightB << 1) & 2) | ((upB) & 1); //shift bits accordingly and write to IO register
			break;
		}
	}
	return 0;
}

string controlSchemes[] = { "0: None", "1: Pacman", "2: Space Invaders", "3: Pong" };

int inputMethod;

int getInput(SDL_Event &e)
{
	switch (inputMethod)
	{
	case 1:
		return pacmanInputLayout(e);
	case 2:
		return spaceInvadersInputLayout(e);
	case 3:
		return pongInputLayout(e);
	default:
		return defaultControlScheme(e);
	}
}




//set carry flag and zero flag based on addition
void updateFlagsAdd()
{
	if (((unsigned int)A + (unsigned int)B) > 65535)
	{
		carryFlag = true;
	}
	else
	{
		carryFlag = false;
	}
	zeroFlag = ((A + B) == 0);
}

//set carry flag and zero flag based on subtraction
void updateFlagsSub()
{
	if (((unsigned int)A - (unsigned int)B) > 65535)
	{
		carryFlag = true;
	}
	else
	{
		carryFlag = false;
	}
	zeroFlag = ((A - B) == 0);

}



using namespace std;
int main(int argc, char* argv[])
{
	//Get control scheme
	cout << "Choose control scheme:" << endl;

	for (string &s : controlSchemes)
	{
		cout << s << endl;
	}

	cin >> inputMethod;

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		printf("error initializing SDL: %s\n", SDL_GetError());
	}
		
	SDL_Window* win = SDL_CreateWindow("Edputer Screen",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		1000, 750, 0);



	if (win == NULL)
	{
		printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
		while (1);
	}
	else
	{
		//Get window surface
		
		//initialize the two buffer windows
		surface = SDL_CreateRGBSurface(0, 100, 75, 16, 0, 0, 0, 0);
		surface2 = SDL_CreateRGBSurface(0, 100, 75, 16, 0, 0, 0, 0);

		//window surface set to first buffer
		winsurface = SDL_GetWindowSurface(win);
	}




	
	//load the Code section of program memory from file

	std::ifstream Code("Code.bin", std::ifstream::binary);
	if (Code) {
		// get length of file:
		Code.seekg(0, Code.end);
		int length = Code.tellg();
		Code.seekg(0, Code.beg);
		Code.read(PROMCode, length);
		if (!Code)
			std::cout << "error: only " << Code.gcount() << " could be read";
		Code.close();
	}

	//load the Argument section of program memory from file
	std::ifstream Arg("Arg.bin", std::ifstream::binary);
	if (Arg) {
		// get length of file:
		Arg.seekg(0, Arg.end);
		int length = Arg.tellg();
		Arg.seekg(0, Arg.beg);
		Arg.read(PROMArgs, length);
		if (!Arg)
			std::cout << "error: only " << Arg.gcount() << " could be read";
		Arg.close();
	}

	//combine the two byte long arrays into one 16-bit wide chunk of memory
	for (int i = 0; i < 16384; i++)
	{
		PROM[i] = (((short)PROMCode[i]) << 8) | (((short)PROMArgs[i]) & 255);
	}

	SDL_UpdateWindowSurface(win);
	
	SDL_Event e;
	bool halt = false;
	reset();
	addr = 0;
	unsigned short opcode;

	
	while (1)
	{
		skipIncrement: 

		int res = getInput(e);
		if (res == 1) break;
		else if (res == 2) continue;

		if (!single && !halt)
		{
			opcode = PROM[addr] >> 8; //pull opcode from current code memory address according to program counter

			// do the operation based on opcode
			switch (opcode)
			{
			case 0: //HLT							
					halt = true;
					while (1) {};
				break;
			case 1: //LDACMA
					//arg as address, load A from code memory
				A = PROM[PROM[addr] & 255];
				break;
			case 2: //LDAI
				A = (PROM[addr] & 255);
				break;
			case 3: //LDBCMA
				B = PROM[PROM[addr] & 255];
				break;
			case 4: //LDBI
				B = (PROM[addr] & 255);
				break;
			case 5: //LDAIO
				A = 0;
				if (IOHDir == 0) //H in
				{
					A |= IOH;
				}
				if (IOLDir == 0) //L in
				{
					A |= IOL;
				}
				break;
			case 6: //LDACMC					
				A = PROM[C];
				break;
			case 7: //LDBIO
				B = 0;
				if (IOHDir == 0) //H in
				{
					B |= IOH;
				}
				if (IOLDir == 0) //L in
				{
					B |= IOL;
				}
				break;
			case 8: //ADDA
				updateFlagsAdd();
				A = A + B;
				break;
			case 9: //ADDB
				updateFlagsAdd();
				B = A + B;
				break;
			case 10: //ADDC
				updateFlagsAdd();
				C = A + B;
				break;
			case 11: //SUBA		
				updateFlagsSub();
				A = A - B;
				break;
			case 12: //SUBB
				updateFlagsSub();
				B = A - B;
				break;
			case 13: //SUBC
				updateFlagsSub();
				C = A - B;
				break;
			case 14: //FLIP				
				if (VRAMToggle)
				{
					SDL_BlitScaled(surface2, NULL, winsurface, NULL);
				}
				else
				{
					SDL_BlitScaled(surface, NULL, winsurface, NULL);
				}			
				VRAMToggle = !VRAMToggle;
				SDL_UpdateWindowSurface(win);
				break;
			case 15: //LDARAM
				A = RAM[PROM[addr] & 255];
				break;
			case 16: //JMP
				addr = (PROM[addr] & 255);
				goto skipIncrement;
			case 17: //JMPA
				addr = A;
				goto skipIncrement;
			case 18: //JMPB
				addr = B;
				goto skipIncrement;
			case 19: //JMPC
				addr = C;
				goto skipIncrement;
			case 20: //JMPRAM
				addr = RAM[PROM[addr] & 255];
				goto skipIncrement;
			case 21: //CALL
					 //store current address in stack, increment sp, jmp to arg
				RAM[SP] = addr;
				SP++;
				addr = (PROM[addr] & 255);
				goto skipIncrement;
			case 22: //RET
					 //decrement sp, jmp to addr in ram at sp
				SP--;
				addr = RAM[SP];
				break;
			case 23: //PUSH immediate
				RAM[SP] = (PROM[addr] & 255);
				SP++;
				break;
			case 24: //POPA
				SP--;
				A = RAM[SP];
				break;
			case 25: //POPB
				SP--;
				B = RAM[SP];
				break;
			case 26: //POPC
				SP--;
				C = RAM[SP];
				break;
			case 27: //PUSHA
				RAM[SP] = A;
				SP++;
				break;
			case 28: //PUSHB
				RAM[SP] = B;
				SP++;
				break;
			case 29: //PUSHC
				RAM[SP] = C;
				SP++;
				break;
			case 30: //LDBRAM
				B = RAM[PROM[addr] & 255];
				break;
			case 31: //LDCCMA
				B = PROM[PROM[addr] & 255];
				break;
			case 32: //LDCI
				C = (PROM[addr] & 255);
				break;
			case 33: //LDCIO
				C = 0;
				if (IOHDir == 0) //H in
				{
					C |= IOH;
				}
				if (IOLDir == 0) //L in
				{
					C |= IOL;
				}
				break;
			case 34: //VRA		
				VRAMMAR = (PROM[addr] & 255);
				if (VRAMToggle)
				{
					writeSurface(VRAMMAR, A, surface2);
				}
				else
				{
					writeSurface(VRAMMAR, A, surface);
				}
				break;
			case 35: //VRC
				VRAMMAR = (PROM[addr] & 255);
				if (VRAMToggle)
				{
					writeSurface(VRAMMAR, C, surface2);
				}
				else
				{
					writeSurface(VRAMMAR, C, surface);
				}				
				break;
			case 36: //VRW
				if (VRAMToggle)
				{
					writeSurface(VRAMMAR, (PROM[addr] & 255), surface2);
				}
				else
				{
					writeSurface(VRAMMAR, (PROM[addr] & 255), surface);
				}
				break;
			case 37: //VMARA
				VRAMMAR = A;
				break;
			case 38: //VMARB
				VRAMMAR = B;
				break;
			case 39: //VMARC
				VRAMMAR = C;
				break;
			case 40: //JZI JMP immediate if zero flag
				if (zeroFlag)
				{
					addr = (PROM[addr] & 255);
					goto skipIncrement;
				}
				break;
			case 41: //JZA
				if (zeroFlag)
				{
					addr = A;
					goto skipIncrement;
				}
				break;
			case 42: //JZB
				if (zeroFlag)
				{
					addr = B;
					goto skipIncrement;
				}
				break;
			case 43: //JZC
				if (zeroFlag)
				{
					addr = C;
					goto skipIncrement;
				}
				break;
			case 44: //JZRAM
				if (zeroFlag)
				{
					addr = RAM[PROM[addr] & 255];
					goto skipIncrement;
				}
				break;
			case 45: //JCI JMP immediate if carry flag
				if (carryFlag)
				{
					addr = (PROM[addr] & 255);
					goto skipIncrement;
				}
				break;
			case 46: //JCA
				if (carryFlag)
				{
					addr = A;
					goto skipIncrement;
				}
				break;
			case 47: //JCB
				if (carryFlag)
				{
					addr = B;
					goto skipIncrement;
				}
				break;
			case 48: //JCC
				if (carryFlag)
				{
					addr = C;
					goto skipIncrement;
				}
				break;
			case 49: //JCRAM
				if (carryFlag)
				{
					addr = RAM[PROM[addr] & 255];
					goto skipIncrement;
				}
				break;
			case 50: //MOVAIO
				break;
			case 51: //MOVBIO
				break;
			case 52: //MOVCIO
				break;
			case 53: //LDARAMC
				A = RAM[C];
				break;
			case 54: //MOVAB
				B = A;
				break;
			case 55: //MOVAC
				C = A;
				break;
			case 56: //MOVBA
				A = B;
				break;
			case 57:  //MOVBC
				C = B;
				break;
			case 58: //MOVCA
				A = C;
				break;
			case 59: //MOVCB
				B = C;
				break;
			case 60: //NOPS			
			case 61: //NOPM			
			case 62: //NOP
				break;
			case 63: //STA
				RAM[PROM[addr] & 255] = A;
				break;
			case 64: //STB
				RAM[PROM[addr] & 255] = B;
				break;
			case 65: //STC
				RAM[PROM[addr] & 255] = C;
				break;
			case 66: //CMP
				updateFlagsSub();
				break;
			case 67: //LDCRAM
				C = RAM[PROM[addr] & 255];
				break;
			case 68: //LCALL, arg is a CM address to jmp to
				RAM[SP] = addr;
				SP++;
				addr = PROM[PROM[addr] & 255];
				goto skipIncrement;
			case 69: //JMP indirect using arg as CM address
				addr = PROM[PROM[addr] & 255];
				goto skipIncrement;
			case 70: //JCCM
				if (carryFlag)
				{
					addr = RAM[PROM[addr] & 255];
					goto skipIncrement;
				}
				break;
			case 71: //JZCM
				if (zeroFlag)
				{
					addr = RAM[PROM[addr] & 255];
					goto skipIncrement;
				}
				break;
			case 72: //VRCC				
				if (VRAMToggle)
				{
					writeSurface(VRAMMAR, C, surface2);
				}
				else
				{
					writeSurface(VRAMMAR, C, surface);
				}
				break;
			case 73: //RJMP
				addr = addr + (PROM[addr] & 255);
				break;
			case 74: //RJMP
				addr = addr - (PROM[addr] & 255);
				break;
			case 75: //RJCI
				if (carryFlag)
				{
					addr = addr + (PROM[addr] & 255);
				}
				break;
			case 76: //RJCI
				if (carryFlag)
				{
					addr = addr - (PROM[addr] & 255);
				}
				break;
			case 77: //RJZI
				if (zeroFlag)
				{
					addr = addr + (PROM[addr] & 255);
				}
				break;
			case 78: //RJZI
				if (zeroFlag)
				{
					addr = addr - (PROM[addr] & 255);
				}
				break;
			case 79: //STARAMC
				RAM[C] = A;
				break;
			default:
				cout << "Unknown opcode: ";
				cout << opcode << endl;
			}
			addr++; //increment program counter
		}
	}
	return 0;
}