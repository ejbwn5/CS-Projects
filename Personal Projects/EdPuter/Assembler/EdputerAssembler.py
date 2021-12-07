import sys
import re

#list of commands and their respective opcodes
#also discern between commands that use arguments and that don't
argcommands=[("LDACMA",1),("LDAI",2),("LDBCMA",3),("LDBI",4),("LDARAM",15),("JMP",16),("JMPRAM",20),("CALL",21),("PUSHI",23),("LDBRAM",30),("LDCCMA",31),("LDCI",32),("VRW",36),("JZI",40),("JZRAM",44),("JCI",45),("JCRAM",49),("STA",63),("STB",64),("STC",65),("LDCRAM",67),("LCALL",68),("JMPCM",69),("JCCM",70),("JZCM",71),("RJMP",73),("RJCI",75),("RJZI",77)]
noargcommands=[("HLT",0),("LDAIO",5),("LDACMC",6),("LDBIO",7),("ADDA",8),("ADDB",9),("ADDC",10),("SUBA",11),("SUBB",12),("SUBC",13),("FLIP",14),("JMPA",17),("JMPB",18),("JMPC",19),("RET",22),("POPA",24),("POPB",25),("POPC",26),("PUSHA",27),("PUSHB",28),("PUSHC",29),("LDCIO",33),("VRA",34),("VRC",35),("VMARA",37),("VMARB",38),("VMARC",39),("JZA",41),("JZB",42),("JZC",43),("JCA",46),("JCB",47),("JCC",48),("MOVAIO",50),("MOVBIO",51),("MOVCIO",52),("LDARAMC",53),("MOVAB",54),("MOVAC",55),("MOVBA",56),("MOVBC",57),("MOVCA",58),("MOVCB",59),("NOPS",60),("NOPM",61),("NOP",62),("CMP",66),("VRCC",72),("STARAMC", 79)]

#make sure you input the required arguments
if len(sys.argv)<4 or len(sys.argv)>6:
  print("Invalid Arguments")
  print("Usage: python EdputerAssembler.py ASMFILE INSTDESTINATION ARGDESTINATION [startadd] [startarrayadd]")
  exit()

#read in the ASM file
infile = open(sys.argv[1],"r")
code = infile.readlines()
infile.close()


startaddress=100 #default is RAM loc 100 is the starting point for variables
if len(sys.argv)==5:
  startaddress=int(sys.argv[4]) #unless specified otherwise in the command line


arrayadd=256 #starting address for arrays is 256
if len(sys.argv)==6:
  arrayadd=int(sys.argv[5]) #unless specified otherwise in the command line

  
#------ preprocessor part

#replace vaiables with RAM addresses

#list of known variables
variables = []

for line in code:
  e = re.findall('\$\w+', line) #find all instances of variables, looks like $var
  
  for i in range(len(e)): #make list of all variable names
    if e[i] not in variables:
      variables = variables + [e[i]]
      
for line in range(len(code)):
  e = re.findall('&\w+\[\d+\]', code[line]) #if an array var found in a line of ASM
  
  for i in range(len(e)):    
    size=re.search("(?:&\w+\[)(\d+)", e[i]) 
    
    rep = re.sub("&\w+\[\d+\]", str(arrayadd>>8)+" "+str(arrayadd&255), code[line]) #replace var name with the RAM address allocated for it
    code[line] = rep
    arrayadd+=int(size.group(1)) #increment the next array memory position by the size of this one
    
for line in range(len(code)): #replace normal variables with their allocated RAM address
  newline = code[line]
  for varidx in range(len(variables)):
    newline = re.sub(("(" +  re.escape(variables[varidx]) + ")(?:\s.*)"), str(startaddress+varidx)+"\n", newline)      
  code[line] = newline

  
#----- Time to actually assemble the program

labels=[]

instfile = open(sys.argv[2],"wb") #open the two files in binary write mode
argfile = open(sys.argv[3],"wb")
linenum=0 #keep track of linenumber in case we need to report an error

for line in code:  
  e = re.findall('\w+:', line)
  for i in range(len(e)):
    labels = labels + [[e[i][:-1], linenum]] #accumulate a list of all labels (jump points)
  linenum+=1  
    
  
for line in range(len(code)):
  e = re.search('(.DA (.+))', code[line])  
  if (e): #this line has a "define address" 
    for l in labels:
      if e.group(2)==l[0]: 
         code[line] = re.sub('(.DA (.+))', ".DW "+str(l[1]>>8)+" "+str(l[1]&255), code[line]) #define address is basically just a pointer to a location in ram
    

