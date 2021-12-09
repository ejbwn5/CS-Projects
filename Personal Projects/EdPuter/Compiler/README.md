# Edputer Compiler

This is the compiler I wrote in C++ using Flex and Bison to compile a C-like language into Edputer Assembly.

## Differences between C and Edputer-C

### Variable Declaration

The biggest difference between Edputer-C and regular C is that Edputer doesn't support local variables. This means that all variables are statically assigned a place in RAM. All variable declarations should be made in global space, and any attempt to declare a variable inside a function will result in a syntax error.

However, it is technically possible for the user to program local variables using the stack, but I decided to not implement this by default since the maximum code space for this program is merely 16 kilobytes. Having local variables and stack manipulation built in by default would likely take up a lot of space and be costly.

### Types

Given that Edputer is a barebones computer, there is no concept of types built in. The only type of value is a 16-bit unsigned integer. Any type discerning is up to the programmer. For example, you could consider values above 0 to be *true* and a value of 0 *false*, or you could consider a value of 0 to be the letter *a*, 1 to be *b*, and so on, but the values are still all considered integers to the compiler. 

### Edputer-C Specific Functions

There are three built-in functions to Edputer-C that pertain to graphics. 

The *vrammar()* function is used to set the Video RAM Memory Address Register. 

The *write()* function is used to write to VRAM at the location currently specified by the VRAM Memory Address Register.

The *flip* statement is used to flip the VRAM buffers. 