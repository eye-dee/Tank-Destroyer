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

BackgroundPointer b = BackgroundPointer(new Background());
TankPointer t = TankPointer(new Tank());
AimPointer a = AimPointer(new Aim());

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

void fogTry()
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glBegin(GL_POLYGON);
	glColor3d(1.0,0.0,0.0);

	glVertex2d(100.0,100.0);
	glVertex2d(100.0,200.0);
	glVertex2d(300.0,200.0);
	glVertex2d(300.0,100.0);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor4d(0.56,0.56,0.56,0.0);

	glVertex2d(0.0,0.0);
	glVertex2d(0.0,poleY);
	glVertex2d(poleX,poleY);
	glVertex2d(poleX,0.0);

	glEnd();

	glDisable(GL_BLEND);
}

double startX = -0.5, startY = -0.5, startZ = -0.5;
	
std :: vector<int> KeyDown(256);;

void display(){

	//  Clear screen and Z-buffer
	keyPress();
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	/*b->draw();
	t->draw();
	a->draw();*/

	fogTry();


	glEnable(GL_FOG);                       // Включает туман (GL_FOG)
	glFogi(GL_FOG_MODE, fogMode[fogfilter]);// Выбираем тип тумана
	glFogfv(GL_FOG_COLOR, fogColor);        // Устанавливаем цвет тумана
	glFogf(GL_FOG_DENSITY, 1.0);          // Насколько густым будет туман
	glHint(GL_FOG_HINT, GL_DONT_CARE);      // Вспомогательная установка тумана
	glFogf(GL_FOG_START, 1.0f);             // Глубина, с которой начинается туман
	glFogf(GL_FOG_END, 5.0f);               // Глубина, где туман заканчивается.

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
	glClearColor(0.5f,0.5f,0.5f,1.0f);      // Будем очищать экран, заполняя его цветом тумана. ( Изменено )

	glOrtho(0.0,poleX,0.0,poleY,0.0,poleZ);
	//  Enable Z-buffer depth test
	//glEnable(GL_DEPTH_TEST);

	/*t->load();
	b->load();
	a->load();*/
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
}

void motion(int x, int y)
{
	a->setX(x);
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