#include <SoftwareSerial.h>

SoftwareSerial btSerial(10, 11);  // RX | TX

struct sensor
{
  const int pin;
  int value;
  int limit;
};

sensor gas = { 5, 0, 450 };
sensor light = { 4, 0, 700 };
String mainMode = "0\r\n";

int calibrateSensor(int limit)
{
  String input = "1\r\n";
  int newLimit = limit;
  btSerial.println("+/-: 50 up/down | 0: save");
  btSerial.print("Current treshold: ");
  btSerial.println(limit);
  while (input != "0\r\n")
  {
    while (!btSerial.available());
    input = btSerial.readString();
    if (input == "+\r\n")
    {
      newLimit = newLimit + 50;
    }
    else if (input == "-\r\n")
    {
      newLimit = newLimit - 50;
    }
  }
  btSerial.print("New treshold: ");
  btSerial.println(newLimit);
  return newLimit;
}

void configurationInstructions()
{
  btSerial.println("0 -> Quit");
  btSerial.println("1 -> Calibrate gas sensor");
  btSerial.println("2 -> Calibrate light sensor");
}

void setup()
{
  btSerial.begin(115200);
}

void loop()
{
  if (btSerial.available())
  {
    mainMode = btSerial.readString();
  }

  //  Standard mode
  if (mainMode == "0\r\n")
  {
    gas.value = analogRead(gas.pin);
    light.value = analogRead(light.pin);
    btSerial.print("Gas: ");
    btSerial.println(gas.value);
    btSerial.print("Light: ");
    btSerial.println(light.value);
    if (gas.value > gas.limit || light.value > light.limit)
    {
      btSerial.println("HIGH");
    }
    delay(1500);
  }
  
  //  Configuration Mode
  else if (mainMode == "1\r\n") 
  {
    String confMode = "3\r\n";
    btSerial.println("CONFIGURATION MODE");
    configurationInstructions();
    while (confMode != "0\r\n")
    {
      while (!btSerial.available());
      confMode = btSerial.readString();
      if (confMode == "1\r\n")
      {
        btSerial.println("Gas Level configuration");
        gas.limit = calibrateSensor(gas.limit);
        configurationInstructions();
      }
      else if (confMode == "2\r\n") 
      {
        btSerial.println("Light level configuration");
        light.limit = calibrateSensor(light.limit);
        configurationInstructions();
      }
    }
    btSerial.println("Configuration successfull...");
    mainMode = "0\r\n";
  }
}