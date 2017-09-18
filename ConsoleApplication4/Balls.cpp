#include "stdafx.h"

// CONSTANTS AND GLOBAL VALUES
// type      name           value
const double DT            = 0.01;
int          TopId         = 0;  //! TODO: Remove me

template < typename T >
void QuickSort (T data[], int Size, int Left, int Right);

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
private:
	
	DPOINT vel = { 0, 0 };
	double radius = 10;

	void Physics()
	{
		pos.x += vel.x * DT;
		pos.y += vel.y * DT;

		if (pos.x - radius < txGetExtentX() / 5 + txGetExtentX() / 200)
		{
			pos.x = radius + txGetExtentX() / 5 + txGetExtentX() / 200;
			vel.x = -vel.x;
			score++;
		}

		if (pos.y - 10 < 0)
		{
			pos.y = radius;
			vel.y = -vel.y;
			score++;
		}

		if (pos.x + radius > txGetExtentX())
		{
			pos.x = txGetExtentX() - radius;
			vel.x = -vel.x;
			score++;
		}

		if (pos.y + radius > txGetExtentY())
		{
			pos.y = txGetExtentY() - radius;
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

public:

	void Run()
	{
		Physics();
		Draw();
	}

	Ball(int MAX_VELOCITY, int BALLS_COUNT)
	{
		vel.x = rand() % MAX_VELOCITY - MAX_VELOCITY / 2;
		vel.y = rand() % MAX_VELOCITY - MAX_VELOCITY / 2;

		pos.x = rand() % (txGetExtentX() / 5 * 4) + txGetExtentX() / 5;
		pos.y = rand() % (txGetExtentY() / 5 * 4) + txGetExtentY() / 5;

		color = RGB(rand() % 200, rand() % 200, rand() % 200);

		Run();

		id = rand() % (BALLS_COUNT * 10);
	}

	int score = 0;
	int id = 0;
	DPOINT pos = { 0, 0 };
	COLORREF color = TX_BLACK;
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
	int BALLS_COUNT = 0;
	SCORECELL *arr;

	int CELL_COUNT = 0;

	void Refresh(std::vector<Ball> ball)
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
		char *buff = new char[32];
		for (int i = 0; i < CELL_COUNT; i++)
		{
			txSetColor(arr[i].color);
			txSetFillColor(arr[i].color);

			txRectangle(0, txGetExtentY() / 20 * i, txGetExtentX()  /5, txGetExtentY() / 20 * i + txGetExtentY() / 20);

			txSetColor(TX_WHITE);

			sprintf(buff, "#%d    Score: %d.", i + 1, arr[i].score);
			txDrawText(0, i * txGetExtentY() / 20, txGetExtentX() / 5, i * txGetExtentY() / 20 + txGetExtentY() / 20, buff);
		}
		delete(buff);
	}

	void Run()
	{

        QuickSort(arr, BALLS_COUNT, 0, BALLS_COUNT - 1);
        REV(arr, BALLS_COUNT);
        TopId = arr[0].id;


		Draw();
	}
	
	ScoreBoard(int _BALLS_COUNT)
	{
		BALLS_COUNT = _BALLS_COUNT;
		arr = new SCORECELL[BALLS_COUNT];
		CELL_COUNT = (BALLS_COUNT <= 20) ? BALLS_COUNT : 20;
	}

	~ScoreBoard()
	{
		delete(arr);
	}
};

bool operator > (SCORECELL const & a, SCORECELL const & b);
bool operator < (SCORECELL const & a, SCORECELL const & b);

int main()
{
	const int    BALLS_COUNT = 100;
	const int    MAX_VELOCITY = 5000;

	txCreateWindow(800, 600);
	txBegin();
	txDisableAutoPause();
	srand(time(0));
	std::vector<Ball> balls;

	

	for (int i = 0; i < BALLS_COUNT; i++)
	{
		Ball example(MAX_VELOCITY, BALLS_COUNT);
		balls.push_back(example);
	}

	ScoreBoard Board(BALLS_COUNT);
	txSelectFont("Calibri Light", 25);
	int counter = 0;

	while (!GetAsyncKeyState(VK_ESCAPE))
	{
		Board.Refresh(balls);

		for (int i = 0; i < BALLS_COUNT; i++) balls[i].Run();
		Board.Run();

		txSetColor(TX_ORANGE);
		txSetFillColor(TX_ORANGE);

		txRectangle(txGetExtentX() / 5, 0, txGetExtentX() / 5 + txGetExtentX() / 200, txGetExtentY());

		txSetFillColor(TX_WHITE);
		txSleep(20);
		txClear();
		txClearConsole();

		counter++;
	}

    return 0;
}

template < typename T >
void QuickSort (T data[], int Size, int Left, int Right)
{
    int mid = (Left + Right)/2;
    int x = Left;
    int y = Right;

    while (x <= y)
    {
        while (data[x] < data [mid])
        {
            x++;
        }

        while (data [y] > data [mid])
        {
            y--;
        }

        if (x <= y)
        {
            Swap (data, x, y);
            x++;
            y--;
        }
    }

    if (x < Right)
    {
       QuickSort (data, Size, x, Right);
    }

    if (y > Left)
    {
       QuickSort (data, Size, Left, y);
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

void BallsInit(int size, const int MAX_VEL)
{
	
}


