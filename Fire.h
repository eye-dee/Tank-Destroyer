#pragma once
#include <iostream>

class Fire
{
public:
	Fire();
	~Fire();

	void load();
	void draw();

	inline void setX(double set)
	{
		x = set;
	}
	inline void setY(double set)
	{
		y = set;
	}
	inline void setSize(double set)
	{
		size = set;
	}
	inline void setShellSize(double set)
	{
		aspect = size/set;
		dopSize = set;
	}
private:
	char* fileName[27];
	unsigned person[27];

	double x,y;
	double size;
	double aspect;
	double dopSize;

	int curState;

	int speed;

	inline void nextState()
	{
		++curState;
		if (curState == 27*speed)
			curState = 0;
	}
};

