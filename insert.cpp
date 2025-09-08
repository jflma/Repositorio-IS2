#include "insert.h"

InsertQuery::InsertQuery(const map<string, vector<pair<string, string>>>& schemeData) {
    queryType = "INSERT";
    scheme = schemeData;
}

void InsertQuery::menu() {
    insertIntoTable();
}

string InsertQuery::showQuery() {
    return queryString;
}

void InsertQuery::evaluateQuery() {
    stringstream ss(queryString);
    string token;

    getline(ss, token, ' ');  
    getline(ss, token, ' ');  
    getline(ss, tableName, ' ');  

    if (scheme.find(tableName) == scheme.end()) {
        cout << "Error: La tabla '" << tableName << "' no existe.\n";
        return;
    }

    getline(ss, token, '(');
    getline(ss, token, ')');

    stringstream valuesStream(token);
    string value;
    vector<string> rowData;

    while (getline(valuesStream, value, ',')) {
        rowData.push_back(value);
    }

    if (rowData.size() != scheme[tableName].size()) {
        cout << "Error: La cantidad de valores no coincide con la cantidad de columnas. "
             << "Se esperaban " << scheme[tableName].size() << " valores, pero se recibieron " << rowData.size() << ".\n";
        return;
    }

    for (size_t i = 0; i < rowData.size(); ++i) {
        string columnType = scheme[tableName][i].second;
        if (columnType == "int" && !std::all_of(rowData[i].begin(), rowData[i].end(), ::isdigit)) {
            cout << "Error: El valor '" << rowData[i] << "' no es un entero válido para la columna '" << scheme[tableName][i].first << "'.\n";
            return;
        }
    }

    ofstream tableFile(tableName + ".txt", ios::app);
    for (const string& data : rowData) {
        tableFile << data << (data == rowData.back() ? "" : " ");  // Añadir espacio entre valores
    }
    tableFile << endl;
    tableFile.close();

    cout << "Datos insertados exitosamente en la tabla " << tableName << ".\n";
}


void InsertQuery::insertIntoTable() {
    string tableName;
    cout << "Ingrese el nombre de la tabla: ";
    cin >> tableName;
    
    if (scheme.find(tableName) == scheme.end()) {
        cout << "Tabla no existe.\n";
        return;
    }
    
    queryString = "INSERT INTO " + tableName + " VALUES (";
    vector<string> rowData;

    for (const auto& column : scheme[tableName]) {
        string value;
        cout << "Ingrese valor para " << column.first << " (" << column.second << "): ";
        cin >> value;
        rowData.push_back(value);
        queryString += value + ", ";
    }
    queryString.pop_back();
    queryString.pop_back();
    queryString += ")";
    
    ofstream tableFile(tableName + ".txt", ios::app);
    for (const string& data : rowData) {
        tableFile << data << " ";
    }
    tableFile << endl;
    tableFile.close();
    evaluateQuery();
    cout << "Datos insertados exitosamente en la tabla " << tableName << ".\n";
}