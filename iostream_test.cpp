#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <strstream>

using std::locale;
int main()
{
    setlocale(LC_ALL, "chs");
    //std::wcout.imbue(locale(""));
    //using namespace std;
    std::wcout << L"s你好" << std::endl;
    std::cout << std::string("s你好") << std::endl;
   // std::cout.exceptions(std::ios::eofbit|std::ios::failbit|std::ios::badbit);
    //std::cout.exceptions();
    //std::cout.setstate(std::ios::failbit);
    std::cout << std::showpos << 1234 <<std::put_money(1234) <<std::endl;
    std::cout << 2233 << std::endl;
    std::cout.width(10);
    std::cout.fill('*');
    std::cout << std::internal<< 11234 << std::endl;
    std::cout << std::cout.flags() << std::endl;
    std::ofstream file("nidaye.txt",std::ios::out|std::ios::app);
    if(!file)
    {
        std::cerr << "can not open file" << std::endl;
        return (-1);
    }

    for (int i = 0; i < 10;++i)
    {
        file.width(i+1);
        file << i << std::endl;
    }

    file << "hello world" << std::endl;
    if(file.is_open())
    {
        std::cout << "file is open" << std::endl;
    }
    float x = 1.333333;
    std::ostrstream buffer;
    buffer << "float x:" << x << std::ends;
    std::cout << buffer.str() << std::endl;
    char *p = buffer.str();
    buffer.freeze(false);
    buffer.seekp(0,std ::ios::beg);
    buffer << "new conternt here" << std::ends;
    std::cout << buffer.str() << std::endl;
    buffer.freeze(false);
    //std::cout << p << std::endl;
    std::cerr.tie(&std::cout);
    std::cout << "haha" << std::endl;
    //std::cout.rdbuf(file.rdbuf());
    std::filebuf buf;
    std::ostream output(&buf);
    std::istream input(&buf);
    buf.open("nidaye2.txt",std::ios::in |std::ios::out |std::ios::trunc);
    for (int i = 10; i > 0;--i)
    {
        output << i << ". line" << std::endl;
        input.seekg(0);
        char c;
        while (input.get(c))
        {
            std::cout.put(c);

        }
        std::cout << std::endl;
        input.clear();
    }
}