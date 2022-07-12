// -------------------------------------------------------------------------------

#include <Adafruit_NeoPixel.h>
#include <WiFi.h>
#include "time.h"
#include <HTTPClient.h>

const char* ssid       = "xxxxxxxx";
const char* password   = "xxxxxxxx"; 
#define PIN 17

int wc = 0;
boolean ifl = false;

int feel = 0;

int morgen = 0;
int mittag = 0;
int abend = 0;
int nacht = 0;
int regen = 0;
int sonne = 0;

int rd1,rd2,rd3,rd4,rd5,rd6,rd7,rd8,rd9,rd10,rd11,rd12;
int pd1,pd2;
int ef1,ef2;

// -------------------------------------------------------------------------------
 
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(58, PIN, NEO_GRB + NEO_KHZ800);

// -------------------------------------------------------------------------------
 
void setup()
{
Serial.begin(115200);  
Serial.println("Setup...");

pixels.begin(); 
delay(100);

Serial.println("Intro...");

for (int i = 0; i < 3; i++) {    //3 turns

//Serial.println("i: " + String(i));
  
for (int p = 56; p < 58; p++) {
if (i == 0) pixels.setPixelColor(p, pixels.Color(50, 30, 10)); 
if (i == 1) pixels.setPixelColor(p, pixels.Color(30, 50, 100)); 
if (i == 2) pixels.setPixelColor(p, pixels.Color(200, 190, 180)); 
if (i > 0) delay(80 / ((i*2)+1));
if (i > 0) pixels.show(); 
delay(15);
}
for (int p = 0; p < 56; p++) {
if (i == 0) pixels.setPixelColor(p, pixels.Color(50, 30, 10)); 
if (i == 1) pixels.setPixelColor(p, pixels.Color(30, 50, 100)); 
if (i == 2) pixels.setPixelColor(p, pixels.Color(200, 190, 180)); 
if (i > 0) delay(80 / ((i*2)+1));
if (i > 0) pixels.show(); 
delay(15);
}

if (i == 0) {
  delay(50);
  pixels.setPixelColor(0, pixels.Color(50, 30, 10)); 
  delay(50);
  pixels.show();
  delay(800);}
if (i == 1) {delay(300);}

delay(1000);
} //end turns

Serial.printf("Verbinde zu %s ", ssid);
WiFi.begin(ssid, password);
while (WiFi.status() != WL_CONNECTED && wc < 10) {
      delay(500);
      Serial.print(".");
      wc ++;
}

if (wc < 10) {
Serial.println(" verbunden.");
Serial.print("IP-Adresse: ");
Serial.println(WiFi.localIP());
ifl = true;
}
else {
Serial.println(" nicht verbunden.");
ifl = false;
}

if(ifl) {

    HTTPClient http;
 
    http.begin("http://homeserver3/neolamp/ctrl.txt"); //Specify the URL
    int httpCode = http.GET();                                        //Make the request
 
    if (httpCode > 0) { //Check for the returning code
 
        String payload = http.getString();
        Serial.println(payload);
        feel = payload.toInt();
      }
 
    else {
      Serial.println("Fehler bei HTTP-Request");
    }
 
    http.end(); 

WiFi.disconnect(true);
WiFi.mode(WIFI_OFF);
Serial.println("WiFi-Verbindung aufgeloest.");
}

switch (feel){
  case 0:
  Serial.println("feel = 0 - Standard-Programm...");
  break;
  case 1:
  Serial.println("feel = 1 - Morgen-Programm...");
  morgen = 20;
  break;
  case 2:
  Serial.println("feel = 2 - Mittags-Programm...");
  mittag = 60;
  break;
  case 3:
  Serial.println("feel = 3 - Abend-Programm...");
  abend = 50;
  break;
  case 4:
  Serial.println("feel = 4 - Nacht-Programm...");
  nacht = 100;
  break;
  case 5:
  Serial.println("feel = 5 - Regen-Programm...");
  regen = 80;
  break;
  case 6:
  Serial.println("feel = 6 - Sonne-Programm...");
  sonne = 100;
  break;
  case 7:
  Serial.println("feel = 7 - Kein Programm, volle Lichtleistung...");
  break;
  default:
  Serial.println("feel unbestimmt, setze zu feel = 0 - Standard-Programm...");
  feel = 0;
  break;
}

Serial.println("20s Pause...");

delay(20000);

Serial.println("Loop...");

} //end setup

