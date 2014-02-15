/* Computer Graphics assignment, Triangle Rasterization
 * Filename ........ trirast.c
 * Description ..... Implements triangle rasterization
 * Created by ...... Paul Melis
 *
 * Student name: Abe Wiersma
 * Student email: abe.wiersma@hotmail.nl
 * Collegekaart: 10433120
 * Date: 09-02-2014
 * Comments: Due to being out of the country the startup took some time.
 *
 *
 * (always fill in these fields before submitting!!)
 */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "trirast.h"

/*
 * Rasterize a single triangle.
 * The triangle is specified by its corner coordinates
 * (x0,y0), (x1,y1) and (x2,y2).
 * The triangle is drawn in color (r,g,b).
 */

/*
 * The default triangle rasterization function
 */
void draw_triangle(float x0, float y0, float x1, float y1, float x2, float y2,
    byte r, byte g, byte b){
    int x_min, x_max, y_min, y_max;
    float alpha, beta, gamma, alpha_part, beta_part, gamma_part;
    float x_array[3] = {x0, x1, x2};
    float y_array[3] = {y0, y1, y2};

    /*
     * Set x_min and x_max to first x position of the corner, point x0.
     */
    x_min = floor(x0);
    x_max = ceil(x0);

    /*
     * Set y_min and y_max to first y position of a corner, point y0.
     */
    y_min = floor(y0);
    y_max = ceil(y0);


    /*
     * Because we put the extrema's to the first points we start with an index
     * of 1.
     */
    for(int index = 1; index < 3; index++){
        if(floor(x_array[index]) < x_min){
            x_min = floor(x_array[index]);
        }
        else if(ceil(x_array[index]) > x_max){
            x_max = ceil(x_array[index]);
        }
        if(floor(y_array[index]) < x_min){
            y_min = floor(y_array[index]);
        }
        else if(ceil(y_array[index]) > x_max){
            y_max = ceil(y_array[index]);
        }
    }

    /*
     * this seemed so obvious i automatically implemented it.
     */
    alpha_part = func1(x_array[0], y_array[0], x_array[1], y_array[1],
                          x_array[2], y_array[2]);
    beta_part = func1(x_array[1], y_array[1], x_array[2], y_array[2],
                          x_array[0], y_array[0]);
    gamma_part = func1(x_array[2], y_array[2], x_array[0], y_array[0],
                          x_array[1], y_array[1]);

    /*
     * Loop from the algorithm.
     */
    for(int y = y_min; y < y_max; y++){
        for(int x = x_min; x < x_max; x++){
            alpha = func1((float)x, (float)y, x_array[1], y_array[1],
                          x_array[2], y_array[2]) / alpha_part;
            beta = func1((float)x, (float)y, x_array[2], y_array[2],
                          x_array[0], y_array[0]) / beta_part;
            gamma = func1((float)x, (float)y, x_array[0], y_array[0],
                          x_array[1], y_array[1]) / gamma_part;
            if((alpha > 0) && (beta > 0) && (gamma > 0)){
                PutPixel(x, y, r, g, b);
            }
        }
    }
}

/*
 * The optimized triangle rasterization function
 */
void draw_triangle_optimized(float x0, float y0, float x1, float y1, float x2,
    float y2, byte r, byte g, byte b){
    int x_min, x_max, y_min, y_max;
    float alpha, beta, gamma, alpha_part, beta_part, gamma_part;
    float x_array[3] = {x0, x1, x2};
    float y_array[3] = {y0, y1, y2};

    /*
     * Set x_min and x_max to first x position of the corner, point x0.
     */
    x_min = floor(x0);
    x_max = ceil(x0);

    /*
     * Set y_min and y_max to first y position of a corner, point y0.
     */
    y_min = floor(y0);
    y_max = ceil(y0);


    /*
     * Because we put the extrema's to the first points we start with an index
     * of 1.
     */
    for(int index = 1; index < 3; index++){
        if(floor(x_array[index]) < x_min){
            x_min = floor(x_array[index]);
        }
        else if(ceil(x_array[index]) > x_max){
            x_max = ceil(x_array[index]);
        }
        if(floor(y_array[index]) < x_min){
            y_min = floor(y_array[index]);
        }
        else if(ceil(y_array[index]) > x_max){
            y_max = ceil(y_array[index]);
        }
    }

    /*
     * this seemed so obvious i automatically implemented it.
     */
    alpha_part = func1(x_array[0], y_array[0], x_array[1], y_array[1],
                          x_array[2], y_array[2]);
    beta_part = func1(x_array[1], y_array[1], x_array[2], y_array[2],
                          x_array[0], y_array[0]);
    gamma_part = func1(x_array[2], y_array[2], x_array[0], y_array[0],
                          x_array[1], y_array[1]);

    /*
     * Optimized loop from the algorithm.
     */
    for(int y = y_min; y < y_max; y++){
        for(int x = x_min; x < x_max; x++){
            alpha = func1((float)x, (float)y, x_array[1], y_array[1],
                          x_array[2], y_array[2]) / alpha_part;
            beta = func1((float)x, (float)y, x_array[2], y_array[2],
                          x_array[0], y_array[0]) / beta_part;
            gamma = func1((float)x, (float)y, x_array[0], y_array[0],
                          x_array[1], y_array[1]) / gamma_part;
            if((alpha >= 0) && (beta >= 0) && (gamma >= 0)){
                if((alpha > 0 || func1(-1.0, -1.0, x_array[1], y_array[1],
                                       x_array[2], y_array[2]) * alpha_part > 0)
                   && (beta > 0 || func1(-1.0, -1.0, x_array[2], y_array[2], 
                                         x_array[0], y_array[0]) * beta_part)
                   && (gamma > 0 || func1(-1.0, -1.0, x_array[0], y_array[0],
                                          x_array[1], y_array[1]) * 
                                                gamma_part > 0)){
                    PutPixel(x, y, r, g, b);
                }
            }
        }
    }
}

/*
 * A function for the functions in the algorithm.
 */
float func1(float x, float y, float x0, float y0, float x1, float y1){
    return (y0 - y1) * x + (x1 - x0) * y + x0 * y1 - x1 * y0;
}