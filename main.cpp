#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include "shabi.h"
using std::cerr;
using std::cin;
using std::cout;
using std::endl;
using std::istream;
using std::ofstream;
using std::string;
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
string combine2(const string &prefix, string &name, const string &suffix) //9.46
{
  name.insert(0, prefix);
  name.insert(name.size(), suffix);
  return name;
}
int main()
{
  int a[2];
  int a[0];
  cout << "Hello World!" << endl;
  cout << "haha" << endl;
  return 0;
}