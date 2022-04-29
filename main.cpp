#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include "shabi.h"
#include <stack>
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
int main()
{
  vector<string> v1{"10", "(", "25", "/", "5", ")", "7", "6"};
  string linshi;
  stack<string, vector<string>> stack1(v1); //新建stack stack1
  while (!stack1.empty())
  {
    if (stack1.top() == ")") //如果栈顶是右括号
    {
      stack1.pop(); //弹出右括号
      while (stack1.top() != "(") //在到左括号之前
      {
        linshi.insert(0, stack1.top()); //把每个元素插到linshi里
        stack1.pop(); //把元素弹出
        if (stack1.empty()) //如果没遇见左括号直接退出整个循环
          break;
      }
    }
    else //;如果没遇见右括号
    {
      stack1.pop(); //弹出元素
    }
  }
  string shuzi = "0123456789";
  size_t first_not_of = linshi.find_first_not_of(shuzi);//找出第一个不是数字的地方
  string jieguo;
  string a = linshi.substr(0, first_not_of);//第一个数字
  string b = linshi.substr(first_not_of + 1);//运算符右边的数字
  if (linshi[first_not_of] == '+')
    jieguo = jia(stoi(a), stoi(b));
  if (linshi[first_not_of] == '-')
    jieguo = jian(stoi(a), stoi(b));
  if (linshi[first_not_of] == '*')
    jieguo = cheng(stoi(a), stoi(b));
  if (linshi[first_not_of] == '/')
    jieguo = chu(stoi(a), stoi(b));
  stack1.push(jieguo);
  cout << stack1.top()<<endl;
  return 0;
}