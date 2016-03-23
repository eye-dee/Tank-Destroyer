#include "Tank.h"
#include <glut.h>
#include <math.h>

Tank::Tank() : x(350.0),
	y(1.0),
	z(500.0),
	V(0.01),
	angle(PI/4.0),
	a(5.0)
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

void Tank :: draw() const
{
	glPushMatrix();
	// Other Transformations
	// glTranslatef( 0.1, 0.0, 0.0 );      // Not included
	// glRotatef( 180, 0.0, 1.0, 0.0 );    // Not included

	glTranslated(x,y,0.0);

	auto hScaled = (max-z)/max*tankH;
	glScaled(15*a,hScaled,a);

	// Other Transformations
	// glScalef( 2.0, 2.0, 0.0 );          // Not included

	//Multi-colored side - FRONT
	glBegin(GL_POLYGON);

	glColor3f( 1.0, 0.0, 0.0 );     glVertex3f(  1.0, 0.0, 0.0 );      // P1 is red
	glColor3f( 0.0, 1.0, 0.0 );     glVertex3f(  1.0,  1.0, 0.0 );      // P2 is green
	glColor3f( 0.0, 0.0, 1.0 );     glVertex3f( 0.0,  1.0, 0.0 );      // P3 is blue
	glColor3f( 1.0, 0.0, 1.0 );     glVertex3f( 0.0, 0.0, 0.0 );      // P4 is purple

	glEnd();

	// White side - BACK
	glBegin(GL_POLYGON);
	glColor3f(   1.0,  1.0, 1.0 );
	glVertex3f(  1.0, 0.0, 1.0 );
	glVertex3f(  1.0,  1.0, 1.0 );
	glVertex3f( 0.0,  1.0, 1.0 );
	glVertex3f( 0.0, 0.0, 1.0 );
	glEnd();

	// Purple side - RIGHT
	glBegin(GL_POLYGON);
	glColor3f(  1.0,  0.0,  1.0 );
	glVertex3f( 1.0, 0.0, 0.0 );
	glVertex3f( 1.0,  1.0, 0.0 );
	glVertex3f( 1.0,  1.0,  1.0 );
	glVertex3f( 1.0, 0.0,  1.0 );
	glEnd();

	// Green side - LEFT
	glBegin(GL_POLYGON);
	glColor3f(   0.0,  1.0,  0.0 );
	glVertex3f( 0.0, 0.0,  1.0 );
	glVertex3f( 0.0,  1.0,  1.0 );
	glVertex3f( 0.0,  1.0, 0.0 );
	glVertex3f( 0.0, 0.0, 0.0 );
	glEnd();

	// Blue side - TOP
	glBegin(GL_POLYGON);
	glColor3f(   0.0,  0.0,  1.0 );
	glVertex3f(  1.0,  1.0,  1.0 );
	glVertex3f(  1.0,  1.0, 0.0 );
	glVertex3f( 0.0,  1.0, 0.0 );
	glVertex3f( 0.0,  1.0,  1.0 );
	glEnd();

	// Red side - BOTTOM
	glBegin(GL_POLYGON);
	glColor3f(   1.0,  0.0,  0.0 );
	glVertex3f(  1.0, 0.0, 0.0 );
	glVertex3f(  1.0, 0.0,  1.0 );
	glVertex3f( 0.0, 0.0,  1.0 );
	glVertex3f( 0.0, 0.0, 0.0 );
	glEnd();

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