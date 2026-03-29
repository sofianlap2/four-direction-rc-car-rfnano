#include <SPI.h>
#include <RF24.h>

RF24 radio(9, 10);
const byte address[6] = "NODE1";

struct Data {
  int speed;
  int turn;
};

Data data;

const int forwardBtn  = 4;
const int backwardBtn = 5;
const int leftBtn     = 6;
const int rightBtn    = 7;

void setup() {
  pinMode(forwardBtn, INPUT_PULLUP);
  pinMode(backwardBtn, INPUT_PULLUP);
  pinMode(leftBtn, INPUT_PULLUP);
  pinMode(rightBtn, INPUT_PULLUP);

  radio.begin();
  radio.setChannel(108);
  radio.setDataRate(RF24_250KBPS);
  radio.openWritingPipe(address);
  radio.stopListening();
}

void loop() {
  bool fwd  = digitalRead(forwardBtn) == LOW;
  bool bwd  = digitalRead(backwardBtn) == LOW;
  bool left = digitalRead(leftBtn) == LOW;
  bool right= digitalRead(rightBtn) == LOW;

  // SPEED
  if (fwd && !bwd) data.speed = 1;
  else if (bwd && !fwd) data.speed = -1;
  else data.speed = 0;

  // TURN
  if (left && !right) data.turn = -1;
  else if (right && !left) data.turn = 1;
  else data.turn = 0;

  radio.write(&data, sizeof(data));

  delay(50);
}