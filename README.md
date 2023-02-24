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
Every bluetooth terminal that can receive or send text should work.
However, if you want to have sound support, it is reccomended to use [WeatherTerminal](https://github.com/TommasoTodescato/WeatherTerminal.git).

## General Behaviour:
The nature of the project is completely modular, and it's structured so that it should be pretty easy to add your own sensors.
In fact, it is sufficient to use the `sensor` struct.

``
struct sensor {const int pin; int value; int limit;}
``

Whe the limit is surpassed, TX sends a signal that is interpreted by WeatherTerminal as a sound, and so it reproduces one.
You can calibrate your treshold for every sensor with the configuration mode.

## Configuration mode:
There are 2 main modes of execution:
1. Standard mode
2. Configuration mode

In configuration mode you can calibrate your sensors during runtime.
To enter configuration mode, send `1` in the terminal at any time while you are connected to WeatherBox.
Once you are in, you will have all the instructions needed.