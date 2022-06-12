#ifndef SALES_DATA
#define SALES_DATA
#include <string>
#include <iostream>
#include<math.h>
#include<vector>
using std::string;
using std::istream;
using std::ostream;
using std::endl;
using std::vector;



class Sales_data
{
	friend istream& read(istream& is,Sales_data&);
	friend ostream& print(ostream& os,const Sales_data&);
private:
	double revenue=0;
	unsigned units_sold=0;
	string bookNo="";//���ڳ�ʼֵ
	double avg_price();
public:
	Sales_data() :Sales_data("", 0, 0) {  }
	
	Sales_data(string s, unsigned u, double r) : bookNo(s), units_sold(u),
		revenue(r) {}
	explicit Sales_data(string s) :bookNo(s) {}
	 Sales_data& combine(const Sales_data& rhs) 
	{
		revenue += rhs.revenue;
		units_sold += rhs.units_sold;
		return *this;
	}
	string isbn() const
	{
		return bookNo;
	}
	
};
istream& read(istream& is,Sales_data&);
ostream& print(ostream& os,const Sales_data&);
 Sales_data add(const Sales_data a, const Sales_data b);
inline double Sales_data::avg_price()//7.26
{
	return units_sold ? revenue / units_sold : 0;
}

struct Person;
istream& read_person(istream& is, Person& Amanda);
ostream& print_person(ostream& os, const Person& Amanda);
struct Person
{
	friend istream& read_person(istream& is, Person& Amanda);
	friend ostream& print_person(ostream& os, const Person& Amanda);
private:

	string name{""};
	string address="";
	
public:
	Person(string n, string a) :name(n), address(a) {}
	Person() = default;

	string get_name() const//Ӧ��ʹ��const��Ϊ����û�иı��ڲ�����
	{
		return name;
	}
	string get_address() const//Ӧ��ʹ��const��Ϊ����û�иı��ڲ�����
	{
		return address;
	}
};
class Employee {
private:
	double height, weight;
	string company;
public:
	Employee(double w, double h, string c="Tencent"):height(h),weight(w),company(c){ }
	Employee() :Employee(75, 180) { std::cout << company << endl; }
};
class Debug {//7.53
private:
	int jj = 54;
	int error, num;
public:
	constexpr Debug(int e, int n) :error(e), num(n) {}
	Debug() = default;
};
class Account {
private:
	static double interestRate;
	double deposit;
	unsigned year;
	double nowMoney;
	static constexpr int vecSize = 20;
	static vector<double> vec;
public:
	Account():Account(300,0){}
	Account(double d,unsigned y):deposit(d),year(y),nowMoney(d*pow((1+interestRate),y)){}
	double getMoney()
	{
		return nowMoney;
	}
};

constexpr int Account::vecSize;
struct PersonInfo
{
	string name;
	vector<string> phones;
};

#endif