#include "Bspline.h"

// The B-Spline drawing routine.  
// Remember to call drawSegment (auxiliary function) for each set of 4 points.
void Bspline::DrawCurve(int LOD) 
{
	ConnectControlPoints();
	if (points.size() >= 4) 
	{
		std::vector<ControlPoint>::iterator controlpoint1 = points.begin();
		std::vector<ControlPoint>::iterator controlpoint2 = controlpoint1 + 1;
		std::vector<ControlPoint>::iterator controlpoint3 = controlpoint2 + 1;
		std::vector<ControlPoint>::iterator controlpoint4 = controlpoint3 + 1;
		for (unsigned int i = 0; i + 4 <= points.size(); i++) 
		{
			drawSegment(controlpoint1, controlpoint2, controlpoint3, controlpoint4, LOD);
			controlpoint1++;
			controlpoint2++;
			controlpoint3++;
			controlpoint4++;
		}
	}
}

void Bspline::drawSegment(std::vector<ControlPoint>::iterator controlpoint1, std::vector<ControlPoint>::iterator controlpoint2, std::vector<ControlPoint>::iterator controlpoint3, std::vector<ControlPoint>::iterator controlpoint4, int LOD)
{
	float x, y;
	//list of points which approximate the curve
	std::vector<ControlPoint> listOfU;
	if (points.size() >= 4)
	{
		//uses explicit formula of cubic splines to solve for each u
		//F(u) = [u^3, u^2, u] M [p0; p1; p2; p3] where M is a dervied matrix
		float M[4][4] = { { -1.0f, 3.0f, -3.0f, 1.0f },
		{ 3.0f, -6.0f, 3.0f, 0.0f },
		{ -3.0f, 0.0f, 3.0f, 0.0f },
		{ 1.0f, 4.0f, 1.0f, 0.0f } };
		float utimesM[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
		for (int k = 0; k <= LOD; k++)
		{
			//sets u to be equal ratios from 0 to LOD
			float u = (float)k / (float)LOD;
			float uvec[4] = { u * u * u, u * u, u, 1.0f };
			for (int i = 0; i < 4; i++)
			{
				utimesM[i] = (1.0f / 6.0f) * ((uvec[0] * M[0][i]) + (uvec[1] * M[1][i]) + (uvec[2] * M[2][i]) + (uvec[3] * M[3][i]));
			}
			x = (utimesM[0] * controlpoint1->x) + (utimesM[1] * controlpoint2->x) + (utimesM[2] * controlpoint3->x) + (utimesM[3] * controlpoint4->x);
			y = (utimesM[0] * controlpoint1->y) + (utimesM[1] * controlpoint2->y) + (utimesM[2] * controlpoint3->y) + (utimesM[3] * controlpoint4->y);
			listOfU.push_back(ControlPoint(x, y));
		}
	}
	//DrawCurve segment
	if (points.size() >= 4) 
	{
		for (unsigned int r = 0; r < (listOfU.size() - 1); r++) {
			DrawCurveLine(listOfU[r].x, listOfU[r].y, listOfU[r + 1].x, listOfU[r + 1].y);
		}
	}
	//DrawCurve point at knots (where segments meet)
	ControlPoint p(x, y);
	p.DrawPoint();
}