/* Computer Graphics, Assignment, Translations, Rotations and Scaling
 *
 * Filename ........ transformations.c
 * Description ..... Contains the re-programmed translation, rotation and scaling functions
 * Student name: Abe Wiersma
 * Student email: abe.wiersma@hotmail.nl
 * Collegekaart: 10433120
 * Date: 16-02-2014
 * Comments: Due to being out of the country the startup still took some time.
 *
 *
 *
 * (always fill in these fields before submitting!!)
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/gl.h>
#include "transformations.h"

/* ANSI C/ISO C89 does not specify this constant (?) */
#ifndef M_PI
#define M_PI           3.14159265358979323846  /* pi */
#endif

void myScalef(GLfloat x, GLfloat y, GLfloat z)
{
    GLfloat M[16] =
    {
        x, 0.0, 0.0, 0.0,
        0.0, y, 0.0, 0.0,
        0.0, 0.0, z, 0.0,
        0.0, 0.0, 0.0, 1.0
    };

    glMultMatrixf(M);
}


void myTranslatef(GLfloat x, GLfloat y, GLfloat z)
{
    GLfloat M[16] =
    {
        1.0, 0.0, 0.0, 0.0,
        0.0, 1.0, 0.0, 0.0,
        0.0, 0.0, 1.0, 0.0,
        x, y, z, 1.0
    };

    glMultMatrixf(M);
}

void myRotatef(GLfloat angle, GLfloat x, GLfloat y, GLfloat z)
{
    GLfloat u[3], v[3], w[3], t[3];
    float length;
    int smallest_index;

    //
    // 1. Create the orthonormal basis
    //
    // Store the incoming rotation axis in w and normalize w
    length = sqrt((x * x) + (y * y) + (z * z));
    w[0] = x / length;
    w[1] = y / length;
    w[2] = z / length;

    // Compute the value of t, based on w
    smallest_index = 0;

    t[0] = w[0];
    t[1] = w[1];
    t[2] = w[2];

    for(int index = 1; index < 3; index++){
        if(t[index] < t[smallest_index]){
            smallest_index = index;
        }
    }
    t[smallest_index] = 1;

    length = sqrt((t[0] * t[0]) + (t[1] * t[1]) + (t[2] * t[2]));
    for(int index = 0; index < 3; index++){
        t[index] = t[index] / length;
    }

    // Compute u = t x w
    u[0] = (t[1] * w[2]) - (t[2] * w[1]);
    u[1] = (t[2] * w[0]) - (t[0] * w[2]);
    u[2] = (t[0] * w[1]) - (t[1] * w[0]);

    // Normalize u
    length = sqrt((u[0] * u[0]) + (u[1] * u[1]) + (u[2] * u[2]));
    for(int index = 0; index < 3; index++){
        u[index] = u[index] / length;
    }

    // Compute v = w x u
    v[0] = (w[1] * u[2]) - (w[2] * u[1]);
    v[1] = (w[2] * u[0]) - (w[0] * u[2]);
    v[2] = (w[0] * u[1]) - (w[1] * u[0]);

    // Normalize v
    length = sqrt((v[0] * v[0]) + (v[1] * v[1]) + (v[2] * v[2]));
    for(int index = 0; index < 3; index++){
        v[index] = v[index] / length;
    }

    // At this point u, v and w should form an orthonormal basis.
    // If your routine does not seem to work correctly it might be
    // a good idea to the check the vector values.

    //
    // 2. Set up the three matrices making up the rotation
    //

    // Specify matrix A

    GLfloat A[16] =
    {
        u[0], u[1], u[2], 0.0,
        v[0], v[1], v[2], 0.0,
        w[0], w[1], w[2], 0.0,
        0.0,  0.0,  0.0,  1.0
    };

    // Convert 'angle' to radians

    // Specify matrix B

    GLfloat B[16] =
    {
        cos(angle * M_PI / 180.0), sin(angle * M_PI / 180.0), 0.0, 0.0,
        -sin(angle * M_PI / 180.0), cos(angle * M_PI / 180.0), 0.0, 0.0,
        0.0, 0.0, 1.0, 0.0,
        0.0, 0.0, 0.0, 1.0
    };

    // Specify matrix C

    GLfloat C[16] =
    {
        u[0], v[0], w[0], 0.0,
        u[1], v[1], w[1], 0.0,
        u[2], v[2], w[2], 0.0,
        0.0,  0.0,  0.0,  1.0
    };

    //
    // 3. Apply the matrices to get the combined rotation
    //

    glMultMatrixf(A);
    glMultMatrixf(B);
    glMultMatrixf(C);
}

