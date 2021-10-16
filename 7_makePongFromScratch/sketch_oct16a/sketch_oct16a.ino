//Si Pham (tonka7su)
//October 15, 2021
//A simple Pong clone

#include <Arduboy2.h>
Arduboy2 arduboy;

int gamestate = 0;
int ballx = 62;
int bally = 0;
int ballsize = 4;
int ballright = 1;
int balldown = 1;

void setup() {
  arduboy.begin();
  arduboy.initRandomSeed();
  arduboy.setFrameRate(60);
  arduboy.clear();
}

void loop() {
  if (!arduboy.nextFrame()) {
    return;
  }
  
  arduboy.clear();
  arduboy.pollButtons();
  
  switch (gamestate) {
  case 0:
    // title screen
    arduboy.setCursor(0, 0);
    arduboy.print("Title Screen");
    if (arduboy.justPressed(A_BUTTON)) {
      gamestate = 1;
    }
    break;
  
  case 1:
    // gameplay screen
    arduboy.setCursor(0, 0);
    arduboy.print("Gameplay");
    if (arduboy.justPressed(A_BUTTON)) {
      gamestate = 2;
    }
    arduboy.fillRect(ballx, bally, ballsize, ballsize, WHITE);
    if (ballright == 1) {
      ballx = ballx + 1;
    }
    if (balldown == 1) {
      ballx = ballx + 1;
    }
    if (ballx == 0) {
      ballright = 1;
    }
    if (ballx == 127) {
      ballright = -1;
    }
    break;

  case 2:
    // win screen
    arduboy.setCursor(0, 0);
    arduboy.print("Win Screen");
    if (arduboy.justPressed(A_BUTTON)) {
      gamestate = 3;
    }
    break;

  case 3:
    // game over screen
    arduboy.setCursor(0, 0);
    arduboy.print("Game over screen");
    if (arduboy.justPressed(A_BUTTON)) {
      gamestate = 0;
    }
    break;
  }

  arduboy.display();
}
