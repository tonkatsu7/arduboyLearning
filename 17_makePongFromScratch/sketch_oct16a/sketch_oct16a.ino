//Si Pham (tonka7su)
//October 15, 2021
//A simple Pong clone

#include <Arduboy2.h>
Arduboy2 arduboy;

// overall state of the program
int gamestate = 0;
// ball
int ballx = 62;
int bally = 0;
int ballsize = 4;
int ballright = 1;
int balldown = 1;
// player paddle
int paddlewidth = 4;
int paddleheight = 9;
int playerx = 0;
int playery = 0;
// computer paddle
int computerx = 127 - paddlewidth;
int computery = 0;
// scoring
int playerscore = 0;
int computerscore = 0;

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
    arduboy.setCursor(20, 0);
    arduboy.print(playerscore);

    arduboy.setCursor(101, 0);
    arduboy.print(computerscore);

    // ##### DRAW BALL #####

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

    // ##### DRAW PLAYER PADDLE #####

    // draw player paddle
    arduboy.fillRect(playerx, playery, paddlewidth, paddleheight, WHITE);

    if (arduboy.pressed(UP_BUTTON) && playery > 0) {
      playery = playery - 1;
    }
    if (arduboy.pressed(DOWN_BUTTON) && playery + paddleheight < 63) {
      playery = playery + 1;
    }
    
    // ##### DRAW COMPUTER PADDLE #####

    // draw computer paddle
    arduboy.fillRect(computerx, computery, paddlewidth, paddleheight, WHITE);

    if (ballx > 115 | random(0, 20) == 1) {
      if (bally < computery) {
        computery = computery - 1;
      }
      if (bally + ballsize > computery + paddleheight) {
        computery = computery + 1;
      }  
    }

    // ##### SCORING #####

    // player scores a point when the ball goes off the screen on the right
    if (ballx < -10) {
      ballx = 63;
      computerscore = computerscore + 1;
    }

    // computer scores a point when the ball goes off the screen on the left
    if (ballx > 130) {
      ballx = 63;
      playerscore = playerscore + 1;
    }

    // player wins
    if (playerscore == 5) {
      gamestate = 2;
    }

    // player loses
    if (computerscore == 5) {
      gamestate = 3;
    }

    // player concede?
    if (arduboy.justPressed(A_BUTTON)) {
      gamestate = 2;
    }
    break;

  case 2:
    // win screen
    arduboy.setCursor(0, 0);
    arduboy.print("Win Screen");
    reset();
    if (arduboy.justPressed(A_BUTTON)) {
      gamestate = 3;
    }
    break;

  case 3:
    // game over screen
    arduboy.setCursor(0, 0);
    arduboy.print("Game over screen");
    reset();
    if (arduboy.justPressed(A_BUTTON)) {
      gamestate = 0;
    }
    break;
  }

  arduboy.display();
}

void reset() {
  ballx = 0;
  playerscore = 0;
  computerscore = 0;
}
