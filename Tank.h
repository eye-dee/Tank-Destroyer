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
	inline void setCurState(int set)
	{
		angle = set*PI;
		switch(set)
		{
		case 0: angle = PI; curAspect = TANK_ASPECT0; curPart = TANK_PART0; break;
		case 1: angle = 0.0; curAspect = TANK_ASPECT0; curPart = TANK_PART0; break;
		case 2: angle = 3.0*PI/4.0; curAspect = TANK_ASPECT45; curPart = TANK_PART45; break;
		case 3: angle = PI/4.0; curAspect = TANK_ASPECT45; curPart = TANK_PART45; break;
		case 4: angle = PI/2.0; curAspect = TANK_ASPECT90; curPart = TANK_PART90; break;
		}
		curState = set;
	}

	inline void stop()
	{
		V = 0.0;
	}

	inline double getX()
	{
		return x;
	}
	inline double getZ()
	{
		return z;
	}
	inline double getY()
	{
		return y;
	}
	inline void setAimRad(double set)
	{
		aimRad = set;
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
	double x,y,z;
	double V;

	char* fileName[3];
	unsigned person[3];
	int curState;

	double angle;
	//temp
	double aimRad;

	double *bDistToSize, *cDistToSize, *dDistToSize;
	double *splineDist, *splineSize;

	double curAspect;
	double curPart;
};
