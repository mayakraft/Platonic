#include "../platonic.c"
#include "world.h"

char selected_solid = 0;
unsigned short seeThrough = 0;
unsigned short scene = 0;
#define NUM_SCENES 4

//approx
#define CLOCKS_PER_SECOND 60000

static GLfloat light_position1[] = { 5.0, 5.0, 5.0, 0.0 };
static GLfloat light_position2[] = { -5.0, 5.0, -5.0, 0.0 };
static GLfloat light_position3[] = { -5.0, -5.0, 5.0, 0.0 };

// float elapsedTime = 0;

void setup(){
	GRID = 0;
	ZOOM = 3.0;
	POV = POLAR;
	glPointSize(64);
	originZ = -1.0;
	// glLineWidth(5);
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
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHT2);
	// glEnable(GL_LIGHTING);
	glCullFace(GL_FRONT);
	glEnable(GL_CULL_FACE);
	// glShadeModel(GL_FLAT);
	glShadeModel(GL_SMOOTH);
	glEnable( GL_POINT_SMOOTH );
	glLineWidth(5);
	glPointSize(10);
}

void update(){
}

void draw(){
	// glColor3f(1.0, 1.0, 0.5);
	// drawPoint(7,7,7);
	glEnable(GL_LIGHTING);

	switch (scene){
		case 0:
			if(seeThrough == 2)
				drawPlatonicSolidPoints(selected_solid);
			else if(seeThrough == 1)
				drawPlatonicSolidLines(selected_solid);
			else
				drawPlatonicSolidFaces(selected_solid);

			if(keyboard[D_KEY] || keyboard[d_KEY]){
				// D pressed
				float scale = platonic_midradius[selected_solid]/platonic_midradius[ _platonic_dual_index[selected_solid] ];
				glPushMatrix();
					glScalef(scale, scale, scale);
					if(seeThrough == 2)
						drawPlatonicSolidPoints(_platonic_dual_index[selected_solid]);
					else if(seeThrough == 1)
						drawPlatonicSolidLines(_platonic_dual_index[selected_solid]);
					else
						drawPlatonicSolidFaces(_platonic_dual_index[selected_solid]);
				glPopMatrix();
			}
		break;

		case 1:
			drawPlatonicSolidFaces(selected_solid);
			float elapsed = (float)clock() / (float)CLOCKS_PER_SECOND * 3;
			float upperBounds = platonic_midradius[selected_solid] / platonic_midradius[ _platonic_dual_index[selected_solid] ];
			float lowerBounds = platonic_inradius[ _platonic_dual_index[selected_solid] ];
			float scale = lowerBounds + ( upperBounds - lowerBounds ) * (sin(elapsed)*.5 + .5);
			glPushMatrix();
				glScalef(scale, scale, scale);
				drawPlatonicSolidFaces( _platonic_dual_index[selected_solid] );
			glPopMatrix();

		break;
		case 2:
			drawPlatonicSolidFaces(selected_solid);
			float rotation1 = (float)clock() / (float)CLOCKS_PER_SECOND * 40;
			glPushMatrix();
				glRotatef(rotation1, 0, 0, 1);
				float edgeScale = 1.0 / platonic_midradius[ _platonic_dual_index[selected_solid] ];
				glScalef(edgeScale, edgeScale, edgeScale);
				drawPlatonicSolidLines( _platonic_dual_index[selected_solid] );
			glPopMatrix();

		break;
		case 3:
			drawPlatonicSolidFaces(selected_solid);
			float rotation2;
			if(selected_solid == 0 || selected_solid == 5)
				rotation2 = 0;
			else if(selected_solid == 4 || selected_solid == 3)
				rotation2 = DODECAHEDRON_DIHEDRAL_ANGLE;
			else
				rotation2 = 45;
			glPushMatrix();
				glRotatef(rotation2, 0, 0, 1);
				float scale1 = 1.0 / platonic_midradius[ _platonic_dual_index[selected_solid] ];
				glScalef(scale1, scale1, scale1);
				drawPlatonicSolidLines( _platonic_dual_index[selected_solid] );
				glPushMatrix();
					glRotatef(rotation2, 0, 0, 1);
					float scale2 = 1.0 / platonic_midradius[ selected_solid ];
					glScalef(scale2, scale2, scale2);
					drawPlatonicSolidLines( selected_solid );
					glPushMatrix();
						glRotatef(rotation2, 0, 0, 1);
						float scale3 = 1.0 / platonic_midradius[ _platonic_dual_index[selected_solid] ];
						glScalef(scale3, scale3, scale3);
						drawPlatonicSolidLines( _platonic_dual_index[selected_solid] );
					glPopMatrix();
				glPopMatrix();
			glPopMatrix();

		break;
		default:

		break;
	}

	glDisable(GL_LIGHTING);
}

void keyDown(unsigned int key) {
	if(key == '1') selected_solid = 0;
	else if(key == '2') selected_solid = 1;
	else if(key == '3') selected_solid = 2;
	else if(key == '4') selected_solid = 3;
	else if(key == '5') selected_solid = 4;
	else if(key == '0') selected_solid = -1;
	else if(key == ' ') { // SPACE BAR
		seeThrough = (seeThrough+1)%3;
	}
	else if(key == RETURN_KEY){
		scene = (scene+1)%NUM_SCENES;
	}

}
void keyUp(unsigned int key) { }
void mouseDown(unsigned int button) { }
void mouseUp(unsigned int button) { }
void mouseMoved(int x, int y) { }
