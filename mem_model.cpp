#include <iostream>
#if 0
struct A {
  int ax;
  int *a;
  virtual void f0() { a = new int[100]; }
  virtual void bar() {
      std::cout << sizeof(this) << std::endl;
      delete[] a;
  }
};
struct B : virtual public A /****************************/
{                           /* */
  int bx;                   /* A */
  void f0() override {}     /* v/ \v */
}; /* / \ */                /* B C */
struct C : virtual public A /* \ / */
{                           /* \ / */
  int cx;                   /* D */
  void f0() override {}     /* */
};                          /****************************/
struct D : public B, public C {
  int dx;
  void f0() override {}
};
#endif
#if 1
int c_a = 0, c_b = 0, d_a = 0, d_b = 0;
struct A {
  int *ax;
  int a;
  A(const A& rhs) {
      a = rhs.a;
      std::cout << "a copy" << std::endl;
  }
  A() {
    std::cout << sizeof(*this) << std::ends;
    std::cout << "a_c"<<c_a++ << std::endl;
  }
  ~A() {
    std::cout << sizeof(*this) << std::ends;
    std::cout << "a_d"<<d_a++ << std::endl;
  }
};
struct B : public A {
  int *bx;
  int b;
  B(const B& rhs):A(rhs)
  {
      b = rhs.b;
      std::cout << "b copy" << std::endl;
  }
  B():A() {
    std::cout << sizeof(*this) << std::ends;
    std::cout << "b_c"<<c_b++ << std::endl;
  }
  ~B() {
    std::cout << sizeof(*this) << std::ends;
    std::cout << "b_d"<<d_b++ << std::endl;
  }
};
struct D : public B {
  int dx;
  void d() {}
};
#endif
int main() {
    using namespace std;
    B xxx;
    xxx.a = 1;
    xxx.b = 2;
    cout << xxx.a << " " << xxx.b << endl;
    B yyy(xxx);
    cout << yyy.a << " " << yyy.b << endl;

    int size = 1000;
    int *array  = new int[size];
    array = new int[100];
    delete[] array;
}