linenum=0 #reset line count
totlines=0 #actual amount of generated instructions, since the actual file can have whitespace
for line in code:
  tokens = line.split()
  
  #initialize info known about this line
  needarg=False
  opname=""
  opcode=0
  opcodefound=False
  arg=0
  argfound=False
  
  
  for token in tokens:    #iterate over all tokens in the line
    if token.find(':')!=-1: #skip labels
      continue
    elif token.find('#')!=-1: #ignore comments, quit parsing this line
      break
    else:
      if opcodefound==False: #look for opcode
        for cd in noargcommands: #try to match with instrutions without arguments
          if cd[0].lower()==token.lower(): #matched
            opcodefound=True
            opcode=int(cd[1])
            argfound=True #there isn't actually an argument for this one
        if opcodefound==True: #we can stop since we've successfully identified a valid instruction
          break
        for cd in argcommands: #we haven't found a valid instruction yet, so check instructions that use arguments
          if cd[0].lower()==token.lower(): #found a command name
            opname=token
            opcodefound=True              
            needarg=True #mark that we need an argument for this instruction in case one is missing, so we can report the error
            if cd[1]>72 and cd[1]<79: #these are the operations involving relative jumps
              directionFound=False #we need to figure out if the relative jump is forwards or backwards because these have different opcodes
              for lbl in labels:              
                if tokens[tokens.index(token)+1]==lbl[0]:
                  directionFound=True
                  if lbl[1] > linenum:
                    #addrjmp
                    opcode=int(cd[1])
                  else:
                    #subrjmp
                    opcode=int(cd[1])+1
              if directionFound==False: #couldn't find the label this was referencing
                print("Unrecognized label on line "+str(linenum)+", '"+tokens[tokens.index(token)+1]+"'")
                instfile.close()
                argfile.close()
                exit()
            else: #if its not a relative jump, simply mark down the opcode
              opcode=int(cd[1])
        if opcodefound==True: #found a valid operation, loop back again to process the argument, if any
          continue     
        else: #no operation found, check if this line was an assembler directive
          if token.lower()==".dw": # "define word", simply store a specific value in code memory at this location
            try:
              if tokens[tokens.index(token)+1].isdigit(): #the values need to be actual number values          
                opcode=int(tokens[tokens.index(token)+1])            
              if tokens[tokens.index(token)+2].isdigit():
                arg=int(tokens[tokens.index(token)+2])
            except:
              print("Invalid values for .DW")
              instfile.close()
              argfile.close()
              exit()              
            break #quit parsing this line since the define word assembling is complete          
          else: #at this point, the assembler has no idea what was input, and should display an error
            print("Unrecognized string on line "+str(linenum)+", '"+token+"'")
            instfile.close()
            argfile.close()
            exit()
      if opcodefound==True and argfound==False: #at this stage, we have found the opcode, but have not found the argument
        if token.isdigit(): #see if the argument is a literal integer
          argfound=True
          arg=int(token)   #simply use this integer as the argument
        else: #try to see if the text is a known label
          for lbl in labels:
            if token==lbl[0]: #we found it
              argfound=True
              if opcode==73 or opcode==75 or opcode==77: #these are relative jump forwards, so we calculate the distance after the current line
                arg=int(lbl[1]-linenum-1)
              elif opcode==74 or opcode==76 or opcode==78: #these are relative jump backwards, so we calculate the distance before the current line
                arg=int(-(lbl[1]-linenum-1))
              else: #simply record the location of the label
                arg=int(lbl[1])
      
  if needarg==True and argfound==False: #does this operation need an argument and no valid one was found?
    print("Operation "+opname+" is missing an argument on line "+str(linenum))
    print(line)
    instfile.close()
    argfile.close()
    exit()
  try:   
    if opcode==10: #10s are weird. Since their ascii value represents a newline(\n), python writes the windows newline (\r\n) to the file instead.
      instfile.write('\12')      #this is why I manually write in the octal form of 10, \12 into the file instead. This was a huge bug I had for a while.
    else: #if its opcode isn't 10, it can be converted normally without getting a carriage return attached
      instfile.write(str(chr(opcode)))
    if arg==10: #same as with the opcode
      argfile.write('\12')
    else:
      argfile.write(str(chr(arg)))
    totlines+=1
  except ValueError:
    print("Error on line "+str(linenum)+", Argument value not in range (0-255)") #the argument and opcode both need to be the size of a byte
    instfile.close()
    argfile.close()
    exit()
  #except:
  #  pass
    
  linenum+=1

#fill in the remaining spaces with 0s
for i in range(totlines,16384):
  instfile.write(str(chr(0)))
  argfile.write(str(chr(0)))

print("Successfully assembled program") #assembly complete
instfile.close()
argfile.close()