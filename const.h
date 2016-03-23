#ifndef CONST_H
#define CONST_H
	
#include <memory>
#include <iostream>
	class Tank;
	class Background;

	typedef std :: shared_ptr<Tank> TankPointer;
	typedef std :: shared_ptr<Background> BackgroundPointer;

	const auto PI = 3.1415926535897932384626433832795;
	const auto max = 1050.0;
	const auto tankH = 2.7;

#endif