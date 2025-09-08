#ifndef QUERY
#define QUERY

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <limits>
#include <map>
#include <algorithm>
using namespace std;

class Query {
protected:
    string queryType;
    string queryString;
public:
    virtual void menu() = 0;
    virtual string showQuery() = 0;
    virtual void evaluateQuery() = 0;
};
#endif 