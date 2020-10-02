This is a program about binary search tree and treasure hunter.

In the binary search tree,
User must to key in the node by hands(first type in “i” or ”I”) as delete(“d” or ”D”) and search(“s” or “S”).
User can also see what the tree now is by type in “p” or “P”.
You can exit by typing “r” or “R”.

In the treasure hunter,
You must to deliver an exmap.txt file into this program.
Then,input the key, treasure, and bomb number , and in particular, a bomb number x means that all the bomb with a number containing x.
After doing that , the program will show the node be deleted and the shortest path from root to key to treasure.

========================
shortest path’s algorithm:
by finding the key and treasure’s nearest ancestor.

If (both key’s value and treasure’s value > current root’s value) → key and treasure’s nearest ancestor will be in the current root’s right subtree→ current root = current root ’s right child

Else if (both key’s value and treasure’s value < current root’s value) → key and treasure’s nearest ancestor will be in the current root’s left subtree→ current root = current root ’s left child

Else (key’s value < current root’s value < treasure’s value) or (treasure’s value < current root’s value < key’s value) → current root is key and treasure’s nearest ancestor

After finding the key and treasure’s nearest ancestor
You must print a route : root → key → (key and treasure’s nearest ancestor) → treasure
*be care: 1, key = key and treasure’s nearest ancestor ; 2, treasure = key and treasure’s nearest ancestor,don’t double print!

