#ifndef RECT_H
#define RECT_H

#include "vec2.h"
#include "shape.h"

/* simple data representation of a rectangle */
class Rect : public shape {
  public:
	Rect(double lX, double lY, double rX, double rY, color C, double deep) : shape{C, deep}, 
		upperL(lX, lY), lowerR(rX, rY) {}
	Rect(vec2(left), vec2(right), color C, double deep) : shape{C, deep}, 
		upperL(left), lowerR(right) {}
	Rect(vec2(left), double width, double height, color C, double deep) : shape{C, deep}, 
		upperL(left), lowerR(left.x()+width,left.y()+height) {}

	bool eval(double x, double y) {
		if ((x >= upperL.x() && x <= lowerR.x()) && (y >= upperL.y() && y <= lowerR.y())) {
			return true;
		}
		return false;
	}

	void translate(vec2 offset) {
		upperL += offset;
		lowerR += offset;
	}

	double getWidth() const {return lowerR.x() - upperL.x(); }
	double getHeight() const {return lowerR.y() - upperL.y(); }
	double getArea() const {return (lowerR.x() - upperL.x())*(lowerR.y() - upperL.y());}

	void setDepth(double inD) { depth= inD; }
	void setColor(color col) { 
		col.setR(0);
		col.setG(0);
		inC = col; 
	}
	void setLCorner(vec2 inLCor) { upperL = inLCor; }
	void setRCorner(vec2 inRCor) {lowerR = inRCor;}

  private:
	vec2 upperL;
	vec2 lowerR;
};

#endif