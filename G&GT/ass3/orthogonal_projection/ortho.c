/* Computer Graphics, Assignment 5, Orthogonal projection
 *
 * Filename ........ ortho.c
 * Description ..... Contains the re-programmed orthogonal projection matrix
 * Date ............ 01.09.2006
 * Created by ...... Jurgen Sturm 
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
#include <GL/glut.h>   
#include <GL/gl.h>
#include <GL/glu.h>

 
#define sqr(x) ((x)*(x))

/* ANSI C/ISO C89 does not specify this constant (?) */
#ifndef M_PI
#define M_PI           3.14159265358979323846  /* pi */
#endif

void myOrtho(GLdouble left,
             GLdouble right,
             GLdouble bottom,
             GLdouble top,
             GLdouble near,
             GLdouble far) {

    float tx, ty, tz;
    /*
     * Thought it was nice to do this outside the matrix.
     */
    tx = -((right + left) / (right - left));
    ty = -((top + bottom) / (top - bottom));
    tz = -((far + near) / (far - near));

    GLfloat M[16] =
    {
        2 / (right - left), 0.0, 0.0, 0.0,
        0.0, 2 / (top - bottom), 0.0, 0.0,
        0.0, 0.0, -2 / (far - near), 0.0,
        tx, ty, tz, 1.0
    };
    glMultMatrixf(M);
}
