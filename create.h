#ifndef CREATE
#define CREATE

#include "query.h"

class CreateQuery : public Query {
private:
    map<string, vector<pair<string, string>>> scheme;

public:
    CreateQuery();
    void menu() override;
    string showQuery() override;
    void evaluateQuery() override;
    void loadScheme();
    void saveScheme();
    map<string, vector<pair<string, string>>> getScheme() const { return scheme; }
};
#endif 