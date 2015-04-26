#ifdef __APPLE__
#  include <OpenGL/gl.h>
#  include <OpenGL/glu.h>
#  include <GLUT/glut.h>
#else
#  include <GL/gl.h>
#  include <GL/glu.h>
#  include <GL/glut.h>
#endif

#include <stdlib.h>
#include <math.h>

#include "platonic.h"


////////////////////////////////////////////////////////
//       OpenGL ES draw functions for platonic.h
//
void drawPlatonicSolidFaces(unsigned short solidType){
	const float *vertices;
	const unsigned short *faces;
	unsigned int numFaces;
	if(solidType == 0){
		vertices = _tetrahedron_points;
		numFaces = TETRAHEDRON_FACES;
		faces = _tetrahedron_faces;
	}
	else if(solidType == 1){
		vertices = _octahedron_points;
		numFaces = OCTAHEDRON_FACES;
		faces = _octahedron_faces;
	}
	else if(solidType == 2){
		vertices = _hexahedron_points;
		numFaces = HEXAHEDRON_TRIANGLE_FACES;
		faces = _hexahedron_triangle_faces;
	}
	else if(solidType == 3){
		vertices = _icosahedron_points;
		numFaces = ICOSAHEDRON_FACES;
		faces = _icosahedron_faces;
	}
	else if(solidType == 4){
		vertices = _dodecahedron_points;
		numFaces = DODECAHEDRON_TRIANGLE_FACES;
		faces = _dodecahedron_triangle_faces;
	}
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, vertices);
	glNormalPointer(GL_FLOAT, 0, vertices);
	glDrawElements(GL_TRIANGLES, 3*numFaces, GL_UNSIGNED_SHORT, faces);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
}
void drawPlatonicSolidLines(unsigned short solidType){
	const float *vertices;
	const unsigned short *lines;
	unsigned int numLines;
	if(solidType == 0){
		vertices = _tetrahedron_points;
		numLines = TETRAHEDRON_LINES;
		lines = _tetrahedron_lines;
	}
	else if(solidType == 1){
		vertices = _octahedron_points;
		numLines = OCTAHEDRON_LINES;
		lines = _octahedron_lines;
	}
	else if(solidType == 2){
		vertices = _hexahedron_points;
		numLines = HEXAHEDRON_LINES;
		lines = _hexahedron_lines;
	}
	else if(solidType == 3){
		vertices = _icosahedron_points;
		numLines = ICOSAHEDRON_LINES;
		lines = _icosahedron_lines;
	}
	else if(solidType == 4){
		vertices = _dodecahedron_points;
		numLines = DODECAHEDRON_LINES;
		lines = _dodecahedron_lines;
	}
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, vertices);
	glNormalPointer(GL_FLOAT, 0, vertices);
	glDrawElements(GL_LINES, 2*numLines, GL_UNSIGNED_SHORT, lines);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
}
////////////////////////////////////////////////////////
////////////////////////////////////////////////////////



// CHOOSE YOUR OWN PERSPECTIVE
//
// 0: first person perspective, X Y movement
// 1: polar, focus on origin, Y radius
// 2: orthographic from above, X Y panning
static int PERSPECTIVE = 1;
// size of window in OS
static int windowWidth = 800;
static int windowHeight = 400;
// INPUT HANDLING
static unsigned int UP_PRESSED = 0;    // KEY UP:0   KEY DOWN:1
static unsigned int DOWN_PRESSED = 0;
static unsigned int RIGHT_PRESSED = 0;
static unsigned int LEFT_PRESSED = 0;
static int mouseDragOffsetX = 0;  // how far mouse is dragged during one session (between click and release)
static int mouseDragOffsetY = 0;
static int mouseTotalOffsetX = 0;  // how far mouse has been dragged since program began
static int mouseTotalOffsetY = 0;
// helpers
static int mouseDragStartX = 0;
static int mouseDragStartY = 0;
static int mouseTotalOffsetStartX = 0;
static int mouseTotalOffsetStartY = 0;

