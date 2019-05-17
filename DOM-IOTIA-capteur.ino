/* Eleve : GRANET
 * Class : Lp IOTIA 2019
 * Etablisement IUT Nice-Sophia
 */
#include <M5Stack.h>
#include "BluetoothSerial.h"
#include <OneWire.h>
#include <DallasTemperature.h>
/****************************Initialisation du Bluetooth*****************************/
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif
BluetoothSerial SerialBT;
/****************************Capteur de pluie*****************************/
const int capteur_D = 3;  // pin connecté à la sortie digital du capteur
const int capteur_A = 35; // pin connecté à la sortie analogique du capteur
int val_analogique;       //int de la valeur analogique du capteur 
/*************************************************************************/

/****************************Capteur de DS18B20*****************************/
  #define ONE_WIRE_BUS 22               // DS18B20 on arduino pin2 corresponds to D4 on physical board
  OneWire oneWire(ONE_WIRE_BUS);        //Difinition du bus OneWire
  DallasTemperature DS18B20(&oneWire);  //declaration du Capteur sur le bus OneWire
/***************************************************************************/

/****************************Capteur de Luminosite*****************************/
  int LuminositerPinA = 36; //valeur annalogique de la photo-resistance
/*****************************************************************************/
void setup()
{
  SerialBT.begin("gaetan2"); //Bluetooth device name
  M5.begin();                //Start M5Stack
  M5.Speaker.mute();
  Serial.begin(115200);      //Vitesse du port serie
  Serial.println("Demarage de l'application ");
  /****************************Capteur de pluie*****************************/
  pinMode(capteur_D, INPUT);  //D0 : Sortie digital, qui envoi une valeur numérique 0 ou 1.
  pinMode(capteur_A, INPUT);  //A0 : Sortie analogique, qui permet d’avoir une valeur variable et graduelle.
                              //ici A0 non utiliser
  /*************************************************************************/
}


void loop()
{
   /****************************Declaration des variable*****************************/
  String pluie = "";        //Instaciation de la variable Pluie
  float Temperature = 0.0;  //Instaciation de la variable Pluie 
  int Luminosite = 0;       //Intanciation de la variable Luminosite
  String Humidite = "";     //Intanciation de la variable Humidite

  //---------------------------------START---------------------------------
  M5.Speaker.mute();
  M5.Lcd.clear();                     //Effacement des valeurs LCD
  M5.Lcd.setCursor(0,0);              //Emplacement de l'ecriture 
  M5.Lcd.setTextSize(2);              //Taille d'ecriture
  
  //float celsius;
  int count = DS18B20.getDS18Count(); //nombre de device connecte
  DS18B20.begin();                    //Demarer le DS18B20
 /****************************Capteur de pluie*****************************/
  if(digitalRead(capteur_D) == HIGH) // Le capteur est actif à l'Haut
  {
    pluie = "OUI";
    Serial.println("Valeur digital : mouille");  
  }
  else
  {
    pluie = "NON";
    Serial.println("Valeur digital : Pas mouille");
  }
  SerialBT.println("T = ");
  SerialBT.println(pluie);
  M5.Lcd.print("Pluie       : ");
  M5.Lcd.println(pluie);
  delay(5000);
  /****************************Capteur de DS18B20*****************************/
  if (count > 0) // si 1 capteur de temperature est trouve
  {
    DS18B20.requestTemperatures(); //on obtient la temperature
    for (int i=0; i < count; i++) 
    {
      Temperature = DS18B20.getTempCByIndex(i);
      Temperature = round(Temperature);
      //Temperature = celsius;
      Serial.print("Temperature : ");
      Serial.println(Temperature);
      M5.Lcd.print("Temperature : ");
      M5.Lcd.println(Temperature);
      SerialBT.println(Temperature);
    }
  }
  delay(5000);
  /****************************Capteur de Luminosite*****************************/
  Luminosite = analogRead(LuminositerPinA);  //Lecture analogique de la Photo-resistance
  M5.Lcd.print("Lumiere     : ");
  M5.Lcd.println(Luminosite);
  Serial.print("Lumiere     : ");
  Serial.println(Luminosite);
  SerialBT.println(Luminosite);
  /*************************************************************************/
  delay(5000); // 5 secondes soit 5000 millisecondes
}
