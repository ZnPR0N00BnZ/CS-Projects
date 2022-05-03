//
//  newSequence.cpp
//  newSequence
//
//  Created by Lim Zhineng on 4/12/22.
//

#include "newSequence.h"

Sequence::Sequence():m_size(0),m_maxsize(DEFAULT_MAX_ITEMS)
{
    m_array = new ItemType[DEFAULT_MAX_ITEMS];
}

Sequence::Sequence(int value): m_size(0) {
    m_array = new ItemType[value];
    m_maxsize = value;
}

//copy constructor
Sequence::Sequence(const Sequence& src) {
    m_size = src.m_size;
    m_maxsize = src.m_maxsize;
    m_array = new ItemType[m_size];
    for (int i = 0; i < m_size; i++) {
        m_array[i] = src.m_array[i];
    }
}


//asignment operator
Sequence& Sequence::operator= (const Sequence & src) {
    if (this == &src) {
        return *this;
    }
    else {
        delete [] m_array;
        m_size = src.m_size;
        m_array = new ItemType[m_size];
        for (int i = 0; i < m_size; i++) {
            m_array[i] = src.m_array[i];
        }
        return *this;
    }
}

Sequence::~Sequence() {
    delete [] m_array;
}


bool Sequence::empty() const {
    if (m_size == 0) {
        return true;
    }
    else {
        return false;
    }
}

 
int Sequence::size() const {
    return m_size;
}




int Sequence::insert(int pos, const ItemType& value){
 if (pos > size() || pos < 0 || pos > m_maxsize-1) {
     return -1;
 }
 else if (pos == m_size){
     m_array[pos] = value;
     m_size++;
     return pos;
 }
 else {
 for (int i= m_size; i > pos; i--) {
     m_array[i] = m_array[i-1];
 }
     m_array[pos] = value;
     m_size++;
     return pos;
 }
}


int Sequence::insert(const ItemType& value) {
 if (m_size == m_maxsize) {
     return -1;
 }
 
 int x = 0;
 for (int tip = 0; m_array[tip] < value && tip != size(); tip++) {
     x++;
 }
 if (x == size()) {
     m_array[size()] = value;
     m_size++;
     return x;
 }
 else {
 for (int i= m_size; i > x; i--) {
     m_array[i] = m_array[i-1];
 }
     m_array[x] = value;
     m_size++;
     return x;
 
 }
}


bool Sequence::erase(int pos) {
    if (pos < 0 || pos >= size()) {
        return false;
    }
    else {
    for (int i= pos; i < size()-1; i++) {
        m_array[i] = m_array[i+1];
    }
        m_size--;
        return true;
    }
    
}


int Sequence::remove(const ItemType& value) {
 int noRemoved = 0;
 for (int i = 0; i < size(); i++) {
     if (m_array[i] == value) {
         erase(i);
         noRemoved++;
     }
 }
 return noRemoved;
}


bool Sequence::get(int pos, ItemType& value) const {
 if (pos < 0 || pos >= size() ) {
     return false;
 }
 else {
     value = m_array[pos];
     return true;
 }
}

bool Sequence::set(int pos, const ItemType& value) {
    if (pos < 0 || pos >= size() ) {
        return false;
    }
    else {
        m_array[pos] = value;
        return true;
    }
}

int Sequence::find(const ItemType& value) const {
    for (int i=0; i < size(); i++) {
        if (m_array[i] == value) {
            return i;
        }
    }
    return -1;
}

void Sequence::swap(Sequence& other) {
    //swap size first
    int temp = other.m_size;
    other.m_size = m_size;
    m_size = temp;
    
    //swap maxsize
    int temp2 = other.m_maxsize;
    other.m_maxsize = m_maxsize;
    m_maxsize = temp2;
    
    //swap the array
    ItemType * pointer = nullptr;
    pointer = other.m_array;
    other.m_array = this->m_array;
    this->m_array = pointer;
    
    
    }


