README.txt

-Project Summary-

*Please read the entire README file before starting the program*

This project is an implementation of a Delta-V map of the solar system. Delta-V is the necessary change in velocity required to travel from one place to another in space. It can be made to work with any solar system, but the text files included with the project contain the necessary files to build the solar system we currently live in. The primary data structure used is a graph. The primary struct in this graph is called a body. There are two primary types of bodies. The first is a planet, where each planet's adjacency list is all of the other planets in the solar system. The edges between each planet are weighted with the delta-v required to travel between them. In additon to having an adjacency list of planets, each planet has an adjacency list of moons, which is the second primary type of body. Not every planet has a moon. Only the planet that physically has moons will have an adjacency list of those moons. Therefore, in order to access the edges between planets and moons, you need to first access the moon's parent planet. the abstract portion of this is that it takes less delta-v to travel to a moon of a planet than to the planet itself, because traveling to the planet requires you to go further down into its gravity well. For example, if you want to travel from Earth to Jupiter's moon, Europa, then you would calculate the delta-v required to travel from Earth to Jupiter and then subtract out the delta-v required to travel from Jupiter to Europa. This is why each planet has its own adjacency list for its moons. Finally, there is also a 'Ship' struct which tells you your current location and the fuel remaining, in terms of delta-v. Your ship starts off with 100 km/s delta-v.

-How To Run-

For the program to work, you need the three code files, which are
System.h, System.cpp, and main.cpp, which is the driver function. If you would like to automatically build the solar system then you also need to include "Planets.txt" and "Moons.txt". Simply uncomment everything above the Menu in the driver file to enable this feature. Otherwise, simply use the menu options "Add Body" and "Add Edge" to build your own system. When using "Add Body", it will prompt you for the type of body. Enter "planet" or "moon", case sensitive. When adding an edge between a moon and a planet (you can only add an edge between a moon and a planet when one of the bodies is a moon), the delta-v MUST be negative for the delta-v required to calculate 
properly. The other menu options are "Display State of Ship", which displays your current location and fuel left, "Display System", which simply displays the planets and moons of the system, "Travel Throughout System", which will prompt you for a destination and take you there if you have the fuel required for it, "Refuel Ship", which will add 50 km/s delta-v to your ship, "Show Order of Planets and Moons", which will print the solar system in order with each planet and moon's position displayed, and "Leave System", which will exit the program.

-How to Use Your Own Text Files-

This project is meant to take any text files, just as long as they are formatted. Just follow the formatting for both the provided text files.However, the moon file might take a little explaining. For each line in the file, the parent's planet name is listed. Next is either a zero or one. If zero, the planet has no moons and the I/O moves onto the next line. If it's a one, then there is a list of the moons and their delta-v's.  

-Dependencies-

None. Uses only standard C++ libraries.

-System Requirements-

Should run on any system. I personally built and ran this in 
Code::Blocks.

-Group Members-

Just me, Ian Cooke

-Contributors-

Cody Charland helped me with a few debugging issues.

-Open Issues/Bugs-

Only bug so far is the menu, inputting anything but numbers 1-8 will cause an infinte loop. Beware of the function associated with the Travel Throughout System Option, makeTrip(). It's rather messy at ~130 lines. All of the other functions are much simpler however. The File I/0 is also a bit messy. 