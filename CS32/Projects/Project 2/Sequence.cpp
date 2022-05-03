
#include "Sequence.h"

Sequence::Node::Node(ItemType data) {
    m_data= data;
    next = nullptr;
    prev = nullptr;
}


Sequence::~Sequence() {

        Node * p = head;
        while (p != nullptr) {
            Node * n = p->next;
            delete p;
            p = n;
    }
}
 

Sequence::Sequence(const Sequence& other) {
    
    
    if (other.head == nullptr) {
        head = nullptr;
    }
    else {
        m_size = other.m_size;
        
        //initialise first node
        Node * otherCurrent= other.head;
        Node * ourCurrent = new Node(otherCurrent->m_data);
        head = ourCurrent;
        
        Node * p = head;
        //loop to copy other nodes
        while (otherCurrent->next != nullptr) {
            otherCurrent = otherCurrent->next;
            ourCurrent->next = new Node (otherCurrent->m_data);
            p = p->next;
            p->prev = ourCurrent;
            ourCurrent=ourCurrent->next;
        }
    }
    
}



Sequence& Sequence::operator=(const Sequence& other) {
    
    if (this == &other)
        return *this;
    int size = other.size();
    Sequence temp;
    ItemType testValue;
    for (int k = 0; k < size; k++)
    {
        other.get(k, testValue);
        temp.insert(k, testValue);
    }
    swap(temp);
    this->m_size = size;
    return *this;
}


Sequence::Sequence(): m_size(0)
{
    head = nullptr;
}


bool Sequence::empty() const {
    return m_size == 0 && head == nullptr;
}

int Sequence::size() const {
    return m_size;
}


int Sequence::insert(int pos, const ItemType& value){
    if (pos < 0 || pos > m_size) {
        return -1;
    }
    
    //if empty list or 1 element only
    if (head== nullptr || pos == 0) {
        Node * p = new Node(value);
        p->next = head;
        head = p;
        m_size++;
    }
    //add to rear
    else if (pos == m_size) {
        Node *p = head;
        Node * temp = new Node(value);
        while (p->next != nullptr) {
            p=p->next;
        }
        p->next = temp;
        temp->prev = p;
        m_size++;
    }
    //middle case and front case
    else {
        Node * temp = new Node(value);
        Node * p = head;
        for (int i=0; i < pos-1; i++) {
            p = p->next;
        }
        temp->next = p->next;
        temp->prev = p;
        p->next = temp;
        p->next->prev = temp;
        m_size++;
    }
    return pos;
}

int Sequence::insert(const ItemType& value) {
    //empty list case
    if (head== nullptr) {
        Node * p = new Node(value);
        p->next = head;
        head = p;
        m_size++;
        return 0;
    }
    // 1 element case
    else if (head->next == nullptr && head ->prev == nullptr) {
        Node * p = new Node(value);
        if (value <= head->m_data) {
            p->next = head;
            head->prev = p;
            head = p;
            m_size++;
            return 0;
        }
        else { //value > head->m_data
            head->next = p;
            p->prev = head;
            m_size++;
            return 1;
        }
        
    }
    else { //front, middle, back case

        int counter = 0;
        Node * p = new Node(value);
        Node * q = head;
    
        //front case
        if (value <= q->m_data) {
            p->next = q;
            q->prev = p;
            head = p;
            m_size++;
            return 0;
        }
        
        //other cases
        while (q->m_data <= value) {
            //accounts for end case
            if (q->next ==  nullptr) {
                break;
            }
            q = q->next;
            counter++;

        }
        //end case
        if (q->next == nullptr && q->m_data < value) {
        p->next= q->next;
        p->prev = q;
        q->next = p;
            counter++;
        }
        
        //end-1 case (same as middle case)
        else if (q->next ==nullptr && q->m_data >= value) {
            q=q->prev;
            p->next = q->next;
            p->prev = q;
            q->next->prev = p;
            q->next = p;
        }
        
        //middle case
        else {
            q=q->prev;
            p->next = q->next;
            p->prev = q;
            q->next->prev = p;
            q->next = p;
        }
        m_size++;
        return counter;

        
    }
}


