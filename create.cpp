#include "create.h"

CreateQuery::CreateQuery() {
    queryType = "CREATE";
    queryString = "CREATE TABLE <table_name> (<columns>)";
    loadScheme(); 
}

void CreateQuery::loadScheme() {
    ifstream schemeFile("scheme.txt");
    string line;

    while (getline(schemeFile, line)) {
        istringstream ss(line);
        string tableName;
        getline(ss, tableName, '#');  

        vector<pair<string, string>> columns;
        string columnName, columnType;
        
        while (getline(ss, columnName, '#') && getline(ss, columnType, '#')) {
            columns.push_back(make_pair(columnName, columnType));  
        }

        scheme[tableName] = columns; 
    }

    schemeFile.close();
}


void CreateQuery::saveScheme() {
    ofstream schemeFile("scheme.txt", ios::trunc);
    for (const auto& [tableName, columns] : scheme) {
        schemeFile << tableName;
        for (const auto& column : columns) {
            schemeFile << "#" << column.first << "#" << column.second;
        }
        schemeFile << endl;
    }
    schemeFile.close();
}

void CreateQuery::menu() {
    int opc;
    do {
        cout << "% MEGATRON3000\n"
        "  Welcome to MEGATRON 3000! \n& "
        + showQuery() + "\n";
        cout << "1. Agregar tabla \n";
        cout << "2. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opc;

        if (cin.fail()) {
            cin.clear(); 
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
            cout << "Opcion invalida, intente de nuevo.\n\n";
            continue; 
        }
        cout<<endl;

        if (opc == 1){
            string tableName;
            int numColumns;
            queryString = "CREATE TABLE ";
            
            cout << "Ingrese nombre de la tabla: ";
            cin >> tableName;
            queryString += tableName + " (";

            cout << "Ingrese el numero de columnas: ";
            cin >> numColumns;
            vector<pair<string, string>> columns(numColumns);
            
            for (int i = 0; i < numColumns; ++i) {
                cout << "Nombre de la columna " << (i + 1) << ": ";
                cin >> columns[i].first;
                cout << "Tipo de la columna " << (i + 1) << " (int/str): ";
                cin >> columns[i].second;

                queryString += columns[i].first + " " + columns[i].second;
                if (i < numColumns - 1) queryString += ", ";
            }
            queryString += ")";
            
            scheme[tableName] = columns;
            saveScheme();
    
            cout << "Tabla creada exitosamente.\n";

        }
        else if(opc==2) continue;
        else
            cout << "Opcion invalida, intente de nuevo.\n\n";
    } while (opc != 2);
}

string CreateQuery::showQuery() {
    return queryString;
}

void CreateQuery::evaluateQuery() {}