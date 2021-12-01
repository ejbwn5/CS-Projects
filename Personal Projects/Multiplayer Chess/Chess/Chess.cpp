// Chess.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "Chess.h"
#include <iostream>
#include <math.h>
#include <vector>
#include <windowsx.h>
#include <objidl.h>
#include <gdiplus.h>
#include <regex>
#include <thread>
//#define _CRTDBG_MAP_ALLOC
//#include <stdlib.h>
//#include <crtdbg.h>

using namespace Gdiplus;
#pragma comment (lib,"Gdiplus.lib")

#define MAX_LOADSTRING 100
#define WIDTH 1024
#define HEIGHT 827
// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    Promote(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    Multi(HWND, UINT, WPARAM, LPARAM);

enum pieceClass { pawn, knight, king, queen, bishop, rook };
enum occupiedStatus { unoccupied, white, black };
enum team {nobody,w, b};
enum buttons { multiplayerMenu };

string to_string(team t1)
{
	if (t1 == w)
	{
		return "White";
	}
	else if (t1 == b)
	{
		return "Black";
	}
	else
	{
		return "Unknown";
	}
}

team to_team(string s)
{
	if (s == "Black")
	{
		return b;
	}
	else if (s == "White")
	{
		return w;
	}
	else
	{
		throw exception();
	}
}

team turn;
team playerTeam;
bool multi = false;
void mBox(HWND h, string text){

	MessageBoxA(h, text.c_str(), "Notice", MB_OK);	
}

HWND hWnd, hwndMulti;
class Piece //abstract piece
{
public:
	pieceClass type;
	Piece() {};
	int x, y;
	virtual bool canMoveTo(int newX, int newY, vector<Piece*> whiteP, vector<Piece*> blackP) = 0;
	void moveTo(int newX, int newY, vector<Piece*> whiteP, vector<Piece*> blackP);
	bool dead = false;
	team t;	
};

vector<Piece*> whitePieces;
vector<Piece*> blackPieces;
int selX = -1;
int selY = -1;

int enemySelX = -1;
int enemySelY = -1;

struct whiteEnPassant
{
	int pieceX = -1;
	int pieceY = -1;
	int passY = -1;
	bool active = false;
};

struct blackEnPassant
{
	int pieceX = -1;
	int pieceY = -1;
	int passY = -1;
	bool active = false;
};

whiteEnPassant whiteenpassant;
blackEnPassant blackenpassant;

class King : public Piece
{
public:
	pieceClass type = king;
	King() { x = -1; y = -1; };
	King(int a, int b) { x = a; y = b; };
	King(int a, int b, team newT) { x = a; y = b; t = newT; };
	int x, y;
	bool canMoveTo(int newX, int newY, vector<Piece*> whiteP, vector<Piece*> blackP);	
	bool canCastle = true;
};

class Queen : public Piece
{
public:
	pieceClass type = queen;
	Queen() { x = -1; y = -1; };
	Queen(int a, int b) { x = a; y = b; };
	Queen(int a, int b, team newT) { x = a; y = b; t = newT; };
	int x, y;
	bool canMoveTo(int newX, int newY, vector<Piece*> whiteP, vector<Piece*> blackP);	
};

class Pawn : public Piece
{
public:
	pieceClass type = pawn;
	Pawn() { x = -1; y = -1; };
	Pawn(int a, int b) { x = a; y = b; };
	Pawn(int a, int b, team newT) { x = a; y = b; t = newT; };
	int x, y;
	bool canMoveTo(int newX, int newY, vector<Piece*> whiteP, vector<Piece*> blackP);
	void moveTo(int newX, int newY, vector<Piece*> whiteP, vector<Piece*> blackP);
};

class Bishop : public Piece
{
public:
	pieceClass type = bishop;
	Bishop() { x = -1; y = -1; };
	Bishop(int a, int b) { x = a; y = b; };
	Bishop(int a, int b, team newT) { x = a; y = b; t = newT; };
	int x, y;
	bool canMoveTo(int newX, int newY, vector<Piece*> whiteP, vector<Piece*> blackP);
	
};

class Knight : public Piece
{
public:
	pieceClass type = knight;
	Knight() { x = -1; y = -1; };
	Knight(int a, int b) { x = a; y = b; };
	Knight(int a, int b, team newT) { x = a; y = b; t = newT; };
	int x, y;
	bool canMoveTo(int newX, int newY, vector<Piece*> whiteP, vector<Piece*> blackP);
	

};

class Rook : public Piece
{
public:
	pieceClass type = rook;
	Rook() { x = -1; y = -1; };
	Rook(int a, int b) { x = a; y = b; };
	Rook(int a, int b, team newT) { x = a; y = b; t = newT; };
	int x, y;
	bool canMoveTo(int newX, int newY, vector<Piece*> whiteP, vector<Piece*> blackP);
	bool canCastle = true;
};


Piece *getPiece(int x, int y, vector<Piece*> whiteP, vector<Piece*> blackP)
{
	for (auto i : whiteP)
	{
		if (!static_cast<Rook*>(i)->dead)
		{
			if (static_cast<Rook*>(i)->x == x && static_cast<Rook*>(i)->y == y)
			{
				return i;
			}
		}
	}
	for (auto i : blackP)
	{
		if (!static_cast<Rook*>(i)->dead)
		{
			if (static_cast<Rook*>(i)->x == x && static_cast<Rook*>(i)->y == y)
			{
				return i;
			}
		}
	}
	return nullptr;
}

occupiedStatus isSpaceOccupied(int x, int y, vector<Piece*> whiteP, vector<Piece*> blackP)
{
	for (auto piece : whiteP)
	{
		if (!(static_cast<Rook*>(piece)->dead))
		{
			switch (static_cast<Rook*>(piece)->type)
			{
			case knight:
				if (static_cast<Knight*>(piece)->x == x && static_cast<Knight*>(piece)->y == y)
				{
					return white;
				}
				break;
			case king:
				if (static_cast<King*>(piece)->x == x && static_cast<King*>(piece)->y == y)
				{
					return white;
				}
				break;
			case queen:
				if (static_cast<Queen*>(piece)->x == x && static_cast<Queen*>(piece)->y == y)
				{
					return white;
				}
				break;
			case pawn:
				if (static_cast<Pawn*>(piece)->x == x && static_cast<Pawn*>(piece)->y == y)
				{
					return white;
				}
				break;
			case bishop:
				if (static_cast<Bishop*>(piece)->x == x && static_cast<Bishop*>(piece)->y == y)
				{
					return white;
				}
				break;
			case rook:
				if (static_cast<Rook*>(piece)->x == x && static_cast<Rook*>(piece)->y == y)
				{
					return white;
				}
				break;
			}
			
		}
	}
	for (auto piece : blackP)
	{
		if (!(static_cast<Rook*>(piece)->dead))
		{
			switch (static_cast<Rook*>(piece)->type)
			{
			case knight:
				if (static_cast<Knight*>(piece)->x == x && static_cast<Knight*>(piece)->y == y)
				{
					return black;
				}
				break;
			case king:
				if (static_cast<King*>(piece)->x == x && static_cast<King*>(piece)->y == y)
				{
					return black;
				}
				break;
			case queen:
				if (static_cast<Queen*>(piece)->x == x && static_cast<Queen*>(piece)->y == y)
				{
					return black;
				}
				break;
			case pawn:
				if (static_cast<Pawn*>(piece)->x == x && static_cast<Pawn*>(piece)->y == y)
				{
					return black;
				}
				break;
			case bishop:
				if (static_cast<Bishop*>(piece)->x == x && static_cast<Bishop*>(piece)->y == y)
				{
					return black;
				}
				break;
			case rook:
				if (static_cast<Rook*>(piece)->x == x && static_cast<Rook*>(piece)->y == y)
				{
					return black;
				}
				break;
			}

		}
	}
	return unoccupied;
}

bool detectCheck(vector<Piece*> whiteP, vector<Piece*> blackP);

bool detectImminentCheck(int x, int y, int newX, int newY)
{
	vector<Piece*> tempWhite;
	vector<Piece*> tempBlack;
	for (auto origW : whitePieces)
	{
		if (!origW->dead)
		{
			switch (static_cast<Rook*>(origW)->type)
			{
			case knight:
				tempWhite.push_back(new Knight(static_cast<Knight*>(origW)->x, static_cast<Knight*>(origW)->y, w));
				break;
			case king:
				tempWhite.push_back(new King(static_cast<King*>(origW)->x, static_cast<King*>(origW)->y, w));
				break;
			case queen:
				tempWhite.push_back(new Queen(static_cast<Queen*>(origW)->x, static_cast<Queen*>(origW)->y, w));
				break;
			case bishop:
				tempWhite.push_back(new Bishop(static_cast<Bishop*>(origW)->x, static_cast<Bishop*>(origW)->y, w));
				break;
			case pawn:
				tempWhite.push_back(new Pawn(static_cast<Pawn*>(origW)->x, static_cast<Pawn*>(origW)->y, w));
				break;
			case rook:
				tempWhite.push_back(new Rook(static_cast<Rook*>(origW)->x, static_cast<Rook*>(origW)->y, w));
				break;
			}
		}
	}

	for (auto origB : blackPieces)
	{
		if (!origB->dead)
		{
			switch (static_cast<Rook*>(origB)->type)
			{
			case knight:
				tempBlack.push_back(new Knight(static_cast<Knight*>(origB)->x, static_cast<Knight*>(origB)->y, b));
				break;
			case king:
				tempBlack.push_back(new King(static_cast<King*>(origB)->x, static_cast<King*>(origB)->y, b));
				break;
			case queen:
				tempBlack.push_back(new Queen(static_cast<Queen*>(origB)->x, static_cast<Queen*>(origB)->y, b));
				break;
			case bishop:
				tempBlack.push_back(new Bishop(static_cast<Bishop*>(origB)->x, static_cast<Bishop*>(origB)->y, b));
				break;
			case pawn:
				tempBlack.push_back(new Pawn(static_cast<Pawn*>(origB)->x, static_cast<Pawn*>(origB)->y, b));
				break;
			case rook:
				tempBlack.push_back(new Rook(static_cast<Rook*>(origB)->x, static_cast<Rook*>(origB)->y, b));
				break;
			}
		}
	}

	Piece *p = getPiece(x, y, tempWhite, tempBlack);
	p->moveTo(newX, newY, tempWhite, tempBlack);
	bool res = !detectCheck(tempWhite, tempBlack);

	while (tempWhite.size() > 0)
	{
		delete tempWhite.back();
		tempWhite.pop_back();
	}
	while (tempBlack.size() > 0)
	{
		delete tempBlack.back();
		tempBlack.pop_back();
	}

	return res;
}

bool inCheck = false;
bool actual = false;

