#include <Arduino.h>

long pre = -999;
long now = 0;

uint8_t enc_state;
long enc_read() {
  enc_state >>= 2;
  enc_state |= (digitalRead(2) << 3) | (digitalRead(3) << 2);
  switch(enc_state) {
    case 0b1000:
    case 0b1110:
    case 0b0111:
    case 0b0001:
      return 1;
    case 0b0100:
    case 0b1101:
    case 0b1011:
    case 0b0010:
      return -1;
    default:
      return 0;
  }
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  pinMode(4, INPUT);
}

void loop() {
  now += enc_read();
  // put your main code here, to run repeatedly:
  auto now = pre + enc_read();
  if(now != pre) {
    Serial.println(now);
    pre = now;
  }
}
