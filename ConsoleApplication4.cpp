#include "stdafx.h"

const double dt = 0.01;
const int WSizeX = 800;
const int WSizeY = 600;
bool needSort = true;
const int BallCount = 40;

struct DPOINT
{
	double x;
	double y;
};

class Ball
{
public:
	DPOINT pos = { 0, 0 };
	DPOINT vel = { 0, 0 };
	double radius = 10;
	
	int score = 0;

	COLORREF color = TX_BLACK;

	int id = 0;

	void Physics()
	{
		pos.x += vel.x * dt;
		pos.y += vel.y * dt;

		if (pos.x - radius < 200)
		{
			pos.x = radius + 200;
			vel.x = -vel.x;
			score++;
			needSort = true;
		}

		if (pos.y - 10 < 0)
		{
			pos.y = radius;
			vel.y = -vel.y;
			score++;
			needSort = true;
		}

		if (pos.x + radius > WSizeX)
		{
			pos.x = WSizeX - radius;
			vel.x = -vel.x;
			score++;
			needSort = true;
		}

		if (pos.y + radius > WSizeY)
		{
			pos.y = WSizeY - radius;
			vel.y = -vel.y;
			score++;
			needSort = true;
		}
	}

	void Draw()
	{
		txSetColor(color);
		txSetFillColor(color);

		txCircle(pos.x, pos.y, radius);
	}

	Ball()
	{
		vel.x = rand() % 1000 - 500;
		vel.y = rand() % 1000 - 500;

		pos.x = rand() % WSizeX;
		pos.y = rand() % WSizeY;

		color = RGB(rand() % 255, rand() % 255, rand() % 255);

		Run();
		id = rand()%100;
	}

	void Run()
	{
		Physics();
		Draw();
	}
};

struct SCORECELL
{
	DPOINT pos;
	int id;
	int score;
	COLORREF color;
};

class ScoreBoard
{
public:
	SCORECELL arr[BallCount] = {};
	
	void Refresh(Ball ball[], int size)
	{
		for (int i = 0; i < BallCount; i++)
		{
			arr[i].id = ball[i].id;
			arr[i].score = ball[i].score;
			arr[i].pos = ball[i].pos;
			arr[i].color = ball[i].color;
		}
	}

	void Draw()
	{
		char buff[128] = "";

		for (int i = 0; i < 10; i++)
		{
			txSetColor(arr[i].color);
			txSetFillColor(arr[i].color);
			txRectangle(0, 60 * i, 200, 60 * i + 59);
			txSetColor(TX_WHITE);
			sprintf(buff, "Score: %d, id: %d.", arr[i].score, arr[i].id);
			txDrawText(0, i * 60, 200, i * 60 + 61, buff);
		}
	}

	void swap(SCORECELL balls[], int a, int b)
	{
		SCORECELL buff = balls[a];
		balls[a] = balls[b];
		balls[b] = buff;
	}

	void Sort()
	{
		bool sorted = false;

		while (true)
		{
			sorted = false;

			for (int i = 0; i < BallCount - 1; i++)
			{
				if (arr[i].score < arr[i + 1].score)
				{
					swap(arr, i, i + 1);
					sorted = true;
				}
			}

			if (sorted == false) break;
		}
	}

	void Run()
	{
		Sort();
		Draw();
	}
};

int main()
{
	txCreateWindow(WSizeX, WSizeY);

	srand(time(0));

	Ball balls[BallCount];

	ScoreBoard Board;

	while (!GetAsyncKeyState(VK_ESCAPE))
	{
		Board.Refresh(balls, BallCount);
		for (int i = 0; i < BallCount; i++)
			balls[i].Run();
		Board.Run();

		txSetColor(TX_BLACK);
		txLine(200, 0, 200, 600);

		txSetFillColor(TX_WHITE);
		txSleep(20);
		txClear();
		txClearConsole();
	}

    return 0;
}
