# Engima Machine Simulator

This is the program I wrote to simulate the Engima I. It supports Rotors I through V, reflector types B and C, plugboard mappings, and both ring setting and rotor position. It also properly simulates the double shift issue that occurred with the original ratchet and pawl operated Enigma Machines. 

This program currently only runs on Windows machines, since I use the msvcrt Windows library to capture keyboard input, but it could be modified to run on Linux pretty easily.

## Example

Here is an example of encoding and decoding using the Enigma Machine. This example also shows an [online Engima Machine Simulator](https://piotte13.github.io/enigma-cipher/) next to it for comparison/validation.

### Encoding

For this example I encode the message "TEST" using the following settings:

- Rotor Selection and Order
  - Rotor IV, Rotor I, Rotor II
- Reflector B
- Ring Setting
  - E (4), K (10), B (1)
- Rotor Position
  - G, T, E
- Plugboard Connections
  - I <==> O
  - G <==> T
  - K <==> L

Here are both machines tuned to these settings, waiting for input
![Before Input](BeforeEncode.PNG?raw=true "Enigma Machine Set Up")

Then, after entering the text "TEST" into both machines:
![After Input](AfterEncode.PNG?raw=true "Enigma Machine Results")

Thus, the text "TEST" encoded using the settings shown results in "APGF". Also, note that the rotor positions of the machine have changed due to text being entered.

### Decoding

Decoding the message requires entering the encoded message into an Enigma Machine using the exact same settings that were present when the message was encoded.

Both machines reset to the original settings
![Before Decode](BeforeDecode.PNG?raw=true "Enigma Machine Set Up Again")

Then, after entering the text "APGF" into both machines:
![After Decode](AfterDecode.PNG?raw=true "Enigma Machine Decoded Results")

The Engima Machine outputs the text "TEST", which is our decoded message.