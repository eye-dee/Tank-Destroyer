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
private:
	double x,y,z;
	double V;

	double angle;
	//temp
	double a;
};
