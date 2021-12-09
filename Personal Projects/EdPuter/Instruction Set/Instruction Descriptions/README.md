# Instruction Descriptions

Here I give brief descriptions of what every instruction in this instruction set do.

There are two different opcodes for each type of relative jump. One for adding the difference and one for subtracting.

## HLT (Opcode 0)

This instruction simply set the halt control bit, which stops the clock from running

## LDACMA (Opcode 1)

Sets the A register to a value from code memory, using the argument as an address.

## LDAI (Opcode 2)

Sets the A register to a value specified in the argument.

## LDBCMA (Opcode 3)

Exact same as LDACMA, except it sets the B register instead.

## LDBI (Opcode 4)

Exact same as LDAI, except it sets the B register instead.

## LDAIO (Opcode 5)

Reads the IO port into the A register.

## LDACMC (Opcode 6)

The same as LDACMA, except the C register is used as the address.

## LDBIO (Opcode 7)

The same as LDAIO, except the IO port is read into the B register instead.

## ADDA (Opcode 8)

Adds the A and B registers together, then stores the result in the A register.

This updates the flags register.

## ADDB (Opcode 9)

Adds the A and B registers together, then stores the result in the B register.

This updates the flags register.

## ADDC (Opcode 10)

Adds the A and B register together, then stores the result in the C register.

This updates the flags register.

## SUBA (Opcode 11)

Subtracts the B register from the A register, then stores the result in the A register.

This updates the flags register.

## SUBB (Opcode 12)

Subtracts the B register from the A register, then stores the result in the B register.

This updates the flags register.

## SUBC (Opcode 13)

Subtracts the B register from the A register, then stores the result in the C register.

This updates the flags register.

## FLIP (Opcode 14)

This flips the two Video RAM buffer controls. The buffer being read from is now writable, and the one that was writable is now being read by the Video Card.

## LDARAM (Opcode 15)

Sets the A register to a value from RAM, using the argument as an address.

## JMP (Opcode 16)

Unconditional absolute jump. This sets the program counter to the argument passed in.

## JMPA (Opcode 17)

Indirect unconditional jump. This sets the program counter to the value stored in the A register.

## JMPB (Opcode 18)

Indirect unconditional jump. This sets the program counter to the value stored in the B register.

## JMPC (Opcode 19)

Indirect unconditional jump. This sets the program counter to the value stored in the C register.

## JMPRAM (Opcode 20)

Indirect unconditional jump. This sets the program counter to the value stored in RAM, using the argument as an address.

## CALL (Opcode 21)

Calls a function. This stores the current program counter value in RAM using the Stack Pointer, then increments the Stack Pointer, and jumps to the address specified in the argument.

## RET (Opcode 22)

Returns from a function. This decrements the Stack Pointer, fetches the address located in RAM at the Stack Pointer, then jumps to it.

## PUSHI (Opcode 23)

Pushes an immediate value onto the stack. Puts the argument in RAM at the Stack Pointer, then increments the Stack Pointer.

## POPA (Opcode 24)

Pops a value off the stack and loads it into the A register. 

## POPB (Opcode 25)

The same as POPA, but the value is loaded into the B register.

## POPC (Opcode 26)

The same as POPA, but the value is loaded into the C register.

## PUSHA (Opcode 27)

Pushes the value stored in the A register onto the stack.

## PUSHB (Opcode 28)

Pushes the value stored in the B register onto the stack.

## PUSHC (Opcode 29)

Pushes the value stored in the C register onto the stack.

## LDBRAM (Opcode 30)

The same as LDARAM, but the value is loaded into the B register instead.

## LDCCMA (Opcode 31)

The same as LDACMA, but the value is loaded into the C register instead.

## LDCI (Opcode 32)

The same as LDAI, but loads the value into the C register instead.

## LDCIO (Opcode 33)

The same as LDAIO, but the IO port is loaded into the C register instead.

## VRA (Opcode 34)

Writes the value stored in A to VRAM, using the argument as an address.

## VRC (Opcode 35)

Writes the value stored in C to VRAM, using the argument as an address.

## VRW (Opcode 36)

Writes the value stored in the argument to the currently selected VRAM address.

## VMARA (Opcode 37)

Sets the Video RAM Memory Address Register to the value stored in the A register.

## VMARB (Opcode 38)

The same as VMARA, but using the value stored in the B register instead.

