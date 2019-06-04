#include <iostream>
#include "class_test.h"

int main()
{
    Message m1("test1");
    Folder f1("folder1");
    m1.save(f1);
    f1.print_m();
    m1.print_f();
}