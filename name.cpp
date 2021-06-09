#include "name.h"

Name::Name() {
    first="Sin definir";
    last="Sin definir";
}

Name::Name(const Name& n): first(n.first),last(n.last) { }

Name::Name(const string& f, const string& l): first(f),last(l) { }

void Name::setFirst(const string& first) {
    this->first=first;
    }

void Name::setLast(const string& last) {
    this->last=last;
    }

string Name::getFirst() const {
    return first;
    }

string Name::getLast() const {
    return last;
    }

string Name::toString() const {
    string result;
    result= first + " " + last;
    return result;
    }

bool Name::operator==(const Name& n) const {
    return toString() == n.toString();
    }

bool Name::operator!=(const Name& n) const {
    return toString() != n.toString();
    }

bool Name::operator>(const Name& n) const {
    return toString()>n.toString();
    }

bool Name::operator>=(const Name& n) const {
    return toString() >= n.toString();
    }

bool Name::operator<(const Name& n) const {
    return toString()<n.toString();
    }

bool Name::operator<=(const Name& n) const {
    return toString() <= n.toString();
    }

Name& Name::operator=(const Name& n) {
    first = n.first;
    last = n.last;

    return *this;
    }

ostream& operator <<(ostream& out, const Name& n){
    out << n.first << ", " << n.last;
    return out;
}

istream& operator >>(istream& in, Name& n){
    getline(in,n.first,',');
    getline(in,n.last,' ');
    getline(in,n.last);

    return in;
}
