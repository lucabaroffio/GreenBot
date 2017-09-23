# GreenBot: open-source, Arduino-based lawn mower robot

GreenBot is an open-source lawn mower robot based on Arduino. The first prototype features two brushed motors to move the robot, and one brushless motor for the blade.

## Ingredients

### Brain

[Arduino Mega 2560 Rev3](https://www.arduino.cc/en/Main/arduinoBoardMega2560/) Choosing the brain was a no brainer :-)

### Moving the robot

[Two 9V, 86rpm brushed motors](https://www.kiwi-electronics.nl/dc-motor-25mm-9v-86rpm?lang=en) help us move the 2WD robot. We don't need high speed, I would say 30-100rpm. But we need a good torque to move a few kilos up and down our (hilly) yards.

As the motors' stall current is reported to be 2.7A, we need [a powerful motor driver](https://www.sparkfun.com/products/10182). 

### Cutting the grass

The blade is work in progress. Still, based on a quick research, it looks like we need high speed, in the range of 2k-4k rpm.
I am currently testing a brushless motor, namely, the [Quanum MT Series 4108](https://hobbyking.com/en_us/quanum-mt-series-4108-370kv-brushless-multirotor-motor-built-by-dys.html).
It spins at 370 rpm per Volt provided. It means that we can achieve around 3700rpm @ 10V. Stall current is about 17A. 

To drive the brushless motor, I use a [20A ESC produced by HobbyKing](https://hobbyking.com/en_us/hobby-king-20a-esc-3a-ubec.html?___store=en_us).

### Battery

I am using a spare [Roomba Battery](https://www.amazon.com/Tenergy-3500mAh-Battery-Advanced-Replacement/dp/B003MXMWQ2). It is a 12-cell NiMH battery with a nominal voltage of 14.4V

## Schematics

Coming soon.
