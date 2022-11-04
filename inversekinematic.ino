#include <Servo.h>

String nom = "Arduino";
String msg;
const float pi = 3.14159;
float izq;
float der;
float L1;
float L2;
float n;
float m;
float phi1;
float phi2;
float beta1;
float beta2;
float tita1;
float tita2;
float R1;
float R2;

Servo leftServo;
Servo rightServo;

void setup() {
  //medida de los brazos del arduino
  L1 = 4;
  L2 = 4;
  n = 3;
  m = 6;

  Serial.begin(9600);

  leftServo.attach(3);
  rightServo.attach(5);

  inverseKinematic(0,6.6);
  leftServo.write(phi2);
  rightServo.write(phi1);
}

void loop() {
  readSerialPort();
  if (msg != "") {
    sendData();
  //} else {
  //  inverseKinematic(0,4.6);
  }
  
  leftServo.write(phi2);
  rightServo.write(phi1);
  delay(500);
}

void readSerialPort() {
  msg = "";
  if (Serial.available()) {
      //delay(5);
      while (Serial.available() > 0) {
          msg += (char)Serial.read();
      }
      Serial.flush();
  }
}

void sendData() {
  //Desplazamos adelante
  if (msg == "adelante"){
    Serial.print((String)nom + " received : " + msg);
    inverseKinematic(0,6.6);
    delay(5);
  }

  //Desplazamos atras
  if (msg == "atras" or msg == "atrás"){
    Serial.print((String)nom + " received : " + msg);
    inverseKinematic(0,2.6); 
    delay(5);
  }

  // Desplazamos izquierda
  if (msg == "izquierda") {
    Serial.print((String)nom + "received : " + msg);
    inverseKinematic(-2,6.6); 
    delay(5);
  }

  // Desplazamos derecha
  if (msg == "derecha") {
    Serial.print((String)nom + "received : " + msg);
    inverseKinematic(2,6.6); 
    delay(5);
  }

  // Alto
  if (msg == "alto") {
    Serial.print((String)nom + "received : " + msg);
    inverseKinematic(0,4.6); 
    delay(5);
  }
  
}


void inverseKinematic(int x, int y){
  R1 = sqrt(pow(n-x,2) + pow(y,2)); 
  R2 = sqrt(pow(n+x,2) + pow(y,2));
  
  //derecha
  phi1 = acos((pow(L1,2) + pow(R1,2) - pow(L2,2)) / (2*L1*R1));
  beta1 = acos((pow(m,2) + pow(R1,2) - pow(R2,2)) / (2*m*R1));
  tita1 = phi1 + beta1;
  tita1 = tita1*(180/pi);
  
  //izquierda
  phi2 = acos((pow(L1,2) + pow(R2,2) - pow(L2,2)) / (2*L1*R2));
  beta2 = acos((pow(m,2) + pow(R2,2) - pow(R1,2)) / (2*m*R2));
  tita2 = phi2 + beta2;
  tita2 = tita2*(180/pi);
}
