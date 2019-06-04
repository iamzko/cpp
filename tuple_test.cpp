#include <iostream>
#include <string>
#include <tuple>

using namespace std;

int main()
{
    tuple<int, double, long, unsigned long, string> t1(1, 2.0, 44444444, 55555, "hi");
    cout << get<0>(t1) << endl;
    cout << get<4>(t1) << endl;
    string temp;
    cin >> temp;
    try
    {
        if(temp.size() < 3)
            throw -1;
        cout << "what you input is: " << temp << endl;
    }
    catch(int e)
    {
        cout << e << ends << "error happend " << endl;
    }
}