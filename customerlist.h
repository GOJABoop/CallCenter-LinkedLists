#ifndef CUSTOMERLIST_H_INCLUDED
#define CUSTOMERLIST_H_INCLUDED

#include "customernode.h"
#include "customer.h"
#include "listexception.h"
#include <fstream>

class CustomerList{
private:
    CustomerNode* anchor;

    bool isValidPos(CustomerNode* p) const;
    void copyAll(const CustomerList& l);
public:
    CustomerList();
    CustomerList(const CustomerList& l);
    ~CustomerList();

    bool isEmpty() const;

    void insertData(CustomerNode* p,const Customer& c);
    void insertSortedData(const Customer& c);

    void deleteData(CustomerNode* p);

    CustomerNode* getFirstPos() const;
    CustomerNode* getLastPos() const;
    CustomerNode* getPrevPos(CustomerNode* p) const;
    CustomerNode* getNextPos(CustomerNode* p) const;

    CustomerNode* findData(const Customer& c) const;

    Customer retrieve(CustomerNode* p);

    std::string toString() const;

    void deleteAll();

    CustomerList& operator = (const CustomerList& l);

    void writeToDisk(std::string& fileName);
    void readFromDisk(std::string& fileName);
};


#endif // CUSTOMERLIST_H_INCLUDED
