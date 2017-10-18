#include "Bezier.h"


void Bezier::DrawCurve(int LOD) 
{
	ConnectControlPoints();
	std::vector<ControlPoint> listOfU;
	int n = points.size() - 1;
	//initialize matrix used to solve the polynomial equation that approximates current curve 
	std::vector<std::vector<ControlPoint>> pMat;
	for (int i = 0; i <= n; i++) 
	{
		std::vector<ControlPoint> empty;
		pMat.push_back(empty);
		for (int j = 0; j <= n; j++)
		{
			ControlPoint emp(0.0f, 0.0f);
			pMat[i].push_back(emp);
		}
	}
	//only perform function if there is more than 1 point on screen
	if (points.size() > 1) 
	{
		//for each LOD, solve deCastlejau's algorithm for the given ratio of u to (1 - u) in each segment of the control shape
		//LOD is the number of points in the curve approximation
		for (int k = 0; k <= LOD; k++)
		{
			float u = (float)k / (float)LOD;
			for (int level = n; level >= 0; level--) 
			{
				if (level == n) 
				{
					for (int i = 0; i <= n; i++) pMat[level][i] = points[i];
					continue;
				}
				for (int i = 0; i <= level; i++)
				{
					pMat[level][i].x = (1 - u) * pMat[level + 1][i].x + u * pMat[level + 1][i + 1].x;
					pMat[level][i].y = (1 - u) * pMat[level + 1][i].y + u * pMat[level + 1][i + 1].y;
				}
			}
			//list of locations at which to approximate the points on the curve
			listOfU.push_back(pMat[0][0]);
		}
	}
	if (points.size() > 1) 
	{
		//DrawCurve line between each point that approximates the curve
		for (unsigned int r = 0; r < (listOfU.size() - 1); r++)
		{
			DrawCurveLine(listOfU[r].x, listOfU[r].y, listOfU[r + 1].x, listOfU[r + 1].y);
		}
	}
}
