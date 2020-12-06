#include <string>
using namespace std;
#include <vector>
#include <iostream>
//#include "quicksort.cpp"
//#include "funct.cpp"

class order
{
private:
    string Country;
    string Item_Type;
    string Order_ID;
    int Units_Sold;
    float Total_Profit;

public:
    order(string, string, string, int, float);
    string getCountry();
    string getItem_Type();
    string getOrder_ID();
    int getUnit_Sold();
    float getTotal_Profit();
    ~order();
};

order::order(string s1, string s2, string s3, int i4, float f5)
{
    Country = s1;
    Item_Type = s2;
    Order_ID = s3;
    Units_Sold = i4;
    Total_Profit = f5;
}
string order::getCountry()
{
    return Country;
}

string order::getItem_Type()
{
    return Item_Type;
}

string order::getOrder_ID()
{
    return Order_ID;
}

int order::getUnit_Sold()
{
    return Units_Sold;
}

float order::getTotal_Profit()
{
    return Total_Profit;
}

order::~order()
{
}