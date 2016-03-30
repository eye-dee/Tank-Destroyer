#include <stdio.h>
#include <stdarg.h>
#include <math.h>
#include <iostream>
#define GL_GLEXT_PROTOTYPES
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <glut.h>
#endif

#include <vector>
#include <Windows.h>
#include "const.h"
#include "Tank.h"
#include "Background.h"
#include "Aim.h"
#include "Shell.h"

BackgroundPointer b = BackgroundPointer(new Background());
TankPointer t = TankPointer(new Tank());
AimPointer a = AimPointer(new Aim());
ShellPointer s = ShellPointer(new Shell());

bool   gp;                              // G Нажата? ( Новое )
GLuint filter;                          // Используемый фильтр для текстур
GLuint fogMode[]= { GL_EXP, GL_EXP2, GL_LINEAR }; // Хранит три типа тумана
GLuint fogfilter= 2;                    // Тип используемого тумана
GLfloat fogColor[4]= {0.5f, 0.5f, 0.5f, 1.0f}; // Цвет тумана

void display();
void specialKeys();
void keyPress();
double rotate_y=0; 
double rotate_x=0;

double stX = 0.0, stY = 0.0;

double startX = -0.5, startY = -0.5, startZ = -0.5;
	
std :: vector<int> KeyDown(256);;

void display(){

	//  Clear screen and Z-buffer
	keyPress();
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	t->forward();
	//b->draw();
	t->draw();
	a->drawPicture();
	s->stepForward();
	s->draw();

	glutSwapBuffers();
}

void key(unsigned char key, int x, int y){
	KeyDown[key] = 1;
}
void keyUp(unsigned char key, int x, int y){
	KeyDown[key] = 0;
}
void keyPress() 
{
//  Right arrow - increase rotation by 5 degree
	if (KeyDown['6'])
		rotate_y += 0.1;

	//  Left arrow - decrease rotation by 5 degree
	else if (KeyDown['4'])
		rotate_y -= 0.1;

	else if (KeyDown['8'] )
		rotate_x += 0.1;

	else if (KeyDown['5'])
		rotate_x -= 0.1;

	else if (KeyDown['w'])
		t->forward();
	else if (KeyDown['s'])
		t->backward();

	if (KeyDown['g'] && !gp)                   // Нажата ли клавиша "G"?
	{
		   gp=TRUE;                         // gp устанавливаем в TRUE
		   fogfilter+=1;                    // Увеличиние fogfilter на 1
		   if (fogfilter>2)                 // fogfilter больше 2 ... ?
		   {
				  fogfilter=0;              // Если так, установить fogfilter в ноль
		   }
		   glFogi (GL_FOG_MODE, fogMode[fogfilter]); // Режим тумана
	}
	if (!KeyDown['g'])                         // Клавиша "G" отпущена?
	{
		   gp=FALSE;                        // Если да, gp установить в FALSE
	}
}

void Init()
{
	std :: cout << "It's started\n";

	glClearColor(0.5f,0.5f,0.5f,1.0f);      // Будем очищать экран, заполняя его цветом тумана. ( Изменено )

	glOrtho(0.0,poleX,0.0,poleY,0.0,poleZ);
	//  Enable Z-buffer depth test
	glEnable(GL_DEPTH_TEST);

	t->load();
	//b->load();
	a->load();
}

void mouse(int but, int st, int x,int y)
{
	if (but == GLUT_RIGHT_BUTTON)
	{
		if (st == GLUT_DOWN)
		{
			a->changeShown();
		}
	}
	if (but == GLUT_LEFT_BUTTON)
	{
		if (st == GLUT_DOWN)
		{
			s->fire(stX);
		}
	}
}

void motion(int x, int y)
{
	stX = x;
	a->setX(x);
	stY = iWindowY - y;
	a->setY(iWindowY - y);
}

int main(int argc, char* argv[]){

	//  Initialize GLUT and process user parameters
	glutInit(&argc,argv);

	//  Request double buffered true color window with Z-buffer
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(iWindowX,iWindowY);				
	glutInitWindowPosition(50,50);	

	// Create window
	glutCreateWindow("Awesome Cube");

	Init();

	// Callback functions
	glutDisplayFunc(display);
	glutIdleFunc(display);
	glutKeyboardFunc(key);
	glutKeyboardUpFunc(keyUp);
	glutMouseFunc(mouse);
	glutPassiveMotionFunc(motion);

	//  Pass control to GLUT for events
	glutMainLoop();

	//  Return to OS
	return 0;

}