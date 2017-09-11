#include "stdafx.h"

//CONSTANTS AND GLOBAL VALUES
//type       name            value
const double DT            = 0.1;
const int    WINDOW_SIZE_X = 800;
const int    WINDOW_SIZE_Y = 600;
const int    BALLS_COUNT   = 10000;
const int    MAX_VELOCITY  = 500;
const int    FONT_SIZE     = 25;
const int    UPD_TIME      = 1;
const bool   FULLSCREEN    = false;
int          TopId         = 0;

template < typename T >
void QuickSort (T data[], int size, int left, int right);

template < typename T >
void Swap(T balls[], int a, int b);

template < typename T >
void REV (T data [], int size);

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
		pos.x += vel.x * DT;
		pos.y += vel.y * DT;

		if (pos.x - radius < WINDOW_SIZE_X / 5 + WINDOW_SIZE_X / 200)
		{
			pos.x = radius + WINDOW_SIZE_X / 5 + WINDOW_SIZE_X / 200;
			vel.x = -vel.x;
			score++;
		}

		if (pos.y - 10 < 0)
		{
			pos.y = radius;
			vel.y = -vel.y;
			score++;
		}

		if (pos.x + radius > WINDOW_SIZE_X)
		{
			pos.x = WINDOW_SIZE_X - radius;
			vel.x = -vel.x;
			score++;
		}

		if (pos.y + radius > WINDOW_SIZE_Y)
		{
			pos.y = WINDOW_SIZE_Y - radius;
			vel.y = -vel.y;
			score++;
		}
	}

	void Draw()
	{
		txSetColor(color);
		txSetFillColor(color);

		if(id != TopId) txCircle(pos.x, pos.y, radius);
		else txRectangle(pos.x - radius, pos.y - radius, pos.x + radius, pos.y + radius);
	}

	Ball()
	{
		vel.x = rand() % MAX_VELOCITY - MAX_VELOCITY / 2;
		vel.y = rand() % MAX_VELOCITY - MAX_VELOCITY / 2;

		pos.x = rand() % (WINDOW_SIZE_X / 5 * 4) + WINDOW_SIZE_X / 5;
		pos.y = rand() % (WINDOW_SIZE_Y / 5 * 4) + WINDOW_SIZE_Y / 5;

		color = RGB(rand() % 200, rand() % 200, rand() % 200);

		Run();

		id = rand()%(BALLS_COUNT * 10) ;
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
	SCORECELL arr[BALLS_COUNT] = {};

	int CELL_COUNT = (BALLS_COUNT <= 20) ? BALLS_COUNT : 20;

	void Refresh(Ball ball[])
	{
		for (int i = 0; i < BALLS_COUNT; i++)
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

		for (int i = 0; i < CELL_COUNT; i++)
		{
			txSetColor(arr[i].color);
			txSetFillColor(arr[i].color);

			txRectangle(0, WINDOW_SIZE_Y / 20 * i, WINDOW_SIZE_X  /5, WINDOW_SIZE_Y / 20 * i + WINDOW_SIZE_Y / 20);

			txSetColor(TX_WHITE);

			sprintf(buff, "#%d    Score: %d.", i + 1, arr[i].score);
			txDrawText(0, i * WINDOW_SIZE_Y / 20, WINDOW_SIZE_X / 5, i * WINDOW_SIZE_Y / 20 + WINDOW_SIZE_Y / 20, buff);
		}
	}

	void Run()
	{

        QuickSort(arr, BALLS_COUNT, 0, BALLS_COUNT - 1);
        REV(arr, BALLS_COUNT);
        TopId = arr[0].id;


		Draw();
	}
};

bool operator > (SCORECELL const & a, SCORECELL const & b);
bool operator < (SCORECELL const & a, SCORECELL const & b);
void NewBall (Ball balls[], int & size, int realsize);

int main()
{
	txCreateWindow(WINDOW_SIZE_X, WINDOW_SIZE_Y);
	txBegin();
	txDisableAutoPause();
	srand(time(0));
	Ball balls[BALLS_COUNT];
	ScoreBoard Board;
	txSelectFont("Calibri Light", FONT_SIZE);
	int counter = 0;

	int size = 1;

	while (!GetAsyncKeyState(VK_ESCAPE))
	{
		if (counter % UPD_TIME == 0) Board.Refresh(balls);

        NewBall(balls, size, BALLS_COUNT);

		for (int i = 0; i < size; i++) balls[i].Run();
		Board.Run();

		txSetColor(TX_ORANGE);
		txSetFillColor(TX_ORANGE);

		txRectangle(WINDOW_SIZE_X / 5, 0, WINDOW_SIZE_X / 5 + WINDOW_SIZE_X / 200, WINDOW_SIZE_Y);

		txSetFillColor(TX_WHITE);
		txSleep(20);
		txClear();
		txClearConsole();

		counter++;
	}

    return 0;
}

template < typename T >
void QuickSort (T data[], int size, int left, int right)
{
    int mid = (left + right)/ 2;
    int count1 = left;
    int count2 = right;

    while (count1 <= count2)
    {
        while (data[count1] < data[mid])
        {
            count1++;
        }

        while (data[count2] > data[mid])
        {
            count2--;
        }

        if (count1 <= count2)
            {
            Swap (data, count1, count2);
            count1++;
            count2--;
            }
    }

    if (count1 < right)
    {
        QuickSort (data, size, count1, right);
    }

    if (count2 > left)
    {
        QuickSort (data, size, left, count2);
    }
}

template < typename T >
void Swap(T balls[], int a, int b)
{
    T buff = balls[a];
    balls[a] = balls[b];
    balls[b] = buff;
}

template < typename T >
void REV (T data [], int size)
{
    for(int i = 0; i < size / 2; i++)
    {
        Swap(data, i, size - i - 1);
    }
}

bool operator > (SCORECELL const & a, SCORECELL const & b)
{
    return b.score < a.score;
}

bool operator < (SCORECELL const & a, SCORECELL const & b)
{
    return b.score > a.score;
}

void NewBall (Ball balls[], int & size, int realsize)
{
    if(txMouseButtons() == 1 && size < realsize)
    {
        balls[++size].pos.x = txMouseX();
        balls[  size].pos.y = txMouseY();
    }
}
