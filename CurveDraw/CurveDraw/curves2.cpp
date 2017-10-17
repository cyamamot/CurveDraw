#include "WorkingScene.h"

// This file includes the basic functions that your program must fill in.  
// Note that there are several helper functions from Curve.cpp that can be used!
// In particular, take a look at moveActivePoint, connectTheDots, drawLine, etc.

// What happens when you drag the mouse to x and y?  
// In essence, you are dragging control points on the curve.
void WorkingScene::drag(int x, int y) {
	/* YOUR CODE HERE */
	//you must figure out how to transform x and y so they make sense
	//update oldx, and oldy
	//make sure scene gets redrawn
	float normx = (float)(x - oldx) / (float)Scene::width;
	float normy = (float)(y - oldy) / (float)Scene::height;
    theOnlyCurve->moveActivePoint(normx, -normy);
	oldx = x;
	oldy = y;
	glutPostRedisplay();
}

// Mouse motion.  You need to respond to left clicks (to add points on curve) 
// and right clicks (to delete points on curve) 
void WorkingScene::mouse(int button, int state, int x, int y) {
	// theOnlyCurve is the current type of curve being drawn. It is created in Scene.cpp.
	if (theOnlyCurve && state == GLUT_DOWN) {
		if (button == GLUT_LEFT_BUTTON) {
			/* YOUR CODE HERE */
			float normx = (float)x / (float)Scene::width;
			float normy = (float)y / (float)Scene::height;
			theOnlyCurve->addPoint(normx, 1.0f - normy);
		}
		if (button == GLUT_RIGHT_BUTTON) {	
			/* YOUR CODE HERE */
			float normx = (float)x / (float)Scene::width;
			float normy = (float)y / (float)Scene::height;
			theOnlyCurve->updateActivePoint(normx, 1.0f - normy);
			theOnlyCurve->deleteActivePoint();
		}
	}

	/* YOUR CODE HERE */
	//update oldx, and oldy
	//make sure scene gets redrawn
	oldx = x;
	oldy = y;
	glutPostRedisplay();
}



#include "Bezier.h"

// Bezier drawing function.  This is by deCasteljau or equivalent algorithm. 
// It should support Bezier curves of arbitrary degree/order.
void Bezier::draw(int levelOfDetail) {

	connectTheDots();
	int i, j, k;
	Pvector::iterator p;

	/* YOUR CODE HERE */

	Pvector listOfU;
	int n = points.size() - 1;
	std::vector< std::vector<Point> > pMat;
	for (int i = 0; i <= n; i++) {
		std::vector<Point> empty;
		pMat.push_back(empty);
		for (int j = 0; j <= n; j++) {
			Point emp(0.0f, 0.0f);
			pMat[i].push_back(emp);
		}
	}
	if (points.size() > 1) {
		for (k = 0; k <= levelOfDetail; k++) {
			float u = (float)k / (float)levelOfDetail;
			for (int level = n; level >= 0; level--) {
				if (level == n) {
					for (int i = 0; i <= n; i++) pMat[level][i] = points[i];
					continue;
				}
				for (int i = 0; i <= level; i++) {
					pMat[level][i].x = (1 - u) * pMat[level + 1][i].x + u * pMat[level + 1][i + 1].x;
					pMat[level][i].y = (1 - u) * pMat[level + 1][i].y + u * pMat[level + 1][i + 1].y;
				}
			}
			listOfU.push_back(pMat[0][0]);
		}
	}
	if (points.size() > 1) {
		for (int r = 0; r < (listOfU.size() - 1); r++) {
			drawLine(listOfU[r].x, listOfU[r].y, listOfU[r + 1].x, listOfU[r + 1].y);
		}
	}

	/*Pvector listOfU;
	i = points.size() - 1;
	int multiplier = points.size() - 1;
	j = 0;    //de Casteljau exponent
	for (k = 0; k <= levelOfDetail; k++) {
		float u = (float)k / (float)levelOfDetail;
		std::cout << u << std::endl;
		Point input(0.0f, 0.0f);
		if (points.size() > 1) {
			for (p = points.begin(); p != points.end(); p++) {
				std::cout << p->x << " " << p->y << std::endl;
				if (p != points.begin() && p != (points.end() - 1)) {
					input.x = input.x + (multiplier * pow(u, (float)j) * pow((1.0f - u), (float)i) * p->x);
					input.y = input.y + (multiplier * pow(u, (float)j) * pow((1.0f - u), (float)i) * p->y);
					i--;
					j++;
				}
				else {
					//std::cout << input.x << " " << pow(u, j) << " " << pow((1.0f - u), i) << " " << p->x << std::endl;
					//std::cout << input.y << " " << pow(u, j) << " " << pow((1.0f - u), i) << " " << p->y << std::endl;
					input.x = input.x + (pow(u, (float)j) * pow((1.0f - u), (float)i) * p->x);
					input.y = input.y + (pow(u, (float)j) * pow((1.0f - u), (float)i) * p->y);
					i--;
					j++;
				}
			}
			//std::cout << input.x << " " << input.y << std::endl;
			listOfU.push_back(input);
			input = Point(0.0f, 0.0f);
			i = points.size() - 1;
			j = 0;
		}
	}
	if (points.size() > 1) {
		for (int r = 0; r < (listOfU.size() - 1); r++) {
			drawLine(listOfU[r].x, listOfU[r].y, listOfU[r + 1].x, listOfU[r + 1].y);
		}
	}*/
}


