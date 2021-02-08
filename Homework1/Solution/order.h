#include <string>
using namespace std;

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

order::order(string newCountry, string newItem_Type, string newOrder_ID, int newUnits_Sold, float newTotal_Profit)
{
    Country = newCountry;
    Item_Type = newItem_Type;
    Order_ID = newOrder_ID;
    Units_Sold = newUnits_Sold;
    Total_Profit = newTotal_Profit;
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