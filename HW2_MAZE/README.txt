This is a program about two rats in a maze.
Rat A start at (0,0),and follow four direction when walking(right>down>up>left);Rat B start at (14,14),and follow another four direction when walking(left>up>down>right).
If either of them finds the export, the path is found.
You should deliver a 15*15 maze into it.
The program will output the complete path which two rats has walked if your maze has a route to the export.
However,if your maze don't have a path to the export, the program will output no path found.
All the result can be seen in the result.txt file.

Here is the program's algorithm:
if "either" have not arrive the export and stack is not empty
try four direction
test ok or not
unvisited and not out of boundary)
 if ok , "push" in the stack and "mark" the position
 if not and complete trying four direction , "pop" out the stack to go previous position
 if "either" have arrive the export(find the path) or stack is empty(no path)
 end the program
