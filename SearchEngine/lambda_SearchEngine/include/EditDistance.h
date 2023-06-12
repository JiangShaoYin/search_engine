#ifndef __EDITDISTANCE_H__
#define __EDITDISTANCE_H__

#include <string>

using std::string;

class EditDistance
{
public:
    EditDistance(){}
    ~EditDistance(){}

    size_t nBytesCode(const char ch);
    std::size_t length(const std::string &str);
    int triple_min(const int &a, const int &b, const int &c)
    { return a < b ? (a < c ? a : c) : (b < c ? b : c); }

    int editDistance(const std::string & lhs, const std::string &rhs);

};




#endif
