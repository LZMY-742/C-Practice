#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <memory>
#include "shabi.h"
#include "SearchWord.h"
#include "Sales_data.h"


using std::cin;
using std::cout;
using std::endl;
using std::ifstream;
using std::istream;
using std::ofstream;
using std::string;
using std::vector;
using std::shared_ptr;

shared_ptr<vector<int>> vecFactory()
{
  return std::make_shared<vector<int>>();
}
shared_ptr<vector<int>> read_vec(shared_ptr<vector<int>> v,istream& is)
{
  int num=0;
  while(is>>num)
    (*v).push_back(num);
  return v;
}

string make_plural(size_t ctr, const string &word, const string &ending)
{
  return (ctr>1)? word+ending : word;
}
std::ostream& print(std::ostream& os, QueryResult& qr) //definition for print
{
    os<<qr.sought<<" occurs "<<qr.count<<" "
    <<make_plural(qr.count, "times", "s")<<endl;
    for(auto num : *qr.lines)
        os<<"\t(Line "<<num+1<<") "<<qr.file.get(num)<<endl;
    return os;
}

void runQueries(ifstream &infile)
{
  TextQuery tq(infile);
  do
  {
    /* code */
    cout<<"enter word to look for, or q to quit: ";
    string s;
    if(!(cin>>s) || s== "q") break;
    auto qr = tq.query(s); //不能把引用绑定在一个右值上
    print(cout, qr)<<endl; 
  } while (true);
}

int main()
{
  ifstream infile("input.txt");
  runQueries(infile);
  return 0;
}