#ifndef CONFIG_HPP_INCLUDED
#define CONFIG_HPP_INCLUDED

enum {FRONT, BACK, TOP, BOTTOM, LEFT, RIGHT};

enum class Warning{
    TOP,
    BOT,
    LEFT,
    RIGHT,
    START,
    STOP
};

#define M_PI           3.14159265358979323846
#define GUI_CYAN_R 0.46
#define GUI_CYAN_G 1.0
#define GUI_CYAN_B 0.94

#define GUI_RED_R 0.93
#define GUI_RED_G 0.26
#define GUI_RED_B 0.29

#define FPS 60
#define FRAME_DELAY 1000/FPS

// Define function pointer macro
typedef void (*fctptr)();

#endif // CONFIG_HPP_INCLUDED
