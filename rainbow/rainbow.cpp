#include "rainbow.h"

Graph_lib::Rainbow::Rainbow(Point p, int start_r, int rad_incr, Fl_Color sky)
{
	add(Point{ p.x - r, p.y - r });
	int rad = start_r;
	Circle* tmp;
	// Build rainbow
	for (int i = 0; i < 7; i++)
	{
		tmp = new Circle(p, rad);
		tmp->set_fill_color(fl_rgb_color(colors[i][0], colors[i][1], colors[i][2]));
		tmp->set_color(fl_rgb_color(colors[i][0], colors[i][1], colors[i][2]));
		rad -= rad_incr;
		rainbow_elems.push_back(tmp);
	}
	// Add sky center
	tmp = new Circle(p, rad);
	tmp->set_fill_color(sky);
	tmp->set_color(sky);
	rainbow_elems.push_back(tmp);
}

Graph_lib::Rainbow::~Rainbow()
{
	vector<Circle*>::const_iterator it;
	for (it = rainbow_elems.begin(); it != rainbow_elems.end(); it++)
		delete (*it);
}
;


void Graph_lib::Rainbow::draw_lines() const
{
	vector<Circle*>::const_iterator it;
	for (it = rainbow_elems.begin(); it != rainbow_elems.end(); it++)
		(*it)->draw_lines();
}