// -------------------------------------------------------------------------------

void loop()
{

pd1= random(500);
delay(90 + pd1);

pd2= random(5);

ef1= random(5);
ef2= random(180);

rd1 = random(57);
rd2 = random(57);
rd3 = random(57);
rd4 = random(57);
rd5 = random(57);
rd6 = random(57);
rd7 = random(57);
rd8 = random(57);
rd9 = random(57);
rd10 = random(57);
rd11 = random(57);
rd12 = random(57);

switch (feel) {
  
case 0:
case 1:
case 2:
case 3:
case 4:
case 5:
case 6:

pixels.setPixelColor(rd1, pixels.Color(200 - (nacht*1.5) - abend - regen - morgen, 190 - nacht - abend - regen, 180 - nacht - abend - regen)); 
pixels.setPixelColor(rd7, pixels.Color(30 + mittag + sonne + morgen, 45, 110 + morgen)); 
pixels.setPixelColor(rd2, pixels.Color(200 - (nacht*1.5) - abend - regen - morgen, 190 - nacht - abend - regen, 180 - nacht - abend - regen)); 
pixels.setPixelColor(rd8, pixels.Color(10 + mittag + sonne + morgen + abend + regen, 25, 160 - abend - regen)); 
pixels.setPixelColor(rd3, pixels.Color(200 - (nacht*1.5) - abend - regen - morgen, 190 - nacht - abend - regen, 180 - nacht - abend)); 
pixels.setPixelColor(rd11, pixels.Color(0, 0, 0)); 
if (pd2 == 1) {
delay(200);
pixels.show();
delay(200);
}
pixels.setPixelColor(rd4, pixels.Color(200 - (nacht*1.5) - abend - regen - morgen, 190 - nacht - abend - regen, 180 - nacht - abend)); 
pixels.setPixelColor(rd10, pixels.Color(150 + (mittag/2) + (sonne/2) + (morgen/2), 100, 10)); 
pixels.setPixelColor(rd5, pixels.Color(200 - (nacht*1.5) - abend - regen - morgen, 190 - nacht - abend - regen, 180 - nacht - abend)); 
pixels.setPixelColor(rd9, pixels.Color(60 + mittag + sonne + morgen, 40, 10 + morgen)); 
pixels.setPixelColor(rd6, pixels.Color(200 - (nacht*1.5) - abend - regen - morgen, 190 - nacht - abend - regen, 180 - nacht - abend)); 
pixels.setPixelColor(rd12, pixels.Color(200 - (nacht*1.5) - abend - regen - morgen, 200 - nacht - abend - regen, 200 - nacht - abend)); 
delay(200);
pixels.show();

if (ef1 == 1) {
delay(1000);
}

if (ef2 == 1) {
for (int p = 56; p < 58; p++) {
pixels.setPixelColor(p, pixels.Color(200 - (morgen * 2) - (nacht * 2) - abend - (regen * 2.5), 190 - nacht - morgen - abend - (regen * 0.5), 180 - nacht - abend + regen)); 
delay(50);
pixels.show();
}
for (int p = 0; p < 56; p++) {
pixels.setPixelColor(p, pixels.Color(200 - (morgen * 2) - (nacht * 2) - abend - (regen * 2.5), 190 - nacht - morgen - abend - (regen * 0.5), 180 - nacht - abend + regen)); 
delay(50);
pixels.show();
}
delay(2000);
}

if (ef2 == 2) {
for (int p = 56; p < 58; p++) {
pixels.setPixelColor(p, pixels.Color(50 + mittag + sonne + morgen - (nacht / 2), 30 + sonne, 10 + regen + nacht)); 
delay(50);
pixels.show();
}
for (int p = 0; p < 56; p++) {
pixels.setPixelColor(p, pixels.Color(50 + mittag + sonne + morgen - (nacht / 2), 30 + sonne, 10 + regen + nacht)); 
delay(50);
pixels.show();
}
delay(2000);
}

if (ef2 == 3) {
for (int p = 56; p < 58; p++) {
pixels.setPixelColor(p, pixels.Color(30 + mittag + sonne + morgen, 50 + sonne, 100 - abend - nacht)); 
delay(50);
pixels.show();
}
for (int p = 0; p < 56; p++) {
pixels.setPixelColor(p, pixels.Color(30 + mittag + sonne + morgen, 50 + sonne, 100 - abend - nacht)); 
delay(50);
pixels.show();
}
delay(2000);
}

if (ef2 == 4) {
for (int p = 56; p < 58; p++) {
pixels.setPixelColor(p, pixels.Color(20 + abend + mittag + sonne, 20 + regen + mittag + morgen + sonne, 20 + nacht + regen + sonne + morgen)); 
delay(50);
pixels.show();
}
for (int p = 0; p < 56; p++) {
pixels.setPixelColor(p, pixels.Color(20 + abend + mittag + sonne, 20 + regen + mittag + morgen + sonne, 20 + nacht + regen + sonne + morgen)); 
delay(50);
pixels.show();
}
delay(2000);
}

if (ef2 == 5) {


if (feel == 0)
{
//Standard-Programm

for (int p = 56; p < 58; p++) {
pixels.setPixelColor(p, pixels.Color(random(200 - (nacht * 2) - abend - regen), random(200 - nacht - abend), random(200 - nacht - abend))); 
delay(50);
pixels.show();
}
for (int p = 0; p < 56; p++) {
pixels.setPixelColor(p, pixels.Color(random(200 - (nacht * 2) - abend - regen), random(200 - nacht - abend), random(200 - nacht - abend))); 
delay(50);
pixels.show();
}

delay(1000);
}


}


if (ef2 == 6) {
for (int p = 56; p < 58; p++) {
pixels.setPixelColor(p, pixels.Color(200 - (morgen * 2) - (nacht * 2) - (abend * 2) - (regen * 2.5), 0 + sonne + mittag + (morgen * 2) + nacht, 0 + sonne + morgen + nacht + regen)); 
delay(50);
pixels.show();
}
for (int p = 0; p < 56; p++) {
pixels.setPixelColor(p, pixels.Color(200 - (morgen * 2) - (nacht * 2) - (abend * 2) - (regen * 2.5), 0 + sonne + mittag + (morgen * 2) + nacht, 0 + sonne + morgen + nacht + regen)); 
delay(50);
pixels.show();
}
delay(2000);
}

if (ef2 == 7) {
for (int p = 56; p < 58; p++) {
pixels.setPixelColor(p, pixels.Color(0 + mittag + sonne + morgen, 200 - (nacht * 2) - abend - regen - mittag, 0 + regen + nacht)); 
delay(50);
pixels.show();
}
for (int p = 0; p < 56; p++) {
pixels.setPixelColor(p, pixels.Color(0 + mittag + sonne + morgen, 200 - (nacht * 2) - abend - regen - mittag, 0 + regen + nacht)); 
delay(50);
pixels.show();
}
delay(2000);
}

if (ef2 == 8) {
for (int p = 56; p < 58; p++) {
pixels.setPixelColor(p, pixels.Color(0 + mittag + sonne + morgen, 0 + mittag + morgen, 200 - nacht - abend - regen - mittag - morgen)); 
delay(50);
pixels.show();
}
for (int p = 0; p < 56; p++) {
pixels.setPixelColor(p, pixels.Color(0 + mittag + sonne + morgen, 0 + mittag + morgen, 200 - nacht - abend - regen - mittag - morgen)); 
delay(50);
pixels.show();
}
delay(2000);
}

if (ef1 == 1) {
delay(1000);

}

break;

case 7:
break;
default:
break;
}

}

// -------------------------------------------------------------------------------
