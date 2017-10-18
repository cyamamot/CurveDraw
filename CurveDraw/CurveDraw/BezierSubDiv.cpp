#include "BezierSubDiv.h"


//helper function to fill list of points for all subdivisions based on original control points
void accumulateNextLevel(std::vector<ControlPoint>* accum, std::vector<ControlPoint> pts)
{
	if (pts.empty()) return;
	//save first point in control shape
	accum->push_back(*(pts.begin()));
	if (pts.size() == 1) return;
	//create subdivided points from given control points in pts (alters the original list)
	for (std::vector<ControlPoint>::iterator it = pts.begin(); it != pts.end() - 1; it++)
	{
		it->x = 0.5f * (it->x + (it + 1)->x);
		it->y = 0.5f * (it->y + (it + 1)->y);
	}
	//save the last point in control shape
	ControlPoint last = *(pts.end() - 1);
	pts.pop_back();
	//recursive call on altered list
	accumulateNextLevel(accum, pts);
	accum->push_back(last);
}

void BezierSubDiv::DrawCurve(int LOD)
{
	if (LOD > 0) 
	{
		ConnectControlPoints();
	}
	//used to ensure above statement is only called once
	else
	{
		LOD = -LOD;
	}
	//Base case
	if (LOD <= 1) 
	{
		if (points.size() >= 2) 
		{
			for (std::vector<ControlPoint>::iterator it = points.begin(); it != points.end() - 1; it++)
			{
				//DrawCurve lines between all current points
				DrawCurveLine(it->x, it->y, (it + 1)->x, (it + 1)->y);
			}
		}
	}
	else 
	{
		std::vector<ControlPoint>* accum = new std::vector<ControlPoint>();
		//left and right section of current total curve
		BezierSubDiv left, right;
		if (points.size() > 1)
		{
			//get new control points
			accumulateNextLevel(accum, points);
			//first control point in right subsection is the middle new control point
			right.points.push_back((*accum)[accum->size() / 2]);
			//places new control points in either left or right's list
			for (unsigned int i = 0; i < accum->size(); i++) 
			{
				if (i < accum->size() / 2) left.points.push_back((*accum)[i]);
				else if (i > accum->size() / 2) right.points.push_back((*accum)[i]);
			}
			//last control point in left subsection is the middle new control point
			left.points.push_back((*accum)[accum->size() / 2]);
			//each successive call reduces LOD by 1
			left.DrawCurve(1 - LOD);
			right.DrawCurve(1 - LOD);
			delete accum;
		}
	}
}
