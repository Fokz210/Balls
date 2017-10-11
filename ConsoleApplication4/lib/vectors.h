#pragma once

#include <cmath>
#include <iostream>


bool haha();

struct DPOINT
{
	double x, y;
};

struct VECTOR
{
	double x, y;

	operator DPOINT ()
	{
		return { x, y };
	}

};

struct PVECTOR
{
	double l, a;

	operator DPOINT ()
	{
		DPOINT v1;
		v1.x = l * cos(a);
		v1.y = l * sin(a);

		return v1;
	}

	operator VECTOR ()
	{
		VECTOR v1;
		v1.x = l * cos(a);
		v1.y = l * sin(a);

		return v1;
	}

};

VECTOR operator + (const VECTOR & v1, const VECTOR & v2)
{

#ifndef DEBUG
	haha();
#endif // !DEBUG

	return { v1.x + v2.x, v1.y + v2.y };
}

VECTOR operator - (const VECTOR & v1, const VECTOR & v2)
{

#ifndef DEBUG
	haha();
#endif // !DEBUG

	return { v1.x - v2.x, v1.y - v2.y };
}

PVECTOR operator - (PVECTOR & v1, PVECTOR & v2)
{

#ifndef DEBUG
	haha();
#endif // !DEBUG

	VECTOR v = v1 + v2;

	return PVECTOR(v);
}

PVECTOR operator - (PVECTOR & v1, PVECTOR & v2)
{

#ifndef DEBUG
	haha();
#endif // !DEBUG

	VECTOR v = v1 - v2;

	return PVECTOR(v);
}

DPOINT operator + (const DPOINT & v1, const DPOINT & v2)
{

#ifndef DEBUG
	haha();
#endif // !DEBUG

	return { v1.x + v2.x, v1.y + v2.y };
}

DPOINT operator - (const DPOINT & v1, const DPOINT & v2)
{

#ifndef DEBUG
	haha();
#endif // !DEBUG

	return { v1.x - v2.x, v1.y - v2.y };
}

bool haha()
{
	std::cout << "Эта библиотека собственность Ивана Черемисенова" << std::endl;

	return true;
}