bool King::canMoveTo(int newX, int newY, vector<Piece*> whiteP, vector<Piece*> blackP)
{
	if (abs(newX - x) <= 1 && abs(newY - y) <= 1 && !((newY - y)==0 && (newX - x)==0))
	{
		if (isSpaceOccupied(newX, newY, whiteP, blackP) == unoccupied)
		{
			return true;
		}
		else
		{
			if ((t == w && isSpaceOccupied(newX, newY, whiteP, blackP) == black) || (t == b && isSpaceOccupied(newX, newY, whiteP, blackP) == white))
			{
				return true;
			}
		}

	}
	else if (newY - y == 0 && abs(newX - x) == 2 && canCastle && !inCheck) //try castle
	{
		if (newX - x == 2) //right side
		{
			Piece *r = getPiece(8, y, whiteP, blackP);
			if (r == nullptr) return false;
			if (static_cast<Rook*>(r)->type != rook) return false;
			if (!static_cast<Rook*>(r)->canCastle) return false;
			for (int i = x + 1; i < 8; i++)
			{
				if (isSpaceOccupied(i, y, whiteP, blackP) != unoccupied) return false;
			}
			for (int i = x + 1; i < x + 3; i++)
			{
				vector<Piece*> tempWhite;
				vector<Piece*> tempBlack;
				for (auto origW : whitePieces)
				{
					if (!origW->dead)
					{
						switch (static_cast<Rook*>(origW)->type)
						{
						case knight:
							tempWhite.push_back(new Knight(static_cast<Knight*>(origW)->x, static_cast<Knight*>(origW)->y, w));
							break;
						case king:
							tempWhite.push_back(new King(static_cast<King*>(origW)->x, static_cast<King*>(origW)->y, w));
							break;
						case queen:
							tempWhite.push_back(new Queen(static_cast<Queen*>(origW)->x, static_cast<Queen*>(origW)->y, w));
							break;
						case bishop:
							tempWhite.push_back(new Bishop(static_cast<Bishop*>(origW)->x, static_cast<Bishop*>(origW)->y, w));
							break;
						case pawn:
							tempWhite.push_back(new Pawn(static_cast<Pawn*>(origW)->x, static_cast<Pawn*>(origW)->y, w));
							break;
						case rook:
							tempWhite.push_back(new Rook(static_cast<Rook*>(origW)->x, static_cast<Rook*>(origW)->y, w));
							break;
						}
					}
				}

				for (auto origB : blackPieces)
				{
					if (!origB->dead)
					{
						switch (static_cast<Rook*>(origB)->type)
						{
						case knight:
							tempBlack.push_back(new Knight(static_cast<Knight*>(origB)->x, static_cast<Knight*>(origB)->y, b));
							break;
						case king:
							tempBlack.push_back(new King(static_cast<King*>(origB)->x, static_cast<King*>(origB)->y, b));
							break;
						case queen:
							tempBlack.push_back(new Queen(static_cast<Queen*>(origB)->x, static_cast<Queen*>(origB)->y, b));
							break;
						case bishop:
							tempBlack.push_back(new Bishop(static_cast<Bishop*>(origB)->x, static_cast<Bishop*>(origB)->y, b));
							break;
						case pawn:
							tempBlack.push_back(new Pawn(static_cast<Pawn*>(origB)->x, static_cast<Pawn*>(origB)->y, b));
							break;
						case rook:
							tempBlack.push_back(new Rook(static_cast<Rook*>(origB)->x, static_cast<Rook*>(origB)->y, b));
							break;
						}
					}
				}

				Piece *tempKing = getPiece(x, y, tempWhite, tempBlack);
				tempKing->moveTo(i, y, tempWhite, tempBlack);
				if (detectCheck(tempWhite, tempBlack)) return false;

				while (tempWhite.size() > 0)
				{
					delete tempWhite.back();
					tempWhite.pop_back();
				}
				while (tempBlack.size() > 0)
				{
					delete tempBlack.back();
					tempBlack.pop_back();
				}
			}


			//all good
			r->moveTo(6, y, whiteP, blackP);
			if (multi && actual)
			{
				sendMessage("move");
				sendMessage("(" + to_string(8) + "," + to_string(y) + ")(" + to_string(6) + "," + to_string(y) + ")");
			}
			return true;

		}
		else //left side
		{
			Piece *r = getPiece(1, y, whiteP, blackP);
			if (r == nullptr) return false;
			if (static_cast<Rook*>(r)->type != rook) return false;
			if (!static_cast<Rook*>(r)->canCastle) return false;
			for (int i = x - 1; i > 1; i--)
			{
				if (isSpaceOccupied(i, y, whiteP, blackP) != unoccupied) return false;
			}
			for (int i = x - 1; i > x - 3; i--)
			{
				vector<Piece*> tempWhite;
				vector<Piece*> tempBlack;
				for (auto origW : whitePieces)
				{
					if (!origW->dead)
					{
						switch (static_cast<Rook*>(origW)->type)
						{
						case knight:
							tempWhite.push_back(new Knight(static_cast<Knight*>(origW)->x, static_cast<Knight*>(origW)->y, w));
							break;
						case king:
							tempWhite.push_back(new King(static_cast<King*>(origW)->x, static_cast<King*>(origW)->y, w));
							break;
						case queen:
							tempWhite.push_back(new Queen(static_cast<Queen*>(origW)->x, static_cast<Queen*>(origW)->y, w));
							break;
						case bishop:
							tempWhite.push_back(new Bishop(static_cast<Bishop*>(origW)->x, static_cast<Bishop*>(origW)->y, w));
							break;
						case pawn:
							tempWhite.push_back(new Pawn(static_cast<Pawn*>(origW)->x, static_cast<Pawn*>(origW)->y, w));
							break;
						case rook:
							tempWhite.push_back(new Rook(static_cast<Rook*>(origW)->x, static_cast<Rook*>(origW)->y, w));
							break;
						}
					}
				}

				for (auto origB : blackPieces)
				{
					if (!origB->dead)
					{
						switch (static_cast<Rook*>(origB)->type)
						{
						case knight:
							tempBlack.push_back(new Knight(static_cast<Knight*>(origB)->x, static_cast<Knight*>(origB)->y, b));
							break;
						case king:
							tempBlack.push_back(new King(static_cast<King*>(origB)->x, static_cast<King*>(origB)->y, b));
							break;
						case queen:
							tempBlack.push_back(new Queen(static_cast<Queen*>(origB)->x, static_cast<Queen*>(origB)->y, b));
							break;
						case bishop:
							tempBlack.push_back(new Bishop(static_cast<Bishop*>(origB)->x, static_cast<Bishop*>(origB)->y, b));
							break;
						case pawn:
							tempBlack.push_back(new Pawn(static_cast<Pawn*>(origB)->x, static_cast<Pawn*>(origB)->y, b));
							break;
						case rook:
							tempBlack.push_back(new Rook(static_cast<Rook*>(origB)->x, static_cast<Rook*>(origB)->y, b));
							break;
						}
					}
				}

				Piece *tempKing = getPiece(x, y, tempWhite, tempBlack);
				tempKing->moveTo(i, y, tempWhite, tempBlack);
				if (detectCheck(tempWhite, tempBlack)) return false;

				while (tempWhite.size() > 0)
				{
					delete tempWhite.back();
					tempWhite.pop_back();
				}
				while (tempBlack.size() > 0)
				{
					delete tempBlack.back();
					tempBlack.pop_back();
				}
			}


			//all good
			r->moveTo(4, y, whiteP, blackP);
			if (multi && actual)
			{
				sendMessage("move");
				sendMessage("(" + to_string(1) + "," + to_string(y) + ")(" + to_string(4) + "," + to_string(y) + ")");
			}
			return true;
		}

	}
	return false;
	
}

bool Rook::canMoveTo(int newX, int newY, vector<Piece*> whiteP, vector<Piece*> blackP)
{
	if (newX - x == 0)
	{
		if (newY - y != 0)
		{
			if (t == w)
			{
				if (isSpaceOccupied(newX, newY,whiteP, blackP) == unoccupied || isSpaceOccupied(newX, newY, whiteP, blackP) == black)
				{
					if (newY - y > 0)
					{
						for (int i = y+1; i < newY; i++)
						{
							if (isSpaceOccupied(newX, i, whiteP, blackP) != unoccupied)
							{
								return false;
							}
						}
						return true;
					}
					else
					{
						for (int i = y-1; i > newY; i--)
						{
							if (isSpaceOccupied(newX, i, whiteP, blackP) != unoccupied)
							{
								return false;
							}
						}
						return true;
					}
				}
			}
			else
			{
				if (isSpaceOccupied(newX, newY, whiteP, blackP) == unoccupied || isSpaceOccupied(newX, newY, whiteP, blackP) == white)
				{
					if (newY - y > 0)
					{
						for (int i = y+1; i < newY; i++)
						{
							if (isSpaceOccupied(newX, i, whiteP, blackP) != unoccupied)
							{
								return false;
							}
						}
						return true;
					}
					else
					{
						for (int i = y-1; i > newY; i--)
						{
							if (isSpaceOccupied(newX, i, whiteP, blackP) != unoccupied)
							{
								return false;
							}
						}
						return true;
					}
				}
			}
		}
	}
	else if (newY - y == 0)
	{
		if (newX - x != 0)
		{
			if (t == w)
			{
				if (isSpaceOccupied(newX, newY, whiteP, blackP) == unoccupied || isSpaceOccupied(newX, newY, whiteP, blackP) == black)
				{
					if (newX - x > 0)
					{
						for (int i = x + 1; i < newX; i++)
						{
							if (isSpaceOccupied(i, newY, whiteP, blackP) != unoccupied)
							{
								return false;
							}
						}
						return true;
					}
					else
					{
						for (int i = x - 1; i > newX; i--)
						{
							if (isSpaceOccupied(i, newY, whiteP, blackP) != unoccupied)
							{
								return false;
							}
						}
						return true;
					}
				}
			}
			else
			{
				if (isSpaceOccupied(newX, newY, whiteP, blackP) == unoccupied || isSpaceOccupied(newX, newY, whiteP, blackP) == white)
				{
					if (newX - x > 0)
					{
						for (int i = x + 1; i < newX; i++)
						{
							if (isSpaceOccupied(i, newY, whiteP, blackP) != unoccupied)
							{
								return false;
							}
						}
						return true;
					}
					else
					{
						for (int i = x - 1; i > newX; i--)
						{
							if (isSpaceOccupied(i, newY, whiteP, blackP) != unoccupied)
							{
								return false;
							}
						}
						return true;
					}
				}
			}
		}
	}
	return false;
}

bool Knight::canMoveTo(int newX, int newY, vector<Piece*> whiteP, vector<Piece*> blackP)
{
	if (pow(newX-x, 2) + pow(newY-y, 2)==5)
	{
		if (t == w)
		{
			if (isSpaceOccupied(newX, newY, whiteP, blackP) == unoccupied || isSpaceOccupied(newX, newY, whiteP, blackP) == black)
			{
				return true;
			}
		}
		else
		{
			if (isSpaceOccupied(newX, newY, whiteP, blackP) == unoccupied || isSpaceOccupied(newX, newY, whiteP, blackP) == white)
			{
				return true;
			}
		}
	}
	return false;
}


