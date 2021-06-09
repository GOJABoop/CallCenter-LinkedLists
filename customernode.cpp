#include "customernode.h"

CustomerNode::CustomerNode(): next(nullptr) {}

CustomerNode::CustomerNode(const Customer& c): data(c),next(nullptr) {}

void CustomerNode::setData(const Customer& c) {
    data=c;
    }

void CustomerNode::setNext(CustomerNode* p) {
    next=p;
    }

Customer CustomerNode::getData() const {
    return data;
    }

CustomerNode* CustomerNode::getNext() const {
    return next;
    }
