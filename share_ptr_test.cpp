#include <iostream>
#include <list>
#include <memory>
#include <string>
#include <vector>

using namespace std;

class StrBlob {
public:
  typedef vector<string>::size_type size_type;
  StrBlob();
  StrBlob(initializer_list<string> il);
  size_type size() const { return data->size(); }
  bool empty() const { return data->empty(); }
  void push_back(const string &t) { data->push_back(t); }
  void pop_back();
  string &front();
  string &back();

private:
  shared_ptr<vector<string>> data;
  void check(size_type i, const string &msg) const;
};

StrBlob::StrBlob() : data(make_shared<vector<string>>()) {}
StrBlob::StrBlob(initializer_list<string> il)
    : data(make_shared<vector<string>>(il)) {}

void StrBlob::check(size_type i, const string &msg) const {
  if (i >= data->size()) {
    throw out_of_range(msg);
  }
}

string &StrBlob::front() {
  check(0, "front on empty StrBlob");
  return data->front();
}

string &StrBlob::back() {
  check(0, "back on empty StrBlob");
  return data->back();
}
void StrBlob::pop_back() {
  check(0, "pop_back on empty StrBlob");
  data->pop_back();
}

string *new_test() { return new string("made by another function"); }

void f(string *t) {
  shared_ptr<string> sp(t);
  cout << "use string * in f()"
       << "\tsp is " << *sp << endl;
}
void f2(shared_ptr<string> t) {
  *t = string("this is f2 yo");
  cout << "in f2 t len is " << (*t).length() << endl;
  cout << "in f2 t is " << *t << endl;
}
int main() {
  shared_ptr<string> p1 = make_shared<string>("nihao");
  if (p1) {
    *p1 = "hello\n";
    cout << "p1 is " << *p1 << endl;
  }
  int *p2 = new int(10000);
  //*p2 = 1000;
  string *p3 = new string(100, 'u');
  //*p3 = "hello 2";
  cout << "p2 is " << *p2 << endl;
  cout << "p3 is " << *p3 << endl;
  auto p4 = new auto("ssssssss");
  cout << "p4 is " << *p4 << endl;

  string *p5 = new (nothrow) string("定位new");
  cout << "p5 is " << *p5 << endl;
  delete p5;

  string *p6 = new_test();
  cout << "p6 is " << *p6 << endl;
  delete p6;

  // shared_ptr<string> p7;
  // p7 = new string("this is pointed by a shared_ptr");
  //不能将内置指针隐式转换为一个智能指针，必须使用直接初始化形式
  shared_ptr<string> p7(new string("this is pointed by shared_ptr"));
  cout << "p7 is " << *p7 << endl;
  string *p8 = p7.get();
  cout << "p8 is " << *p8 << endl;
  p7.reset(new string("after reset "));
  cout << "after reset p7 is " << *p7
       << endl; // p8这时候就会指向一片被释放的内存，变成悬空指针
  string *p9 = new string("test normal * change to shared_ptr in function");
  f(p9);
  // cout << "p9 is " << *p9 << endl;//在f（）
  // 中p9转换为智能指针，且在函数结束后，所指向区域被释放，此时p9为悬空指针
  shared_ptr<string> p10(new string("this is p10"));
  f2(p10);
  cout << "p10 is " << *p10 << endl;
  string *p11 = p10.get();
  *p10 = "new ddddd";
  cout << "p11 is " << p11 << "\n"
       << "p10 now is " << p10 << endl;
  weak_ptr<string> p12(p10);
  shared_ptr<string> p13 = p12.lock();
  cout << "p12 is " << *p13 << endl;
  p7.reset();
  weak_ptr<string> p14(p7);
  auto ret = p14.lock();
  if (!ret)
    cout << "p7 is not exist now" << endl;
  int *p15 = new int[100]();
  for (int *t = p15; t != p15 + 100; ++t) {
    cout << *t << '\t';
  }
  cout << endl;
  delete[] p15;

  //使用unique_ptr管理动态数组，必须在对象类型后面跟一对空方括号
  unique_ptr<int[]> p16(new int[10]());
  for (int i = 0; i < 10; i++) {
    cout << p16[i] << '\t';
  }
  cout << endl;
  //使用shared_ptr管理动态数组
  shared_ptr<int[]> p17(new int[10](), [](int *p) { delete[] p; });
  for (int i = 0; i != 10; ++i) {
    *(p17.get() + i) = i;
    cout << *(p17.get() + i) << '\t';
  }
  cout << endl;

  // allocator的使用
  allocator<string> al1;
  auto const p18 = al1.allocate(10);
  for (int i = 0; i < 10; ++i) {
    if (i % 2 ==0)
      al1.construct(p18 + i, to_string(i));
    else
      al1.construct(p18 + i, i, 'a' + i);
    cout << *(p18 + i) << '\t';
  }
  cout << endl;
  auto q = p18 ;
  for (int i = 0; i < 10;++i)
  {
      al1.destroy(q++);
  }

  string s1 ;
  for (int i = 0; i < 100;++i)
  {
      s1 += (i + 20);
  }
  cout << "now s1 is " << s1 << endl;
  al1.construct(p18, 100, '0');
  uninitialized_copy(s1.begin(), s1.end() , p18->begin());//注意第三个参数应为迭代器，第二个参数应为end迭代器，p18必须有分配的足够的内存空间
  cout << "now p18 is " << *p18 << endl;
  if (p18->empty()) {
    cout << "p18 is null now" << endl;
  } else {
      cout << p18->size() << endl;
      for (auto it = p18->cbegin(); it != p18->cend();++it)
          cout  << *it ;
  }
  al1.destroy(p18);
  al1.deallocate(p18, 10);
  cout << endl;
}