#pragma once
#include "const.h"

class Tank
{
public:
	Tank();
	Tank(double setX, double setY, double setZ);
	~Tank();

	void draw() const;

	void forward();
	void backward();

	void load();

	inline void setSpeed(double set)
	{
		V = set/100.0;
	}
private:
	double x,y,z;
	double V;

	char* fileName[3];
	unsigned person[3];
	int curState;

	double angle;
	//temp
	double a;
};
