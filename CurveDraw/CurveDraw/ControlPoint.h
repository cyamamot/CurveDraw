/*
Class that defines each Control Point of a curve
*/
#if !defined(CONTROLPOINT_H)
#define CONTROLPOINT_H

class ControlPoint  
{

public:
	//position coordinates
	float x;
	float y;
	//whether this point is currently selected
	bool Selected;
	//click radius (if this radius is clicked, point becomes selected)
	static float RADIUS;
	unsigned int colorPos;

	ControlPoint(float xpos, float ypos);
	virtual ~ControlPoint();
	void DrawPoint();

private:
	float LINE_WIDTH = 12.0f;

};

#endif

