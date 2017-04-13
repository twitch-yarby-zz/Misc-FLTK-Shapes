/******************************
Malcolm Yarbrough
2017-03-22
rainbow.h
********************************/

#ifndef SHAPE_RAINBOW
#define SHAPE_RAINBOW

#include "Graph.h"
#include "Point.h"
#include "fltk.h"
#include "std_lib_facilities.h"

namespace Graph_lib {

	struct Rainbow : Shape
	{
	private:
		int r;
		vector<Circle*> rainbow_elems;
		const int colors[7][3] = { { 255,0,0 },{ 255, 127, 0 },{ 255, 255, 0 },{ 0, 255, 0 },{ 0, 0, 255 },{ 75, 0, 130 },{ 148, 0, 211 } };

	public:
		Rainbow(Point p, int start_r, int rad_incr,Fl_Color sky);
		~Rainbow();

		void draw_lines() const;

		Point center() const { return{ point(0).x + r, point(0).y + r }; }

		int radius() const { return r; }
	};

}

#endif // !SHAPE_RAINBOW