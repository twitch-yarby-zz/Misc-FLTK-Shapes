#include "stickfigure.h"
#include "Graph.h"
#include <math.h>

#define DEG_TO_RAD 3.14159 / 180.0


StickFigure::StickFigure(const Point p, const int height, const Fl_Color color)
	: StickFigure(p,height,color, 45.0, 45.0, 32.75, 32.75, 32.75, 32.75, 20.5, 20.5)
{}

StickFigure::StickFigure(const Point p, const int height, const Fl_Color color,
			double rel_upper_arm_angle,
			double rel_lower_arm_angle,
			double rel_upper_leg_angle,
			double rel_lower_leg_angle)
	: StickFigure(p,height,color,
			rel_upper_arm_angle, rel_upper_arm_angle,
			rel_lower_arm_angle, rel_lower_arm_angle,
			rel_upper_leg_angle, rel_upper_leg_angle,
			rel_lower_leg_angle, rel_lower_leg_angle)
{}

StickFigure::StickFigure(const Point p, const int height, const Fl_Color color,
			double rel_arm_upper_left_angle, double rel_arm_upper_right_angle,
			double rel_arm_lower_left_angle, double rel_arm_lower_right_angle,
			double rel_leg_upper_left_angle, double rel_leg_upper_right_angle,
			double rel_leg_lower_left_angle, double rel_leg_lower_right_angle)
{
	// Set initial values
	p_top = p;
	c_color = color;
	v_height = height;

	s_head = 0;
	s_body = 0;
	s_arm_upper_left = 0;
	s_arm_upper_right = 0;
	s_forearm_left = 0;
	s_forearm_right = 0;
	s_hand_left = 0;
	s_hand_right = 0;
	s_leg_upper_left = 0;
	s_leg_upper_right = 0;
	s_leg_lower_left = 0;
	s_leg_lower_right = 0;
	s_foot_left = 0;
	s_foot_right = 0;

	// Calculate dimensions
	v_head = v_height / 13;
	v_body = v_height / 2.1 - v_head * 2;
	v_shoulders = v_height / 6;
	v_upper_arms = v_height / 10;
	v_hands = v_height / 40;
	v_forearms = v_height / 10 - v_hands;
	v_upper_legs = v_height / 7;
	v_feet = v_height / 40;
	v_lower_legs = v_height / 7 - v_feet * 2;

	move(p_top.x, p_top.y,
		rel_arm_upper_left_angle, rel_arm_upper_right_angle,
		rel_arm_lower_left_angle, rel_arm_lower_right_angle,
		rel_leg_upper_left_angle, rel_leg_upper_right_angle,
		rel_leg_lower_left_angle, rel_leg_lower_right_angle);
}

StickFigure::~StickFigure()
{
	delete s_head;
	delete s_body;
	delete s_arm_upper_left;
	delete s_arm_upper_right;
	delete s_forearm_left;
	delete s_forearm_right;
	delete s_hand_left;
	delete s_hand_right;
	delete s_leg_upper_left;
	delete s_leg_upper_right;
	delete s_leg_lower_left;
	delete s_leg_lower_right;
	delete s_foot_left;
	delete s_foot_right;
}

void StickFigure::position(int x, int y)
{
	if (p_top.x != x || p_top.y != y)
	{
		move(x, y,
			v_abs_arm_upper_left_angle, v_abs_arm_upper_right_angle,
			v_abs_arm_lower_left_angle, v_abs_arm_lower_right_angle,
			v_abs_leg_upper_left_angle, v_abs_leg_upper_right_angle,
			v_abs_leg_lower_left_angle, v_abs_leg_lower_right_angle);
	}
}

void StickFigure::angles(double rel_arm_upper_left_angle, double rel_arm_upper_right_angle,
									double rel_arm_lower_left_angle, double rel_arm_lower_right_angle,
									double rel_leg_upper_left_angle, double rel_leg_upper_right_angle,
									double rel_leg_lower_left_angle, double rel_leg_lower_right_angle)
{
	move(p_top.x, p_top.y,
		rel_arm_upper_left_angle, rel_arm_upper_right_angle,
		rel_arm_lower_left_angle, rel_arm_lower_right_angle,
		rel_leg_upper_left_angle, rel_leg_upper_right_angle,
		rel_leg_lower_left_angle, rel_leg_lower_right_angle);
}

