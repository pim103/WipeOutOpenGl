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
#include <time.h>
#include <math.h>

#include "config.hpp"
#include "Ship.hpp"
#include "glut_tools.hpp"
#include "geometry.hpp"
#include "toolbox.hpp"

float _tmpGlobal1 = 0.0;

float angle = 0.0;
float angleL2 = 0.0;

GLdouble angleX = 0.0;
GLdouble angleY = 0.0;
GLdouble angleZ = 0.0;

int xLastMouse = 0;
int yLastMouse = 0;

int pressButton = 0;

bool _doRotate = false;
bool _doRoll = false;
bool _doLooping = false;
bool _doImmelmann = false;
bool _doLateral = false;

float translateX = 0;
float translateY = 0;
float maxAngle = 45;

int _keyPressed = 0;
extern int screenH;
extern int screenW;

/* Initialisation d'OpenGL pour le rendu de la scne */
void initRendering() {
  Ship *ship = Ship::getInstance();

        /* Active le z-buffer */
        glEnable(GL_BLEND);
        glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_TEXTURE_2D);
        /* Activation des couleurs */
        glEnable(GL_COLOR_MATERIAL);

        /* dfinit la couleur d'effacement et la couleur de fond */
        glClearColor(0.0, 0.0, 0.0, 0.0);

        /* Activation des lumires */
        glEnable(GL_LIGHTING);          // Activation du mode
        glEnable(GL_LIGHT0);            // Activation lumire n0
        // glEnable(GL_LIGHT1);            // Activation lumire n1
        // glEnable(GL_LIGHT2);            // Activation lumire n2

        /* Les normales (cres par glNormal(*)) sont automatiquement unitaires */
        glEnable(GL_NORMALIZE);

        /* Activation du mode ombrage (shading) et lissage (smooth) des couleur */
        glShadeModel(GL_SMOOTH);

        /*  dfinit la taille d'un pixel*/
        glPointSize(2.0);

        ship->loadTexture();
}

