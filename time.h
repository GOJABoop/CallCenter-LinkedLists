#ifndef TIME_H_INCLUDED
#define TIME_H_INCLUDED

#include <iostream>
#include <string>
#include <ctime>
#include <chrono>

class Time{
private:
    int hour;
    int minute;

    bool isValid(const int& hour, const int& minute) const;
    int toInt() const;
public:
    Time();
    Time(const Time& t);
    Time(const int& hour, const int&minute);

    void setHour(const int& hour);
    void setMinute(const int& minute);

    int getHour() const;
    int getMinute() const;

    std::string toString() const;

    bool operator ==(const Time& t) const;
    bool operator !=(const Time& t) const;
    bool operator > (const Time& t) const;
    bool operator >=(const Time& t) const;
    bool operator < (const Time& t) const;
    bool operator <=(const Time& t) const;

    Time& operator = (const Time& t);

    friend std::ostream& operator << (std::ostream& out,const Time& t);
    friend std::istream& operator >> (std::istream& in, Time& t);
};


#endif // TIME_H_INCLUDED
