You need to deliver a file to this program,and the program will show four algorithm of sorting.
Here are the four algorithm.

Algorithm of selection sort
1.the array will be divided into two kind, the sorted and the unsorted.Initially, we pick the first data in array as the sorted one, and the rest be the sorted one.
2.pick the minimum data in the unsorted array and concatenate it to the back of the sorted array.
3. Repeat step 2 until there is nothing in the unsorted array.

Algorithm of bubble sort
1.compare the nth data and the (n+1)th data in the array, and swap them if the nth’s if bigger than the (n+1)th’s. After completing the procedure, the biggest one will be on the last location in the array.Initially, we let n=1.
2.Repeat step 1 until (n-1) biggest data is swapped to the array’s back.

Algorithm of insertion sort
1.like selection sort, we divide the array into two different kind, the sorted and the unsorted.initially, the first data will be the sorted one, and the rest will be the unsorted one.
2.pick the head data in the unsorted array and insert it to the right place in the sorted array.(right place means that after inserting it, the sorted array is also the “sorted” array.).
You can compare the head data in the unsorted array with the last data in the sorted array,
(1)if the former is smaller than the latter , then swap them.
(2)the latter will be the (last-1)the data in the sorted array.
(3) Repeat step (1) and step (2) until the former is bigger than the latter.
3.Repeat step 2 until there is nothing in the unsorted array.

Algorithm of quick sort
1.pick a data in the array as the pivot, and here we pick the first data in the array as the pivot.
Step 2 try to let pivot’s left be smaller than the pivot and pivot’s right be bigger than the pivot.
2.set two index,S and M.
Initially, the index_S will points to the second data in the array(the first one is the pivot),and the index_M will points to the last data in the array.
After two for loop,index_S will points to the data which is bigger than the pivot,and index_M will pointes to the data which is smaller than the pivot.
(1)if index_S is smaller than index_M,then swap index_S’s data and index_M’s data.it is because this means that the index_S’s data is on the pivot left but it’s bigger than the pivot , and the index_M’s data is on the pivot’s right but it’s smaller then the pivot.
(2)Repeat step (1) until index_S is bigger than the index_M.(because it means that the index_S’s data is on the pivot right and it’s bigger than the pivot, and the index_M’s data is on the pivot’s left and it’s bigger then the pivot.)
(3)Swap index_M’s data(because the data which is pointer by the index_M is  smaller then the pivot)and the pivot.After the step, the array will be [smaller, pivot, bigger].
3.recursive 
(1)(L,pivot-1),and L will be L, pivot-1 will be R
(2)(pivot+1,R),and pivot+1 will be L,R will be R
4.repeat 3 until L>=R