bool Pawn::canMoveTo(int newX, int newY, vector<Piece*> whiteP, vector<Piece*> blackP)
{
	if (newX - x == 0)
	{
		if (t == w && (newY - y) == 1)
		{
			if (isSpaceOccupied(newX, newY, whiteP, blackP) == unoccupied)
			{
				return true;
			}
		}
		else if (t == b && (newY - y) == -1)
		{
			if (isSpaceOccupied(newX, newY, whiteP, blackP) == unoccupied)
			{
				return true;
			}			
		}
		else if ((t == w && y == 2) || (t == b && y == 7))
		{
			if (t == w && (newY - y) == 2)
			{
				if (isSpaceOccupied(newX, newY, whiteP, blackP) == unoccupied && isSpaceOccupied(x, y+(newY-y)/2, whiteP, blackP) == unoccupied)
				{
					return true;
				}
			}
			else if (t == b && (newY - y) == -2)
			{
				if (isSpaceOccupied(newX, newY, whiteP, blackP) == unoccupied && isSpaceOccupied(x, y + (newY - y) / 2, whiteP, blackP) == unoccupied)
				{
					return true;
				}
			}
		}
	}
	else if (abs(newX-x)==1)
	{
		if (t == w && (newY - y) == 1)
		{
			if (isSpaceOccupied(newX, newY, whiteP, blackP) == black)
			{
				return true;
			}
			else if(blackenpassant.active && newX == blackenpassant.pieceX && blackenpassant.passY == newY && actual)
			{
				static_cast<Rook*>(getPiece(blackenpassant.pieceX, blackenpassant.pieceY, whiteP, blackP))->dead = true;
				if (multi) {
					sendMessage("kill");
					sendMessage("(" + to_string(blackenpassant.pieceX) + "," + to_string(blackenpassant.pieceY) + ")");
				}
				return true;
			}
		}
		else if (t == b && (newY - y) == -1)
		{
			if (isSpaceOccupied(newX, newY, whiteP, blackP) == white)
			{
				return true;
			}
			else if (whiteenpassant.active && newX == whiteenpassant.pieceX && whiteenpassant.passY == newY && actual)
			{
				static_cast<Rook*>(getPiece(whiteenpassant.pieceX, whiteenpassant.pieceY, whiteP, blackP))->dead = true;
				if (multi) {
					sendMessage("kill");
					sendMessage("(" + to_string(whiteenpassant.pieceX) + "," + to_string(whiteenpassant.pieceY) + ")");
				}
				return true;
			}
		}
	}
	return false;
}

bool Bishop::canMoveTo(int newX, int newY, vector<Piece*> whiteP, vector<Piece*> blackP)
{
	int dX = newX - x;
	int dY = newY - y;
	if (dX == 0 && dY == 0) return false;
	if (abs(dX) != abs(dY)) return false;
	if (dX > 0)
	{
		if (dY > 0)
		{
			for (int i = 1; i < dX; i++)
			{
				if (isSpaceOccupied(x + i, y + i, whiteP, blackP) != unoccupied) return false;
			}
			if (t == w)
			{
				if (isSpaceOccupied(newX, newY, whiteP, blackP) == unoccupied || isSpaceOccupied(newX, newY, whiteP, blackP) == black)
				{
					return true;
				}
			}
			else
			{
				if (isSpaceOccupied(newX, newY, whiteP, blackP) == unoccupied || isSpaceOccupied(newX, newY, whiteP, blackP) == white)
				{
					return true;
				}
			}
		}
		else
		{
			for (int i = 1; i < dX; i++)
			{
				if (isSpaceOccupied(x + i, y - i, whiteP, blackP) != unoccupied) return false;
			}
			if (t == w)
			{
				if (isSpaceOccupied(newX, newY, whiteP, blackP) == unoccupied || isSpaceOccupied(newX, newY, whiteP, blackP) == black)
				{
					return true;
				}
			}
			else
			{
				if (isSpaceOccupied(newX, newY, whiteP, blackP) == unoccupied || isSpaceOccupied(newX, newY, whiteP, blackP) == white)
				{
					return true;
				}
			}
		}
	}
	else
	{
		if (dY > 0)
		{
			for (int i = 1; i < abs(dX); i++)
			{
				if (isSpaceOccupied(x - i, y + i, whiteP, blackP) != unoccupied) return false;
			}
			if (t == w)
			{
				if (isSpaceOccupied(newX, newY, whiteP, blackP) == unoccupied || isSpaceOccupied(newX, newY, whiteP, blackP) == black)
				{
					return true;
				}
			}
			else
			{
				if (isSpaceOccupied(newX, newY, whiteP, blackP) == unoccupied || isSpaceOccupied(newX, newY, whiteP, blackP) == white)
				{
					return true;
				}
			}
		}
		else
		{
			for (int i = 1; i < abs(dX); i++)
			{
				if (isSpaceOccupied(x - i, y - i, whiteP, blackP) != unoccupied) return false;
			}
			if (t == w)
			{
				if (isSpaceOccupied(newX, newY, whiteP, blackP) == unoccupied || isSpaceOccupied(newX, newY, whiteP, blackP) == black)
				{
					return true;
				}
			}
			else
			{
				if (isSpaceOccupied(newX, newY, whiteP, blackP) == unoccupied || isSpaceOccupied(newX, newY, whiteP, blackP) == white)
				{
					return true;
				}
			}
		}
	}
	return false;
}



bool Queen::canMoveTo(int newX, int newY, vector<Piece*> whiteP, vector<Piece*> blackP)
{
	if (newX - x == 0)
	{
		if (newY - y != 0)
		{
			if (t == w)
			{
				if (isSpaceOccupied(newX, newY, whiteP, blackP) == unoccupied || isSpaceOccupied(newX, newY, whiteP, blackP) == black)
				{
					if (newY - y > 0)
					{
						for (int i = y + 1; i < newY; i++)
						{
							if (isSpaceOccupied(newX, i, whiteP, blackP) != unoccupied)
							{
								return false;
							}
						}

						return true;
					}
					else
					{
						for (int i = y - 1; i > newY; i--)
						{
							if (isSpaceOccupied(newX, i, whiteP, blackP) != unoccupied)
							{
								return false;
							}
						}
						return true;
					}
				}
			}
			else
			{
				if (isSpaceOccupied(newX, newY, whiteP, blackP) == unoccupied || isSpaceOccupied(newX, newY, whiteP, blackP) == white)
				{
					if (newY - y > 0)
					{
						for (int i = y + 1; i < newY; i++)
						{
							if (isSpaceOccupied(newX, i, whiteP, blackP) != unoccupied)
							{
								return false;
							}
						}
						return true;
					}
					else
					{
						for (int i = y - 1; i > newY; i--)
						{
							if (isSpaceOccupied(newX, i, whiteP, blackP) != unoccupied)
							{
								return false;
							}
						}
						return true;
					}
				}
			}
		}
	}
	else if (newY - y == 0)
	{
		if (newX - x != 0)
		{
			if (t == w)
			{
				if (isSpaceOccupied(newX, newY, whiteP, blackP) == unoccupied || isSpaceOccupied(newX, newY, whiteP, blackP) == black)
				{
					if (newX - x > 0)
					{
						for (int i = x + 1; i < newX; i++)
						{
							if (isSpaceOccupied(i, newY, whiteP, blackP) != unoccupied)
							{
								return false;
							}
						}
						return true;
					}
					else
					{
						for (int i = x - 1; i > newX; i--)
						{
							if (isSpaceOccupied(i, newY, whiteP, blackP) != unoccupied)
							{
								return false;
							}
						}
						return true;
					}
				}
			}
			else
			{
				if (isSpaceOccupied(newX, newY, whiteP, blackP) == unoccupied || isSpaceOccupied(newX, newY, whiteP, blackP) == white)
				{
					if (newX - x > 0)
					{
						for (int i = x + 1; i < newX; i++)
						{
							if (isSpaceOccupied(i, newY, whiteP, blackP) != unoccupied)
							{
								return false;
							}
						}
						return true;
					}
					else
					{
						for (int i = x - 1; i > newX; i--)
						{
							if (isSpaceOccupied(i, newY, whiteP, blackP) != unoccupied)
							{
								return false;
							}
						}
						return true;
					}
				}
			}
		}
	}

	int dX = newX - x;
	int dY = newY - y;
	if (dX == 0 && dY == 0) return false;
	if (abs(dX) != abs(dY)) return false;
	if (dX > 0)
	{
		if (dY > 0)
		{
			for (int i = 1; i < dX; i++)
			{
				if (isSpaceOccupied(x + i, y + i, whiteP, blackP) != unoccupied) return false;
			}
			if (t == w)
			{
				if (isSpaceOccupied(newX, newY, whiteP, blackP) == unoccupied || isSpaceOccupied(newX, newY, whiteP, blackP) == black)
				{
					return true;
				}
			}
			else
			{
				if (isSpaceOccupied(newX, newY, whiteP, blackP) == unoccupied || isSpaceOccupied(newX, newY, whiteP, blackP) == white)
				{
					return true;
				}
			}
		}
		else
		{
			for (int i = 1; i < dX; i++)
			{
				if (isSpaceOccupied(x + i, y - i, whiteP, blackP) != unoccupied) return false;
			}
			if (t == w)
			{
				if (isSpaceOccupied(newX, newY, whiteP, blackP) == unoccupied || isSpaceOccupied(newX, newY, whiteP, blackP) == black)
				{
					return true;
				}
			}
			else
			{
				if (isSpaceOccupied(newX, newY, whiteP, blackP) == unoccupied || isSpaceOccupied(newX, newY, whiteP, blackP) == white)
				{
					return true;
				}
			}
		}
	}
	else
	{
		if (dY > 0)
		{
			for (int i = 1; i < abs(dX); i++)
			{
				if (isSpaceOccupied(x - i, y + i, whiteP, blackP) != unoccupied) return false;
			}
			if (t == w)
			{
				if (isSpaceOccupied(newX, newY, whiteP, blackP) == unoccupied || isSpaceOccupied(newX, newY, whiteP, blackP) == black)
				{
					return true;
				}
			}
			else
			{
				if (isSpaceOccupied(newX, newY, whiteP, blackP) == unoccupied || isSpaceOccupied(newX, newY, whiteP, blackP) == white)
				{
					return true;
				}
			}
		}
		else
		{
			for (int i = 1; i < abs(dX); i++)
			{
				if (isSpaceOccupied(x - i, y - i, whiteP, blackP) != unoccupied) return false;
			}
			if (t == w)
			{
				if (isSpaceOccupied(newX, newY, whiteP, blackP) == unoccupied || isSpaceOccupied(newX, newY, whiteP, blackP) == black)
				{
					return true;
				}
			}
			else
			{
				if (isSpaceOccupied(newX, newY, whiteP, blackP) == unoccupied || isSpaceOccupied(newX, newY, whiteP, blackP) == white)
				{
					return true;
				}
			}
		}
	}
	

	return false;
}





