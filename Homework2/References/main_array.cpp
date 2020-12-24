#include <iostream>
#include <fstream>
#include <string>

using namespace std;
//#include "pq.cpp"
#include "pq_array.cpp"
// Driver Code
int main()
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
    insert(45);
    insert(20);
    insert(14);
    insert(12);
    insert(31);
    insert(7);
    insert(11);
    insert(13);
    insert(7);

    int i = 0;

    // Priority queue before extracting max
    cout << "Priority Queue : ";
    while (i <= size)
    {
        cout << H[i] << " ";
        i++;
    }

    cout << "\n";

    // Node with maximum priority
    cout << "Node with maximum priority : "
         << extractMax() << "\n";

    // Priority queue after extracting max
    cout << "Priority queue after "
         << "extracting maximum : ";
    int j = 0;
    while (j <= size)
    {
        cout << H[j] << " ";
        j++;
    }

    cout << "\n";

    // Change the priority of element
    // present at index 2 to 49
    changePriority(2, 49);
    cout << "Priority queue after "
         << "priority change : ";
    int k = 0;
    while (k <= size)
    {
        cout << H[k] << " ";
        k++;
    }

    cout << "\n";

    // Remove element at index 3
    remove(3);
    cout << "Priority queue after "
         << "removing the element : ";
    int l = 0;
    while (l <= size)
    {
        cout << H[l] << " ";
        l++;
    }

    //cout << "\n" << endl;

    /*for (int i = 0; i < 8; i++)
    {
        cout << extractMax() << endl;
    }*/

    return 0;
}
