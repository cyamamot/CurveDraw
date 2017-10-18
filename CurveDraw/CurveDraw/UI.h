/*
Class that defines the UI of the program (how the user can interact with what is drawn on screen)
Defines canvas size values, keyboard input, and mouse movements
*/
#if !defined(CLASS_UI)
#define CLASS_UI

#include "Curve.h"
#include "../CurveDraw/Dependencies/glut/glut.h"

class UI {
public:
	static GLuint colorPos; 
	static int height;
	static int width;
	//last recorded position of the mouse on screen
	static int LastX;
	static int LastY;
	//to be outputted mode
	static std::string NewMode;
	//to be outputted LOD
	static std::string NewLOD;
	//combined string
	static std::string NewModeLOD;
	static int LOD;

	static Curve* CurveOnScreen;
	UI();
	virtual ~UI();
	//defines keyboard inputs and their actions
	static void keyboard(unsigned char key, int x, int y);
	static void Reset();
	static void PrintMode();
	static void PrintInstructions();
	//resizes canvas and images 
	static void Resize(int w, int h);
	//watches movement of mouse and updates screen according to its location
	static void passiveMotion(int x, int y);
	//uses mouse movement to drag control points
	static void drag(int x, int y);
	//defines mouse click inputs and their actions
	static void mouse(int button, int state, int x, int y);
};

#endif 

