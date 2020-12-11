#include <iostream>
#include <vector>
#include <string>

#include "order.h" //order class header file

using namespace std;

template <class T>
int partition(vector<T> &v, int low, int high)
{
    string pivotCountry = v[high].getCountry();         
    //float pivotTotal_Profit = v[high].getTotal_Profit(); // pivot

    int i = (low - 1); // Index of smaller element

    for (int j = low; j <= high - 1; j++)
    {
        // If current element is smaller than the pivot
        if (v[j].getCountry() < pivotCountry)
        {
            i++; // increment index of smaller element
            swap(v[i], v[j]);
        }
        /*else if (v[j].getCountry() == pivotCountry && v[j].getTotal_Profit() > pivotTotal_Profit)
        {
            i++; // increment index of smaller element
            swap(v[i], v[j]);
        }*/
    }
    swap(v[i + 1], v[high]);
    return (i + 1);
}

template <class T>
void quickSort(vector<T> &v, int low, int high)
{
    if (low < high)
    {
        /* pi is partitioning index, v[p] is now 
		at right place */
        int pi = partition(v, low, high);

        // Separately sort elements before
        // partition and after partition
        quickSort(v, low, pi - 1);
        quickSort(v, pi + 1, high);
    }
}
