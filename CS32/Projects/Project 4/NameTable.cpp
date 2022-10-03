// NameTable.cpp

//MY OWN

#include "NameTable.h"
#include <string>
#include <vector>
#include <functional>
#include <list>
#include <stack>
#include <iterator>
using namespace std;

//Bucket size is a global const
const int NUMBER_OF_BUCKETS = 20000;

//Bucket v3
struct Buckets {
    string m_id;
    int m_lineNum;
    int m_currentScope;
    Buckets(string id, int num, int currentScope): m_id(id),m_lineNum(num), m_currentScope(currentScope) {}
};


unsigned int hashy(const std::string &hashMe)
{
   std::hash<std::string> str_hash;                      // creates a string hasher!
   unsigned int hashValue = str_hash(hashMe);   // now hash our string!
   // then just add your own modulo
   unsigned int bucketNum = hashValue % NUMBER_OF_BUCKETS;
   return bucketNum;
}
//Version3
class NameTableImpl
{
  public:
    NameTableImpl() {
        currentScope = 0;
        for (int i =0; i<NUMBER_OF_BUCKETS; i++) {
            m_buckets[i] = list<Buckets>();
        }
    }
    void enterScope();
    bool exitScope();
    bool declare(const string& id, int lineNum);
    int find(const string& id) const;
  private:
    list<Buckets> m_buckets[NUMBER_OF_BUCKETS];
    stack <string> m_scopeTracker;
    int currentScope;
};


void NameTableImpl::enterScope()
{
    m_scopeTracker.push("");
    currentScope++;
}

bool NameTableImpl::exitScope()
{

    //deleting from hashtable
        while (!m_scopeTracker.empty() && m_scopeTracker.top() != "")
        {
            string toDelete= m_scopeTracker.top();
            m_scopeTracker.pop();
            int bucket = hashy(toDelete);
            m_buckets[bucket].pop_front();
        }

    if (m_scopeTracker.empty()) {
        return false;
    }

    m_scopeTracker.pop();
    currentScope--;
        return true;
}

bool NameTableImpl::declare(const string& id, int lineNum)
{
    //Checks empty id
    if (id.empty()) {
        return false;
    }
    int bucket = hashy(id);
    
    //Checks id exists already in scope
    list<Buckets> :: iterator it;
    for (it = m_buckets[bucket].begin(); it != m_buckets[bucket].end(); it++) {
        if (id == it->m_id && currentScope == it->m_currentScope) {
            return false;
        }
    }
    
    //All clear, proceed to declare
    m_buckets[bucket].push_front(Buckets(id,lineNum,currentScope));
    m_scopeTracker.push(id);
    return true;
}

int NameTableImpl::find(const string& id) const
{
    int bucket = hashy(id);

    list<Buckets>:: const_iterator it;
    for (it = m_buckets[bucket].begin(); it != m_buckets[bucket].end(); it++) {

        if (id == it->m_id) {
            return it->m_lineNum;
        }
    }
    return -1;
}



//*********** NameTable functions **************

// For the most part, these functions simply delegate to NameTableImpl's
// functions.

NameTable::NameTable()
{
    m_impl = new NameTableImpl;
}

NameTable::~NameTable()
{
    delete m_impl;
}

void NameTable::enterScope()
{
    m_impl->enterScope();
}

bool NameTable::exitScope()
{
    return m_impl->exitScope();
}

bool NameTable::declare(const string& id, int lineNum)
{
    return m_impl->declare(id, lineNum);
}

int NameTable::find(const string& id) const
{
    return m_impl->find(id);
}
