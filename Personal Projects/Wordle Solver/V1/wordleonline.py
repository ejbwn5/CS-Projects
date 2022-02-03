import time
import asyncio
from pyppeteer import launch
from pyppeteer.errors import NetworkError
import random

f=open("allcommon5.txt", "r") #pull the dictionary of common 5 letter words
commonWords = f.read().split()
f.close()

f=open("all5.txt", "r") #pull the dictionary of 'every' 5 letter word
allWords = f.read().split()
f.close()

#returns list of words matching the criteria set
#exclude is a list of letters in the gray category
#requiredSpace is a list of letters in the green category
#requiredWrongSpace is a list of letters in the yellow category
#unallowedWords is a list of words to ignore (already used or not valid word)
def getMatching(exclude="", requiredSpace=[None for _ in range(5)], requiredWrongSpace=[], unallowedWords=[]):
  matching = [] #init empty
  
  #only return list of possible common words, unless there are none
  #in that case, return list of any english word that fits
  #this way, more common english words are preferred
  
  
  dicts = [[commonWords, True],[allWords, False]]
  
  for dictionary in dicts:
    common = dictionary[1] #whether or not this dictionary is of common words
    for word in dictionary[0]:    
      if word not in unallowedWords: 
        if (all(requiredSpace[i]==None or word[i]==requiredSpace[i] for i in range(5))): #word satisfies green letters
          if (all(char not in exclude for char in word)): #word has none of the gray letters
            good = True #the remaining logic is more complicated, so use a boolean to keep track of the validity of this word
            for rws in requiredWrongSpace:
              #try to find a match
              good2=False #another tracking boolean
              for i in range(5): #check every space
                if i in rws[1]: 
                  if word[i] == rws[0]: #this letter cannot be in this slot, word fails if it is
                    good2=False
                    break
                if requiredSpace[i] != None: #this space is taken
                  continue
                if word[i] == rws[0]: #a legal space for this letter is available
                  good2=True
              if not good2: #if the word doesn't pass the check by the end, then this word is no good
                good = False
                break
            if good: #this word is legal
              matching += [word]
    if len(matching)!=0: #words were found by the common dictionary iteration
      break #stop looking
  return (matching, common)
  

def updateParams(exclude, requiredSpace, requiredWrongSpace, evaluations, choice):
  
  
  
  thisEval = None
  
  for i in range(5, -1, -1):
    if evaluations[i] != None:
      thisEval = evaluations[i]
      break
  
  
  print(thisEval)
  
  grayletters = [" " for _ in range(5)]
  yellowletters = [" " for _ in range(5)]
  greenletters = [" " for _ in range(5)]
  
  for i in range(5):
    if thisEval[i] == "absent":
      grayletters[i] = choice[i]
    elif thisEval[i] == "present":
      yellowletters[i] = choice[i]
    elif thisEval[i] == "correct":
      greenletters[i] = choice[i]
  
  for letter in grayletters:
    if letter != " ":
      exclude += letter  
  
  newyellow = []
  
  
  
  for i in range(5):
    if yellowletters[i] != " ":
      #check if the letter is a known green but not used in this word choice
      
      dontaccept=False
      if yellowletters[i] in requiredSpace:
        for spot in range(5):
          if requiredSpace[spot] == yellowletters[i] and spot != i:
            #dont add this letter since we already know it should exist            
            dontaccept=True
            break
      if dontaccept:
        continue
      
      #letter used
      #check if already exists
      newyellow += [yellowletters[i]]
      found=False
      for ind in range(len(requiredWrongSpace)):
        if requiredWrongSpace[ind][0] == yellowletters[i]:
          found=True
          #found it
          requiredWrongSpace[ind][1] += [i]
          break
      if not found:
        requiredWrongSpace += [[yellowletters[i], [i]]]
      if yellowletters[i] in grayletters:
        #also add this location to the list of no-gos
        for ind in range(len(requiredWrongSpace)):
          if requiredWrongSpace[ind][0] == yellowletters[i]:            
            requiredWrongSpace[ind][1] += [grayletters.index(yellowletters[i])]
            break
  
  
  
  for i in range(5):
    if greenletters[i] != " ":
      if requiredSpace[i] == None:
        requiredSpace[i] = greenletters[i]        
        #remove yellows of this         
        for ind in range(len(requiredWrongSpace)):
          if requiredWrongSpace[ind][0] == greenletters[i]:            
            #found            
            requiredWrongSpace = requiredWrongSpace[:ind] + requiredWrongSpace[ind+1:]
            print(requiredWrongSpace)
            break
        if greenletters[i] in newyellow:
          #add yellow back
          requiredWrongSpace += [[greenletters[i], [yellowletters.index(greenletters[i])]]]
      
  
  char_seen = []
  for char in exclude:
    if char not in char_seen and all(char != thing[0] for thing in requiredWrongSpace):             
      if char not in requiredSpace:
        char_seen.append(char)
  exclude = ''.join(char_seen)
  
  
  return (exclude, requiredSpace, requiredWrongSpace)
  