void Pawn::moveTo(int newX, int newY, vector<Piece*> whiteP, vector<Piece*> blackP)
{
	Piece *p = getPiece(newX, newY, whiteP, blackP);
	if (abs(newY - y) == 2)
	{
		//en passant activates
		if (t == w)
		{
			whiteenpassant.active = true;
			whiteenpassant.pieceX = newX;
			whiteenpassant.pieceY = newY;
			whiteenpassant.passY = newY-1;
		}
		else
		{
			blackenpassant.active = true;
			blackenpassant.pieceX = newX;
			blackenpassant.pieceY = newY;
			blackenpassant.passY = newY + 1;
		}
	}
	if (p != nullptr)
	{	
		static_cast<Rook*>(p)->dead = true;
	}
	x = newX;
	y = newY;

}

void Piece::moveTo(int newX, int newY, vector<Piece*> whiteP, vector<Piece*> blackP)
{
	Piece *p = getPiece(newX, newY, whiteP, blackP);
	if (p != nullptr)
	{
		static_cast<Rook*>(p)->dead = true;
	}
	static_cast<Rook*>(this)->x = newX;
	static_cast<Rook*>(this)->y = newY;
}



struct myMove
{
	int initX;
	int initY;
	int endX;
	int endY;
};





bool detectCheck(vector<Piece*> whiteP, vector<Piece*> blackP)
{
	if (turn == w)
	{
		int x, y;
		for (auto i : whiteP)
		{
			if (static_cast<Rook*>(i)->type == king)
			{
				x = static_cast<Rook*>(i)->x;
				y = static_cast<Rook*>(i)->y;
				break;
			}
		}
		for (auto i : blackP)
		{
			if (!static_cast<Rook*>(i)->dead)
			{
				switch (static_cast<Rook*>(i)->type)
				{
				case knight:
					if (static_cast<Knight*>(i)->canMoveTo(x, y, whiteP, blackP))
						return true;
					break;
				case king:
					if (static_cast<King*>(i)->canMoveTo(x, y, whiteP, blackP))
						return true;
					break;
				case pawn:
					if (static_cast<Pawn*>(i)->canMoveTo(x, y, whiteP, blackP))
						return true;
					break;
				case bishop:
					if (static_cast<Bishop*>(i)->canMoveTo(x, y, whiteP, blackP))
						return true;
					break;
				case rook:
					if (static_cast<Rook*>(i)->canMoveTo(x, y, whiteP, blackP))
						return true;
					break;
				case queen:
					if (static_cast<Queen*>(i)->canMoveTo(x, y, whiteP, blackP))
						return true;
					break;
				}
			}
			
		}
	}
	else
	{
		int x, y;
		for (auto i : blackP)
		{
			if (static_cast<Rook*>(i)->type == king)
			{
				x = static_cast<Rook*>(i)->x;
				y = static_cast<Rook*>(i)->y;
				break;
			}
		}
		for (auto i : whiteP)
		{
			if (!static_cast<Rook*>(i)->dead)
			{
				switch (static_cast<Rook*>(i)->type)
				{
				case knight:
					if (static_cast<Knight*>(i)->canMoveTo(x, y, whiteP, blackP))
						return true;
					break;
				case king:
					if (static_cast<King*>(i)->canMoveTo(x, y, whiteP, blackP))
						return true;
					break;
				case pawn:
					if (static_cast<Pawn*>(i)->canMoveTo(x, y, whiteP, blackP))
						return true;
					break;
				case bishop:
					if (static_cast<Bishop*>(i)->canMoveTo(x, y, whiteP, blackP))
						return true;
					break;
				case rook:
					if (static_cast<Rook*>(i)->canMoveTo(x, y, whiteP, blackP))
						return true;
					break;
				case queen:
					if (static_cast<Queen*>(i)->canMoveTo(x, y, whiteP, blackP))
						return true;
					break;
				}
			}
		}
	}
	return false;
}

