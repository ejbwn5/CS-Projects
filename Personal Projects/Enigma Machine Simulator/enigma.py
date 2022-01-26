import msvcrt


#Rotors used for the Enigma Machine
#first value is the mapping, second is the value at which the next rotor will shift
ROTORS = [["EKMFLGDQVZNTOWYHXUSPAIBRCJ", "Q", "Rotor I"], 
          ["AJDKSIRUXBLHWTMCQGZNPYFVOE", "E", "Rotor II"], 
          ["BDFHJLCPRTXVZNYEIWGAKMUSQO", "V", "Rotor III"], 
          ["ESOVPZJAYQUIRHXLNFTGKDCMWB", "J", "Rotor IV"], 
          ["VZBRGITYUPSDNHLXAWMJQOFECK", "Z", "Rotor V"]]


#Reflectors used for the Enigma machine
REFLB = ["YRUHQSLDPXNGOKMIEBFZCWVJAT", "Reflector B"]
REFLC = ["FVPJIAOYEDRZXWGCTKUQSBNMHL", "Reflector C"]


def getIndex(letter):
  return ord(letter)-ord("A")

rotorposition=["A","A","A"]
  
def enigma(message, LeftRotor=ROTORS[2], MiddleRotor=ROTORS[1], RightRotor=ROTORS[0], Reflector=REFLB, setting=["A","A","A"], plugboard=[]):
  
  output="" #string to return
  
  doubleShift=False #when to execute the double shift that occurs when using standard notch and pawl actuated enigma machines
  
  plug="ABCDEFGHIJKLMNOPQRSTUVWXYZ" #mapping of the plugboard
  
  plugboard = [(p[0].upper(), p[1].upper()) for p in plugboard] #ensure plugboard letters are uppercase
  
  used = [] #used letters on the plugboard
  for pair in plugboard: #swap around the mapping according to the plugboard pairs
    used = used + [pair[0]] + [pair[1]]
    plug = plug[:getIndex(pair[0])] + pair[1] + plug[getIndex(pair[0])+1:]
    plug = plug[:getIndex(pair[1])] + pair[0] + plug[getIndex(pair[1])+1:]
  for let in used:
    if let not in "ABCDEFGHIJKLMNOPQRSTUVWXYZ":
      print("Invalid letter in plugboard")
      exit()
    if used.count(let) > 1:
      print("Cannot use same letter more than once on the plugboard")
      exit()
  if len(used) > 20:
    print("Cannot have more than 10 pairs on the plugboard at a time")
    exit()
  
  message = message.upper() #make everything uppercase
  
  setting = [val.upper() for val in setting]
  
  for letter in message:    
    if letter not in "ABCDEFGHIJKLMNOPQRSTUVWXYZ": #ignore non characters 
      if letter != chr(8): #no backspaces
        output += letter
      continue
    
    #advance rotors
    shiftMid = (rotorposition[2] == RightRotor[1]) #whether or not the middle rotor should shift    
    
    rotorposition[2] = chr(ord("A")+((getIndex(rotorposition[2])+1)%26)) #rightmost rotor always shifts
    
    if doubleShift: 
      doubleShift=False
      rotorposition[1] = chr(ord("A")+((getIndex(rotorposition[1])+1)%26)) #shift middle rotor (the double shift)
      rotorposition[0] = chr(ord("A")+((getIndex(rotorposition[0])+1)%26)) #shift leftmost rotor
        
    if shiftMid:
      rotorposition[1] = chr(ord("A")+((getIndex(rotorposition[1])+1)%26)) #shift middle rotor      
      doubleShift = (rotorposition[1] == MiddleRotor[1]) #check to see if we should double shift next time
      
    #plugboard    
    letter = plug[getIndex(letter)]
    
    #right rotor
    letter = chr((getIndex(letter)+getIndex(rotorposition[2])-getIndex(setting[2]))%26+ord("A"))
    letter = RightRotor[0][getIndex(letter)]
    letter = chr(((getIndex(letter)+getIndex(setting[2])-getIndex(rotorposition[2])) % 26) + ord("A"))
    
    #middle rotor
    letter = chr((getIndex(letter)+getIndex(rotorposition[1])-getIndex(setting[1]))%26+ord("A"))
    letter = MiddleRotor[0][getIndex(letter)]
    letter = chr(((getIndex(letter)+getIndex(setting[1])-getIndex(rotorposition[1])) % 26) + ord("A"))
    
    #left rotor
    letter = chr((getIndex(letter)+getIndex(rotorposition[0])-getIndex(setting[0]))%26+ord("A"))
    letter = LeftRotor[0][getIndex(letter)]
    letter = chr(((getIndex(letter)+getIndex(setting[0])-getIndex(rotorposition[0])) % 26) + ord("A"))
    
    #reflector
    letter = Reflector[0][getIndex(letter)]
    
    #left rotor
    letter = chr(((getIndex(letter)-getIndex(setting[0])+getIndex(rotorposition[0])) % 26) + ord("A"))
    letter = chr(LeftRotor[0].index(letter)+ord("A"))
    letter = chr((getIndex(letter)-getIndex(rotorposition[0])+getIndex(setting[0]))%26+ord("A"))
    
    #middle rotor
    letter = chr(((getIndex(letter)-getIndex(setting[1])+getIndex(rotorposition[1])) % 26) + ord("A"))
    letter = chr(MiddleRotor[0].index(letter)+ord("A"))
    letter = chr((getIndex(letter)-getIndex(rotorposition[1])+getIndex(setting[1]))%26+ord("A"))
    
    #right rotor
    letter = chr(((getIndex(letter)-getIndex(setting[2])+getIndex(rotorposition[2])) % 26) + ord("A"))
    letter = chr(RightRotor[0].index(letter)+ord("A"))
    letter = chr((getIndex(letter)-getIndex(rotorposition[2])+getIndex(setting[2]))%26+ord("A"))
    
    #plugboard    
    letter = plug[getIndex(letter)]
    
    #done with letter
    output += letter
  
  #done   
  return output

