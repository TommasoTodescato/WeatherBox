#include <SoftwareSerial.h>

char mainMode = "1";
/*  MODE:
  0: STANDARD
  1: CONFIGURATION
*/

SoftwareSerial btSerial(10, 11);  // RX | TX

struct sensor 
{
  const int pin;
  int value;
  int limit;
};

sensor gas = {5, 0 , 450};
sensor light = {4, 0, 700};

int calibrateSensor(int limit)
{
  char input = "1";
  int newLimit = limit;
  btSerial.println("+/-: 50 up/down | 0: save");
  btSerial.print("Current treshold: ");
  btSerial.println(limit);
  while(input != "0")
  {
    while(!btSerial.available());
    input = (char)btSerial.read();
    if(input == "+")
    {
      newLimit = newLimit + 50;
    }
    else if(input == "-")
    {
      newLimit = newLimit - 50;
    }
  }
  btSerial.print("New treshold: ");
  btSerial.println(input);
  return newLimit;
}



void setup()
{
  btSerial.begin(115200);
}

void loop()
{
  if(btSerial.available())
  {
    mainMode = (char)btSerial.read();
  }
  //  Standard mode
  if(mainMode == "0")
  {
    gas.value = analogRead(gas.pin);
    light.value = analogRead(light.pin);
    btSerial.print("Gas: ");
    btSerial.println(gas.value);
    btSerial.print("Light: ");
    btSerial.println(light.value);
    if(gas.value > gas.limit || light.value > light.limit)
    {
      btSerial.println("ABOVE");
    }
    delay(2000);
  }
  //  Configuration Mode
  else if(mainMode == "1")
  {
    char confMode = "3";
    btSerial.println("CONFIGURATION MODE\n \
    0 -> Quit\n \
    1 -> Calibrate Gas sensor\n \
    2 -> Calibrate Light sensor\n \
    ");
    while(confMode != 0)
    {
      while(!btSerial.available());
      confMode = (char)btSerial.read();
      if(confMode == "1")
      {
        btSerial.println("Gas Level configuration");
        gas.limit = calibrateSensor(gas.limit);
      }
      else if(confMode == "2")
      {
        btSerial.println("Light level configuration");
        light.limit = calibrateSensor(light.limit);
      }
    }
  }
}