vector<myMove> detectCheckmate()
{
	actual = false;
	vector<myMove> moveSet;
	if (turn == w)
	{
		for (auto p : whitePieces)
		{
			if (!static_cast<Rook*>(p)->dead)
			{
				for (int x = 1; x < 9; x++)
				{
					for (int y = 1; y < 9; y++)
					{
						vector<Piece*> tempWhite;
						vector<Piece*> tempBlack;
						for (auto origW : whitePieces)
						{
							if (!origW->dead)
							{
								switch (static_cast<Rook*>(origW)->type)
								{
								case knight:
									tempWhite.push_back(new Knight(static_cast<Knight*>(origW)->x, static_cast<Knight*>(origW)->y, w));
									break;
								case king:
									tempWhite.push_back(new King(static_cast<King*>(origW)->x, static_cast<King*>(origW)->y, w));
									break;
								case queen:
									tempWhite.push_back(new Queen(static_cast<Queen*>(origW)->x, static_cast<Queen*>(origW)->y, w));
									break;
								case bishop:
									tempWhite.push_back(new Bishop(static_cast<Bishop*>(origW)->x, static_cast<Bishop*>(origW)->y, w));
									break;
								case pawn:
									tempWhite.push_back(new Pawn(static_cast<Pawn*>(origW)->x, static_cast<Pawn*>(origW)->y, w));
									break;
								case rook:
									tempWhite.push_back(new Rook(static_cast<Rook*>(origW)->x, static_cast<Rook*>(origW)->y, w));
									break;
								}
							}
						}

						for (auto origB : blackPieces)
						{
							if (!origB->dead)
							{
								switch (static_cast<Rook*>(origB)->type)
								{
								case knight:
									tempBlack.push_back(new Knight(static_cast<Knight*>(origB)->x, static_cast<Knight*>(origB)->y, b));
									break;
								case king:
									tempBlack.push_back(new King(static_cast<King*>(origB)->x, static_cast<King*>(origB)->y, b));
									break;
								case queen:
									tempBlack.push_back(new Queen(static_cast<Queen*>(origB)->x, static_cast<Queen*>(origB)->y, b));
									break;
								case bishop:
									tempBlack.push_back(new Bishop(static_cast<Bishop*>(origB)->x, static_cast<Bishop*>(origB)->y, b));
									break;
								case pawn:
									tempBlack.push_back(new Pawn(static_cast<Pawn*>(origB)->x, static_cast<Pawn*>(origB)->y, b));
									break;
								case rook:
									tempBlack.push_back(new Rook(static_cast<Rook*>(origB)->x, static_cast<Rook*>(origB)->y, b));
									break;
								}
							}
						}

						switch (static_cast<Rook*>(p)->type)
						{
						case knight:
							if (static_cast<Knight*>(p)->canMoveTo(x, y, tempWhite, tempBlack))
							{
								Piece *tempPiece = getPiece(static_cast<Knight*>(p)->x, static_cast<Knight*>(p)->y, tempWhite, tempBlack);
								static_cast<Knight*>(tempPiece)->moveTo(x, y, tempWhite, tempBlack);
								if (!detectCheck(tempWhite, tempBlack))
								{
									myMove newPossMove;
									newPossMove.initX = static_cast<Rook*>(p)->x;
									newPossMove.initY = static_cast<Rook*>(p)->y;
									newPossMove.endX = x;
									newPossMove.endY = y;
									moveSet.push_back(newPossMove);
								}
							}
							break;
						case king:
							if (static_cast<King*>(p)->canMoveTo(x, y, tempWhite, tempBlack))
							{
								Piece *tempPiece = getPiece(static_cast<King*>(p)->x, static_cast<King*>(p)->y, tempWhite, tempBlack);
								static_cast<King*>(tempPiece)->moveTo(x, y, tempWhite, tempBlack);
								if (!detectCheck(tempWhite, tempBlack))
								{
									myMove newPossMove;
									newPossMove.initX = static_cast<King*>(p)->x;
									newPossMove.initY = static_cast<King*>(p)->y;
									newPossMove.endX = x;
									newPossMove.endY = y;
									moveSet.push_back(newPossMove);
								}
							}
							break;
						case pawn:							
							if (static_cast<Pawn*>(p)->canMoveTo(x, y, tempWhite, tempBlack))
							{
								Piece *tempPiece = getPiece(static_cast<Pawn*>(p)->x, static_cast<Pawn*>(p)->y, tempWhite, tempBlack);								
								static_cast<Pawn*>(tempPiece)->moveTo(x, y, tempWhite, tempBlack);
								if (!detectCheck(tempWhite, tempBlack))
								{
									myMove newPossMove;
									newPossMove.initX = static_cast<Pawn*>(p)->x;
									newPossMove.initY = static_cast<Pawn*>(p)->y;
									newPossMove.endX = x;
									newPossMove.endY = y;
									moveSet.push_back(newPossMove);
								}
							}
							break;
						case bishop:
							if (static_cast<Bishop*>(p)->canMoveTo(x, y, tempWhite, tempBlack))
							{
								Piece *tempPiece = getPiece(static_cast<Bishop*>(p)->x, static_cast<Bishop*>(p)->y, tempWhite, tempBlack);
								static_cast<Bishop*>(tempPiece)->moveTo(x, y, tempWhite, tempBlack);
								if (!detectCheck(tempWhite, tempBlack))
								{
									myMove newPossMove;
									newPossMove.initX = static_cast<Bishop*>(p)->x;
									newPossMove.initY = static_cast<Bishop*>(p)->y;
									newPossMove.endX = x;
									newPossMove.endY = y;
									moveSet.push_back(newPossMove);
								}
							}
							break;
						case rook:
							if (static_cast<Rook*>(p)->canMoveTo(x, y, tempWhite, tempBlack))
							{
								Piece *tempPiece = getPiece(static_cast<Rook*>(p)->x, static_cast<Rook*>(p)->y, tempWhite, tempBlack);
								static_cast<Rook*>(tempPiece)->moveTo(x, y, tempWhite, tempBlack);
								if (!detectCheck(tempWhite, tempBlack))
								{
									myMove newPossMove;
									newPossMove.initX = static_cast<Rook*>(p)->x;
									newPossMove.initY = static_cast<Rook*>(p)->y;
									newPossMove.endX = x;
									newPossMove.endY = y;
									moveSet.push_back(newPossMove);
								}
							}
							break;
						case queen:
							if (static_cast<Queen*>(p)->canMoveTo(x, y, tempWhite, tempBlack))
							{
								Piece *tempPiece = getPiece(static_cast<Queen*>(p)->x, static_cast<Queen*>(p)->y, tempWhite, tempBlack);
								static_cast<Queen*>(tempPiece)->moveTo(x, y, tempWhite, tempBlack);
								if (!detectCheck(tempWhite, tempBlack))
								{
									myMove newPossMove;
									newPossMove.initX = static_cast<Queen*>(p)->x;
									newPossMove.initY = static_cast<Queen*>(p)->y;
									newPossMove.endX = x;
									newPossMove.endY = y;
									moveSet.push_back(newPossMove);
								}
							}
							break;
						}
						while (tempWhite.size() > 0)
						{
							delete tempWhite.back();
							tempWhite.pop_back();
						}
						while (tempBlack.size() > 0)
						{
							delete tempBlack.back();
							tempBlack.pop_back();
						}
					}
				}
			}
		}
	}
	else if (turn == b)
	{
		for (auto p : blackPieces)
		{
			if (!static_cast<Rook*>(p)->dead)
			{
				for (int x = 1; x < 9; x++)
				{
					for (int y = 1; y < 9; y++)
					{
						vector<Piece*> tempWhite;
						vector<Piece*> tempBlack;
						for (auto origW : whitePieces)
						{
							if (!origW->dead)
							{
								switch (static_cast<Rook*>(origW)->type)
								{
								case knight:
									tempWhite.push_back(new Knight(static_cast<Knight*>(origW)->x, static_cast<Knight*>(origW)->y, w));
									break;
								case king:
									tempWhite.push_back(new King(static_cast<King*>(origW)->x, static_cast<King*>(origW)->y, w));
									break;
								case queen:
									tempWhite.push_back(new Queen(static_cast<Queen*>(origW)->x, static_cast<Queen*>(origW)->y, w));
									break;
								case bishop:
									tempWhite.push_back(new Bishop(static_cast<Bishop*>(origW)->x, static_cast<Bishop*>(origW)->y, w));
									break;
								case pawn:
									tempWhite.push_back(new Pawn(static_cast<Pawn*>(origW)->x, static_cast<Pawn*>(origW)->y, w));
									break;
								case rook:
									tempWhite.push_back(new Rook(static_cast<Rook*>(origW)->x, static_cast<Rook*>(origW)->y, w));
									break;
								}
							}
						}

						for (auto origB : blackPieces)
						{
							if (!origB->dead)
							{
								switch (static_cast<Rook*>(origB)->type)
								{
								case knight:
									tempBlack.push_back(new Knight(static_cast<Knight*>(origB)->x, static_cast<Knight*>(origB)->y, b));
									break;
								case king:
									tempBlack.push_back(new King(static_cast<King*>(origB)->x, static_cast<King*>(origB)->y, b));
									break;
								case queen:
									tempBlack.push_back(new Queen(static_cast<Queen*>(origB)->x, static_cast<Queen*>(origB)->y, b));
									break;
								case bishop:
									tempBlack.push_back(new Bishop(static_cast<Bishop*>(origB)->x, static_cast<Bishop*>(origB)->y, b));
									break;
								case pawn:
									tempBlack.push_back(new Pawn(static_cast<Pawn*>(origB)->x, static_cast<Pawn*>(origB)->y, b));
									break;
								case rook:
									tempBlack.push_back(new Rook(static_cast<Rook*>(origB)->x, static_cast<Rook*>(origB)->y, b));
									break;
								}
							}
						}

						switch (static_cast<Rook*>(p)->type)
						{
						case knight:
							if (static_cast<Knight*>(p)->canMoveTo(x, y, tempWhite, tempBlack))
							{
								Piece *tempPiece = getPiece(static_cast<Knight*>(p)->x, static_cast<Knight*>(p)->y, tempWhite, tempBlack);
								static_cast<Knight*>(tempPiece)->moveTo(x, y, tempWhite, tempBlack);
								if (!detectCheck(tempWhite, tempBlack))
								{
									myMove newPossMove;
									newPossMove.initX = static_cast<Rook*>(p)->x;
									newPossMove.initY = static_cast<Rook*>(p)->y;
									newPossMove.endX = x;
									newPossMove.endY = y;
									moveSet.push_back(newPossMove);
								}
							}
							break;
						case king:
							if (static_cast<King*>(p)->canMoveTo(x, y, tempWhite, tempBlack))
							{
								Piece *tempPiece = getPiece(static_cast<King*>(p)->x, static_cast<King*>(p)->y, tempWhite, tempBlack);
								static_cast<King*>(tempPiece)->moveTo(x, y, tempWhite, tempBlack);
								if (!detectCheck(tempWhite, tempBlack))
								{
									myMove newPossMove;
									newPossMove.initX = static_cast<King*>(p)->x;
									newPossMove.initY = static_cast<King*>(p)->y;
									newPossMove.endX = x;
									newPossMove.endY = y;
									moveSet.push_back(newPossMove);
								}
							}
							break;
						case pawn:
							if (static_cast<Pawn*>(p)->canMoveTo(x, y, tempWhite, tempBlack))
							{
								Piece *tempPiece = getPiece(static_cast<Pawn*>(p)->x, static_cast<Pawn*>(p)->y, tempWhite, tempBlack);
								static_cast<Pawn*>(tempPiece)->moveTo(x, y, tempWhite, tempBlack);
								if (!detectCheck(tempWhite, tempBlack))
								{
									myMove newPossMove;
									newPossMove.initX = static_cast<Pawn*>(p)->x;
									newPossMove.initY = static_cast<Pawn*>(p)->y;
									newPossMove.endX = x;
									newPossMove.endY = y;
									moveSet.push_back(newPossMove);
								}
							}
							break;
						case bishop:
							if (static_cast<Bishop*>(p)->canMoveTo(x, y, tempWhite, tempBlack))
							{
								Piece *tempPiece = getPiece(static_cast<Bishop*>(p)->x, static_cast<Bishop*>(p)->y, tempWhite, tempBlack);
								static_cast<Bishop*>(tempPiece)->moveTo(x, y, tempWhite, tempBlack);
								if (!detectCheck(tempWhite, tempBlack))
								{
									myMove newPossMove;
									newPossMove.initX = static_cast<Bishop*>(p)->x;
									newPossMove.initY = static_cast<Bishop*>(p)->y;
									newPossMove.endX = x;
									newPossMove.endY = y;
									moveSet.push_back(newPossMove);
								}
							}
							break;
						case rook:
							if (static_cast<Rook*>(p)->canMoveTo(x, y, tempWhite, tempBlack))
							{
								Piece *tempPiece = getPiece(static_cast<Rook*>(p)->x, static_cast<Rook*>(p)->y, tempWhite, tempBlack);
								static_cast<Rook*>(tempPiece)->moveTo(x, y, tempWhite, tempBlack);
								if (!detectCheck(tempWhite, tempBlack))
								{
									myMove newPossMove;
									newPossMove.initX = static_cast<Rook*>(p)->x;
									newPossMove.initY = static_cast<Rook*>(p)->y;
									newPossMove.endX = x;
									newPossMove.endY = y;
									moveSet.push_back(newPossMove);
								}
							}
							break;
						case queen:
							if (static_cast<Queen*>(p)->canMoveTo(x, y, tempWhite, tempBlack))
							{
								Piece *tempPiece = getPiece(static_cast<Queen*>(p)->x, static_cast<Queen*>(p)->y, tempWhite, tempBlack);
								static_cast<Queen*>(tempPiece)->moveTo(x, y, tempWhite, tempBlack);
								if (!detectCheck(tempWhite, tempBlack))
								{
									myMove newPossMove;
									newPossMove.initX = static_cast<Queen*>(p)->x;
									newPossMove.initY = static_cast<Queen*>(p)->y;
									newPossMove.endX = x;
									newPossMove.endY = y;
									moveSet.push_back(newPossMove);
								}
							}
							break;
						}
						while (tempWhite.size() > 0)
						{
							delete tempWhite.back();
							tempWhite.pop_back();
						}
						while (tempBlack.size() > 0)
						{
							delete tempBlack.back();
							tempBlack.pop_back();
						}
					}
				}
			}
		}
	}
	return moveSet;
}


bool DEBUG = false;
void initBoard()
{
	while (whitePieces.size()>0)
	{
		delete whitePieces.back();
		whitePieces.pop_back();
	}
	while (blackPieces.size()>0)
	{
		delete blackPieces.back();
		blackPieces.pop_back();
	}
	selX = -1;
	selY = -1;
	turn = w;	
	if (!DEBUG)
	{
		whitePieces.push_back(new Rook(1, 1, w));
		whitePieces.push_back(new Knight(2, 1, w));
		whitePieces.push_back(new Bishop(3, 1, w));
		whitePieces.push_back(new Queen(4, 1, w));
		whitePieces.push_back(new King(5, 1, w));
		whitePieces.push_back(new Bishop(6, 1, w));
		whitePieces.push_back(new Knight(7, 1, w));
		whitePieces.push_back(new Rook(8, 1, w));
		for (int i = 1; i < 9; i++)
		{
			whitePieces.push_back(new Pawn(i, 2, w));
		}

		blackPieces.push_back(new Rook(1, 8, b));
		blackPieces.push_back(new Knight(2, 8, b));
		blackPieces.push_back(new Bishop(3, 8, b));
		blackPieces.push_back(new Queen(4, 8, b));
		blackPieces.push_back(new King(5, 8, b));
		blackPieces.push_back(new Bishop(6, 8, b));
		blackPieces.push_back(new Knight(7, 8, b));
		blackPieces.push_back(new Rook(8, 8, b));
		for (int i = 1; i < 9; i++)
		{
			blackPieces.push_back(new Pawn(i, 7, b));
		}
	}
	else
	{
		blackPieces.push_back(new King(5, 8, b));
		whitePieces.push_back(new King(5, 1, w));		
		whitePieces.push_back(new Rook(1, 1, w));		
		whitePieces.push_back(new Bishop(7, 4, w));
		blackPieces.push_back(new Rook(1, 8, b));
		blackPieces.push_back(new Pawn(8, 5, b));
	}
}


int screenX = -1;
int screenY = -1;

vector<myMove> forcedMoves;
void toggleTurn()
{
	if (turn == w)
	{
		turn = b;
	}
	else
	{
		turn = w;
	}
	actual = false;
	inCheck = detectCheck(whitePieces, blackPieces);
	forcedMoves = detectCheckmate();
	if (inCheck)
	{
		
		//mBox(hWnd, to_string(forcedMoves.size()));
		if (forcedMoves.size() == 0)
		{
			mBox(hWnd, "Checkmate");
			turn = nobody;
		}
		else
		{
			mBox(hWnd, "Check");
		}
		
	}
	else
	{
		//mBox(hWnd, to_string(forcedMoves.size()));
		if (forcedMoves.size() == 0)
		{
			mBox(hWnd, "Draw");
			turn = nobody;
		}
	}
}

