#pragma once
#include <iostream>
#include <string>
#include <set>
#include <memory>
#include "class_test.h"

using namespace std;
class Folder
{
    public:
        Folder() = default;
        ~Folder()=default;

    private:
        set<Message *> messages;
        void addMsg(Message &);
        void remMsg(Message &);
};
void Folder::addMsg(Message &m)
{
    messages.insert(&m);
}
void Folder::remMsg (Message &m)
{
    messages.erase(&m);
}
