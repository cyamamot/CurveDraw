/*
Class that defines B-Splines, a subclass of the Curves class
B-Splines have local control, every segment, excluding ends, correspond to a curve segment of the total curve
*/
#if !defined(BSPLINE_H)
#define BSPLINE_H

#include "Curve.h"


class Bspline : public Curve  
{
protected:
	//drawws segment of control curve using every 4 consecutive control points 
    void drawSegment(std::vector<ControlPoint>::iterator controlpoint1, std::vector<ControlPoint>::iterator controlpoint2, std::vector<ControlPoint>::iterator controlpoint3, std::vector<ControlPoint>::iterator controlpoint4, int LOD);

public:
	//draws curve by drawing each segment of the control shape
	void DrawCurve(int LOD);
	Bspline() {};
	virtual ~Bspline() {};

};

#endif 
