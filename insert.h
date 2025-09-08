#ifndef INSERT
#define INSERT

#include "query.h"
class InsertQuery : public Query {
private:
    map<string, vector<pair<string, string>>> scheme;
    string tableName;

public:
    InsertQuery(const map<string, vector<pair<string, string>>>& schemeData);
    void menu() override;
    string showQuery() override;
    void evaluateQuery() override;
    void insertIntoTable();
};
#endif