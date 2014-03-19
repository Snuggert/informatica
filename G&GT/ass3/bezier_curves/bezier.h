#ifndef BEZIER_H
#define BEZIER_H

#include <GL/gl.h>

// A single control point of a Bezier curve
typedef struct control_point
{
    float x;
    float y;
}control_point;

int 	factorial(int n);
float polynomial_term(int n, int k, float t);
void    evaluate_bezier_curve(float *x, float *y, control_point p[], int num_points, float t);
void    draw_bezier_curve(int num_segments, control_point p[], int num_points);
int     intersect_cubic_bezier_curve(float x, float *y, control_point p[], int num_points);

#endif
