#include <LedControlMS.h>

int DIN = 11;
int CS = 7;
int CLK = 13;
LedControl lc = LedControl(DIN, CLK, CS, 0);

int x = A0;     //Saída analógica (Eixo X)
int y = A1;     //Saída analógica (Eixo Y)
int botao = 2;  //Saída digital do botão (Eixo Z)

int column = 1, row = random(8) + 1;  // define aleatóriamente em que ponto a bola deve começar
int directionX = 1, directionY = 1;   //define que vai primeiro da esquerda para a direita

int pinPot = 14;
int pinPotVal;                        // valor do eixo x - joystick
int velocidade = 200;                 // valor inicial para a velocidade
byte counter = 0;                     // contador
const byte mult = 10;                 // multiplicador

byte sad[] = {
  B00111100,
  B01000010,
  B10100101,
  B10000001,
  B10011001,
  B10100101,
  B01000010,
  B00111100
};

byte smile[] = {
  B00111100,
  B01000010,
  B10100101,
  B10000001,
  B10100101,
  B10011001,
  B01000010,
  B00111100
};

void setup() {
  lc.shutdown(0, false);      //habilita o display
  lc.setIntensity(0, 8);      //define o brilho como médio
  lc.clearDisplay(0);         //limpa o display
  randomSeed(analogRead(0));  //criar séries genuinamente aleatórias
  newGame();
}  // end setup

void loop() {
  pinPotVal = analogRead(pinPot);
  pinPotVal = map(pinPotVal, 200, 1024, 1, 6);
  column += directionX;
  row += directionY;

  if (column == 6 && directionX == 1 && (pinPotVal == row || pinPotVal + 1 == row || pinPotVal + 2 == row)) directionX = -1;
  if (column == 0 && directionX == -1) directionX = 1;
  if (row == 7 && directionY == 1) directionY = -1;
  if (row == 0 && directionY == -1) directionY = 1;
  if (column == 7) gameOver();

  lc.clearDisplay(0);  //limpa tela para próxima quadro de animação
  lc.setLed(0, column, row, HIGH);
  lc.setLed(0, 7, pinPotVal, HIGH);
  lc.setLed(0, 7, pinPotVal + 1, HIGH);
  lc.setLed(0, 7, pinPotVal + 2, HIGH);

  if (!(counter % mult)) {
    velocidade -= 5;
    mult* mult;
  }
  delay(velocidade);

  counter++;

}  //end loop

void gameOver() {
  setSprite(sad);  // exibe carinha triste
  delay(1500);
  lc.clearDisplay(0);
  newGame();
}

void newGame() {
  for (byte x = 0; x < 3; x++) {
    lc.clearDisplay(0);
    delay(250);
    for (int y = 0; y < 8; y++) {
      lc.setRow(0, y, 255);
    }
    delay(250);
  }  //end for

  setSprite(smile);  // exibe carinha com riso
  delay(1500);
  lc.clearDisplay(0);

  counter = 0;  //reinicia todos os valores
  velocidade = 300;
  column = 1;
  row = random(8) + 1;

}  //end newGame

void setSprite(byte sprite[]) {
  for (byte r = 0; r < 8; r++) {
    lc.setRow(0, r, sprite[r]);
  }
}  // end setSpritevoid setup() {
  // put your setup code here, to run once:
