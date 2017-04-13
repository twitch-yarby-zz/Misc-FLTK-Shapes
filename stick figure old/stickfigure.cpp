#include "stickfigure.h"
#include "Graph.h"

#define DEG_TO_RAD 3.14159 / 180.0

Graph_lib::StickFigure::StickFigure(const Point p, const int height, const Fl_Color color)
	: StickFigure(p,height,color, 45.0, 57.25, 57.25, 69.5)
{}

Graph_lib::StickFigure::StickFigure(const Point p, const int height, const Fl_Color color, double abs_upper_arm_angle, double abs_lower_arm_angle, double abs_upper_leg_angle, double abs_lower_leg_angle)
{
	p_top = p;
	c_color = color;

	// Solid values
	v_abs_upper_arm_angle = abs_upper_arm_angle;
	v_abs_lower_arm_angle = abs_lower_arm_angle;
	v_abs_upper_leg_angle = abs_upper_leg_angle;
	v_abs_lower_leg_angle = abs_lower_leg_angle;

	// Calculate values
	v_height = height;
	v_head = v_height / 13;
	v_body = v_height / 2.1 - v_head * 2;
	v_shoulders = v_height / 6;
	v_upper_arms = v_height / 10;
	v_hands = v_height / 40;
	v_forearms = v_height / 10 - v_hands;
	v_upper_legs = v_height / 7;
	v_feet = v_height / 40;
	v_lower_legs = v_height / 7 - v_feet * 2;

	// Calculate Deltas
	d_elbow_left_x = (int)(v_upper_arms * cos(v_abs_upper_arm_angle * DEG_TO_RAD));
	d_elbow_left_y = (int)(v_upper_arms * sin(v_abs_upper_arm_angle * DEG_TO_RAD));

	d_elbow_right_x = (int)(v_upper_arms * cos((180 - v_abs_upper_arm_angle) * DEG_TO_RAD));
	d_elbow_right_y = (int)(v_upper_arms * sin((180 - v_abs_upper_arm_angle) * DEG_TO_RAD));

	d_wrist_left_x = (int)(v_forearms * cos(v_abs_lower_arm_angle * DEG_TO_RAD));
	d_wrist_left_y = (int)(v_forearms * sin(v_abs_lower_arm_angle * DEG_TO_RAD));

	d_wrist_right_x = (int)(v_forearms * cos((180 - v_abs_lower_arm_angle) * DEG_TO_RAD));
	d_wrist_right_y = (int)(v_forearms * sin((180 - v_abs_lower_arm_angle) * DEG_TO_RAD));

	d_hand_left_x = (int)(v_hands * cos(v_abs_lower_arm_angle * DEG_TO_RAD));
	d_hand_left_y = (int)(v_hands * sin(v_abs_lower_arm_angle * DEG_TO_RAD));

	d_hand_right_x = (int)(v_hands * cos((180 - v_abs_lower_arm_angle) * DEG_TO_RAD));
	d_hand_right_y = (int)(v_hands * sin((180 - v_abs_lower_arm_angle) * DEG_TO_RAD));

	d_knee_left_x = (int)(v_upper_legs * cos(v_abs_upper_leg_angle * DEG_TO_RAD));
	d_knee_left_y = (int)(v_upper_legs * sin(v_abs_upper_leg_angle * DEG_TO_RAD));

	d_knee_right_x = (int)(v_upper_legs * cos((180 - v_abs_upper_leg_angle) * DEG_TO_RAD));
	d_knee_right_y = (int)(v_upper_legs * sin((180 - v_abs_upper_leg_angle) * DEG_TO_RAD));

	d_ankle_left_x = (int)(v_lower_legs * cos(v_abs_lower_leg_angle * DEG_TO_RAD));
	d_ankle_left_y = (int)(v_lower_legs * sin(v_abs_lower_leg_angle * DEG_TO_RAD));

	d_ankle_right_x = (int)(v_lower_legs * cos((180 - v_abs_lower_leg_angle) * DEG_TO_RAD));
	d_ankle_right_y = (int)(v_lower_legs * sin((180 - v_abs_lower_leg_angle) * DEG_TO_RAD));

	d_foot_left_x = (int)(v_feet * cos(v_abs_lower_leg_angle * DEG_TO_RAD));
	d_foot_left_y = (int)(v_feet * sin(v_abs_lower_leg_angle * DEG_TO_RAD));

	d_foot_right_x = (int)(v_feet * cos((180 - v_abs_lower_leg_angle) * DEG_TO_RAD));
	d_foot_right_y = (int)(v_feet * sin((180 - v_abs_lower_leg_angle) * DEG_TO_RAD));

	// Create Points
	p_head = Point(p_top.x, p_top.y + v_head);
	p_body_upper = Point(p_head.x, p_head.y + v_head);
	p_shoulders = Point(p_top.x, p_top.y + v_shoulders);
	p_groin = Point(p_body_upper.x, p_body_upper.y + v_body);
	p_elbow_left = Point(p_shoulders.x + d_elbow_left_x, p_shoulders.y + d_elbow_left_y);
	p_elbow_right = Point(p_shoulders.x + d_elbow_right_x, p_shoulders.y + d_elbow_right_y);
	p_wrist_left = Point(p_elbow_left.x + d_wrist_left_x, p_elbow_left.y + d_wrist_left_y);
	p_wrist_right = Point(p_elbow_right.x + d_wrist_right_x, p_elbow_right.y + d_wrist_right_y);
	p_hand_left = Point(p_wrist_left.x + d_hand_left_x, p_wrist_left.y + d_hand_left_y);
	p_hand_right = Point(p_wrist_right.x + d_hand_right_x, p_wrist_right.y + d_hand_right_y);
	p_knee_left = Point(p_groin.x + d_knee_left_x, p_groin.y + d_knee_left_y);
	p_knee_right = Point(p_groin.x + d_knee_right_x, p_groin.y + d_knee_right_y);
	p_ankle_left = Point(p_knee_left.x + d_ankle_left_x, p_knee_left.y + d_ankle_left_y);
	p_ankle_right = Point(p_knee_right.x + d_ankle_right_x, p_knee_right.y + d_ankle_right_y);
	p_foot_left = Point(p_ankle_left.x + d_foot_left_x, p_ankle_left.y + d_foot_left_y);
	p_foot_right = Point(p_ankle_right.x + d_foot_right_x, p_ankle_right.y + d_foot_right_y);

	// Create Shapes
	s_head = new Circle(p_head, v_head);
	s_head->set_color(c_color);

	s_body = new Line(p_body_upper, p_groin);
	s_body->set_color(c_color);

	s_arm_upper_left = new Line(p_shoulders, p_elbow_left);
	s_arm_upper_left->set_color(c_color);

	s_arm_upper_right = new Line(p_shoulders, p_elbow_right);
	s_arm_upper_right->set_color(c_color);

	s_forearm_left = new Line(p_elbow_left, p_wrist_left);
	s_forearm_left->set_color(c_color);

	s_forearm_right = new Line(p_elbow_right, p_wrist_right);
	s_forearm_right->set_color(c_color);

	s_hand_left = new Circle(p_hand_left, v_hands);
	s_hand_left->set_color(c_color);

	s_hand_right = new Circle(p_hand_right, v_hands);
	s_hand_right->set_color(c_color);

	s_leg_upper_left = new Line(p_groin, p_knee_left);
	s_leg_upper_left->set_color(c_color);

	s_leg_upper_right = new Line(p_groin, p_knee_right);
	s_leg_upper_right->set_color(c_color);

	s_leg_lower_left = new Line(p_knee_left, p_ankle_left);
	s_leg_lower_left->set_color(c_color);

	s_leg_lower_right = new Line(p_knee_right, p_ankle_right);
	s_leg_lower_right->set_color(c_color);

	s_foot_left = new Circle(p_foot_left, v_feet);
	s_foot_left->set_color(c_color);

	s_foot_right = new Circle(p_foot_right, v_feet);
	s_foot_right->set_color(c_color);
}

Graph_lib::StickFigure::~StickFigure()
{
}

void Graph_lib::StickFigure::draw_lines() const
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
