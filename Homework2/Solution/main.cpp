#include <iostream>
#include <fstream>
#include <string>

#include <sstream>
#include <math.h>

using namespace std;
#include "pq.cpp"
//#include "pq_array.cpp"
// Driver Code
int main(int argc, char const *argv[])

{

    /*		  45 
			/	 \ 
		   31	 14 
		  / \    / \ 
		13  20  7  11 
		/ \ 
	   12  7 
	Create a priority queue shown in 
	example in a binary max heap form. 
	Queue will be represented in the 
	form of array as: 
	45 31 14 13 20 7 11 12 7 */

    // Insert the element to the
    // priority queue

    ifstream file;
    file.open("locations.txt");

    if (!file)
    {
        cerr << "File cannot be opened!";
        exit(1);
    }

    string line;
    getline(file, line);

    int M = stoi(argv[1]);
    float p = stof(argv[2]);

    for (int z = 0; z < M; z++)
    {
        int ratio = p * 100;
        int r = rand() % 100;

        if (r < ratio)
        {
            int x = rand() % size;
            update(x, Heap[x] - 0.01);
        }
        else
        {
            float longitude, latitude;
            file >> longitude;
            file >> latitude;

            float distance = sqrt(longitude * longitude + latitude * latitude);
            insert(distance);

            getline(file, line, '\n'); //this is for reading the \n character into dummy variable.
        }
    }

    /*insert(45);
    insert(20);
    insert(14);
    insert(12);
    insert(31);
    insert(7);
    insert(11);
    insert(13);
    insert(7);*/

    int i = 0;

    // Priority queue before extracting max
    cout << "Priority Queue : ";
    while (i <= size)
    {
        cout << Heap[i] << " ";
        i++;
    }

    cout << "\n";

    // Node with maximum priority
    cout << "Node with nearest : "
         << extractMax() << "\n";

    // Priority queue after extracting max
    cout << "Priority queue after "
         << "call nearest : ";
    int j = 0;
    while (j <= size)
    {
        cout << Heap[j] << " ";
        j++;
    }

    cout << "\n";

    // Change the priority of element
    // present at index 2 to 49
    /*changePriority(2, 49);
    cout << "Priority queue after "
         << "priority change : ";
    int k = 0;
    while (k <= size)
    {
        cout << Heap[k] << " ";
        k++;
    }*/

    //cout << "\n";

    // Remove element at index 3
    /*remove(3);
    cout << "Priority queue after "
         << "removing the element : ";
    int l = 0;
    while (l <= size)
    {
        cout << Heap[l] << " ";
        l++;
    }*/

    //cout << "\n" << endl;

    /*for (int i = 0; i < 8; i++)
    {
        cout << extractMax() << endl;
    }*/

    return 0;
}
