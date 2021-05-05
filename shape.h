#ifndef SHAPE_H
#define SHAPE_H
#include "movable.h"
#include "vec2.h"

/* a base class for our lecture code! */
class shape : public movable {
  public:
  	shape(color theColor, double inDepth) : inC(theColor), depth(inDepth) {}

	virtual void translate(vec2 offset) = 0;

	color getInC() const {return inC; }
	double getDepth() const {return depth; }
	virtual bool eval(double x, double y) = 0;

	virtual void setColor(color col) {
		inC = col;
	}

  protected:
	color inC;
	double depth;
};

#endif