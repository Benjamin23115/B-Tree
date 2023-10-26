# B-Tree Implementation

In this project, we will be implementing a B-Tree data structure as discussed in class. The B-Tree will be a templated class, utilizing at least two classes, and its properties will be determined based on the type of data being stored and a block size of 512 bytes.

## B-Tree Class Functions

The B-Tree class should have at least the following functions:

### Constructor

1. Initialize the B-Tree with an empty root.
2. Take a comparison function as a function pointer to determine how to compare items in the B-Tree.
3. Set any initial parameters or variables required for the B-Tree structure.

### Destructor

1. Traverse the B-Tree in a depth-first manner.
2. Recursively delete nodes and free any dynamically allocated memory.
3. Ensure that no memory leaks occur.

### Insert

1. Start at the root node and navigate through the tree to find the appropriate leaf node for insertion.
2. Check if the leaf node has room for the new item.
3. If the leaf node is full, split it and promote the middle item to the parent node.
4. Continue this process up the tree, potentially splitting parent nodes as well, until a suitable spot for the new item is found.
5. Insert the item in the appropriate location within the leaf node.
6. Ensure that the B-Tree properties are maintained, such as balancing and no duplicate values.

### Find

1. Start at the root node and navigate through the tree to find the target item.
2. Utilize the comparison function to compare items and decide which branch to follow.
3. If the item is found, return it. If not, throw an exception indicating that the item was not found.

### Remove

1. Start at the root node and navigate through the tree to find the target item for removal.
2. Utilize the comparison function to compare items and decide which branch to follow.
3. If the item is not found, throw an exception indicating that the item wasn't found.
4. If the item is found, remove it from the node.
5. Ensure that the B-Tree properties are maintained, such as redistribution or merging of nodes if necessary.

### Count/Size

1. Traverse the B-Tree in a depth-first manner.
2. Recursively count the number of keys in each node.
3. Sum the counts from all nodes to determine the total number of keys stored in the B-Tree.

By following these steps, you will ensure that your B-Tree implementation works correctly and efficiently.

## Driver Program

To test these functions, you need to implement a driver program that performs the following steps:

1. Initialize the B-Tree.
2. Insert enough values to cause at least two overflows.
3. Remove enough values to return the B-Tree to a condition where the root is a leaf node.
