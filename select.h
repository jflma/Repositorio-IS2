#ifndef SELECT
#define SELECT

#include "query.h"

class SelectQuery : public Query {
private:
    vector<string> columns;
    vector<string> tables;
    string condition;
    string fileName;
    map<string, vector<pair<string, string>>> scheme;
    map<string, vector<vector<string>>> data;

public:
    SelectQuery(const map<string, vector<pair<string, string>>>& schemeData);
    void menu() override;
    string showQuery() override;
    void evaluateQuery() override;
    void loadData();
    bool evaluateCondition(const vector<string>&, const vector<string>&); 
    void editColumns();
    void editTables();
    void addCondition();
    void save();
};

#endif