void StickFigure::move(int x, int y, double rel_arm_upper_left_angle, double rel_arm_upper_right_angle, double rel_arm_lower_left_angle, double rel_arm_lower_right_angle, double rel_leg_upper_left_angle, double rel_leg_upper_right_angle, double rel_leg_lower_left_angle, double rel_leg_lower_right_angle)
{
	// Check for point movement
	bool b_top_move = false;
	if (p_top.x != x || p_top.y != y)
	{
		p_top = Point(x, y);
		b_top_move = true;
	}
	// store old angles for comparison
	double o_abs_arm_upper_left_angle = v_abs_arm_upper_left_angle;
	double o_abs_arm_upper_right_angle = v_abs_arm_upper_right_angle;
	double o_abs_arm_lower_left_angle = v_abs_arm_lower_left_angle;
	double o_abs_arm_lower_right_angle = v_abs_arm_lower_right_angle;
	double o_abs_leg_upper_left_angle = v_abs_leg_upper_left_angle;
	double o_abs_leg_upper_right_angle = v_abs_leg_upper_right_angle;
	double o_abs_leg_lower_left_angle = v_abs_leg_lower_left_angle;
	double o_abs_leg_lower_right_angle = v_abs_leg_lower_right_angle;

	// Calculate absolute angles
	v_abs_arm_upper_left_angle = 90 - rel_arm_upper_left_angle;
	v_abs_arm_upper_right_angle = 90 + rel_arm_upper_right_angle;
	v_abs_arm_lower_left_angle = 90 - rel_arm_lower_left_angle;
	v_abs_arm_lower_right_angle = 90 + rel_arm_lower_right_angle;
	v_abs_leg_upper_left_angle = 90 - rel_leg_upper_left_angle;
	v_abs_leg_upper_right_angle = 90 + rel_leg_upper_right_angle;
	v_abs_leg_lower_left_angle = 90 - rel_leg_lower_left_angle;
	v_abs_leg_lower_right_angle = 90 + rel_leg_lower_right_angle;

	// Check for changes
	bool b_arm_upper_left_angle = o_abs_arm_upper_left_angle != v_abs_arm_upper_left_angle;
	bool b_arm_upper_right_angle = o_abs_arm_upper_right_angle != v_abs_arm_upper_right_angle;
	bool b_arm_lower_left_angle = o_abs_arm_lower_left_angle != v_abs_arm_lower_left_angle;
	bool b_arm_lower_right_angle = o_abs_arm_lower_right_angle != v_abs_arm_lower_right_angle;
	bool b_leg_upper_left_angle = o_abs_leg_upper_left_angle != v_abs_leg_upper_left_angle;
	bool b_leg_upper_right_angle = o_abs_leg_upper_right_angle != v_abs_leg_upper_right_angle;
	bool b_leg_lower_left_angle = o_abs_leg_lower_left_angle != v_abs_leg_lower_left_angle;
	bool b_leg_lower_right_angle = o_abs_leg_lower_right_angle != v_abs_leg_lower_right_angle;
	
	// Recalculate head && body
	if (b_top_move)
	{
		p_head = Point(p_top.x, p_top.y + v_head);
		p_body_upper = Point(p_head.x, p_head.y + v_head);
		p_shoulders = Point(p_top.x, p_top.y + v_shoulders);
		p_groin = Point(p_body_upper.x, p_body_upper.y + v_body);

		if (s_head)
			delete s_head;
		if (s_body)
			delete s_body;

		s_head = new Circle(p_head, v_head);
		s_head->set_color(c_color);
		s_body = new Line(p_body_upper, p_groin);
		s_body->set_color(c_color);
	}

	// Recalculate arm_upper_left
	if (b_arm_upper_left_angle)
	{
		d_elbow_left_x = (int)(v_upper_arms * cos(v_abs_arm_upper_left_angle * DEG_TO_RAD));
		d_elbow_left_y = (int)(v_upper_arms * sin(v_abs_arm_upper_left_angle * DEG_TO_RAD));
	}
	if (b_top_move || b_arm_upper_left_angle)
	{
		p_elbow_left = Point(p_shoulders.x + d_elbow_left_x, p_shoulders.y + d_elbow_left_y);

		if (s_arm_upper_left)
			delete s_arm_upper_left;

		s_arm_upper_left = new Line(p_shoulders, p_elbow_left);
		s_arm_upper_left->set_color(c_color);
	}

	// Recalculate arm_upper_right
	if (b_arm_upper_right_angle)
	{
		d_elbow_right_x = (int)(v_upper_arms * cos(v_abs_arm_upper_right_angle * DEG_TO_RAD));
		d_elbow_right_y = (int)(v_upper_arms * sin(v_abs_arm_upper_right_angle * DEG_TO_RAD));
	}
	if (b_top_move || b_arm_upper_right_angle)
	{
		p_elbow_right = Point(p_shoulders.x + d_elbow_right_x, p_shoulders.y + d_elbow_right_y);

		if (s_arm_upper_right)
			delete s_arm_upper_right;

		s_arm_upper_right = new Line(p_shoulders, p_elbow_right);
		s_arm_upper_right->set_color(c_color);
	}

	// Recalculate arm_lower_left && hand_left
	if (b_arm_lower_left_angle)
	{
		d_wrist_left_x = (int)(v_forearms * cos(v_abs_arm_lower_left_angle * DEG_TO_RAD));
		d_wrist_left_y = (int)(v_forearms * sin(v_abs_arm_lower_left_angle * DEG_TO_RAD));
		d_hand_right_x = (int)(v_hands * cos(v_abs_arm_lower_right_angle * DEG_TO_RAD));
		d_hand_right_y = (int)(v_hands * sin(v_abs_arm_lower_right_angle * DEG_TO_RAD));
	}
	if (b_top_move || b_arm_upper_left_angle || b_arm_lower_left_angle)
	{
		p_wrist_left = Point(p_elbow_left.x + d_wrist_left_x, p_elbow_left.y + d_wrist_left_y);
		p_hand_left = Point(p_wrist_left.x + d_hand_left_x, p_wrist_left.y + d_hand_left_y);

		if (s_forearm_left)
			delete s_forearm_left;
		if (s_hand_left)
			delete s_hand_left;

		s_forearm_left = new Line(p_elbow_left, p_wrist_left);
		s_forearm_left->set_color(c_color);
		s_hand_left = new Circle(p_hand_left, v_hands);
		s_hand_left->set_color(c_color);
	}

	// Recalculate arm_lower_right && hand_right
	if (b_arm_lower_right_angle)
	{
		d_wrist_right_x = (int)(v_forearms * cos(v_abs_arm_lower_right_angle * DEG_TO_RAD));
		d_wrist_right_y = (int)(v_forearms * sin(v_abs_arm_lower_right_angle * DEG_TO_RAD));
		d_hand_left_x = (int)(v_hands * cos(v_abs_arm_lower_left_angle * DEG_TO_RAD));
		d_hand_left_y = (int)(v_hands * sin(v_abs_arm_lower_left_angle * DEG_TO_RAD));
	}
	if (b_top_move || b_arm_upper_right_angle || b_arm_lower_right_angle)
	{
		p_wrist_right = Point(p_elbow_right.x + d_wrist_right_x, p_elbow_right.y + d_wrist_right_y);
		p_hand_right = Point(p_wrist_right.x + d_hand_right_x, p_wrist_right.y + d_hand_right_y);

		if (s_forearm_right)
			delete s_forearm_right;
		if (s_hand_right)
			delete s_hand_right;

		s_forearm_right = new Line(p_elbow_right, p_wrist_right);
		s_forearm_right->set_color(c_color);
		s_hand_right = new Circle(p_hand_right, v_hands);
		s_hand_right->set_color(c_color);
	}

	// Recalculate leg_upper_left
	if (b_leg_upper_left_angle)
	{
		d_knee_left_x = (int)(v_upper_legs * cos(v_abs_leg_upper_left_angle * DEG_TO_RAD));
		d_knee_left_y = (int)(v_upper_legs * sin(v_abs_leg_upper_left_angle * DEG_TO_RAD));
	}
	if (b_top_move || b_leg_upper_left_angle)
	{
		p_knee_left = Point(p_groin.x + d_knee_left_x, p_groin.y + d_knee_left_y);

		if (s_leg_upper_left)
			delete s_leg_upper_left;

		s_leg_upper_left = new Line(p_groin, p_knee_left);
		s_leg_upper_left->set_color(c_color);
	}

	// Recalculate leg_upper_right
	if (b_leg_upper_right_angle)
	{
		d_knee_right_x = (int)(v_upper_legs * cos(v_abs_leg_upper_right_angle * DEG_TO_RAD));
		d_knee_right_y = (int)(v_upper_legs * sin(v_abs_leg_upper_right_angle * DEG_TO_RAD));
	}
	if (b_top_move || b_leg_upper_right_angle)
	{
		p_knee_right = Point(p_groin.x + d_knee_right_x, p_groin.y + d_knee_right_y);

		if (s_leg_upper_right)
			delete s_leg_upper_right;

		s_leg_upper_right = new Line(p_groin, p_knee_right);
		s_leg_upper_right->set_color(c_color);
	}

	// Recalculate leg_lower_left && foot_left
	if (b_leg_lower_left_angle)
	{
		d_ankle_left_x = (int)(v_lower_legs * cos(v_abs_leg_lower_left_angle * DEG_TO_RAD));
		d_ankle_left_y = (int)(v_lower_legs * sin(v_abs_leg_lower_left_angle * DEG_TO_RAD));
		d_foot_left_x = (int)(v_feet * cos(v_abs_leg_lower_left_angle * DEG_TO_RAD));
		d_foot_left_y = (int)(v_feet * sin(v_abs_leg_lower_left_angle * DEG_TO_RAD));
	}
	if (b_top_move || b_leg_upper_left_angle || b_leg_lower_left_angle)
	{
		p_ankle_left = Point(p_knee_left.x + d_ankle_left_x, p_knee_left.y + d_ankle_left_y);
		p_foot_left = Point(p_ankle_left.x + d_foot_left_x, p_ankle_left.y + d_foot_left_y);

		if (s_leg_lower_left)
			delete s_leg_lower_left;
		if (s_foot_left)
			delete s_foot_left;

		s_leg_lower_left = new Line(p_knee_left, p_ankle_left);
		s_leg_lower_left->set_color(c_color);
		s_foot_left = new Circle(p_foot_left, v_feet);
		s_foot_left->set_color(c_color);
	}

	// Recalculate leg_lower_left && foot_left
	if (b_leg_lower_right_angle)
	{
		d_ankle_right_x = (int)(v_lower_legs * cos(v_abs_leg_lower_right_angle * DEG_TO_RAD));
		d_ankle_right_y = (int)(v_lower_legs * sin(v_abs_leg_lower_right_angle * DEG_TO_RAD));
		d_foot_right_x = (int)(v_feet * cos(v_abs_leg_lower_right_angle * DEG_TO_RAD));
		d_foot_right_y = (int)(v_feet * sin(v_abs_leg_lower_right_angle * DEG_TO_RAD));
	}
	if (b_top_move || b_leg_upper_right_angle || b_leg_lower_right_angle)
	{
		p_ankle_right = Point(p_knee_right.x + d_ankle_right_x, p_knee_right.y + d_ankle_right_y);
		p_foot_right = Point(p_ankle_right.x + d_foot_right_x, p_ankle_right.y + d_foot_right_y);

		if (s_leg_lower_right)
			delete s_leg_lower_right;
		if (s_foot_right)
			delete s_foot_right;

		s_leg_lower_right = new Line(p_knee_right, p_ankle_right);
		s_leg_lower_right->set_color(c_color);
		s_foot_right = new Circle(p_foot_right, v_feet);
	}
}

void StickFigure::draw_lines() const
{
	s_head->draw();
	s_body->draw();
	s_arm_upper_left->draw();
	s_arm_upper_right->draw();
	s_forearm_left->draw();
	s_forearm_right->draw();
	s_hand_left->draw();
	s_hand_right->draw();
	s_leg_upper_left->draw();
	s_leg_upper_right->draw();
	s_leg_lower_left->draw();
	s_leg_lower_right->draw();
	s_foot_left->draw();
	s_foot_right->draw();
}
