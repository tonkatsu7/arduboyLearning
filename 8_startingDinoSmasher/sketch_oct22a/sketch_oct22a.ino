//Si Pham (tonka7su)
//October 21, 2021
//DinoSmasher

#include <Arduboy2.h>

#define SPEED       5
#define GAME_TITLE  0
#define GAME_PLAY   1
#define GAME_OVER   2
#define GAME_HIGH   3

Arduboy2 arduboy;

int player_x = 0;
int player_y = 0;
int gamestate = GAME_TITLE;

void move_left() {
  player_x -= SPEED;
}
void move_right() {
  player_x += SPEED;
}
void move_up() {
  player_y -= SPEED;
}
void move_down() {
  player_y += SPEED;
}

void titleScreen() {
  arduboy.setCursor(0, 0);
  arduboy.print("Title screen\n");
  if (arduboy.justPressed(A_BUTTON)) {
    gamestate = GAME_PLAY;
  }
}

void gameplay() {
  arduboy.setCursor(0, 0);
  arduboy.print("Gameplay\n");
  if (arduboy.justPressed(A_BUTTON)) {
    gamestate = GAME_OVER;
  }
}

void gameOverScreen() {
  arduboy.setCursor(0, 0);
  arduboy.print("Game over screen\n");
  if (arduboy.justPressed(A_BUTTON)) {
    gamestate = GAME_HIGH;
  }
}

void highScoreScreen() {
  arduboy.setCursor(0, 0);
  arduboy.print("High score screen\n");
  if (arduboy.justPressed(A_BUTTON)) {
    gamestate = GAME_TITLE;
  }
}

void gameLoop() {
  switch (gamestate)
  {
  case GAME_TITLE:
    titleScreen();
    break;

  case GAME_PLAY:
    gameplay();
    break;

  case GAME_OVER:
    gameOverScreen();
    break;

  case GAME_HIGH:
    highScoreScreen();
    break;
  
  default:
    break;
  }
  arduboy.print(F("HELLO!"));
}

void setup() {
  arduboy.begin();
  arduboy.setFrameRate(45);
  arduboy.display();
  arduboy.initRandomSeed();
  arduboy.clear();
}

void loop() {
  if (!arduboy.nextFrame()) {
    return;
  }
  arduboy.pollButtons();
  arduboy.clear();
  gameLoop();
  arduboy.display();
}
