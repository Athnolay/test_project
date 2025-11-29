#include "common.h"

void StringTrim(string &str, char token)
{
    size_t first_pos, last_pos;
    first_pos = str.find_first_not_of(token);
    last_pos = str.find_last_not_of(token);
    str = str.substr(first_pos, last_pos - first_pos);
}

void StringSplit(string str, char split, vector<string> &ret)
{
    if (str.empty())
        return;
    str += split;
    size_t pos;
    while ((pos = str.find(split)) != string::npos)
    {
        string split_str = str.substr(0, pos);
        ret.push_back(split_str);
        str = str.substr(pos + 1);
    }
    return;
}