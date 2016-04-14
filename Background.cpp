#include "Background.h"
#include "lodepng.h"
#include <iostream>
#include <glut.h>
#include <algorithm>
#include <math.h>

#include "spline.h"

Background::Background() : fileName("picture/back.png"), isBondBlood(false)
{
	speedFileName[0] = "picture/VT.png";
	speedFileName[1] = "picture/κμ_χ.png";
	speedFileName[2] = "picture/5.png";
	speedFileName[3] = "picture/10.png";
	speedFileName[4] = "picture/15.png";
	speedFileName[5] = "picture/20.png";
	speedFileName[6] = "picture/25.png";
	speedFileName[7] = "picture/30.png";
	speedFileName[8] = "picture/35.png";
	speedFileName[9] = "picture/40.png";

	speedFileName[10] = "picture/VW.png";
	speedFileName[11] = "picture/μ_ρ.png";
	speedFileName[12] = "picture/1W.png";
	speedFileName[13] = "picture/2W.png";
	speedFileName[14] = "picture/3W.png";
	speedFileName[15] = "picture/4W.png";
	speedFileName[16] = "picture/5W.png";

	speedFileName[17] = "picture/0WD.png";
	speedFileName[18] = "picture/90WD.png";
	speedFileName[19] = "picture/180WD.png";
	speedFileName[20] = "picture/270WD.png";
}

Background::~Background()
{
}

void Background :: load()
{
	curTankSpeed = /*2 + random(8)*/2;
	curWindSpeed = TANK_N + 2 + random(5);
	curWindDir = TANK_N + WIND_N + random(4);
	curTankDir = /*random(5)*/1;

	unsigned char* data;
	unsigned width, height;
	person = lodepng_decode32_file(&data, &width, &height, fileName);

	glGenTextures(1,&person);
	glBindTexture(GL_TEXTURE_2D,person);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
	gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, width, height, GL_RGBA, GL_UNSIGNED_BYTE, data);

	for (int i = 0; i < TANK_N + WIND_N + DIR_N; ++i)
	{
		speedId[i] = lodepng_decode32_file(&data, &width, &height, speedFileName[i]);

		glGenTextures(1,&(speedId[i]));
		glBindTexture(GL_TEXTURE_2D,speedId[i]);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
		gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, width, height, GL_RGBA, GL_UNSIGNED_BYTE, data);
	}

	delete data;

	bondX = new double[N];
	bondY = new double[N];
	bondB = new double[N];
	bondC = new double[N];
	bondD = new double[N];

	int i = 0;
	for (double t = 0.0; t < POLE_X + bondH; ++i, t += bondH)
	{
		bondX[i] = t;
		bondY[i] = f(t);
	};

	int flag;
	spline(N,0,0,0,0,bondX,bondY,bondB,bondC,bondD, &flag);

	if (flag != 0)
		exit(-1);
}

void Background :: draw() const
{
	double X1 = 0.0,Y1 = 0,X2= 1,Y2 = 1, Z = 1.0;

	glPushMatrix();
	glTranslated(0.0,0.0,-5.0);

	glEnable( GL_TEXTURE_2D );
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	
	glBindTexture( GL_TEXTURE_2D, person);

	glPixelStorei( GL_UNPACK_ALIGNMENT, 1 ); 
	glBegin( GL_QUADS );

	glTexCoord2d(X1,Y2); glVertex2f(0.0,0.0);
	glTexCoord2d(X1,Y1); glVertex2f(0.0,POLE_Y);
	glTexCoord2d(X2,Y1); glVertex2f(POLE_X,POLE_Y);
	glTexCoord2d(X2,Y2); glVertex2f(POLE_X,0.0);
	glEnd();

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);

	glPopMatrix();
}

