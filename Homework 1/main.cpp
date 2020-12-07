#include <iostream>
#include <fstream>
#include <string>

#include <sstream>
#include <vector>

using namespace std;

#include "sort.cpp"

int main(void)
{

	ifstream file;
	file.open("Homework 1/sales.txt");

	if (!file)
	{
		cerr << "File cannot be opened!";
		exit(1);
	}

	int N = 100; //you should read value of N from command line
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

	quickSort(orderlist, 0, orderlist.size() - 1);
	printv(orderlist);

	return 0;
}
