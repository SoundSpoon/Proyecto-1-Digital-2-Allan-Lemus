//▶︎ •၊၊||၊|။|||| |၊၊•    •၊၊||၊|။||||။‌‌‌‌‌၊|• 
// Universidad del Valle de Guatemala
// BE3029- Electronica digital 2
// Allan Lemus
// 5/08/25
// Proyecto 1
// MCU: ESP32
//▶︎ •၊၊||၊|။|||| |၊၊•    •၊၊||၊|။||||။‌‌‌‌‌၊|•


//▶︎ •၊၊||၊|။|||| |၊၊•  Librerías  •၊၊||၊|။||||။‌‌‌‌‌၊|• 

#include <Arduino.h>
#include "AdafruitIO_WiFi.h"
#include <stdint.h>
#include "driver/ledc.h"
#include "config.h"

//▶︎ •၊၊||၊|။|||| |၊၊•  Definiciones  •၊၊||၊|။||||။‌‌‌‌‌၊|• 

#define ledR 15
#define ledG 2
#define ledB 4
#define leda 12
#define ledb 14
#define leddp 27
#define ledc 26
#define ledd 25
#define lede 33
#define ledf 19
#define ledg 32
#define d1 16
#define d2 17
#define d3 5
#define btn 18
#define temp 34
#define freqPWM 100 
#define resPWN 16
#define servoFreq   50
#define servoRes   12
#define servoMin 1000   
#define servoCanal 0  
#define srv 13



//▶︎ •၊၊||၊|။|||| |၊၊•  Prototipos de funciones  •၊၊||၊|။||||။‌‌‌‌‌၊|• 

void MostrarNumero(uint8_t);

//▶︎ •၊၊||၊|။|||| |၊၊•  Variables Globales  •၊၊||၊|။||||။‌‌‌‌‌၊|• 

int contando = 0;  
int decenas = 0;
int unidades = 0;
int decimal = 0;
int freq = 50;
int res = 16;
bool lecturab1;
bool eb1 = LOW;
unsigned long antesb1 = 0; 
const unsigned long retraso = 100; 

//▶︎ •၊၊||၊|။|||| |၊၊•  ISRs rutinas de interrupción  •၊၊||၊|။||||။‌‌‌‌‌၊|• 



//▶︎ •၊၊||၊|။|||| |၊၊•  Adafruit  •၊၊||၊|။||||။‌‌‌‌‌၊|• 

#define IO_USERNAME "SndSpn"
#define IO_KEY "aio_riux56ZW4WGOpkbNhCAKGKFQktP4"
#define WIFI_SSID "AllanWifi"
#define WIFI_PASS "07070707"
AdafruitIO_WiFi io(IO_USERNAME, IO_KEY, WIFI_SSID, WIFI_PASS);
#define IO_LOOP_DELAY 5000
unsigned long lastUpdate = 0;

// set up the 'counter' feed
AdafruitIO_Feed *canaltemp = io.feed("temp");


//▶︎ •၊၊||၊|။|||| |၊၊•  Configuraciones  •၊၊||၊|။||||။‌‌‌‌‌၊|• 

