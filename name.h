#ifndef NAME_H_INCLUDED
#define NAME_H_INCLUDED

#include <iostream>
#include <string>

using namespace std;

class Name {
private:
    string first;
    string last;
public:
    Name();
    Name(const Name& n);
    Name(const string& f, const string& l);

    void setFirst(const string& first);
    void setLast(const string& last);

    string getFirst() const;
    string getLast()  const;
    string toString() const;

    bool operator ==(const Name& n) const;
    bool operator !=(const Name& n) const;
    bool operator > (const Name& n) const;
    bool operator >=(const Name& n) const;
    bool operator < (const Name& n) const;
    bool operator <=(const Name& n) const;

    Name& operator =(const Name& n);

    friend ostream& operator <<(ostream& out, const Name& n);
    friend istream& operator >>(istream& in, Name& n);
};

#endif // NAME_H_INCLUDED
