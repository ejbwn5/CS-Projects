import time
import asyncio
from pyppeteer import launch
from pyppeteer.errors import NetworkError
import random

f=open("allcommon5.txt", "r") #pull the dictionary of common 5 letter words
commonWords = f.read().split()
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
  
  for word in commonWords:    
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
  return matching



#given the list of parameters, the evaluations of the letters from the game, and the word that was used, update the list of parameters
def updateParams(exclude, requiredSpace, requiredWrongSpace, evaluations, choice):

  thisEval = None
  
  for i in range(5, -1, -1): #the game returns the evaluations of all the previous guesses, so find the most recent one
    if evaluations[i] != None:
      thisEval = evaluations[i]
      break
    
  print(thisEval) #print it to console for debugging purposes
  
  grayletters = [" " for _ in range(5)]
  yellowletters = [" " for _ in range(5)]
  greenletters = [" " for _ in range(5)]
  
  for i in range(5): #update the lists for gray, yellow, and green letters based on the evaluations
    if thisEval[i] == "absent":
      grayletters[i] = choice[i]
    elif thisEval[i] == "present":
      yellowletters[i] = choice[i]
    elif thisEval[i] == "correct":
      greenletters[i] = choice[i]
  
  for letter in grayletters:
    if letter != " ":
      exclude += letter #add the gray letters to the list of letters to exclude
  
  newyellow = [] #list of letters to be added to the list of yellow letters
  for i in range(5):
    if yellowletters[i] != " ":
    
      #check if the letter is a known green but not used in this word choice      
      dontaccept=False
      if yellowletters[i] in requiredSpace:
        for spot in range(5):
          if requiredSpace[spot] == yellowletters[i] and spot != i:
            #this letter is not a true yellow, since we know where its true position is but chose not to use it there
            dontaccept=True
            break
      if dontaccept: #this letter is already accounted for in the list of greens, so ignore it
        continue
      
      #letter used      
      newyellow += [yellowletters[i]]
      #check if already exists      
      found=False
      for ind in range(len(requiredWrongSpace)):
        if requiredWrongSpace[ind][0] == yellowletters[i]:
          found=True
          #found it
          requiredWrongSpace[ind][1] += [i] #append this index to it's list of banned indices
          break
      if not found:
        requiredWrongSpace += [[yellowletters[i], [i]]] #make new entry for this letter
      if yellowletters[i] in grayletters:
        #also add this location to the list of no-gos 
        for ind in range(len(requiredWrongSpace)):
          if requiredWrongSpace[ind][0] == yellowletters[i]:            
            requiredWrongSpace[ind][1] += [grayletters.index(yellowletters[i])]
            break
  
  
  
  for i in range(5):
    if greenletters[i] != " ":
      if requiredSpace[i] == None: #only do this if this letter is discovered for the first time
        requiredSpace[i] = greenletters[i]        
        #remove yellows of this letter since we found it's real place
        for ind in range(len(requiredWrongSpace)):
          if requiredWrongSpace[ind][0] == greenletters[i]:            
            #found            
            requiredWrongSpace = requiredWrongSpace[:ind] + requiredWrongSpace[ind+1:]
            print(requiredWrongSpace)
            break
        if greenletters[i] in newyellow: #this same letter has another yellow in a different place (aka this letter appears twice in the word)
          #add yellow back
          requiredWrongSpace += [[greenletters[i], [yellowletters.index(greenletters[i])]]]

  char_seen = [] 
  for char in exclude: #make the list of letters in exclude unique
    if char not in char_seen and all(char != thing[0] for thing in requiredWrongSpace): #also remove from exclude if this letter is in yellow too
      if char not in requiredSpace:
        char_seen.append(char)
  exclude = ''.join(char_seen)  
  return (exclude, requiredSpace, requiredWrongSpace) #return list of new params
  
#returns the amount of unique letters in this word
def getUnique(word):
  char_seen = []
  for char in word:
    if char not in char_seen:      
      char_seen.append(char)
  return len(char_seen)

#returns the amount of unique letters in this word that are also in the string 'desired'
def getCountOfDesiredLetters(word, desired):
  char_seen = []
  for char in word:
    if char not in char_seen:      
      if char in desired:
        char_seen.append(char)
  return len(char_seen)

#launch chrome instance and go to the wordle website
async def create():
  global browser
  
  #headless=False so that the chrome GUI actually shows
  #executable path is the location of my Chromium Chrome.exe program, and userdata is the path to my user data for this instance  
  browser = await launch(headless=False, executablePath='F:\\Chromium\\chrome-win\\chrome.exe', userDataDir="F:\\Chromium\\ChromiumData", autoClose=False)  
  page = (await browser.pages())[0] #get first page
  await page.goto("https://wordle.berknation.com/")  #go to website for wordle  
  await asyncio.sleep(0.5)

