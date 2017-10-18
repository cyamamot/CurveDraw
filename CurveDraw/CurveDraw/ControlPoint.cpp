#include <vector>
#include "../CurveDraw/Dependencies/glew/glew.h"
#include "../CurveDraw/Dependencies/glut/glut.h"
#include <math.h>
#include "ControlPoint.h"
#include "UI.h"


float ControlPoint::RADIUS = 0.05f;

ControlPoint::ControlPoint(float xpos, float ypos)
{
	x = xpos;
	y = ypos;
	Selected = false;
	colorPos = UI::colorPos;
}

ControlPoint::~ControlPoint()
{
}

void ControlPoint::DrawPoint() {
	std::vector<float> coords;
	//Draws a red diamond around the selected point
	if (Selected) {
		glUniform3f(colorPos, 1.0, 0.0, 0.0);
		coords.push_back(x + RADIUS);
		coords.push_back(y);
		coords.push_back(x);
		coords.push_back(y + RADIUS);
		coords.push_back(x - RADIUS);
		coords.push_back(y);
		coords.push_back(x);
		coords.push_back(y - RADIUS);
		coords.push_back(x + RADIUS);
		coords.push_back(y);
		glBufferData(GL_ARRAY_BUFFER, coords.size() * sizeof(float), &coords[0], GL_STATIC_DRAW);
		glDrawArrays(GL_LINE_STRIP, 0, coords.size() / 2);
	}
	//draws the actual point
	glUniform3f(colorPos, 1.0, 1.0, 1.0);
	coords.clear();
	coords.push_back(x);
	coords.push_back(y);
	glBufferData(GL_ARRAY_BUFFER, coords.size() * sizeof(float), &coords[0], GL_STATIC_DRAW);
	glPointSize(LINE_WIDTH);
	glDrawArrays(GL_POINTS, 0, coords.size() / 2);
	coords.clear();
}


