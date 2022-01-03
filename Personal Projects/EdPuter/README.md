# Edputer

Edputer is a 16-bit computer I designed. I designed the computer board, instruction set, assembler for the instruction set, a C-like compiler, and an emulator for the computer.

I wanted this computer to be as simple as possible and be made primarily from basic 7400 series ICs. The ALU is simply made of a few 74LS283 binary adders. There are three general purpose registers, a stack pointer register, a RAM memory address register, a VRAM memory address register, a code memory address register, and an instruction register. The 24 control bits used in instruction decoding are managed using three 28C256 EEPROMS. 

There are currently 80 instructions in the instruction set, but there is space for 256 total instructions. 

I haven't actually built a real Edputer yet. All of my program development was done using the emulator I made. However, I have already ordered and received the PCBs, but I still need to order most of the components and solder the components on.

## Components

- [Hardware](Hardware/) - Schematics for the computer board and VGA card
- [Compiler](Compiler/) - A compiler for a C-like language I designed for Edputer
- [Assembler](Assembler/) - An assembler to convert Assembly code into a raw binary form that Edputer can actually execute
- [Emulator](Emulator/) - An emulator written in C++ using the SDL library to simulate Edputer on a Windows machine. I have also been experimenting recently on a new Emulator written in x86 ASM and C to run on bare metal
- [Instruction Set](Instruction%20Set/) - Description of the computer's set of instructions, and an explanation of the instruction set itself
- [Programs](Programs/) - A collection of some programs I've written for Edputer

## Screenshots

A screenshot from my Space Invaders clone

![Space Invaders](Programs/Space%20Invaders/Space%20Invaders.PNG?raw=true "Space invaders")

A screenshot from my unfinished Pacman clone

![Pacman](Programs/Pacman/Pacman.PNG?raw=true "Pacman")
