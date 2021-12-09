# Edputer Emulator

This is the emulator I wrote in C++ to simulate Edputer. I made this in Visual Studio 2015, and I used the SDL library for the graphics simulation.

This emulator runs Edputer programs which are stored in the form of **Code.bin** and **Arg.bin** machine code files. These files would normally be written to 16K EEPROMS and inserted into the program slots on the physical board.

## Instruction Decoding

This emulator used to use the **EdputerCPU.bin** file to properly simulate the instruction decoding for every instruction, including subclock simulation, but it had incredibly poor performance, as emulators often do. I have since reworked the emulator to use a more optimized approach where it simply calculates the equivalent operation based on the opcode for each instruction. 

However, I'm still including the **EdputerCPU.bin** file for completeness, since it's needed for the real physical Edputer. It can be found in the [Instruction Set](../Instruction%20Set/) folder.


## Execution

To use this, you need the **EdputerEmulator.exe**, **SDL2.dll**, and the **Code.bin** and **Arg.bin** files in the same directory.

Since not everyone has Visual Studio, I included a precompiled executable in the x64/Release folder.

Also, for some reason SDL2 runs faster when you first give it focus. This means that if you click and hold the mouse button in the window, then move the mouse off screen and release, the SDL2 window will run faster. This is a pretty strange effect, but I actually find it very useful since the emulator is usually fairly slow, and this speed boost makes it run a lot faster.