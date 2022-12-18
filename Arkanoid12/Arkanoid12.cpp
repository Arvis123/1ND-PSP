#include <iostream>
#include <math.h>
#include <string>
#include <stdlib.h>
#include <conio.h>
#include <cstdlib>
#include "Arkanoid12.h"

using namespace std;

#define KEY_LEFT 75
#define KEY_RIGHT 77
#define KEY_X 120
#define KEY_PLAY 112
#define KEY_END 101

int main()
{

	cout << "Welcome to Arkanoid" << endl;
	cout << "Press P to start the game" << endl;
	cout << "Press E to leave now" << endl;

	string wallStr = "@";
	string brickStr = "#";
	string padStr = "*";
	string ballStr = "O";
	int padx, pady, ballx, bally, balldx, balldy, changeBallY, score;
	int ballPos[28][66];
	changeBallY = 2;
	padx = 23;
	pady = 30;
	ballx = 20;
	bally = 30;
	balldx = -1;
	balldy = 0;
	score = 0;

	int matrix[100][100] = {
			{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
			{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
			{1,1,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,1,1},
			{1,1,3,3,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,3,3,1,1},
			{1,1,3,3,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,3,3,1,1},
			{1,1,3,3,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,3,3,1,1},
			{1,1,3,3,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,3,3,1,1},
			{1,1,3,3,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,3,3,1,1},
			{1,1,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,1,1},
			{1,1,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,1,1},
			{1,1,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,1,1},
			{1,1,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,1,1},
			{1,1,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,1,1},
			{1,1,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,1,1},
			{1,1,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,1,1},
			{1,1,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,1,1},
			{1,1,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,1,1},
			{1,1,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,1,1},
			{1,1,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,1,1},
			{1,1,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,1,1},
			{1,1,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,1,1},
			{1,1,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,1,1},
			{1,1,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,1,1},
			{1,1,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,1,1},
			{1,1,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,1,1},
			{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
			{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	};

	switch (_getch())
	{
	case KEY_PLAY:
		while (true)
		{
			ballx = ballx + balldx;
			bally = bally - changeBallY;

			cout << "Score: " << score << "           Press X to quit :)" << endl;
			Matrixdraw(padx, pady, padStr, ballx, bally, matrix, ballStr, balldx, score, changeBallY, wallStr, brickStr);

			switch (_getch())
			{
			case KEY_LEFT:
				if (pady != 5) {
					pady = pady - 5;
				}
				break;
			case KEY_RIGHT:
				if (pady != 60) {
					pady = pady + 5;
				}
				break;
			case KEY_X:
				return EndGameBefore(score);
			}
			if (score == 275) {
				return FinishGame(score);
			}
			if (ballx > 24)
			{
				return LostGame(score);
			}
			if (matrix[ballx][bally-1] == 1 or matrix[ballx][bally + 2] == 1) {
				changeBallY = changeBallY * -1;
			}
			else if (matrix[ballx][bally] == 2)
			{
				balldx = balldx * -1;
			}
			else if ((ballx + 1 == padx and bally == pady) or (ballx + 1 == padx and bally == pady - 1) or (ballx + 1 == padx and bally == pady - 2) or (ballx + 1 == padx and bally == pady - 3)
				or (ballx + 1 == padx and bally == pady + 1) or (ballx + 1 == padx and bally == pady + 2) or (ballx + 1 == padx and bally == pady + 3))
			{
				balldx = balldx * -1;
			}

			system("CLS");
		}
		break;
	case KEY_END:
		return LeftGame();
	default:
		break;
	}
}

int LeftGame()
{
	system("CLS");
	cout << "You have left the game" << endl;
	cout << endl;
	cout << endl;
	cout << endl;
	return 0;
}

int LostGame(int score)
{
	system("CLS");
	cout << "You have lost  the game, better luck next time" << endl;
	cout << "End score: " << score << endl;
	cout << endl;
	cout << endl;
	cout << endl;
	return 0;
}

int FinishGame(int score)
{
	system("CLS");
	cout << "You have won the game good job buddy" << endl;
	cout << "End score: " << score << endl;
	cout << endl;
	cout << endl;
	cout << endl;
	return 0;
}

int EndGameBefore(int score)
{
	system("CLS");
	cout << "Your score was: " << score << endl;
	cout << endl;
	cout << endl;
	cout << "Better luck next time";
	return 0;
}

void Matrixdraw(int padx, int pady, string& padStr, int& ballx, int& bally, int  matrix[100][100], string& ballStr, int balldx, int& score, int changeBallY, string& wallStr, string& brickStr)
{
	for (int x = 0; x < 28; x++)
	{
		for (int y = 0; y < 66; y++)
		{
			if ((padx == x and y == pady) or (padx == x and y == pady - 1) or (padx == x and y == pady - 2) or (padx == x and y == pady - 3)
				or (padx == x and y == pady + 1) or (padx == x and y == pady + 2) or (padx == x and y == pady + 3))
			{
				cout << padStr;
			}
			else if (ballx == x and bally == y and matrix[x][y] != 2) {
				cout << ballStr;
			}
			else if (ballx == x and bally == y and matrix[x][y] == 2) {
				cout << " ";
				ballx = ballx + balldx;
				matrix[x][y] = 3;
				score += 1;
			}
			else if (ballx == x and bally == y and matrix[x][y] == 1) {
				ballx = ballx + balldx;
				bally = bally + changeBallY;
			}
			else if (matrix[x][y] == 1) {
				cout << wallStr;
			}
			else if (matrix[x][y] == 2) {
				cout << brickStr;
			}
			else if (matrix[x][y] == 3)
			{
				cout << " ";
			}
			else if (matrix[x][y] == 4) {
				cout << score;
			}
		}
		cout << endl;
	}
}
