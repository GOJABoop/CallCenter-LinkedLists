#include "agentmenu.h"
#include <clocale>

using namespace std;

void pantallaDeInicio();
void printWithFormat(string text,string filled);

int main()
{
    pantallaDeInicio();
    new AgentMenu(new AgentList);
    return 0;
}

void pantallaDeInicio(){
    setlocale(LC_ALL,"spanish");
    printWithFormat("Control Informático de Agentes y Clientes"," ");
    printWithFormat("CIAC"," ");
    printWithFormat("Brixton Call Center"," ");
    for(int i=0;i<15;i++){
        cout << endl;
    }
    printWithFormat("Presiona <ENTER> para iniciar."," ");
    printWithFormat("Desarrolado por José Alberto García Ochoa"," ");
    cin.get();
    }

void printWithFormat(string text, string filled) {
    int textLength=text.length();
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
