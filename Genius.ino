// Definição dos pinos
const int LED_GREEN = 2; // LED do botão verde
const int LED_RED = 3;   // LED do botão vermelho
const int LED_BLUE = 4;  // LED do botão azul
const int LED_YELLOW = 5;// LED do botão amarelo

const int BTN_GREEN = 6; // Botão verde
const int BTN_RED = 7;   // Botão vermelho
const int BTN_BLUE = 8;  // Botão azul
const int BTN_YELLOW = 10; // Botão amarelo

const int BUZZER = 9;

// Variáveis do jogo
int sequence[100]; // Sequência de cores (até 100 passos)
int sequenceLength = 0; // Tamanho atual da sequência
bool playerTurn = false;

void setup() {
  // Configuração dos pinos dos LEDs
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);
  pinMode(LED_YELLOW, OUTPUT);

  // Configuração dos pinos dos botões
  pinMode(BTN_GREEN, INPUT_PULLUP);
  pinMode(BTN_RED, INPUT_PULLUP);
  pinMode(BTN_BLUE, INPUT_PULLUP);
  pinMode(BTN_YELLOW, INPUT_PULLUP);

  // Configuração do buzzer
  pinMode(BUZZER, OUTPUT);

  Serial.begin(9600);
  randomSeed(analogRead(0)); // Inicializa o gerador de números aleatórios
}

void loop() {
  // Mostra a sequência ao jogador
  playSequence();

  // Espera a resposta do jogador
  if (!playerTurn) {
    playerTurn = true;
    if (!playerInput()) {
      gameOver();
    }
    playerTurn = false;
  }

  // Adiciona um novo passo à sequência
  addStep();
}

// Adiciona um novo passo à sequência
void addStep() {
  sequence[sequenceLength] = random(0, 4); // Gera um número aleatório entre 0 e 3
  sequenceLength++;
}

// Mostra a sequência de luzes e sons
void playSequence() {
  for (int i = 0; i < sequenceLength; i++) {
    playColor(sequence[i]);
    delay(500);
  }
  delay(1000); // Pequena pausa antes da jogada do jogador
}

// Reproduz uma cor com som e luz
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

// Captura a entrada do jogador
bool playerInput() {
  for (int i = 0; i < sequenceLength; i++) {
    int playerMove = waitForButtonPress();
    if (playerMove != sequence[i]) {
      return false; // Resposta errada
    }
  }
  return true; // Jogador acertou toda a sequência
}

// Espera até que o jogador pressione um botão
int waitForButtonPress() {
  while (true) {
    if (digitalRead(BTN_GREEN) == LOW) return 0;
    if (digitalRead(BTN_RED) == LOW) return 1;
    if (digitalRead(BTN_BLUE) == LOW) return 2;
    if (digitalRead(BTN_YELLOW) == LOW) return 3;
  }
}

// Finaliza o jogo em caso de erro
void gameOver() {
  for (int i = 0; i < 3; i++) {
    tone(BUZZER, 200, 500);
    delay(500);
  }
  sequenceLength = 0; // Reseta o jogo
  addStep();          // Adiciona o primeiro passo para recomeçar
}
