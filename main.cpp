#include <iostream>
#include <vector>
#include "BTree.h"
using namespace std;

int main()
{
    BTree<int> btree(128);

    // Insert enough values
    for (int i = 1; i <= 128; i++)
    {
        btree.insert(i);
    }

    cout << "After inserting 128 values:" << endl;
    // Print the key count
    cout << "Key count: " << btree.count() << endl;

    // try to insert a number that is already inserted, which should throw an error
    try
    {
        btree.insert(50);
    }
    catch (DuplicateValueException &e)
    {
        cerr << "Error: " << e.what() << endl;
    }

    // Find and retrieve a value
    try
    {
        int foundValue = btree.findAndRetrieve(50);
        cout << "Found value: " << foundValue << endl;
    }
    catch (KeyNotFoundException &e)
    {
        cerr << "Error: " << e.what() << endl;
    }

    // Try to find a value that doesn't exist
    try
    {
        int notFoundValue = btree.findAndRetrieve(200);
        cout << "Found value: " << notFoundValue << endl;
    }
    catch (KeyNotFoundException &e)
    {
        cerr << "Error: " << e.what() << endl;
    }
    // Remove enough values to return to the condition where the root is a leaf
    for (int i = 1; i <= 128; i++)
    {
        try
        {
            btree.findAndRemove(i);
        }
        catch (KeyNotFoundException &e)
        {
            cerr << "Error: " << e.what() << endl;
        }
    }

    cout << "After removing 128 values:" << endl;
    // Print the key count
    cout << "Key count: " << btree.count() << endl;
    return 0;
}
