#include "agentnode.h"

AgentNode::AgentNode() : dataPtr(nullptr), prev(nullptr), next(nullptr) {}

AgentNode::AgentNode(const Agent& a) : dataPtr(new Agent(a)), prev(nullptr), next(nullptr){
    if(dataPtr == nullptr){
        throw NodeException("Memoria no disponible, AgentNode(const Agent& a)");
    }
}

AgentNode::~AgentNode() {
    delete dataPtr;
}

void AgentNode::setData(const Agent& a) {
    if(dataPtr == nullptr){
        if((dataPtr = new Agent(a)) == nullptr){
            throw NodeException("Memoria no disponible, AgentNode::setData");
        }
    }
    else{
        *dataPtr = a;
    }
}

void AgentNode::setDataPtr(Agent* p) {
    dataPtr = p;
}

void AgentNode::setPrev(AgentNode* p) {
    prev = p;
}

void AgentNode::setNext(AgentNode* p) {
    next = p;
}

Agent AgentNode::getData() const {
    if(dataPtr == nullptr){
        throw NodeException("Dato inexistente, AgentNode::getData()");
    }
    return *dataPtr;
}

Agent* AgentNode::getDataPtr() const {
    return dataPtr;
}

AgentNode* AgentNode::getPrev() const {
    return prev;
}

AgentNode* AgentNode::getNext() const {
    return next;
}
