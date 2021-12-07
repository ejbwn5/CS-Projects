# Formula SAE Lap Timer Software

This is the Python program I wrote using tKinter to display and modify the data collected from the Arduinos. It logs everything it receives from the Arduinos in the Logs folder, and you can save the data sheet as an Excel file in the Results folder.

This program was honestly a massive pain to write. It required a ton of workarounds to get serial communication to work, and the UI was really hard to get working properly. Making scalable interfaces is a lot harder than I anticipated. I ended up rewriting this program a couple times because I tried changing it to be permanently 1920x1080, but ultimately rewrote it to be scalable. The scaling could still use some work, but it's better than having a static resolution. Overall, all I can say is if I were to do this again, I would absolutely use a different graphical interface library.

Here is a picture of the interface.

![User Interface](GUI.PNG?raw=true "User Interface")


In the results folder are some sample Excel sheets output by this program. I recorded some of my roommate's model trains' lap times around a short loop track for testing.

The Logs folder is basically just full of random logs taken during development testing. 