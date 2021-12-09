# Edputer Video Card

First and foremost, I want to clarify that the original circuit schematic for this VGA card is not mine. I did however design the PCB for this circuit, and set it up to connect with Edputer. The [original VGA circuit](https://www.youtube.com/watch?v=l7rce6IQDWs) was designed by a Youtuber named Ben Eater. His design was only intended to display an image from a single EEPROM. I extended this to connect to Edputer, and is able to read from one of two RAM buffers.

This video card is designed to display a 100x75px VGA image. The circuit actually uses the 800x600 VGA resolution mode, but with a slower clock rate to compensate.

## PCB

Here are sample images of what the PCB I designed looks like. The actual gerber files needed to print this PCB are located in the [Gerber](Gerber/) folder.

![Top Side](top.svg?raw=true "Top Side")

![Bottom Side](bottom.svg?raw=true "Bottom Side")