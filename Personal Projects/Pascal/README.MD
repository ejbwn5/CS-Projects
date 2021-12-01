# Pascal's Triangle Calculator

This is a project I did in August 2021. This calculates values of [Pascal's Triangle](https://en.wikipedia.org/wiki/Pascal%27s_triangle) using recursion. I used [memoization](https://en.wikipedia.org/wiki/Memoization) to cache completed subproblems to make it efficient. 

I also included a custom data type `BigInt` for the purpose of storing very large integer numbers in the form of strings. This was because the numbers this program is capable of calculating far exceeds the biggest integer type, `long long int`. I only implemented addition for this data type, since this algorithm only requires addition.

I included an example image showing some test cases.

![Example Image](Example.PNG?raw=true "Example Image")

The reason I did this project was because I wanted to freshen up my dynamic programming skills, so I decided to try solving a problem that could be memoized.

