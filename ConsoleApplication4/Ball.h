#pragma once

class Ball
{
public:
	Ball(int max_vel, int balls_count);
	~Ball();
	void run();
	void setTopId(int topId);
	int getId();
	int getScore();
	DPOINT getPos();
	COLORREF getColor();
	void setAnimation(HDC animation, POINT animationSize, int animationLength);
	
private:
	void physics();
	void draw();

	DPOINT vel_;
	DPOINT pos_;
	POINT animationSize_;
	COLORREF color_;
	HDC animation_;
	double radius_;
	int score_;
	int id_;
	int topId_;
	int animationLength_;
	int globalCounter_;
};

