#ifndef AGENTMENU_H_INCLUDED
#define AGENTMENU_H_INCLUDED

#include "time.h"
#include "name.h"
#include "agent.h"
#include "agentnode.h"
#include "agentlist.h"
#include "customermenu.h"

class AgentMenu {
    private:
        AgentList* agentListPtr;

        void enterToContinue();
        void clearScreen();
        void printWithFormat(char* text,char* filled);
        void mainMenu();
        void showAgents();
        void registerAgent();
        void searchAgent();
        void modifyAgent();
        void deleteAgent();
        void deleteAllAgents();

        void sortAgents();

        void writeToDisk();
        void readFromDisk();

    public:
        AgentMenu(AgentList* p);
    };
#endif // AGENTMENU_H_INCLUDED
