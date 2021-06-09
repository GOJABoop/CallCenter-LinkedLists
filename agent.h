#ifndef AGENT_H_INCLUDED
#define AGENT_H_INCLUDED

#include <iostream>
#include <string>
#include <cstdio>
#include <cstdlib>
#include "name.h"
#include "time.h"
#include "customerlist.h"

using namespace std;

class Agent{
private:
    Name name;
    Time checkInTime;
    Time departureTime;
    string employeeNumber;
    int extensionNumber;
    Time extraHours;
    string especialty;
    CustomerList customerList;
public:
    Agent();
    ~Agent();
    Agent(const Agent& a);

    void setName(const Name& n);
    void setCheckInTime(const Time& t);
    void setDepartureTime(const Time& t);
    void setEmployeeNum(const string& n);
    void setNumExtension(const int& n);
    void setExtraHours(const Time& t);
    void setEspeciality(const string& s);
    void setClientList(const CustomerList& l);

    Name getName() const;
    Time getCheckInTime();
    Time getDepartureTime();
    string getEmployeeNum();
    int getNumExtension();
    Time getExtraHours();
    string getEspeciality();
    CustomerList& getCustomerList();

    string toString(const bool& op = false) const;
    Agent& operator = (const Agent& a);

    bool operator ==(const Agent& a) const;
    bool operator !=(const Agent& a) const;
    bool operator > (const Agent& a) const;
    bool operator >=(const Agent& a) const;
    bool operator < (const Agent& a) const;
    bool operator <=(const Agent& a) const;

    friend ostream& operator << (ostream& out, const Agent& a);
    friend istream& operator >> (istream& in,Agent& a);
};


#endif // AGENT_H_INCLUDED
