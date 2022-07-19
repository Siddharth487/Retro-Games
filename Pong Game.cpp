// Pong Game.cpp : This file contains the 'main' function. Program execution begins and ends there.
//



// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file


#include <iostream>
#include <time.h>
#include <conio.h>
using namespace std;

enum eDir{ STOP = 0, LEFT = 1, UPLEFT = 2, DOWNLEFT = 3, RIGHT = 4, UPRIGHT = 5, DOWNRIGHT = 6};

class cBall
{
private:
	int x, y;
	int originalX, originalY;
	eDir direction;
public:
	cBall(int posX, int posY)
	{
		originalX = posX;
		originalY = posY;
		x = posX;
		y = posY;
		direction = STOP;
	}

	void Reset()
	{
		x = originalX;
		y = originalY;
		direction = STOP;
	}

	void changeDirection(eDir d)
	{
		direction = d;
	}

	void randomDirection()
	{
		direction = (eDir)((rand() % 6) + 1);
	}

	inline int getX() { return x; }
	inline int getY() { return y; }
	inline eDir getDirection() { return direction; }

		void Move()
	{
		switch (direction)
		{
		case STOP:
			break;
		case LEFT:
				x--;
				break;
			case RIGHT:
				x++;
				break;
			case UPLEFT:
				x--;
				y--;
				break;
			case DOWNLEFT:
				x--;
				y++;
				break;
			case UPRIGHT:
				x++;
				y--;
				break;
			case DOWNRIGHT:
				x++;
				y++;
				break;
			default:
				break;

		}
	}
	friend ostream& operator<<(ostream& o, cBall c)
	{
		o << "Ball [" << c.x << "," << c.y << "][" << c.direction << "]";
		return o;
	}

};

class cPaddle
{
private:
	int x, y;
	int originalX, originalY;
public:
	cPaddle()
	{
		x = y = 0;
	}

	cPaddle(int posX, int posY) : cPaddle()
	{
		originalX = posX;
		originalY = posY;
		x = posX;
		y = posY;
	}
	inline void Reset() { x = originalX; y = originalY; }
	inline int getX() { return x; }
	inline int getY() { return y; }
	inline void moveUp() { y--; }
	inline void moveDown() { y++; }
	friend ostream& operator<<(ostream& o, cPaddle c)
	{
		o << "Paddle [" << c.x << "," << c.y << "]";
		return o;
	}

};

class cGameManager
{
private:
	int width, height;
	int score1, score2;
	char up1, down1, up2, down2;
	bool quit;
	cBall * ball;
	cPaddle *player1;
	cPaddle *player2;
public:
	cGameManager(int w, int h)
	{
		srand(time(NULL));
		quit = false;
		up1 = 'w';
		up2 = 'i';
		down1 = 's';
		down2 = 'k';
		score1 = score2 = 0;
		width = w;
		height = h;
		ball = new cBall(w / 2, h / 2);
		player1 = new cPaddle(1, h/2 - 3);
		player2 = new cPaddle(w - 2, h / 2 - 3);
	}

	~cGameManager()
	{
		delete ball, player1, player2;
	}

	void ScoreUp(cPaddle * player)
	{
		if (player == player1)
			score1++;
		else if (player == player2)
			score2++;

		ball->Reset();
		player1->Reset();
		player2->Reset();
	}

	void Draw()
	{
		system("cls");
		for (int i = 0; i < width + 2; i++)
			cout << "\xB2";
		cout << endl;

		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width; j++)
			{
				int ballX = ball->getX();
				int ballY = ball->getY();
				int player1X = player1->getX();
				int player1Y = player1->getY();
				int player2X = player2->getX();
				int player2Y = player2->getY();

				if (j == 0)
					cout << "\xB2";

				if (ballX == j && ballY == i)
					cout << "O"; // ball
				else if (player1X == j && player1Y == i)
					cout << "\xDB"; // player 1 paddle
				else if (player2X == j && player2Y == i)
					cout << "\xDB"; // player 2 paddle

				else if (player1X == j && player1Y + 1 == i)
					cout << "\xDB"; // player 1 paddle
				else if (player1X == j && player1Y + 2 == i)
					cout << "\xDB"; // player 1 paddle
				else if (player1X == j && player1Y + 3 == i)
					cout << "\xDB"; // player 1 paddle

				else if (player2X == j && player2Y + 1 == i)
					cout << "\xDB"; // player 2 paddle
				else if (player2X == j && player2Y + 2 == i)
					cout << "\xDB"; // player 2 paddle
				else if (player2X == j && player2Y + 3 == i)
					cout << "\xDB"; // player 2 paddle


				else
					cout << " ";

				if (j == width - 1)
					cout << "\xB2";
			}

			cout << endl;
		}

		for (int i = 0; i < width + 2; i++)
			cout << "\xB2";
		cout << endl;

		cout << "Left Score:" << score1 << endl;
		cout << "Right Score:" << score2 << endl;
	}

	void Input()
	{
		ball->Move();

		int ballX = ball->getX();
		int ballY = ball->getY();
		int player1X = player1->getX();
		int player1Y = player1->getY();
		int player2X = player2->getX();
		int player2Y = player2->getY();

		if (_kbhit())
		{
			char current = _getch();

			if (current == up1)
				if (player1Y > 0)
					player1->moveUp();
			if (current == up2)
				if (player2Y > 0)
					player2->moveUp();

			if (current == down1)
				if (player1Y + 4 < height)
					player1->moveDown();
			if (current == down2)
				if (player2Y + 4 < height)
					player2->moveDown();

			if (ball->getDirection() == STOP)
				ball->randomDirection();

			if (current == 'q')
				quit = true;
		}
	}

	void Logic()
	{
		int ballX = ball->getX();
		int ballY = ball->getY();
		int player1X = player1->getX();
		int player1Y = player1->getY();
		int player2X = player2->getX();
		int player2Y = player2->getY();

		// left paddle
		for (int i = 0; i < 4; i++)
			if (ballX == player1X + 1)
				if (ballY == player1Y + i)
					ball->changeDirection((eDir)((rand() % 3) + 4));

		// right paddle
		for (int i = 0; i < 4; i++)
			if (ballX == player2X - 1)
				if (ballY == player1Y + i)
					ball->changeDirection((eDir)((rand() % 3) + 1));

		// bounce off bottom wall
		if (ballY == height - 1)
			ball->changeDirection(ball->getDirection() == DOWNRIGHT ? UPRIGHT : UPLEFT);

		// bounce off top wall
		if (ballY == 0)
			ball->changeDirection(ball->getDirection() == UPRIGHT ? DOWNRIGHT : DOWNLEFT);

		// right wall
		if (ballX == width - 1)
			ScoreUp(player1);

		// left wall
		if (ballX == 0)
			ScoreUp(player2);
	}

	void Run()
	{ 
		while (!quit)
		{
			Draw();
			Input();
			Logic();
		}
	}
};
int main()
{
	cGameManager c(40, 20);
	c.Run();
	return 0;
}