# include "create.cpp"
# include "select.cpp"
# include "insert.cpp"
# include "update.cpp"

void mainMenu() {
    CreateQuery createQuery;
    map<string, vector<pair<string, string>>> scheme = createQuery.getScheme();

    int option;
    do {
        cout << "% MEGATRON3000\n"
        "  Welcome to MEGATRON 3000!\n";        
        cout << "1. CREATE\n";
        cout << "2. SELECT\n";
        cout << "3. INSERT\n";
        cout << "4. UPDATE\n";
        cout << "5. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> option;

        if (cin.fail()) {
            cin.clear(); 
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
            cout << "Opcion invalida, intente de nuevo.\n";
            continue; 
        }
        cout<<endl;

        switch (option) {
            case 1: {
                createQuery.menu();
                scheme = createQuery.getScheme();
                break;
            }
            case 2: {
                SelectQuery selectQuery(scheme);
                selectQuery.menu();
                break;
            }
            case 3: {
                InsertQuery insertQuery(scheme);
                insertQuery.menu();
                break;
            }
            case 4: {
                UpdateQuery updateQuery(scheme);
                updateQuery.menu();
                break;
            }
            case 5:
                cout << "& quit\n%\n";
                break;
            default:
                cout << "Opción inválida, intente de nuevo.\n";
        }
    } while (option != 5);
}

int main() {
    mainMenu();
    return 0;
}
