#include <Arduino.h>
#include <Adafruit_ILI9341.h>

#include "asteroid.h"
#include "spaceship.h"
#include "gamestate.h"

#define TFT_DC 9
#define TFT_CS 10
#define TFT_WIDTH 320
#define TFT_HEIGHT 240

Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);
GameState gameState;

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
	gameState.spawn(&ast);

	Asteroid ast2;
	ast2.initRand(&tft);
	gameState.spawn(&ast2);

	Spaceship ss;
	ss.init(&tft);
	gameState.spaceship = ss;

	while (true) {
		gameState.tick();
		delay(10);
	}

	return 0;
}
