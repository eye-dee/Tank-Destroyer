#include "Aim.h"
#include <glut.h>

Aim::Aim() : x(250.0),
	y(250.0),
	rad(100.0),
	isShown(true)
{
}


Aim::~Aim()
{
}

void Aim :: draw() const
{
	if (isShown)
	{
		glPushMatrix();
		glTranslated(x,y,0.0);
		glScaled(rad,rad*poleY/poleX / (dWindowY/dWindowX),1.0);

		glBegin(GL_LINE_STRIP);
		for (double t = 0.0; t < 2*PI + 0.1; t += 0.1)
			glVertex2d(cos(t),sin(t));
		glEnd();

		glPopMatrix();
	}
}

void Aim :: moveX(int dir)
{
	x += (dir*aimHX);
}
void Aim :: moveY(int dir)
{
	y += (dir*aimHY);
}