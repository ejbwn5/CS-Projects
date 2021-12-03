# Edputer Emulator

This is the emulator I wrote in C++ to simulate Edputer. I made this in Visual Studio 2015, and I used the SDL library for the graphics simulation.

This emulator runs Edputer programs which are stored in the form of **Code.bin** and **Arg.bin** machine code files. These files would normally be written to 16K EEPROMS and inserted into the program slots on the physical board.

## Instruction Decoding

This emulator used to use the **EdputerCPU.bin** file to properly simulate the instruction decoding for every instruction, including subclock simulation, but it had incredibly poor performance, as emulators often do. I have since reworked the emulator to use a more optimized approach where it simply calculates the equivalent operation based on the opcode for each instruction. 

However, I'm still including the **EdputerCPU.bin** file for completeness, since it's needed for the real physical Edputer. 


## Execution

To use this, you need the **EdputerEmulator.exe**, **SDL2.dll**, and the **Code.bin** and **Arg.bin** files in the same directory.
