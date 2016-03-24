#ifndef CONST_H
#define CONST_H
	
#include <memory>
#include <iostream>
	class Tank;
	class Background;
	class Aim;

	typedef std :: shared_ptr<Tank> TankPointer;
	typedef std :: shared_ptr<Background> BackgroundPointer;
	typedef std :: shared_ptr<Aim> AimPointer;

	const auto PI = 3.1415926535897932384626433832795;
	const auto max = 1050.0;
	const auto tankH = 2.7;

	auto const poleX = 1024.0,
		poleY = 621.0,
		poleZ = 1024.0;
	
	const auto iWindowX = 1024,
		iWindowY = 621;

	const auto dWindowX = 1024.0,
		dWindowY = 621.0;

	const auto aimHX= 1.0,
		aimHY = 1.0;
#endif