# Wordle Solver

This is my automatic Wordle solver. I use Python's Pyppeteer and Asyncio libraries to automatically control an instance of Google Chrome to play Wordle.

https://user-images.githubusercontent.com/95320219/152296932-f5725868-ae0b-4899-8686-b72ee584f722.mp4

## Strategy

I've refined my strategy multiple times, and now have a win rate of about 98%. However, it now usually takes me longer to reach the solution. I decided that it's better to take longer to win if it means increasing my overall win rate.

My first attempt is always the exact same. I decided to go with the word "stane" for a few reasons. These letters are some of the most common letters in the alphabet, the letter "s" is statistically the most common starting letter, and the letter "e" is statistically the most common ending letter. Using this word first gives me a fair amount of information right off the bat.

My second attempt chooses a random word that doesn't use any of the discovered gray letters, and uses any yellow letters to try to find their actual spot. However, I don't use any green letters because I want to find out as much information about unused letters as I can.

Attempts 3 through 5 try to find words that don't include any of the previously used letters. This is to find out as much about the unknown letters as possible to narrow down the possible options. However, if no words can be made using the remaining letters, I try something else. I try to find words using as many of the unknown letters as possible, without excluding any previously used letters. This will further narrow down the possibilities.

If I make it all the way to attempt 6, or if the previous method has no possible results found, I resort to choosing the most common word out of my remaining choices. My dictionary of words is sorted according to commonality, so I just use whichever word is more common. This is sometimes wrong though, which is why my win rate is only 98%, not 100%. 

Finally, all of the previous rules are ignored if there is only a single word in my dictionary that matches it. This is why I usually don't need all 6 tries. Similarly, during attempt 3-5, if the amount of possible choices left is less than or equal to the amount of tries I have left, I just try all of the remaining choices according to their commonality instead.

## Revisions

### V1

My first attempt. This won after fewer tries on average than the new version, but lost more often.

![Version 1](v1.PNG?raw=true "Version 1")

### V2

My newest version. Has a higher win rate because it's more careful. It rules out remaining possibilies better than the old version, and thus doesn't have to make wild guesses as much.

![Version 2](v2.PNG?raw=true "Version 2")
