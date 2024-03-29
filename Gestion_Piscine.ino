

// Date and time functions using a DS3231 RTC connected via I2C and Wire lib
#include <Wire.h>
#include "RTClib.h"
#include <string.h>
#include <stdio.h>
RTC_DS3231 rtc;

char daysOfTheWeek[7][12] = {"Dimanche", "Lundi", "Mardi", "Mercredi", "Jeudi", "Vendredi", "Samedi"};
char monthOfTheYear[12][4] = {"Janv", "Fev", "Mar", "Avr", "Mai", "Juin", "Juil", "Aout", "Sept", "Oct", "Nov", "Dec"};
// Déclaration de la variable reçue par le port serie

String STRrecu = " " ;

unsigned long previous_time=0;
int NJour =0;
char STRenvoye [100];
int Jour =0;
int Mois =0;
int Annee = 0;
int Heure =0;
int Minute =0;
int VarInt=0;


void setup() {

//#ifndef ESP8266
// while (!Serial); // for Leonardo/Micro/Zero
//#endif
Serial.begin(9600);


delay(3000); // wait for console opening

 if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }
  
if (rtc.lostPower()) {
    Serial.println("RTC lost power, lets set the time!");
    // following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // This line sets the RTC with an explicit date & time, for example to set
    // January 21, 2014 at 3am you would call:
    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
  }


Serial.setTimeout(100);
pinMode(8,OUTPUT);
}





void loop() {


STRrecu= Serial.readString();

unsigned long current_time=millis();

if (current_time-previous_time>60000)
{
  
  previous_time=current_time;


  DateTime now = rtc.now(); 

// Affichage du numéro dujour de la semaine
  VarInt = now.day();
  sprintf(STRenvoye,"txtNJour.txt=\"%d\"",VarInt);
  
  Serial.print(STRenvoye);
  Serial.write(0xFF);
  Serial.write(0xFF);
  Serial.write(0xFF);

// Affichage du jour de la semaine
  Jour = daysOfTheWeek[now.dayOfTheWeek()];
  sprintf(STRenvoye,"txtJour.txt=\"%s\"",Jour);
  Serial.print(STRenvoye);
  Serial.write(0xFF);
  Serial.write(0xFF);
  Serial.write(0xFF);

//Affichage du Mois

VarInt = now.month();
switch (VarInt) {
  case 1:
    Serial.print("txtMois.txt=\"Janv\"");
    break;
  case 2:
    Serial.print("txtMois.txt=\"Fev\"");
    break;
   case 3:
    Serial.print("txtMois.txt=\"Mars\"");
    break; 
       case 4:
    Serial.print("txtMois.txt=\"Avr\"");
    break; 
       case 5:
    Serial.print("txtMois.txt=\"Mai\"");
    break; 
       case 6:
    Serial.print("txtMois.txt=\"Juin\"");
    break; 
       case 7:
    Serial.print("txtMois.txt=\"Juil\"");
    break; 
       case 8:
    Serial.print("txtMois.txt=\"Aout\"");
    break; 
       case 9:
    Serial.print("txtMois.txt=\"Sept\"");
    break; 
       case 10:
    Serial.print("txtMois.txt=\"Oct\"");
    break; 
       case 11:
    Serial.print("txtMois.txt=\"Nov\"");
    break; 
       case 12:
    Serial.print("txtMois.txt=\"Dec\"");
    break; 
  
}
  Serial.write(0xFF);
  Serial.write(0xFF);
  Serial.write(0xFF);


// Affichage l'année
  VarInt = now.year();
  sprintf(STRenvoye,"txtAn.txt=\"%d\"",VarInt);
  
  Serial.print(STRenvoye);
  Serial.write(0xFF);
  Serial.write(0xFF);
  Serial.write(0xFF);


// Affichage de l'heure
  VarInt = now.hour();

if (VarInt<10) {

  sprintf(STRenvoye,"txtHeure.txt=\"0%d\"",VarInt); 
 }
 else {
 sprintf(STRenvoye,"txtHeure.txt=\"%d\"",VarInt);
 }    
  Serial.print(STRenvoye);
  Serial.write(0xFF);
  Serial.write(0xFF);
  Serial.write(0xFF);
 

 // Affichage des minutes
 VarInt = now.minute();

if (VarInt<10) {

sprintf(STRenvoye,"txtMinute.txt=\"0%d\"", VarInt); 
 }
 else {
 sprintf(STRenvoye,"txtMinute.txt=\"%d\"", VarInt);
 }    


  Serial.print(STRenvoye);
  Serial.write(0xFF);
  Serial.write(0xFF);
  Serial.write(0xFF); 

}
//Fin de la  Mise à jour Date / Heure


if (((STRrecu)==("LedOn")))
{
  digitalWrite(8,HIGH);

  Serial.print("t0.txt=\"ON\"");
  Serial.write(0xFF);
  Serial.write(0xFF);
  Serial.write(0xFF); 
  delay (100);

}
if (((STRrecu)==("Ledoff")))
{
  digitalWrite(8,LOW);

Serial.print("t0.txt=\"OFF\"");
Serial.write(0xFF);
Serial.write(0xFF);
Serial.write(0xFF);
 delay (100);
}

}