/* Cration de la scne avec lampes */
void display(void){
        /*
        GUI *gui = GUI::getInstance();
        Game *game = Game::getInstance();
        // Skybox *skybox = Skybox::getInstance();
        Screen *pauseScreen = game->getPauseScreen();

        Camera *camera = Camera::getInstance();
        Ship *ship = Ship::getInstance();
        static float moveZ = 0;

        // GLfloat no_mat[] = {0.0, 0.0, 0.0, 1.0};
        // GLfloat mat_ambient_color[] = {0.8, 0.8, 0.2, 1.0};
        // GLfloat mat_specular[] = {1.0, 1.0, 1.0, 1.0};
        // GLfloat no_shininess[] = {0.0};
        // GLfloat low_shininess[] = {5.0};
        // GLfloat high_shininess[] = {100.0};

        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

        glMatrixMode(GL_MODELVIEW);
        // glMatrixMode(GL_PROJECTION);

        glLoadIdentity();

        camera->lookAt();

        if (game->getPauseState()) {
            glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

            gui->update();
            pauseScreen->draw();
            glutSwapBuffers();*/
            /* On force l'affichage */
            /*
            glFlush();
            handleKeyboard();
            return;
        }

        GLfloat ambientColor[] = {1, 1, 1, 1.0f}; // Default
        glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientColor);

        // GLfloat mat_ambient[] = {0.1,0.1,0.1,1};
        // GLfloat mat_diffuse[] = {1,1,1,1};

        GLfloat mat_emission[] = {0.5, 0.5, 0.5, 1};
        GLfloat mat_specular[] = {1,1,1,1};

        // Key light
        GLfloat lightColor0[] = {1,1,1, 1};
        GLfloat lightPos0[] = {4,4,0,1};

        Light *light0 = new Light(GL_LIGHT0, GL_SPECULAR, lightColor0, lightPos0);

        // light0->setMaterial(GL_FRONT, GL_DIFFUSE, mat_diffuse);
        light0->setMaterial(GL_FRONT, GL_SPECULAR, mat_specular);
        light0->setMaterial(GL_FRONT, GL_EMISSION, mat_emission);
        // light0->setMaterial(GL_FRONT, GL_AMBIENT, mat_ambient);
        // light0->display();

        // Fill light
        GLfloat lightColor1[] = {0,0,0, 0.5};
        GLfloat lightPos1[] = {-4,4,0, 1};

        Light *light1 = new Light(GL_LIGHT1, GL_SPECULAR, lightColor1, lightPos1);

        light1->setMaterial(GL_FRONT, GL_EMISSION, mat_emission);
        // light1->setMaterial(GL_FRONT, GL_SPECULAR, mat_specular);
        // light1->display();

        GLfloat lightColor2[] = {0.7,0.5,0, 0.5};
        GLfloat lightPos2[] = {0,3,-6, 1};

        // Back light
        Light *light2 = new Light(GL_LIGHT2, GL_SPECULAR, lightColor2, lightPos2);

        light2->setMaterial(GL_FRONT, GL_EMISSION, mat_emission);
        light2->setMaterial(GL_BACK, GL_SPECULAR, mat_specular);
        // light2->setMaterial(GL_FRONT, GL_SPECULAR, mat_specular);
        // light2->display();

        // // Ajout lumire positionnelle L1
        // glLightfv(GL_LIGHT1, GL_DIFFUSE, lightColor1);
        // // glLightfv(GL_LIGHT1, GL_SPECULAR, lightColor1); // lumire spculaire
        // glLightfv(GL_LIGHT1, GL_POSITION, lightPos1);
        // glPushMatrix();
        //     glRotatef(angleL2, 0.0f, 0.0f, 1.0f);
        //     glLightfv(GL_LIGHT2, GL_DIFFUSE, lightColor2);
        //     glLightfv(GL_LIGHT2, GL_POSITION, lightPos2);
        //     glLightf(GL_LIGHT2, GL_LINEAR_ATTENUATION, 0.5);
        // glPopMatrix();
    moveZ += ship->getSpeedZ();
    if(moveZ > 5) moveZ = 0;
    glPushMatrix();
        glTranslatef(0, 0, moveZ);
        for(float i = -1000; i <= 1000; i += 5)
      	{
          // glBegin(GL_LINES);
      		glBegin(GL_QUADS);
      			glColor3ub(47, 45, 95);
      			glVertex3f(-1000, -45, i);
      			glVertex3f(1000, -45, i);
      			glVertex3f(i, -45,-1000);
      			glVertex3f(i, -45, 1000);
      		glEnd();
      	}

        // glBegin(GL_QUADS);
        //   glColor3ub(47, 45, 95);
        //   glVertex3f(-500, -25, 500);
        //   glVertex3f(500, -25, 500);
        //   glVertex3f(500, -25,-500);
        //   glVertex3f(500, -25, 500);
        //   glEnd();


        for(float i = -1000; i <= 1000; i += 5)
      	{
          glBegin(GL_LINES);
      		// glBegin(GL_QUADS);
      			glColor3ub(212, 0, 241);
      			glVertex3f(-1000, -40, i);
      			glVertex3f(1000, -40, i);
      			glVertex3f(i, -40,-1000);
      			glVertex3f(i, -40, 1000);
      		glEnd();
      	}
    glPopMatrix();
        gui->update();
        // skybox->draw(0,0,0,100,100,100);
        glPushMatrix();
            // Camera angles
            glRotatef(angleY, -1, 0, 0);
            glRotatef(angleX, 0, -1, 0);
            glRotatef(angleZ, 0, 0, 1);

            ship->display();
        glPopMatrix();
    ship->checkIntegrity();
    glPopMatrix();
*/
    /* Dessin de la scène */
    /*
    glPushMatrix();
        glTranslatef(scene.translateX, scene.translateY, 0);
        scene.drawAsteroid();
    glPopMatrix();

        glutSwapBuffers();
        glFlush();

        if (!game->getIsPresenting()) {
          handleKeyboard();
        }
    */
}

