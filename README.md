# Motion-Sensor
A small arduino project to detect movement of a person using a PIR sensor and alerting via a small buzzer and some flashing LEDs. For the LED indication, I decided to make the LEDs fade in and out, as opposed to On and Off. 

I added a button to toggle the sensor into silent mode, which is indicated by a green light when the device is in silent mode. This simply stops sounds. 

![alt text](https://i.ibb.co/jy55sTD/IMG-6252.jpg "It's not a bomb!")

Note: my PIR sensor is set that, when there's movement, it stays active for a few seconds after the movement stops. Some return true when the movement stops. Mine has a delay. This can be changed, but you need some l33t soldering skills, or one with jumpers. 

## Parts
This project makes use of an Arduino UNO, but can be used on any Arduino. I've run it on a Particle Photon as well.

* 1 xPIR Motion detector sensor
* 3 x LEDs (I used Red and Blue, as they're used as an alarm, and it reminded me of a cop car, and one for the 'Silent' mode)
* 3 x 220ohm resistors
* 1 x Pizzo buzzer
* 1 x toggle button
* 1 x Breadboard (I didn mine on a half size)
* Around 10 jumper wires.

## Wiring it up
The while thing sits on a bradboard, with the sensor hanging lose, so that it can be moved around. I'd put longer leads on the PIR, which allows it to be moved independently of the board.

I use the following pins:

* Buzzer: A0
* LED 1: 10
* LED 2: 9
* PIR: 4

### The Sketch.

![alt text](https://i.ibb.co/HFVdrcj/Motion-Sensor-No-Screen-bb.jpg "High quality")
