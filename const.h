#ifndef CONST_H
#define CONST_H
	
#include <memory>
#include <iostream>

	class Tank;
	class Background;
	class Aim;
	class Shell;
	class Fire;

	typedef std :: shared_ptr<Tank> TankPointer;
	typedef std :: shared_ptr<Background> BackgroundPointer;
	typedef std :: shared_ptr<Aim> AimPointer;
	typedef std :: shared_ptr<Shell> ShellPointer;
	typedef std :: shared_ptr<Fire> FirePointer;

	const auto PI = 3.1415926535897932384626433832795;
	const auto max = 300.0;
	const auto TANK_H = 2.7;

	auto const POLE_X = 1024.0,
		POLE_Y = 621.0,
		POLE_Z = 1024.0;
	
	const auto iWindowX = 1024,
		iWindowY = 621;

	const auto D_WINDOW_X = 1024.0,
		D_WINDOW_Y = 621.0;

	const auto AIM_H_X= 1.0,
		AIM_H_Y = 1.0;
	
	const auto SHELL_H = 0.1;
	
	const auto PICTURE_ASPECT = 0.8;

	const auto SPEED_POS_X = 20.0,
		SPEED_POS_Y = 0.9*POLE_Y;
	const auto TEXT_SIZE = 60.0;

	const auto bondIH = 0.0005,
		bondH = 30.0;
	const int N = POLE_X/bondH + 2;

	inline int random(int a)
	{
		return rand()%a;
	}

	inline double f(double x)
	{
		double sum = 0.0;
		for (int i = 0; i < 15; ++i)
			sum += random(30)*abs(sin(x)) + random(30)*abs(cos(x));

		if (sum > POLE_Y)
			return POLE_Y;
		return POLE_Y - sum;
	}

	const auto NdistToSize = 9;
	const double dist[] = {200.0,300.0,400.0,500.0,600.0,700.0,800.0,900.0,1000.0},
		size[] = {61.0/468.0,45.0/468.0,34.0/468.0,26.0/468.0,20.0/468.0,18.0/468.0,16.0/468.0,15.0/468.0,14.0/468.0};

	const auto NZToY = 20;
	const double Z[] = {50.0,100.0,150.0,200.0,250.0,300.0,350.0,400.0,450.0,500.0,550.0,600.0,650.0,700.0,750.0,800.0,850.0,900.0,950.0,1000.0},
		Y[] = {440.0,637.0,767.0,897.0,1010.0,1105.0,1178.0,1258.0,1318.0,1368.0,1408.0,1453.0,1492,1524.0,1548.0,1568.0,1588.0,1600.0,1610.0,1615.0};

	const auto TANK_ASPECT0 = 3.3666666666666666666666666666667,
		TANK_ASPECT45 = 3.25,
		TANK_ASPECT90 = 1.8266666666666666666666666666667;
	const auto TANK_PART0 = 240.0/300.0,
		TANK_PART45 = 204.0/300.0,
		TANK_PART90 = 193.0/300.0;
#endif