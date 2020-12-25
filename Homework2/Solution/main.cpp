#include <iostream>
#include <fstream>
#include <string>

#include <sstream>
#include <math.h>
#include <chrono>

using namespace std;
#include "pq.cpp" // priority queue with binary heap

int main(int argc, char const *argv[])
{
    srand(time(0));

    ifstream file;
    file.open("locations.txt"); // input file

    if (!file)
    {
        cerr << "File cannot be opened!";
        exit(1);
    }

    string line;
    getline(file, line); // header line

    int m = stoi(argv[1]);         // total operation number
    double p = stod(argv[2]);      // update probablity
    int op_add = 0, op_update = 0; // counter for add and update operations

    auto t1 = chrono::high_resolution_clock::now();

    for (int op = 1; op < m + 1; op++)
    {
        if (op % 100 == 0 && size >= 0) // for protection to segmentation fault
        {                               // if heap is empty you couldnt call taxi
            cout << "The distance of the called taxi: " << call() << endl;
        }
        else
        {
            int ratio = p * 100;
            int r = rand() % 100;

            if (r < ratio) // update taxi
            {
                if (size >= 0) // for protection to segmentation fault
                {              // when program cannot update if head is empty
                    int x = rand() % taxi.size();
                    {
                        update(x, taxi[x] - 0.01);
                    }
                }
                op_update++;
            }
            else // add taxi
            {
                double h_longitude = 33.40819;
                double h_latitude = 39.19001;

                float longitude, latitude;
                file >> longitude; // read longitude from file
                file >> latitude;  // read latitude from file

                double distance = sqrt(pow((longitude - h_longitude), 2) + pow((latitude - h_latitude), 2)); // Euclidian distance
                add(distance);

                getline(file, line, '\n'); // this is for reading the \n character into dummy variable.
                op_add++;
            }
        }
    }

    auto t2 = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> duration = t2 - t1;

    cout << "The number of taxi additions: " << op_add << endl;
    cout << "The number of distance updates: " << op_update << endl;

    cout << "Total running time is: " << duration.count() << " milliseconds." << endl;

    /*for (int i = 0; i < taxi.size(); i++)
    {
        cout << call() << endl;
    }*/

    return 0;
}
