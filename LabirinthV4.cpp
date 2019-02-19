#include "pch.h"
#include <iostream>
#include <windows.h>
#include <conio.h>
#include <fstream>


using namespace std;


enum CellType { Floor = 0, wall, start, finish, hero, fruit, poison };
// 0 - Пол - Путь жизни
// 1 - Стенки лабиринта, не пускают бедного Hero пройти
// 2 - Старт
// 3 - Финиш

struct Vector2
{
	int x;
	int y;

public:

	Vector2() {
		x = 0;
		y = 0;
	}

	Vector2(int new_x, int new_y)
	{
		x = new_x;
		y = new_y;
	}

	friend
		Vector2 operator + (Vector2 v1, Vector2 v2)
	{
		return Vector2(v1.x + v2.x, v1.y + v2.y);
	}

};




class Game {

private:
	//constants
	char symbols[7];
	int score = 0;
	int TotalScore = 0;
	int Arr[24][24];
	Vector2 HeroCoords;
	bool running = true;
	int level = 1;
	double GameVersion = 1.04;
	
public:

	void ReadLevel1()
	{
		
		int rows = 24; int cols = 24;
		//Заполнение матрицы значениями из файла

		string path = "Matrix.txt";
		ifstream fin;
		fin.open(path);
		if (!fin.is_open())
		{
			cout << "Error! File was not opened" << endl;
		}
		else {

			for (int i = 0; i < rows; i++)
				for (int j = 0; j < cols; j++)
					fin >> Arr[i][j];
				
		}
		fin.close();

	}

	void ReadLevel2()
	{

		int rows = 24; int cols = 24;
		//Заполнение матрицы значениями из файла
		string path = "Matrix2.txt";
		ifstream fin;
		fin.open(path);
		if (!fin.is_open())
		{
			cout << "Error! File was not opened" << endl;
		}
		else 
		{

			for (int i = 0; i < rows; i++)
				for (int j = 0; j < cols; j++)
					fin >> Arr[i][j];
		}
		fin.close();

	}

	void ReadLevel3()
	{

		int rows = 24; int cols = 24;
		//Заполнение матрицы значениями из файла
		string path = "Matrix3.txt";
		ifstream fin;
		fin.open(path);
		if (!fin.is_open())
		{
			cout << "Error! File was not opened" << endl;
		}
		else 
		{

			for (int i = 0; i < rows; i++)
				for (int j = 0; j < cols; j++)
					fin >> Arr[i][j];
		}
		fin.close();

	}

	void ReadLevel4()
	{

		int rows = 24; int cols = 24;
		//Заполнение матрицы значениями из файла
		string path = "Matrix4.txt";
		ifstream fin;
		fin.open(path);
		if (!fin.is_open())
		{
			cout << "Error! File was not opened" << endl;
		}
		else 
		{

			for (int i = 0; i < rows; i++)
				for (int j = 0; j < cols; j++)
					fin >> Arr[i][j];
		}
		fin.close();

	}



	void PrintLab() {

		for (int x = 0; x < 24; x++) //переключение по строкам
		{
			for (int y = 0; y < 24; y++)// переключение по столбцам
			{
				Vector2 pos = Vector2(x, y);
				cout << symbols[Arr[x][y]];
					
			}
			cout << endl;
			
		}
		
	}
	



	void PrintGameOver()
	{
		SetCursorPosition(Vector2(5, 27));
		cout << "Game over!!!" << endl;
	}

	void PrintVictory()
	{
		SetCursorPosition(Vector2(8, 8));
		cout << "You've passed through the Labirinth! Congratulations"<< endl;
		cout <<"\t\t" <<"Your Game result is " << TotalScore << endl;
		system("pause");
	}

	void PrintGameStatus()
	{
		SetCursorPosition(Vector2(27, 5));
		cout << "Labirinth Hero Game, ver " << GameVersion << endl;
		SetCursorPosition(Vector2(27, 6));
		cout << "Current Level - " << level << endl;
		SetCursorPosition(Vector2(27, 7));
		cout << "Level " << level << " Score: " << score << endl;
		SetCursorPosition(Vector2(27, 8));
		cout << "Total Game Score  " << TotalScore << endl;
	
	}

	//Поехали
	

	//НапечататьСимвол
	void PrintSymbol(Vector2 pos, CellType cell_type)
	{
		

		//Поставить на позицию
		SetCursorPosition(pos);

		//Выводим на экран
		std::cout << symbols[static_cast<int>(cell_type)];

	}
	void SetCursorPosition(Vector2 coord) {
		COORD pos = { (short)coord.x, (short)coord.y };
		HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleCursorPosition(output, pos);
	}