int promoteChoice;
int promoteCoordsX, promoteCoordsY;
void promote()
{
	Piece *p = getPiece(promoteCoordsX, promoteCoordsY, whitePieces, blackPieces);
	switch (promoteChoice)
	{
	case 0:
		if (static_cast<Rook*>(p)->t == w)
		{
			for (int i = 0; i<16; i++)
			{
				if (static_cast<Rook*>(whitePieces.at(i))->x == promoteCoordsX && static_cast<Rook*>(whitePieces.at(i))->y == promoteCoordsY)
				{
					whitePieces.erase(whitePieces.begin() + i);
					whitePieces.push_back(new Rook(promoteCoordsX, promoteCoordsY, w));
					break;
				}
			}
		}
		else
		{
			for (int i = 0; i<16; i++)
			{
				if (static_cast<Rook*>(blackPieces.at(i))->x == promoteCoordsX && static_cast<Rook*>(blackPieces.at(i))->y == promoteCoordsY)
				{
					blackPieces.erase(blackPieces.begin() + i);
					blackPieces.push_back(new Rook(promoteCoordsX, promoteCoordsY, b));
					break;
				}
			}
		}
		break;
	case 1:
		if (static_cast<Rook*>(p)->t == w)
		{
			for (int i = 0; i<16; i++)
			{
				if (static_cast<Rook*>(whitePieces.at(i))->x == promoteCoordsX && static_cast<Rook*>(whitePieces.at(i))->y == promoteCoordsY)
				{
					whitePieces.erase(whitePieces.begin() + i);
					whitePieces.push_back(new Bishop(promoteCoordsX, promoteCoordsY, w));
					break;
				}
			}
		}
		else
		{
			for (int i = 0; i<16; i++)
			{
				if (static_cast<Rook*>(blackPieces.at(i))->x == promoteCoordsX && static_cast<Rook*>(blackPieces.at(i))->y == promoteCoordsY)
				{
					blackPieces.erase(blackPieces.begin() + i);
					blackPieces.push_back(new Bishop(promoteCoordsX, promoteCoordsY, b));
					break;
				}
			}
		}
		break;
	case 2:
		if (static_cast<Rook*>(p)->t == w)
		{
			for (int i = 0; i<16; i++)
			{
				if (static_cast<Rook*>(whitePieces.at(i))->x == promoteCoordsX && static_cast<Rook*>(whitePieces.at(i))->y == promoteCoordsY)
				{
					whitePieces.erase(whitePieces.begin() + i);
					whitePieces.push_back(new Queen(promoteCoordsX, promoteCoordsY, w));
					break;
				}
			}
		}
		else
		{
			for (int i = 0; i<16; i++)
			{
				if (static_cast<Rook*>(blackPieces.at(i))->x == promoteCoordsX && static_cast<Rook*>(blackPieces.at(i))->y == promoteCoordsY)
				{
					blackPieces.erase(blackPieces.begin() + i);
					blackPieces.push_back(new Queen(promoteCoordsX, promoteCoordsY, b));
					break;
				}
			}
		}
		break;
	case 3:
		if (static_cast<Rook*>(p)->t == w)
		{
			for (int i = 0; i<16; i++)
			{
				if (static_cast<Rook*>(whitePieces.at(i))->x == promoteCoordsX && static_cast<Rook*>(whitePieces.at(i))->y == promoteCoordsY)
				{
					whitePieces.erase(whitePieces.begin() + i);
					whitePieces.push_back(new Knight(promoteCoordsX, promoteCoordsY, w));
					break;
				}
			}
		}
		else
		{
			for (int i = 0; i<16; i++)
			{
				if (static_cast<Rook*>(blackPieces.at(i))->x == promoteCoordsX && static_cast<Rook*>(blackPieces.at(i))->y == promoteCoordsY)
				{
					blackPieces.erase(blackPieces.begin() + i);
					blackPieces.push_back(new Knight(promoteCoordsX, promoteCoordsY, b));
					break;
				}
			}
		}
		break;
	}
}






void receiveMessage()
{
	string action = readMessage();
	if (action == "move")
	{
		string move = readMessage();
		string first = move.substr(0, move.find(")") + 1);
		string end = move.substr(move.find(")") + 1, move.length() - move.find(")"));
		int initX = stoi(first.substr(1, first.find(",") - 1));
		int initY = stoi(first.substr(first.find(",") + 1, first.length() - first.find(',')));
		int endX = stoi(end.substr(1, end.find(",") - 1));
		int endY = stoi(end.substr(end.find(",") + 1, end.length() - end.find(',')));

		Piece *p = getPiece(initX, initY, whitePieces, blackPieces);
		switch (static_cast<Rook*>(p)->type)
		{
		case knight:
			whiteenpassant.active = false;
			blackenpassant.active = false;
				static_cast<Knight*>(p)->moveTo(endX, endY, whitePieces, blackPieces);
			break;
		case king:			
				whiteenpassant.active = false;
				blackenpassant.active = false;
				static_cast<King*>(p)->moveTo(endX, endY, whitePieces, blackPieces);			
			break;
		case pawn:
			
				whiteenpassant.active = false;
				blackenpassant.active = false;
				static_cast<Pawn*>(p)->moveTo(endX, endY, whitePieces, blackPieces);
			break;
		case queen:
			
				whiteenpassant.active = false;
				blackenpassant.active = false;
				static_cast<Queen*>(p)->moveTo(endX, endY, whitePieces, blackPieces);
			break;
		case rook:
			
				whiteenpassant.active = false;
				blackenpassant.active = false;
				static_cast<Rook*>(p)->moveTo(endX, endY, whitePieces, blackPieces);
			break;
		case bishop:			
				whiteenpassant.active = false;
				blackenpassant.active = false;
				static_cast<Bishop*>(p)->moveTo(endX, endY, whitePieces, blackPieces);
			break;			
		}
		enemySelX = -1;
		enemySelY = -1;
	}
	else if (action == "kill")
	{
		string place = readMessage();
		int initX = stoi(place.substr(1, place.find(",") - 1));
		int initY = stoi(place.substr(place.find(",") + 1, place.length() - place.find(',')));
		Piece *p = getPiece(initX, initY, whitePieces, blackPieces);
		static_cast<Rook*>(p)->dead = true;
	}
	else if (action == "selectSpace")
	{
		string place = readMessage();
		enemySelX = stoi(place.substr(1, place.find(",") - 1));
		enemySelY = stoi(place.substr(place.find(",") + 1, place.length() - place.find(',')));		
		InvalidateRect(hWnd, NULL, FALSE);//RedrawWindow(hWnd, NULL, NULL, RDW_INVALIDATE);
	}
	else if (action == "promote")
	{
		string place = readMessage();
		promoteChoice = stoi(place.substr(0, 1));
		promoteCoordsX = stoi(place.substr(2, place.find(",") - 1));
		promoteCoordsY = stoi(place.substr(place.find(",") + 1, place.length() - place.find(',')));
		promote();

		InvalidateRect(hWnd, NULL, FALSE);//RedrawWindow(hWnd, NULL, NULL, RDW_INVALIDATE);
	}
	else if (action == "end")
	{
		toggleTurn();
		InvalidateRect(hWnd, NULL, FALSE);//RedrawWindow(hWnd, NULL, NULL, RDW_INVALIDATE);
	}
}


void otherPlayerTurn()
{
	if (playerTeam == w)
	{
		while (turn == b)
		{
			receiveMessage();
		}
	}
	else
	{
		while (turn == w)
		{
			receiveMessage();
		}
	}
}


void startClient(HWND hDlg, string ip, string port)
{	
	string result = clientConnect(ip, port);
	multi = true;
	mBox(hDlg, result);	
	if (result != "Unable to connect to server!")
	{
		initBoard();
		RedrawWindow(hDlg, NULL, NULL, RDW_INVALIDATE);
		string m = readMessage();
		mBox(hDlg, m);
		playerTeam = to_team(m.substr(7, m.length() - 7));
		if (playerTeam == b)
		{
			thread otherTurn(otherPlayerTurn);
			otherTurn.detach();
		}
	}
	
}


void server(HWND hDlg, string port)
{
	srand(time(0));
	mBox(hDlg, startServer(port));	
	mBox(hDlg, connectToClient());
	multi = true;
	team randTeam = (rand() % 2 == 0) ? w : b;
	mBox(hDlg, "Team : " + to_string(randTeam));
	initBoard();
	RedrawWindow(hDlg, NULL, NULL, RDW_INVALIDATE);
	team other = randTeam == w ? b : w;
	playerTeam = randTeam;
	sendMessage("Team : " + to_string(other));
	if (playerTeam == b)
	{		
			thread otherTurn(otherPlayerTurn);
			otherTurn.detach();
	}
}

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.
	screenX = GetSystemMetrics(SM_CXSCREEN);
	screenY = GetSystemMetrics(SM_CYSCREEN);
	initBoard();
	

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_CHESS, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_CHESS));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}










