#pragma once
#include <initializer_list>
#include <stdexcept>
#include <string>
#include <vector>

using std::string;
using std::vector;

class StrBlobPtr;
class StrBlob
{
    friend class StrBlobPtr;
    typedef vector<string>::size_type size_type;
public:
    StrBlob():data(std::make_shared<vector<string>>()){ }
    StrBlob(std::initializer_list<string> il):data(std::make_shared<vector<string>>(il)){ }
    size_type size() const {return data->size();}
    bool empty() const {return data->empty();}
    void push_back(const string& t){data->push_back(t);}
    void pop_back()
    {
        check(0,"pop_back on empty StrBlob");
        data->pop_back();
    }
    string& front() const
    {
        check(0, "front on empty StrBlob");
        return data->front();
    }
    string& back() const
    {
        check(0, "back on empty StrBlob");
        return data->back();
    }
    string& get(size_type index) 
    {
        return (*data)[index];
    }
    std::shared_ptr<vector<string>> getPtr()
    {
        return data;
    }
    StrBlobPtr begin();
    StrBlobPtr end();
private:
    std::shared_ptr<vector<string>> data;
    void check(size_type i, const string &msg) const
    {
        if(i >= data->size())
            throw std::out_of_range(msg);
    }

};

class StrBlobPtr
{
private:
    std::weak_ptr<vector<string>> wptr;
    std::size_t curr;
    std::shared_ptr<vector<string>>
    check (std::size_t i, const string& msg) const
    {
        auto ret = wptr.lock();
        if(!ret)
            throw std::runtime_error("unbound StrBlobPtr");
        if(i>=ret->size())
            throw std::out_of_range(msg);
        return ret;
    }
public:
    StrBlobPtr(): curr(0){}
    StrBlobPtr(StrBlob& a, std::size_t sz = 0): 
    wptr(a.data), curr(sz){}
    string& deref() const
    {
        auto p = check(curr, "dereference past end");
        return (*p)[curr];
    }
    StrBlobPtr& incr()
    {
        check(curr,"increment past end of StrBlobPtr");
        ++curr;
        return *this;
    }
    std::size_t getCurr() const
    {
        return curr;
    }

};

StrBlobPtr StrBlob::begin()//注意前向声明问题，函数定义得在StrBlobPtr后面
{
    return StrBlobPtr(*this);
}
StrBlobPtr StrBlob::end()
{
    return StrBlobPtr(*this, data->size());
}