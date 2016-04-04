#pragma once
#include "const.h"

const auto TANK_N = 10;
const auto WIND_N = 7;
const auto DIR_N = 4;

class Background
{
public:
	Background();
	~Background();

	void load();
	void draw() const;
	void drawSpeed() const;

	double inline getWindSpeed()
	{
		return curWindSpeed - 11.0;
	}
	double inline getWindAngle()
	{
		return (curWindDir - 17)*PI/2.0;
	}
	double inline getTankSpeed()
	{
		return (curTankSpeed-2.0)*5.0;
	}
private:
	const char* fileName;
	unsigned person;

	const char* speedFileName[TANK_N+WIND_N+DIR_N];
	unsigned speedId[TANK_N+WIND_N+DIR_N];
	int curTankSpeed;
	int curWindSpeed;
	int curWindDir;
};

