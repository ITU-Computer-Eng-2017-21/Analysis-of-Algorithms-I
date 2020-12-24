#include <iostream>
#include <fstream>
#include <string>

#include <sstream>
#include <math.h>
#include <chrono>

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

    auto t1 = chrono::high_resolution_clock::now();

    for (int op = 1; op < m + 1; op++)
    {
        if (op % 100 == 0 && size >= 0)
        {
            cout << "The distance of the called taxi: " << callTaxi() << endl;
        }
        else
        {
            int ratio = p * 100;
            int r = rand() % 100;

            if (r < ratio)
            {
                if (size >= 0)
                {
                    int x = rand() % Heap.size();
                    {
                        update(x, Heap[x] - 0.01);
                    }
                }
                op_update++;
            }
            else
            {
                double h_longitude = 33.40819;
                double h_latitude = 39.19001;

                float longitude, latitude;
                file >> longitude;
                file >> latitude;

                double distance = sqrt(pow((longitude - h_longitude), 2) + pow((latitude - h_latitude), 2));
                add(distance);

                getline(file, line, '\n'); //this is for reading the \n character into dummy variable.
                op_add++;
            }
        }
    }

    auto t2 = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> elapsed = t2 - t1; //if you want milliseconds you should use: std::chrono::duration<double,milli>
    cout << "Algorithm Runtime is: " << elapsed.count() << " milliseconds." << endl;

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
