#include "Background.h"
#include "lodepng.h"
#include <iostream>
#include <glut.h>
#include <algorithm>
#include <math.h>

Background::Background() : fileName("back.png")
{
}

Background::~Background()
{
}

void Background :: load()
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

void Background :: draw()
{
	double X1 = 0.0,Y1 = 0,X2= 1,Y2 = 1, Z = 1.0;

	glPushMatrix();
	glTranslated(0.0,0.0,-1.0);

	glEnable( GL_TEXTURE_2D );
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	
	glBindTexture( GL_TEXTURE_2D, person);

	glPixelStorei( GL_UNPACK_ALIGNMENT, 1 ); 
	glBegin( GL_QUADS );

	glTexCoord2d(X1,Y2); glVertex2f(0.0,0.0);
	glTexCoord2d(X1,Y1); glVertex2f(0.0,2.7);
	glTexCoord2d(X2,Y1); glVertex2f(1000.0,2.7);
	glTexCoord2d(X2,Y2); glVertex2f(1000.0,0.0);
	glEnd();

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);

	glPopMatrix();
}