/*
Class that defines Bezier curve, a subclass of the Curve class
Given certain connected control points, create a smooth curve constrained by the control points using recursive subdivision
*/
#if !defined(BEZIERSUBDIV_H)
#define BEZIERSUBDIV_H

#include "Curve.h"

class BezierSubDiv : public Curve  
{
public:
	//draws the curve by continuously subdividing curve into smaller bezier curves and recursively solving for each portion
	void DrawCurve(int LOD);
	BezierSubDiv() {};
	virtual ~BezierSubDiv() {};
};

#endif
