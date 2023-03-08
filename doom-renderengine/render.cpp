//
//  render.cpp
//  doom-renderengine
//
//  Created by Juan Pablo Gutierrez on 07/03/23.
//
#include "render.hpp"
#include "player.hpp"

#include <stdio.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <math.h>
#include <GLUT/GLUT.h>

typedef struct{
    int fr1, fr2;
}xtime; xtime T;

int tick;

//Handles pixel drawing according to the color
void pixel(int x, int y, int c){
    int rgb[3];
    
    if(c == 0) {rgb[0] = 255; rgb[1] = 255; rgb[2] = 0;} //Yellow
    if(c == 1) {rgb[0] = 160; rgb[1] = 160; rgb[2] = 0;} //Darker Yellow
    if(c == 2) {rgb[0] = 0; rgb[1] = 255; rgb[2] = 0;} //Green
    if(c == 3) {rgb[0] = 0; rgb[1] = 160; rgb[2] = 0;} //Darker Green
    if(c == 4) {rgb[0] = 0; rgb[1] = 255; rgb[2] = 255;} //Cyan
    if(c == 5) {rgb[0] = 0; rgb[1] = 160; rgb[2] = 160;} //Darker Cyan
    if(c == 6) {rgb[0] = 160; rgb[1] = 100; rgb[2] = 0;} //Brown
    if(c == 7) {rgb[0] = 110; rgb[1] = 50; rgb[2] = 0;} //Darker brown
    if(c == 8) {rgb[0] = 0; rgb[1] = 60; rgb[2] = 130;} //Background
    if(c == 9) {rgb[0] = 160; rgb[1] = 0; rgb[2] = 0;} //Red
    if(c == 8) {rgb[0] = 255; rgb[1] = 0; rgb[2] = 130;} //Darker red
    
    glColor3ub(rgb[0], rgb[1], rgb[2]);
    glBegin(GL_POINT);
    glVertex2i(x * pixelScale + 2, y * pixelScale + 2);
    glEnd();
}

//Uses the pixel() function to set all pixels to black
void clearBackground(){
    int x, y;
    for (y = 0; y < sHeight; y++) {
        for (x = 0; x < sWidth; x++) {
            pixel(x, y, 8);
        }
    }
}

void draw3D(){
    int x, y, c = 0;
    for (y = 0; y < sHeight2; y++) {
        for (x = 0; x < sHeight2; x++) {
            pixel(x, y, c);
            c += 1;
            if(c > 8) {c = 0;}
        }
    }
    
    //Manages frame rate
    tick += 1; if(tick > 20 ) {tick = 0;}
    pixel(sWidth2, sHeight2, 0);
}

void display(){
    int x, y;
    if(T.fr1 - T.fr2 >= 50){
        movePlayer();
        draw3D();
        
        T.fr2 = T.fr1;
                
    }
    T.fr1 = glutGet(GLUT_ELAPSED_TIME);
    
    glutPostRedisplay();
}