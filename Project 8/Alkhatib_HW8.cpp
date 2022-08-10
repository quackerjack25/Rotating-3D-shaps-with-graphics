//FILE NAME:HW8
//description:adding textures!
//Author:Nabeel Alkhatib
//Date created:11/27/2018
//Date modified:11/27/2018
#include "GLUtilities.h"
#include "camera.h"
#include "material.h"
//#include <iostream>
//using namespace std;
//Prototypes

void resetScene();
void display(void);
void reshape(GLsizei width, GLsizei height);
void keyboardClick(unsigned char key, int x, int y);
void mouseClick(int button, int state, int x, int y);
void mouseMotion(int x, int y);
void timer(int milisec);
void enableLights();

GLfloat locationX, locationY;	//current location of the object
GLfloat rotationX, rotationY;
GLsizei mouseX, mouseY;			//current mouse location in window
int orbitRotation;				//Rotation in degrees
bool blEnableLights= true;
bool blMouseLeftDown;			// Current state of button
bool blMouseMiddleDown;			// Current state of button
bool blMouseRightDown;			// Current state of button
int screenWidth = 640;
int screenHeight = 480; 

Camera avatarPOV;

Material ground;
Material teapot;
Material cone;
Material materials[6];
Material sky;
GLUquadric *q;

int main(int argc, char** argv) {

    

    //initializion functions
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE);      						//enable double buffer mode
    glutInitWindowSize(screenWidth, screenHeight); 				//set the window's initial width and height
    glutInitWindowPosition(50, 50); 							//sets the window's position to top-left corner
    glutCreateWindow("Textures Everywhere!!"); 		//has to go after init size & position

    //callback functions - set up scene
    glutDisplayFunc(&display); 			// Callback for display refresh
    glutReshapeFunc(&reshape); 			// Callback for window resizing
	glutKeyboardFunc(&keyboardClick); 	// Callback function for key presses
	glutMouseFunc(&mouseClick); 		// Callback function for mouse clicks
	glutMotionFunc(&mouseMotion);		//callback function for mouse movement 
	glutTimerFunc(20, &timer, 20);		//redraw every 20 ms
    
    ground.load("Textures//Stone1.tga");
    teapot.load("Textures//Tiles1.tga");
    cone.load("Textures//Stones2.tga");
    materials[0].load("Textures//Carpet1.tga");
    materials[1].load("Textures//Metal1.tga");
    materials[2].load("Textures//Tiles2.tga");
    materials[3].load("Textures//Wood7.tga");
    materials[4].load("Textures//Wood6.tga");
    materials[5].load("Textures//Wood5.tga");
    sky.load("Textures//Sky1.tga");
    
    
	q = gluNewQuadric();		//create new quadric 
	gluQuadricNormals(q, GL_SMOOTH);	// 
	gluQuadricTexture(q, GL_TRUE);		// 
	glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);		//
	glTexGeni(GL_T,GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);			//	
	
	resetScene();
	//main loop
	glutMainLoop();
	return EXIT_SUCCESS;

    

}





void resetScene(){
	
	avatarPOV.setLocation(0.0f, 0.0f, -19.0f);
	avatarPOV.setRotation(0.0f, 0.0f, 1.0f);
	locationX = 0.0f;
	locationY = 0.0f;
	rotationX = 0.0f;
	rotationY = 0.0f;
	orbitRotation = 0;
	mouseX=0;
	mouseY=0;
	 blMouseLeftDown = false;	
	 blMouseMiddleDown = false;	
	 blMouseRightDown	= false;
	 blEnableLights = true;

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);  				     //Set the background color to black & opaque
    glClearDepth(1.0f);                     			    //Set the background to furthest away
    glEnable(GL_DEPTH_TEST);                			   //enable depth test for z-culling
    glDepthFunc(GL_LEQUAL);                				  //set the depth to be in front of the background
    glShadeModel(GL_SMOOTH);                			 //set to smooth shading (or glat!)
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  //Use best perspective correction

    enableLights();
    reshape(screenWidth, screenHeight);
	
}

void enableLights()
{
	if(blEnableLights)
	{
		glEnable(GL_LIGHTING);
		glEnable(GL_COLOR_MATERIAL);					//make it not grey
		GLfloat lightKa[] = {0.2f, 0.2f, 0.2f, 1.0f};	//ambient light
		GLfloat lightKd[] = {0.7f, 0.7f, 0.7f, 1.0f};	//diffuse light
		GLfloat lightKs[] = {1.0f, 1.0f, 1.0f, 1.0f};	//specular light
		
		glLightfv(GL_LIGHT0, GL_AMBIENT, lightKa);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, lightKd);
		glLightfv(GL_LIGHT0, GL_SPECULAR, lightKs);
		//position the light
		GLfloat lightPos[] = {0.0f, 0.0f, -20.0f, 1.0f};			//positional light
		glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
		
		glEnable(GL_LIGHT0);
		
	}
	else
		glDisable(GL_LIGHTING);
	
}

void reshape(GLsizei width, GLsizei height){
    
    if (height <= 0) height = 1;		//sanity
    if (width <= 0) width = 1;			//sanity
	screenWidth = width;
	screenHeight = height;

	avatarPOV.setupCamera(CAM_PROJ_PERSPECTIVE, width, height, 45.0f, 0.01f, 2000.0f);  	  

	//Set the viewport to cover the new window size
	glViewport(0, 0, width, height);
    
    
    

}



