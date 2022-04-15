 #include <iostream>
 #include <vector>
 #include <string>
 #include <fstream>
 #include <sstream>
 using std::cout;
 using std::endl;
 using std::cin;
 using std::istream;
 using std::cerr;
 using std::string;
 using std::ofstream;
 istream& xiba(istream& is)
 {
   int data;
   while(is>>data)
   {
     cout<<data<<endl;
   }
   cout<<is.eof()<<endl;
   is.clear();                              
   return is;
 }                                 
int main(){
  ofstream os("input.txt",ofstream::app);
  int a=322;
  os<<'\t'<<a<<endl;
  return 0; 
}