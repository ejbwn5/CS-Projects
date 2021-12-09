import sys
import re


if len(sys.argv) < 3:
  print("Invalid Arguments")
  print("Usage: python EdputerPostCompiler.py INPUT OUTPUT")
  exit()



infile = open(sys.argv[1],"r")
code = infile.readlines()
infile.close()

replacedSomething=True
alreadyPointered = [] #keeps track of labels which have pointers assigned to them
bridgeNum=0 #amount of bridges made

while replacedSomething==True: #keep rerunning until no changes are made  
  replacedSomething=False #reset flag
  newcode=[] #modified code
  foundRETStatement=False
  
  #This bit of code removes the duplicate RET statements which sometimes happens during compilation
  for line in code:
    if (re.search("RET", line)):      
      if not foundRETStatement:
        foundRETStatement=True #found one
        newcode = newcode + [line] #add the line
      else: #don't add the duplicate RET to the code
        replacedSomething=True #code has changed since a duplicate RET was removed
    else: #not a RET statement, reset the RET discovered flag
      newcode = newcode + [line]
      foundRETStatement=False

  code = newcode #update code with modified code

  #identify all labels
  labels=[]    
  linenum=0
  for line in code:  
    e = re.findall('\w+:', line)
    for i in range(len(e)):
      labels = labels + [[e[i][:-1], linenum]] #record its position in the file
    linenum+=1
  
  newcode=[]
  for line in code:
    m=re.search("(?:(?:^|\s)+)(CALL \w+)", line) #find any standard CALL instructions
    if m: #CALL statement on this line
      replaced=False
      for lbl in labels:
        if lbl[0]==m.group(1)[5:]:
          if (lbl[1]>255): #see if the location of this label is past the 255th line
            #if it is, then this instruction needs to be a LCALL function referencing a pointer instead
            replaced=True  
            replacedSomething=True                        
            newcode = newcode + [re.sub("(?:(?:^|\s)+)(CALL \w+)", " LCALL "+m.group(1)[5:] +"_loc", line)]            
            skip=False
            for p in alreadyPointered:  
              if p==lbl[0]:  #no need to add a pointer          
                skip=True
                break
            if not skip: #no pointer yet made, insert a .DA instruction at the top of the file
              newcode = newcode[0:2] + [m.group(1)[5:]+"_loc: .DA "+m.group(1)[5:]+"\n"] + newcode[2:]            
              alreadyPointered = alreadyPointered + [lbl[0]] #add to the list of labels which have pointers            
            break
      if replaced==False: #no need to LCALL, just add the original CALL instruction
        newcode = newcode + [line]            
    else: #no CALL on this line, add the instruction normally
      newcode = newcode + [line]
    
  code = newcode #update any changes

  #Basically the exact same thing as the CALL -> LCALL part, but with JMP to RJMP
  newcode=[]
  for line in code:
    m=re.search("(?:(?:^|\s)+)(JMP \w+)", line) #
    if m:
      replaced=False
      for lbl in labels:
        if lbl[0]==m.group(1)[4:]:
          if (lbl[1]>255):
            replaced=True  
            replacedSomething=True                                
            newcode = newcode + [re.sub("(?:(?:^|\s)+)(JMP \w+)", " RJMP "+m.group(1)[4:], line)]
            break
      if replaced==False:
        newcode = newcode + [line]            
    else:
      newcode = newcode + [line]
  code = newcode

  #Basically the exact same thing as the CALL -> LCALL part, but with JCI -> RJCI
  newcode=[]
  for line in code:
    m=re.search("(?:(?:^|\s)+)(JCI \w+)", line)
    if m:
      replaced=False
      for lbl in labels:
        if lbl[0]==m.group(1)[4:]:
          if (lbl[1]>255):
            replaced=True    
            replacedSomething=True                                        
            newcode = newcode + [re.sub("(?:(?:^|\s)+)(JCI \w+)", " RJCI "+m.group(1)[4:], line)]
            break
      if replaced==False:
        newcode = newcode + [line]            
    else:
      newcode = newcode + [line]
  code = newcode

  #Basically the exact same thing as the CALL -> LCALL part, but with JZI -> RJZI
  newcode=[]
  for line in code:
    m=re.search("(?:(?:^|\s)+)(JZI \w+)", line)
    if m:
      replaced=False      
      for lbl in labels:
        if lbl[0]==m.group(1)[4:]:
          if (lbl[1]>255):
            replaced=True          
            replacedSomething=True                                
            newcode = newcode + [re.sub("(?:(?:^|\s)+)(JZI \w+)", " RJZI "+m.group(1)[4:], line)]
            break
      if replaced==False:
        newcode = newcode + [line]            
    else:
      newcode = newcode + [line]
  code = newcode
  
  
  #This part ensures that a RJMP/RJCI/RJZI instruction isn't more than 255 spaces away from its target
  #This is done by adding a small section of code 200 spaces ahead/behind it with an additional RJMP to the target
  #It also has a bridge over it so that whatever code was there before isn't affected
  
  lblsToAdd=[]  
  newcode=[]
  ln=0
  for line in code:
    m=re.search("((?:RJMP|RJCI|RJZI) (\w+))", line)
    if m:    
      for lbl in labels:
        if lbl[0]==m.group(2):          
          if (int(lbl[1]) - ln) > 255:              
            newcode = newcode + [re.sub("((?:RJMP|RJCI|RJZI) (\w+))", m.group(1)+"l"+str(bridgeNum), line)]                
            lblsToAdd = lblsToAdd + [[m.group(2), ln+200, bridgeNum]]            
            bridgeNum=bridgeNum+1
          elif (ln - int(lbl[1])) > 255:              
            newcode = newcode + [re.sub("((?:RJMP|RJCI|RJZI) (\w+))", m.group(1)+"l"+str(bridgeNum), line)]                
            lblsToAdd = lblsToAdd + [[m.group(2), ln-200, bridgeNum]]            
            bridgeNum=bridgeNum+1
            print("Backwards bridge at "+str(lbl[1])+" from "+str(ln))
          else:
            newcode = newcode + [line]
          break
    else:
      newcode = newcode + [line]
    ln=ln+1
  code = newcode
    
  #this is what actually makes the bridges
  while len(lblsToAdd)>0:  
    replacedSomething=True
    indOfFarthest=-1; 
    farthest=-1        
    for t in range(len(lblsToAdd)):
      if lblsToAdd[t][1] > farthest:
        farthest = lblsToAdd[t][1]
        indOfFarthest = t    
        
    a=lblsToAdd.pop(indOfFarthest) #find the position of the farthest bridge we need to make
        
    while re.search("CMP", code[a[1]]): #go backwards from this position until we find a CMP statement
      a[1]=a[1]-1             #this is to make sure our bridge won't be placed right after a CMP statement, which would
                              #break quite a lot of things
    #add the bridge
    code.insert(a[1], a[0]+"l"+str(a[2])+"skp: ")
    code.insert(a[1],a[0]+"l"+str(a[2])+": RJMP "+a[0]+"\n")
    code.insert(a[1],"RJMP "+a[0]+"l"+str(a[2])+"skp\n")

#Made an iteration which didn't change the code's contents

output = open(sys.argv[2],"w") #write to the file specified in the command line

for line in code:
  output.write(line)
output.close()
