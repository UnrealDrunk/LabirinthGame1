// LabirinthGame1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <iostream>
#include <Windows.h>
#include<conio.h>

using namespace std;

const int Arr_Limit = 10;

enum SurfaceElements { FLOOR = 0, WALL, START, FINISH, PLAYER };
	
enum MoveDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
MoveDirection dir;

bool GameOver;
	
	

struct Vector2
{
	int row;
	int col;

public:

	Vector2() 
	{
		row = 0;
		col = 3;
	}

	Vector2(int new_row, int new_col)
	{
		row = new_row;
		col = new_col;
	}

	friend
		Vector2 operator + (Vector2 v1, Vector2 v2)
	{
		return Vector2(v1.row + v2.row, v1.col + v2.col);
	}

};


class Game
{
	Vector2 PlayerCoords;

	int ArrLab[Arr_Limit][Arr_Limit] =
	{
	{1,1,1,1,1,1,1,1,1,1,},
	{1,1,0,0,0,0,0,0,0,1,},
	{2,0,0,1,1,1,1,0,1,1,},
	{1,1,1,1,0,1,1,0,0,1,},
	{1,0,0,1,0,1,1,1,0,1,},
	{1,0,1,1,0,0,0,0,0,1,},
	{1,0,1,1,0,1,1,1,1,1,},
	{1,0,0,0,0,0,0,0,1,1,},
	{1,0,1,1,0,1,1,0,0,3,},
	{1,1,1,1,1,1,1,1,1,1,}
	};
	char symbols[4];
public:
	Game()
	{
		symbols[static_cast<int>(FLOOR)] = ' ';
		symbols[static_cast<int>(WALL)] = '\xB2';
		symbols[static_cast<int>(PLAYER)] = '\xFD';
		symbols[static_cast<int>(FINISH)] = '\xB';
		symbols[static_cast<int>(START)] = '\xB0';
	}
	


public: 
	void PrepareConsole()
	{
		system("color 1F");
		ShowMeTheCursor(FALSE);
	}
	BOOL ShowMeTheCursor(BOOL bShow)
	{
		CONSOLE_CURSOR_INFO cci;
		HANDLE hStdOut;
		hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
		if (hStdOut == INVALID_HANDLE_VALUE)
			return FALSE;
		if (!GetConsoleCursorInfo(hStdOut, &cci))
			return FALSE;
		cci.bVisible = bShow;
		if (!SetConsoleCursorInfo(hStdOut, &cci))
			return FALSE;
		return TRUE;
	}

	void SetCursorPosition(Vector2 coord)
	{
		COORD pos = { (short)coord.col, (short)coord.row };
		HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleCursorPosition(output, pos);
	}

	void PrintSym(SurfaceElements type)
	{
		if (type == START)
			cout << "\xB0";
		else if (type == FLOOR)
			cout << " ";
		else if (type == WALL)
			cout << "\xB2";
		else if (type == FINISH)
			cout << "\xB";
		else if (type == PLAYER)
			cout << "\xFD";
	}
	
	void PrintPlayer(Vector2 pos, SurfaceElements ElementType)
	{
		SetCursorPosition(pos);
		cout << symbols[static_cast<int>(ElementType)];
	}

	
	void Draw()
	{
		do 
		{
			system("cls");
			for (int i = 0; i < Arr_Limit; i++)
			{
				for (int j = 0; j < Arr_Limit; j++)
				{
					if (ArrLab[i][j] == 0)
						PrintSym(FLOOR);
					else if (ArrLab[i][j] == 1)
						PrintSym(WALL);
					else if (ArrLab[i][j] == 2)
						PrintSym(START);
					else if (ArrLab[i][j] == 3)
						PrintSym(FINISH);
				}
				cout << endl;
				
			}
			//cin.get();

			MovePlayer(Vector2(0, 3));
			
		} while (true);
	}

	void MovePlayer(Vector2 shift) {
		// calc new coords
		Vector2 new_coords = PlayerCoords + shift;

		// check them
		/*if (!CheckCell(new_coords))
			return;*/

		// all ok, lets move our player

		//draw floor on player pos
		PrintPlayer(PlayerCoords, SurfaceElements::FLOOR);

		//change player coords
		PlayerCoords = new_coords;

		//draw player on new place
		PrintPlayer(PlayerCoords, SurfaceElements::PLAYER);
	}



	void Input()
	{
		if (_kbhit())
		{
			switch (_getch())
			{
			case 'a':
				dir = LEFT;
				break;
			case 'd':
				dir = RIGHT;
				break;
			case 'w':
				dir = UP;
				break;
			case 's':
				dir = DOWN;
				break;
			case 'x':
				GameOver = true;
				break;

			}
		}
	}

	void Logic()
	{
		switch (dir)
		{
		case LEFT:
			MovePlayer(Vector2(-1, 0));
			break;
		case RIGHT:
			MovePlayer(Vector2(+1, 0));
			break;
		case UP:
			MovePlayer(Vector2(0, -1));
			break;
		case DOWN:
			MovePlayer(Vector2(0, +1));
			break;
		}


	}
	


	/*void Run()
	{
		while (!GameOver)
		{
			PrepareConsole();
			Draw();
			Input();
			Logic();

		}

	}*/

};

int main()
{
	
	Game Labirinth;
	while (!GameOver)
	{
		Labirinth.PrepareConsole();
		Labirinth.Draw();
		Labirinth.Input();
		Labirinth.Logic();

	}

	

	getchar();
}