void Background :: drawSpeed() const
{
	double X1 = 0.0,Y1 = 0,X2= 1,Y2 = 1, Z = 1.0;
	glPushMatrix();

		/*SPEED TANK*/
		glTranslated(SPEED_POS_X,SPEED_POS_Y,-0.5);
		glScaled(TEXT_SIZE,TEXT_SIZE,1.0);

		glEnable( GL_TEXTURE_2D );
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	
		glBindTexture( GL_TEXTURE_2D, speedId[0]);

		glPixelStorei( GL_UNPACK_ALIGNMENT, 1 ); 
		glBegin( GL_QUADS );

		glTexCoord2d(X1,Y2); glVertex2f(0.0,0.0);
		glTexCoord2d(X1,Y1); glVertex2f(0.0,1.0);
		glTexCoord2d(X2,Y1); glVertex2f(1.0,1.0);
		glTexCoord2d(X2,Y2); glVertex2f(1.0,0.0);
		glEnd();

		glBindTexture( GL_TEXTURE_2D, speedId[curTankSpeed]);

		glPixelStorei( GL_UNPACK_ALIGNMENT, 1 ); 
		glBegin( GL_QUADS );

		glTexCoord2d(X1,Y2); glVertex2f(1.0,0.0);
		glTexCoord2d(X1,Y1); glVertex2f(1.0,1.0);
		glTexCoord2d(X2,Y1); glVertex2f(2.0,1.0);
		glTexCoord2d(X2,Y2); glVertex2f(2.0,0.0);
		glEnd();

		glBindTexture( GL_TEXTURE_2D, speedId[1]);

		glPixelStorei( GL_UNPACK_ALIGNMENT, 1 ); 
		glBegin( GL_QUADS );

		glTexCoord2d(X1,Y2); glVertex2f(2.0,0.0);
		glTexCoord2d(X1,Y1); glVertex2f(2.0,1.0);
		glTexCoord2d(X2,Y1); glVertex2f(3.0,1.0);
		glTexCoord2d(X2,Y2); glVertex2f(3.0,0.0);
		glEnd();

		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

		/*SPEED WIND*/

		glEnable( GL_TEXTURE_2D );
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	
		glBindTexture( GL_TEXTURE_2D, speedId[TANK_N]);

		glPixelStorei( GL_UNPACK_ALIGNMENT, 1 ); 
		glBegin( GL_QUADS );

		glTexCoord2d(X1,Y2); glVertex2f(0.0,-1.0);
		glTexCoord2d(X1,Y1); glVertex2f(0.0,0.0);
		glTexCoord2d(X2,Y1); glVertex2f(1.0,0.0);
		glTexCoord2d(X2,Y2); glVertex2f(1.0,-1.0);
		glEnd();

		glBindTexture( GL_TEXTURE_2D, speedId[curWindSpeed]);

		glPixelStorei( GL_UNPACK_ALIGNMENT, 1 ); 
		glBegin( GL_QUADS );

		glTexCoord2d(X1,Y2); glVertex2f(1.0,-1.0);
		glTexCoord2d(X1,Y1); glVertex2f(1.0,0.0);
		glTexCoord2d(X2,Y1); glVertex2f(2.0,0.0);
		glTexCoord2d(X2,Y2); glVertex2f(2.0,-1.0);
		glEnd();

		glBindTexture( GL_TEXTURE_2D, speedId[TANK_N + 1]);

		glPixelStorei( GL_UNPACK_ALIGNMENT, 1 ); 
		glBegin( GL_QUADS );

		glTexCoord2d(X1,Y2); glVertex2f(2.0,-1.0);
		glTexCoord2d(X1,Y1); glVertex2f(2.0,0.0);
		glTexCoord2d(X2,Y1); glVertex2f(3.0,0.0);
		glTexCoord2d(X2,Y2); glVertex2f(3.0,-1.0);
		glEnd();
		
		/*Wind Dir*/
		glBindTexture( GL_TEXTURE_2D, speedId[curWindDir]);

		glPixelStorei( GL_UNPACK_ALIGNMENT, 1 ); 
		glBegin( GL_QUADS );

		glTexCoord2d(X1,Y2); glVertex2f(3.0,-1.0);
		glTexCoord2d(X1,Y1); glVertex2f(3.0,0.0);
		glTexCoord2d(X2,Y1); glVertex2f(4.0,0.0);
		glTexCoord2d(X2,Y2); glVertex2f(4.0,-1.0);
		glEnd();

		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

		glDisable(GL_BLEND);
		glDisable(GL_TEXTURE_2D);
		/**/
	glPopMatrix();
}

void Background :: drawBondBlood() const
{
	if (isBondBlood)
	{
		static double bondI = 0.0;

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glPushMatrix();
				glTranslated(0.0,0.0,-0.3);
				//glBegin(GL_POLYGON);
				//glBegin(GL_LINE_STRIP);
				glBegin(GL_LINES);

					int last;

					double start, end;
					for (double t = 0.0; t < POLE_X; t += 1.0)
					{
						start = seval(N,t,bondX,bondY,bondB,bondC,bondD,&last);
						end = /*seval(N,t,bondX[1],bondY[1],bondB[1],bondC[1],bondD[1],&last)*/0.0;
						glColor4d(1.0,0.0,0.0,0.7);
						glVertex2d(t,start + bondI*(end-start));
						glColor4d(0.9,0.05,0.05,0.4);
						glVertex2d(t,POLE_Y);
					}	
				glEnd();

				if (bondI < 1.0)
					bondI += bondIH;

				glBegin(GL_LINE_STRIP);
					glColor3d(0.0,1.0,0.0);
	
						for (int i = 0; i < N; ++i)
							glVertex2d(bondX[i], bondY[i]-50.0);	

				glEnd();

			glPopMatrix();

		glDisable(GL_BLEND);
	}
}