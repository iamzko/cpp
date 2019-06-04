#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>
#include <functional>


using namespace std;
bool isShorter(const string &s1, const string &s2) {
  return s1.size() < s2.size();
}

int main() {
  int val = 42;
  vector<int> target = {1, 22, 34, 53, 23, 5, 42, 89, 87, 96};
  auto result = find(target.cbegin(), target.cend(), val);
  cout << "the value "
       << (result == target.cend() ? "is not present" : "is present") << endl;
  // vector<string> m(10, "a_");
  // string total = accumulate(m.begin(), m.end(), string(""));
  // cout << "the last string is " << total << endl;
  vector<int> vec;
  auto it = back_inserter(vec);
  *it = 42;
  cout << vec[0] << endl;
  fill_n(it, 10, 2);
  cout << "vec size is " << vec.size() << " now and vec[2] is " << vec[2]
       << endl;
  // back_inserter插入后会指向下一个
  int a1[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  int a2[sizeof(a1) / sizeof(*a1)];
  auto ret = copy(begin(a1), end(a1), a2);
  cout << a2[2] << endl;
  vector<string> color = {"fox", "jumps", "over", "quick",
                          "red", "fox",   "the",  "red"};
  sort(color.begin(), color.end());
  cout << "after sort" << endl;
  for (auto it = color.begin(); it != color.end(); ++it) {
    cout << *it << '\t';
  }
  cout << endl;
  auto end_unique = unique(color.begin(), color.end());
  color.erase(end_unique, color.end());
  cout << "after uniq" << endl;
  for (auto it = color.begin(); it != color.end(); ++it) {
    cout << *it << '\t';
  }
  cout << endl;
  cout << "after stable_sort" << endl;
  stable_sort(color.begin(), color.end(), isShorter);
  for (auto it = color.begin(); it != color.end(); ++it) {
    cout << *it << '\t';
  }
  cout << endl;
  cout << "lambda test" << endl;
  auto f = [] { return 42; };
  cout << f() << endl;
  auto f2 = [](int x) -> int { return x * x; };
  cout << f2(16) << endl;
  int n = 100;
  auto f3 = [n](int k) { return n + k; };
  std::cout << f3(3) << endl;
  auto b = 3;
  auto b2 = [n, &b](int c) -> int { // n只读， b读写
    b = c * 2;
    return n + c;
  }(1000);

  std::cout << n << std::endl;
  std::cout << b << std::endl;
  std::cout << b2 << std::endl;
  for_each(color.begin(), color.end(), [](const string &s) { cout << s << '\t'; });
  cout << endl;

  auto bind_test = bind(isShorter,std::placeholders::_1,string("abcd"));
  cout << "after bind:" << bind_test("123") << endl;
  ostream &os = cout;
  for_each(color.begin(), color.end(), [&os](const string &s) { os << s; });
  cout << endl;
  
}