bool Sequence::erase(int pos) {
    if (pos < 0 || pos >= m_size || empty()) {
        return false;
    }
    
    else if (pos == 0) {
        Node * p = head;
        head= head->next;
        delete p;
        m_size--;
        return true;
    }
    //middle case
    else if (pos < m_size-1) {
        Node * p = head;
    for (int i = 0; i < pos-1; i++) {
        p = p ->next;
    }
    Node * q = p->next;
    p->next = q->next;
    q->next->prev = p;
    delete q;
    m_size--;
    return true;
    }
    
    //end case
    else if (pos == m_size-1 && pos > 0) {
        Node * p = head;
        while (p->next != nullptr) {
            p = p->next;
        }
        Node * q = p->prev;
        q->next = nullptr;
        delete p;
        m_size--;
        return true;
    }
    //1 element case
    else {
         
            Node* p = head;
            head = nullptr;
            delete p;
            m_size--;
            return true;

    }
}


int Sequence::remove(const ItemType& value) {
    int instance = 0;
    while (find(value) != -1) {
        erase(find(value));
        instance++;
    }
    return instance;
}


bool Sequence::get(int pos, ItemType& value) const {
    if (pos < 0 || pos >= m_size) {
        return false;
    }
    
    else {
        Node * p = head;
        for (int i = 0 ; i < pos; i++) {
            p = p->next;
        }
        value = p->m_data;
        return true;
    }
}


bool Sequence::set(int pos, const ItemType& value) {
    if (pos <0 || pos >= size()) {
        return false;
    }
    else {
        Node * p = head;
        for (int i = 0; i < pos; i++) {
            p= p->next;
        }
        p->m_data = value;
        return true;
    }
}


int Sequence::find(const ItemType& value) const {
    
    int isFound = -1;
    int posCounter = 0;
    Node * p = head;
    //empty case
    if (empty() && p == nullptr) {
        return isFound;
    }
    
    //1 element case
    if (size() == 1 && p->next == nullptr) {
        return 0;
    }
    
    //1st node has value case
    else if (p->m_data == value){
        return 0;
    }
    
    //middle or end case
    else {
    while (p->next != nullptr) {
        p = p->next;
        posCounter++;
        if (p->m_data == value) {
            isFound = posCounter;
            break;
        }
    }
    return isFound;
    }
}



void Sequence::swap(Sequence& other) {
    //swap m_size first
    int temp = m_size;
    m_size = other.m_size;
    other.m_size = temp;
    
    //swap linked list
    Node * tempo = head;
    head = other.head;
    other.head = tempo;
}

int subsequence(const Sequence& seq1, const Sequence& seq2) {
    
    
    if (seq2.empty() || seq2.size() > seq1.size() ) {
        return -1;
    }
    else {
        ItemType value1;
        ItemType value2;
        int PositionTracker = -1;
        
        for (int i =0; i < seq1.size(); i++) {
            seq2.get(0, value2);
            seq1.get(i, value1);
            PositionTracker++;
            
            if (value1 == value2) {
                for (int j = 0; j < seq2.size(); j++) {
                    seq2.get(j, value2);
                    seq1.get(i+j, value1);
                    
                    if (value1!=value2){
                        break;
                    }
                    else if (value1==value2 && j==seq2.size()-1) {
                        return PositionTracker;
                    }
                    
                }
            }
            
        } return -1;
        
    }
}

void interleave(const Sequence& seq1, const Sequence& seq2, Sequence& result) {
    
    
    if (seq1.empty()) {
        result = seq2;
    }
    else if (seq2.empty()) {
        result = seq1;
    }
    
    else if (seq1.size() > seq2.size()) {
        Sequence tempresult;
        int count = 0;
        ItemType value1;
        ItemType value2;
        
        int diff = seq1.size() - seq2.size();
        for (int i = 0; i < seq2.size(); i++) {
            seq1.get(i,value1);
            seq2.get(i,value2);
            tempresult.insert(count,value1);
            count++;
            tempresult.insert(count,value2);
            count++;
        }
        for (int i = 0; i < diff ; i++) {
            seq1.get(seq2.size()+i, value1);
            tempresult.insert(count,value1);
            count++;
        }
        result = tempresult;
    }
        else { //seq2 size > seq1 size
            Sequence tempresult;
            int count = 0;
            ItemType value1;
            ItemType value2;
            
            int diff = seq2.size() - seq1.size();
            for (int i = 0; i < seq1.size(); i++) {
                seq1.get(i,value1);
                seq2.get(i,value2);
                tempresult.insert(count,value1);
                count++;
                tempresult.insert(count,value2);
                count++;
            }
            for (int i = 0; i < diff ; i++) {
                seq2.get(seq1.size()+i, value2);
                tempresult.insert(count,value2);
                count++;
            }
            result=tempresult;
    }
     
}
