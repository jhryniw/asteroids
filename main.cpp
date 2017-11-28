#include <Arduino.h>
#include <Adafruit_ILI9341.h>

#include "asteroid.h"
#include "spaceship.h"
#include "gamestate.h"

#define TFT_DC 9
#define TFT_CS 10

Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);
GameState gameState(&tft);

float prevTime;
float deltaTime;

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

	deltaTime = (millis() - prevTime) / 100;
	prevTime = millis() / 100;

	gameState.drawScore();

	while (true) {
		unsigned long start = millis();
		gameState.tick(deltaTime);

		if(!gameState.hasMaxAsteroids() && random(1000) < (MAX_ASTEROIDS - gameState.numAsteroids())) {
			Asteroid a;
			spawn_asteroid(&a);
		}

		unsigned long run_time = millis() - start;
		delay(max(10 - (long)run_time, 0));
	}

	return 0;
}
