#ifndef UPDATE
#define UPDATE
#include "query.h"
class UpdateQuery : public Query {
private:
    map<string, vector<pair<string, string>>> scheme;
    string tableName;
    string condition;
    vector<string> setClauses;

public:
    UpdateQuery(const map<string, vector<pair<string, string>>>& schemeData);
    void menu() override;
    string showQuery() override;
    void evaluateQuery() override;
    void updateTable();
    bool evaluateCondition(const string&);
    void addCondition();
    void setColumns();
};

#endif