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
private:
	double x,y,z;
	double V;

	const char* fileName;
	unsigned person;

	double angle;
	//temp
	double a;
};
