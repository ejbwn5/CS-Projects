# Formula SAE Lap Timer

This is the lap timer I designed for my school's Formula SAE racing team. This project showcases my abilities in both software and hardware design. 

## Purpose

This project was to help my school's Formula team with their lap timing during testing. They originally had a wired microcontroller which connected to an IR sensor and required someone to hand-copy the lap times down in an excel sheet. Also, in the event that the team was testing acceleration, they needed a several hundred foot long cable to connect to a second IR sensor at the end of the strip.

My job was to create a wireless solution for them. This way, there is no need to drag a long cable out to the IR sensors, and the person logging the data can stand further away from the course, which makes it safer. 

## Hardware

This project used 3 Arduino Nanos connected to NRF24L01 2.4GHz RF transceivers. Two of them were used as transmitters and were connected to the IR sensors on the course. The other was used as a receiver, and was connected via USB to a laptop. The transceivers communicate with the Arduino using the SPI protocol. The receiver Arduino communicates with the laptop over Serial USB. A 1000µF capacitor is connected directly to the 3.3v and ground pins of each RF transceiver to help stabilize power during transmission.

## Software 

I designed a GUI in tKinter, a Python library, to communicate with the receiver Arduino and display the lap times.