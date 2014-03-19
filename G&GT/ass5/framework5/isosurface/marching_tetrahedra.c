/* Computer Graphics, Assignment, Volume rendering with cubes/points/isosurface
 *
 * Student name: Abe Wiersma
 * Student email: abe.wiersma@hotmail.nl
 * Collegekaart: 10433120
 * Date: 13-03-14
 * Comments ........
 *
 * (always fill in these fields before submitting!!)
 */

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "marching_tetrahedra.h"

/* Compute a linearly interpolated position where an isosurface cuts
   an edge between two vertices (p1 and p2), each with their own
   scalar value (v1 and v2) */

static vec3
interpolate_points(unsigned char isovalue, vec3 p1, vec3 p2, unsigned char v1, unsigned char v2)
{
    /* Initially, simply return the midpoint between p1 and p2.
       So no real interpolation is done yet */

    return v3_add(v3_multiply(p1, 0.5), v3_multiply(p2, 0.5));
}

/* Using the given iso-value generate triangles for the tetrahedron
   defined by corner vertices v0, v1, v2, v3 of cell c.

   Store the resulting triangles in the "triangles" array.

   Return the number of triangles created (either 0, 1, or 2).

   Note: the output array "triangles" should have space for at least
         2 triangles.
*/

static int
generate_tetrahedron_triangles(triangle *triangles, unsigned char isovalue, cell c, int v0, int v1, int v2, int v3)
{
    int w1 = 0, w2 = 0, w3 = 0, w0 = 0;

    if(volume[(int)c.value[v0]] > isovalue) 
        w0 = 1;
    if(volume[(int)c.value[v1]] > isovalue) 
        w1 = 1;
    if(volume[(int)c.value[v2]] > isovalue) 
        w2 = 1;
    if(volume[(int)c.value[v3]] > isovalue) 
        w3 = 1;

    /* interpolate as shown in figure 10 of assignment. */
    if((w3 == 0 && w2 == 0 && w1 == 0 && w0 == 1) || (w3 == 1 && w2 == 1 && w1 == 1 && w0 == 0))
    {
        triangles[0].p[0] = interpolate_points(isovalue, c.p[v0], c.p[v1], c.value[v0], c.value[v1]);
        triangles[0].p[1] = interpolate_points(isovalue, c.p[v0], c.p[v2], c.value[v0], c.value[v2]);
        triangles[0].p[2] = interpolate_points(isovalue, c.p[v0], c.p[v3], c.value[v0], c.value[v3]);
        return 1;
    }
    if((w3 == 0 && w2 == 0 && w1 == 1 && w0 == 0) || (w3 == 1 && w2 == 1 && w1 == 0 && w0 == 1))
    {
        triangles[0].p[0] = interpolate_points(isovalue, c.p[v0], c.p[v1], c.value[v0], c.value[v1]);
        triangles[0].p[1] = interpolate_points(isovalue, c.p[v1], c.p[v2], c.value[v1], c.value[v2]);
        triangles[0].p[2] = interpolate_points(isovalue, c.p[v1], c.p[v3], c.value[v1], c.value[v3]);
        return 1;
    }
    if((w3 == 0 && w2 == 1 && w1 == 0 && w0 == 0) || (w3 == 1 && w2 == 0 && w1 == 1 && w0 == 1))
    {
        triangles[0].p[0] = interpolate_points(isovalue, c.p[v2], c.p[v0], c.value[v2], c.value[v0]);
        triangles[0].p[1] = interpolate_points(isovalue, c.p[v1], c.p[v2], c.value[v1], c.value[v2]);
        triangles[0].p[2] = interpolate_points(isovalue, c.p[v2], c.p[v3], c.value[v2], c.value[v3]);
        return 1;
    }
    if((w3 == 1 && w2 == 0 && w1 == 0 && w0 == 0) || (w3 == 0 && w2 == 1 && w1 == 1 && w0 == 1))
    {
        triangles[0].p[0] = interpolate_points(isovalue, c.p[v3], c.p[v0], c.value[v3], c.value[v0]);
        triangles[0].p[1] = interpolate_points(isovalue, c.p[v1], c.p[v3], c.value[v1], c.value[v3]);
        triangles[0].p[2] = interpolate_points(isovalue, c.p[v2], c.p[v3], c.value[v2], c.value[v3]);
        return 1;
    }
    if((w3 == 0 && w2 == 0 && w1 == 1 && w0 == 1) || (w3 == 1 && w2 == 1 && w1 == 0 && w0 == 0))
    {
        triangles[0].p[0] = interpolate_points(isovalue, c.p[v0], c.p[v1], c.value[v0], c.value[v1]);
        triangles[0].p[1] = interpolate_points(isovalue, c.p[v1], c.p[v2], c.value[v1], c.value[v2]);
        triangles[0].p[2] = interpolate_points(isovalue, c.p[v1], c.p[v3], c.value[v1], c.value[v3]);
        triangles[1].p[0] = interpolate_points(isovalue, c.p[v0], c.p[v1], c.value[v0], c.value[v1]);
        triangles[1].p[1] = interpolate_points(isovalue, c.p[v0], c.p[v2], c.value[v0], c.value[v2]);
        triangles[1].p[2] = interpolate_points(isovalue, c.p[v0], c.p[v3], c.value[v0], c.value[v3]);
        return 2;
    }
    if((w3 == 0 && w2 == 1 && w1 == 0 && w0 == 1) || (w3 == 1 && w2 == 0 && w1 == 1 && w0 == 0))
    {
        triangles[0].p[0] = interpolate_points(isovalue, c.p[v0], c.p[v1], c.value[v0], c.value[v1]);
        triangles[0].p[1] = interpolate_points(isovalue, c.p[v0], c.p[v2], c.value[v0], c.value[v2]);
        triangles[0].p[2] = interpolate_points(isovalue, c.p[v0], c.p[v3], c.value[v0], c.value[v3]);
        triangles[1].p[0] = interpolate_points(isovalue, c.p[v2], c.p[v0], c.value[v2], c.value[v0]);
        triangles[1].p[1] = interpolate_points(isovalue, c.p[v1], c.p[v2], c.value[v1], c.value[v2]);
        triangles[1].p[2] = interpolate_points(isovalue, c.p[v2], c.p[v3], c.value[v2], c.value[v3]);
        return 2;
    }
    if((w3 == 0 && w2 == 1 && w1 == 1 && w0 == 0) || (w3 == 1 && w2 == 0 && w1 == 0 && w0 == 1))
    {
        triangles[0].p[0] = interpolate_points(isovalue, c.p[v2], c.p[v0], c.value[v2], c.value[v0]);
        triangles[0].p[1] = interpolate_points(isovalue, c.p[v1], c.p[v2], c.value[v1], c.value[v2]);
        triangles[0].p[2] = interpolate_points(isovalue, c.p[v2], c.p[v3], c.value[v2], c.value[v3]);
        triangles[1].p[0] = interpolate_points(isovalue, c.p[v0], c.p[v1], c.value[v0], c.value[v1]);
        triangles[1].p[1] = interpolate_points(isovalue, c.p[v1], c.p[v2], c.value[v1], c.value[v2]);
        triangles[1].p[2] = interpolate_points(isovalue, c.p[v1], c.p[v3], c.value[v1], c.value[v3]);
        return 2;
    }
    return 0;
}

/* Generate triangles for a single cell for the given iso-value. This function
   should produce at most 6 * 2 triangles (for which the "triangles" array should
   have enough space).

   Use calls to generate_tetrahedron_triangles().

   Return the number of triangles produced
*/

int
generate_cell_triangles(triangle *triangles, cell c, unsigned char isovalue)
{
    int tri_num = 0;
    tri_num += generate_tetrahedron_triangles(&triangles[tri_num], isovalue, c, 0, 1, 3, 7);
    tri_num += generate_tetrahedron_triangles(&triangles[tri_num], isovalue, c, 0, 2, 6, 7);
    tri_num += generate_tetrahedron_triangles(&triangles[tri_num], isovalue, c, 0, 4, 5, 7);
    tri_num += generate_tetrahedron_triangles(&triangles[tri_num], isovalue, c, 0, 1, 5, 7);
    tri_num += generate_tetrahedron_triangles(&triangles[tri_num], isovalue, c, 0, 2, 3, 7);
    tri_num += generate_tetrahedron_triangles(&triangles[tri_num], isovalue, c, 0, 4, 6, 7);
    return tri_num;
}