// POLAR PERSPECTIVE
static float cameraRadius = 3.0f;
// ORTHOGRAPHIC
static float panX = 0.0f;
static float panY = 0.0f;
// LIGHTING
static GLfloat light_position1[] = { 5.0, 5.0, 5.0, 0.0 };
static GLfloat light_position2[] = { -5.0, 5.0, -5.0, 0.0 };
static GLfloat light_position3[] = { -5.0, -5.0, 5.0, 0.0 };

#define STEP .10f  // WALKING SPEED. @60fps, walk speed = 6 units/second

unsigned short selected_solid = 0;
unsigned short seeThrough = 0;


void init(){
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glDepthMask(GL_TRUE);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	GLfloat mat_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat mat_shininess[] = { 5.0f };
	GLfloat red[] = {1.0f, 0.0f, 0.0f, 1.0f};
	GLfloat green[] = {0.0f, 1.0f, 0.0f, 1.0f};
	GLfloat blue[] = {0.0f, 0.0f, 1.0f, 1.0f};
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_specular);
	// glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, red);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, blue);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, green);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position1);
	glLightfv(GL_LIGHT1, GL_POSITION, light_position2);
	glLightfv(GL_LIGHT2, GL_POSITION, light_position3);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHT2);
	glCullFace(GL_FRONT);
	glEnable(GL_CULL_FACE);
	glShadeModel(GL_FLAT);
	glShadeModel (GL_SMOOTH);
	glLineWidth(5);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
}