//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_CHESS));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_CHESS);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable
   
   hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW ^ WS_THICKFRAME ^ WS_MAXIMIZEBOX,
      screenX/2-WIDTH/2, screenY/2-HEIGHT/2, WIDTH, HEIGHT, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   hwndMulti = CreateWindow(
	   _T("BUTTON"),
	   _T("Multiplayer"),
	   WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON | CS_VREDRAW,
	   10,
	   10,
	   100,
	   50,
	   hWnd,
	   (HMENU)multiplayerMenu,
	   (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
	   NULL);
  
   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//

//

void getTile(int &x, int &y)
{
	if (x < 152)
	{
		x = -1;
		y = -1;
		return;
	}
	x = floor((x - 152) / 90) + 1;
	y = floor((744 - y) / 90) + 1;
	if (!(x > 0 && x < 9 && y>0 && y < 9))
	{
		x = -1;
		y = -1;
		return;
	}
}


Image *wBishop;
Image *bBishop;
Image *wKing;
Image *bKing;
Image *wPawn;
Image *bPawn;
Image *wQueen;
Image *bQueen;
Image *wRook;
Image *bRook;
Image *wKnight;
Image *bKnight;

HDC imgHdc;
HBRUSH hBrush, hBrush2;


void toggleTeam()
{
	if (playerTeam == w)
	{
		playerTeam = b;
	}
	else
	{
		playerTeam = w;
	}
}


ULONG_PTR gdiplusToken;
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_CREATE:
		{		
			srand((unsigned)time(NULL));
			Gdiplus::GdiplusStartupInput gdiplusStartupInput;
			
			Gdiplus::GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

			wBishop = Gdiplus::Image::FromFile(L"images\\whiteBishop.png");
			bBishop = Gdiplus::Image::FromFile(L"images\\blackBishop.png");
			wKing = Gdiplus::Image::FromFile(L"images\\whiteKing.png");
			bKing = Gdiplus::Image::FromFile(L"images\\blackKing.png");
			wPawn = Gdiplus::Image::FromFile(L"images\\whitePawn.png");
			bPawn = Gdiplus::Image::FromFile(L"images\\blackPawn.png");
			wQueen = Gdiplus::Image::FromFile(L"images\\whiteQueen.png");
			bQueen = Gdiplus::Image::FromFile(L"images\\blackQueen.png");
			wRook = Gdiplus::Image::FromFile(L"images\\whiteRook.png");
			bRook = Gdiplus::Image::FromFile(L"images\\blackRook.png");
			wKnight = Gdiplus::Image::FromFile(L"images\\whiteKnight.png");
			bKnight = Gdiplus::Image::FromFile(L"images\\blackKnight.png");


			turn = w;
			playerTeam = w;
			int cap = GetSystemMetrics(SM_CYMENU);
			//mBox(hWnd, to_string(cap));
		}
		break;
    case WM_COMMAND:
		{
			
			int wmId = LOWORD(wParam);
			// Parse the menu selections:
			switch (wmId)
			{
			case multiplayerMenu:
			{
				DialogBox(hInst, MAKEINTRESOURCE(IDD_MULTI), hWnd, Multi);
				break;
			}
			case IDM_ABOUT:
				DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
				break;
			case IDM_EXIT:
				DestroyWindow(hWnd);
				break;
			default:
				return DefWindowProc(hWnd, message, wParam, lParam);
			}		
		}        
    case WM_PAINT:
        {
            PAINTSTRUCT ps;			
            HDC hdc = BeginPaint(hWnd, &ps);
			HDC hdcBuf = CreateCompatibleDC(hdc);
			HBITMAP hBitmap = ::CreateCompatibleBitmap(hdc, WIDTH, HEIGHT);
			SelectObject(hdcBuf, hBitmap);
			SetBkMode(hdc, TRANSPARENT);
			SetBkMode(hdcBuf, TRANSPARENT);
			string szText;
			if (turn == w)
			{
				szText = "Turn : White";
			}
			else if (turn==b)
			{
				szText = "Turn : Black";
			}
			else
			{
				szText = "Game Over";
			}
			RECT r;

			hBrush = CreateSolidBrush(RGB(255,255,255));
			r.bottom = HEIGHT;
			r.top = 0;
			r.left = 0;
			r.right = WIDTH;
			FillRect(hdcBuf, &r, hBrush);
			DeleteObject(hBrush);

			
			r.left = 10;
			r.right = 120;
			r.top = 200;
			r.bottom = 230;

			std::wstring stemp = std::wstring(szText.begin(), szText.end());
			LPCWSTR sw = stemp.c_str();

			

			DrawTextW(hdcBuf, sw, _tcslen(sw), &r, DT_CENTER | DT_VCENTER);
			// TODO: Add any drawing code that uses hdc here...
			hBrush = CreateSolidBrush(RGB(128,128,128));
			
			r.bottom = 748;
			r.top = 20;
			r.left = (WIDTH/2)-90*4-4;
			r.right = (WIDTH/2)+90*4+4;			
			FillRect(hdcBuf, &r, hBrush);
			DeleteObject(hBrush);

			hBrush = CreateSolidBrush(RGB(0,0,0));
			hBrush2 = CreateSolidBrush(RGB(255, 255, 255));
			for (int x = 0; x < 8; x++)
			{
				for (int y = 0; y < 8; y++)
				{
					r.left = (WIDTH / 2) - 90 * 4 + 90 * x;
					r.right = (WIDTH / 2) - 90 * 3 + 90 * x;
					r.bottom = 744 - 90 * y;
					r.top = r.bottom - 90;
					if ((x + y) % 2 == 0)
					{
						FillRect(hdcBuf, &r, hBrush);
					}
					else
					{
						FillRect(hdcBuf, &r, hBrush2);
					}
				}

			}


			DeleteObject(hBrush);
			DeleteObject(hBrush2);
			if (selX > 0 && selX < 9 && selY>0 && selY < 9) 
			{
				hBrush = CreateSolidBrush(RGB(255, 255, 0));
				r.left = (WIDTH / 2) - 90 * 4 + 90 * (selX-1);
				r.right = (WIDTH / 2) - 90 * 3 + 90 * (selX-1);
				r.bottom = 744 - 90 * (selY-1);
				r.top = r.bottom - 90;
				FillRect(hdcBuf, &r, hBrush);
				DeleteObject(hBrush);
			}
			
			if (enemySelX > 0 && enemySelX < 9 && enemySelY>0 && enemySelY < 9)
			{
				hBrush = CreateSolidBrush(RGB(128, 0, 0));
				r.left = (WIDTH / 2) - 90 * 4 + 90 * (enemySelX - 1);
				r.right = (WIDTH / 2) - 90 * 3 + 90 * (enemySelX - 1);
				r.bottom = 744 - 90 * (enemySelY - 1);
				r.top = r.bottom - 90;
				FillRect(hdcBuf, &r, hBrush);
				DeleteObject(hBrush);
			}

			Graphics graphics(hdcBuf);
			r.left = 10;
			r.right = 95;
			r.top = 10;
			r.bottom = 95;			
			for (auto i : whitePieces)
			{				
				if (!(i->dead))
				{
					Image *ref=0;
					switch (static_cast<Rook*>(i)->type)
					{
					case knight:
						ref = wKnight;
						break;
					case king:
						ref = wKing;
						break;						
					case pawn:
						ref = wPawn;
						break;
					case queen:
						ref = wQueen;
						break;
					case rook:
						ref = wRook;
						break;
					case bishop:
						ref = wBishop;
						break;
					default:
						mBox(hWnd, "Piece Unidentified");
					}					

					graphics.DrawImage(ref, 64 + 90 * static_cast<Rook*>(i)->x, 747 - 90 * static_cast<Rook*>(i)->y);
					
				}
			}

			for (auto i : blackPieces)
			{
				if (!(i->dead))
				{
					Image *ref = 0;
					switch (static_cast<Rook*>(i)->type)
					{
					case knight:
						ref = bKnight;
						break;
					case king:
						ref = bKing;
						break;
					case pawn:
						ref = bPawn;
						break;
					case queen:
						ref = bQueen;
						break;
					case rook:
						ref = bRook;
						break;
					case bishop:
						ref = bBishop;
						break;
					default:
						mBox(hWnd, "Piece Unidentified");
					}

					graphics.DrawImage(ref, 64 + 90 * static_cast<Rook*>(i)->x, 747 - 90 * static_cast<Rook*>(i)->y);

				}
			}
			BitBlt(hdc, 0, 0, WIDTH, HEIGHT, hdcBuf, 0, 0, SRCCOPY);
			DeleteObject(hBitmap);
            EndPaint(hWnd, &ps);
        }
        break;
		case WM_ERASEBKGND:
			return TRUE;
	case WM_LBUTTONDOWN:
		{
			if (playerTeam == turn)
			{
				int xPos = (int)GET_X_LPARAM(lParam);
				int yPos = (int)GET_Y_LPARAM(lParam);
				getTile(xPos, yPos);
				if (selX == -1 && selY == -1)
				{
					Piece *p = getPiece(xPos, yPos, whitePieces, blackPieces);
					if (p != nullptr)
					{
						if (static_cast<Rook*>(p)->t==playerTeam)
						{
							selX = xPos;
							selY = yPos;
							if (multi) {
								sendMessage("selectSpace");
								sendMessage("(" + to_string(selX) + "," + to_string(selY) + ")");
							}
						}
					}					
				}
				else
				{
					//attempt move
					if(multi) {
						sendMessage("selectSpace");
						sendMessage("(" + to_string(-1) + "," + to_string(-1) + ")");
					}

					Piece *p = getPiece(selX,selY, whitePieces, blackPieces);
					
					switch (static_cast<Rook*>(p)->type)
					{
					case knight:
						if (static_cast<Knight*>(p)->canMoveTo(xPos, yPos, whitePieces, blackPieces))
						{
							bool good = false;
							if (inCheck)
							{
								for (auto m : forcedMoves)
								{
									if (m.initX == selX && m.initY == selY && m.endX == xPos && m.endY == yPos)
									{
										good = detectImminentCheck(selX, selY, xPos, yPos);
										break;
									}
								}
							}
							else
							{
								good = detectImminentCheck(selX, selY, xPos, yPos);
							}
							if (good) {
								whiteenpassant.active = false;
								blackenpassant.active = false;
								static_cast<Knight*>(p)->moveTo(xPos, yPos, whitePieces, blackPieces);
								toggleTurn();
								if (multi) {
									sendMessage("move");
									sendMessage("(" + to_string(selX) + "," + to_string(selY) + ")(" + to_string(xPos) + "," + to_string(yPos) + ")");
									sendMessage("end");
									thread otherTurn(otherPlayerTurn);
									otherTurn.detach();
								}
								else
								{
									toggleTeam();
								}
							}
							
						}
						break;
					case king:
						actual = true;
						if (static_cast<King*>(p)->canMoveTo(xPos, yPos, whitePieces, blackPieces))
						{

							bool good = false;
							if (inCheck)
							{
								for (auto m : forcedMoves)
								{
									if (m.initX == selX && m.initY == selY && m.endX == xPos && m.endY == yPos)
									{
										good = detectImminentCheck(selX, selY, xPos, yPos);
										break;
									}
								}
							}
							else
							{
								good = detectImminentCheck(selX, selY, xPos, yPos);
							}
							if (good) {
								whiteenpassant.active = false;
								blackenpassant.active = false;
								if (static_cast<King*>(p)->canCastle)
								{
									static_cast<King*>(p)->canCastle = false;
								}
								static_cast<King*>(p)->moveTo(xPos, yPos, whitePieces, blackPieces);
								toggleTurn();
								if (multi) {
									sendMessage("move");
									sendMessage("(" + to_string(selX) + "," + to_string(selY) + ")(" + to_string(xPos) + "," + to_string(yPos) + ")");
									sendMessage("end");
									thread otherTurn(otherPlayerTurn);
									otherTurn.detach();
								}
								else toggleTeam();
							}
						}
						break;
					case pawn:
						actual = true;
						if (static_cast<Pawn*>(p)->canMoveTo(xPos, yPos, whitePieces, blackPieces))
						{
							bool good = false;
							if (inCheck)
							{
								for (auto m : forcedMoves)
								{
									if (m.initX == selX && m.initY == selY && m.endX == xPos && m.endY == yPos)
									{
										good = detectImminentCheck(selX, selY, xPos, yPos);
										break;
									}
								}
							}
							else
							{
								good = detectImminentCheck(selX, selY, xPos, yPos);
							}
							if (good) {
								whiteenpassant.active = false;
								blackenpassant.active = false;
								static_cast<Pawn*>(p)->moveTo(xPos, yPos, whitePieces, blackPieces);
								if (multi) {
									sendMessage("move");
									sendMessage("(" + to_string(selX) + "," + to_string(selY) + ")(" + to_string(xPos) + "," + to_string(yPos) + ")");
								}
								if (static_cast<Pawn*>(p)->t == w)
								{
									if (static_cast<Pawn*>(p)->y == 8)
									{
										promoteCoordsX = xPos;
										promoteCoordsY = yPos;
										DialogBox(hInst, MAKEINTRESOURCE(IDD_PROMOTEPAWN), hWnd, Promote);
									}
								}
								else
								{
									if (static_cast<Pawn*>(p)->y == 1)
									{
										promoteCoordsX = xPos;
										promoteCoordsY = yPos;
										DialogBox(hInst, MAKEINTRESOURCE(IDD_PROMOTEPAWN), hWnd, Promote);
									}
								}
								toggleTurn();
								if (multi) {
									sendMessage("end");
									thread otherTurn(otherPlayerTurn);
									otherTurn.detach();
								}
								else toggleTeam();
							}
						}
						break;
					case queen:
						if (static_cast<Queen*>(p)->canMoveTo(xPos, yPos, whitePieces, blackPieces))
						{

							bool good = false;
							if (inCheck)
							{
								for (auto m : forcedMoves)
								{
									if (m.initX == selX && m.initY == selY && m.endX == xPos && m.endY == yPos)
									{
										good = detectImminentCheck(selX, selY, xPos, yPos);
										break;
									}
								}
							}
							else
							{
								good = detectImminentCheck(selX, selY, xPos, yPos);
							}
							if (good) {
								whiteenpassant.active = false;
								blackenpassant.active = false;
								static_cast<Queen*>(p)->moveTo(xPos, yPos, whitePieces, blackPieces);
								toggleTurn();
								if (multi) {
									sendMessage("move");
									sendMessage("(" + to_string(selX) + "," + to_string(selY) + ")(" + to_string(xPos) + "," + to_string(yPos) + ")");
									sendMessage("end");
									thread otherTurn(otherPlayerTurn);
									otherTurn.detach();
								}
								else toggleTeam();
							}
						}
						break;
					case rook:
						if (static_cast<Rook*>(p)->canMoveTo(xPos, yPos, whitePieces, blackPieces))
						{
							bool good = false;
							if (inCheck)
							{
								for (auto m : forcedMoves)
								{
									if (m.initX == selX && m.initY == selY && m.endX == xPos && m.endY == yPos)
									{
										good = detectImminentCheck(selX, selY, xPos, yPos);
										break;
									}
								}
							}
							else
							{
								good = detectImminentCheck(selX, selY, xPos, yPos);
							}
							if (good) {
								whiteenpassant.active = false;
								blackenpassant.active = false;
								if (static_cast<Rook*>(p)->canCastle)
								{
									static_cast<Rook*>(p)->canCastle = false;
								}
								static_cast<Rook*>(p)->moveTo(xPos, yPos, whitePieces, blackPieces);
								toggleTurn();
								if (multi) {
									sendMessage("move");
									sendMessage("(" + to_string(selX) + "," + to_string(selY) + ")(" + to_string(xPos) + "," + to_string(yPos) + ")");
									sendMessage("end");
									thread otherTurn(otherPlayerTurn);
									otherTurn.detach();
								}
								else toggleTeam();
							}
						}
						break;
					case bishop:
						if (static_cast<Bishop*>(p)->canMoveTo(xPos, yPos, whitePieces, blackPieces))
						{

							bool good = false;
							if (inCheck)
							{
								for (auto m : forcedMoves)
								{
									if (m.initX == selX && m.initY == selY && m.endX == xPos && m.endY == yPos)
									{
										good = detectImminentCheck(selX, selY, xPos, yPos);
										break;
									}
								}
							}
							else
							{
								good = detectImminentCheck(selX, selY, xPos, yPos);
							}
							if (good) {
								whiteenpassant.active = false;
								blackenpassant.active = false;
								static_cast<Bishop*>(p)->moveTo(xPos, yPos, whitePieces, blackPieces);
								toggleTurn();
								if (multi) {
									sendMessage("move");
									sendMessage("(" + to_string(selX) + "," + to_string(selY) + ")(" + to_string(xPos) + "," + to_string(yPos) + ")");
									sendMessage("end");
									thread otherTurn(otherPlayerTurn);
									otherTurn.detach();
								}
								else toggleTeam();
							}
						}
						break;
					default:
						mBox(hWnd, "Piece Unidentified");
					}

					selX = -1;
					selY = -1;
					

				}
				InvalidateRect(hWnd, NULL, FALSE);
				//RedrawWindow(hWnd, NULL, NULL, RDW_INVALIDATE);
			}
		}
		break;
	case WM_RBUTTONDOWN:	
		{				
			selX = -1;
			selY = -1;
			if (multi) {
				sendMessage("selectSpace");
				sendMessage("(" + to_string(selX) + "," + to_string(selY) + ")");
			}
			InvalidateRect(hWnd, NULL, FALSE);
			//RedrawWindow(hWnd, NULL, NULL, RDW_INVALIDATE);
		}
		break;
    case WM_DESTROY:	
		while (whitePieces.size() > 0)
		{
			delete whitePieces.back();
			whitePieces.pop_back();
		}
		while (blackPieces.size() > 0)
		{
			delete blackPieces.back();
			blackPieces.pop_back();
		}
		Gdiplus::GdiplusShutdown(gdiplusToken);
		//_CrtDumpMemoryLeaks();
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}




