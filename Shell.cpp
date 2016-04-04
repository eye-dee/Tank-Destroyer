#include "Shell.h"
#include <math.h>
#include <glut.h>

#include "Fire.h"

#include <conio.h> 
#include <windows.h>
#include <iostream>
#pragma comment(lib, "fmodex_vc.lib")

Shell::Shell() : isFire(false), isExplosion(false),countFire(0)
{
}

Shell::~Shell()
{
}

void Shell :: fire(double startX, double setEndZ)
{
	isFire = true;
	x = startX;
	y = 0.0;
	z = 0.0;

	countFire = 0;

	speed = 50.0;
	endZ = setEndZ;

	result = system[0]->playSound(FMOD_CHANNEL_FREE, sound[0], false, &(channel[0]));

	channel[0]->set3DDopplerLevel(400);
	channel[0]->set3DSpread(100); //под каким углом идет распролстранение
	channel[0]->set3DMinMaxDistance(300,500); // actually play sound
}

void Shell :: load()
{
	f = FirePointer(new Fire());
	f->load();

	result = FMOD::System_Create(&(system[0]));
	result = system[0]->init(16, FMOD_INIT_3D_RIGHTHANDED, 0);
	result = system[0]->createSound("sound/rpg.mp3", FMOD_3D, 0, &(sound[0])); // creating sound

	result = FMOD::System_Create(&(system[1]));
	result = system[1]->init(16, FMOD_INIT_3D_RIGHTHANDED, 0);
	result = system[1]->createSound("sound/explosion.mp3", FMOD_3D, 0, &(sound[1])); // creating sound
}

void Shell :: stepForward()
{
	if (isFire && ++countFire > 12)
	{
		z += speed*SHELL_H;

		//y = -0.005*z*z + 1.0*z + 3.0/5.0*z;
		y = -1/endZ*z*(z-endZ) + 4.5/5.0*z;

		x += 0.1*windSpeed*cos(angle);

		if (z > endZ)
		{
			result = system[1]->playSound(FMOD_CHANNEL_FREE, sound[1], false, &(channel[1]));

			channel[1]->set3DDopplerLevel(400);
			channel[1]->set3DSpread(100); //под каким углом идет распролстранение
			channel[1]->set3DMinMaxDistance(300,500); // actually play sound
			isFire = false;
			isExplosion = true;
			auto hScaled = 552.0/9.0 - 48.0/900.0*z;
			f->setSize(hScaled);
			f->setShellSize(10.0);
			f->setX(x);
			f->setY(y);
		}
	}
}

void Shell :: draw()
{
	if (isFire && ++countFire > 12)
	{
		glPushMatrix();
		glTranslated(x,y,0.0);
		glScaled(10.0,10.0,1.0);

		glBegin(GL_POLYGON);
		glColor3d(1.0,0.0,0.0);
		for (double i = 0.0; i < 2*PI; i += 0.1)
			glVertex2d(cos(i), sin(i));
		glEnd();

		glPopMatrix();
	}
	else if (isExplosion)
	{
		explosion();
	}
}

void Shell :: explosion()
{
	if (f->draw())
	{
		isExplosion = false;
	}
}