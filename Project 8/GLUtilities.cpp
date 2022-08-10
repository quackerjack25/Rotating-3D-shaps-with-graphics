//FILE NAME:GLUtilities.cpp
//description:See Structural file for details
//Author:Nabeel Alkhatib
//Date created:11/13/2018
//Date modified:11/13/2018

#include "GLUtilities.h"

void drawCube()
{

    glBegin(GL_QUADS);
		
		//Top face (y = 1.0)

        glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f( 1.0f,  1.0f,  1.0f);        //A
		glVertex3f( 1.0f,  1.0f, -1.0f);        //F
		glVertex3f(-1.0f,  1.0f, -1.0f);        //E
		glVertex3f(-1.0f,  1.0f,  1.0f);        //B

    

        //Bottom Face (y = -1.0f)

        glColor3f(0.5f, 0.5f, 1.0f);
		glVertex3f(-1.0f, -1.0f,  1.0f);        //C
		glVertex3f(-1.0f, -1.0f, -1.0f);        //H
		glVertex3f( 1.0f, -1.0f, -1.0f);        //G
        glVertex3f( 1.0f, -1.0f,  1.0f);        //D

    

        //Front face (z = 1.0f)

        glColor3f(0.0f, 1.0f, 0.0f);
        glVertex3f( 1.0f,  1.0f,  1.0f);        //A
        glVertex3f(-1.0f,  1.0f,  1.0f);        //B
        glVertex3f(-1.0f, -1.0f,  1.0f);        //C
        glVertex3f( 1.0f, -1.0f,  1.0f);        //D

    

        //Back Face (z = -1.0f)

        glColor3f(0.0f, 1.2f, 1.0f);
        glVertex3f(-1.0f,  1.0f, -1.0f);        //E
        glVertex3f( 1.0f,  1.0f, -1.0f);        //F
        glVertex3f( 1.0f, -1.0f, -1.0f);        //G
        glVertex3f(-1.0f, -1.0f, -1.0f);        //H

    

        //Right Face (x = 1.0f)

        glColor3f(0.0f, 0.0f, 1.0f);
        glVertex3f( 1.0f,  1.0f,  1.0f);        //A
        glVertex3f( 1.0f, -1.0f,  1.0f);        //D
        glVertex3f( 1.0f, -1.0f, -1.0f);        //G
        glVertex3f( 1.0f,  1.0f, -1.0f);        //F

    	// left face
		
		glColor3f(0.8f, 0.8f, 0.9f);
		glVertex3f(-1.0f,  1.0f,  1.0f);        //B
		glVertex3f(-1.0f,  1.0f, -1.0f);        //E
		glVertex3f(-1.0f, -1.0f, -1.0f);        //H
		glVertex3f(-1.0f, -1.0f,  1.0f);        //C
    
        
    glEnd();
}

