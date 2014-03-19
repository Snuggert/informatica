/* Computer Graphics, Assignment, Bezier curves
 * Filename ........ bezier.c
 * Description ..... Bezier curves
 * Date ............ 22.07.2009
 * Created by ...... Paul Melis
 *
 * Student name ....
 * Student email ...
 * Collegekaart ....
 * Date ............
 * Comments ........
 *
 *
 * (always fill in these fields before submitting!!)
 */

#include <math.h>
#include "bezier.h"
#include <stdio.h>

/*
 * Return factorial of n.
 */
int factorial(int n)
{
    if (n<=1){
        return(1);
    }
    else{
        n=n*factorial(n-1);
    }
    return(n);
}

float polynomial_term(int n, int k, float t){
	return (factorial(n) / (factorial(k) * factorial(n-k))) * pow(t, k) 
															* pow((1-t), n-k);
}

/* Given a Bezier curve defined by the 'num_points' control points
 * in 'p' compute the position of the point on the curve for parameter
 * value 'u'.
 *
 * Return the x and y values of the point by setting *x and *y,
 * respectively.
 */

void
evaluate_bezier_curve(float *x, float *y, control_point p[], int num_points, float t)
{
	float term_val;
    *x = 0.0;
    *y = 0.0;
    for(int k = 0; k < num_points; k++){
    	term_val = polynomial_term(num_points - 1, k, t);
    	*x += term_val * p[k].x;
    	*y += term_val * p[k].y;
    }
}

/* Draw a Bezier curve defined by the control points in p[], which
 * will contain 'num_points' points.
 *
 * Draw the line segments you compute directly on the screen
 * as a single GL_LINE_STRIP. This is as simple as using
 *
 *      glBegin(GL_LINE_STRIP);
 *      glVertex2f(..., ...);
 *      ...
 *      glEnd();
 *
 * DO NOT SET ANY COLOR!
 *
 * The 'num_segments' parameter determines the "discretization" of the Bezier
 * curve and is the number of straight line segments that should be used
 * to approximate the curve.
 *
 * Call evaluate_bezier_curve() to compute the necessary points on
 * the curve.
 */

void
draw_bezier_curve(int num_segments, control_point p[], int num_points)
{
	float x, y;
	glBegin(GL_LINE_STRIP);
	for(int n = 0; n <= num_segments; n++){
		evaluate_bezier_curve(&x, &y, p, num_points, (float)n / num_segments);
		glVertex2f(x, y);
	}
	glEnd();
}

/* Find the intersection of a cubic Bezier curve with the line X=x.
   Return 1 if an intersection was found and place the corresponding y
   value in *y.
   Return 0 if no intersection exists.
*/

int
intersect_cubic_bezier_curve(float x, float *y, control_point p[], int num_points)
{
	float testx, testy;
	for(float t = 0.0; t <= 1.0; t += 0.001){
		evaluate_bezier_curve(&testx, &testy, p, num_points, t);
		if(fabs(testx - x) < 0.001){
			*y = testy;
			return 1;
		}
	}
    return 0;
}

