#include <iostream>
#include <vector>
#include <string>

#include "order.h"

using namespace std;

template <class T>
int partition(vector<T> &v, int low, int high)
{
    string pivotCountry = v[high].getCountry();          // pivot
    float pivotTotal_Profit = v[high].getTotal_Profit(); // pivot

    int i = (low - 1); // Index of smaller element

    for (int j = low; j <= high - 1; j++)
    {
        // If current element is smaller than the pivot
        if (v[j].getCountry() < pivotCountry)
        {
            i++; // increment index of smaller element
            swap(v[i], v[j]);
        }
        else if (v[j].getCountry() == pivotCountry && v[j].getTotal_Profit() > pivotTotal_Profit)
        {
            i++; // increment index of smaller element
            swap(v[i], v[j]);
        }
    }
    swap(v[i + 1], v[high]);
    return (i + 1);
}

template <class T>
void quickSort(vector<T> &v, int low, int high)
{
    if (low < high)
    {
        /* pi is partitioning index, arr[p] is now 
		at right place */
        int pi = partition(v, low, high);

        // Separately sort elements before
        // partition and after partition
        quickSort(v, low, pi - 1);
        quickSort(v, pi + 1, high);
    }
}

template <class T>
void printv(vector<T> v)
{
    for (int i = 0; i < v.size(); i++)
    {
        cout << v[i].getCountry() << "\t" << v[i].getItem_Type() << "\t" << v[i].getOrder_ID() << "\t" << v[i].getUnit_Sold() << "\t" << v[i].getTotal_Profit() << endl;
    }
}

/*int main()
{
    vector<order> a1;

    order *abc = new order("x", "Fruits", "443368995", 1593, 3839.13);

    order o1 = order("x", "Fruits", "443368995", 1593, 3839.13);
    order o2 = order("a", "Clothes", "667593514", 4611, 338631.84);
    order o3 = order("e", "Meat", "940995585", 360, 20592);
    order o4 = order("e", "Clothes", "880811536", 562, 41273.28);
    order o5 = order("d", "Beverages", "174590194", 3973, 62217.18);

    a1.push_back(o1);
    a1.push_back(o2);
    a1.push_back(o3);
    a1.push_back(o4);
    a1.push_back(o5);
    a1.push_back(*abc);

    quickSort(a1, 0, a1.size() - 1);
    printv(a1);

    //int clocktime = clock();

    return 0;
}*/