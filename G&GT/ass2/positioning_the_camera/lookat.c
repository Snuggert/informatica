/* Computer Graphics, Assignment 4, Positioning the camera
 *
 * Filename ........ lookat.c
 * Description ..... Contains the re-programmed lookAt function
 * Created by ...... Jurgen Sturm 
 *
 * Student name: Abe Wiersma
 * Student email: abe.wiersma@hotmail.nl
 * Collegekaart: 10433120
 * Date: 16-02-2014
 * Comments: Due to being out of the country the startup still took some time.
 *
 *
 * (always fill in these fields before submitting!!)
 */
#include <GL/glut.h>   
#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>
 
/* ANSI C/ISO C89 does not specify this constant (?) */
#ifndef M_PI
#define M_PI           3.14159265358979323846  /* pi */
#endif

void myLookAt(GLdouble eyeX, GLdouble eyeY, GLdouble eyeZ,
              GLdouble centerX, GLdouble centerY, GLdouble centerZ,
              GLdouble upX, GLdouble upY, GLdouble upZ) {
    float cz[3], cx[3], cy[3], length;

    /*
     * vector in direction of eye to center is the center vector minus eye 
     * vector.
     */
    cz[0] = centerX - eyeX;
    cz[1] = centerY - eyeY;
    cz[2] = centerZ - eyeZ;

    /* Normalize */
    length = sqrt((cz[0] * cz[0]) + (cz[1] * cz[1]) + (cz[2] * cz[2]));
    for(int index = 0; index < 3; index++){
        cz[index] = cz[index] / length;
    }

    /* Compute cx = cz x up */
    cx[0] = (cz[1] * upZ) - (cz[2] * upY);
    cx[1] = (cz[2] * upX) - (cz[0] * upZ);
    cx[2] = (cz[0] * upY) - (cz[1] * upX);

    /* Normalize */
    length = sqrt((cx[0] * cx[0]) + (cx[1] * cx[1]) + (cx[2] * cx[2]));
    for(int index = 0; index < 3; index++){
        cx[index] = cx[index] / length;
    }

    /* Compute cy = cz x cx */
    cy[0] = ((cz[1] * cx[2]) - (cz[2] * cx[1])) * -1.0;
    cy[1] = ((cz[2] * cx[0]) - (cz[0] * cx[2])) * -1.0;
    cy[2] = ((cz[0] * cx[1]) - (cz[1] * cx[0])) * -1.0;

    /* Normalize */
    length = sqrt((cy[0] * cy[0]) + (cy[1] * cy[1]) + (cy[2] * cy[2]));
    for(int index = 0; index < 3; index++){
        cy[index] = cy[index] / length;
    }

    /* Create R matrix */
    GLfloat R[16] =
    {
        cx[0], cy[0], -cz[0], 0.0,
        cx[1], cy[1], -cz[1], 0.0,
        cx[2], cy[2], -cz[2], 0.0,
          0.0,   0.0,    0.0, 1.0
    };

    /* apply final result */
    glMultMatrixf(R);
}
