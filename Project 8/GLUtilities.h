//FILE NAME:GLUtilities.h
//description:Tools for openGL
//Author:Nabeel Alkhatib
//Date created:11/13/2018
//Date modified:11/13/2018

#include"Material.h"
#include <GL\freeglut.h>
#include <iostream>
using namespace std;

#pragma once
#if !defined (_GL_UTILITIES_H_)								// can get rid of first and last _
#define _GL_UTILITIES_H_

void drawCube();
void drawTexturedCube(Material mats[], float w);
void drawPyramid();



void drawStrokeText(char *text, void *font, GLfloat x, GLfloat y, GLfloat z);
GLfloat getStrokeTextWidth(char *text, void *font);

void drawBitmapText(char *text, void *font, GLfloat x, GLfloat y);
GLfloat getBitmapTextWidth(char *text,void *font);

#endif			//_GL_UTILITES_H_
