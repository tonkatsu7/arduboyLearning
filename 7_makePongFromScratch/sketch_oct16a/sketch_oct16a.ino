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
int paddlewidth = 4;
int paddleheight = 9;
int playerx = 0;
int playery = 0;
int computerx = 127 - paddlewidth;
int computery = 0;

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

    // draw player paddle
    arduboy.fillRect(playerx, playery, paddlewidth, paddleheight, WHITE);

    if (arduboy.pressed(UP_BUTTON) && playery > 0) {
      playery = playery - 1;
    }
    if (arduboy.pressed(DOWN_BUTTON) && playery + paddleheight < 63) {
      playery = playery + 1;
    }

    // draw computer paddle
    arduboy.fillRect(computerx, computery, paddlewidth, paddleheight, WHITE);

    if (bally < computery) {
      computery = computery - 1;
    }
    if (bally + ballsize > computery + paddleheight) {
      computery = computery + 1;
    }

    // draw ball
    arduboy.fillRect(ballx, bally, ballsize, ballsize, WHITE);
    // ball moves right
    if (ballright == 1) {
      ballx = ballx + 1;
    }
    // ball moves left
    if (ballright == -1) {
      ballx = ballx - 1;
    }
    // ball bounces from right to left
    if (ballx == playerx + paddlewidth && playery < bally + ballsize && playery + paddleheight > bally) {
      ballright = 1;
    }
    // ball bounces from right to left
    if (ballx + ballsize == computerx && computery < bally + ballsize && computery + paddleheight > bally) {
      ballright = -1;
    }

    if (balldown == 1) {
      bally = bally + 1;
    }
    if (balldown == -1) {
      bally = bally - 1;
    }
    if (bally == 0) {
      balldown = 1;
    }
    if (bally + ballsize == 63) {
      balldown = -1;
    }

    if (arduboy.justPressed(A_BUTTON)) {
      gamestate = 2;
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
