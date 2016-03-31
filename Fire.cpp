#include "Fire.h"
#include "lodepng.h"
#include "const.h"

#include <stdlib.h>
#include <string.h>
#include <glut.h>

Fire::Fire() : curState(0), speed(2)
{
	char* temp,* str;
	for (int i = 0; i < 27; ++i)
	{
		str = new char[11];
		strcpy(str,"explosion/");
		str[10] = 0;
		temp = new char[3];
		itoa(i,temp,10);
		strcat(temp, ".png");
		strcat(str,temp);

		fileName[i] = str;
	}
}


Fire::~Fire()
{
}

void Fire :: load()
{
	unsigned char* data;
	for (int i = 0; i < 27; ++i)
	{
		unsigned width, height;
		person[i] = lodepng_decode32_file(&data, &width, &height, fileName[i]);
		glGenTextures(1,&(person[i]));
		glBindTexture(GL_TEXTURE_2D,person[i]);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
		gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, width, height, GL_RGBA, GL_UNSIGNED_BYTE, data);
	}

	delete data;
}

void Fire :: draw()
{
	glPushMatrix();

	glTranslated(x,y,0.0);

	glScaled(size*pictureAspect,size,1.0);

	int X1 = 0,Y1 = 0,X2= 1,Y2 = 1, Z = 1.0;

	glEnable( GL_TEXTURE_2D );
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	
	glBindTexture( GL_TEXTURE_2D, person[curState/speed]);

	glPixelStorei( GL_UNPACK_ALIGNMENT, 1 );
	glBegin( GL_QUADS );

	glTexCoord2f(X1,Y2); glVertex2f(1.0,0.0);
	glTexCoord2f(X1,Y1); glVertex2f(1.0,2.0);
	glTexCoord2f(X2,Y1); glVertex2f(-1.0,2.0);
	glTexCoord2f(X2,Y2); glVertex2f(-1.0,0.0);
	glEnd();

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);

	glPopMatrix();

	nextState();
}