#get new puzzle
async def newPuzzle():
  global browser  
  page = (await browser.pages())[0] #get current page
  await page.focus("*")
  await page.evaluate("window.todaysWord()") #call this function first to avoid a bug where the random word wouldn't load
  await asyncio.sleep(1)
  await page.evaluate("window.randomWord()")
  await asyncio.sleep(1)

foundSolutions = []
notRealWords = []

#plays a whole game
async def main():
  global browser  
  global foundSolutions
  global notRealWords
  page = (await browser.pages())[0]      
  await asyncio.sleep(1)
  await page.focus("*")
  await page.click("*") #click on page in case one of the pop-ups are there
  await asyncio.sleep(0.5)
  
  #initialize parameters
  exclude=""
  requiredSpace=[None for _ in range(5)]
  requiredWrongSpace=[]
  unallowedWords=[]
  tryNum=1
  
  while tryNum < 7:
  
    choice = None #initialize to no choice
    yikes=False #this variable is used when we have no choice but to make a guess
    if tryNum == 1:
      choice = "stane" #always start with this word because it has very common letters
    else:
      matches = getMatching(exclude, requiredSpace, requiredWrongSpace, unallowedWords+notRealWords) 
      
      #exclude all used letters
      e = exclude[:]
      for thing in requiredSpace:
        if thing != None:
          e += thing
      for thing in requiredWrongSpace:          
        e += thing[0]
            
      matches2 = [] 
      
      if tryNum < 6 and len(matches) > 1: #if we have more than one option and aren't on our last guess
        if tryNum < 3: #if this is guess #2, find words with known yellows, but not known greens
          matches2 = getMatching(exclude, [None for _ in range(5)], requiredWrongSpace, unallowedWords+notRealWords)
        else: #otherwise, find only words that have none of the previously used words         
          matches2 = getMatching(e, [None for _ in range(5)], [], unallowedWords+notRealWords)
      
      #if we found valid words in the last step, use them instead
      if len(matches2) > 0:        
        matches = matches2
      elif len(matches) > 1: #otherwise, check if we have possible words at all
        if len(matches) <= (7-tryNum): #there are fewer possibilities than remaining tries
          #just guess them in terms of commonality since we have enough time
          print("Opting to guess by commonality")
          yikes=True #not really a 'yikes' moment, but the logic is the same so we set this boolean
        else:
          print("No available pruning") #we need to find words that have as many letters that we don't know about as we can          
          if tryNum < 6: #if we are on guess 6, don't do this since we will definitely lose
            #try random words with as many of the remaining letters as we can
            print("go go gadget rule out letters")
            
            print(matches)
            
            #get a list of literally every word except for unallowed words
            matches3 = getMatching("", [None for _ in range(5)], [], unallowedWords+notRealWords) 
            
            groups2 = [[] for _ in range(6)] #split them into groups based on how many of the letters they have in them
            
            remainingLetters = ""
            
            for word in matches:
              for letter in word:
                if letter not in remainingLetters:
                  remainingLetters += letter #put every letter found in one of our matches in this list
            for thing in requiredSpace:
              if thing != None:
                remainingLetters = remainingLetters.replace(thing, "") #remove all letters that are in the green category
            for thing in requiredWrongSpace:          
              remainingLetters = remainingLetters.replace(thing[0], "") #remove all letters that are in the yellow category
            for thing in exclude:          
              remainingLetters = remainingLetters.replace(thing, "") #remove all letters that are in the gray category
              
            #now we have a list of unused letters that appear in at least one of our possible choices
            print(remainingLetters) 
            if len(remainingLetters) == 0:
              print("This is a yikes moment, pray") #we have absolutely nothing to narrow down our choices. yikes. 
              yikes=True
            else: #we can narrow it down some
              for word in matches3:
                #print(word)
                groups2[getCountOfDesiredLetters(word, remainingLetters)] += [word] #put the words into bins based on how many desired letters they have
              
              #print(groups2)
              
              for i in range(5, -1, -1): #find a word from the group with the highest number of desired letters
                if len(groups2[i]) > 0:
                  choice = random.choice(groups2[i]) #this is our best bet of narrowing down the possibilities
                  break
          
      #assuming we haven't already chosen a choice by other means, we need to choose a word with the highest amount of unique letters to increase our information gain
      groups = [[] for _ in range(5)]      
      for word in matches:
        #print(word)
        groups[getUnique(word)-1] += [word]  #bin the words by number of unique letters
        
      #print(matches)
      
      
      if tryNum == 6 or yikes: #guess the word based on how common it is
        print("Ordering by commonality")
        print(matches)
        
        #remove already found solutions
        
        matches2 = []        
        for m in matches:
          if m not in foundSolutions: #this word was not already a solution we found, so it is a possibility
            matches2 += [m]
          else: #this word was a solution to an earlier puzzle, and therefore should not be the solution to this one since the random puzzles don't give duplicates
            print("Already had " + str(m) + " as a solution before, ignore")
        matches = matches2
        found = None #find the 
        for w in commonWords:
          if w in matches:
            if found == None: #find and choose the first word in the list of words since it is the most common   
              found = w  
              break
        choice = found
        if found == None: #no word found in the list of common words
          print("No commonality")          
      else: #if this isnt our last guess
        if choice == None: #if we don't have a choice by now, just choose a word with as many unique letters in it as we can to maximize our information gain
          for i in range(4, -1, -1):
            if len(groups[i]) > 0:
              choice = random.choice(groups[i])
              break
    
    if choice == None: #if this happens, then we legitimately don't have the solution in our dictionary
      print("No more ideas")
      choice = "yikes" #give up on this puzzle
    
    #debug output the choice
    print(choice) #input choice
    
    #now to enter the choice into the game
    for letter in choice:
      await page.focus("*")
      await page.keyboard.press(letter) #type the letters of the choice
    await page.focus("*")
    await page.keyboard.press("\n") #hit enter key
    await asyncio.sleep(0.1) #wait a little bit
    await page.focus("*")
    values = await page.evaluate('''() => [...document.getElementsByTagName("game-app")]''') #game has a dataframe with information about the game, including the letter evaluations
    
    gs = values[0]["gameStatus"] #this says if the game is ongoing or if we won or lost
    
    if gs == "WIN":
      print("We Won")
      print("Solution: " + str(values[0]["solution"]))
      if values[0]["solution"] not in foundSolutions:
        foundSolutions += [values[0]["solution"]] #add the solution to our list of solutions found
      else:
        print("\n\n\n\nSolution already in array??\n\n\n\n") #this shouldnt be possible since the game isn't supposed to give repeats
      break
    elif gs == "FAIL":
      print("We Lost")
      print("Solution: " + str(values[0]["solution"]))
      if values[0]["solution"] not in foundSolutions:
        foundSolutions += [values[0]["solution"]] #add the solution to our list of solutions found
      else:
        print("\n\n\n\nSolution already in array but we lost??\n\n\n\n") #this shouldnt be possible since the game isn't supposed to give repeats      
      break

    if values[0]["rowIndex"] == (tryNum-1): #check if the word we entered was valid by seeing if the rowindex of the game is the same as the try number we were just on
      #no good
      if values[0]["tileIndex"] != 5: #if tileindex isn't 5 when this happens, then we didn't properly enter the word. This usually means the window lost focus
        print("Don't have focus")
        for i in range(5):
          await page.focus("*")
          await page.keyboard.press('Backspace') #erase the word
        await asyncio.sleep(5) #wait a little bit before trying again
        continue
      elif values[0]["tileIndex"] == 5: #if tileindex is 5 when this happens, then the word was invalid
        for i in range(5):
          await page.focus("*")
          await page.keyboard.press('Backspace') #erase the word
        await asyncio.sleep(0.1) #wait a short amount of time
        print("Invalid word") 
        notRealWords += [choice] #add the word to the list of words to not try anymore
        continue
      
    #the word was legit, but we haven't won yet
      
    unallowedWords += [choice] #don't try this word again since that would be stupid
    
    await asyncio.sleep(3) #wait a few seconds for the animations to play
    
    #print(values)

    res = updateParams(exclude, requiredSpace, requiredWrongSpace, values[0]["evaluations"], choice) #update our params based on the letter evals
    print(res)
    exclude=res[0]
    requiredSpace=res[1]
    requiredWrongSpace=res[2]
    tryNum += 1 #next attempt
  
  await asyncio.sleep(5) # we won or lost. Wait five seconds before loading the next puzzle
    
#launch chrome and load the website
asyncio.get_event_loop().run_until_complete(create())

#play puzzles indefinitely
while True:
  try:
    asyncio.get_event_loop().run_until_complete(newPuzzle()) #load new puzzle
    asyncio.get_event_loop().run_until_complete(main())      #play it
  except (IndexError, NetworkError, ConnectionError) as e: #some sore of error usually associated with the page closing. We should quit the program
    print("Page gone, quit")
    print(e)
    break
  except Exception as e: #if anything else went wrong, just wait a little bit and try loading a new puzzle
    print (e)
    print (type(e))
    print("Error, doing another")
    time.sleep(3)