#include "Bspline.h"

// The B-Spline drawing routine.  
// Remember to call drawSegment (auxiliary function) for each set of 4 points.
void Bspline::draw(int levelOfDetail) {
	connectTheDots();
	/* YOUR CODE HERE */
	if (points.size() >= 4) {
		Pvector::iterator p0 = points.begin();
		Pvector::iterator p1 = p0 + 1;
		Pvector::iterator p2 = p1 + 1;
		Pvector::iterator p3 = p2 + 1;
		for (int i = 0; i + 4 <= points.size(); i++) {
			drawSegment(p0, p1, p2, p3, levelOfDetail);
			p0++;
			p1++;
			p2++;
			p3++;
		}
	}
}

void Bspline::drawSegment(Pvector::iterator p1, Pvector::iterator p2, Pvector::iterator p3, Pvector::iterator p4, int levelOfDetail) {
	float x, y;

	/* YOUR CODE HERE */
	Pvector listOfU;
	if (points.size() >= 4) {
		for (int k = 0; k <= levelOfDetail; k++) {
			float u = (float)k / (float)levelOfDetail;
			float uvec[4] = { u * u * u, u * u, u, 1.0f };
			float M[4][4] = { {-1.0f, 3.0f, -3.0f, 1.0f},
							{3.0f, -6.0f, 3.0f, 0.0f},
							{-3.0f, 0.0f, 3.0f, 0.0f},
							{1.0f, 4.0f, 1.0f, 0.0f} };
			float utimesM[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
			for (int i = 0; i < 4; i++) {
				utimesM[i] = (1.0f / 6.0f) * ((uvec[0] * M[0][i]) + (uvec[1] * M[1][i]) + (uvec[2] * M[2][i]) + (uvec[3] * M[3][i]));
			}
			x = (utimesM[0] * p1->x) + (utimesM[1] * p2->x) + (utimesM[2] * p3->x) + (utimesM[3] * p4->x);
			y = (utimesM[0] * p1->y) + (utimesM[1] * p2->y) + (utimesM[2] * p3->y) + (utimesM[3] * p4->y);
			//std::cout << u << " : " << x << " " << y << std::endl;
			Point upoint(x, y);
			listOfU.push_back(upoint);
		}
	}
	//draw segment
	if (points.size() >= 4) {
		for (int r = 0; r < (listOfU.size() - 1); r++) {
			drawLine(listOfU[r].x, listOfU[r].y, listOfU[r + 1].x, listOfU[r + 1].y);
		}
	}
	//then create a Point to be drawn where the knot should be

	Point p(x, y);
	p.draw();
}

#include "Bezier2.h"

//This function is provided to aid you.
//It should be used in the spirit of recursion, though you may choose not to.
//This function takes an empty vector of points, accum
//It also takes a set of control points, pts, and fills accum with
//the control points that correspond to the next level of detail.
void accumulateNextLevel(Pvector* accum, Pvector pts) {
	if (pts.empty()) return; 
	accum->push_back(*(pts.begin()));
	if (pts.size() == 1) return;
	for (Pvector::iterator it = pts.begin(); it != pts.end() - 1; it++) {
		/* YOUR CODE HERE  (only one to three lines)*/
		it->x = 0.5f * (it->x + (it + 1)->x);
		it->y = 0.5f * (it->y + (it + 1)->y);
	}
	//save the last point
	Point last = *(pts.end()-1);
	pts.pop_back();
	//recursive call
	accumulateNextLevel(accum, pts);
	accum->push_back(last);
}


// The basic draw function for Bezier2.  Note that as opposed to Bezier, 
// this draws the curve by recursive subdivision.  So, levelofdetail 
// corresponds to how many times to recurse.  
void Bezier2::draw(int levelOfDetail) {
	//This is just a trick to find out if this is the top level call
	//All recursive calls will be given a negative integer, to be flipped here
	if (levelOfDetail > 0) {
		connectTheDots();
	} else {
		levelOfDetail = -levelOfDetail;
	}

	//Base case.  No more recursive calls.
	if (levelOfDetail <= 1) {
		if (points.size() >= 2) {
			for (Pvector::iterator it = points.begin(); it != points.end() - 1; it++) {

				/* YOUR CODE HERE */
				drawLine(it->x, it->y, (it + 1)->x, (it + 1)->y);
				
			}
		}
	} else {
		Pvector* accum = new Pvector();
		Bezier2 left, right;

		//add the correct points to 'left' and 'right'.
		//You may or may not use accum as you see fit.
		/* YOUR CODE HERE */
		if (points.size() > 1) {
			accumulateNextLevel(accum, points);
			right.points.push_back((*accum)[accum->size() / 2]);
			for (int i = 0; i < accum->size(); i++) {
				if (i < accum->size() / 2) left.points.push_back((*accum)[i]);
				else if (i > accum->size() / 2) right.points.push_back((*accum)[i]);
			}
			left.points.push_back((*accum)[accum->size() / 2]);

			left.draw(1 - levelOfDetail);
			right.draw(1 - levelOfDetail);
			delete accum;
		}
	}
}
