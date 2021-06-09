#ifndef CUSTOMERMENU_H_INCLUDED
#define CUSTOMERMENU_H_INCLUDED

#include "customer.h"
#include "customernode.h"
#include "customerlist.h"

class CustomerMenu {
        CustomerList* customersListPtr;
        void enterToContinue();
        void clearScreen();
        void printWithFormat(char* text,char* filled);
    public:
        CustomerMenu(CustomerList* l);

        void clientMenu();
        void registerCustomer();
        void removeCustomer();
        void removeAll();
        void modifyCallDuration();
    };

#endif // CUSTOMERMENU_H_INCLUDED
