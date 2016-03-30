#include "Shell.h"
#include <math.h>
#include <glut.h>

Shell::Shell() : isFire(false), isExplosion(false)
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

	angle = PI/2.0;

	speed = 1.0;
	endZ = setEndZ;
}

void Shell :: stepForward()
{
	if (isFire)
	{
		double tempAngle = atan(2*z);

		z += speed*shellH;

		y = -0.005*z*z + 1.0*z + 3.0/5.0*z;

		x += cos(angle);

		if (z > endZ)
		{
			isFire = false;
			isExplosion = true;
		}
	}
}

void Shell :: draw() const
{
	if (isFire)
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

void Shell :: explosion() const
{
	//static 
}