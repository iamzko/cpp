#pragma once
#include <iostream>
#include <memory>
#include <set>
#include <string>

//#include "Folders.h"

using namespace std;
class Message;
class Folder {
public:
  Folder(const string& n):name(n) {};
  ~Folder() = default;
  void addMsg(Message *);
  void remMsg(Message *);
  void prints() { cout << "folder name is " << endl; }
  void print_m();

  private:
  string name;
  set<Message *> messages;
};
void Folder::addMsg(Message *m) { messages.insert(m); }
void Folder::remMsg(Message *m) { messages.erase(m); }
void Folder::print_m()
{
    for(auto l : messages)
    {
         l->prints();
    }
}
class Message {
  friend class Folder;

public:
  explicit Message(const string &str = "") : contents(str){};
  Message(const Message &);
  Message &operator=(const Message &);
  ~Message();
  void prints() { cout << "contents is " << contents << endl; }
  void print_f();
  void save(Folder &);
  void remove(Folder &);

private:
  string contents;
  set<Folder *> folders;
  void add_to_Folders(const Message &);
  void remove_from_Folders();
};
void Message::print_f()
{
    for (auto f:folders)
        f->prints();

}
void Message::save(Folder &f) {
  folders.insert(&f);
  f.addMsg(this);
}
void Message::remove(Folder &f) {
  folders.erase(&f);
  f.remMsg(this);
}
void Message::add_to_Folders(const Message &m) {
  for (auto f : m.folders)
    f->addMsg(this);
}
Message::Message(const Message &m) : contents(m.contents), folders(m.folders) {
  add_to_Folders(m);
}
void Message::remove_from_Folders() {
  for (auto f : folders)
    f->remMsg(this);
}
Message::~Message() { remove_from_Folders(); }
Message &Message::operator=(const Message &rhs) 
{
  remove_from_Folders();
  contents = rhs.contents;
  folders = rhs.folders;
  add_to_Folders(rhs);
  return *this;
}
/*
void swap(Message &lhs,Message &rhs)
{
    using std::swap;
    for(auto f:lhs.folders)
        f->remMsg(&lhs);
    for(auto f:rhs.folders)
        f->remMsg(&rhs);
    swap(lhs.folders, rhs.folders);
    swap(lhs.contents, rhs.contents);
    for(auto f: lhs.folders)
        f->addMsg(&lhs);
    for(auto f:rhs.folders)
        f->addMsg(&rhs);
}*/