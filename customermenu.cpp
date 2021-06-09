#include "customermenu.h"
#include <iostream>
#include <cstring>
#include <cstdlib>
#include "time.h"
#include "name.h"

void CustomerMenu::enterToContinue() {
    cout << "Presione <ENTER> para continuar . . .";
    cin.get();
    clearScreen();
    }

void CustomerMenu::clearScreen() {
    system("cls || clear");
    }

void CustomerMenu::printWithFormat(char* text, char* filled) {
    int textLength=strlen(text);
    int spaces=(80-textLength)/2;
    int i;
    for(i=0;i<spaces;i++){
        cout << filled;
    }
    cout << text;
    i+=textLength;
    for(;i<80;i++){
        cout << filled;
    }
    }

CustomerMenu::CustomerMenu(CustomerList* l): customersListPtr(l) {
    clientMenu();
    }

void CustomerMenu::clientMenu() {
    int option;
    while(true) {
        clearScreen();
        printWithFormat((char*)"Control Informático de Agentes y Clientes – CIAC",(char*)" ");
        printWithFormat((char*)"Gestión de Clientes",(char*)" ");
        cout << endl << endl;
        cout << "    Control de Clientes" << endl;
        cout << "  1) Agregar Cliente" << endl;
        cout << "  2) Eliminar cliente" << endl;
        cout << "  3) Eliminar todos los clientes" << endl;
        cout << "  4) Modificar duración de llamada de cliente." << endl;
        cout << "  5) Regresar al menú principal" << endl;
        cout << "Escriba la opción que desea realizar: ";
        cin >> option;
        switch(option) {
            case 1:
                registerCustomer();
                break;
            case 2:
                removeCustomer();
                break;
            case 3:
                removeAll();
                break;
            case 4:
                modifyCallDuration();
                break;
            case 5:
                cin.ignore();
                return;
                break;
            default:
                cout << "Opción inválida" << endl;
                enterToContinue();
                break;
            }
        }
    }

void CustomerMenu::registerCustomer() {
    Time myTime;
    Name myName;
    Customer myCustomer;
    CustomerNode* position;
    string myStr;
    clearScreen();
    printWithFormat((char*)"Control Informático de Agentes y Clientes – CIAC",(char*)" ");
    printWithFormat((char*)"Gestión de Clientes->Registrar Cliente",(char*)" ");
    cout << endl << endl;
    cout << "Escriba los datos que se solicitan: " << endl;
    cout << "Nombre(s): ";
    cin.ignore();
    getline(cin,myStr);
    myName.setFirst(myStr);
    cout << "Apellido(s):";
    getline(cin,myStr);
    myName.setLast(myStr);
    myCustomer.setName(myName);

    cout << "Hora de llamada (HH:MM): ";
    getline(cin,myStr,':');
    myTime.setHour(atoi(myStr.c_str()));
    getline(cin,myStr);
    myTime.setMinute(atoi(myStr.c_str()));
    myCustomer.setCallTime(myTime);

    cout << "Duración llamada (HH:MM): ";
    getline(cin,myStr,':');
    myTime.setHour(atoi(myStr.c_str()));
    getline(cin,myStr);
    myTime.setMinute(atoi(myStr.c_str()));
    myCustomer.setCallDuration(myTime);

    position= customersListPtr->findData(myCustomer);
    if (position!=nullptr) {
        cout << "Ya esta en la lista";
        enterToContinue();
        return;
        }
    try {
        customersListPtr->insertSortedData(myCustomer);
        }
    catch (ListException ex) {
        cout << "Error al tratar de insertar cliente, " << ex.what() << endl << endl;
        enterToContinue();
        return;
        }
    cout << endl << "Cliente insertado con exito."  << endl;
    enterToContinue();
    }