void drawTexturedCube(Material mats[], float w)
{	
		// drawing of the cube
	float vertices[8][3] = {{ w, w, w },				//v0
						   { -w, w, w },					//v1
						   { -w, -w, w },				//v2	
						   { w, -w, w },					//v3
						   { w, -w, -w },				//v4
						   { w, w, -w },					//v5
						   { -w, w, -w },				//v6
						   { -w, -w, -w }};				//v7
	// Next, the order in which the vertices are linked 	  
	static int faces [6] [4] ={{0, 1, 2, 3},			// front
							   {0, 3, 4, 5},			// right
							   {0, 5, 6, 1},			// up
							   {4, 7, 6, 5},			// back
							   {1, 6, 7, 2},			// left
							   {2, 7, 4, 3}};					  
	
	// Now we can draw each of the quads
	for(int f=0; f<6; f++)
	{
		glPushMatrix();
		mats[f].setupMaterial();
		glBegin(GL_QUADS);
		glTexCoord2f(1.0f,1.0f);
		glVertex3f(vertices[faces[f][0]][0], vertices[faces[f][0]][1], vertices[faces[f][0]][2]);
		glTexCoord2f(0.0f,1.0f);
		glVertex3f(vertices[faces[f][1]][0], vertices[faces[f][1]][1], vertices[faces[f][1]][2]);
		glTexCoord2f(0.0f,0.0f);
		glVertex3f(vertices[faces[f][2]][0], vertices[faces[f][2]][1], vertices[faces[f][2]][2]);
		glTexCoord2f(1.0f,0.0f);
		glVertex3f(vertices[faces[f][3]][0], vertices[faces[f][3]][1], vertices[faces[f][3]][2]);
		glEnd();
		mats[f].stopMaterial();
		glPopMatrix();
	}
}

 void drawPyramid()
{
	glBegin(GL_TRIANGLES);
//Triangle 1
    glColor3f(1.0f,0.0f,0.0f); glVertex3f( 0.0f, 1.0f, 0.0f);   //V0(red)
    glColor3f(0.0f,1.0f,0.0f); glVertex3f(-1.0f,-1.0f, 1.0f);   //V1(green)
    glColor3f(0.0f,0.0f,1.0f); glVertex3f( 1.0f,-1.0f, 1.0f);   //V2(blue)
  //Triangle 2
    glColor3f(1.0f,0.0f,0.0f); glVertex3f( 0.0f, 1.0f, 0.0f);   //V0(red)
    glColor3f(0.0f,0.0f,1.0f); glVertex3f( 1.0f,-1.0f, 1.0f);   //V2(blue)
    glColor3f(0.0f,1.0f,0.0f); glVertex3f( 1.0f,-1.0f,-1.0f);   //V3(green)
  //Triangle 3
    glColor3f(1.0f,0.0f,0.0f); glVertex3f( 0.0f, 1.0f, 0.0f);   //V0(red)
    glColor3f(0.0f,1.0f,0.0f); glVertex3f( 1.0f,-1.0f,-1.0f);   //V3(green)
    glColor3f(0.0f,0.0f,1.0f); glVertex3f(-1.0f,-1.0f,-1.0f);   //V4(blue)
  //Triangle 4
    glColor3f(1.0f,0.0f,0.0f); glVertex3f( 0.0f, 1.0f, 0.0f);   //V0(red)
    glColor3f(0.0f,0.0f,1.0f); glVertex3f(-1.0f,-1.0f,-1.0f);   //V4(blue)
    glColor3f(0.0f,1.0f,0.0f); glVertex3f(-1.0f,-1.0f, 1.0f);   //V1(green)
        
	glEnd();
	
	glBegin(GL_QUADS);
	glColor3f(0.0f, 4.0f, 0.5f);
	
	glVertex3f( -1.0f, -1.0f, 1.0f);
	glVertex3f( -1.0f, -1.0f, -1.0f);
	glVertex3f( 1.0f, -1.0f, -1.0f);
	glVertex3f( 1.0f, -1.0f, 1.0f);
	glEnd();
}
void drawStrokeText(char *text, void *font, GLfloat x, GLfloat y, GLfloat z)
{
	glPushMatrix();
	glTranslatef(x, y, z);
	char *c;
	for (c=text; *c; c++)
	{
		
	glutStrokeCharacter(font, *c);
	
	}
	glPopMatrix();
}
GLfloat getStrokeTextWidth(char *text, void *font)
{
	
	GLfloat w = 0.0f;
	char *c;
	for (c=text; *c; c++)
	{
		
		w += glutStrokeWidth(font, *c);
	
	}
	return w;
}

void drawBitmapText(char *text, void *font, GLfloat x, GLfloat y)
{
	glPushMatrix();
	glRasterPos2f(x, y);
	char *c;
	for (c=text; *c; c++)
	{
		
		glutBitmapCharacter(font, *c);
	
	}
	glPopMatrix();
}
GLfloat getBitmapTextwidth(char *text, void *font)
{
	
	GLfloat w = 0.0f;
	char *c;
	for (c=text; *c; c++)
	{
		
		w += glutBitmapWidth(font, *c);
	
	}
	return w;
}
