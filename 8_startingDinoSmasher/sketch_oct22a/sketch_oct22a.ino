//Si Pham (tonka7su)
//October 21, 2021
//DinoSmasher

#include <Arduboy2.h>

#define SPEED       5
#define GAME_TITLE  0
#define GAME_PLAY   1
#define GAME_OVER   2
#define GAME_HIGH   3
#define WORLD_WIDTH   14
#define WORLD_HEIGHT  7
#define TILE_SIZE   16
#define GRASS       0
#define WATER       1
#define TREES       2
#define STONE       3

const unsigned char tiles[] PROGMEM = {
// width, height,
16, 16,

// grass
0xff, 0x7f, 0xfb, 0xff, 0xff, 0xbf, 0xff, 0xff, 0xf7, 0xff, 0xfd, 0xff, 0xff, 0xf7, 0x7f, 0xff, 
0xdf, 0xff, 0xff, 0xfb, 0x7f, 0xff, 0xff, 0xff, 0xef, 0xfe, 0xff, 0xff, 0xfb, 0xff, 0x7f, 0xff, 

// water
0x08, 0x10, 0x10, 0x08, 0x10, 0x08, 0x10, 0x10, 0x10, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x20, 0x40, 0x40, 0x20, 0x00, 0x01, 0x02, 0x02, 0x01, 0x02, 0x02, 0x01, 0x02, 0x21, 0x40, 0x40, 


// tree
0xff, 0x1f, 0x5b, 0x3f, 0xeb, 0xdd, 0xff, 0xf7, 0xbb, 0xef, 0xfd, 0x7f, 0xe3, 0xcb, 0xe3, 0xff, 
0xff, 0xc7, 0x96, 0xc7, 0xff, 0xff, 0xef, 0xfd, 0xff, 0xe3, 0xcb, 0xe3, 0xff, 0xff, 0x7b, 0xff, 

// stone
0xff, 0xdf, 0x7b, 0x3f, 0x9f, 0x6f, 0x77, 0xab, 0xdb, 0xd7, 0xcd, 0x5f, 0xbf, 0x77, 0xff, 0xff, 
0xff, 0xc1, 0xdc, 0xd3, 0xaf, 0x9f, 0xae, 0xb0, 0xbb, 0xbd, 0xbd, 0xba, 0xd7, 0xcc, 0x63, 0xff, 
};

Arduboy2 arduboy;

int player_x = 0;
int player_y = 0;
int gamestate = GAME_TITLE;
int mapx = 0;
int mapy = 0;

int world[WORLD_HEIGHT][WORLD_WIDTH] = {
  { TREES, GRASS, GRASS, WATER, GRASS, GRASS, GRASS, TREES, GRASS, GRASS, GRASS, GRASS, GRASS, TREES },
  { GRASS, WATER, WATER, WATER, GRASS, WATER, GRASS, GRASS, GRASS, GRASS, GRASS, STONE, GRASS, GRASS },
  { GRASS, GRASS, GRASS, GRASS, GRASS, WATER, STONE, GRASS, GRASS, GRASS, TREES, GRASS, GRASS, GRASS },
  { STONE, GRASS, GRASS, STONE, TREES, WATER, WATER, WATER, GRASS, WATER, WATER, GRASS, TREES, GRASS },
  { GRASS, GRASS, GRASS, GRASS, TREES, GRASS, GRASS, GRASS, TREES, WATER, GRASS, GRASS, STONE, TREES },
  { GRASS, GRASS, GRASS, WATER, STONE, GRASS, GRASS, TREES, TREES, TREES, GRASS, GRASS, WATER, WATER },
  { GRASS, WATER, WATER, TREES, GRASS, WATER, WATER, TREES, TREES, GRASS, GRASS, GRASS, GRASS, STONE }
};

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
void drawWorld() {
  for (int j = 0; j < WORLD_HEIGHT; j++) {
    for (int i = 0; i < WORLD_WIDTH; i++) {
      Sprites::drawOverwrite(i * TILE_SIZE + mapx, j * TILE_SIZE + mapy, tiles, world[j][i]);
    }
    arduboy.print("\n");
  }
}

void playerInput() {
  if (arduboy.pressed(UP_BUTTON)) {
    mapy += 1;
  }
  if (arduboy.pressed(DOWN_BUTTON)) {
    mapy -= 1;
  }
  if (arduboy.pressed(LEFT_BUTTON)) {
    mapx += 1;
  }
  if (arduboy.pressed(RIGHT_BUTTON)) {
    mapx -= 1;
  }
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

  playerInput();
  drawWorld();

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
  // arduboy.print(F("HELLO!"));
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
