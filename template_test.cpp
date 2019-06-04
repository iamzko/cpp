#include <iostream>
#include <sstream>
#include <string>
#include <cstring>
using std::cout;
using std::endl;

template <typename T> int compare(const T &v1, const T &v2) {
  if (v1 < v2)
    return -1;
  if (v2 < v1)
    return 1;
  return 0;
}
template <>
int compare(const char* const &p1,const char * const &p2)
{
  return strcmp(p1, p2);
}

template <typename T>
std::string debug_rep(const T &t) { //版本一
  std::ostringstream ret;
  ret << t;
  return ret.str();
}

template <typename T> std::string debug_rep(T *p) { //版本二
  std::ostringstream ret;
  ret << "pointer: " << p;
  if (p)
    ret << " " << debug_rep(*p);
  else
    ret << " null pointer";
  return ret.str();
}
std::string debug_rep(const std::string &s) { return '"' + s + '"'; }
std::string debug_rep(char *p) {
  cout << "* ";
  return debug_rep(std::string(p));
}
std::string debug_rep(const char *p) {
  cout << "const * ";
  return debug_rep(std::string(p));
}

template <typename T> std::ostream &print(std::ostream &os, const T &t) {
  return os << t;
}
template <typename T, typename... Args>
std::ostream &print(std::ostream &os, const T &t, const Args &... rest) {
  os << t << ", ";
  return print(os, rest...);
}

template <typename... Args>
std::ostream &errormsg(std::ostream &os, const Args &... rest) {
  return print(os, debug_rep(rest)...);
}

int main() {
  int i = 666;
  std::string s("hi");
  cout << debug_rep(s) << endl;
  cout << debug_rep(&s) << endl; //调用第二个版本的函数
  const std::string *sp = &s;
  cout << debug_rep(sp)
       << endl; //两个函数版本都可以用，但根据匹配规则会精确匹配第二个版本
  cout << debug_rep(s)
       << endl; //当存在多个同样好的函数模板时，编译器选择最特例化的版本
  //一个非模板函数比一个函数模板更好
  cout << debug_rep("today is a fine day") << endl;
  std::cout << compare(1, 3) << std::endl;
  print(cout, i, s, 42);
  cout << endl;
  errormsg(std::cerr, 1, 23, 4, "error");
  cout << endl;
  const char *ss1 = "yo", *ss2 = "man";
  cout << compare(ss1, ss2) << endl;
}