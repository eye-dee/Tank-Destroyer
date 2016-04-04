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

	void draw();

	inline void setWindSpeed(double set)
	{
		windSpeed = set;
	}
	inline void setAngleWind(double set)
	{
		angle = PI+set;
	}
private:
	double x,y,z;

	double angle;
	double speed;
	double windSpeed;

	double t;

	bool isFire;
	bool isExplosion;

	double endZ;

	FirePointer f;	
	void explosion();
};

