#pragma once
#include "const.h"

#include "inc\fmod.hpp"
#include "inc\fmod_errors.h"
#include "Background.h"

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
	inline void setBackgroundPointer(BackgroundPointer setBP)
	{
		bP = setBP;
	}
	inline bool isExlosion()
	{
		return isExplosion;
	}

	inline double getX() const
	{
		return x;
	}
	inline double getZ() const
	{
		return z;
	}
	inline double getY() const
	{
		return y;
	}

	inline void setDistToSize(double* setB, double* setC, double* setD)
	{
		bDistToSize = setB;
		cDistToSize = setC;
		dDistToSize = setD;
	}
	inline void setSplineMas(double* setDist,double* setSize)
	{
		splineDist = setDist;
		splineSize = setSize;
	}
private:
	inline void setBondBlood()
	{
		bP->setBondBlood();
	}
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

	double *bDistToSize, *cDistToSize, *dDistToSize;
	double *splineDist, *splineSize;
	int last;
	double factor;

	BackgroundPointer bP;
};

