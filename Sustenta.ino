/**
 * 
 * 
 * https://create.arduino.cc/projecthub/iotboys/how-to-use-ds18b20-water-proof-temperature-sensor-2adecc
 * 
 * 4.7 [khom] pull up resistor is needed between signal and 5V
 * 
 * Error: -127 °C Check Wiring!  
 * 
 * The SD circuit:
 * SD card attached to SPI bus as follows:
 ** MOSI - pin 11
 ** MISO - pin 12
 ** CLK - pin 13
 * 
 */

#include <OneWire.h>
#include <DallasTemperature.h>
#include <SPI.h>
#include <SD.h>

// Sets data rate, rates availables 300, 600, 1200, 2400, 4800, 9600, 14400, 19200, 28800, 38400, 57600, or 115200
int dataRate = 1200;

// minSoilHumidity measured in V [Should be a Low Voltage]
//float minSoilHumidity = 1.4; // 1 --> The sensor is into the water
                             //   5 --> The sensor is out the water
float minSoilHumidity = 2.35;
float Celcius = 0;

// ### Pins [Analog pins must begin with "A"]
int inSignalPin = A0;
int out_outOfLimits = 12;
int out_insideOfLimits = 13; 
#define ONE_WIRE_BUS 5
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature tempSensors(&oneWire);
const int chipSelect = 8;

// ### Functions

float toAnalogVoltage(int analogInput){
  /*
   * @param:    analogInput     Given by analogRead(pin)
   * @return:   analogVoltage   Analog voltaje in the pin     
  */ 
  float analogVoltage = analogInput*5.0/1024;
  return analogVoltage;
  }

float toHumidity(int analogInput){
  float humidity = -0.106*analogInput+140.28; 
  if(humidity > 100.){
    humidity = 100.;
    }
  return humidity;
  }

void setup(void)
{  
  pinMode(SS, OUTPUT);
  Serial.begin(dataRate);
  tempSensors.begin();
  pinMode(inSignalPin, INPUT);
  pinMode(out_outOfLimits, OUTPUT);
  pinMode(out_insideOfLimits, OUTPUT);

  Serial.print("Initializing SD card...");
  if (!SD.begin(chipSelect)) {
  Serial.println("Card failed, or not present");
  // don't do anything more:
  while (1);
  }
  Serial.println("card initialized.");
  
}

void loop(void)
{ 
  String dataString = "";
  tempSensors.requestTemperatures(); 
  Celcius = tempSensors.getTempCByIndex(0);

  int analogInput = analogRead(inSignalPin);
  float humidity = toHumidity(analogInput);

/*
  if (humidity >= minSoilHumidity){
  
    digitalWrite(out_outOfLimits, HIGH);
    digitalWrite(out_insideOfLimits, LOW);
    }

   else{
    digitalWrite(out_outOfLimits, LOW);
    digitalWrite(out_insideOfLimits, HIGH);
    }
*/

  /*
  //DEBUG
  Serial.print("Hum ");
  Serial.print(humidity);
  Serial.print(" Temp ");
  Serial.println(Celcius);
  */
  dataString = String(humidity) + "," + String(Celcius) + "\n";

  File dataFile = SD.open("datalog.txt", FILE_WRITE);

  // if the file is available, write to it:
  if (dataFile) {
    dataFile.println(dataString);
    dataFile.close();
    // print to the serial port too:
    Serial.println(dataString);
  }
  // if the file isn't open, pop up an error:
  else {
    Serial.println("error opening datalog.txt");
    dataFile.close();
  }

  delay(900000);
  
}
