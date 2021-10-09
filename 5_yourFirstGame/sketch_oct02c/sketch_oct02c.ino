// Si Pham (tonka7su)
// 2021-10-02
// Make your own Arduboy game: part 5 - your first game

#include <Arduboy2.h>
Arduboy2 arduboy;
int playerWin;
int attempts;
int guessedNumber;
int randomNumber;

void setup() {
  arduboy.begin();
  arduboy.clear();

  playerWin = 0;
  attempts = 0;
  guessedNumber = 0;

  arduboy.initRandomSeed();
  randomNumber = random(1, 101);
}

void loop() {
  arduboy.clear();
  arduboy.pollButtons();
  
  if (playerWin == 0) {
    if (attempts == 7) {
      arduboy.setCursor(0, 0);
      arduboy.print("You lost!");
      arduboy.print("\n");
      arduboy.print("Correct number: ");
      arduboy.print(randomNumber);
      if (arduboy.justPressed(A_BUTTON)) {
        randomNumber = random(1, 101);
        attempts = 0;
        playerWin = 0;
      }
    } else {
      if (arduboy.justPressed(UP_BUTTON)) {
        guessedNumber = guessedNumber + 1;
      }
      if (arduboy.justPressed(DOWN_BUTTON)) {
        guessedNumber = guessedNumber - 1;
      }
      if (arduboy.justPressed(A_BUTTON)) {
        if (guessedNumber == randomNumber) {
          playerWin = 1;
        } else {
          attempts = attempts + 1;
        }
      }
      arduboy.setCursor(0, 0);
      arduboy.print("Attempt: ");
      arduboy.print(attempts);
      arduboy.print("\n");
      arduboy.print("Number to guess: ");
      arduboy.print(guessedNumber);
    }
  } else {
    arduboy.setCursor(0, 0);
    arduboy.print("YOU WON!");
    arduboy.print("\n");
    arduboy.print("Corrct number: ");

    if (arduboy.justPressed(A_BUTTON)) {
      randomNumber = random(1, 101);
      attempts = 0;
      playerWin = 0;
    }
  }
  arduboy.display();
}
