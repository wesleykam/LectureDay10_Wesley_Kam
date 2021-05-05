#ifndef MOVABLE_H
#define MOVABLE_H
#include "vec2.h"

class movable {
	public:
		movable() {};

		virtual void translate(vec2 offset) = 0;
};

#endif
