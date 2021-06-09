#include "agentlist.h"

using namespace std;

bool AgentList::isValidPos(AgentNode* p) const {
    AgentNode* aux(header->getNext());

    while(aux != header) {
        if(aux == p) {
            return true;
            }
        aux = aux->getNext();
        }
    return false;
    }

void AgentList::copyAll(const AgentList& l) {
    AgentNode* aux(l.header->getNext());
    AgentNode* newNode;

    while(aux != l.header) {
        try {
            if((newNode = new AgentNode(aux->getData()))== nullptr) {
                throw ListException("Memoria no disponible");
                }
            }
        catch(NodeException ex) {
            string msg(string("Hubo problema: ") + ex.what());
            throw ListException(msg);
            }
        newNode->setPrev(header->getPrev());
        newNode->setNext(header);

        header->getPrev()->setPrev(newNode);
        header->setPrev(newNode);

        aux =  aux->getNext();
        }
    }

void AgentList::swapPtr(AgentNode* p, AgentNode* q) {
    if(p!=q) {
        Agent* aux(p->getDataPtr());
        p->setDataPtr(q->getDataPtr());
        q->setDataPtr(aux);
        }
    }

void AgentList::sortByName(AgentNode* leftEdge, AgentNode* rightEdge) {
    if(leftEdge==rightEdge) {
        return;
        }

    if(leftEdge->getNext()==rightEdge) {
        if(leftEdge->getData().getName() > rightEdge->getData().getName()) {
            swapPtr(leftEdge,rightEdge);
            }
        return;
        }
    AgentNode* i(leftEdge);
    AgentNode* j(rightEdge);

    while(i!=j) {
        while(i != j && i->getData().getName() <= rightEdge->getData().getName()) {
            i= i->getNext();
            }
        while(i != j && j->getData().getName() >= rightEdge->getData().getName()) {
            j= j->getPrev();
            }
        swapPtr(i,j);
        }
    swapPtr(i,rightEdge);

    if(i!=leftEdge) {
        sortByName(leftEdge,i->getPrev());
        }
    if(i!=rightEdge) {
        sortByName(i->getNext(),rightEdge);
        }
    }

void AgentList::sortByEspeciality(AgentNode* leftEdge, AgentNode* rightEdge) {
    if(leftEdge==rightEdge) {
        return;
        }

    if(leftEdge->getNext()==rightEdge) {
        if(leftEdge->getData().getEspeciality() > rightEdge->getData().getEspeciality()) {
            swapPtr(leftEdge,rightEdge);
            }
        return;
        }
    AgentNode* i(leftEdge);
    AgentNode* j(rightEdge);

    while(i!=j) {
        while(i != j && i->getData().getEspeciality() <= rightEdge->getData().getEspeciality()) {
            i= i->getNext();
            }
        while(i != j && j->getData().getEspeciality() >= rightEdge->getData().getEspeciality()) {
            j= j->getPrev();
            }
        swapPtr(i,j);
        }
    swapPtr(i,rightEdge);

    if(i!=leftEdge) {
        sortByEspeciality(leftEdge,i->getPrev());
        }
    if(i!=rightEdge) {
        sortByEspeciality(i->getNext(),rightEdge);
        }
    }

AgentList::AgentList() : header(new AgentNode) {
    if(header == nullptr) {
        throw ListException("Memoria no disponible, inicializando lista");
        }
    header->setPrev(header);
    header->setNext(header);
    }

AgentList::AgentList(const AgentList& l): AgentList() {
    copyAll(l);
    }

AgentList::~AgentList() {
    deleteAll();
    delete header;
    }

bool AgentList::isEmpty() const {
    return header->getNext() == header;
    }

void AgentList::insertData(AgentNode* p, const Agent& a) {
    if(p != nullptr and !isValidPos(p)) {
        throw ListException("Posicion invalida, insertData");
        }

    if(p == nullptr) {
        p = header;
        }
    AgentNode* aux;
    try {
        if((aux = new AgentNode(a)) == nullptr) {
            throw ListException("Memoria no disponible, insertData");
            }
        }
    catch(NodeException ex) {
        string msg("Error durante la insercion: ");
        msg += ex.what();

        throw ListException(msg);
        }

    aux->setPrev(p);
    aux->setNext(p->getNext());

    p->getNext()->setPrev(aux);
    p->setNext(aux);
    }

