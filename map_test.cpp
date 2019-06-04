#include <fstream>
#include <functional>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <utility>

using namespace std;

const string &transform(const string &s, const map<string, string> &m) {
  auto map_it = m.find(s);
  if (map_it != m.cend()) {
    return map_it->second;
  } else {
    return s;
  }
}

map<string, string> buildMap(ifstream &map_file) {
  map<string, string> trans_map;
  string key;
  string value;
  while ((map_file >> key) && (getline(map_file, value))) {//ifstream定义在fstream中,记得要include
    if (value.size() > 1) {
      trans_map[key] = value.substr(1); //跳过前导空格
    } else {
      throw runtime_error("no rule for " + key);
    }
  }
  return trans_map;
}

void word_transform(ifstream &map_file, ifstream &input) {
  auto trans_map = buildMap(map_file);
  string text;
  while (getline(input, text)) {
    istringstream stream(text); //读取每个单词
    string word;
    bool firstword = true;
    while (stream >> word) {
      if (firstword) {
        firstword = false;
      } else {
        cout << " ";
        cout << transform(word, trans_map);
      }
      cout << endl;
    }
  }
}
int main() {
  /*
  map<string,size_t> word_count;
  string word;
  while(cin>>word)
      ++word_count[word];
  for(const auto &w :word_count)
      cout << w.first << " occurs " << w.second << ((w.second > 1) ? " times" :
  " time") << endl;
  */
  /*
   set<string> exc;
   string word2;
   while(cin>>word2)
       exc.insert(word2);
   for (auto it = exc.begin(); it != exc.end();++it)
       cout << *it << '\t';
   cout << endl;
   */
  // pair<string, string> anno("a","b");
  auto anno = make_pair("a", "b");
  cout << " anno.first:" << anno.first << "\tanno.second:" << anno.second
       << endl;
  cout << "anno first type is : " << (1) << endl;
  map<string, size_t> word_count;
  string word;
  while (cin >> word) {
    auto ret = word_count.insert({word, 1});
    if (ret.second)
      cout << "insert successfully" << endl;
    else
      cout << word << " has already exists" << endl;
  }
  word_count["a"] = 2;
  word_count["kate"] = 5;
  for_each(word_count.begin(), word_count.end(),
           [](const pair<string, size_t> &s) {
             cout << s.first << ":" << s.second << endl;
           });
  cout << word_count.find("a")->first
       << endl; // find返回的是一个迭代器,解引用之后为pair

  cout << endl;
}