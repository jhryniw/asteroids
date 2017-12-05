#include <Arduino.h>
#include <Adafruit_ILI9341.h>

#include "asteroid.h"
#include "spaceship.h"
#include "gamestate.h"

#define TFT_DC 9
#define TFT_CS 10

Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);
GameState gameState(&tft);

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

	// Sets random number generator
	uint16_t seed = 0;
	for (int i = 0; i < 16; i++) {
		seed = (seed << 1) | analogRead(A7) & 1;
	}

	randomSeed(seed);
}

int main() {
	setup();
	gameState.drawScore();

	while (true) {
		// Updates delta time since last frame
		deltaTime = (millis() - prevTime) / 1000;
		prevTime = millis();

		gameState.tick(deltaTime);

		// Spawning scales up with less asteroids on screen
		if(!gameState.hasMaxAsteroids() && random(1000)
				< (MAX_ASTEROIDS - gameState.numAsteroids())) {
					Asteroid a;
					spawn_asteroid(&a);
		}
	}

	return 0;
}
