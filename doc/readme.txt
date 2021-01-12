// file      : Readme.txt
// begin     : Jul 30 2000
// copyright : (C) 2000 by Hans Kopp
// 
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.

README for Truffle-Swine Keeper 

* Introduction 

Truffle-Swine Keeper is a Minesweeper clone. The UI resembles very 
closely other Minesweeper versions. Its main feature compared to 
other Minesweepers is the 'solve'-function that can help you to 
improve your skills in solving Minesweeper.

* Installation 

To install the precompiled executable, extract it to 
a new directory. 

[Windows]
After that, you can start 'SwineKeeper.exe'. 
When you start the program, it creates a Windows INI-File 
named 'SwineKeeper.ini' in the system directory of Windows. 

[Linux]
After that, you can start 'swinekeeper'. 
When you start the program, it creates a config file 
named '.truffleswinekeeperrc' in the home directory. 

It does not modify your system in any other way. 

* Story 

You are an owner of a pig that is trained to search for truffles. 
Your pig is very good at searching for truffles, but once it 
stands on a field that contains truffles, it immediatly eats these 
truffles and refuses to search any longer. Fortunatly, the pig 'tells' 
you how many truffles are in the neighborhood of the swine (you can 
see this because the pig gets exited when there are truffles nearby).
Thus your goal is to find all fields that are containing truffles without 
letting the pig touch a field that actually contains a truffle. 

* Gameplay 

The game is played exactly as other Minesweeper versions. You don't need
to read the text below if you already played minesweeper. 

After you started the game, you see a rectangular array of fields. About 
20% of these fields contain truffles. You have to uncover all 
fields that do not contain a truffle without uncovering a field 
that does contain a truffle. You should do this as fast as possible.  

You have to begin the game by first uncovering some guessed fields.

If you have uncovered a field, a number appears that shows the 
count of truffles in the (up to eight) neighboring fields. 
You can use these numbers to determine further fields without 
truffles, and uncover these. If you can't deduce fields
that are save to uncover, you have to guess. 

You can use the left mouse button to uncover a field, the right 
mouse button to mark a field as a truffle. If you click on a 
uncovered field with the middle mouse button, and the number of 
neighboring marked truffles is equal to the count on the field, 
all neighboring fields that are not marked are uncovered. 

On the right side of the game area, there is a counter that 
displays the number of remaining (unmarked) truffles. On the 
left side, there is a timer that displays the number of seconds
that have elapsed since the first mouse click. With the 
pig-icon in the middle you can reset the game. 

Examples: 

...  
11. -> the covered field (#) is a truffle for sure because of 
#1.    the concoverd '1' in the middle. 

11211 -> The second and forth covered fields are sure truffles, 
#####    the middle field is save to uncover 

The game has three levels, beginner, intermediate and expert. 
You can select the level using the popup menu 'game'. 

If you finished a level faster than anybody before you, you 
can enter your name into the hall of fame. 

In addition to the three default levels, you can select a 
game array with arbitrary dimensions. However, if you do this, 
you cannot enter into the hall of fame. 

* The 'solve' function

You can ask the computer to solve a truffle array for you. To do 
this, select the menu entry 'solve' in the view popup menu. 
A black dot will appear at fields that can be resolved as 
truffles, and a white dot at fields that can be resolved to contain 
no truffles (and thus are save to uncover). If it is not possible 
to determine if a field contains a truffle, a red frame will 
appear. The filled area in this frame describe the probability 
that the field contains a truffle. You can determine the exact 
value of this probablity by letting the mouse pointer rest 
on a red field. This will cause the display of a tooltip. 

The resolution algorithm is perfect, i.e. if it is possible to 
determine if a field is save to uncover, the algorithm will 
find it. Note that the algorithm consideres the number of 
remaining truffles. 

The resolution algorithm currenlty only considers fields 
that have at least an uncovered neighbor. It does not display 
anything for the remaining fields.

If you use the solve function in a game, you cannot enter into 
the hall of fame anymore. 

* Contact 

For questions, remarks etc. write to hskopp@hotmail.com. 



