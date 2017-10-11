#pragma once

struct SCORECELL
{
	DPOINT pos;
	int id;
	int score;
	COLORREF color;
};


bool operator > (SCORECELL const & a, SCORECELL const & b);
bool operator < (SCORECELL const & a, SCORECELL const & b);

class ScoreBoard
{
public:
	ScoreBoard(int BALLS_COUNT);
	~ScoreBoard();
	void run();
	int getTopId();
	void refresh(std::vector<Ball> ball);

private:
	void draw();

	int BALLS_COUNT_;
	int CELL_COUNT_;
	SCORECELL * arr_;
	int topId_;
};

bool operator > (SCORECELL const & a, SCORECELL const & b)
{
	return b.score < a.score;
}

bool operator < (SCORECELL const & a, SCORECELL const & b)
{
	return b.score > a.score;
}

