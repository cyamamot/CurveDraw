/*
Class that defines Bezier curve, a subclass of the Curve class
Given certain connected control points, create a smooth curve constrained by the control points using deCasteljau's algorithm
*/
#if !defined(BEZIER_H)
#define BEZIER_H

#include "Curve.h"

class Bezier : public Curve  
{
public:
	//draws curve based on control points using deCasteljau algorithm for some LOD (level of detail)
	void DrawCurve(int LOD);
	Bezier() {};
	virtual ~Bezier() {};

};

#endif
