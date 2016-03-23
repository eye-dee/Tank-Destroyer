#ifndef CONST_H
#define CONST_H
	
#include <memory>
#include <iostream>
	class Tank;

	typedef std :: shared_ptr<Tank> TankPointer;

	const auto PI = 3.1415926535897932384626433832795;
	const auto max = 1100.0;
	const auto tankH = 2.7;

#endif