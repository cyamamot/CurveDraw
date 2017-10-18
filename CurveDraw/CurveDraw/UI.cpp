#include "UI.h"
#include "Bezier.h"
#include "Bspline.h"
#include "BezierSubDiv.h"
#include <iostream>
#include <string> 

//all static members initialized here
int UI::height = 600;
int UI::width = 600;
int UI::LastX = 0;
int UI::LastY = 0;
std::string UI::NewMode = "";
std::string UI::NewLOD = "";
std::string UI::NewModeLOD = "";
int UI::LOD = 5;
GLuint UI::colorPos;
Curve* UI::CurveOnScreen = NULL;


UI::UI() {
}

UI::~UI() {
}

void UI::keyboard( unsigned char key, int x, int y )
{
	switch(key) {
	case '0':
		Reset();
		if (CurveOnScreen) delete CurveOnScreen;
		CurveOnScreen = new Curve();
		CurveOnScreen->setShaderReferences(colorPos);
		NewMode = "Straight-";
		break;
	case '1':
		Reset();
		if (CurveOnScreen) delete CurveOnScreen;
		CurveOnScreen = new Bezier();
		CurveOnScreen->setShaderReferences(colorPos);
		NewMode = "Bezier-";
		break;
	case '2':
		Reset();
		if (CurveOnScreen) delete CurveOnScreen;
		CurveOnScreen = new Bspline();
		CurveOnScreen->setShaderReferences(colorPos);
		NewMode = "B-Spline-";
		break;
	case '3':
		Reset();
		if (CurveOnScreen) delete CurveOnScreen;
		CurveOnScreen = new BezierSubDiv();
		CurveOnScreen->setShaderReferences(colorPos);
		NewMode = "Sub Div Bezier-";
		break;
	case '+':
		LOD++;
		break;
	case '-':
		LOD--;
		break;
	case 'q':
		exit(0) ;
		break ;
	}
	if (LOD < 1) LOD = 1;
	else if (LOD > 50) LOD = 50;
	NewLOD = std::to_string(LOD);
	PrintMode();
	glutPostRedisplay();
}
 
void UI::Reset() {
	LOD = 5;
}

void UI::PrintMode() 
{
	NewModeLOD = NewMode + NewLOD;
	std::cout << "\r" << NewModeLOD << std::string(10, ' ');
}

void UI::PrintInstructions()
{
	std::cout << "Controls : " << std::endl;
	std::cout << "Left click mouse on canvas to draw point" << std::endl;
	std::cout << "Left click mouse on a white point and drag to move" << std::endl;
	std::cout << "Right click mouse on a white point to delete it" << std::endl;
	std::cout << "Press 'q' to exit program" << std::endl;
	std::cout << std::endl;
	std::cout << "Drawing Modes : " << std::endl;
	std::cout << "Numpad 0 = Draw Straight Lines" << std::endl;
	std::cout << "Numpad 1 = Draw Bezier Curve" << std::endl;
	std::cout << "Numpad 2 = Draw B-Spline Curve" << std::endl;
	std::cout << "Numpad 3 = Draw SubDivided Bezier Curve" << std::endl;
	std::cout << "+ = increase Level of Detail" << std::endl;
	std::cout << "- = decrease Level of Detail" << std::endl;
	std::cout << std::endl;
	std::cout << "WARNING : current drawing mode will be displayed on console." << std::endl;
	std::cout << "resizing console may affect console output layout but not drawing functionality" << std::endl;
	std::cout << "Please click on canvas before attempting input" << std::endl;
	std::cout << std::endl;
	std::cout << "Current Drawing Mode : " << std::endl;
}

void UI::Resize(int w, int h) {
	width = w;
	height = h;
	glViewport( 0,0, w, h );
	glutPostRedisplay();
}

//follows mouse movement and location onscreen and attempts to update values of control points of curve
void UI::passiveMotion(int x, int y) {
	if (CurveOnScreen != NULL) {
		CurveOnScreen->UpdatePoint(x / (float)width, (height - y) / (float)height);
	}
	glutPostRedisplay();
}

//moves control point with mouse
//y axis is inverted because opengl screen inverts y axis for on screen position
void UI::drag(int x, int y) {
	if (CurveOnScreen != NULL)
	{
		float normx = (float)(x - LastX) / (float)UI::width;
		float normy = (float)(y - LastY) / (float)UI::height;
		CurveOnScreen->MovePoint(normx, -normy);
		LastX = x;
		LastY = y;
		glutPostRedisplay();
	}
}

void UI::mouse(int button, int state, int x, int y) {
	if (CurveOnScreen != NULL && state == GLUT_DOWN) {
		//add point on left click
		if (button == GLUT_LEFT_BUTTON) {
			float normx = (float)x / (float)UI::width;
			float normy = (float)y / (float)UI::height;
			CurveOnScreen->AddPoint(normx, 1.0f - normy);
		}
		//delete current selected point on right click
		if (button == GLUT_RIGHT_BUTTON) {
			float normx = (float)x / (float)UI::width;
			float normy = (float)y / (float)UI::height;
			CurveOnScreen->UpdatePoint(normx, 1.0f - normy);
			CurveOnScreen->DeletePoint();
		}
	}
	LastX = x;
	LastY = y;
	glutPostRedisplay();
}



