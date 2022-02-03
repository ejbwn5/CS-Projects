# Chess AI

This is the Chess AI I wrote for my Intro to Artificial Intelligence (CS 5400) class in the Spring 2020 semester.

The [Original](Original/) folder contains the original source for the project, including the code that was given to us to connect with the "Joueur" matchmaking system. My actual code for the AI can be found [here](Original/games/chess). The files of interest are ai.cpp and Chess.cpp/Chess.h. Chess.cpp is where I defined the logic for chess, and ai.cpp is where I interface with the matchmaking API to submit my moves.

However, the matchmaking system used for this project no longer has running servers, and so I have no way of using it anymore. This is why I'm currently working to migrate my AI to a standalone system using a C++ library for Chess.