# Edputer Assembler

This is the assembler I wrote in Python 2.7 to turn mnemonic-based instructions into actual binary machine code that can run on Edputer. Python 3 handles binary files differently, and this has not been updated to work with it yet. 

Since this is a 16-bit computer, each instruction has 16 bits (8 for opcode, 8 for argument). The program code is intended to be flashed onto two 32k EEPROMS, each holding 8 of the bits for an instruction. This is why the assembler outputs two different binary files (**Code.bin** and **Arg.bin**).