rotors=[ROTORS[2], ROTORS[1], ROTORS[0]] #rotors currently being used
refl = REFLB #reflector currently being used
ringsetting=["A","A","A"] #current ring setting
plugboardcon=[] #current plugboard configuration

#get string representation of ring setting
def getRingSetting():
  return (ringsetting[0] + ", " + ringsetting[1] + ", " + ringsetting[2])

#get string representation of rotor position  
def getRotorPosition():
  return (rotorposition[0] + ", " + rotorposition[1] + ", " + rotorposition[2])

#get string representation of plugboard configuration
def getPlugboardConnections():
  s=""
  for p in plugboardcon:
    s = s + p[0] + p[1] + ", "
  if s == "":
    return "None"
  return s[:-2]
  
#print machine settings
def displaySettings():
  print("Enigma Machine Settings:")
  print("Rotors: " + str(rotors[0][2]) + ", " + str(rotors[1][2]) + ", " + str(rotors[2][2]))
  print("Reflector: " + str(refl[1]))
  print("Ring Setting: " + getRingSetting())
  print("Rotor Position: " + getRotorPosition())
  print("Plugboard Connections: " + getPlugboardConnections())
  print()

#print list of possible actions
def printActions():
  print("Actions:")
  print("1 (or empty): Type on Enigma Machine")
  print("2: Change Rotors")
  print("3: Change Reflector")
  print("4: Change Ring Setting")
  print("5: Change Rotor Position")
  print("6: Change Plugboard Connections")
  print("7: Reset to Default Settings")
  print("8: Quit")

#loop until user quits
while True:
  print() #newline
  displaySettings()
  printActions() #show current settings and possible actions
  
  #get input  
  choice = input()
  
  if choice == "1" or choice=="": 
    print("Press the Enter Key to stop") 
    while True: #simulate enigma machine until user hits enter key
      ch = msvcrt.getch() #fetch key entered
      if ch == b'\xe0': #special character
        ch = msvcrt.getch() #get special char code
        continue #ignore it since it isnt an actual letter
      if ord(ch.decode("ASCII")) == 13: #enter key
        break #quit
      elif ord(ch.decode("ASCII")) in range(32, 126): #if a normal character
        print(enigma(ch.decode("ASCII"), LeftRotor=rotors[0], MiddleRotor=rotors[1], RightRotor=rotors[2], Reflector=refl, setting=ringsetting, plugboard=plugboardcon), end='', flush=True)            
    print() 
  elif choice == "2": #change rotor configuration
    print("Enter the rotors you want to use, ordered left to right (1, 2, 3, 4, or 5)")
    print("e.g. \"3 2 1\" or \"321\"")    
    try:
      r = input().split()[:3]     
      if len(r) == 1: #maybe typed with no spaces
        r = [r[0][0], r[0][1], r[0][2]]
      rotors[0] = ROTORS[int(r[0])-1]
      rotors[1] = ROTORS[int(r[1])-1]
      rotors[2] = ROTORS[int(r[2])-1]     
    except:
      print("Invalid input")    
  elif choice == "3": #change reflector
    print("Enter the reflector you want to use (B, C)")
    print("e.g. \"B\"")   
    try:
      r = input().upper()     
      if r == "B":
        refl = REFLB
      elif r == "C":
        refl = REFLC
      else:
        raise Exception
    except:
      print("Invalid input")
  elif choice == "4": #set ring setting
    print("Set ring setting (A through Z) for the three rotors")
    print("e.g. \"A B C\" or \"ABC\"")        
    try:
      r = input().split()[:3]     
      if len(r) == 1: #maybe typed with no spaces
        r = [r[0][0], r[0][1], r[0][2]]     
      ringsetting = [setting.upper() for setting in r]
    except:
      print("Invalid input")    
  elif choice == "5": #set rotor position
    print("Set rotor position (A through Z) for the three rotors")
    print("e.g. \"A B C\" or \"ABC\"")        
    try:
      r = input().split()[:3]     
      if len(r) == 1: #maybe typed with no spaces
        r = [r[0][0], r[0][1], r[0][2]]     
      rotorposition = [position.upper() for position in r]
    except:
      print("Invalid input")    
  elif choice == "6": #set plugboard configuration
    print("Set plugboard connections")
    print("e.g. \"AF GT LS\"")
    try:
      r = input().split()     
      plugboardcon = [(v[0].upper(), v[1].upper()) for v in r]      
    except:
      print("Invalid input")    
  elif choice == "7": #reset all settings to default
    rotors=[ROTORS[2], ROTORS[1], ROTORS[0]]
    refl = REFLB
    ringsetting=["A","A","A"]
    plugboardcon=[]
    rotorposition=["A","A","A"]
  elif choice == "8": #quit
    break 
  else:
    print("That isn't a valid option")
  