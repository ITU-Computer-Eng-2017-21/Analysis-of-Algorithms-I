#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main(void)
{

	ifstream file;
	file.open("sales.txt");

	if (!file)
	{
		cerr << "File cannot be opened!";
		exit(1);
	}

	int N = 100; //you should read value of N from command line
	string line;

	getline(file, line); //this is the header line

	for (int i = 0; i < N; i++)
	{

		getline(file, line, '\t'); //country (string)
		getline(file, line, '\t'); //item type (string)
		getline(file, line, '\t'); //order id (string)
		file >> line;			   //units sold (integer)
		file >> line;			   //total profit (float)
		getline(file, line, '\n'); //this is for reading the \n character into dummy variable.
	}

	return 0;
}
