#include <iostream>
#include <fstream>
#include <string>

#include <sstream>
#include <vector>

using namespace std;

#include "sort.cpp"

int main(int argc, char const *argv[])
{

	ifstream file;
	file.open("sales.txt");

	if (!file)
	{
		cerr << "File cannot be opened!";
		exit(1);
	}

	int N = stoi(argv[1]); //read value of N from command line
	string line;

	vector<order> orderlist;

	getline(file, line); //this is the header line

	for (int i = 0; i < N; i++)
	{
		getline(file, line, '\t'); //country (string)
		string Country = line;

		getline(file, line, '\t'); //item type (string)
		string Item_Type = line;

		getline(file, line, '\t'); //order id (string)
		string Order_ID = line;

		file >> line; //units sold (integer)
		int Units_Sold = stoi(line);

		file >> line; //total profit (float)
		float Total_Profit = stof(line);

		getline(file, line, '\n'); //this is for reading the \n character into dummy variable.

		order *new_order = new order(Country, Item_Type, Order_ID, Units_Sold, Total_Profit);
		orderlist.push_back(*new_order);
	}
	clock_t start; // time operation
	double duration;

	start = clock();

	quickSort(orderlist, 0, orderlist.size() - 1); //QuickSort Algorithm

	duration = (clock() - start) / (double)CLOCKS_PER_SEC;
	cout << "Execution Time: " << duration << endl;

	ofstream myfile("sorted.txt"); // write to txt file
	if (myfile.is_open())
	{
		myfile << "Country"
			   << "\t"
			   << "Item Type"
			   << "\t"
			   << "Order ID"
			   << "\t"
			   << "Units Sold"
			   << "\t"
			   << "Total Profit"
			   << "\n";

		for (int i = 0; i < orderlist.size(); i++)
		{
			myfile << orderlist[i].getCountry() << "\t" << orderlist[i].getItem_Type() << "\t" << orderlist[i].getOrder_ID() << "\t" << orderlist[i].getUnit_Sold() << "\t" << orderlist[i].getTotal_Profit() << "\n";
		}
	}

	return 0;
}