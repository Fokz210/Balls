#define _CRT_SECURE_NO_WARNINGS

#include "stdafx.h"

#include "DPOINT.h"
#include "Ball.h"
#include "ScoreBoard.h"
#include "sort.h"

const double DT = 0.01;
const double METER = 100.0;
const double Grav = 9.815;

int main()
{
	const int    BALLS_COUNT = 50;
	const int    MAX_VELOCITY = 10;

	txCreateWindow(1200, 1000);
	txBegin();
	txDisableAutoPause();
	srand((unsigned int)time(0));
	std::vector<Ball> balls;

	for (int i = 0; i < BALLS_COUNT; i++)
	{
		Ball example(MAX_VELOCITY, BALLS_COUNT);
		balls.push_back(example);
	}

	HDC animation = txLoadImage("res//animation.bmp");

	for (int i = 0; i < balls.size(); i++)
		balls[i].setAnimation(animation, { 50, 50 }, 14);

	ScoreBoard Board(BALLS_COUNT);
	txSelectFont("Calibri Light", 25);
	int counter = 0;

	while (!GetAsyncKeyState(VK_ESCAPE))
	{
		Board.refresh(balls);
		

		for (int i = 0; i < BALLS_COUNT; i++)
		{
			balls[i].setTopId(Board.getTopId());
			balls[i].run();
		}
		Board.run();

		txSetColor(TX_ORANGE);
		txSetFillColor(TX_ORANGE);

		txRectangle(txGetExtentX() / 5, 0, txGetExtentX() / 5 + txGetExtentX() / 200, txGetExtentY());

		txSetFillColor(TX_WHITE);
		txSleep(10);
		txClear();
		txClearConsole();

		counter++;
	}

	txDeleteDC(animation);

    return 0;
}

Ball::Ball(int max_vel, int balls_count) :
	vel_({ double(rand() % max_vel - max_vel / 2) , double(rand() % max_vel - max_vel / 2) }),
	pos_({ double(rand() % (txGetExtentX() / 5 * 4) + txGetExtentX() / 5) , double(rand() % (txGetExtentX() / 5 * 4) + txGetExtentX() / 5) }),
	color_(RGB(rand() % 200, rand() % 200, rand() % 200)),
	radius_(25),
	score_(0),
	id_(rand() % (balls_count * 10)),
	topId_(0),
	globalCounter_(0)
{
}

Ball::~Ball()
{
}

void Ball::run()
{
	physics();
	draw();

	globalCounter_++;
}

void Ball::setTopId(int topId)
{
	topId_ = topId;
}

int Ball::getId()
{
	return id_;
}

int Ball::getScore()
{
	return score_;
}

DPOINT Ball::getPos()
{
	return pos_;
}

COLORREF Ball::getColor()
{
	return color_;
}

void Ball::setAnimation(HDC animation, POINT animationSize, int animationLength)
{
	animation_ = animation;
	animationSize_ = animationSize;
	animationLength_ = animationLength;
}

ScoreBoard::ScoreBoard(int BALLS_COUNT) :
	BALLS_COUNT_(BALLS_COUNT),
	CELL_COUNT_((BALLS_COUNT <= 20) ? BALLS_COUNT : 20),
	arr_(new SCORECELL[BALLS_COUNT]),
	topId_(0)
{
}

ScoreBoard::~ScoreBoard()
{
	delete(arr_);
}

void ScoreBoard::run()
{
	QuickSort(arr_, BALLS_COUNT_, 0, BALLS_COUNT_ - 1);
	REV(arr_, BALLS_COUNT_);
	topId_ = arr_[0].id;

	draw();

}

int ScoreBoard::getTopId()
{
	return topId_;
}

void ScoreBoard::refresh(std::vector<Ball> ball)
{
	for (int i = 0; i < BALLS_COUNT_; i++)
	{
		arr_[i].id = ball[i].getId();
		arr_[i].score = ball[i].getScore();
		arr_[i].pos = ball[i].getPos();
		arr_[i].color = ball[i].getColor();
	}
}

void ScoreBoard::draw()
{
	char *buff = new char[32];
	for (int i = 0; i < CELL_COUNT_; i++)
	{
		txSetColor(arr_[i].color);
		txSetFillColor(arr_[i].color);

		txRectangle(0, txGetExtentY() / 20 * i, txGetExtentX() / 5, txGetExtentY() / 20 * i + txGetExtentY() / 20);

		txSetColor(TX_WHITE);

		sprintf(buff, "#%d    Score: %d.", i + 1, arr_[i].score);
		txDrawText(0, i * txGetExtentY() / 20, txGetExtentX() / 5, i * txGetExtentY() / 20 + txGetExtentY() / 20, buff);
	}
	delete(buff);
}


void Ball::physics()
{
	pos_.x += vel_.x * DT * METER;
	pos_.y += vel_.y * DT * METER;

	if (pos_.x - radius_ < txGetExtentX() / 5 + txGetExtentX() / 200)
	{
		pos_.x = radius_ + txGetExtentX() / 5 + txGetExtentX() / 200;
		vel_.x = -vel_.x;
		score_++;
	}

	if (pos_.y - radius_ < 0)
	{
		pos_.y = radius_;
		vel_.y = -vel_.y;
		score_++;
	}

	if (pos_.x + radius_ > txGetExtentX())
	{
		pos_.x = txGetExtentX() - radius_;
		vel_.x = -vel_.x;
		score_++;
	}

	if (pos_.y + radius_ > txGetExtentY())
	{
		pos_.y = txGetExtentY() - radius_;
		vel_.y = -vel_.y;
		score_++;
	}
}

void Ball::draw()
{
	static int counter = 0;

	if (globalCounter_ % 3 == 0) counter++;

	txSetColor(color_, 3);
	txSetFillColor(TX_WHITE);

	if (id_ != topId_) txCircle(pos_.x, pos_.y, radius_);
	else txRectangle(pos_.x - radius_, pos_.y - radius_, pos_.x + radius_, pos_.y + radius_);

	if (animation_) txTransparentBlt(txDC(), pos_.x - radius_, pos_.y - radius_, animationSize_.x, animationSize_.y, animation_, animationSize_.x * (counter % animationLength_), 0, TX_WHITE);
}




