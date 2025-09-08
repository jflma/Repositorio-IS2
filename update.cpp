// #include "update.h"

// UpdateQuery::UpdateQuery(const map<string, vector<pair<string, string>>>& schemeData) {
//     queryType = "UPDATE <tabla> SET <columnas> WHERE <condicion>";
//     scheme = schemeData; 
// }

// void UpdateQuery::menu() {
//     updateTable();
// }

// string UpdateQuery::showQuery() {
//     return queryString;
// }

// void UpdateQuery::evaluateQuery() {
//     updateTable();
// }

// bool UpdateQuery::evaluateCondition(const string& row) {
//     if (condition.empty()) {
//         return true; 
//     }

//     istringstream iss(condition);
//     string column, op, value;
//     iss >> column >> op >> value;

//     if (value.front() == '\'' && value.back() == '\'') {
//         value = value.substr(1, value.size() - 2);
//     }

//     vector<string> result;
//     stringstream ss(row);
//     string item;

//     while (getline(ss, item, '#')) { 
//         result.push_back(item);
//     }
//     vector<string> rowData = result;
//     int columnIndex = -1;

//     for (size_t i = 0; i < scheme[tableName].size(); ++i) {
//         if (scheme[tableName][i].first == column) {
//             columnIndex = i;
//             break;
//         }
//     }

//     if (columnIndex == -1) {
//         cout << "Error: La columna '" << column << "' no existe en la tabla '" << tableName << "'.\n";
//         return false;
//     }

//     string columnValue = rowData[columnIndex];

//     if (op == "=") {
//         return columnValue == value;
//     } else if (op == "<") {
//         return columnValue < value;
//     } else if (op == ">") {
//         return columnValue > value;
//     } else if (op == "<=") {
//         return columnValue <= value;
//     } else if (op == ">=") {
//         return columnValue >= value;
//     } else {
//         cout << "Error: Operador desconocido '" << op << "'.\n";
//         return false;
//     }
// }

// void UpdateQuery::updateTable() {
//     cout << "Ingrese el nombre de la tabla: ";
//     cin >> tableName;

//     if (scheme.find(tableName) == scheme.end()) {
//         cout << "Tabla no existe.\n";
//         return;
//     }

//     setColumns();
//     addCondition();

//     ifstream tableFile(tableName + ".txt");
//     vector<string> rows;
//     string line;
//     while (getline(tableFile, line)) {
//         rows.push_back(line);
//     }
//     tableFile.close();

//     ofstream outFile(tableName + ".txt");
//     for (const string& row : rows) {
//         if (evaluateCondition(row)) { 
//             string updatedRow = row;
//             for (const string& clause : setClauses) {
//                 size_t pos = updatedRow.find(clause.substr(0, clause.find("=") - 1));
//                 if (pos != string::npos) {
//                     updatedRow.replace(pos, clause.size(), clause);
//                 }
//             }
//             outFile << updatedRow << endl;
//         } else {
//             outFile << row << endl;
//         }
//     }
//     outFile.close();

//     cout << "Tabla actualizada exitosamente.\n";
// }

// void UpdateQuery::addCondition() {
//     cout << "Ingrese la condicion para el UPDATE (ejemplo id = 1): ";
//     cin.ignore(numeric_limits<streamsize>::max(), '\n');
//     getline(cin, condition);
//     queryString = "UPDATE " + tableName + " SET <columnas> WHERE " + condition;
// }

// void UpdateQuery::setColumns() {
//     cout << "Cantidad de columnas a actualizar: ";
//     int n;
//     cin >> n;
//     setClauses.resize(n);

//     for (int i = 0; i < n; i++) {
//         cout << "Ingrese la columna y nuevo valor (ejemplo nombre = 'NuevoNombre'): ";
//         cin.ignore(numeric_limits<streamsize>::max(), '\n');
//         getline(cin, setClauses[i]);
//     }
//     queryString = "UPDATE " + tableName + " SET ";
//     for (int i = 0; i < setClauses.size(); i++) {
//         queryString += setClauses[i];
//         if (i < setClauses.size() - 1) queryString += ", ";
//     }
//     queryString += " WHERE <condicion>";
// }

#include "update.h"

UpdateQuery::UpdateQuery(const map<string, vector<pair<string, string>>>& schemeData) {
    queryType = "UPDATE";
    queryString = "UPDATE <tabla> SET <columnas> WHERE <condicion>";
    scheme = schemeData; 
}

void UpdateQuery::menu() {
    int opc;
    do {
        cout << "% MEGATRON3000\n"
             << "  Welcome to MEGATRON 3000! \n& "
             << showQuery() << "\n";
        cout << "1. Actualizar tabla \n";
        cout << "2. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opc;

        if (cin.fail()) {
            cin.clear(); 
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
            cout << "Opcion invalida, intente de nuevo.\n\n";
            continue; 
        }
        cout << endl;

        if (opc == 1) {
            updateTable();
        } else if (opc == 2) {
            continue;
        } else {
            cout << "Opcion invalida, intente de nuevo.\n\n";
        }
    } while (opc != 2);
}


