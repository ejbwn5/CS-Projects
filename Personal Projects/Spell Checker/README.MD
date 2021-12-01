# Spell Checker

This is a small project I did in November 2021. It uses basic [Levenshtein Distance](https://en.wikipedia.org/wiki/Levenshtein_distance) to determine how different the input text is from another text. It calculates this distance for all words in a given dictionary, and determines the closest words to what was input. I calculate the Levenshtein Distance using an optimized tabulation method, lowering the needed array size from (n+1) x (m+1) to (n+1) x 1.

Here are the results for a few test case inputs.

![Example Image](Example.PNG?raw=true "Example Image")

