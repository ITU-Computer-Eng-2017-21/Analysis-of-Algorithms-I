// C++ code to implement priority-queue
// using array implementation of
// binary heap

#include <bits/stdc++.h>
#include <vector>
using namespace std;

vector<double> Heap;
int size = -1;

// Function to return the index of the
// parent node of a given node
int parent(int i)
{
    return (i - 1) / 2;
}

// Function to return the index of the
// left child of the given node
int leftChild(int i)
{
    return ((2 * i) + 1);
}

// Function to return the index of the
// right child of the given node
int rightChild(int i)
{
    return ((2 * i) + 2);
}

// Function to shift up the node in order
// to maintain the heap property
void shiftUp(int i)
{
    while (i > 0 && Heap[parent(i)] > Heap[i])
    {

        // Swap parent and current node
        swap(Heap[parent(i)], Heap[i]);

        // Update i to parent of i
        i = parent(i);
    }
}

// Function to shift down the node in
// order to maintain the heap property
void shiftDown(int i)
{
    int maxIndex = i;

    // Left Child
    int l = leftChild(i);

    if (l <= size && Heap[l] < Heap[maxIndex])
    {
        maxIndex = l;
    }

    // Right Child
    int r = rightChild(i);

    if (r <= size && Heap[r] < Heap[maxIndex])
    {
        maxIndex = r;
    }

    // If i not same as maxIndex
    if (i != maxIndex)
    {
        swap(Heap[i], Heap[maxIndex]);
        shiftDown(maxIndex);
    }
}

// Function to insert a new element
// in the Binary Heap
void add(double p)
{
    size = size + 1;
    Heap.push_back(p);
    // Shift Up to maintain heap property
    shiftUp(size);
}

// Function to extract the element with
// maximum priority
double callTaxi()
{
    double result = Heap[0];

    // Replace the value at the root
    // with the last leaf
    //Heap[0] = Heap[size];
    swap(Heap[0], Heap[size]);
    Heap.pop_back();
    size = size - 1;

    // Shift down the replaced element
    // to maintain the heap property
    shiftDown(0);

    return result;
}

// Function to change the priority
// of an element
void update(int i, double p)
{

    float oldp = Heap[i];
    Heap[i] = p;

    if (p < oldp)
    {
        shiftUp(i);
    }
    else
    {
        shiftDown(i);
    }
}