#ifndef __INPUTS_H__
#define __INPUTS_H__

#include <Arduino.h>

#define JOY_HORIZ A0
#define JOY_VERT  A1
#define JOY_SEL   2
#define JOY_DEADZONE  24
#define JOY_CENTRE 512

#define BUTTON_1 13
#define BUTTON_2 12

int getJoystickHoriz();
int getJoystickVert();
bool getButtonPress(int button, bool click);

#endif
