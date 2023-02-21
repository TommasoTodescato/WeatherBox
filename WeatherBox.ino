#include <SoftwareSerial.h>

#define gasPin 5
#define lightPin 4
int gasValue;
int lightValue;
int gasLimit = 450;
int lightLimit = 700;
char calibrationInput;
char mode = "1";
/*  MODE:
    1/(ANY): SILENT
    2: VERBOSE
    3: CONFIGURATION
*/
char configurationMode = "0";
SoftwareSerial btSerial(10, 11);  // RX | TX

void setup()
{  
  // pinMode(7, OUTPUT);
  btSerial.begin(115200);
}

void loop()
{
  if(btSerial.available())
  {
    mode = (char)btSerial.read();
  }
  if(mode == "3")
  {
    btSerial.println("CONFIGURATION MODE\n \
    0 -> Quit without saving\n \
    1 -> Calibrate Gas sensor\n \
    2 -> Calibrate Light sensor\n \
    ");
    while(!btSerial.available()); //(Waits for input)
    configurationMode = (char)btSerial.read();
    switch(configurationMode)
    {
      case "1":
        btSerial.println("+/-: 50 up/down | 0: save");
        btSerial.print("Current level:");
        btSerial.println(gasLimit);
        while(calibrationInput != "0")
        {
          while(!btSerial.available());
          calibrationInput = (char)btSerial.read();
        }

        
        break;
      case "2":

        break;
    }
  }
  else if(mode == "2")
  {
  }
  else

  gasValue = analogRead(gasPin);
  lightValue = analogRead(lightPin);
  btSerial.print("Gas:");
  btSerial.println(gasValue);
  btSerial.print("Light:");
  btSerial.println(lightValue);
  delay(2000);
  

  //  (Test to turn on led and get input)
  // if (mySerial.available())
  // {
  //   char inChar = (char)mySerial.read();
  
  //   if(inChar == "1")
  //     digitalWrite(7, HIGH);  
  //   else if(inChar == "0")
  //     digitalWrite(7, LOW);
  //   inChar = "";
  // }
}