#This program is used to split the normal EdputerCPU.bin file into the 
#three actual binary files that can be flashed onto the instruction decoding EEPROMS

#Intended to work with python 2.7x
#Python3 handles binary files differently and therefore doesn't work with this yet

inputfile = open("EdputerCPU.bin", "r")
code = inputfile.readlines() #read in the input file
inputfile.close()

cpu1 = open("CPU1.bin","wb") #open the three binary output files
cpu2 = open("CPU2.bin","wb")
cpu3 = open("CPU3.bin","wb")

for line in code:    
  t = line[2:].strip() #strip whitespace and cut off first two chars (0b), so that there's only 0s and 1s left
  cpu1.write(str(chr(int(t[:8],2)))) #split the 24 bit value into 3 byte sized chunks, and write to the files
  cpu2.write(str(chr(int(t[8:16],2))))
  cpu3.write(str(chr(int(t[16:],2))))
cpu1.close()
cpu2.close()
cpu3.close()