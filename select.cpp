#include "select.h"

SelectQuery::SelectQuery(const map<string, vector<pair<string, string>>>& schemeData) {
    queryType = "SELECT";
    queryString = "SELECT <columnas> FROM <tablas>";
    scheme = schemeData; 
}

void SelectQuery::menu() {
    int opc;
    do {
        cout << "% MEGATRON3000\n"
        "  Welcome to MEGATRON 3000! \n& "
        + showQuery() + "\n";
        cout << "1. Editar columnas \n";
        cout << "2. Editar tablas\n";
        cout << "3. Agregar condicion \n";
        cout << "4. Guardar relacion\n";
        cout << "5. Evaluar query\n";
        cout << "6. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opc;

        if (cin.fail()) {
            cin.clear(); 
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
            cout << "Opcion invalida, intente de nuevo.\n\n";
            continue; 
        }
        cout<<endl;
        
        switch (opc) {
            case 1:
                editColumns();
                break;
            case 2:
                editTables();
                break;
            case 3:
                addCondition();
                break;
            case 4:
                save();
                break;
            case 5:
                evaluateQuery();
                break;
            case 6:
                break;
            default:
                cout << "Opcion invalida, intente de nuevo.\n\n";
        }
    } while (opc != 6);
}

string SelectQuery::showQuery() {
    queryString = "SELECT ";
    if(!columns.empty()){
        for(int i = 0; i < columns.size(); i++){
            if (i > 0) queryString += ", ";
            queryString += columns[i];
        }
    }else queryString += "<columnas>";
    
    queryString += " FROM ";

    if(!tables.empty()){
        for(int i = 0; i < tables.size(); i++){
            if (i > 0) queryString += ", ";
            queryString += tables[i];
        }
    }else queryString += "<tablas>";

    if(!condition.empty())
        queryString += " WHERE " + condition;
    
    if(!fileName.empty())
        queryString += " | " + fileName;
    return queryString;
}

bool SelectQuery::evaluateCondition(const vector<string>& row1, const vector<string>& row2) {
    if (condition.empty()) {
        return true;
    }

    string modifiedCondition = condition;

    vector<string> conditions;

    size_t andPos = modifiedCondition.find(" AND ");
    size_t orPos = modifiedCondition.find(" OR ");

    while (andPos != string::npos || orPos != string::npos) {
        if (andPos != string::npos) {
            string subCondition = modifiedCondition.substr(0, andPos);
            conditions.push_back(subCondition);
            conditions.push_back("AND");  
            modifiedCondition = modifiedCondition.substr(andPos + 5);  
        } else if (orPos != string::npos) {
            string subCondition = modifiedCondition.substr(0, orPos);
            conditions.push_back(subCondition);
            conditions.push_back("OR");  
            modifiedCondition = modifiedCondition.substr(orPos + 4);  
        }

        andPos = modifiedCondition.find(" AND ");
        orPos = modifiedCondition.find(" OR ");
    }

    if (!modifiedCondition.empty()) {
        conditions.push_back(modifiedCondition);
    }

    bool result = false;
    bool inAnd = false;
    bool inOr = false;

    for (size_t i = 0; i < conditions.size(); ++i) {
        if (conditions[i] == "AND") {
            inAnd = true;
            inOr = false;
            continue;
        } else if (conditions[i] == "OR") {
            inOr = true;
            inAnd = false;
            continue;
        }

        string column, op, value;
        string cond = conditions[i];

        cond.erase(remove_if(cond.begin(), cond.end(), ::isspace), cond.end());

        size_t opPos = cond.find_first_of("=<>");
        if (opPos == string::npos) {
            cout << "Error: Condición inválida '" << cond << "'.\n";
            return false;
        }

        column = cond.substr(0, opPos);
        if (cond[opPos] == '=' || cond[opPos] == '<' || cond[opPos] == '>') {
            op = cond[opPos];
            if (cond[opPos + 1] == '=') {
                op += '=';
            }
        }

        value = cond.substr(opPos + op.size());

        if (!value.empty() && value.front() == '\'' && value.back() == '\'') {
            value = value.substr(1, value.size() - 2);
        }

        bool currentCondition = false;
        int columnIndex = -1;
        vector<string> currentRow;

        size_t dotPos = column.find('.');
        if (dotPos != string::npos) {
            string table = column.substr(0, dotPos);
            column = column.substr(dotPos + 1);

            if (table == tables[0]) {
                currentRow = row1;
            } else if (tables.size() > 1 && table == tables[1]) {
                currentRow = row2;
            }
        } else {
            currentRow = row1;
        }

        for (size_t j = 0; j < scheme[tables[0]].size(); ++j) {
            if (scheme[tables[0]][j].first == column) {
                columnIndex = j;
                break;
            }
        }

        if (columnIndex == -1) {
            cout << "Error: La columna '" << column << "' no existe en las tablas seleccionadas.\n";
            return false;
        }

        string columnValue = currentRow[columnIndex];

        if (op == "=") {
            currentCondition = columnValue == value;
        } else if (op == "<") {
            currentCondition = columnValue < value;
        } else if (op == ">") {
            currentCondition = columnValue > value;
        } else if (op == "<=") {
            currentCondition = columnValue <= value;
        } else if (op == ">=") {
            currentCondition = columnValue >= value;
        }

        if (i == 0) {
            result = currentCondition;
        } else if (inAnd) {
            result = result && currentCondition;
        } else if (inOr) {
            result = result || currentCondition;
        }
    }

    return result;
}



