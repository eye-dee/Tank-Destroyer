#include "Tank.h"
#include <glut.h>
#include <math.h>

#include "Fire.h"
#include "lodepng.h"

#include "spline.h"

Tank::Tank() : x(350.0),
	y(250.0),
	z(600.0),
	V(0.05),
	curState(2),
	angle(PI/2.0)
{
	fileName[0] = "picture/abrams0.png";
	fileName[1] = "picture/abrams45.png";
	fileName[2] = "picture/abrams90.png";

	y = (5.0/30.0*z + 1200.0/9.0);
}

Tank::Tank(double setX, double setY, double setZ) : x(setX),
	y(setY),
	z(setZ)
{
	fileName[0] = "picture/abrams0.png";
	fileName[1] = "picture/abrams45.png";
	fileName[2] = "picture/abrams90.png";
	y = (5.0/3.0*z + 2550.0/9.0);
}


Tank::~Tank()
{
}

void Tank :: load()
{
	for (int i = 0; i < 3; ++i)
	{
		unsigned char* data;
		unsigned width, height;
		person[i] = lodepng_decode32_file(&data, &width, &height, fileName[i]);
		glGenTextures(1,&(person[i]));
		glBindTexture(GL_TEXTURE_2D,person[i]);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
		gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, width, height, GL_RGBA, GL_UNSIGNED_BYTE, data);
		delete data;
	}
}

void Tank :: draw() const
{
	static int last;
	glPushMatrix();

	glTranslated(x,y,-4.0);

	//auto hScaled = 2.7*(max-z)/max*POLE_Y;
	auto hScaled = seval(NdistToSize,z,splineDist, splineSize, bDistToSize, cDistToSize, dDistToSize, &last)/curPart;
	//glScaled(40*a,hScaled,a);
	//std :: cout << hScaled << '\n';
	glScaled(hScaled*aimRad*curAspect,hScaled*aimRad/**curAspect*/,1.0);

	int X1 = 0,Y1 = 0,X2= 1,Y2 = 1, Z = 1.0;

	glEnable( GL_TEXTURE_2D );
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	
	glBindTexture( GL_TEXTURE_2D, person[curState/2]);

	glPixelStorei( GL_UNPACK_ALIGNMENT, 1 ); 
	glBegin( GL_QUADS );

	if (curState%2 == 0)
	{
		glTexCoord2f(X1,Y2); glVertex2f(-1.0,-1.0);
		glTexCoord2f(X1,Y1); glVertex2f(-1.0,1.0);
		glTexCoord2f(X2,Y1); glVertex2f(1.0,1.0);
		glTexCoord2f(X2,Y2); glVertex2f(1.0,-1.0);
	} else
	{
		glTexCoord2f(X2,Y2); glVertex2f(-1.0,-1.0);
		glTexCoord2f(X2,Y1); glVertex2f(-1.0,1.0);
		glTexCoord2f(X1,Y1); glVertex2f(1.0,1.0);
		glTexCoord2f(X1,Y2); glVertex2f(1.0,-1.0);
	}
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

	y = (5.0/30.0*z + 1200.0/9.0);
	//y = 4.0/5.0*z;
}
void Tank ::backward()
{
	x -= V*cos(angle);
	z += V*sin(angle);

	y = (5.0/30.0*z + 1200.0/9.0);
	//y = 4.0/5.0*z;
}