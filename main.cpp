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

BackgroundPointer b = BackgroundPointer(new Background());
TankPointer t = TankPointer(new Tank());

// ----------------------------------------------------------
// Function Prototypes
// ----------------------------------------------------------
void display();
void specialKeys();
void keyPress();

// ----------------------------------------------------------
// Global Variables
// ----------------------------------------------------------
double rotate_y=0; 
double rotate_x=0;

double startX = -0.5, startY = -0.5, startZ = -0.5;
double a = 1.0;
	
std :: vector<int> KeyDown(256);;

// ----------------------------------------------------------
// display() Callback function
// ----------------------------------------------------------
void display(){

	//  Clear screen and Z-buffer
	keyPress();
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	b->draw();
	t->draw();

	//glFlush();
	glutSwapBuffers();
	//Sleep(100);
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
}

void Init()
{
	glOrtho(0.0,1000.0,0.0,2.7,0.0,1000.0);
	//  Enable Z-buffer depth test
	glEnable(GL_DEPTH_TEST);

	t->load();
	b->load();
}

int main(int argc, char* argv[]){

	//  Initialize GLUT and process user parameters
	glutInit(&argc,argv);

	//  Request double buffered true color window with Z-buffer
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(1024,640);				
	glutInitWindowPosition(100,50);	

	// Create window
	glutCreateWindow("Awesome Cube");

	Init();

	// Callback functions
	glutDisplayFunc(display);
	glutIdleFunc(display);
	glutKeyboardFunc(key);
	glutKeyboardUpFunc(keyUp);

	//  Pass control to GLUT for events
	glutMainLoop();

	//  Return to OS
	return 0;

}