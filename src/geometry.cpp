#ifdef __APPLE__
  #include <GLUT/glut.h>
#elif __linux__
  #include <X11/Xlib.h>
  #include <GL/gl.h>
  #include <GL/glut.h>
  #include <GL/glx.h>
#elif _WIN32
  #include <windows.h>
  #include <GL/glut.h>
#else
  #warning "OS or compiler not supported"
#endif

#include <stdlib.h>
#include <stdio.h>

#include "config.hpp"
#include "geometry.hpp"
#include "toolbox.hpp"

void createCube(fctptr animation, float minx, float maxx, float miny, float maxy, float minz, float maxz){

  animation();

  glBegin(GL_QUADS);

  //Front
  glNormal3f(0,0,1);
  glVertex3f(minx, miny, minz);
  glVertex3f(minx, maxy, minz);
  glVertex3f(maxx, maxy, minz);
  glVertex3f(maxx, miny, minz);

  // Left
  glNormal3f(0,0,1);
  glVertex3f(minx, miny, minz);
  glVertex3f(minx, maxy, minz);
  glVertex3f(minx, maxy, maxz);
  glVertex3f(minx, miny, maxz);

  // Top
  glNormal3f(0,0,1);
  glVertex3f(minx, maxy, minz);
  glVertex3f(maxx, maxy, minz);
  glVertex3f(maxx, maxy, maxz);
  glVertex3f(minx, maxy, maxz);

  // Right
  glNormal3f(0,0,1);
  glVertex3f(maxx, miny, minz);
  glVertex3f(maxx, maxy, minz);
  glVertex3f(maxx, maxy, maxz);
  glVertex3f(maxx, miny, maxz);

  // Bottom
  glNormal3f(0,0,1);
  glVertex3f(minx, miny, minz);
  glVertex3f(maxx, miny, minz);
  glVertex3f(maxx, miny, maxz);
  glVertex3f(minx, miny, maxz);

  //Back
  glNormal3f(0,0,1);
  glVertex3f(minx, miny, maxz);
  glVertex3f(minx, maxy, maxz);
  glVertex3f(maxx, maxy, maxz);
  glVertex3f(maxx, miny, maxz);

  glEnd();
}

void createPyramid(fctptr animation, float minx, float maxx, float miny, float maxy, float minz, float maxz){
  float midx = (maxx + minx)/2;
  float midz = (maxz + minz)/2;

  animation();

  glBegin(GL_TRIANGLE_STRIP);

/*  //glColor3f(1.0f, 1.0f, 0.0f);
  // Front
  glVertex3f(midx, maxy, midz);
  glVertex3f(minx, miny, maxz);
  glVertex3f(maxx, miny, maxz);

  //glColor3f(0.0f, 1.0f, 0.0f);
  // Right
  glVertex3f(midx, maxy, midz);
  glVertex3f(maxx, miny, maxz);
  glVertex3f(maxx, miny, minz);

  //glColor3f(1.0f, 0.0f, 0.0f);
  // Back
  glVertex3f(midx, maxy, midz);
  glVertex3f(maxx, miny, minz);
  glVertex3f(minx, miny, minz);

  //glColor3f(1.0f, 1.0f, 1.0f);
  // Left
  glVertex3f(midx, maxy, midz);
  glVertex3f(minx, miny, minz);
  glVertex3f(minx, miny, maxz);

  //glColor3f(1.0f, 1.0f, 1.0f);
  // Top
  glVertex3f(midx, maxy, midz);
  glVertex3f(midx, maxy, midz);
  glVertex3f(midx, maxy, midz);

*/

glNormal3f(maxx-minx,maxy-miny,maxz-minz);
  glTexCoord2f(midx, maxy);
  glVertex3f( midx, maxy, midz);
  glTexCoord2f(minx, miny);
  glVertex3f( minx, miny, maxz);
  glTexCoord2f(maxx, miny);
  glVertex3f( maxx, miny, maxz);

  glNormal3f(maxx-minx,maxy-miny,maxz-minz);
  glTexCoord2f(midx, maxy);
  glVertex3f( midx, maxy, midz);
  glTexCoord2f(maxx, miny);
  glVertex3f( maxx, miny, maxz);
  glTexCoord2f(maxx, miny);
  glVertex3f( maxx, miny, minz);

  glNormal3f(maxx-minx,maxy-miny,maxz-minz);
  glTexCoord2f(midx, maxy);
  glVertex3f( midx, maxy, midz);
  glTexCoord2f(maxx, miny);
  glVertex3f( maxx, miny, minz);
  glTexCoord2f(minx, miny);
  glVertex3f( minx, miny, minz);

  glNormal3f(maxx-minx,maxy-miny,maxz-minz);
  glTexCoord2f(midx, maxy);
  glVertex3f( midx, maxy, midz);
  glTexCoord2f(minx, miny);
  glVertex3f( minx, miny, minz);
  glTexCoord2f(minx, miny);
  glVertex3f( minx, miny, maxz);

  glEnd();
}

void createAsteroid(fctptr animation) {
    animation();

    glColor3f(1.0,1.0,0.0);
    glutSolidDodecahedron();
}
