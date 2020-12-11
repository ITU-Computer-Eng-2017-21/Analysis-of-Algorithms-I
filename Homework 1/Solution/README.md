for run g++ -std=c++11 main.cpp
then ./a.out N

Part 2 algorithm files in Part 2 directory.
For test you should add this sort files to main.cpp
(#include sort_by_profit.cpp)
(#include sort_by_az.cpp)

For worst case tests (sorted to sorted) you should change files on main.cpp
file.open("sales.txt");
ofstream myfile("sorted.txt");
