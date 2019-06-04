#include <iostream>
#include <string>
#include <memory>
using namespace std;

unique_ptr<string> f(string &t)
{
    return unique_ptr<string>(new string(t));
}

int main()
{
    //unique_ptr 拥有它指向的对象，某个时刻只能有一个unique_ptr指向一个给定的对象
    unique_ptr<string> p1(new string("first unique_ptr"));
    cout << "p1 is " << *p1 << endl;
    unique_ptr<string> p2(p1.release());
    cout << "p2 is " << *p2 << endl;
    if(p1 == nullptr)
        cout << "p1 is null now" << endl;
    p2.reset();
    if(p2 == nullptr)
        cout << "p2 is null now " << endl;
    string s1 = string("test unique_ptr return from function ");
    p2 = f(s1);
    cout << "now p2 is " << *p2 << endl;
}