	void HideCursor() {
		CONSOLE_CURSOR_INFO lpCursor;
		HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);

		GetConsoleCursorInfo(output, &lpCursor);
		lpCursor.bVisible = false;
		SetConsoleCursorInfo(output, &lpCursor);
	}

	


	bool CheckCell(Vector2 new_coords) {
		
		bool walk(Arr[new_coords.y][new_coords.x] == wall);

		bool finish(Arr[new_coords.y][new_coords.x] == finish);
		if (finish == true)
		{
			score += 100;
			TotalScore += 100;
			return true;
		}
		
		if (Arr[new_coords.y][new_coords.x] == fruit)
		{
			score += 10;
			TotalScore += 10;
			Arr[new_coords.y][new_coords.x] = Floor;
		}

		if (Arr[new_coords.y][new_coords.x] == poison)
		{
			score -= 10;
			TotalScore -= 10;
			Arr[new_coords.y][new_coords.x] = Floor;
		}
		
		return !walk;

	}
	
	


	void MovePlayer(Vector2 shift)
	{
		// calc new coords
		Vector2 new_coords = HeroCoords + shift;

		// check them
		if (!CheckCell(new_coords))
			return;

		// all ok, lets move our player

		//draw floor on player pos
			
		PrintSymbol(HeroCoords, CellType::Floor);
	
				//change player coords
		HeroCoords = new_coords;

			//draw player on new place
		PrintSymbol(HeroCoords, CellType::hero);
			
			
		
	}

	void CheckStartPosition()
	{
		for (int i = 0; i < 24; i++)
			for (int j = 0; j < 24; j++)
				if (Arr[i][j] == start)
					HeroCoords = Vector2(j, i);
		
	}




	void PrepareToRun()
	{
		system("color 1F");
		HideCursor();
	}

	void Logic()
	{
		if (score < 0)
		{
			PrintGameOver();
			running = false;
		}
		else if (score >= 100 && level == 1)
		{
			system("cls");
			system("color 2F");
			score = 20;
			ReadLevel2();
			PrintLab();
			CheckStartPosition();
			level++;
		}
		else if (score >= 100 && level == 2)
		{
			system("cls");
			system("color 5F");
			score = 20;
			ReadLevel3();
			PrintLab();
			CheckStartPosition();
			level++;
		}
		else if (score >= 100 && level == 3)
		{
			system("cls");
			system("color CF");
			score = 20;
			ReadLevel4();
			PrintLab();
			CheckStartPosition();
			level++;
		}
		else if (score >= 100 && level == 4)
		{
			running = false;
			system("cls");
			PrintVictory();

		}



	}

	Game() {
		//init char symbols
		symbols[static_cast<int>(Floor)] = ' '; //Называем Пол - который Путь жизни из 0 в s1 //
		symbols[static_cast<int>(wall)] = '\xB2'; //Называем Стенки лабиринта из 1 в s2 //
		symbols[static_cast<int>(start)] = '\x11'; //Называем Старт из 2 в s3 //
		symbols[static_cast<int>(finish)] = 'X'; //Называем Финиш из 3 в s4 //
		symbols[static_cast<int>(hero)] = '\xFE';
		symbols[static_cast<int>(fruit)] = '\x94';
		symbols[static_cast<int>(poison)] = '\x83';

	}

	void Run()
	{
		PrepareToRun();
		ReadLevel1();
		PrintLab();
		CheckStartPosition();

		while (running)
		{
			PrintGameStatus();
			char c = _getch();

			switch (c){
			case 27:
				std::cout << "Game over!" << '\n';
				running = false;
				break;

			case 72: // (keysArrow == 72 || keysArrow == 150 || keysArrow == 230) - Вверх
				MovePlayer(Vector2(0, -1));
				break;

			case 80: // (keysArrow == 80 || keysArrow == 155 || keysArrow == 265) - Вниз
				MovePlayer(Vector2(0, +1));
				break;

			case 77: // (keysArrow == 77 || keysArrow == 130 || keysArrow == 262) - Вправо
				MovePlayer(Vector2(+1, 0));
				break;

			case 75: // (keysArrow == 75 || keysArrow == 148 || keysArrow == 235) - Влево
				MovePlayer(Vector2(-1, 0));
				break;
			}
			
			Logic();
			

		} 
	}
};


int main() {
	Game * game = new Game();
	game->Run();

	delete game;
};
