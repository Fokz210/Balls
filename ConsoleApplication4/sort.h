#pragma once

template < typename T >
void QuickSort(T data[], int Size, int Left, int Right);

template < typename T >
void Swap(T balls[], int a, int b);

template < typename T >
void REV(T data[], int size);

template < typename T >
void QuickSort(T data[], int Size, int Left, int Right)
{
	int mid = (Left + Right) / 2;
	int x = Left;
	int y = Right;

	while (x <= y)
	{
		while (data[x] < data[mid])
		{
			x++;
		}

		while (data[y] > data[mid])
		{
			y--;
		}

		if (x <= y)
		{
			Swap(data, x, y);
			x++;
			y--;
		}
	}

	if (x < Right)
	{
		QuickSort(data, Size, x, Right);
	}

	if (y > Left)
	{
		QuickSort(data, Size, Left, y);
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
void REV(T data[], int size)
{
	for (int i = 0; i < size / 2; i++)
	{
		Swap(data, i, size - i - 1);
	}
}

