# Associative-MAPS-using-AVL-Trees
C++ code for AVL Trees.
## Execution
Open the project in Visual studio and run the project.
It will either produce `AVL.exe` - double click that and program will run or it will run the program directly and command prompt will open which will look like this:

![image](https://user-images.githubusercontent.com/68595241/121823213-2feeda80-ccbd-11eb-86d6-091f11a1ba99.png)

Now the user may choose the functionality they want to perform accordingly.

I produced the following tree by recursively inserting:

![image](https://user-images.githubusercontent.com/68595241/121823234-6593c380-ccbd-11eb-8db3-98950c86cebb.png)


To load AVL from file, use this syntax
![image](https://user-images.githubusercontent.com/68595241/121823275-aa1f5f00-ccbd-11eb-8195-2fa5a19587fa.png)


## Functionality

Provide following operations in your BST class
1. Insert: Provide Recursive Insert function. The Insert function will insert a given value in AVL MAP. Incase value already
exist then it should return false and do not insert.
2. Delete: Provide Recursive Delete function. The delete function will delete the node with given key. Incase key does not
exist then it should return false. Your code will perform deletion by copy.
3. LookUp: Provide Recursive function to find if the record with the given Key exists.
4. PrintINORDER: Recursively Print the records sorted by the key.
5. Destructor
6. PRINT the AVL Tree on Screen in the following manner. Only print keys (do not show values)
7. Load: create an AVL from the file data. The file will consist of ID, Name and Quantity. File format will be as follows
(the fields are separated by tab)

![image](https://user-images.githubusercontent.com/68595241/121823275-aa1f5f00-ccbd-11eb-8195-2fa5a19587fa.png)


