#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <memory>
#include <sstream>
#include <map>
#include <set>
#include <algorithm>
#include "shabi.h"

using std::vector;
using std::ifstream;
using std::cout;
using std::endl;
using std::shared_ptr;
using std::string;
using std::map;
using std::set;
using std::istringstream;
using std::make_shared;
using std::pair;
using std::weak_ptr;

class QueryResult;
class TextQuery{
public:
    using line_no = vector<string>::size_type;
    TextQuery(ifstream&);
    QueryResult query (const string&);
private:
    StrBlob file;
    map<string, shared_ptr<set<line_no>>> wm;
};
TextQuery::TextQuery(ifstream &is): file()
{
    string text;
    while(getline(is, text))
    {
        file.push_back(text);
        int n = file.size() - 1;
        istringstream line(text);
        string word;
        while(line>>word)
        {
            word.erase(remove_if(word.begin(),word.end(),ispunct),word.end());
            auto &lines = wm[word];
            if(!lines)
                lines.reset(new set<line_no>);
            lines->insert(n);
        }
    }
}

class QueryResult
{
    friend std::ostream& print(std::ostream&, QueryResult&); //friend declaration for print
public:
    QueryResult(string s,
                shared_ptr<set<TextQuery::line_no>> p,
                StrBlob f,
                unsigned c): sought(s), lines(p), file(f), count(c) {}
    set<TextQuery::line_no>::iterator begin()
    {
        return lines->begin();
    }
    set<TextQuery::line_no>::iterator end()
    {
        return lines->end();
    }
    shared_ptr<StrBlob> get_file()
    {
        return make_shared<StrBlob>();
    }
private:
    string sought;
    shared_ptr<set<TextQuery::line_no>> lines;
    StrBlob file;
    unsigned count;
};

QueryResult TextQuery::query(const string &sought)
{
    static shared_ptr<set<TextQuery::line_no>> nodata (make_shared<set<TextQuery::line_no>>());
    auto loc = wm.find(sought);
    string word;
    unsigned count = 0;
    if(loc == wm.end())
        return QueryResult(sought, nodata, file, 0);
    else
    {
        for(auto begin = file.begin(); begin.getCurr() != file.size(); begin.incr())
        {
            istringstream lines(begin.deref());
            while(lines>>word)
            {
                word.erase(remove_if(word.begin(),word.end(),ispunct),word.end());
                if(word == sought)
                    ++count;
            }
        }
        return QueryResult(sought, loc->second, file, count);
    }
}



