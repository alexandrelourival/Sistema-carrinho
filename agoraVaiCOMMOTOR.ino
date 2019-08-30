#include <Ultrasonic.h>
#include <ArduinoJson.h>
#define potenciometro A0
#define motorEF 38
#define motorET 40
#define motorDF 42
#define motorDT 44
#define velocidadeMD 13
#define velocidadeME 11
#define pino_trigger1 34
#define pino_echo1 30
#define pino_trigger2 24
#define pino_echo2 22


int val;
int pwm;
int estado = 0;
int aleatorio;
int lastTimeComando = 0;

Ultrasonic ultrasonic1(pino_trigger1, pino_echo1);
Ultrasonic ultrasonic2(pino_trigger2, pino_echo2);

void setup() {
  Serial.begin(115200);
  pinMode(motorEF, OUTPUT);
  pinMode(motorET, OUTPUT);
  pinMode(motorDF, OUTPUT);
  pinMode(motorDT, OUTPUT);
  pinMode(velocidadeMD, OUTPUT);
  pinMode(velocidadeME,OUTPUT);
  pinMode(potenciometro, INPUT);
}

void loop() {
  char comando;
  float sensor1, sensor2;
  long microsec1;
  long microsec2;


  microsec1 = ultrasonic1.timing();
  microsec2 = ultrasonic2.timing();
  sensor1 = ultrasonic1.convert(microsec1, Ultrasonic::CM);
  sensor2 = ultrasonic2.convert(microsec2, Ultrasonic::CM);

  val = analogRead(potenciometro);
  pwm = map(val, 0, 1023, 0, 255);
  comando = Serial.read();

  DynamicJsonBuffer jBuffer;
  JsonObject& root = jBuffer.createObject();

  root["Sensor1"] = sensor1;
  root["Sensor2"] = sensor2;

  root.printTo(Serial);
  Serial.println();
  
  if (comando == '1'){                                      //andando para frente
    digitalWrite(motorEF, HIGH);
    digitalWrite(motorDF, HIGH);
    digitalWrite(motorET, LOW);
    digitalWrite(motorDT, LOW);
    analogWrite(velocidadeMD, pwm);
    analogWrite(velocidadeME, pwm);
    if (sensor1 < 15) {
      aleatorio = random(0, 3);
      while (sensor1 < 15) {
        if (aleatorio == 1) {                                    //curva para esquerda
          analogWrite(velocidadeME, pwm * 0.1);
          analogWrite(velocidadeMD, pwm);
          digitalWrite(motorEF, HIGH);
          digitalWrite(motorDF, HIGH);
          digitalWrite(motorET, LOW);
          digitalWrite(motorDT, LOW);
        }
        else if (aleatorio == 2) {                              //curva para direita
          analogWrite(velocidadeMD, pwm * 0.1);
          analogWrite(velocidadeME, pwm);
          digitalWrite(motorEF, HIGH);
          digitalWrite(motorDF, HIGH);
          digitalWrite(motorET, LOW);
          digitalWrite(motorDT, LOW);
        }
        microsec1 = ultrasonic1.timing();
        sensor1 = ultrasonic1.convert(microsec1, Ultrasonic::CM);
      }

    }
  }
  else if (comando == '2') {
    digitalWrite(motorET, HIGH);
    digitalWrite(motorDT, HIGH);
    digitalWrite(motorEF, LOW);
    digitalWrite(motorDF, LOW);
    analogWrite(velocidadeMD, pwm);
    analogWrite(velocidadeME, pwm);
    if (sensor2 < 15) {
      aleatorio = random(0, 3);
      while(sensor2 < 15){
        if (aleatorio == 1) {                                     //curva para esquerda
          analogWrite(velocidadeMD, pwm * 0.1);
          analogWrite(velocidadeME, pwm);
          digitalWrite(motorET, HIGH);
          digitalWrite(motorDT, HIGH);
          digitalWrite(motorEF, LOW);
          digitalWrite(motorDF, LOW);

        }
        else if (aleatorio == 2) {                             //curva para direita
          analogWrite(velocidadeME, pwm * 0.1);
          analogWrite(velocidadeMD, pwm);
          digitalWrite(motorET, HIGH);
          digitalWrite(motorDT, HIGH);
          digitalWrite(motorEF, LOW);
          digitalWrite(motorDF, LOW);
        }
         microsec2 = ultrasonic2.timing();
         sensor2 = ultrasonic2.convert(microsec2, Ultrasonic::CM);
      }
    }
  }
}
