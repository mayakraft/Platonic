#include "platonic.h"

#ifdef __APPLE__
#  include <OpenGL/gl.h>
#  include <OpenGL/glu.h>
#  include <GLUT/glut.h>
#else
#  include <GL/gl.h>
#  include <GL/glu.h>
#  include <GL/glut.h>
#endif

////////////////////////////////////////////////////////
//    OpenGL ES convenience functions for platonic.h
//              rendering points, lines, faces

// index convention for now:
//   0: tetrahedron
//   1: octahedron
//   2: hexahedron
//   3: icosahedron
//   4: dodecahedron
//   5: tetrahedron dual  <- special case

unsigned int _poly_num_vertices[6] = {TETRAHEDRON_POINTS, OCTAHEDRON_POINTS, HEXAHEDRON_POINTS, ICOSAHEDRON_POINTS, DODECAHEDRON_POINTS, TETRAHEDRON_POINTS};
unsigned int _poly_num_lines[6] = {TETRAHEDRON_LINES, OCTAHEDRON_LINES, HEXAHEDRON_LINES, ICOSAHEDRON_LINES, DODECAHEDRON_LINES, TETRAHEDRON_LINES};
unsigned int _poly_num_faces[6] = {TETRAHEDRON_FACES, OCTAHEDRON_FACES, HEXAHEDRON_TRIANGLE_FACES, ICOSAHEDRON_FACES, DODECAHEDRON_TRIANGLE_FACES, TETRAHEDRON_FACES};

const float* _poly_point_arrays[6] = {_tetrahedron_points, _octahedron_points, _hexahedron_points, _icosahedron_points, _dodecahedron_points, _tetrahedron_dual_points};
const unsigned short* _poly_line_array[6] = {_tetrahedron_lines, _octahedron_lines, _hexahedron_lines, _icosahedron_lines, _dodecahedron_lines, _tetrahedron_dual_lines};
const unsigned short* _poly_face_array[6] = {_tetrahedron_faces, _octahedron_faces, _hexahedron_triangle_faces, _icosahedron_faces, _dodecahedron_triangle_faces, _tetrahedron_dual_faces};

// float midradius[6] = {0.5, 0.5, 0.5, 0.5, 0.5, 0.5};
float midradius[6] = {
	TETRAHEDRON_MIDRADIUS ,
	OCTAHEDRON_MIDRADIUS  ,
	HEXAHEDRON_MIDRADIUS  ,
	ICOSAHEDRON_MIDRADIUS ,
	DODECAHEDRON_MIDRADIUS,
	TETRAHEDRON_MIDRADIUS
};
void drawPlatonicSolidFaces(char solidType){
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, _poly_point_arrays[solidType]);
	glNormalPointer(GL_FLOAT, 0, _poly_point_arrays[solidType]);
	glDrawElements(GL_TRIANGLES, 3*_poly_num_faces[solidType], GL_UNSIGNED_SHORT, _poly_face_array[solidType]);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
}
void drawPlatonicSolidLines(char solidType){
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, _poly_point_arrays[solidType]);
	glNormalPointer(GL_FLOAT, 0, _poly_point_arrays[solidType]);
	glDrawElements(GL_LINES, 2*_poly_num_lines[solidType], GL_UNSIGNED_SHORT, _poly_line_array[solidType]);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
}
void drawPlatonicSolidPoints(char solidType){
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, _poly_point_arrays[solidType]);
	glNormalPointer(GL_FLOAT, 0, _poly_point_arrays[solidType]);
	glDrawArrays(GL_POINTS, 0, _poly_num_vertices[solidType]);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
}