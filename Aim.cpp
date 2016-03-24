#include "Aim.h"
#include <glut.h>

Aim::Aim() : x(250.0),
	y(250.0),
	rad(200.0),
	isShown(true),
	wCeil(1.0/18.0),
	biasX(1.0/100.0),
	biasY(1.0/50.0)
{
	for (int i = 0; i < 3; ++i)
		heightCeil[i] = 1.0/(20.0+5*i);
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

		for (int i = 0; i < 6; ++i)
		{
			glBegin(GL_LINE_LOOP);
				glVertex2d(-biasX -1.0/3.0 + i*wCeil,0.0);
				glVertex2d(-biasX -1.0/3.0 + (i+1)*wCeil,0.0);
				glVertex2d(-biasX -1.0/3.0 + (i+1)*wCeil,heightCeil[1]);
				glVertex2d(-biasX -1.0/3.0 + i*wCeil,heightCeil[1]);
			glEnd();

			glBegin(GL_LINE_LOOP);
				glVertex2d(biasX +1.0/3.0 - i*wCeil,0.0);
				glVertex2d(biasX +1.0/3.0 - (i+1)*wCeil,0.0);
				glVertex2d(biasX +1.0/3.0 - (i+1)*wCeil,heightCeil[1]);
				glVertex2d(biasX +1.0/3.0 - i*wCeil,heightCeil[1]);
			glEnd();

			glBegin(GL_LINE_LOOP);
				glVertex2d(-biasX -1.0/3.0 + i*wCeil,0.0);
				glVertex2d(-biasX -1.0/3.0 + (i+1)*wCeil,0.0);
				glVertex2d(-biasX -1.0/3.0 + (i+1)*wCeil,-heightCeil[0]);
				glVertex2d(-biasX -1.0/3.0 + i*wCeil,-heightCeil[0]);
			glEnd();

			glBegin(GL_LINE_LOOP);
				glVertex2d(biasX +1.0/3.0 - i*wCeil,0.0);
				glVertex2d(biasX +1.0/3.0 - (i+1)*wCeil,0.0);
				glVertex2d(biasX +1.0/3.0 - (i+1)*wCeil,-heightCeil[0]);
				glVertex2d(biasX +1.0/3.0 - i*wCeil,-heightCeil[0]);
			glEnd();

			glBegin(GL_LINE_LOOP);
				glVertex2d(-biasX -1.0/3.0 + i*wCeil,heightCeil[1] + biasY);
				glVertex2d(-biasX -1.0/3.0 + (i+1)*wCeil,heightCeil[1] + biasY);
				glVertex2d(-biasX -1.0/3.0 + (i+1)*wCeil,heightCeil[1] + biasY + heightCeil[2]);
				glVertex2d(-biasX -1.0/3.0 + i*wCeil,heightCeil[1] + biasY + heightCeil[2]);
			glEnd();

			glBegin(GL_LINE_LOOP);
				glVertex2d(biasX +1.0/3.0 - i*wCeil,heightCeil[1] + biasY);
				glVertex2d(biasX +1.0/3.0 - (i+1)*wCeil,heightCeil[1] + biasY);
				glVertex2d(biasX +1.0/3.0 - (i+1)*wCeil,heightCeil[1] + biasY + heightCeil[2]);
				glVertex2d(biasX +1.0/3.0 - i*wCeil,heightCeil[1] + biasY + heightCeil[2]);
			glEnd();

		}

		glBegin(GL_LINES);

			glVertex2d(-biasX,0.0);
			glVertex2d(-biasX,-0.3);

			glVertex2d(biasX,0.0);
			glVertex2d(biasX,-0.3);

		glEnd();

		glBegin(GL_LINES);

			glVertex2d(0.0,0.55);
			glVertex2d(0.0,0.45);

			glVertex2d(-0.05,0.5);
			glVertex2d(0.05,0.5);

			glVertex2d(0.1,-0.27);
			glVertex2d(0.33,-0.27);

		glEnd();

		glBegin(GL_LINE_STRIP);
			for (double t = 0.0; t < 9.1; t += 1.0)
				glVertex2d(0.1 + t/9.0*0.23,-0.25 + 0.1*exp(-0.3*t));
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