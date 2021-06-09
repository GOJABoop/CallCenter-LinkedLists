#include "customer.h"

Customer::Customer() { }

Customer::Customer(const Customer& c): name(c.name),callTime(c.callTime),
    callDuration(c.callDuration) { }

void Customer::setName(const Name& n) {
    name=n;
    }

void Customer::setCallTime(const Time& t) {
    callTime=t;
    }

void Customer::setCallDuration(const Time& t) {
    callDuration=t;
    }

Name Customer::getName() const {
    return name;
    }

Time Customer::getCallTime() const {
    return callTime;
    }

Time Customer::getCallDuration() const {
    return callDuration;
    }

string Customer::toString() const {
    string str;
    str = callTime.toString();
    str+= "\t   ";
    str+= callDuration.toString();
    str+= "\t";
    str+= name.toString();

    return str;
    }

bool Customer::operator==(const Customer& c) const {
    return callTime == c.callTime;
    }

bool Customer::operator!=(const Customer& c) const {
    return callTime != c.callTime;
    }

bool Customer::operator>(const Customer& c) const {
    return callTime > c.callTime;
    }

bool Customer::operator>=(const Customer& c) const {
    return callTime >= c.callTime;
    }

bool Customer::operator<(const Customer& c) const {
    return callTime < c.callTime;
    }

bool Customer::operator<=(const Customer& c) const {
    return callTime <= c.callTime;
    }

Customer& Customer::operator=(const Customer& c) {
    name = c.name;
    callTime = c.callTime;
    callDuration = c.callDuration;

    return *this;
    }

ostream& operator << (ostream& out, const Customer& c){
    out << c.callTime << endl;
    out << c.callDuration << endl;
    out << c.name;

    return out;
}

istream& operator >> (istream& in, Customer& c){
    in >> c.callTime;
    in >> c.callDuration;
    in >> c.name;
    return in;
}
