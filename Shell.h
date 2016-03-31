#pragma once
#include "const.h"

class Shell
{
public:
	Shell();
	~Shell();

	void fire(double startX, double setEndZ);
	void stepForward();

	void load();

	void draw() const;
private:
	double x,y,z;

	double angle;
	double speed;

	double t;

	bool isFire;
	bool isExplosion;

	double endZ;

	FirePointer f;	
	void explosion() const;
};

