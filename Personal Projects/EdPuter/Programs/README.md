# Edputer Programs

Here is a collection of programs made to run on Edputer. Every program here has certain files associated with it:

- A *\*.c* file
  - This is the actual Ed-C script written for the program
- *Output.asm*
  - This is the compiled assembly file using the [Edputer compiler](../Compiler/)
- *Post.asm*
  - This is the post-compiled assembly file. Created by running the [Edputer Post-Compiler](../Compiler/EdputerPostCompiler.py) on the Output.asm file
- *Code.bin* and *Arg.bin*
  - These are the actual machine code files created by running [Edputer's Assembler](../Assembler/) on *Post.asm*