void setup() {
  pinMode(btn, INPUT);
  pinMode(temp, INPUT);
  pinMode(ledR, OUTPUT);
  pinMode(ledG, OUTPUT);
  pinMode(ledB, OUTPUT);
  pinMode(leda, OUTPUT);
  pinMode(ledb, OUTPUT);
  pinMode(leddp, OUTPUT);
  pinMode(ledc, OUTPUT);
  pinMode(ledd, OUTPUT);
  pinMode(lede, OUTPUT);
  pinMode(ledf, OUTPUT);
  pinMode(ledg, OUTPUT);
  pinMode(d1, OUTPUT);
  pinMode(d2, OUTPUT);
  pinMode(d3, OUTPUT);
  digitalWrite(d1, LOW);
  digitalWrite(d2, LOW);
  digitalWrite(d3, LOW);
  digitalWrite(leda, LOW);
  digitalWrite(ledb, LOW);
  digitalWrite(leddp, LOW);
  digitalWrite(ledc, LOW);
  digitalWrite(ledd, LOW);
  digitalWrite(lede, LOW);
  digitalWrite(ledf, LOW);
  digitalWrite(ledg, LOW);
  ledcSetup(servoCanal, servoFreq, servoRes);
  ledcAttachPin(srv, servoCanal);
  ledcWrite(servoCanal, 0);
  Serial.begin(115200);
  Serial.print("Conectando a Adafruit....");
  io.connect();
  while (io.status() < AIO_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println("\nConectado a Adafruit ");
}

//▶︎ •၊၊||၊|။|||| |၊၊•  Loop infinito  •၊၊||၊|။||||။‌‌‌‌‌၊|• 

void loop() {
     digitalWrite(d1, HIGH);
     digitalWrite(d2, LOW);
     digitalWrite(d3, LOW);
     MostrarNumero(decenas);
     digitalWrite(leddp, LOW);
     delay(5);
     digitalWrite(d1, LOW);
     digitalWrite(d2, HIGH);
     digitalWrite(d3, LOW);
     MostrarNumero(unidades);
     digitalWrite(leddp, HIGH);
     delay(5);
     digitalWrite(d1, LOW);
     digitalWrite(d2, LOW);
     digitalWrite(d3, HIGH);
     MostrarNumero(decimal);
     digitalWrite(leddp, LOW);
     delay(5);
     digitalWrite(d1, LOW);
     digitalWrite(d2, LOW);
     digitalWrite(d3, LOW);
     delay(5);
  if (digitalRead(btn) == HIGH){
     io.run();
     int sensorValue = analogRead(temp);
     float voltage = (sensorValue / 4095.0) * 3.3;
     float lectura = (voltage *100.0)+9;
     decenas = lectura/10;
     unidades = lectura-(decenas*10);
     decimal = (lectura*10)-(decenas*100)-(unidades*10);
     canaltemp->save(lectura);
    if (lectura < 22){
     digitalWrite(ledB, HIGH);
     digitalWrite(ledR, LOW);
     digitalWrite(ledG, LOW);
     Serial.print("Temperatura: ");
     Serial.print(lectura);
     Serial.println(" °C");
     ledcWrite(servoCanal, 255);

    }
    else if (lectura<25 && lectura>22){
     Serial.print("Temperatura: ");
     Serial.print(lectura);
     Serial.println(" °C");
     digitalWrite(ledG, HIGH);
     digitalWrite(ledR, LOW);
     digitalWrite(ledB, LOW);
     ledcWrite(servoCanal, 327);
    }
    else{
      Serial.print("Temperatura: ");
      Serial.print(lectura);
      Serial.println(" °C");
      digitalWrite(ledR, HIGH);
      digitalWrite(ledB, LOW);
      digitalWrite(ledG, LOW);
      ledcWrite(servoCanal, 425);
    }
    delay(300);
  }
    }

//▶︎ •၊၊||၊|။|||| |၊၊•  Otras funciones  •၊၊||၊|။||||။‌‌‌‌‌၊|• 

void MostrarNumero(uint8_t numero){
  switch (numero){
    case 0:
    digitalWrite(leda, HIGH);
    digitalWrite(ledb, HIGH);
    digitalWrite(leddp, LOW);
    digitalWrite(ledc, HIGH);
    digitalWrite(ledd, HIGH);
    digitalWrite(lede, HIGH);
    digitalWrite(ledf, HIGH);
    digitalWrite(ledg, LOW);
    break;
    case 1:
    digitalWrite(leda, LOW);
    digitalWrite(ledb, HIGH);
    digitalWrite(leddp, LOW);
    digitalWrite(ledc, HIGH);
    digitalWrite(ledd, LOW);
    digitalWrite(lede, LOW);
    digitalWrite(ledf, LOW);
    digitalWrite(ledg, LOW);
    break;
    case 2:
    digitalWrite(leda, HIGH);
    digitalWrite(ledb, HIGH);
    digitalWrite(leddp, LOW);
    digitalWrite(ledc, LOW);
    digitalWrite(ledd, HIGH);
    digitalWrite(lede, HIGH);
    digitalWrite(ledf, LOW);
    digitalWrite(ledg, HIGH);
    break;
    case 3:
    digitalWrite(leda, HIGH);
    digitalWrite(ledb, HIGH);
    digitalWrite(leddp, LOW);
    digitalWrite(ledc, HIGH);
    digitalWrite(ledd, HIGH);
    digitalWrite(lede, LOW);
    digitalWrite(ledf, LOW);
    digitalWrite(ledg, HIGH);
    break;
    case 4:
    digitalWrite(leda, LOW);
    digitalWrite(ledb, HIGH);
    digitalWrite(leddp, LOW);
    digitalWrite(ledc, HIGH);
    digitalWrite(ledd, LOW);
    digitalWrite(lede, LOW);
    digitalWrite(ledf, HIGH);
    digitalWrite(ledg, HIGH);
    break;
    case 5:
    digitalWrite(leda, HIGH);
    digitalWrite(ledb, LOW);
    digitalWrite(leddp, LOW);
    digitalWrite(ledc, HIGH);
    digitalWrite(ledd, HIGH);
    digitalWrite(lede, LOW);
    digitalWrite(ledf, HIGH);
    digitalWrite(ledg, HIGH);
    break;
    case 6:
    digitalWrite(leda, HIGH);
    digitalWrite(ledb, LOW);
    digitalWrite(leddp, LOW);
    digitalWrite(ledc, HIGH);
    digitalWrite(ledd, HIGH);
    digitalWrite(lede, HIGH);
    digitalWrite(ledf, HIGH);
    digitalWrite(ledg, HIGH);
    break;
    case 7:
    digitalWrite(leda, HIGH);
    digitalWrite(ledb, HIGH);
    digitalWrite(leddp, LOW);
    digitalWrite(ledc, HIGH);
    digitalWrite(ledd, LOW);
    digitalWrite(lede, LOW);
    digitalWrite(ledf, LOW);
    digitalWrite(ledg, LOW);
    break;
    case 8:
    digitalWrite(leda, HIGH);
    digitalWrite(ledb, HIGH);
    digitalWrite(leddp, LOW);
    digitalWrite(ledc, HIGH);
    digitalWrite(ledd, HIGH);
    digitalWrite(lede, HIGH);
    digitalWrite(ledf, HIGH);
    digitalWrite(ledg, HIGH);
    break;
    case 9:
    digitalWrite(leda, HIGH);
    digitalWrite(ledb, HIGH);
    digitalWrite(leddp, LOW);
    digitalWrite(ledc, HIGH);
    digitalWrite(ledd, HIGH);
    digitalWrite(lede, LOW);
    digitalWrite(ledf, HIGH);
    digitalWrite(ledg, HIGH);
    break;
  }

}
