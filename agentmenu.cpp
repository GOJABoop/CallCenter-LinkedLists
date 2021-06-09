#include <iostream>
#include <cstring>
#include <cstdlib>
#include <clocale>
#include "agentmenu.h"

#define CLEAR "cls || clear"

using namespace std;


AgentMenu::AgentMenu(AgentList* p)  : agentListPtr(p){
    mainMenu();
}

void AgentMenu::enterToContinue() {
    cout << "Presione <ENTER> para continuar . . .";
    cin.get();
    clearScreen();
    }

void AgentMenu::clearScreen() {
    system("cls || clear");
    }

void AgentMenu::printWithFormat(char* text, char* filled) {
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

void AgentMenu::mainMenu() {
    int option;
    while(true){
        clearScreen();
        setlocale(LC_ALL,"spanish");
        printWithFormat((char*)"Control Informático de Agentes y Clientes - CIAC",(char*)" ");
        cout << endl << endl;
        cout << "   Menú Pricipal" << endl;
        cout << "  1) Mostrar agentes" << endl;
        cout << "  2) Registrar agente" << endl;
        cout << "  3) Búsqueda de agente" << endl;
        cout << "  4) Modificar agente" << endl;
        cout << "  5) Eliminar agente" << endl;
        cout << "  6) Eliminar todos los agentes" << endl;
        cout << "  7) Ordenar agentes" << endl;
        cout << "  8) Guardar agentes" << endl;
        cout << "  9) Leer agentes" << endl;
        cout << "  10) Salir" << endl << endl;
        cout << "Escriba el número de acción que desea realizar: ";
        cin >> option;

        switch(option){
            case 1:
                showAgents();
                break;
            case 2:
                registerAgent();
                break;
            case 3:
                searchAgent();
                break;
            case 4:
                modifyAgent();
                break;
            case 5:
                deleteAgent();
                break;
            case 6:
                deleteAllAgents();
                break;
            case 7:
                sortAgents();
                break;
            case 8:
                writeToDisk();
                break;
            case 9:
                readFromDisk();
                break;
            case 10:
                return;
                break;
            default:
                cout << "Opción inválida" << endl;
                cin.get();
                enterToContinue();
                clearScreen();
        }
    }
}

void AgentMenu::showAgents() {
    char op;
    clearScreen();
    printWithFormat((char*)"Control Informático de Agentes y Clientes – CIAC",(char*)" ");
    printWithFormat((char*)"Mostrar Agentes",(char*)" ");
    cout << endl << endl;
    if(!agentListPtr->isEmpty()){
        do{
            cout << "Quiere mostrar los agentes con su lista de clientes cada uno? (S/N): ";
            cin >> op;
            cin.ignore();
            op= toupper(op);
        }while(op != 'S' and op != 'N');
        cout << endl;
        printWithFormat((char*)"Lista de Agentes",(char*)" ");
        cout << "#EMP    NOMBRE                        HORARIO     #EXT H.EXTRA ESPECIALIDAD"<< endl;
        cout << agentListPtr->toString(op == 'S') << endl << endl;
        }
    else {
        cout << "No hay agentes registrados" << endl;
        cin.get();
        }
    enterToContinue();
}

void AgentMenu::registerAgent() {
    Agent myAgent;
    Time myTime;
    string myStr,number;
    int extensionNumber;
    Name myName;
    AgentNode* position;
    char op;

    clearScreen();
    printWithFormat((char*)"Control Informático de Agentes y Clientes – CIAC",(char*)" ");
    printWithFormat((char*)"Registrar Agente",(char*)" ");
    cout << endl << endl;
    cout << "Numero de empleado: ";
    cin.ignore();
    getline(cin,number);
    myAgent.setEmployeeNum(number);

    position = agentListPtr->findData(myAgent);
    if(position != nullptr){
        cout << "Ya está registrado ese agente." << endl;
        cin.ignore();
        enterToContinue();
        return;
    }

    cout << "Nombre(s): ";
    getline(cin,myStr);
    myName.setFirst(myStr);
    cout << "Apellido(s): ";
    getline(cin,myStr);
    myName.setLast(myStr);
    myAgent.setName(myName);

    cout << "Hora de Entrada (HH:MM): ";
    getline(cin,myStr,':');
    myTime.setHour(atoi(myStr.c_str()));
    getline(cin,myStr);
    myTime.setMinute(atoi(myStr.c_str()));
    myAgent.setCheckInTime(myTime);

    cout << "Hora de Salida (HH:MM): ";
    getline(cin,myStr,':');
    myTime.setHour(atoi(myStr.c_str()));
    getline(cin,myStr);
    myTime.setMinute(atoi(myStr.c_str()));
    myAgent.setDepartureTime(myTime);

    cout << "Numero de extensión: ";
    cin >> extensionNumber;
    myAgent.setNumExtension(extensionNumber);

    cout << "Horas Extra (HH:MM): ";
    getline(cin,myStr,':');
    myTime.setHour(atoi(myStr.c_str()));
    getline(cin,myStr);
    myTime.setMinute(atoi(myStr.c_str()));
    myAgent.setExtraHours(myTime);

    cout << "Especialidad: ";
    getline(cin,myStr);
    myAgent.setEspeciality(myStr);

    do{
        cout << "Quiere insertar clientes para este agente?(S/N): ";
        cin >> op;
        cin.ignore();
        op = toupper(op);
    }while(op != 'S' and op != 'N');
    if(op == 'S'){
        new CustomerMenu(&myAgent.getCustomerList());
    }
    try{
        agentListPtr->insertData(agentListPtr->getLastPos(),myAgent);
    }catch(ListException ex){
     cout << "Error al insertar agente, " << ex.what() << endl;
     cin.get();
     enterToContinue();
     return;
    }
    cout << "Agente insertado con éxito" << endl;
    enterToContinue();
}

void AgentMenu::searchAgent() {
    Agent myAgent;
    string number;
    Name myName;
    AgentNode* pos;
    char option;
    clearScreen();
    do{
        printWithFormat((char*)"Control Informático de Agentes y Clientes – CIAC",(char*)" ");
        printWithFormat((char*)"Búsquedad de Agente",(char*)" ");
        cout << endl << endl;
        if(agentListPtr->isEmpty()){
            cout << "No hay agentes registrados" << endl;
            cin.get();
            enterToContinue();
            return;
        }
        cout << "Numero de empleado: ";
        cin.ignore();
        getline(cin,number);
        myAgent.setEmployeeNum(number);

        pos = agentListPtr->findData(myAgent);
        if(pos == nullptr){
            cout << "No existe registro con ese numero de empleado" << endl << endl;
            cin.ignore();
            enterToContinue();
            return;
        }
        else{
            cout << "#EMP    NOMBRE                        HORARIO     #EXT H.EXTRA ESPECIALIDAD"<< endl;
            cout << pos->getData().toString(true) << endl;
        }
        cout << endl << "Deseas buscar un nuevo agente (S/N)? ";
        cin >> option;
        option=toupper(option);
        option=='S'?clearScreen():enterToContinue();
    }while(option=='S');
}

void AgentMenu::modifyAgent() {
    Agent myAgent;
    Time myTime;
    string myStr,number;
    int extensionNumber;
    Name myName;
    AgentNode* pos;
    char op;

    clearScreen();
    printWithFormat((char*)"Control Informático de Agentes y Clientes – CIAC",(char*)" ");
    printWithFormat((char*)"Modificar Agente",(char*)" ");
    cout << endl << endl;
    if(agentListPtr->isEmpty()){
        cout << "No hay agentes registrados" << endl;
        cin.get();
        enterToContinue();
        return;
    }
    cout << "Número de empleado: ";
    cin.ignore();
    getline(cin,number);
    myAgent.setEmployeeNum(number);

    pos = agentListPtr->findData(myAgent);
    if(pos == nullptr){
        cout << "No existe ese registro" << endl << endl;
        enterToContinue();
        return;
    }
    myAgent = pos->getData();
    cout << endl << "Dame los nuevos datos." << endl;
    /*cout << "Numero de empleado: ";
    getline(cin,number);
    myAgent.setEmployeeNum(number);*/

    /*pos = agentListPtr->findData(myAgent);
    if(pos != nullptr){
        cout << "Ya existe registro con ese número de empleado." << endl;
        cin.ignore();
        enterToContinue();
        return;
    }*/
    cout << "Nombre(s): ";
    getline(cin,myStr);
    myName.setFirst(myStr);

    cout << "Apellido(s): ";
    getline(cin,myStr);
    myName.setLast(myStr);
    myAgent.setName(myName);

    cout << "Hora de Entrada (HH:MM): ";
    getline(cin,myStr,':');
    myTime.setHour(atoi(myStr.c_str()));
    getline(cin,myStr);
    myTime.setMinute(atoi(myStr.c_str()));
    myAgent.setCheckInTime(myTime);

    cout << "Hora de Salida (HH:MM): ";
    getline(cin,myStr,':');
    myTime.setHour(atoi(myStr.c_str()));
    getline(cin,myStr);
    myTime.setMinute(atoi(myStr.c_str()));
    myAgent.setDepartureTime(myTime);

    cout << "Numero de extension: ";
    cin >> extensionNumber;
    myAgent.setNumExtension(extensionNumber);

    cout << "Horas Extras (HH:MM): ";
    getline(cin,myStr,':');
    myTime.setHour(atoi(myStr.c_str()));
    getline(cin,myStr);
    myTime.setMinute(atoi(myStr.c_str()));
    myAgent.setExtraHours(myTime);

    cout << "Especialidad: ";
    getline(cin,myStr);
    myAgent.setEspeciality(myStr);

    do{
        cout << "Desea modificar clientes para este agente?(S/N): ";
        cin >> op;
        cin.ignore();
        op = toupper(op);
    }while(op != 'S' and op != 'N');
    if(op == 'S'){
        new CustomerMenu(&myAgent.getCustomerList());
    }
    pos->setData(myAgent);
    cout << "El agente se ha modificado con exito" << endl << endl;
    enterToContinue();
}

void AgentMenu::deleteAgent() {
    Agent myAgent;
    AgentNode* pos;
    Name myName;
    string number;
    char option;

    clearScreen();
    printWithFormat((char*)"Control Informático de Agentes y Clientes – CIAC",(char*)" ");
    printWithFormat((char*)"Eliminar Agente",(char*)" ");
    cout << endl << endl;
    if(agentListPtr->isEmpty()){
        cout << "No hay agentes registrados" << endl;
        cin.get();
        enterToContinue();
        return;
    }
    cout << "Numero de empleado: ";
    cin.ignore();
    getline(cin,number);
    myAgent.setEmployeeNum(number);

    pos = agentListPtr->findData(myAgent);
    if (pos == nullptr) {
        cout << "No existe ese registro" << endl << endl;
        enterToContinue();
        return;
    }
    cout << "#EMP    NOMBRE                        HORARIO     #EXT H.EXTRA ESPECIALIDAD"<< endl;
    cout << pos->getData().toString(true) << endl << endl;
    cout << "Esta seguro de eliminar este agente (S/N)? " << endl;
    cout << "Si confirma esta acción tambien se perderán los clientes de este agente: ";
    cin >> option;
    option=toupper(option);
    if(option == 'S'){
        cout << "Eliminando agente..." << endl << endl;
        agentListPtr->deleteData(pos);
        cout << "Agente eliminado..." << endl;
        cin.ignore();
        enterToContinue();
    }
    else{
        cout << endl <<"Agente conservado!" << endl;
        cin.ignore();
        enterToContinue();
    }
}

void AgentMenu::deleteAllAgents() {
    char option;
    clearScreen();
    printWithFormat((char*)"Control Informático de Agentes y Clientes – CIAC",(char*)" ");
    printWithFormat((char*)"Eliminar Todos los Agentes",(char*)" ");
    cout << endl << endl;
    if(agentListPtr->isEmpty()){
        cout << "No hay agentes registrados" << endl;
        cin.get();
        enterToContinue();
        return;
    }
    else{
        cout << "#EMP    NOMBRE                        HORARIO     #EXT H.EXTRA ESPECIALIDAD"<< endl;
        cout << agentListPtr->toString(false) << endl << endl;
        cout << "Esta seguro de eliminar todos los agentes? (S/N): ";
        cin >> option;
        option=toupper(option);
        if(option == 'S'){
            agentListPtr->deleteAll();
            cout << "Agentes eliminados" << endl << endl;
        }
        else{
            cout << "Agentes conservados" << endl << endl;
        }
    }
    cin.ignore();
    enterToContinue();
}

void AgentMenu::sortAgents() {
    char option;
    clearScreen();
    printWithFormat((char*)"Control Informático de Agentes y Clientes – CIAC",(char*)" ");
    printWithFormat((char*)"Ordenar agentes",(char*)" ");
    cout << endl << endl;
    if(agentListPtr->isEmpty()){
        cout << "No hay agentes registrados" << endl;
        cin.get();
        enterToContinue();
        return;
    }
    cout << "Por cual atributo desea ordenar los agentes? " << endl;
    cout << "\t[N]ombre - - - [E]specialidad:  ";
    do{
        cin >> option;
        cin.ignore();
        option=toupper(option);
    }while(option!= 'N' && option != 'E');
    if(option=='N'){
        agentListPtr->sortByName();
        cout << "Los agentes han sido ordenados por nombre." << endl;
    }
    else{
        agentListPtr->sortByEspeciality();
        cout << "Los agentes han sido ordenados por especialidad." << endl;
    }
    enterToContinue();
}

void AgentMenu::writeToDisk() {
    clearScreen();
    printWithFormat((char*)"Control Informático de Agentes y Clientes – CIAC",(char*)" ");
    printWithFormat((char*)"Guardar agentes",(char*)" ");
    cout << endl << endl;
    cout << "Escribiendo en disco registros de agentes . . .";
    try{
        agentListPtr->writeToDisk("Agents.txt");
    }catch(ListException ex){
        cout << "Se presento un problema al intentar escribir: " << ex.what() << endl;
        cin.ignore();
        enterToContinue();
        return;
    }
    cout << "Se han guardado los registros." << endl;
    cin.ignore();
    enterToContinue();
}

void AgentMenu::readFromDisk() {
    clearScreen();
    printWithFormat((char*)"Control Informático de Agentes y Clientes – CIAC",(char*)" ");
    printWithFormat((char*)"Leer agentes",(char*)" ");
    cout << endl << endl;
    cout << "Leyendo de disco registros de agentes . . ." << endl;
    try{
        agentListPtr->readFromDisk("Agents.txt");
    }catch(ListException ex){
        cout << "Se presento un problema al intentar leer: " << ex.what() << endl;
        enterToContinue();
        return;
    }
    cout << "Se han leído los registros." << endl;
    cin.ignore();
    enterToContinue();
}