void reshape(int w, int h){
	windowWidth = w;
	windowHeight = h;
	float a = (float)windowWidth / windowHeight;
	glViewport(0,0,(GLsizei) w, (GLsizei) h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if(PERSPECTIVE == 1)
		glFrustum (-.1, .1, -.1/a, .1/a, .1, 100.0);
	else if (PERSPECTIVE == 2)
		glOrtho(-3.0f, 3.0f, 
				-3.0f/a, 3.0f/a, 
				-100.0, 100.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

// draws a XY 1x1 square in the Z = 0 plane
void unitSquare(float x, float y, float width, float height){
	static const GLfloat _unit_square_vertex[] = { -0.5f, 0.5f, 0.0f,     0.5f, 0.5f, 0.0f,    -0.5f, -0.5f, 0.0f,    0.5f, -0.5f, 0.0f };
	static const GLfloat _unit_square_normals[] = { 0.0f, 0.0f, 1.0f,     0.0f, 0.0f, 1.0f,     0.0f, 0.0f, 1.0f,     0.0f, 0.0f, 1.0f  };
	glPushMatrix();
	glTranslatef(x, y, 0.0);
	glScalef(width, height, 1.0);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, _unit_square_vertex);
	glNormalPointer(GL_FLOAT, 0, _unit_square_normals);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
	glPopMatrix();
}

void display(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	glPushMatrix();
		// apply perspective inside this matrix
		if(PERSPECTIVE == 1){
			glTranslatef(0, 0, -cameraRadius);
			glRotatef(mouseTotalOffsetY, -1, 0, 0);
			glRotatef(mouseTotalOffsetX, 0, 0, -1);
		}
		if(PERSPECTIVE == 2){
			glTranslatef(-mouseTotalOffsetX * .05 /20.0*3.0 - panX*2, mouseTotalOffsetY * .05 /20.0*3.0 - panY*2, 0.0f);
		}

		// perspective has been established
		// draw stuff below

		glDisable(GL_LIGHTING);
		
		glPushMatrix();
			glTranslatef(0.0f, 0.0f, -1.0f);
			int XOffset = 0;
			int ZOffset = 0;
			for(int i = -8; i <= 8; i++){
				for(int j = -8; j <= 8; j++){
					int b = abs(((i+j+XOffset+ZOffset)%2));
					if(b) glColor3f(0.0, 0.0, 0.0);
					else glColor3f(1.0, 1.0, 1.0);
					unitSquare(i-XOffset, j-ZOffset, 1, 1);
				}
			}
		glPopMatrix();

		glEnable(GL_LIGHTING);

		glPushMatrix();
			if(seeThrough)
				drawPlatonicSolidLines(selected_solid);
			else
				drawPlatonicSolidFaces(selected_solid);
		glPopMatrix();


	glPopMatrix();
	// bring back buffer to the front on vertical refresh, auto-calls glFlush
	glutSwapBuffers();
	// glFlush();
}

// process input devices if in orthographic mode
void updateOrthographic(){
	if(UP_PRESSED)
		panY -= STEP;
	if(DOWN_PRESSED)
		panY += STEP;
	if(LEFT_PRESSED)
		panX -= STEP;
	if(RIGHT_PRESSED)
		panX += STEP;
	// reshape(windowWidth, windowHeight);
	glutPostRedisplay();
}

// process input devices if in polar perspective mode
void updatePolar(){
	if(UP_PRESSED)
		cameraRadius -= STEP;
	if(DOWN_PRESSED)
		cameraRadius += STEP;
	if(cameraRadius < 0) 
		cameraRadius = 0;
	glutPostRedisplay();
}

// when mouse button state changes
void mouseButtons(int button, int state, int x, int y){
	if(button == GLUT_LEFT_BUTTON){
		if(!state){  // button down
			mouseDragStartX = x;
			mouseDragStartY = y;
			mouseTotalOffsetStartX = mouseTotalOffsetX;
			mouseTotalOffsetStartY = mouseTotalOffsetY;
		}
		else { }    // button up
	}
	// else if(button == GLUT_MIDDLE_BUTTON){}
	// else if(button == GLUT_RIGHT_BUTTON){}
}

// when mouse is dragging screen
void mouseMotion(int x, int y){
	mouseDragOffsetX = mouseDragStartX - x;
	mouseDragOffsetY = mouseDragStartY - y;
	mouseTotalOffsetX = mouseTotalOffsetStartX + mouseDragOffsetX;
	mouseTotalOffsetY = mouseTotalOffsetStartY + mouseDragOffsetY;
	glutPostRedisplay();
}

void keyboardDown(unsigned char key, int x, int y){
	if(key == 27)  // ESCAPE key
		exit (0);
	// W A S D
	else if(key == 119) // W
		UP_PRESSED = 1;
	else if(key == 115) // S
		DOWN_PRESSED = 1;
	else if(key == 97) // A
		RIGHT_PRESSED = 1;
	else if(key == 100)  // D
		LEFT_PRESSED = 1;
	else if(key == ' '){  // SPACE BAR
		seeThrough = !seeThrough;
	}
	else if(key == '1') selected_solid = 0;
	else if(key == '2') selected_solid = 1;
	else if(key == '3') selected_solid = 2;
	else if(key == '4') selected_solid = 3;
	else if(key == '5') selected_solid = 4;
	else if(key == 'p'){
		PERSPECTIVE = 1;
		// mouseTotalOffsetX = mouseTotalOffsetY = 0;
		reshape(windowWidth, windowHeight);
		glutPostRedisplay();
	}
	else if(key == 'o'){
		PERSPECTIVE = 2;
		mouseTotalOffsetX = mouseTotalOffsetY = 0;
		reshape(windowWidth, windowHeight);
		glutPostRedisplay();	
	}
	
	// anything that affects the screen and requires a redisplay
	// put it in this if statement
	// if(UP_PRESSED || DOWN_PRESSED || RIGHT_PRESSED || LEFT_PRESSED){
		if(PERSPECTIVE == 1)
			glutIdleFunc(updatePolar);
		if(PERSPECTIVE == 2)
			glutIdleFunc(updateOrthographic);
	// }
}

void keyboardUp(unsigned char key,int x,int y){
	if(key == 119) // W
		UP_PRESSED = 0;
	else if(key == 115) // S
		DOWN_PRESSED = 0;
	else if(key == 97) // A
		RIGHT_PRESSED = 0;
	else if(key == 100) // D
		LEFT_PRESSED = 0;
	
	if(!(UP_PRESSED || DOWN_PRESSED || RIGHT_PRESSED || LEFT_PRESSED))
		glutIdleFunc(NULL);
}

int main(int argc, char **argv){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowPosition(10,10);
	glutInitWindowSize(windowWidth,windowHeight);
	glutCreateWindow(argv[0]);
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMouseFunc(mouseButtons);
	glutMotionFunc(mouseMotion);
	glutKeyboardUpFunc(keyboardUp); 
	glutKeyboardFunc(keyboardDown);
	glutPostRedisplay();
	glutMainLoop();
	return 0;
}