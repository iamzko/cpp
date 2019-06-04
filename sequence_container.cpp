// sequence_container contains vector, deque, list, forward_list, array, string
// ...
#include <array>
#include <iostream>
#include <list>
#include <stack>
#include <string>
#include <vector>


using namespace std;
int main() {
  vector<int> a(10);
  cout << a.max_size() << endl;
  cout << a.size() << endl;
  cout << a.empty() << endl;
  int i = 0;
  for (vector<int>::iterator it = a.begin(); it != a.end(); ++it) {
    *it = i++;
  }
  for (vector<int>::reverse_iterator rt = a.rbegin(); rt != a.rend(); ++rt) {
    cout << *rt << '\t';
  }
  cout << endl;
  for (vector<int>::const_iterator rt = a.cbegin(); rt != a.cend(); ++rt) {
    cout << *rt << '\t';
  }
  cout << endl;
  for (auto it = a.rbegin(); it != a.rend(); ++it) {
    cout << *it << '\t';
  } // auto与begin或end结合使用时，获得的迭代器类型依赖于容器类型
  //当不需要写访问时，应使用cbegin和cend
  cout << endl;
  list<string> authors = {"milton", "shankespere", "austen"};
  vector<const char *> articles = {"a", "an", "the"};
  list<string> list2(authors);
  list<string> list3(articles.begin(),
                     articles.end()); // const char* 会转化为string对象
  for (auto it = list3.begin(); it != list3.end(); ++it) {
    cout << *it << '\t';
    if (it == list3.end()) {
      cout << endl;
    }
  }
  auto it1 = a.begin();
  list<int> list4(it1, it1 + 5);
  for (auto it = list4.begin(); it != list4.end(); ++it) {
    cout << *it << '\t';
    if (it == list4.end()) {
      cout << endl;
    }
  }
  cout << endl;

  //当定义一个array时，除了指定元素类型，还要指定容器大小

  array<int, 10> array1 = {100, 200, 309, 400, 566,
                           777, 888, 999, 666}; //不允许array1 =
                                                //{0}在数组声明后出现，不能将花括号列表赋予数组
  array<int, 10> copy = array1;
  array<int, 10> array2;
  swap(copy, array2); // swap会真正交换两个array的元素
  for (auto it = array2.begin(); it != array2.end(); ++it) {
    cout << *it << '\t';
  }
  cout << endl;

  //顺序容器中可使用assign的方法
  list<string> names;
  names.push_front("a");
  names.assign(articles.begin(), articles.end());
  names.assign(10, "b");
  for (auto it1 = names.begin(); it1 != names.end(); ++it1) {
    cout << *it1 << '\t';
  }
  cout << ends;

  string s_test("1234567");
  cout << stof(s_test) << endl;
  for(auto x:array2)
  {
    cout << x <<ends;
  }
  cout << endl;
  wchar_t old_str1[] = L"hello";
  char32_t old_str2[] = U"hello";
  cout << sizeof(old_str2) << endl;
#if 0
  stack<string> words;
  string str;
  cout << "enter some words:" <<endl;
  while(cin>> str)
  {
      words.push(str);
  }
  while(words.empty() == false)
  {
      cout << words.top() << endl;
      words.pop();
  }
  cout << endl;
  #endif
}