def getUnique(word):
  char_seen = []
  for char in word:
    if char not in char_seen:      
      char_seen.append(char)
  return len(char_seen)


async def create():
  global browser
  browser = await launch(headless=False, executablePath='F:\Chromium\chrome-win\\chrome.exe', userDataDir="F:\\Chromium\\ChromiumData", autoClose=False)  
  page = (await browser.pages())[0]
  await page.goto("https://wordle.berknation.com/")  
  
  await asyncio.sleep(0.5)  
  
  

  
async def newPuzzle():
  global browser  
  page = (await browser.pages())[0]
  await page.focus("*")  
  await page.evaluate("window.todaysWord()")
  await asyncio.sleep(1)
  await page.evaluate("window.randomWord()")
  await asyncio.sleep(1)

async def main():
  global browser  
  page = (await browser.pages())[0]      
  await asyncio.sleep(1)
  await page.focus("*")
  await page.click("*")
  await asyncio.sleep(0.5)
  
  #play forever  
  
  
  exclude=""
  requiredSpace=[None for _ in range(5)]
  requiredWrongSpace=[]
  unallowedWords=[]
  tryNum=1
  while tryNum < 7:
  
    if tryNum == 1:
      choice = "antes"
    else:
      matches = getMatching(exclude, requiredSpace, requiredWrongSpace, unallowedWords)
      common = matches[1]
      matches = matches[0]
      
      matches2 = []
      if tryNum < 6 and len(matches) > 3:
        matches = getMatching(exclude, [None for _ in range(5)], requiredWrongSpace, unallowedWords)
        common = matches[1]
        matches = matches[0]  
        #dont guess the same letter for correct spaces to increase chance of finding yellow letters
        print("Trying to cut down")
        for m in matches:
          good=True
          for space in requiredSpace:
            if space == None:
              continue
            if space in m: 
              good=False
              break
          if good:
            matches2 += [m]
        #print(matches2)
        if len(matches2) > 0:
          matches = matches2
        else:
          print("Couldn't cut down")
      
      
      groups = [[] for _ in range(5)]
      
      for word in matches:
        groups[getUnique(word)-1] += [word]  
      choice = None
      #if tryNum == 6 or requiredSpace.count(None) == 1 or len(matches) < 5:
      if len(matches) < 50:
        print("Ordering by commonality")
        found = None
        for w in commonWords:
          if w in matches:
            if found == None:
              if tryNum > 3 or getUnique(w)==5:              
                found = w
            #print(w)
        #print("")
        choice = found
        if not found:
          print("No commonality")
      if tryNum > 3:
        print(groups)
      
    if choice == None:
      for i in range(4, -1, -1):
        if len(groups[i]) > 0:
          choice = random.choice(groups[i])
          break
    
    
    if choice == None:
      print("No more ideas")
      choice = "yikes"
    print(choice) #input choice
    
    for letter in choice:
      await page.focus("*")
      await page.keyboard.press(letter)
    await page.focus("*")
    await page.keyboard.press("\n")
    await asyncio.sleep(0.1)
    await page.focus("*")
    values = await page.evaluate('''() => [...document.getElementsByTagName("game-app")]
      ''')
    
    gs = values[0]["gameStatus"]
    
    if gs == "WIN":
      print("We Won")
      break
    elif gs == "FAIL":
      print("We Lost")
      break

    if values[0]["rowIndex"] == (tryNum-1):
      #no good
      if values[0]["tileIndex"] == 0:
        print("Don't have focus")
        for i in range(5):
          await page.focus("*")
          await page.keyboard.press('Backspace')        
        await asyncio.sleep(5)
        continue
      elif values[0]["tileIndex"] == 5:
        for i in range(5):
          await page.focus("*")
          await page.keyboard.press('Backspace')        
        await asyncio.sleep(0.1)
        print("Invalid word")
        unallowedWords += [choice]    
        continue
      
      
      
    unallowedWords += [choice]    
    
    await asyncio.sleep(3)
    
    #print(values)

    res = updateParams(exclude, requiredSpace, requiredWrongSpace, values[0]["evaluations"], choice)
    print(res)
    exclude=res[0]
    requiredSpace=res[1]
    requiredWrongSpace=res[2]
    tryNum += 1
    #stats = await page.evaluate('''() => [...window.localStorage["statistics"]]
    #  ''')
    #for thing in stats:
    #  print(str(thing) + " : " + str(stats[thing]))
    #print(stats)
      
  await asyncio.sleep(5)
    
    
  
  #await browser.close()
  



asyncio.get_event_loop().run_until_complete(create())

while True:
  try:
    asyncio.get_event_loop().run_until_complete(newPuzzle())
    asyncio.get_event_loop().run_until_complete(main())
  except (IndexError, NetworkError):
    print("Page gone, quit")
    break
  except Exception as e:
    print (e)
    print (type(e))
    print("Error, doing another")
    time.sleep(3)