string UpdateQuery::showQuery() {
    return queryString;
}

void UpdateQuery::evaluateQuery() {
    updateTable();
}

bool UpdateQuery::evaluateCondition(const string& row) {
    if (condition.empty()) {
        return true; 
    }

    istringstream iss(condition);
    string column, op, value;
    iss >> column >> op >> value;

    if (value.front() == '\'' && value.back() == '\'') {
        value = value.substr(1, value.size() - 2);
    }

    vector<string> result;
    stringstream ss(row);
    string item;

    while (getline(ss, item, '#')) { 
        result.push_back(item);
    }
    vector<string> rowData = result;
    int columnIndex = -1;

    for (size_t i = 0; i < scheme[tableName].size(); ++i) {
        if (scheme[tableName][i].first == column) {
            columnIndex = i;
            break;
        }
    }

    if (columnIndex == -1) {
        cout << "Error: La columna '" << column << "' no existe en la tabla '" << tableName << "'.\n";
        return false;
    }

    string columnValue = rowData[columnIndex];

    if (op == "=") {
        return columnValue == value;
    } else if (op == "<") {
        return columnValue < value;
    } else if (op == ">") {
        return columnValue > value;
    } else if (op == "<=") {
        return columnValue <= value;
    } else if (op == ">=") {
        return columnValue >= value;
    } else {
        cout << "Error: Operador desconocido '" << op << "'.\n";
        return false;
    }
}

void UpdateQuery::updateTable() {
    cout << "Ingrese el nombre de la tabla: ";
    cin >> tableName;

    if (scheme.find(tableName) == scheme.end()) {
        cout << "Tabla no existe.\n";
        return;
    }

    setColumns();
    addCondition();

    ifstream tableFile(tableName + ".txt");
    vector<string> rows;
    string line;
    bool modified = false; 

    while (getline(tableFile, line)) {
        rows.push_back(line);
    }
    tableFile.close();

    ofstream outFile(tableName + ".txt");
    for (const string& row : rows) {
        if (evaluateCondition(row)) { 
            string updatedRow = row;
            bool rowModified = false; 

            for (const string& clause : setClauses) {
                string columnToUpdate = clause.substr(0, clause.find("=") - 1);
                size_t pos = updatedRow.find(columnToUpdate);

                if (pos != string::npos) {
                    string newValue = clause.substr(clause.find("=") + 1);
                    newValue = newValue.substr(newValue.find_first_not_of(" "), newValue.find_last_not_of(" ") + 1);
                    newValue.erase(remove(newValue.begin(), newValue.end(), '\''), newValue.end()); 
                    if (updatedRow.substr(pos, newValue.size()) != newValue) {
                        updatedRow.replace(pos, newValue.size(), newValue);
                        rowModified = true; 
                    }
                }
            }

            if (rowModified) {
                modified = true; 
            }

            outFile << updatedRow << endl;
        } else {
            outFile << row << endl;
        }
    }
    outFile.close();

    if (modified) {
        cout << "Tabla actualizada exitosamente.\n";
    } else {
        cout << "No se realizaron modificaciones.\n";
    }
}

void UpdateQuery::addCondition() {
    cout << "Ingrese la condicion para el UPDATE (ejemplo id = 1): ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, condition);
    queryString = "UPDATE " + tableName + " SET <columnas> WHERE " + condition;
}

void UpdateQuery::setColumns() {
    cout << "Cantidad de columnas a actualizar: ";
    int n;
    cin >> n;
    setClauses.resize(n);

    for (int i = 0; i < n; i++) {
        cout << "Ingrese la columna y nuevo valor (ejemplo nombre = 'NuevoNombre'): ";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, setClauses[i]);
        
        setClauses[i].erase(remove_if(setClauses[i].begin(), setClauses[i].end(), ::isspace), setClauses[i].end());

        string columnToUpdate = setClauses[i].substr(0, setClauses[i].find("="));

        bool columnExists = false;
        for (const auto& col : scheme[tableName]) {
            if (col.first == columnToUpdate) {
                columnExists = true;
                break;
            }
        }

        if (!columnExists) {
            cout << "Error: La columna '" << columnToUpdate << "' no existe en la tabla '" << tableName << "'.\n";
            return;
        }
    }

    queryString = "UPDATE " + tableName + " SET ";
    for (int i = 0; i < setClauses.size(); i++) {
        queryString += setClauses[i];
        if (i < setClauses.size() - 1) queryString += ", ";
    }
    queryString += " WHERE <condicion>";
}
