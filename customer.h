#ifndef CUSTOMER_H_INCLUDED
#define CUSTOMER_H_INCLUDED

#include <iostream>
#include <cstring>
#include "time.h"
#include "name.h"

using namespace std;

class Customer{
private:
    Name name;
    Time callTime;
    Time callDuration;
public:
    Customer();
    Customer(const Customer& c);

    void setName(const Name& n);
    void setCallTime(const Time& t);
    void setCallDuration(const Time& t);

    Name getName() const;
    Time getCallTime() const;
    Time getCallDuration() const;

    string toString() const;

    bool operator == (const Customer& c) const;
    bool operator != (const Customer& c) const;
    bool operator >  (const Customer& c) const;
    bool operator >= (const Customer& c) const;
    bool operator <  (const Customer& c) const;
    bool operator <= (const Customer& c) const;

    Customer& operator = (const Customer& c);

    friend ostream& operator << (ostream& out, const Customer& c);
    friend istream& operator >> (istream& in, Customer& c);
};

#endif // CUSTOMER_H_INCLUDED
