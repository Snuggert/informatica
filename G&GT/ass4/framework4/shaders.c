/* Computer Graphics and Game Technology, Assignment Ray-tracing
 *
 * Student name Abe Wiersma
 * Student email abe.wiersma@hotmail.nl
 * Collegekaart 10433120
 * Date 06-03-2014
 * Comments ........
 *
 *
 * (always fill in these fields before submitting!!)
 */

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "shaders.h"
#include "perlin.h"
#include "v3math.h"
#include "intersection.h"
#include "scene.h"
#include "quat.h"
#include "constants.h"

// shade_constant()
//
// Always return the same color. This shader does no real computations
// based on normal, light position, etc. As such, it merely creates
// a "silhouette" of an object.

vec3
shade_constant(intersection_point ip)
{
    return v3_create(1, 0, 0);
}

vec3
shade_matte(intersection_point ip)
{
    int index;
    float intensity;
    vec3 light_vector;

    intensity = scene_ambient_light;
    /* Calculate intensity from all light sources. */
    for(index = 0; index < scene_num_lights; index++)
    {
        if(shadow_check(v3_add(ip.p, v3_multiply(ip.n, 0.0001)),
                scene_lights[index].position) == 0)
        {
            light_vector = v3_normalize(v3_subtract(scene_lights[index].position, ip.p));
            intensity += scene_lights[index].intensity *
                    fmax(0.0, v3_dotprod(ip.n, light_vector));
        }
    }
    /*
     * The intensity must be in range 0..1, here we check if intensity is not 1
     * or above.
     */
    if (intensity > 1)
        intensity = 1;
    return v3_create(intensity, intensity, intensity);
}

vec3
shade_blinn_phong(intersection_point ip)
{
    float a, b;
    vec3 light_vector, halfway;
    int index;
    float matte, phong;

    matte = 0;
    phong = 0;

    /* Calculate intensity from all light sources. */
    for(index = 0; index < scene_num_lights; index++)
    {
        /* Calculate the light vector. */
        light_vector = v3_normalize(v3_subtract(scene_lights[index].position, ip.p));
        if(shadow_check(v3_add(ip.p, v3_multiply(ip.n, 0.0005)), scene_lights[index].position) == 0)
        {
            /* If there is no shadow calculate the color. */
            matte += (scene_lights[index].intensity * fmax(0.0, v3_dotprod(ip.n, light_vector)));
        }
        halfway = v3_normalize(v3_add(ip.i, light_vector));
        /* Add the highlight */
        phong += (scene_lights[index].intensity * fmax(0.0, pow(v3_dotprod(halfway, ip.n), 50)));
    }

    matte *= 0.8;
    matte += scene_ambient_light;
    phong *= 0.5;
    a = matte + phong;
    b = phong;
    if(a > 1) a = 1;
    if(b > 1) b = 1;
    /* create c_full from a and b */
    return v3_create(a, b, b);
}

vec3
shade_reflection(intersection_point ip)
{
    float a, b, c;
    vec3 r, result, matte;

    result = v3_create(0, 0, 0);
    
    r = v3_normalize(v3_subtract(v3_multiply(ip.n, v3_dotprod(ip.i, ip.n) * 2), ip.i));
    matte = shade_matte(ip);
    result = v3_add(ray_color(ip.ray_level + 1, v3_add(ip.p, v3_multiply(ip.n, 0.0005)), r), result);
    
    a = 0.75 * matte.x + 0.25 * result.x;
    b = 0.75 * matte.y + 0.25 * result.y;
    c = 0.75 * matte.z + 0.25 * result.z;
    
    if(a > 1) a = 1;
    if(b > 1) b = 1;
    if(c > 1) c = 1;
    
    return v3_create(a, b, c);
}

// Returns the shaded color for the given point to shade.
// Calls the relevant shading function based on the material index.
vec3
shade(intersection_point ip)
{
    switch (ip.material)
    {
        case 0:
            return shade_constant(ip);
        case 1:
            return shade_matte(ip);
        case 2:
            return shade_blinn_phong(ip);
        case 3:
            return shade_reflection(ip);
        default:
            return shade_constant(ip);

    }
}

// Determine the surface color for the first object intersected by
// the given ray, or return the scene background color when no
// intersection is found
vec3
ray_color(int level, vec3 ray_origin, vec3 ray_direction)
{
        intersection_point  ip;

        // If this ray has been reflected too many times, simply
        // return the background color.
        if (level >= 3)
                return scene_background_color;

        // Check if the ray intersects anything in the scene
        if (find_first_intersection(&ip, ray_origin, ray_direction))
        {
                // Shade the found intersection point
                ip.ray_level = level;
                return shade(ip);
        }

        // Nothing was hit, return background color
        return scene_background_color;
}
