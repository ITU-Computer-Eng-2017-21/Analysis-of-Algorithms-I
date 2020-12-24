#include <iostream>
#include <fstream>
#include <string>

#include <sstream>
#include <math.h>

using namespace std;
#include "pq.cpp"

// Driver Code
int main(int argc, char const *argv[])
//int main()
{
    // Insert the element to the
    // priority queue
    srand(time(0));
    ifstream file;
    file.open("locations.txt");

    if (!file)
    {
        cerr << "File cannot be opened!";
        exit(1);
    }

    string line;
    getline(file, line); // header line

    int m = stoi(argv[1]);
    double p = stod(argv[2]);
    int op_add = 0, op_update = 0;

    //int m = 14;
    //double p = 0.65;

    for (int op = 1; op < m + 1; op++)
    {
        if (op % 100 == 0 && size > 0)
        {
            cout << "The distance of the called taxi: " << callTaxi() << endl;
        }
        else
        {
            int ratio = p * 100;
            int r = rand() % 100;

            if (r < ratio)
            {
                op_update++;
                if (size >= 0)
                {
                    int x = rand() % Heap.size();
                    {
                        update(x, Heap[x] - 0.01);
                    }
                }
            }
            else if (r >= ratio)
            {
                float longitude, latitude;
                file >> longitude;
                file >> latitude;

                float distance = sqrt(longitude * longitude + latitude * latitude);
                add(distance);

                getline(file, line, '\n'); //this is for reading the \n character into dummy variable.
                op_add++;
            }
        }
    }

    cout << "The number of taxi additions: " << op_add << " and distance updates: " << op_update << endl;
    int i = 0;

    // Priority queue before extracting max
    cout << "Priority Queue : ";
    while (i <= size)
    {
        cout << Heap[i] << " ";
        i++;
    }

    return 0;
}
