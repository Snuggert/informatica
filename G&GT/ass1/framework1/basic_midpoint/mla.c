/* Computer Graphics, Assignment 1, Bresenham's Midpoint Line-Algorithm
 *
 * Filename ........ mla.c
 * Description ..... Midpoint Line Algorithm
 * Created by ...... Jurgen Sturm 
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

#include "SDL.h"   
#include "init.h"
#include "math.h"

/*
 * Midpoint Line Algorithm
 *
 * As you probably will have figured out, this is the part where you prove
 * your programming skills. The code in the mla function should draw a direct 
 * line between (x0,y0) and (x1,y1) in the specified color. 
 * 
 * Until now, the example code below draws only a horizontal line between
 * (x0,y0) and (x1,y0) and a vertical line between (x1,y1).
 * 
 * And here the challenge begins..
 *
 * Good luck!
 *
 *
 */
void mla(SDL_Surface *s, int x0, int y0, int x1, int y1, Uint32 colour) {
    int dx, dy, iy, ix, y, x;
    float error, derror;
    dx = x1 - x0;
    dy = y1 - y0;
    /*
     * If x1 is larger than x0 it means that the loop must count back from x0 
     * to x1. Same goes fdr y1 and y0.
     */
    if(x1>x0) ix=1; else ix=-1;
    if(y1>y0) iy=1; else iy=-1;
    error = 0;

    /*
     * Draw the straightest line possible with a larger difference in y or a 
     * larger difference in x.
     */
    if(abs(dx) > abs(dy)){
        derror = fabs((float)dy / dx);
        y=y0;
        for(x=x0;x != x1;x=x+ix){
            PutPixel(s, x, y, colour);
            error += derror;
            if(error >= 0.5){
                y += iy;
                error -= 1;
            }
        }
    }
    else{
        derror = fabs((float)dx / dy);
        x=x0;
        for(y=y0;y != y1;y=y+iy){
            PutPixel(s, x, y, colour);
            error += derror;
            if(error >= 0.5){
                x += ix;
                error -= 1;
            }
        }
    }
    return;
}