void AgentList::deleteData(AgentNode* p) {
    if(!isValidPos(p)) {
        throw ListException("Posicion invalida, deleteData");
        }

    p->getPrev()->setNext(p->getNext());
    p->getNext()->setPrev(p->getPrev());

    delete p;
    }

AgentNode* AgentList::getFirstPos()const {
    if(isEmpty()) {
        return nullptr;
        }

    return header->getNext();
    }

AgentNode* AgentList::getLastPos()const {
    if(isEmpty()) {
        return nullptr;
        }
    return header->getPrev();
    }

AgentNode* AgentList::getPrevPos(AgentNode* p) const {
    if((!isValidPos(p)) || (p->getPrev() == header)) {
        return nullptr;
        }

    return p->getPrev();
    }

AgentNode* AgentList::getNextPos(AgentNode* p) const {
    if(!isValidPos(p) or p->getNext() == header) {
        return nullptr;
        }

    return p->getNext();
    }

AgentNode* AgentList::findData(const Agent& a) {
    AgentNode* aux(header->getNext());

    while(aux != header) {
        if(aux->getData() == a) {
            return aux;
            }
        aux = aux->getNext();
        }
    return nullptr;
    }

Agent AgentList::retrieve(AgentNode* p) {
    if(!isValidPos(p)) {
        throw ListException("Posicion invalida, retrieve");
        }
    return p->getData();
    }

string AgentList::toString(const bool& op) const {
    string result;
    AgentNode* aux(header->getNext());

    while(aux != header) {
        result += aux->getData().toString(op) + "\n";
        aux = aux->getNext();
        }
    return result;
    }

void AgentList::sortByName() {
    sortByName(getFirstPos(),getLastPos());
    }

void AgentList::sortByEspeciality() {
    sortByEspeciality(getFirstPos(),getLastPos());
    }

void AgentList::deleteAll() {
    AgentNode* aux;

    while(header->getNext() != header) {
        aux = header->getNext();
        header->setNext(aux ->getNext());
        delete aux;
        }
    header->setPrev(header);
    }

AgentList& AgentList::operator=(const AgentList& l) {
    deleteAll();
    copyAll(l);

    return *this;
    }

void AgentList::writeToDisk(const std::string& fileName) {
    ofstream myFile;
    string agent;

    myFile.open(fileName,myFile.trunc);
    if(!myFile.is_open()) {
        string msg;
        msg= "Error al abrir el archivo: " + fileName + "para escritura";
        throw ListException(msg);
        }
    AgentNode* aux(header->getNext());
    system("del *.txt");

    while(aux!=header) {
        myFile << aux->getData() << endl;
        agent=aux->getData().getEmployeeNum();
        agent+=".txt";
        try {
            aux->getData().getCustomerList().writeToDisk(agent);
            }
        catch(ListException ex) {
            cout << ex.what() << endl;
            }
        aux= aux->getNext();
        }
    myFile.close();
    }

void AgentList::readFromDisk(const std::string& fileName) {
    ifstream myFile;
    string agent;

    myFile.open(fileName,ios::in);
    if(!myFile.is_open()) {
        string msg;
        msg= "Error al abrir el archivo: " + fileName + " para la lectura";
        throw ListException(msg);
        }

    Agent myAgent;
    AgentNode* aux;
    deleteAll();

    while(myFile >> myAgent) {
        agent=myAgent.getEmployeeNum();
        agent+=".txt";
        try {
            myAgent.getCustomerList().readFromDisk(agent);
            }
        catch(ListException ex) {
            cout << ex.what() << endl;
            }

        if((aux=new AgentNode(myAgent)) == nullptr) {
            myFile.close();
            throw ListException("Memoria no disponible, AgentList::readFromDisk");
            }

        aux->setPrev(header->getPrev());
        aux->setNext(header);

        header->getPrev()->setNext(aux);
        header->setPrev(aux);
        }
    myFile.close();
    }

