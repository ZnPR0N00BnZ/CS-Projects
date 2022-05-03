#include "Sequence.h"

Sequence::Sequence(): m_size(0)
{};

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

    if (pos > size() || pos < 0 || pos > DEFAULT_MAX_ITEMS-1) {
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
    if (m_size == DEFAULT_MAX_ITEMS) {
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
    //temps are in the individual array, instead of creating an entire temp array var
   
    if (size() >= other.size()) {
        for (int i=0; i<size(); i++) {
            if (i<other.size()) { //at the point where both lengths are still equal
            ItemType temp = m_array[i];
            m_array[i] = other.m_array[i];
            other.m_array[i] = temp;
            }
            else if (i >= other.size()){ //beyond above mentioned point
                other.insert(i,m_array[i]);
                erase(i);
            }
        }
    }
    else { //other.size() > size()
        for (int i=0; i<other.size(); i++) {
            if (i<size()) {
            ItemType temp = other.m_array[i];
            other.m_array[i] = m_array[i];
            m_array[i] = temp;
            }
            else if (i >= size()) {
                insert(i,m_array[i]);
                other.erase(i);
            }
    }
        int tempSize = size();
        m_size = other.m_size;
        other.m_size = tempSize;
}
}
