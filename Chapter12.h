#pragma once
#include <memory>
#include <vector>
#include <iostream>
#include <string>
#include "SearchWord.h"


std::shared_ptr<std::vector<int>> vecFactory();
std::shared_ptr<std::vector<int>> read_vec(std::shared_ptr<std::add_lvalue_reference_t<int>> v,std::istream& is);
std::string make_plural(size_t ctr, const std::string &word, const std::string &ending);
std::ostream& print(std::ostream&, QueryResult&);