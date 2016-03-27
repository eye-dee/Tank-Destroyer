#include "Tank.h"
#include <glut.h>
#include <math.h>

#include "lodepng.h"

Tank::Tank() : x(350.0),
	y(250.0),
	z(600.0),
	V(0.01),
	fileName("abrams90.png"),
	angle(PI/4.0),
	a(3.0)
{
}

Tank::Tank(double setX, double setY, double setZ) : x(setX),
	y(setY),
	z(setZ)
{
}


Tank::~Tank()
{
}

void Tank :: load()
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

void Tank :: draw() const
{
	glPushMatrix();

	glTranslated(x,y,-1.0);

	auto hScaled = (max-z)/max*poleY;
	//glScaled(40*a,hScaled,a);
	//std :: cout << hScaled << '\n';
	glScaled(hScaled*a,hScaled,a);

	int X1 = 0,Y1 = 0,X2= 1,Y2 = 1, Z = 1.0;

	glEnable( GL_TEXTURE_2D );
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	
	glBindTexture( GL_TEXTURE_2D, person);

	glPixelStorei( GL_UNPACK_ALIGNMENT, 1 ); 
	glBegin( GL_QUADS );

	glTexCoord2f(X1,Y2); glVertex2f(0.0,0.0);
	glTexCoord2f(X1,Y1); glVertex2f(0.0,1.0);
	glTexCoord2f(X2,Y1); glVertex2f(1.0,1.0);
	glTexCoord2f(X2,Y2); glVertex2f(1.0,0.0);
	glEnd();

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);

	glPopMatrix();
}

void Tank ::forward()
{
	x += V*cos(angle);
	z -= V*sin(angle);
}
void Tank ::backward()
{
	x -= V*cos(angle);
	z += V*sin(angle);
}