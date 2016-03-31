#include "Aim.h"
#include <glut.h>
#include "lodepng.h"

Aim::Aim() : x(250.0),
	y(250.0),
	rad(200.0),
	isShown(true),
	wCeil(1.0/10.0),
	biasX(1.0/100.0),
	biasY(1.0/50.0),
	fileName("aim.png")
{
	for (int i = 0; i < 3; ++i)
		heightCeil[i] = 2.0/(20.0+5*i);
}

void fogTry(double stX, double stY, double rad)
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glPushMatrix();
	glTranslated(0.0,0.0,-1.0);
	double circleX = stX + rad*cos(0.0), circleY = stY + rad*sin(0.0), prevX = poleX, prevY = stY;

	int prevSt = 0;
	for (double t = 0.1; t < 2*PI + 0.09; t += 0.1)
	{
		bool isDopPoint = false;
		double curX = stX + rad*cos(t),
			curY = stY + rad*sin(t);

		double temp = curX - stX;
		double k = -(stY - curY)/temp,
			b = -(stX*curY - curX*stY)/temp;

		double newX;
		double dopX, dopY;
		if (t < PI)
		{
			newX = (poleY - b)/k;
		}	else if (t < 2*PI)
		{
			newX = (0.0 - b)/k;
		}	else
			newX = (poleY - b)/k;

		int st;
		if (newX > poleX)
		{
			newX = poleX;
			if (prevSt == 0)
				st = 0;
			else if (prevSt == 3)
				st = 0;
		} else if (newX < 0.0)
		{
			newX = 0.0;
			if (prevSt == 1)
				st = 2;
			else if (prevSt == 2)
				st = 2;
		} else
		{
			if (prevSt == 0)
				st = 1;
			else if (prevSt == 2)
				st = 3;
			else if (prevSt == 1)
				st = 1;
			else if (prevSt == 3)
				st = 3;
		}

		if (prevSt != st)
		{
			if (st == 1)
			{
				dopX = poleX;
				dopY = poleY;
				prevSt = st;
				isDopPoint = true;
			} else if (st == 2)
			{
				dopX = 0.0;
				dopY = poleY;
				prevSt = st;
				isDopPoint = true;
			} else if (st == 3)
			{
				dopX = 0.0;
				dopY = 0.0;
				prevSt = st;
				isDopPoint = true;
			} else if (st == 0)
			{
				dopX = poleX;
				dopY = 0.0;
				isDopPoint = true;
				prevSt = st;
			}
		}

		double newY = k*newX + b;
		
		if (isDopPoint)
		{
			glBegin(GL_POLYGON);
			glColor3d(0.1,0.1,0.1);
			glVertex2d(circleX,circleY);
			glVertex2d(curX,curY);
			glColor4d(0.76,0.76,0.76,0.7);
			glVertex2d(newX,newY);
			glVertex2d(dopX,dopY);
			glVertex2d(prevX,prevY);
			glEnd();
		} else
		{
			glBegin(GL_POLYGON);
			glColor3d(0.1,0.1,0.1);
			glVertex2d(circleX,circleY);
			glVertex2d(curX,curY);
			glColor4d(0.76,0.76,0.76,0.7);
			glVertex2d(newX,newY);
			glVertex2d(prevX,prevY);
			glEnd();
		}

		circleX = curX; circleY = curY;
		prevX = newX; prevY = newY;
	}
	glPopMatrix();

	glDisable(GL_BLEND);
}

Aim::~Aim()
{
}

