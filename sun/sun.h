/******************************
Malcolm Yarbrough
2017-03-22
sun.h
********************************/

#ifndef SHAPE_CLOUD
#define SHAPE_CLOUD

#include "Graph.h"
#include "Point.h"
#include "fltk.h"
#include "std_lib_facilities.h"

struct Sun : Shape
{
private:
	int sun_radius[2];
	Circle center;
	Polygon outer;

public:
	Sun(Point p, int rad_inner, int rad_outer, int spikes = 15);
	void set_color(Color col);
	void set_fill_color(Color col);
	void draw_lines();
	void move(int dx, int dy);
};



#endif // !SHAPE_CLOUD
