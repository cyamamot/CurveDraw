/*
class that defines base Curve class
contains it list of control points, its currently selected point, and color
responsible for control point manipulation and base curve drawing functions
*/
#if !defined(CURVE_H)
#define CURVE_H

#include <vector>
#include <math.h>
#include "../CurveDraw/Dependencies/glew/glew.h"
#include "../CurveDraw/Dependencies/glut/glut.h"
#include "ControlPoint.h"

class Curve  
{
protected:
	std::vector<ControlPoint> points;
	std::vector<ControlPoint>::iterator SelectedPoint;
    bool HasPointSelected ;
	GLuint colorPos;
	const float LINE_WIDTH = 5.0f;
	
public:
	Curve();
	virtual ~Curve();
	//overridable curve DrawCurve function
	virtual void DrawCurve(int LOD);
	//add control point to list
	void AddPoint(float x, float y);
	//delete currently selected control point (control shape will adjust according to input order or remaining points)
	void DeletePoint();
	//moves currently selected control point
	void MovePoint(float dx, float dy);
	//updats which point is currently selected
	void UpdatePoint(float x, float y);
	//connects all control points
	void ConnectControlPoints();
	//base function used to connect points in curve approximation
    void DrawCurveLine(float x1, float y1, float x2, float y2) ;
	void setShaderReferences(GLuint);
};

#endif

