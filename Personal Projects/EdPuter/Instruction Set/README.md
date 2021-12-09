# Edputer Instruction Set

This is the instruction set I made for Edputer. The [Control Bit Mapping](Control%20Bit%20Mapping.xlsx) file is what I used to plan out all of the sub-instructions each instruction needs to use. Here you will find a table of 0s and 1s that define the desired control bits needed for an instruction at a certain sub clock and flags state.

A green cell indicates that the specified control bit is unset, and a red cell indicates that the control bit is set. An *x* in a flag column indicates that the flag state does not matter, since flags basically only actually matter for conditional statements.

All instructions begin with the same 2 steps called the fetch cycle, which is shown at the top of the chart. This is where the computer uses the program counter register to fetch the next instruction from code memory and load it into the instruction register.

## CPU files

The **EdputerCPU.bin** file shows the 24 bit control word needed for each given instruction input. To be specific, the mapping of the input bits to the instruction decoding EEPROMS is as follows:

![Address Mapping](CPUDecodingAddressMapping.png?raw=true "Address Mapping")

The program **BinarySplit.py** is used to split the **EdputerCPU.bin** file into three separate binary files (CPU1.bin, CPU2.bin, CPU3.bin) which can be flashed onto 32k EEPROMS and used for instruction decoding.

