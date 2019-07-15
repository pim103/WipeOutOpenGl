#ifndef GLUT_TOOLS_HPP_INCLUDED
#define GLUT_TOOLS_HPP_INCLUDED

enum{NONE, THROTTLE_UP, THROTTLE_DOWN, ROLL_LEFT, ROLL_RIGHT};

void initRendering();
void display(void);
void update(int value);
void reshape(int w, int h);
void keyboard(unsigned char key, int x, int y);
void keyboardUp(unsigned char key, int x, int y);
void handleKeyboard();
void empty();
void specialInput(int key, int x, int y);
void mouseFunction(int button, int state, int x, int y);
void mouseMove(int x, int y);
void drawAxes();
void handleThrottle();

void drawGUI();
void drawThrottleIndicator();

#endif // GLUT_TOOLS_HPP_INCLUDED
