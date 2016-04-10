#include <iostream>
#include <string>
#include "clearscreen.h"
#include <time.h>

using namespace std;

//Global Variables
const int ROWS = 31;
const int COLS = 60;
int gen[ROWS][COLS];
int todo[ROWS][COLS];
int backup[ROWS][COLS];
int speed = 100;
string input;

//functions
void copy(int array1[ROWS][COLS], int array2[ROWS][COLS]);
void life(int array[ROWS][COLS]);
void print(int array[ROWS][COLS]);
bool compare(int array1[ROWS][COLS], int array2[ROWS][COLS]);
void game(int cycles);

int main()
{
	cout << "The Game of Life, also known simply as Life, is a cellular " << endl;
	cout << "automaton devised by the British mathematician John Horton" << endl;
	cout << "Conway in 1970." << endl;
	cout << endl;
	cout << "The rules:" << endl;
	cout << "1. Any live cell with fewer than two live neighbours dies, as if caused by under-population." << endl;
	cout << "2. Any live cell with two or three live neighbours lives on to the next generation." << endl;
	cout << "3. Any live cell with more than three live neighbours dies, as if by over-population." << endl;
	cout << "4. Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction." << endl;
	cout << endl;
	cout << "Programmed in C++ by gSilas on 3/7/2016" << endl;
	cout << endl;
	cout << "You want to start the [r]andom game?" << endl;

	getline(cin, input);

	if (input == "r")
	{
		ClearScreen();
		int in;
		cout << "Enter your time restriction(cycles)!" << endl;
		cin >> in;
		cout << "Enter your speed restriction(milliseconds) between cycles!" << endl;
		cin >> speed;
		game(in);
	}
	return 0;
}

void game(int cy)
{
	int cycles = 0;

	ClearScreen();

	cout << "Starting the game with " << cycles << " cycles!" << endl;

	srand(time(NULL));

	for (int j = 1; j < ROWS - 1; j++)
	{
		for (int i = 1; i < COLS - 1; i++)
			gen[j][i] = rand() % 2;
	}

	copy(gen, todo);
	copy(todo, backup);
	print(todo);
	sleepcp(speed);

	while (true)
	{
		life(todo);
		ClearScreen();
		print(todo);
		sleepcp(speed);

		if (cycles >= cy)
		{
			cout << "You want to [e]nd the game or [r]estart?" << endl;

			getline(cin, input);

			if (input == "e")
			{
				break;
			}
			else if (input == "r")
			{
				cycles = 0;
				srand(time(NULL));

				for (int j = 1; j < ROWS - 1; j++)
				{
					for (int i = 1; i < COLS - 1; i++)
						gen[j][i] = rand() % 2;
				}

				copy(gen, todo);
				copy(todo, backup);
				print(todo);
				sleepcp(speed);
			}
		}
		cycles++;
	}
}

void copy(int array1[ROWS][COLS], int array2[ROWS][COLS])
{
	for (int j = 0; j < ROWS; j++)
	{
		for (int i = 0; i < COLS; i++)
			array2[j][i] = array1[j][i];
	}
}

void life(int array[ROWS][COLS])
{
	int temp[ROWS][COLS];
	copy(array, temp);
	for (int j = 1; j < ROWS - 1; j++)
	{
		for (int i = 1; i < COLS - 1; i++)
		{
			int count = 0;
			count =
				array[j - 1][i] +
				array[j - 1][i - 1] +
				array[j][i - 1] +
				array[j + 1][i - 1] +
				array[j + 1][i] +
				array[j + 1][i + 1] +
				array[j][i + 1] +
				array[j - 1][i + 1];
			if (count < 2 || count > 3)
				temp[j][i] = 0;
			if (count == 2)
				temp[j][i] = array[j][i];
			if (count == 3)
				temp[j][i] = 1;
		}
	}
	copy(temp, array);
}

bool compare(int array1[ROWS][COLS], int array2[ROWS][COLS])
{
	int count = 0;
	for (int j = 0; j < ROWS; j++)
	{
		for (int i = 0; i < COLS; i++)
		{
			if (array1[j][i] == array2[j][i])
				count++;
		}
	}
	if (count == ROWS * COLS)
		return true;
	else
		return false;
}

void print(int array[ROWS][COLS])
{
	for (int j = 1; j < ROWS - 1; j++)
	{
		for (int i = 1; i < COLS - 1; i++)
		{
			if (array[j][i] == 1)
				cout << '.';
			else
				cout << ' ';
		}
		cout << endl;
	}
}
