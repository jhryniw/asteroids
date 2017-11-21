#include <Arduino.h>
#include <Adafruit_ILI9341.h>

#include "Asteroid.h"
#include "Spaceship.h"

#define TFT_DC 9
#define TFT_CS 10
#define TFT_WIDTH 320
#define TFT_HEIGHT 240

Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);

void setup() {
	init();

	Serial.begin(9600);
	tft.begin();
	tft.setRotation(3);
	tft.fillScreen(ILI9341_BLACK);

	pinMode(JOY_SEL,INPUT);
	digitalWrite(JOY_SEL,HIGH);
	pinMode(BUTTON_1,INPUT);
	digitalWrite(BUTTON_1,HIGH);
	pinMode(BUTTON_2,INPUT);
	digitalWrite(BUTTON_2,HIGH);

	randomSeed(analogRead(A7));
}

int main() {
	setup();

	Asteroid ast;
	ast.initRand(&tft);

	Spaceship ss;
	ss.init(&tft);

	while (true) {
		ast.update();
		ss.update();
		delay(10);
	}

	return 0;
}
