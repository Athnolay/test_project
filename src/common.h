#ifndef __COMMON_H_
#define __COMMON_H_

#include <string>
#include <vector>

using namespace std;

void StringTrim(string &str, char token);

void StringSplit(string str, char split, vector<std::string> &ret);

#endif