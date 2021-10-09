// Si Pham (tonka7su)
// 2021-10-02
// Make your own Arduboy game: part 2 - printing text

#include <Arduboy2.h>
Arduboy2 arduboy;
int counter;

void setup() {
  arduboy.begin();
  arduboy.clear();
  counter = 0;
}

void loop() {
  arduboy.clear();
  arduboy.setCursor(0, 0);

  if (arduboy.pressed(UP_BUTTON)) {
    counter = counter + 1;
  }

  if (arduboy.pressed(DOWN_BUTTON)) {
    counter = counter - 1;
  }

  if (counter % 100 == 0) {
    arduboy.setCursor(30, 30);
    arduboy.print("Yay!");
  }
  
  arduboy.print(counter);
  arduboy.display();
}
