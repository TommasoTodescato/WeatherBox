# WeatherBox
A tool to measure real time weather related informations, capable of bluetooth communication.
To be used with [WeatherTerminal](https://github.com/TommasoTodescato/WeatherTerminal.git).

## Connection
### Stock version:
1. Arduino UNO R3
2. HC-05 Module for bluetooth communication
	- (Pin 10 RX -> TX / Pin 11 TX -> Voltage divider to 3.3V -> RX)
3. MQ-2 Sensor for gas detection
	- (Analog Output -> Arduino A5)
4. Photoresistor for light level measurement
	- (Pull up 10kΩ, output to Arduino A4)

### WeatherTerminal:
Every bluetooth terminal which can receive or send text should work.
However, if you want to have sound support, it is reccomended to use [WeatherTerminal](https://github.com/TommasoTodescato/WeatherTerminal.git).

## General Behaviour:
2 Modalità:
Output

Modalità verbosa
Modalità silenziosa (solo suono)

Input

Entrare in modalità di input
Calibrare con percentuali preimpostate
Quando si ha finito si esce e si torna in modalità output
