#include "inputs.h"

int lastPress_joy = LOW;
int lastPress_1 = LOW;
int lastPress_2 = LOW;

int getJoystickHoriz() {
	int pos_x = analogRead(JOY_HORIZ) - JOY_CENTRE;

	if (abs(pos_x) > JOY_DEADZONE) {
		return -pos_x;
	}
	else {
		return 0;
	}
}

int getJoystickVert() {
	int pos_y = analogRead(JOY_VERT) - JOY_CENTRE;

	if (abs(pos_y) > JOY_DEADZONE) {
		return pos_y;
	}
	else {
		return 0;
	}
}

bool getButtonPress(int button, bool click) {
	if (!click) {
		return !digitalRead(button);
	}
	else {
		int* lastPress;
		int currentPress;

		switch (button) {
			case BUTTON_1:
				lastPress = &lastPress_1;
				break;
			case BUTTON_2:
				lastPress = &lastPress_2;
				break;
			case JOY_SEL:
				lastPress = &lastPress_joy;
				break;
		}

		currentPress = digitalRead(button);

		if (currentPress != *lastPress && currentPress == LOW) {
			*lastPress = currentPress;
			return true;
		}
		else {
			*lastPress = currentPress;
			return false;
		}
	}
}
