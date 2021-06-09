#ifndef AGENTLIST_H_INCLUDED
#define AGENTLIST_H_INCLUDED

#include <iostream>
#include <cstring>
#include <cstdlib>
#include "agent.h"
#include "agentnode.h"

class AgentList{
private:
    AgentNode* header;

    bool isValidPos(AgentNode* p) const;
    void copyAll(const AgentList& l);

    void swapPtr(AgentNode* p,AgentNode* q);
    void sortByName(AgentNode* leftEdge,AgentNode* rightEdge);
    void sortByEspeciality(AgentNode* leftEdge,AgentNode* rightEdge);
public:
    AgentList();
    AgentList(const AgentList& l);
    ~AgentList();

    bool isEmpty() const;

    void insertData(AgentNode* p, const Agent& a);
    void deleteData(AgentNode* p);

    AgentNode* getFirstPos() const;
    AgentNode* getLastPos()const;
    AgentNode* getPrevPos(AgentNode* p) const;
    AgentNode* getNextPos(AgentNode* p)const;
    AgentNode* findData(const Agent& a);

    Agent retrieve(AgentNode* p);

    std::string toString(const bool& op = false) const;

    void sortByName();
    void sortByEspeciality();

    void deleteAll();

    AgentList& operator = (const AgentList& l);

    void writeToDisk(const std::string& fileName);
    void readFromDisk(const std::string& fileName);
};


#endif // AGENTLIST_H_INCLUDED
