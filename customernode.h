#ifndef CUSTOMERNODE_H_INCLUDED
#define CUSTOMERNODE_H_INCLUDED

#include "customer.h"

class CustomerNode {
    private:
        Customer data;
        CustomerNode* next;
    public:
        CustomerNode();
        CustomerNode(const Customer& c);

        void setData(const Customer& c);
        void setNext(CustomerNode* p);

        Customer getData() const;
        CustomerNode* getNext() const;
    };

#endif // CUSTOMERNODE_H_INCLUDED
