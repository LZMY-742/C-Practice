#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include "shabi.h"
#include <stack>
#include <list>
#include <algorithm>
#include <numeric>
#include <iterator>
#include <bits/stdc++.h>
#include "Sales_data.h"
#include <functional>
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

using namespace std::placeholders;
istream &xiba(istream &is)
{
  int data;
  while (is >> data)
  {
    cout << data << endl;
  }
  cout << is.eof() << endl;
  is.clear();
  return is;
}
string combine(const string &prefix, const string &name, const string &suffix) // 9.45
{
  return prefix + " " + name + " " + suffix;
}
string combine2(const string &prefix, string &name, const string &suffix) // 9.46
{
  name.insert(0, prefix);
  name.insert(name.size(), suffix);
  return name;
}
string jia(int a, int b)
{
  return std::to_string(a+b);
}
string jian(int a, int b)
{
  return std::to_string(a-b); 
}
string cheng(int a,int b)
{
  return std::to_string(a*b);
}
string chu(int a,int b)
{
  return std::to_string(a/b);
}
void elimDups(vector<string> &words)//清除vector中重复的单词
{
  sort(words.begin(),words.end());
  auto end_itr = unique(words.begin(),words.end());
  words.erase(end_itr,words.end());
}
bool isShorter(const string& s1, const string &s2)
{
  return s1.size()<s2.size();
}
bool compareIsbn( const Sales_data& s1,  const Sales_data& s2)
{
  return s1.isbn()<s2.isbn();//按isbn的字典顺序排序
}
bool moreThanFive (const string& s1)
{
  return s1.size()>5;
}
void biggies(vector<string> &words, vector<string>::size_type sz)
{
  elimDups(words);
  auto end_sz = stable_partition(words.begin(),words.end(),[sz](const string& s){return s.size()>=sz;});
  for_each(words.begin(),end_sz,[](const string& s){cout<<s<<" ";});
}
void xyz(int x, int y, int z)
{
	cout << "print: x=" << x << ",y=" << y << ",z=" << z << endl;
}
bool check_sz(const string& s, vector<string>::size_type sz)
{
  return s.size()>=sz;
}
void biggies2(vector<string> &words, vector<string>::size_type sz)
{
  elimDups(words);//删除重复的单词
  auto end_sz = stable_partition(words.begin(),words.end(),bind(check_sz,_1,sz));
  for_each(words.begin(),end_sz,[](const string& s){cout<<s<<" ";});
}
bool comp (const string& s1, const string& s2)
{
  return s1.size()==s2.size();
}
void elimDups_list(list<string>& words)
{
  words.sort();
  words.unique();
}
int main()
{
  ifstream in("input.txt");
  istream_iterator<string> str_in (in),end_in;
  ostream_iterator<string> os(cout," ");
  list<string> words;
  copy(str_in,end_in,back_inserter(words));
  elimDups_list(words);
  copy(words.cbegin(),words.cend(),os);//测试代码
  return 0;
}