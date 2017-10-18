#include "Curve.h"


Curve::Curve()
{
	HasPointSelected = false;
}

Curve::~Curve()
{
}
  
void Curve::DrawCurve(int lod)
{
	if (!points.empty())
	{
		ConnectControlPoints();
	}
}
 
void Curve::AddPoint(float x, float y)
{
	if (!HasPointSelected)
	{
		points.push_back(ControlPoint(x, y));
	}
}

void Curve::DeletePoint()
{
	if (HasPointSelected)
	{
		points.erase(SelectedPoint);
		HasPointSelected = false;
	}
}

void Curve::MovePoint(float dx, float dy)
{
	if (HasPointSelected)
	{
		SelectedPoint->x += dx;
		SelectedPoint->y += dy;
	}
}

void Curve::UpdatePoint(float x, float y)
{
	float dx, dy, distance = 1;
	float radius = ControlPoint::RADIUS * ControlPoint::RADIUS;
	//check to see if new location (x, y) is within the radius of the current selected point
	if (HasPointSelected)
	{
		dx = SelectedPoint->x - x;
		dy = SelectedPoint->y - y;
		distance = (dx * dx) + (dy * dy);
	}
	//if it is outside the radius
	if (distance > radius)
	{
		if (HasPointSelected) SelectedPoint->Selected = false;
		HasPointSelected = false;
		//check to see if the new location is in the radius of any other point
		for (std::vector<ControlPoint>::iterator it = points.begin(); it != points.end(); it++)
		{
			dx = it->x - x;
			dy = it->y - y;
			distance = (dx * dx) + (dy * dy);
			//if new location is in radius of another point, make that point the selected point
			if (distance < radius)
			{
				SelectedPoint = it;
				it->Selected = true;
				HasPointSelected = true;
				break;
			}
		}
	}
}

void Curve::ConnectControlPoints() 
{
	std::vector<ControlPoint>::iterator curr, next;
	std::vector<float> coords;
	// Only DrawCurve lines if we have more than 1 control point
	if (points.size() > 1) 
	{
		for (curr = points.begin(); curr != points.end()-1; curr++)
		{
			next = curr + 1;
			coords.push_back(curr->x);
			coords.push_back(curr->y);
			coords.push_back(next->x);
			coords.push_back(next->y);
		}
		glUniform3f(colorPos, 0.0, 1.0, 0.0);
		glBufferData(GL_ARRAY_BUFFER, coords.size() * sizeof(float), &coords[0], GL_STATIC_DRAW);
		glLineWidth(LINE_WIDTH);
		glDrawArrays(GL_LINE_STRIP, 0, coords.size()/2.0f);
		coords.clear();
	}
	//draws all control points in list
	for (curr = points.begin(); curr != points.end(); curr++) 
	{
		curr->DrawPoint();
		glUniform3f(colorPos, 0.0, 0.0, 1.0);
	}
}

void Curve::DrawCurveLine(float x1, float y1, float x2, float y2) 
{
	glUniform3f(colorPos, 0.0, 0.0, 1.0);
	std::vector<float> coords;
	coords.push_back(x1);
	coords.push_back(y1);
	coords.push_back(x2);
	coords.push_back(y2);
	glBufferData(GL_ARRAY_BUFFER, coords.size() * sizeof(float), &coords[0], GL_STATIC_DRAW);
	glLineWidth(LINE_WIDTH);
	glDrawArrays(GL_LINE_STRIP, 0, coords.size() / 2.0f);
	coords.clear();
}

void Curve::setShaderReferences(GLuint color)
{
	colorPos = color;
}