## VMARC (Opcode 39)

The same as VMARA, but using the value stored in the C register instead.

## JZI (Opcode 40)

JMP to immediate if Zero Flag set. If the Zero Flag is not set, nothing happens. If the Zero Flag is set, then a jump to the address specified in the argument happens.

## JZA (Opcode 41)

JMP to value stored in A register if Zero Flag set. If the Zero Flag is not set, nothing happens. If the Zero Flag is set, then a jump to the address specified in the A register happens.

## JZB (Opcode 42)

The same as JZA, but jumps to the value stored in the B register instead.

## JZC (Opcode 43)

The same as JZA, but jumps to the value stored in the C register instead.

## JZRAM (Opcode 44)

Indirect jump to value stored in RAM at the address specified by the argument, but only if the Zero Flag is set.

## JCI (Opcode 45)

The same as JZI, but the condition is that the Carry Flag is set, not the Zero Flag.

## JCA (Opcode 46)

The same as JZA, but the condition is that the Carry Flag is set, not the Zero Flag.

## JCB (Opcode 47)

The same as JZB, but the condition is that the Carry Flag is set, not the Zero Flag.

## JCC (Opcode 48)

The same as JZC, but the condition is that the Carry Flag is set, not the Zero Flag.

## JCRAM (Opcode 49)

The same as JZRAM, but the condition is that the Carry Flag is set, not the Zero Flag.

## MOVAIO (Opcode 50)

Outputs the value stored in the A register to the IO port.

## MOVBIO (Opcode 51)

Outputs the value stored in the B register to the IO port.

## MOVCIO (Opcode 52)

Outputs the value stored in the C register to the IO port.

## LDARAMC (Opcode 53)

Sets the A register to a value from RAM, using the value stored in the C register as an address.

## MOVAB (Opcode 54)

Sets the B register to the value stored in the A register.

## MOVAC (Opcode 55)

Sets the C register to the value stored in the A register.

## MOVBA (Opcode 56)

Sets the A register to the value stored in the B register.

## MOVBC (Opcode 57)

Sets the C register to the value stored in the B register.

## MOVCA (Opcode 58)

Sets the A register to the value stored in the C register.

## MOVCB (Opcode 59)

Sets the B register to the value stored in the C register.

## NOPS (Opcode 60)

No operation. Wastes 6 clock cycles.

## NOPM (Opcode 61)

No operation. Wastes 10 clock cycles.

## NOP (Opcode 62)

No operation. Wastes 16 clock cycles.

## STA (Opcode 63)

Store the value of the A register in a place in RAM, using the argument as an address.

## STB (Opcode 64)

Store the value of the B register in a place in RAM, using the argument as an address.

## STC (Opcode 65)

Store the value of the C register in a place in RAM, using the argument as an address.

## CMP (Opcode 66)

Compare the A and B registers. Basically, this just subtracts the B register from the A register and then updates the flags register, but doesn't store the result anywhere.

## LDCRAM (Opcode 67)

Loads the C register with a value from RAM, using the argument as an address.

## LCALL (Opcode 68)

Long Call. This does a CALL, but using an address stored in Code Memory at a location specified with the argument.

## JMPCM (Opcode 69)

Indirect jump to an address stored in Code Memory at a location specified with the argument.

## JCCM (Opcode 70)

Indirect jump to an address stored in Code Memory if the Carry Flag is set. If the Carry Flag is not set, nothing happens.

## JZCM (Opcode 71)

The same as JCCM, but the condition is that the Zero Flag is set, not the Carry Flag.

## VRCC (Opcode 72)

Writes the value stored in the C register to the currently selected Video RAM address.

## RJMP (Opcode 73 (Forwards), Opcode 74 (Backwards))

Unconditional relative jump. 

This Pushes the A and B registers onto the stack, then loads the program counter into the A register and the argument into the B register. The two are either added together or subtracted, and written to the program counter. Then the A and B registers are popped back off the stack.

## RJCI (Opcode 75 (Forwards), Opcode 76 (Backwards))

Relative jump if Carry Flag set.

The same as RJMP, but only if the Carry Flag is set.

## RJZI (Opcode 77 (Forwards), Opcode 78 (Backwards))

Relative jump if Zero Flag set.

The same as RJMP, but only if the Zero Flag is set.

## STARAMC (Opcode 79)

Stores the value of the A register in RAM at an address specified by the C register.

