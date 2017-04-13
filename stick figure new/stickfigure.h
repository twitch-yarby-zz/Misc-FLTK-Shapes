/******************************
Malcolm Yarbrough
2017-03-22
stickfigure.h
********************************/

#ifndef SHAPE_STICK_FIGURE
#define SHAPE_STICK_FIGURE

#include "Graph.h"
#include "Point.h"
#include "fltk.h"
#include "std_lib_facilities.h"

struct StickFigure : Shape
{
private:
	Fl_Color c_color;

	// Values
	double v_abs_arm_upper_left_angle;
	double v_abs_arm_upper_right_angle;
	double v_abs_arm_lower_left_angle;
	double v_abs_arm_lower_right_angle;
	double v_abs_leg_upper_left_angle;
	double v_abs_leg_upper_right_angle;
	double v_abs_leg_lower_left_angle;
	double v_abs_leg_lower_right_angle;
	int v_height;
	int v_head;
	int v_body;
	int v_shoulders;
	int v_upper_arms;
	int v_forearms;
	int v_hands;
	int v_upper_legs;
	int v_lower_legs;
	int v_feet;

	// Deltas
	int d_elbow_left_x;
	int d_elbow_left_y;
	int d_elbow_right_x;
	int d_elbow_right_y;
	int d_wrist_left_x;
	int d_wrist_left_y;
	int d_wrist_right_x;
	int d_wrist_right_y;
	int d_hand_left_x;
	int d_hand_left_y;
	int d_hand_right_x;
	int d_hand_right_y;
	int d_knee_left_x;
	int d_knee_left_y;
	int d_knee_right_x;
	int d_knee_right_y;
	int d_ankle_left_x;
	int d_ankle_left_y;
	int d_ankle_right_x;
	int d_ankle_right_y;
	int d_foot_left_x;
	int d_foot_left_y;
	int d_foot_right_x;
	int d_foot_right_y;

	// Points
	Point p_top;
	Point p_head;
	Point p_body_upper;
	Point p_shoulders;
	Point p_groin;
	Point p_elbow_left;
	Point p_elbow_right;
	Point p_wrist_left;
	Point p_wrist_right;
	Point p_hand_left;
	Point p_hand_right;
	Point p_knee_left;
	Point p_knee_right;
	Point p_ankle_left;
	Point p_ankle_right;
	Point p_foot_left;
	Point p_foot_right;

	// Shapes
	Shape* s_head;
	Shape* s_body;
	Shape* s_arm_upper_left;
	Shape* s_arm_upper_right;
	Shape* s_forearm_left;
	Shape* s_forearm_right;
	Shape* s_hand_left;
	Shape* s_hand_right;
	Shape* s_leg_upper_left;
	Shape* s_leg_upper_right;
	Shape* s_leg_lower_left;
	Shape* s_leg_lower_right;
	Shape* s_foot_left;
	Shape* s_foot_right;

public:
	StickFigure(const Point p, const int height, const Fl_Color color);
	StickFigure(const Point p, const int height, const Fl_Color color,
		double rel_upper_arm_angle,
		double rel_lower_arm_angle,
		double rel_upper_leg_angle,
		double rel_lower_leg_angle);
	StickFigure(const Point p, const int height, const Fl_Color color,
		double rel_arm_upper_left_angle, double rel_arm_upper_right_angle,
		double rel_arm_lower_left_angle, double rel_arm_lower_right_angle,
		double rel_leg_upper_left_angle, double rel_leg_upper_right_angle,
		double rel_leg_lower_left_angle, double rel_leg_lower_right_angle);
	~StickFigure();

	void position(int x, int y);
	void angles(double rel_arm_upper_left_angle, double rel_arm_upper_right_angle,
		double rel_arm_lower_left_angle, double rel_arm_lower_right_angle,
		double rel_leg_upper_left_angle, double rel_leg_upper_right_angle,
		double rel_leg_lower_left_angle, double rel_leg_lower_right_angle);
	void move(int x, int y,
		double rel_arm_upper_left_angle, double rel_arm_upper_right_angle,
		double rel_arm_lower_left_angle, double rel_arm_lower_right_angle,
		double rel_leg_upper_left_angle, double rel_leg_upper_right_angle,
		double rel_leg_lower_left_angle, double rel_leg_lower_right_angle);
	void draw_lines() const;
};
#endif // !_SHAPE_STICK_FIGURE