INT_PTR CALLBACK Promote(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		promoteChoice = -1;
		EnableWindow(GetDlgItem(hDlg, IDCANCEL), FALSE);
		return (INT_PTR)TRUE;

	case WM_COMMAND:		
		switch (LOWORD(wParam))
		{
		case IDC_ROOK:				
			EnableWindow(GetDlgItem(hDlg, ID_OK), TRUE);
			promoteChoice = 0;
			break;
		case IDC_BISHOP:
			EnableWindow(GetDlgItem(hDlg, ID_OK), TRUE);
			promoteChoice = 1;
			break;
		case IDC_QUEEN:
			EnableWindow(GetDlgItem(hDlg, ID_OK), TRUE);
			promoteChoice = 2;
			break;
		case IDC_KNIGHT:
			EnableWindow(GetDlgItem(hDlg, ID_OK), TRUE);
			promoteChoice = 3;
			break;
		case ID_OK:
		{
			promote();
			if (multi) {
				sendMessage("promote");
				sendMessage(to_string(promoteChoice) + "(" + to_string(promoteCoordsX) + "," + to_string(promoteCoordsY) + ")");
			}
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
			break;
		}
		default:
			mBox(hDlg, "Ruh Roh");
		}		
	}
	return (INT_PTR)FALSE;
}

bool joinIp, joinPort, hostPort;
int mode;
void checkValid(HWND hDlg)
{
	if ((mode == 0 && joinIp && joinPort) || (mode == 1 && hostPort))
	{
		EnableWindow(GetDlgItem(hDlg, IDOK), TRUE);
	}
	else
	{
		EnableWindow(GetDlgItem(hDlg, IDOK), FALSE);
	}
}


INT_PTR CALLBACK Multi(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
	{	
		mode = -1;
		joinIp = false;
		joinPort = false;
		hostPort = false;
		return (INT_PTR)TRUE;
	}
	case WM_COMMAND:
	{
		if (LOWORD(wParam) == IDOK)
		{			
			if (mode == 0)
			{
				HWND ipedit = GetDlgItem(hDlg, IDC_IP);
				int editlength = GetWindowTextLengthA(ipedit);
				char buff[256];
				GetWindowTextA(ipedit, buff, editlength + 1);
				string ip = string(buff);

				HWND portedit = GetDlgItem(hDlg, IDC_PORTJOIN);
				editlength = GetWindowTextLengthA(portedit);
				GetWindowTextA(portedit, buff, editlength + 1);
				string port = string(buff);

				thread client(startClient, hWnd, ip, port);
				client.detach();

			}
			else if (mode == 1)
			{
				HWND portedit = GetDlgItem(hDlg, IDC_PORTHOST);
				int editlength = GetWindowTextLengthA(portedit);
				char buff[256];
				GetWindowTextA(portedit, buff, editlength + 1);
				string port = string(buff);

				thread serv(server, hWnd, port);
				serv.detach();				
			}
			else
			{
				mBox(hDlg, "How did this happen?");
			}
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		else if (LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		else if (LOWORD(wParam) == IDC_IP)
		{
			HWND fileedit = GetDlgItem(hDlg, IDC_IP);
			int editlength = GetWindowTextLengthA(fileedit) ;
			char buff[256];
			GetWindowTextA(fileedit, buff, editlength+1);
			string s = string(buff);
			if (count(s.begin(), s.end(), '.') == 3)
			{
				
				string r = "([\\d]{1,3}\\.){3}[\\d]{1,3}";	

				regex t(r);

				if (regex_match(s, t))
				{
					joinIp = true;
				}
				else
				{
					joinIp = false;
				}
				checkValid(hDlg);
			}
		}
		else if (LOWORD(wParam) == IDC_PORTJOIN)
		{
			HWND fileedit = GetDlgItem(hDlg, IDC_PORTJOIN);
			int editlength = GetWindowTextLengthA(fileedit);
			char buff[256];
			GetWindowTextA(fileedit, buff, editlength + 1);
			string s = string(buff);			

			string r = "[\\d]{1,5}";

			regex t(r);

			if (regex_match(s, t))
			{
				joinPort = true;
			}
			else
			{
				joinPort = false;
			}
			checkValid(hDlg);
			



		}
		else if (LOWORD(wParam) == IDC_PORTHOST)
		{
			HWND fileedit = GetDlgItem(hDlg, IDC_PORTHOST);
			int editlength = GetWindowTextLengthA(fileedit);
			char buff[256];
			GetWindowTextA(fileedit, buff, editlength + 1);
			string s = string(buff);

			string r = "[\\d]{1,5}";

			regex t(r);

			if (regex_match(s, t))
			{
				hostPort = true;
			}
			else
			{
				hostPort = false;
			}
			checkValid(hDlg);
		}
		else if (LOWORD(wParam) == IDC_CONNECT)
		{
			mode = 0;
			EnableWindow(GetDlgItem(hDlg, IDC_IP), TRUE);
			EnableWindow(GetDlgItem(hDlg, IDC_PORTJOIN), TRUE);
			EnableWindow(GetDlgItem(hDlg, IDC_PORTHOST), FALSE);
		}
		else if (LOWORD(wParam) == IDC_HOST)
		{
			mode = 1;
			EnableWindow(GetDlgItem(hDlg, IDC_IP), FALSE);
			EnableWindow(GetDlgItem(hDlg, IDC_PORTJOIN), FALSE);
			EnableWindow(GetDlgItem(hDlg, IDC_PORTHOST), TRUE);
		}
		break;
	}
	}
	return (INT_PTR)FALSE;
}


