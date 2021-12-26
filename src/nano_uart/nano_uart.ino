

void setup() {
  Serial.begin(19200);
}

template<typename T>
void sendData(const T data){
   for(int i=0; i<2; i++){
    Serial.write((data >> (8*i)) & 0b11111111);
  }
}

void loop() {
  sendData(0xFFFF);
  sendData(analogRead(A3));
  sendData(analogRead(A4));
  sendData(analogRead(A5));
  sendData(analogRead(A6));
}
