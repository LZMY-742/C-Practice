#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "shabi.h"
#include <stack>
#include <list>
#include <algorithm>
#include <numeric>
#include <iterator>
#include "Sales_data.h"
#include <functional>
#include <map>
#include<set>
#include <cctype>
#include <utility>
#include <stdexcept>
#include <sstream>
#include <unordered_map>

using std::cerr;
using std::cin;
using std::cout;
using std::endl;
using std::ifstream;
using std::istream;
using std::ofstream;
using std::stack;
using std::string;
using std::vector;
using std::list;
using std::ostream_iterator;
using std::istream_iterator;
using std::map;
using std::set;
using std::multiset;
using std::pair;
using std::multimap;
using std::runtime_error;
using std::istringstream;
using std::unordered_map;

using namespace std::placeholders;
bool compareIsbn(const Sales_data& lhs, const Sales_data& rhs)
{
  return lhs.isbn()<rhs.isbn();
}
unordered_map<string,string> buildMap(ifstream &map_file)
{
  unordered_map<string,string> trans_map;
  string key, value;
  while(map_file>>key && getline(map_file,value))
  {
    if(value.size()>1)
      trans_map[key] = value.substr(1);
    else
      throw runtime_error("no rule for "+key);
  }
  return trans_map;
}
const string& transform(const string& s, const unordered_map<string,string>& m)
{
  auto target_itr = m.find(s);
  if(target_itr != m.cend())
    return target_itr->second;
  else
    return s;
}
void word_transform(ifstream& map_file, ifstream& input)
{
  auto trans_map = buildMap(map_file);
  string text;
  while(getline(input, text))
  {
    istringstream stream(text);
    string word;
    bool first = true;
    while(stream>>word)
    {
      if(first)
        first = false;
      else
        cout<<" ";
      cout<<transform(word,trans_map);
    }
    cout<<endl;
  }
}

int main()
{
  ifstream map_file("input.txt"),input("input2.txt");
  if(!map_file.is_open() || !input.is_open())
    throw runtime_error("files cannot be opened!");
  word_transform(map_file,input); //注意本程序有个漏洞是如果要替换的词在句子结尾，最后一位会是标点符号，这样程序就无法检测到要替换它因为标点符号和单词读取到一个string里了
  return 0;
}