void Aim :: draw() const
{
	if (isShown)
	{
		glPushMatrix();
		glTranslated(x,y,-3.0);
		glScaled(rad,rad*poleY/poleX / (dWindowY/dWindowX),1.0);

		glBegin(GL_LINE_STRIP);
		for (double t = 0.0; t < 2*PI + 0.1; t += 0.1)
			glVertex2d(cos(t),sin(t));
		glEnd();

		for (int i = 0; i < 6; ++i)
		{
			glBegin(GL_LINE_LOOP);
				glVertex2d(-biasX - 3.0/5.0 + i*wCeil,0.0);
				glVertex2d(-biasX - 3.0/5.0 + (i+1)*wCeil,0.0);
				glVertex2d(-biasX - 3.0/5.0 + (i+1)*wCeil,heightCeil[1]);
				glVertex2d(-biasX - 3.0/5.0 + i*wCeil,heightCeil[1]);
			glEnd();

			glBegin(GL_LINE_LOOP);
				glVertex2d(biasX + 3.0/5.0 - i*wCeil,0.0);
				glVertex2d(biasX + 3.0/5.0 - (i+1)*wCeil,0.0);
				glVertex2d(biasX + 3.0/5.0 - (i+1)*wCeil,heightCeil[1]);
				glVertex2d(biasX + 3.0/5.0 - i*wCeil,heightCeil[1]);
			glEnd();

			glBegin(GL_LINE_LOOP);
				glVertex2d(-biasX - 3.0/5.0 + i*wCeil,0.0);
				glVertex2d(-biasX - 3.0/5.0 + (i+1)*wCeil,0.0);
				glVertex2d(-biasX - 3.0/5.0 + (i+1)*wCeil,-heightCeil[0]);
				glVertex2d(-biasX - 3.0/5.0 + i*wCeil,-heightCeil[0]);
			glEnd();

			glBegin(GL_LINE_LOOP);
				glVertex2d(biasX +3.0/5.0 - i*wCeil,0.0);
				glVertex2d(biasX +3.0/5.0 - (i+1)*wCeil,0.0);
				glVertex2d(biasX +3.0/5.0 - (i+1)*wCeil,-heightCeil[0]);
				glVertex2d(biasX +3.0/5.0 - i*wCeil,-heightCeil[0]);
			glEnd();

			glBegin(GL_LINE_LOOP);
				glVertex2d(-biasX - 3.0/5.0 + i*wCeil,heightCeil[1] + biasY);
				glVertex2d(-biasX -3.0/5.0 + (i+1)*wCeil,heightCeil[1] + biasY);
				glVertex2d(-biasX -3.0/5.0 + (i+1)*wCeil,heightCeil[1] + biasY + heightCeil[2]);
				glVertex2d(-biasX -3.0/5.0 + i*wCeil,heightCeil[1] + biasY + heightCeil[2]);
			glEnd();

			glBegin(GL_LINE_LOOP);
				glVertex2d(biasX +3.0/5.0 - i*wCeil,heightCeil[1] + biasY);
				glVertex2d(biasX +3.0/5.0 - (i+1)*wCeil,heightCeil[1] + biasY);
				glVertex2d(biasX +3.0/5.0 - (i+1)*wCeil,heightCeil[1] + biasY + heightCeil[2]);
				glVertex2d(biasX +3.0/5.0 - i*wCeil,heightCeil[1] + biasY + heightCeil[2]);
			glEnd();

		}

		glBegin(GL_LINES);

			glVertex2d(-biasX,0.0);
			glVertex2d(-biasX,-0.5);

			glVertex2d(biasX,0.0);
			glVertex2d(biasX,-0.5);

		glEnd();

		glBegin(GL_LINES);

			glVertex2d(0.0,0.55);
			glVertex2d(0.0,0.45);

			glVertex2d(-0.05,0.5);
			glVertex2d(0.05,0.5);

			glVertex2d(0.1,-0.48);
			glVertex2d(0.55,-0.48);

		glEnd();

		glBegin(GL_LINE_STRIP);
			for (double t = 0.0; t < 9.1; t += 1.0)
				glVertex2d(0.07 + t/9.0*0.47,-0.45 + 0.25*exp(-0.4*t));
		glEnd();

		glPopMatrix();
		fogTry(x,y,rad);
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

void Aim :: load()
{
	unsigned char* data;
	unsigned width, height;
	person = lodepng_decode32_file(&data, &width, &height, fileName);
	glGenTextures(1,&person);
	glBindTexture(GL_TEXTURE_2D,person);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
	gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, width, height, GL_RGBA, GL_UNSIGNED_BYTE, data);
	delete data;
}

void Aim :: drawPicture() const
{
	if (isShown)
	{
		glPushMatrix();

		glTranslated(x,y,-3.0);
		glScaled(rad,rad*poleY/poleX / (dWindowY/dWindowX),1.0);

		int X1 = 0,Y1 = 0,X2= 1,Y2 = 1, Z = 1.0;

		glEnable( GL_TEXTURE_2D );
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	
		glBindTexture( GL_TEXTURE_2D, person);

		glPixelStorei( GL_UNPACK_ALIGNMENT, 1 ); 
		glBegin( GL_QUADS );

		glTexCoord2f(X1,Y2); glVertex2f(-1.0,-1.0);
		glTexCoord2f(X1,Y1); glVertex2f(-1.0,1.0);
		glTexCoord2f(X2,Y1); glVertex2f(1.0,1.0);
		glTexCoord2f(X2,Y2); glVertex2f(1.0,-1.0);
		glEnd();

		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

		glDisable(GL_BLEND);
		glDisable(GL_TEXTURE_2D);

		glPopMatrix();

		fogTry(x,y,rad);
	}
}