#include "customerlist.h"

bool CustomerList::isValidPos(CustomerNode* p) const {
    CustomerNode* aux(anchor);

    while(aux != nullptr) {
        if(aux == p) {
            return true;
            }
        aux = aux->getNext();
        }
    return false;
    }

void CustomerList::copyAll(const CustomerList& l) {
    CustomerNode* prev(nullptr);
    CustomerNode* aux(l.anchor);
    CustomerNode* newCustomerNode;

    while(aux != nullptr) {
        if((newCustomerNode = new CustomerNode(aux->getData()))== nullptr) {
            throw ListException("Memoria no disponible, copyAll");
            }
        if(prev == nullptr) {
            anchor = newCustomerNode;
            }
        else {
            prev->setNext(newCustomerNode);
            }
        prev = newCustomerNode;
        aux = aux->getNext();
        }
    }

CustomerList::CustomerList(): anchor(nullptr) { }

CustomerList::CustomerList(const CustomerList& l): anchor(nullptr) {
    copyAll(l);
    }

CustomerList::~CustomerList() {
    deleteAll();
    }

bool CustomerList::isEmpty() const {
    return anchor == nullptr;
    }

void CustomerList::insertData(CustomerNode* p, const Customer& c) {
    if (p != nullptr and !isValidPos(p)) {
        throw ListException("Posicion invalida tratando de insertar");
        }
    CustomerNode* aux(new CustomerNode(c));
    if(aux == nullptr) {
        throw ListException("Memoria no disponible, CustomerList::insertData()");
        }
    if(p == nullptr) {
        aux->setNext(anchor);
        anchor = aux;
        }
    else {
        aux->setNext(p->getNext());
        p->setNext(aux);
        }
    }

void CustomerList::insertSortedData(const Customer& c) {
    CustomerNode* aux(anchor);
    CustomerNode* prev(nullptr);

    while(aux != nullptr and c > aux->getData()) {
        prev = aux;
        aux = aux->getNext();
        }
    insertData(prev,c);
    }

void CustomerList::deleteData(CustomerNode* p) {
    if(!isValidPos(p)) {
        throw ListException("Posicion invalida, CustomerList::deleteData() ");
        }
    if(p == anchor) {
        anchor = p->getNext();
        }
    else {
        getPrevPos(p)->setNext(p->getNext());
        }
    delete p;
    }

CustomerNode* CustomerList::getFirstPos() const {
    return anchor;
    }

CustomerNode* CustomerList::getLastPos() const {
    if(isEmpty()) {
        return nullptr;
        }
    CustomerNode* aux(anchor);
    while(aux->getNext() != nullptr) {
        aux = aux->getNext();
        }
    return aux;
    }

CustomerNode* CustomerList::getPrevPos(CustomerNode* p) const {
    if(p == anchor) {
        return anchor;
        }
    CustomerNode* aux(anchor);
    while(aux != nullptr and aux->getNext() != p) {
        aux = aux ->getNext();
        }
    return aux;
    }

CustomerNode* CustomerList::getNextPos(CustomerNode* p) const {
    if(!isValidPos(p)) {
        return nullptr;
        }
    return p->getNext();
    }

CustomerNode* CustomerList::findData(const Customer& c) const {
    CustomerNode* aux(anchor);
    while(aux != nullptr) {
        if(aux->getData() == c) {
            return aux;
            }
        aux = aux->getNext();
        }
    return nullptr;
    }

Customer CustomerList::retrieve(CustomerNode* p) {
    if(!isValidPos(p)) {
        throw ListException("Posicion invalida, CustomerList::retrieve()");
        }
    return p->getData();
    }

std::string CustomerList::toString() const {
    CustomerNode* aux(anchor);
    std::string result;

    while(aux != nullptr) {
        result+= "\t" +aux->getData().toString() + "\n";
        aux = aux->getNext();
        }
    return result;
    }

void CustomerList::deleteAll() {
    CustomerNode* aux;
    while(anchor != nullptr) {
        aux = anchor;
        anchor = aux->getNext();
        delete aux;
        }
    }

CustomerList& CustomerList::operator=(const CustomerList& l) {
    deleteAll();
    copyAll(l);

    return *this;
    }

void CustomerList::writeToDisk(std::string& fileName) {
    ofstream myFile;

    myFile.open(fileName,myFile.trunc);
    if(!myFile.is_open()) {
        string msg;
        msg= "Error al abrir el archivo: " + fileName + "para escritura";
        throw ListException(msg);
        }

    CustomerNode* aux(anchor);
    while(aux!=nullptr) {
        myFile << aux->getData() << endl;
        aux= aux->getNext();
        }
    myFile.close();
    }

void CustomerList::readFromDisk(std::string& fileName) {
    ifstream myFile;

    myFile.open(fileName,ios::in);
    if(!myFile.is_open()) {
        string msg;
        msg= "Error al abrir el archivo: " + fileName + " para la lectura CustomerList::readFromDisk";
        throw ListException(msg);
        }

    deleteAll();
    Customer myCustomer;
    CustomerNode* last(nullptr);
    CustomerNode* newNode;

    while(myFile >> myCustomer) {
        if((newNode= new CustomerNode(myCustomer)) == nullptr) {
            myFile.close();
            throw ListException("Memoria no disponible, CustomerList::readFromDisk");
            }

        if(last==nullptr) {
            anchor= newNode;
            }
        else {
            last->setNext(newNode);
            }
        last=newNode;
        }
    myFile.close();
    }
