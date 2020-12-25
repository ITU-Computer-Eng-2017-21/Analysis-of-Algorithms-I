// priority-queue using vector implementation of binary heap

#include <bits/stdc++.h>
#include <vector>
using namespace std;

vector<double> taxi;
int size = -1;

// Function to return the index of the parent node of a given node
int parent(int i)
{
    return (i - 1) / 2;
}

// Function to return the index of the left child of the given node
int leftChild(int i)
{
    return ((2 * i) + 1);
}

// Function to return the index of the right child of the given node
int rightChild(int i)
{
    return ((2 * i) + 2);
}

// Function to shift up the node in order to maintain the heap property
void shiftUp(int i)
{
    while (i > 0 && taxi[parent(i)] > taxi[i])
    {

        // Swap parent and current node
        swap(taxi[parent(i)], taxi[i]);

        // Update i to parent of i
        i = parent(i);
    }
}

// Function to shift down the node in order to maintain the heap property
void shiftDown(int i)
{
    int current = i;

    // Left Child
    int l = leftChild(i);

    if (l <= size && taxi[l] < taxi[current])
    {
        current = l;
    }

    // Right Child
    int r = rightChild(i);

    if (r <= size && taxi[r] < taxi[current])
    {
        current = r;
    }

    // If i not same as current
    if (i != current)
    {
        swap(taxi[i], taxi[current]);
        shiftDown(current);
    }
}

// Function to add a new taxi in the binary heap
void add(double p)
{
    size = size + 1;
    taxi.push_back(p);
    // Shift Up to maintain heap property
    shiftUp(size);
}

// Function to call the element with maximum priority
double call()
{
    double called = taxi[0];

    // Replace the value at the root with the last leaf
    swap(taxi[0], taxi[size]);
    taxi.pop_back();
    size = size - 1;

    // Shift down the replaced element to maintain the heap property
    shiftDown(0);

    return called;
}

// Function to update the distance of an taxi
void update(int i)
{

    taxi[i] = taxi[i] - 0.01;
    shiftUp(i);
}