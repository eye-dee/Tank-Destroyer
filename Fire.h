#pragma once
#include <iostream>

const auto SIZEN = 17;

class Fire
{
public:
	Fire();
	~Fire();

	void load();
	bool draw();

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
	char* fileName[SIZEN];
	unsigned person[SIZEN];

	double x,y;
	double size;
	double aspect;
	double dopSize;

	int curState;

	int speed;

	inline bool nextState()
	{
		++curState;
		if (curState == SIZEN*speed)
		{
			curState = 0;
			return true;
		}
		return false;
	}
};