void SelectQuery::evaluateQuery() {
    if (tables.empty()) {
        cout << "Error: No se han seleccionado tablas.\n";
        return;
    }
    if (columns.empty()) {
        cout << "Error: No se han seleccionado columnas.\n";
        return;
    }

    loadData(); 

    if (columns.size() == 1 && columns[0] == "*") {
        columns.clear(); 
        for (const string& table : tables) {
            for (const auto& col : scheme[table]) {
                columns.push_back(col.first);  
            }
        }
    }

    for (const string& column : columns) {
        bool found = false;
        for (const string& table : tables) {
            for (const auto& col : scheme[table]) {
                if (col.first == column || (table + "." + col.first) == column) {
                    found = true;
                    break;
                }
            }
            if (found) break;
        }
        if (!found) {
            cout << "Error: La columna '" << column << "' no existe en las tablas seleccionadas.\n";
            return;
        }
    }

    vector<vector<string>> result;

    if (tables.size() == 1) {
    const auto& tableData = data[tables[0]];
    for (const auto& row : tableData) {
        vector<string> selectedRow;
        for (const string& col : columns) {
            for (size_t j = 0; j < scheme[tables[0]].size(); ++j) {
                if (scheme[tables[0]][j].first == col) {
                    selectedRow.push_back(row[j]);
                    break;
                }
            }
        }
        result.push_back(selectedRow);
    }
    } 
    else if (tables.size() == 2) {
        const auto& table1Data = data[tables[0]];
        const auto& table2Data = data[tables[1]];

        for (const auto& row1 : table1Data) {
            for (const auto& row2 : table2Data) {
                vector<string> selectedRow;
                
                for (const string& col : columns) {
                    size_t dotPos = col.find('.');
                    string table = (dotPos != string::npos) ? col.substr(0, dotPos) : "";
                    string column = (dotPos != string::npos) ? col.substr(dotPos + 1) : col;
                    
                    if (table == tables[0] || table.empty()) { 
                        for (size_t j = 0; j < scheme[tables[0]].size(); ++j) {
                            if (scheme[tables[0]][j].first == column) {
                                selectedRow.push_back(row1[j]);
                                break;
                            }
                        }
                    } else if (table == tables[1]) {  
                        for (size_t j = 0; j < scheme[tables[1]].size(); ++j) {
                            if (scheme[tables[1]][j].first == column) {
                                selectedRow.push_back(row2[j]);
                                break;
                            }
                        }
                    }
                }
                result.push_back(selectedRow);
            }
        }
    } else {
        cout << "Error: Solo se soporta un máximo de 2 tablas para el JOIN.\n";
        return;
    }

    cout << "Resultado de la consulta:\n";
    for (const string& column : columns) {
        cout << column << " ";
    }
    cout << endl;

    if (!condition.empty()) {
        vector<vector<string>> filteredResult;
        for (const auto& row : result) {
            if (evaluateCondition(row, {})) {  
                filteredResult.push_back(row);
            }
        }
        result = filteredResult;
    }

    for (const auto& row : result) {
        for (const auto& value : row) {
            cout << value << " ";
        }
        cout << endl;
    }

    if (!fileName.empty()) {
        ofstream outFile(fileName + ".txt");

        for (const string& column : columns) {
            outFile << column << "#";
        }
        outFile << endl;

        for (const auto& row : result) {
            for (size_t i = 0; i < row.size(); ++i) {
                outFile << row[i];
                if (i < row.size() - 1) {
                    outFile << "#";
                }
            }
            outFile << endl;
        }
        outFile.close();
        cout << "Resultado guardado en " << fileName << ".txt\n";

    
        vector<pair<string, string>> newScheme;
        for (const string& column : columns) {
            string dataType; 

            for (const string& table : tables) {
                for (const auto& col : scheme[table]) {
                    if (col.first == column) {
                        dataType = col.second; 
                        break;
                    }
                }
            }

            newScheme.emplace_back(column, dataType);
        }


        string newTableName = fileName;
        scheme[newTableName] = newScheme;

        ofstream schemeFile("scheme.txt");
        for (const auto& entry : scheme) {
            schemeFile << entry.first << "#";
            for (const auto& col : entry.second) {
                schemeFile << col.first << ":" << col.second << "#";
            }
            schemeFile << endl;
        }
        schemeFile.close();
        cout << "Esquema actualizado guardado en scheme.txt\n";
    }
}



void SelectQuery::loadData() {
    for (const auto& table : tables) {
        if (scheme.find(table) == scheme.end()) {
            cout << "Error: La tabla '" << table << "' no existe en el esquema.\n";
            return;
        }
        
        ifstream tableFile(table + ".txt");
        if (!tableFile.is_open()) {
            cout << "Error: No se pudo abrir el archivo de la tabla '" << table << "'.\n";
            return;
        }
        
        vector<vector<string>> tableData;
        string line;
        while (getline(tableFile, line)) {
            vector<string> rowData;
            istringstream ss(line);
            string value;
            while (getline(ss, value, '#')) {
                rowData.push_back(value);
            }
            tableData.push_back(rowData);
        }
        data[table] = tableData;
        tableFile.close();
    }
}

void SelectQuery::editColumns() {
    cout << "Cantidad de columnas: ";
    int n;
    cin >> n;
    columns.resize(n);

    for (int i = 0; i < n; i++) {
        cout << "Columna " << (i + 1) << ": ";
        cin >> columns[i];        
    }
    cout << endl;
}

void SelectQuery::editTables() {
    cout << "Cantidad de tablas: ";
    int n;
    cin >> n;
    tables.resize(n);

    for (int i = 0; i < n; i++) {
        cout << "Tabla " << (i + 1) << ": ";
        cin >> tables[i];
    }
    cout << endl;
}

void SelectQuery::addCondition() {
    cout << "Condicion: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, condition);
    cout << endl;
}

void SelectQuery::save() {
    cout << "Ingrese nombre del archivo: ";
    cin >> fileName;
}