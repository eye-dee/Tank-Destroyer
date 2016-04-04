#pragma once
#include "const.h"

#include "inc\fmod.hpp"
#include "inc\fmod_errors.h"

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
	int countFire;

	double endZ;

	FirePointer f;	
	void explosion();

	FMOD_RESULT result;
	FMOD::System * system[2];
	FMOD::Sound * sound[2]; // sound
	FMOD::Channel * channel[2]; // sound channel
};

