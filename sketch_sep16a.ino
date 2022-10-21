#include <Servo.h>

String nom = "Arduino";
String msg;

Servo leftServo;
Servo rightServo;

void setup() {
  Serial.begin(9600);
  
  leftServo.attach(3);
  rightServo.attach(5);

  leftServo.write(77);
  rightServo.write(103);
}

void loop() {
  readSerialPort();
  if (msg != "") {
      sendData();
  }
  delay(500);
}
void readSerialPort() {
  msg = "";
  if (Serial.available()) {
      delay(10);
      while (Serial.available() > 0) {
          msg += (char)Serial.read();
      }
      Serial.flush();
  }
}
void sendData() {
  //write data
  
  
  // Desplazamos adelante
  if (msg == "adelante") {
    Serial.print(nom);
  Serial.print(" received : ");
  Serial.print(msg);
    //leftServo.write(90);
    //rightServo.write(90);
    //delay(5);
  }

  // Desplazamos atras
  //if (msg == "atras") {
    //leftServo.write(79);
    //rightServo.write(101);
    //delay(5);
  //}

  // Desplazamos derecha
  //if (msg == "derecha") {
    //leftServo.write(94);
    //rightServo.write(112);
    //delay(5);
  //}

  // Desplazamos izquierda
  //if (msg == "izquierda") {
    //leftServo.write(86);
    //rightServo.write(68);
    //delay(5);
  //}

  // Alto
  //if (msg == "alto") {
    //leftServo.write(77);
    //rightServo.write(103);
    //delay(5);
  //}
}
