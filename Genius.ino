// Pin's definition
const int LED_GREEN = 2; // Green button's LED
const int LED_RED = 3;   // Red button's LED
const int LED_BLUE = 4;  // Blue button's LED
const int LED_YELLOW = 5;// Yellow button's LED

const int BTN_GREEN = 6; // Green button
const int BTN_RED = 7;   // Red button
const int BTN_BLUE = 8;  // Blue button
const int BTN_YELLOW = 10; // Yellow Button

const int BUZZER = 9;

// Game's vars
int sequence[100]; // colors sequence (100 steps)
int sequenceLength = 0; // current sequence lenght
bool playerTurn = false;

void setup() {
  // LED Pin's configuration
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);
  pinMode(LED_YELLOW, OUTPUT);

  // Button Pin's configuration
  pinMode(BTN_GREEN, INPUT_PULLUP);
  pinMode(BTN_RED, INPUT_PULLUP);
  pinMode(BTN_BLUE, INPUT_PULLUP);
  pinMode(BTN_YELLOW, INPUT_PULLUP);

  // buzzer config
  pinMode(BUZZER, OUTPUT);

  Serial.begin(9600);
  randomSeed(analogRead(0)); // start the random number generation
}

void loop() {
  //Play the sequence to the player
  playSequence();

  // Wait Player's response
  if (!playerTurn) {
    playerTurn = true;
    if (!playerInput()) {
      gameOver();
    }
    playerTurn = false;
  }

  // Add a new step to the sequence
  addStep();
}

// Add a new step to the sequence
void addStep() {
  sequence[sequenceLength] = random(0, 4); // Generate a random number between 0 and 3
  sequenceLength++;
}

//  Play the sequence of led and sound
void playSequence() {
  for (int i = 0; i < sequenceLength; i++) {
    playColor(sequence[i]);
    delay(500);//delay to understand the sequence
  }
  delay(1000); // Pause before the player's turn
}

// Play a sound and a color
void playColor(int color) {
  switch (color) {
    case 0:
      digitalWrite(LED_GREEN, HIGH);
      tone(BUZZER, 400, 300);
      delay(300);
      digitalWrite(LED_GREEN, LOW);
      break;
    case 1:
      digitalWrite(LED_RED, HIGH);
      tone(BUZZER, 500, 300);
      delay(300);
      digitalWrite(LED_RED, LOW);
      break;
    case 2:
      digitalWrite(LED_BLUE, HIGH);
      tone(BUZZER, 600, 300);
      delay(300);
      digitalWrite(LED_BLUE, LOW);
      break;
    case 3:
      digitalWrite(LED_YELLOW, HIGH);
      tone(BUZZER, 700, 300);
      delay(300);
      digitalWrite(LED_YELLOW, LOW);
      break;
  }
}

// Get the player input
bool playerInput() {
  for (int i = 0; i < sequenceLength; i++) {
    int playerMove = waitForButtonPress();
    if (playerMove != sequence[i]) {
      return false; // Wrong answer
    }
  }
  return true; // Player made the correct sequence
}

// Wait until player press a button
int waitForButtonPress() {
  while (true) {
    if (digitalRead(BTN_GREEN) == LOW) return 0;
    if (digitalRead(BTN_RED) == LOW) return 1;
    if (digitalRead(BTN_BLUE) == LOW) return 2;
    if (digitalRead(BTN_YELLOW) == LOW) return 3;
  }
}

// End the game if there's a error
void gameOver() {
  for (int i = 0; i < 3; i++) {
    tone(BUZZER, 200, 500);
    delay(500);
  }
  sequenceLength = 0; // Reset the game
  addStep();          // Add the first step to restart the game
}