void CustomerMenu::removeCustomer() {
    Customer myCustomer;
    CustomerNode* position;
    Time myTime;
    string myStr;

    clearScreen();
    printWithFormat((char*)"Control Informático de Agentes y Clientes – CIAC",(char*)" ");
    printWithFormat((char*)"Gestión de Clientes->Eliminar Cliente",(char*)" ");
    cout << endl << endl;
    if(!customersListPtr->isEmpty()) {
        cout << endl << "\tLista de Clientes" << endl << endl;
        cout << "\tHora de    Duración  " << endl;
        cout << "\tllamada    de llamada\tNombre"<< endl;
        cout << customersListPtr->toString() << endl;
        cout << "Para eliminar un cliente escriba la hora en la que llamó." << endl;
        cout << "Hora (HH::MM): ";
        getline(cin,myStr,':');
        myTime.setHour(atoi(myStr.c_str()));
        getline(cin,myStr);
        myTime.setMinute(atoi(myStr.c_str()));
        myCustomer.setCallTime(myTime);

        position=customersListPtr->findData(myCustomer);
        if (position==nullptr) {
            cout << "No esta registrado ese cliente" << endl << endl;
            enterToContinue();
            return;
            }
        else {
            cout << "Eliminando cliente..." << endl << endl;
            customersListPtr->deleteData(position);
            cout << "Cliente eliminado..." << endl << endl;
            enterToContinue();
            }
        }
    else {
        cout << "No hay clientes registrados" << endl;
        cin.get();
        enterToContinue();
        }
    }

void CustomerMenu::removeAll() {
    clearScreen();
    char option;
    clearScreen();
    printWithFormat((char*)"Control Informático de Agentes y Clientes – CIAC",(char*)" ");
    printWithFormat((char*)"Gestión de Clientes->Eliminar Todos los Clientes",(char*)" ");
    cout << endl << endl;
    if(!customersListPtr->isEmpty()) {
        cout << endl << "\tLista de Clientes" << endl << endl;
        cout << "Hora de    Duración  " << endl;
        cout << "llamada    de llamada\tNombre"<< endl;
        cout << customersListPtr->toString() << endl;
        cout << "Estás seguro que deseas eliminar todos los clientes (s/n)? ";
        cin >> option;
        option=toupper(option);
        if(option=='S') {
            customersListPtr->deleteAll();
            cout << "Clientes eliminados" << endl;
            cin.get();
            enterToContinue();
            }
        else {
            cout << "Clientes conservados" << endl;
            cin.get();
            enterToContinue();
            }
        }
    else {
        cout << "No hay clientes registrados" << endl;
        cin.get();
        enterToContinue();
        }
    }

void CustomerMenu::modifyCallDuration() {
    CustomerNode* position;
    Customer myCustomer;
    Time myTime;
    string myStr;;
    clearScreen();
    printWithFormat((char*)"Control Informático de Agentes y Clientes – CIAC",(char*)" ");
    printWithFormat((char*)"Gestión de Clientes->Modificar duración de Llamada",(char*)" ");
    cout << endl << endl;
    if(!customersListPtr->isEmpty()) {
        cout << endl << "\tLista de Clientes" << endl << endl;
        cout << "Hora de    Duración  " << endl;
        cout << "llamada    de llamada\tNombre"<< endl;
        cout << customersListPtr->toString() << endl;
        cout << "Hora de llamada: ";
        getline(cin,myStr,':');
        myTime.setHour(atoi(myStr.c_str()));
        getline(cin,myStr);
        myTime.setMinute(atoi(myStr.c_str()));
        myCustomer.setCallTime(myTime);
        position=customersListPtr->findData(myCustomer);
        if(position!=nullptr) {
            try {
                myCustomer=customersListPtr->retrieve(position);
                }
            catch(ListException ex) {
                cout << "Error al tratar de modificar cliente, " << ex.what() << endl << endl;
                enterToContinue();
                return;
                }
            cout << "Nueva duración de llamada: ";
            getline(cin,myStr,':');
            myTime.setHour(atoi(myStr.c_str()));
            getline(cin,myStr);
            myTime.setMinute(atoi(myStr.c_str()));
            myCustomer.setCallDuration(myTime);
            position->setData(myCustomer);
            cout << "Hora modificada correctamente" << endl;
            enterToContinue();
            }
        else {
            cout << "No hay cliente registrado con esa hora de llamada" << endl;
            enterToContinue();
            }
        }
    else {
        cout << "No hay clientes registrados" << endl;
        cin.get();
        enterToContinue();
        }
    }


