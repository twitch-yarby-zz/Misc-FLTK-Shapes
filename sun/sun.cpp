/******************************
Malcolm Yarbrough
2017-03-22
sun.cpp
********************************/

#include "sun.h"
#include "Graph.h"
#include <math.h>

Sun::Sun(Point p, int rad_inner, int rad_outer, int spikes = 15) : center(p,rad_inner)
{
	sun_radius[0] = rad_inner;
	sun_radius[1] = rad_outer;

	int sun_x, sun_y;
	int slices = spikes * 2;
	double slice = 2 * 3.14159 / slices;
	for (int i = 0; i < slices; i++)
	{
		sun_x = (int)(sun_radius[i % 2] * cos(i * slice) + sun_center.x);
		sun_y = (int)(sun_radius[i % 2] * sin(i * slice) + sun_center.y);
		outer.add(Point(sun_x, sun_y));
	}
}

void Sun::set_color(Color col)
{
	center.set_color(col);
	outer.set_color(col);
}

void Sun::set_fill_color(Color col)
{
	center.set_fill_color(col);
	outer.set_fill_color(col);
}

void Sun::draw_lines()
{
	center.draw_lines();
	outer.draw_lines();
}

void Sun::move(int dx, int dy)
{
	center.move(dx, dy);
	outer.move(dx, dy);
}