void display(void){
	reshape(screenWidth, screenHeight);
	avatarPOV.runCamera();
	
	enableLights();
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);       // Go into model mode
    glEnable(GL_CULL_FACE);
    
    
	glLoadIdentity();	
	glTranslatef(0.0f, 0.0f, 10.0f);		//distance the axis of rotation 

	// draw center object
	glPushMatrix();
	glRotatef(-orbitRotation, 1.0f, 1.0f, 0.0f);		//change the axis of rotation
	glScalef(1.0f, 1.0f, 1.0f);
	drawTexturedCube(materials, 1.5f);
	glPopMatrix();


	// draw orbiting object
	glPushMatrix();
	glColor3f(1.0f, 0.3f, 0.5f);	
	glRotatef(rotationX, 1.0f, 0.0f,0.0f );
	glTranslatef(-1.5f + locationX, 3.0f, 4.0f); // c from origin 
	glRotatef(-orbitRotation, 1.0f, 0.0f,0.0f );
	glScalef(1.0f, 1.0f, 1.0f);
	teapot.setupMaterial();
	glutSolidTeapot(1.0);
	//glutSolidCone(1.0f, 1.0, 10, 10);
	teapot.stopMaterial();
	glPopMatrix();
	
	//draw the ground
	glPushMatrix();
	GLfloat groundSize = 1000.0f;
	GLfloat groundHeight = -18.0f;
	GLfloat repeatNum = groundSize / 10.0f;
	ground.setupMaterial();
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, repeatNum);
	glVertex3f(-groundSize/2.0f, groundHeight, groundSize/2.0f);
	glTexCoord2f(repeatNum, repeatNum);
	glVertex3f(groundSize/2.0f, groundHeight, groundSize/2.0f);
	glTexCoord2f(repeatNum, 0.0);
	glVertex3f(groundSize/2.0f, groundHeight, -groundSize/2.0f);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(-groundSize/2.0f, groundHeight, -groundSize/2.0f);	
	glEnd();
	ground.stopMaterial();
	glPopMatrix();
	
	//Draw sky
	glPushMatrix();
	gluQuadricOrientation(q,GLU_INSIDE);
	glEnable(GL_CULL_FACE);
	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_T);
	sky.setupMaterial();
	gluSphere(q, groundSize, 10, 5);
	sky.stopMaterial();
	glDisable(GL_TEXTURE_GEN_T);
	glDisable(GL_TEXTURE_GEN_S);
	glPopMatrix();
		
	glutSwapBuffers();	
}

void keyboardClick(unsigned char key, int x, int y)
{
	switch (key)
	{
		case 27: case 'q': case'Q':
			exit(EXIT_SUCCESS);
			break;
		case 'l': case 'L':
				blEnableLights= !blEnableLights;
				glutPostRedisplay();
				break;
		case'r': case'R':
					resetScene();
					glutPostRedisplay();
					break;
		case 'f':
					locationX += 0.5;
					glutPostRedisplay();
					break;
		case 'g':
				locationX -= 0.5;
				glutPostRedisplay();
					break;
		case'w':
				avatarPOV.moveForward(0.1f);
				break;
		case's':
				avatarPOV.moveBackward(0.1f);
				break;
		case'a':
				avatarPOV.strafeLeft(0.1f);
				break;
		case'd':
				avatarPOV.strafeRight(0.1f);
				break;
		case'i':
				avatarPOV.moveForward(20.f);
				break;
		case'k':
				avatarPOV.moveBackward(20.f);
				break;
		case'j':
				avatarPOV.turnLeft(0.1f);
				break;
		case'h':
				avatarPOV.turnRight(0.1f);
				break;
		case'\\':
				avatarPOV.lookUp(0.1f);
				break;
		case'/':
				avatarPOV.lookDown(0.1f);
				break;				
	}
}

void specialInput(int key, int x, int y)
{
	switch (key)
	{
		case GLUT_KEY_UP:
				avatarPOV.moveForward(0.1f);
				break;
		caseGLUT_KEY_DOWN:
				avatarPOV.moveBackward(-0.1f);
				break;
		caseGLUT_KEY_RIGHT:
				avatarPOV.strafeLeft();
				break;
		caseGLUT_KEY_LEFT:
				avatarPOV.strafeRight();
				break;
}
		
}

void mouseClick(int button, int state, int x, int y)
{
	mouseX= x;
	mouseY= y;
	
	cout <<"button=" << button <<endl; 
	if (button == GLUT_LEFT_BUTTON)
	{
		if (state == GLUT_DOWN)
			blMouseLeftDown = true;
		else 
			blMouseLeftDown = false;
		}
		if (button == GLUT_MIDDLE_BUTTON)
	{
		if (state == GLUT_DOWN)
			blMouseMiddleDown = true;
		else 
			blMouseMiddleDown = false;
	}
		if (button == GLUT_RIGHT_BUTTON)
		{
		if (state == GLUT_DOWN)
			blMouseRightDown = true;
		else 
			blMouseRightDown = false;
}
}

void mouseMotion(int x, int y)
{
	cout << "x=" << x << "y=" << y <<endl;
	
	if (blMouseLeftDown)
	{	
		if(mouseX > x) avatarPOV.turnRight(0.3f);
		if(mouseX < x) avatarPOV.turnLeft(0.3f);
		if(mouseY < y) avatarPOV.lookUp(0.3f);
		if(mouseY > y) avatarPOV.lookDown(0.3f);
		rotationX += (x-mouseX);
		rotationY -= (y-mouseY);		
	}
	
	if (blMouseRightDown)
	{	
		
		locationX += 10.0 * (x-mouseX) / screenWidth;
		locationY -= 10.0 * (y-mouseY) / screenHeight;		
	}
	mouseX = x;
	mouseY = y;
	glutPostRedisplay();
}

void timer(int milisec)
{
	orbitRotation++;
	if(orbitRotation >=360) orbitRotation = 0;
	glutTimerFunc(milisec, &timer, milisec);	//Redraw every milisec ms
	glutPostRedisplay();
}


