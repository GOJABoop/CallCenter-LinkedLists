#include "agent.h"

Agent::Agent() { }

Agent::~Agent() { }

Agent::Agent(const Agent& a): name(a.name),checkInTime(a.checkInTime),departureTime(a.departureTime),
    employeeNumber(a.employeeNumber),extensionNumber(a.extensionNumber),extraHours(a.extraHours),
    especialty(a.especialty),customerList(a.customerList) { }

void Agent::setName(const Name& n) {
    name=n;
    }

void Agent::setCheckInTime(const Time& t) {
    checkInTime=t;
    }

void Agent::setDepartureTime(const Time& t) {
    departureTime=t;
    }

void Agent::setEmployeeNum(const string& n) {
    employeeNumber=n;
    }

void Agent::setNumExtension(const int& n) {
    extensionNumber=n;
    }

void Agent::setExtraHours(const Time& t) {
    extraHours=t;
    }

void Agent::setEspeciality(const string& s) {
    especialty=s;
    }

//void Agent::setClientList(const CustomerList& l) { }

Name Agent::getName() const {
    return name;
    }

Time Agent::getCheckInTime() {
    return checkInTime;
    }

Time Agent::getDepartureTime() {
    return departureTime;
    }

string Agent::getEmployeeNum(){
    return employeeNumber;
    }

int Agent::getNumExtension() {
    return extensionNumber;
    }

Time Agent::getExtraHours() {
    return extraHours;
    }

string Agent::getEspeciality() {
    return especialty;
    }

CustomerList& Agent::getCustomerList() {
    return customerList;
    }

string Agent::toString(const bool& op) const {
    string result;
    char extensionNum[5];
    int i;

    sprintf(extensionNum,"%04d",extensionNumber);

    result= employeeNumber;
    for(i=employeeNumber.length();i<5;i++){
        result+=" ";
    }
    result+= name.toString();
    for(i=name.toString().length();i<32;i++){
        result+=" ";
    }
    result+= checkInTime.toString();
    result+= "-";
    result+= departureTime.toString();
    result+= "  ";
    result+= extensionNum;
    result+= "  ";
    result+= extraHours.toString();
    result+= "  ";
    result+= especialty;

    if(op) {
        result += "\n";
        result += customerList.toString();
        }
    return result;
    }

Agent& Agent::operator=(const Agent& a) {
    name= a.name;
    checkInTime= a.checkInTime;
    departureTime=a.departureTime;
    employeeNumber= a.employeeNumber;
    extensionNumber= a.extensionNumber;
    extraHours= a.extraHours;
    especialty= a.especialty;
    customerList= a.customerList;

    return *this;
    }

bool Agent::operator==(const Agent& a) const {
    return  employeeNumber==a.employeeNumber;
    }

bool Agent::operator!=(const Agent& a) const {
    return  employeeNumber!=a.employeeNumber;
    }

bool Agent::operator>(const Agent& a) const {
    return  employeeNumber>a.employeeNumber;
    }

bool Agent::operator>=(const Agent& a) const {
    return  employeeNumber>=a.employeeNumber;
    }

bool Agent::operator<(const Agent& a) const {
    return  employeeNumber<a.employeeNumber;
    }

bool Agent::operator<=(const Agent& a) const {
    return  employeeNumber<=a.employeeNumber;
    }

ostream& operator << (ostream& out, const Agent& a){
    char extensionNum[5];
    sprintf(extensionNum,"%04d",a.extensionNumber);

    out << a.name << endl;
    out << a.checkInTime << endl;
    out << a.departureTime << endl;
    out << extensionNum << endl;
    out << a.extraHours << endl;
    out << a.especialty << endl;
    out << a.employeeNumber;

    return out;
}

istream& operator >> (istream& in, Agent& a){
    string aux;

    in >> a.name;
    in >> a.checkInTime;
    in >> a.departureTime;
    getline(in,aux);
    a.extensionNumber= atoi(aux.c_str());
    in >> a.extraHours;
    getline(in,a.especialty);
    getline(in,a.employeeNumber);
    return in;
}
