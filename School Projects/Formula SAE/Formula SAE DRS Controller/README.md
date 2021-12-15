# Formula SAE DRS Controller

This is the DRS (Drag Reduction System) controller I wrote for Missouri S&T's Formula SAE team in the Spring 2021 semester. The point of this is to raise the rear wing when the driver holds a button on the steering wheel to reduce drag on the car when not cornering. This was done using a Teensy 3.2 microcontroller, 2 CLS-12V7346 coreless high torque servos, and a 4-bar linkage system to move the wings when the servos turn their shafts. I programmed the controller and the mechanical engineering students designed the 4-bar linkage.

The DRS button was wired directly to the microcontroller, and I implemented simple debouncing logic for the controller to prevent stuttering with the button input. Button bouncing could cause a few problems with the car. A flickering input could potentially damage the servos or cause the wing to go outside the intended angular range it was designed for, which could damage it. Also, without debouncing, any unintended noise could accidentally trigger the DRS without the driver actually pushing the button. Debouncing reduces the odds of these problems occurring.

A short video of the DRS being tested can be found [here](DRS%20Shakedown.mp4).
