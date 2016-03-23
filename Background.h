#pragma once
#include "const.h"

class Background
{
public:
	Background();
	~Background();

	void load();
	void draw();
private:
	const char* fileName;
	unsigned person;
};

