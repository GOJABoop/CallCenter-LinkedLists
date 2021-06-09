#include "time.h"
#include <string>
#include <cstdio>
#include <cstdlib>

using namespace std;

bool Time::isValid(const int& h, const int& m) const {
    return h >= 0 and h < 24 and m >= 0 and m <60;
}

int Time::toInt() const{
    return hour * 100 + minute;
}


Time::Time() {
    chrono::system_clock::time_point today(chrono::system_clock::now());
    time_t tt(chrono::system_clock::to_time_t (today));
    struct tm* timeinfo;
    timeinfo = localtime(&tt);

    hour = timeinfo->tm_hour;
    minute = timeinfo->tm_min;
}

Time::Time(const Time& t) : hour(t.hour), minute(t.minute) {}

Time::Time(const int& h, const int& m) : Time(){
    if(isValid(h,m)){
        hour = h;
        minute = m;
    }

}

int Time::getHour() const {
    return hour;
}

int Time::getMinute() const {
    return minute;
}

string Time::toString() const {
    char result[6];
    sprintf(result, "%02d:%02d", hour, minute);
    return result;
}

void Time::setHour(const int& h) {
    if(isValid(h,minute)){
        hour = h;
    }
}

void Time::setMinute(const int& m) {
    if(isValid(hour,m)){
        minute = m;
    }
}

Time& Time::operator = (const Time& t) {
    hour = t.hour;
    minute = t.minute;

    return *this;
}

bool Time::operator==(const Time& t) const {
    return  toInt() == t.toInt();
}

bool Time::operator!=(const Time& t) const {
    return toInt() != t.toInt() ;
}

bool Time::operator>(const Time& t) const {
    return toInt() > t.toInt();
}

bool Time::operator>=(const Time& t) const {
    return toInt() >= t.toInt();
}

bool Time::operator<(const Time& t) const {
    return toInt() < t.toInt();
}

bool Time::operator<=(const Time& t) const {
    return toInt() <= t.toInt();
}

ostream& operator << (ostream& out,const Time& t){
    out << t.toString();
    return out;
}

istream& operator >> (istream& in, Time& t){
    string aux;

    getline(in,aux,':');
    t.hour= atoi(aux.c_str());
    getline(in,aux);
    t.minute= atoi(aux.c_str());

    return in;
}