/* Fonction de mise  jour: mouvements des objets*/
void update(int value)
{
  Game *game = Game::getInstance();
  Camera *camera = Camera::getInstance();
  Ship *ship = Ship::getInstance();
    camera->update();

    //if(angleX != 0) scene.translateX -= (angleX/maxAngle) * ship.getSpeedX();// + (angleZ/angleY)*0.05;
    //if(angleY != 0) scene.translateY += (angleY/maxAngle) * ship.getSpeedY();// + (angleZ/angleX)*0.05;
    if (!game->getPauseState()) {
      if(angleX != 0) scene.translateX -= (angleX/maxAngle) * ship->getSpeedX();
      if(angleY != 0) scene.translateY += (angleY/maxAngle) * ship->getSpeedY();

      scene.onTheScene();

      scene.timer = clock();

      if(scene.timer > scene.maxTimer)
      {
          scene.maxTimer = clock() + (scene.upgradeLevel * CLOCKS_PER_SEC);
          scene.level++;
      }

      scene.updateAsteroid();

      angleL2 >= 360 ? angleL2 -= 360 : angleL2 += 0.2;
    }

    glutPostRedisplay();
    glutTimerFunc(10,update, 0);
}

/*  Mise en forme de la scne pour l'affichage */
void reshape(int w, int h)
{
    glViewport(0, 0,(GLsizei) w, (GLsizei) h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(60.0, (GLfloat) w / (GLfloat) h, 1.0,  200.0);
}

void keyboardUp(unsigned char key, int x, int y) {
  Ship *ship = Ship::getInstance();
  Game *game = Game::getInstance();
  _keyPressed = 0;

  switch (key) {
    case 27:
      if (!game->getIsPresenting()) {
        game->togglePause();
      }
      break;

    case 'z':
    case 's':
      ship->setThrottle(IDLE);
      ship->animWings(IDLE);
      break;

    case 't':
      ship->animWings(IDLE);
      break;
  }
}

/* Fonction de gestion au clavier des activations des lumires */
void keyboard(unsigned char key, int x, int y)
{
    _keyPressed = key;
}

void handleKeyboard() {
  Camera *camera = Camera::getInstance();
  Ship *ship = Ship::getInstance();
  float beta = camera->getBeta();
  float alpha = camera->getAlpha();

  if(camera->view == CENTRAL_VIEW)
  {

      switch(_keyPressed)
      {
      case 'b': // Triggers barrel roll
          // This switch is deactivated autonomously after the angle has reached 360 in barrelRoll() found un Ship.cpp
          _doRoll = true;
          break;

      case 't':
          ship->animWings(SLOW);
          break;

      case 'a':
        _tmpGlobal1 += 0.01;
        printf(">> %f\n", _tmpGlobal1);
        break;

      case 'e':
        _tmpGlobal1 -= 0.01;
        printf(">> %f\n", _tmpGlobal1);
        break;

      case 'r': // Toggle rotation
          (_doRotate)?_doRotate = false:_doRotate = true;
          break;

      case 'l': // Triggers looping
          // This switch is deactivated autonomously
          _doLooping = true;
          break;

      case 'i': // Triggers Immelmann
          // This switch is deactivated autonomously
          _doImmelmann = true;
          break;

      case 'L': // Triggers lateral looping
          // This switch is deactivated autonomously
          _doLateral = true;
          break;

      case 'z':
          ship->setThrottle(FAST);
          ship->animWings(FAST);
          break;

      case 's':
          ship->setThrottle(SLOW);
          ship->animWings(SLOW);
          break;

      case 'q':
          angleZ > 360 ? angleZ = 0.0 : angleZ += 5;
          break;
      case 'd':
          angleZ < 0.0 ? angleZ = 360 : angleZ -= 5;
          break;
      }
  }
  else if(camera->view == FREE_VIEW)
  {
      switch(_keyPressed)
      {
          case 'z':
              camera->unaryEye(Y, INC);
              break;
          case 'q':
              camera->unaryEye(X, INC);
              break;
          case 's':
              camera->unaryEye(Y, DEC);
              break;
          case 'd':
              camera->unaryEye(X, DEC);
              break;

          case 'o':
              if(beta < 44) beta += 0.025;
              break;
          case 'k':
              if(alpha < 44) alpha += 0.025;
              break;
          case 'l':
              if(beta > -44) beta -= 0.025;
              break;
          case 'm':
              if(alpha > -44) alpha -= 0.025;
              break;
      }
  }

  switch(_keyPressed)
  {
      case 'v':
          if(camera->view == FREE_VIEW) camera->view = CENTRAL_VIEW;
          else camera->view = FREE_VIEW;
          break;

      case 'n':
          exit(0);
          break;
  }
}

void setRandPos(float minx, float maxx, float miny, float maxy, float minz, float maxz) {
      srand(time(NULL));

      float rngx = (rand()%int(maxx)) + minx;
      float rngy = (rand()%int(maxy)) + miny;
      float rngz = (rand()%int(maxz)) + minz;

      glTranslatef(rngx, rngy, rngz);
}

void specialInput(int key, int x, int y)
{
  Camera *camera = Camera::getInstance();
  float beta = camera->getBeta();
  float alpha = camera->getAlpha();

    if(camera->view == CENTRAL_VIEW)
    {
        switch(key)
        {
            case GLUT_KEY_UP:
                if(beta < 44) beta += 0.05;
                break;
            case GLUT_KEY_DOWN:
                if(beta > -44) beta -= 0.05;
                break;
            case GLUT_KEY_RIGHT:
                if(alpha > -44) alpha += 0.05;
                break;
            case GLUT_KEY_LEFT:
                if(alpha < 44) alpha -= 0.05;
                break;
            case GLUT_KEY_PAGE_UP:
                alpha = beta = 0;
                break;
        }
    }
    else if(camera->view == FREE_VIEW)
    {
        switch(key)
        {
            case GLUT_KEY_UP:
                camera->unaryEye(Z, DEC);
                break;
            case GLUT_KEY_DOWN:
                camera->unaryEye(Z, INC);
                break;
        }
    }
}

void mouseFunction(int button, int state, int x, int y)
{
    if(state == GLUT_LEFT_BUTTON)
    {
        pressButton = 1;
    }
}

void mouseMove(int x, int y)
{
    Ship *ship = Ship::getInstance();
    if (ship->isLocked()) {
      return;
    }

    x -= screenW/2;
    y -= screenH/2;

    if(abs(x) > screenW/2) x < 0 ? x = -screenW/2 : x = screenW/2;
    if(abs(y) > screenH/2) y < 0 ? y = -screenH/2 : y = screenH/2;

    angleX = ((float)x / (float)(screenW/2)) * maxAngle;
    angleY = ((float)y / (float)(screenH/2)) * maxAngle;

    xLastMouse = x;
    yLastMouse = y;
}

void drawAxes(){
    float ORG[3] = {0,0,0};

    float XP[3] = {1,0,0};
    float YP[3] = {0,1,0};
    float ZP[3] = {0,0,1};
    glPushMatrix ();

    glTranslatef (-5.0, -5.0, -5.0);
    glRotatef(angleY, -1, 0, 0);
    glRotatef(angleX, 0, -1, 0);
    glScalef (1.0, 1.0, 1.0);

    glLineWidth (2.0);

    glBegin (GL_LINES);
    glColor3f (1,0,0); // X axis is red.
    glVertex3fv (ORG);
    glVertex3fv (XP);
    glColor3f (0,1,0); // Y axis is green.
    glVertex3fv (ORG);
    glVertex3fv (YP);
    glColor3f (0,0,1); // z axis is blue.
    glVertex3fv (ORG);
    glVertex3fv (ZP);
    glEnd();

    glPopMatrix ();
}
