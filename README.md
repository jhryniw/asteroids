# Asteroids
The classic asteroids game, for Arduino!


This was a CMPUT274 final project by Songhui Zhang & James Hryniw

# Accessories:
  * 1x Arduino MEGA board
  * 1x Adafruit ILI9341 Breakout Board
  * 1x SainSmart JoyStick Module
  * 2x Push buttons

# Wiring instructions:
  Adafruit (Left is Adafruit, right is Arduino)
  * GND   <>  GND
  * Vin   <>  5V
  * CLK   <>  52
  * MISO  <>  50
  * MOSI  <>  51
  * CS    <>  10
  * D/C   <>  9
  * Y+    <>  A2
  * X+    <>  4
  * Y-    <>  5
  * X-    <>  A3
  * CCS   <>  6

  Joystick (Left is joystick, right is Arduino)
  * GND   <>  GND
  * +5V   <>  5V
  * VRx   <>  A1
  * VRy   <>  A0
  * SW    <>  2

  Buttons
  * Button 1 + <> 13
  * Button 2 + <> 12
  * Button 1 - <> GND
  * Button 2 - <> GND

# Program instructions:
  * Wire Arduino as above and connect it to the computer.
  * In terminal, navigate to program directory and enter "make upload".
  * The joystick controls the direction of the ship.
  * Pressing and holding button 1 will accelerate the ship.
  * Pressing button 2 will shoot a bullet.
  * Shooting an asteroid with a bullet will increase your score
    and may spawn two smaller asteroids.
  * Colliding the ship with an asteroid will cause you to lose one life
    and respawn in the center of the screen. You will be invulnerable
    for two seconds afterwards.
  * Losing all three lives will end the game. Press the Arduino's
    RESET button to restart the game.

# Code structure:
  * Asteroid, Bullet, and Spaceship are similar physics objects
  * These are updated and created by GameState
  * main() updates GameState with delta time and handles Asteroid spawn
  * inputs and common are misc. files to handle input and game
    logic respectively.
  * The program assumes that the joysticks are calibrated similarly.
